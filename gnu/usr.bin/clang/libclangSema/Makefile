# $OpenBSD: Makefile,v 1.3 2019/01/27 16:59:42 patrick Exp $

LIB=	clangSema
NOPIC=
NOPROFILE=

CPPFLAGS+=	${CLANG_INCLUDES}

.include <bsd.own.mk>
SRCS=	AnalysisBasedWarnings.cpp \
	CodeCompleteConsumer.cpp \
	DeclSpec.cpp \
	DelayedDiagnostic.cpp \
	IdentifierResolver.cpp \
	JumpDiagnostics.cpp \
	MultiplexExternalSemaSource.cpp \
	ParsedAttr.cpp \
	Scope.cpp \
	ScopeInfo.cpp \
	Sema.cpp \
	SemaAccess.cpp \
	SemaAttr.cpp \
	SemaCXXScopeSpec.cpp \
	SemaCast.cpp \
	SemaChecking.cpp \
	SemaCodeComplete.cpp \
	SemaConsumer.cpp \
	SemaCoroutine.cpp \
	SemaCUDA.cpp \
	SemaDecl.cpp \
	SemaDeclAttr.cpp \
	SemaDeclCXX.cpp \
	SemaDeclObjC.cpp \
	SemaExceptionSpec.cpp \
	SemaExpr.cpp \
	SemaExprCXX.cpp \
	SemaExprMember.cpp \
	SemaExprObjC.cpp \
	SemaFixItUtils.cpp \
	SemaInit.cpp \
	SemaLambda.cpp \
	SemaLookup.cpp \
	SemaObjCProperty.cpp \
	SemaOpenMP.cpp \
	SemaOverload.cpp \
	SemaPseudoObject.cpp \
	SemaStmt.cpp \
	SemaStmtAsm.cpp \
	SemaStmtAttr.cpp \
	SemaTemplate.cpp \
	SemaTemplateDeduction.cpp \
	SemaTemplateInstantiate.cpp \
	SemaTemplateInstantiateDecl.cpp \
	SemaTemplateVariadic.cpp \
	SemaType.cpp \
	TypeLocBuilder.cpp

.PATH:	${.CURDIR}/../../../llvm/tools/clang/lib/Sema

install:
	@# Nothing here so far ...

.include <bsd.lib.mk>
