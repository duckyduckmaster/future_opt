{-# LANGUAGE MultiParamTypeClasses, FlexibleInstances #-}

{-|

Translate a @ClassDecl@ (see "AST") to its @CCode@ (see "CCode.Main")
equivalent.

-}

module CodeGen.ClassDecl () where

import CodeGen.Typeclasses
import CodeGen.CCodeNames
import CodeGen.MethodDecl ()
import CodeGen.ClassTable
import CodeGen.Type
import CodeGen.Trace
import CodeGen.GC
import CodeGen.DTrace

import CCode.Main
import CCode.PrettyCCode ()

import Data.List
import Control.Arrow

import qualified AST.AST as A
import qualified AST.Util as Util
import qualified Identifiers as ID
import qualified Types as Ty

instance Translatable A.ClassDecl (ProgramTable -> CCode FIN) where
  translate cdecl table
      | A.isActive cdecl = translateActiveClass cdecl table
      | A.isShared cdecl = translateSharedClass cdecl table
      | otherwise        = translatePassiveClass cdecl table

methodImpls cdecl table = concatMap methodImpl
  where
    methodImpl mdecl = translate mdecl cdecl table

-- | Translates an active class into its C representation. Note
-- that there are additional declarations in the file generated by
-- "CodeGen.Header"
translateActiveClass cdecl@(A.Class{A.cname, A.cfields, A.cmethods}) table =
    Program $ Concat $
      (LocalInclude "header.h") :
      [traitMethodSelector table cdecl] ++
      [typeStructDecl cdecl] ++
      [runtimeTypeInitFunDecl cdecl] ++
      [tracefunDecl cdecl] ++
      [constructorImpl Active cname] ++
      methodImpls cdecl table cmethods ++
      [dispatchFunDecl cdecl] ++
      [runtimeTypeDecl cname]

typeStructDecl :: A.ClassDecl -> CCode Toplevel
typeStructDecl cdecl@(A.Class{A.cname, A.cfields, A.cmethods}) =
    let typeParams = Ty.getTypeParameters cname in
    StructDecl (AsType $ classTypeName cname) $
               ((encoreActorT, Var "_enc__actor") :
                (map (\ty -> (Ptr ponyTypeT, AsLval $ typeVarRefName ty)) typeParams ++
                   zip
                   (map (translate  . A.ftype) cfields)
                   (map (AsLval . fieldName . A.fname) cfields)))

dispatchFunDecl :: A.ClassDecl -> CCode Toplevel
dispatchFunDecl cdecl@(A.Class{A.cname, A.cfields, A.cmethods}) =
    (Function (Static void) (classDispatchName cname)
     ([(Ptr (Ptr encoreCtxT), encoreCtxVar),
       (Ptr ponyActorT, Var "_a"),
       (Ptr ponyMsgT, Var "_m")])
     (Seq [Assign (Decl (Ptr . AsType $ classTypeName cname, thisVar))
                  (Cast (Ptr . AsType $ classTypeName cname) (Var "_a")),
           Seq $ map assignTypeVar classTypeVars,
           (Switch (Var "_m" `Arrow` Nam "id")
            (
             (if (A.isMainClass cdecl)
              then ponyMainClause :
                   methodClauses (filter ((/= ID.Name "main") . A.methodName) cmethods)
              else methodClauses $ cmethods
             ))
            (Statement $ Call (Nam "printf") [String "error, got invalid id: %zd", AsExpr $ (Var "_m") `Arrow` (Nam "id")]))]))
     where
       classTypeVars = Ty.getTypeParameters cname
       assignTypeVar t =
            Assign (Decl (Ptr ponyTypeT, AsLval $ typeVarRefName t))
                   (Arrow thisName (typeVarRefName t))
       ponyMainClause =
           (Nam "_ENC__MSG_MAIN",
            Seq $ [Assign (Decl (Ptr ponyMainMsgT, Var "msg")) (Cast (Ptr ponyMainMsgT) (Var "_m")),
                   Statement $ Call ((methodImplName cname (ID.Name "main")))
                                    [AsExpr encoreCtxVar,
                                     (Cast (translate cname) (Var "_a")),
                                     AsExpr nullVar,
                                     Call (Nam "_init_argv")
                                          [AsExpr encoreCtxVar,
                                           AsExpr $ (Var "msg") `Arrow` (Nam "argc"),
                                           AsExpr $ (Var "msg") `Arrow` (Nam "argv")]]])
       methodClauses = concatMap methodClause

       methodClause m = (mthdDispatchClause m mArgs) :
                         if not (A.isStreamMethod m)
                         then [oneWaySendDispatchClause m mArgs]
                         else []
         where
           mArgs = (A.methodName &&& A.methodParams) m

       -- explode _enc__Foo_bar_msg_t struct into variable names
       methodUnpackArguments :: A.MethodDecl -> CCode Ty -> [CCode Stat]
       methodUnpackArguments mdecl msgTypeName =
         map unpackMethodTypeParam (A.methodTypeParams mdecl) ++
         zipWith unpack (A.methodParams mdecl) [1..]
           where
             unpackMethodTypeParam :: Ty.Type -> CCode Stat
             unpackMethodTypeParam ty =
               (Assign (Decl (Ptr ponyTypeT, AsLval $ typeVarRefName ty))
                       ((Cast (msgTypeName) (Var "_m")) `Arrow` (typeVarRefName ty)))

             unpack :: A.ParamDecl -> Int -> CCode Stat
             unpack A.Param{A.pname, A.ptype} n =
               (Assign (Decl (translate ptype, (AsLval . argName $ pname)))
                       ((Cast (msgTypeName) (Var "_m")) `Arrow` (Nam $ "f"++show n)))

       includeCtx xs = Deref encoreCtxVar : xs

       mthdDispatchClause mdecl (mName, mParams)
           | A.isStreamMethod mdecl =
               (futMsgId cname mName,
                Seq $ unpackFuture : arguments' ++
                      gcReceive ++ [streamMethodCall])
           | otherwise =
               (futMsgId cname mName,
                Seq $ unpackFuture : arguments' ++
                      gcReceive ++ [pMethodDecl, methodCall])
           where
             (pMethodArrName, pMethodDecl) = arrMethodTypeVars mdecl
             arguments' = arguments mdecl (futMsgTypeName cname mName)
             gcReceive  =
                 gcRecv mParams
                 (Statement $ Call ponyTraceObject
                                   (includeCtx
                                      [futVar,
                                       futureTypeRecName `Dot` Nam "trace"]))
             streamMethodCall =
                 Statement $ Call (methodImplName cname mName)
                                  (encoreCtxVar :
                                   thisVar :
                                   nullVar :
                                   futVar :
                                   map (AsLval . argName . A.pname) mParams)
             methodCall =
               Statement $
               if null $ Util.filter A.isForward (A.mbody mdecl)
               then Call futureFulfil
                         [AsExpr encoreCtxVar,
                          AsExpr $ futVar,
                          asEncoreArgT (translate $ A.methodType mdecl)
                          (Call (methodImplName cname mName)
                                (encoreCtxVar : thisVar :
                                pMethodArrName :
                                map (AsLval . argName . A.pname) mParams))]
               else forwardMethodCall mName pMethodArrName mParams futVar

       forwardMethodCall = \mName pMethodArrName mParams lastArg ->
                             Call (forwardingMethodImplName cname mName)
                                (encoreCtxVar : thisVar :
                                pMethodArrName :
                                map (AsLval . argName . A.pname) mParams ++
                                [lastArg])
       arguments mdecl ptr = methodUnpackArguments mdecl (Ptr . AsType $ ptr)
       oneWaySendDispatchClause mdecl (mName, mParams) =
           let ptr = oneWayMsgTypeName cname mName
           in (oneWayMsgId cname mName,
               Seq $ arguments mdecl ptr ++
                     gcReceive ++ [pMethodDecl, methodCall])
           where
             (pMethodArrName, pMethodDecl) = arrMethodTypeVars mdecl
             gcReceive = gcRecv mParams
                         (Comm "Not tracing the future in a oneWay send")
             methodCall =
               Statement $
                 if null $ Util.filter A.isForward (A.mbody mdecl)
                 then Call (methodImplName cname mName)
                           (encoreCtxVar : thisVar : pMethodArrName :
                           map (AsLval . argName . A.pname) mParams)
                 else forwardMethodCall mName pMethodArrName mParams nullVar
       unpackFuture =
         let
           lval = Decl (future, futVar)
           rval = (Cast (Ptr $ encMsgT) (Var "_m")) `Arrow` (Nam "_fut")
         in
           Assign lval rval

arrMethodTypeVars mdecl =
  let arrName = "methodTypeVars"
      arr = map (AsExpr . AsLval . typeVarRefName) (A.methodTypeParams mdecl) :: [CCode Expr]
  in (Var arrName, Assign
                       (Decl (Ptr ponyTypeT, Var $ arrName ++ "[]"))
                       (Record arr))

data Activity = Active | Shared | Passive

constructorImpl :: Activity -> Ty.Type -> CCode Toplevel
constructorImpl act cname =
  let
    retType = translate cname
    fName = constructorImplName cname
    args = [(Ptr (Ptr encoreCtxT), encoreCtxVar),
            (Ptr (Ptr ponyTypeT), encoreRuntimeType)]
    fBody = Seq $
      assignThis :
      decorateThis act ++
      [ret thisVar]
  in
    Function retType fName args fBody
  where
    classType = AsType $ classTypeName cname
    thisType = Ptr classType
    cast = Cast thisType
    declThis = Decl (thisType, thisVar)
    runtimeType = Amp $ runtimeTypeName cname
    create = createCall act
    assignThis = Assign declThis $ cast create
    ret = Return

    createCall :: Activity -> CCode Expr
    createCall Active =
      Call encoreCreateName [AsExpr $ Deref encoreCtxVar, runtimeType]
    createCall Shared =
      Call encoreCreateName [AsExpr $ Deref encoreCtxVar, runtimeType]
    createCall Passive =
      Call encoreAllocName [AsExpr $ Deref encoreCtxVar, Sizeof classType]

    decorateThis :: Activity -> [CCode Stat]
    decorateThis Passive = [Assign (thisVar `Arrow` selfTypeField) runtimeType]
    decorateThis _ = []

translateSharedClass cdecl@(A.Class{A.cname, A.cfields, A.cmethods}) table =
  Program $ Concat $
    (LocalInclude "header.h") :
    [traitMethodSelector table cdecl] ++
    [typeStructDecl cdecl] ++
    [runtimeTypeInitFunDecl cdecl] ++
    [tracefunDecl cdecl] ++
    [constructorImpl Shared cname] ++
    methodImpls cdecl table cmethods ++
    [dispatchFunDecl cdecl] ++
    [runtimeTypeDecl cname]

-- | Translates a passive class into its C representation. Note
-- that there are additional declarations (including the data
-- struct for instance variables) in the file generated by
-- "CodeGen.Header"
translatePassiveClass cdecl@(A.Class{A.cname, A.cfields, A.cmethods}) table =
  Program $ Concat $
    (LocalInclude "header.h") :
    [traitMethodSelector table cdecl] ++
    [runtimeTypeInitFunDecl cdecl] ++
    [tracefunDecl cdecl] ++
    [constructorImpl Passive cname] ++
    methodImpls cdecl table cmethods ++
    -- [dispatchfunDecl] ++
    [runtimePassiveTypeDecl cname]
  where
    dispatchfunDecl =
      Function (Static void) (classDispatchName cname)
               ([(Ptr (Ptr encoreCtxT), encoreCtxVar),
                 (Ptr ponyActorT, Var "_a"),
                 (Ptr ponyMsgT, Var "_m")])
               (Comm "Stub! Might be used when we have dynamic dispatch on passive classes")

traitMethodSelector :: ProgramTable -> A.ClassDecl -> CCode Toplevel
traitMethodSelector table A.Class{A.cname, A.ccomposition} =
  let
    retType = Static (Ptr void)
    fname = traitMethodSelectorName
    args = [(Typ "int" , Var "id")]
    cond = Var "id"
    traitTypes = A.typesFromTraitComposition ccomposition
    traitMethods = map (`lookupMethods` table) traitTypes
    cases = concat $ zipWith (traitCase cname) traitTypes traitMethods
    err = String "error, got invalid id: %d"
    defaultCase = Statement $ Call (Nam "printf") [err, AsExpr $ Var "id"]
    switch = Switch cond cases defaultCase
    body = Seq [ switch, Return Null ]
  in
    Function retType fname args body
  where
    traitCase :: Ty.Type -> Ty.Type -> [A.FunctionHeader] ->
                 [(CCode Name, CCode Stat)]
    traitCase cname tname tmethods =
        let
            methodNames = map A.hname tmethods
            caseNames   = map (msgId tname) methodNames
            caseStmts   = map (Return . methodImplName cname) methodNames
        in zip caseNames caseStmts ++
           if Ty.isActiveSingleType tname then
             let
                 futCaseNames = map (futMsgId tname) methodNames
                 futCaseStmts =
                   map (Return . callMethodFutureName cname) methodNames
                 oneWayCaseNames = map (oneWayMsgId tname) methodNames
                 oneWayCaseStmts =
                   map (Return . methodImplOneWayName cname) methodNames
             in
               zip futCaseNames futCaseStmts ++
               zip oneWayCaseNames oneWayCaseStmts
           else
             []

runtimeTypeInitFunDecl :: A.ClassDecl -> CCode Toplevel
runtimeTypeInitFunDecl A.Class{A.cname, A.cfields, A.cmethods} =
    Function void (runtimeTypeInitFnName cname)
                 [(Ptr . AsType $ classTypeName cname, thisVar), (Embed "...", Embed "")]
                   (Seq $
                    (Statement $ Decl (Typ "va_list", Var "params")) :
                    (Statement $ Call (Nam "va_start") [Var "params", thisVar]) :
                    map initRuntimeType typeParams ++
                    [Statement $ Call (Nam "va_end") [Var "params"]])
        where
          typeParams = Ty.getTypeParameters cname
          initRuntimeType ty =
              Assign (thisVar `Arrow` typeVarRefName ty)
                     (Call (Nam "va_arg") [Var "params", Var "pony_type_t *"])

tracefunDecl :: A.ClassDecl -> CCode Toplevel
tracefunDecl A.Class{A.cname, A.cfields, A.cmethods} =
    case find ((== Ty.getId cname ++ "_trace") . show . A.methodName) cmethods of
      Just mdecl@(A.Method{A.mbody}) ->
          Function void (classTraceFnName cname)
                   [(Ptr encoreCtxT, encoreCtxVar), (Ptr void, Var "p")]
                   (Statement $ Call (methodImplName cname (A.methodName mdecl))
                                [Amp encoreCtxVar, AsExpr $ Var "p", AsExpr nullVar])
      Nothing ->
          Function void (classTraceFnName cname)
                   [(Ptr encoreCtxT, ctxArg),
                   (Ptr void, Var "p")]
                   (Seq $
                    (Assign (Decl (Ptr (Ptr encoreCtxT), encoreCtxVar)) (Amp ctxArg)):
                    (Assign (Decl (Ptr . AsType $ classTypeName cname, thisVar))
                            (Var "p")) :
                     runtimeTypeAssignment ++
                     map traceField cfields)
    where
      ctxArg = Var "_ctx_arg"
      runtimeTypeAssignment = map extractTypeVariable typeParams
      extractTypeVariable t =
         if Ty.isTypeVar t then
            Assign (Decl (Ptr ponyTypeT, AsLval $ typeVarRefName t))
                   (Arrow thisName (typeVarRefName t))
         else error "Expected type variable but found concrete type"
      typeParams = Ty.getTypeParameters cname
      traceField A.Field {A.ftype, A.fname} =
        let var = Var . show $ fieldName fname
            field = thisVar `Arrow` fieldName fname
            fieldAssign = Assign (Decl (translate ftype, var)) field
        in Seq [fieldAssign, traceVariable ftype var]

runtimeTypeDecl cname =
  AssignTL
   (Decl (Typ "pony_type_t", AsLval $ runtimeTypeName cname)) $
      DesignatedInitializer $ [ (Nam "id", AsExpr . AsLval $ classId cname)
      , (Nam "size", Call (Nam "sizeof") [AsLval $ classTypeName cname])
      , (Nam "trace", AsExpr . AsLval $ (classTraceFnName cname))
      , (Nam "dispatch", AsExpr . AsLval $ (classDispatchName cname))
      , (Nam "vtable", AsExpr . AsLval $ traitMethodSelectorName)
      ]

runtimePassiveTypeDecl cname =
  AssignTL
   (Decl (Typ "pony_type_t", AsLval $ runtimeTypeName cname)) $
      DesignatedInitializer $ [ (Nam "id", AsExpr . AsLval $ classId cname)
      , (Nam "size", Call (Nam "sizeof") [AsLval $ classTypeName cname])
      , (Nam "trace", AsExpr . AsLval $ (classTraceFnName cname))
      , (Nam "vtable", AsExpr . AsLval $ traitMethodSelectorName)
      ]