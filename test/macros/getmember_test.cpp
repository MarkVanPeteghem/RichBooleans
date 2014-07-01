//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include "rbtest.hpp"
#include "richbool/richbool.hpp"
#include "richbool/std.hpp"
#include "composite_expressions.hpp"

struct StructWithIntA
{
	StructWithIntA(int n): a(n), ca(n), ccpa(&a)
	{
		pa = &a;
	}

	int a, *pa;
	const int ca;
	const int * const ccpa;

	int GetA() const { return a; }
	const int& GetARef() const { return a; }
	int* GetAPointer() const { return pa; }

private:
	StructWithIntA& operator=(const StructWithIntA &)
	{
		return *this;
	}
};

#ifndef RICHBOOL_NO_TEMPLATE_TYPE_LOOKUP
static RichBool::GetMember<StructWithIntA, int> gm(&StructWithIntA::a, ".a");
static RichBool::Equal<RichBool::GetMember<StructWithIntA, int> > equal_useMember(gm);

static RichBool::GetMember<StructWithIntA, int> gmc(&StructWithIntA::ca, ".ca");
static RichBool::Equal<RichBool::GetMember<StructWithIntA, int> > equal_useConstMember(gmc);

static RichBool::CallMethod<StructWithIntA, int> method(&StructWithIntA::GetA, ".GetA()");
static RichBool::Equal<RichBool::CallMethod<StructWithIntA, int> > equal_useMethod(method);

static RichBool::CallMethod<StructWithIntA, const int&> ref_method(&StructWithIntA::GetARef, ".GetARef()");
static RichBool::Equal<RichBool::CallMethod<StructWithIntA, const int&> > equal_useRefMethod(ref_method);

static RichBool::GetMember<StructWithIntA, int, RichBool::Pointer<> > gmp(&StructWithIntA::pa, ".pa");
static RichBool::Equal<RichBool::GetMember<StructWithIntA, int, RichBool::Pointer<> > >
	equal_usePointerMember(gmp);

static RichBool::GetMember<StructWithIntA, const int, RichBool::Pointer<> > gmccp(&StructWithIntA::ccpa, ".ccpa");
static RichBool::Equal<RichBool::GetMember<StructWithIntA, const int, RichBool::Pointer<> > >
	equal_useCCPointerMember(gmccp);

static RichBool::CallMethod<StructWithIntA, int, RichBool::Pointer<> > ptrMethod(&StructWithIntA::GetAPointer, ".GetAPointer()");
static RichBool::Equal<RichBool::CallMethod<StructWithIntA, int, RichBool::Pointer<> > >
	equal_usePtrMethod(ptrMethod);

static RichBool::Pointer<RichBool::GetMember<StructWithIntA, int> > memberOfPtr(gm);
static RichBool::Equal<RichBool::Pointer<RichBool::GetMember<StructWithIntA, int> > >
	equal_useMemberOfPtr(memberOfPtr);

static RichBool::PointerToValue<RichBool::CallMethod<StructWithIntA, int> > methodOnPtr(method);
static RichBool::Equal<RichBool::PointerToValue<RichBool::CallMethod<StructWithIntA, int> > >
	equal_useMethodOnPtr(methodOnPtr);

#else

static RichBool::GetMemberArg<StructWithIntA, int, int> gm(&StructWithIntA::a, ".a");
static RichBool::Equal<RichBool::GetMemberArg<StructWithIntA, int, int> > equal_useMember(gm);

static RichBool::GetMemberArg<StructWithIntA, int, int> gmc(&StructWithIntA::ca, ".ca");
static RichBool::Equal<RichBool::GetMemberArg<StructWithIntA, int, int> > equal_useConstMember(gmc);

static RichBool::CallMethodArg<StructWithIntA, int, int> method(&StructWithIntA::GetA, ".GetA()");
static RichBool::Equal<RichBool::CallMethodArg<StructWithIntA, int, int> > equal_useMethod(method);

static RichBool::CallMethodArg<StructWithIntA, const int&, const int&> ref_method(&StructWithIntA::GetARef, ".GetARef()");
static RichBool::Equal<RichBool::CallMethodArg<StructWithIntA, const int&, const int&> > equal_useRefMethod(ref_method);

static RichBool::GetMemberArg<StructWithIntA, int, int*, RichBool::Pointer<> > gmp(&StructWithIntA::pa, ".pa");
static RichBool::Equal<RichBool::GetMemberArg<StructWithIntA, int, int*, RichBool::Pointer<> > >
	equal_usePointerMember(gmp);

static RichBool::GetMemberArg<StructWithIntA, const int, const int*, RichBool::Pointer<> > gmccp(&StructWithIntA::ccpa, ".ccpa");
static RichBool::Equal<RichBool::GetMemberArg<StructWithIntA, const int, const int*, RichBool::Pointer<> > >
	equal_useCCPointerMember(gmccp);

static RichBool::CallMethodArg<StructWithIntA, int, int*, RichBool::Pointer<> > ptrMethod(&StructWithIntA::GetAPointer, ".GetAPointer()");
static RichBool::Equal<RichBool::CallMethodArg<StructWithIntA, int, int*, RichBool::Pointer<> > >
	equal_usePtrMethod(ptrMethod);

static RichBool::PointerLike<int, RichBool::GetMemberArg<StructWithIntA, int, int> > memberOfPtr(gm);
static RichBool::Equal<RichBool::PointerLike<int, RichBool::GetMemberArg<StructWithIntA, int, int> > >
	equal_useMemberOfPtr(memberOfPtr);

static RichBool::PointerLikeToValue<int, RichBool::CallMethodArg<StructWithIntA, int, int> > methodOnPtr(method);
static RichBool::Equal<RichBool::PointerLikeToValue<int, RichBool::CallMethodArg<StructWithIntA, int, int> > >
	equal_useMethodOnPtr(methodOnPtr);

#endif // #ifndef RICHBOOL_NO_TEMPLATE_TYPE_LOOKUP

RB_TEST(GetMemberA_Pass)
{
	StructWithIntA s(1);

	RB_PASS(rb2_RB(s, 1, equal_useMember));
}

RB_TEST(GetMemberA_Fail)
{
	StructWithIntA s(1);

	RichBool::SharedExpression se = SuffixText(".a", "s");

	RichBool::SharedAnalysis analysisEqual =
		(RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false).expr(se, ":")("1", true)(" == ")
			.expr("2", ":")("2", true);

	RB_FAIL(rb2_RB(s, 2, equal_useMember), *analysisEqual);
}

RB_TEST(GetMemberCA_Pass)
{
	StructWithIntA s(1);

	RB_PASS(rb2_RB(s, 1, equal_useConstMember));
}

RB_TEST(GetMemberCA_Fail)
{
	StructWithIntA s(1);

	RichBool::SharedExpression se = SuffixText(".ca", "s");

	RichBool::SharedAnalysis analysisEqual =
		(RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false).expr(se, ":")("1", true)(" == ")
			.expr("2", ":")("2", true);

	RB_FAIL(rb2_RB(s, 2, equal_useConstMember), *analysisEqual);
}

RB_TEST(CallMethodGetA_Pass)
{
	StructWithIntA s(1);

	RB_PASS(rb2_RB(s, 1, equal_useMethod));
}

RB_TEST(CallMethodGetA_Fail)
{
	StructWithIntA s(1);

	RichBool::SharedExpression se = SuffixText(".GetA()", "s");

	RichBool::SharedAnalysis analysisEqual =
		(RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false).expr(se, ":")("1", true)(" == ")
			.expr("2", ":")("2", true);

	RB_FAIL(rb2_RB(s, 2, equal_useMethod), *analysisEqual);
}

RB_TEST(CallMethodGetARef_Pass)
{
	StructWithIntA s(1);

	RB_PASS(rb2_RB(s, 1, equal_useRefMethod));
}

RB_TEST(CallMethodGetARef_Fail)
{
	StructWithIntA s(1);

	RichBool::SharedExpression se = SuffixText(".GetARef()", "s");

	RichBool::SharedAnalysis analysisEqual =
		(RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false).expr(se, ":")("1", true)(" == ")
			.expr("2", ":")("2", true);

	RB_FAIL(rb2_RB(s, 2, equal_useRefMethod), *analysisEqual);
}

RB_TEST(GetMemberPA_Pass)
{
	StructWithIntA s(1);

	RB_PASS(rb2_RB(s, 1, equal_usePointerMember));
}

RB_TEST(GetMemberPA_Fail)
{
	StructWithIntA s(1);

	RichBool::SharedExpression pse = PrefixSuffixText("*", ".pa", "s");

	RichBool::SharedAnalysis analysisEqual =
		(RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false).expr(pse, ":")("1", true)(" == ")
			.expr("2", ":")("2", true);

	RB_FAIL(rb2_RB(s, 2, equal_usePointerMember), *analysisEqual);
}

RB_TEST(GetMemberCCPA_Pass)
{
	StructWithIntA s(1);

	RB_PASS(rb2_RB(s, 1, equal_useCCPointerMember));
}

RB_TEST(GetMemberCCPA_Fail)
{
	StructWithIntA s(1);

	RichBool::SharedExpression pse = PrefixSuffixText("*", ".ccpa", "s");

	RichBool::SharedAnalysis analysisEqual =
		(RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false).expr(pse, ":")("1", true)(" == ")
			.expr("2", ":")("2", true);

	RB_FAIL(rb2_RB(s, 2, equal_useCCPointerMember), *analysisEqual);
}

RB_TEST(CallMethodGetAPointer_Pass)
{
	StructWithIntA s(1);

	RB_PASS(rb2_RB(s, 1, equal_usePtrMethod));
}

RB_TEST(CallMethodGetAPointer_Fail)
{
	StructWithIntA s(1);

	RichBool::SharedExpression pse = PrefixSuffixText("*", ".GetAPointer()", "s");

	RichBool::SharedAnalysis analysisEqual =
		(RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false).expr(pse, ":")("1", true)(" == ")
			.expr("2", ":")("2", true);

	RB_FAIL(rb2_RB(s, 2, equal_usePtrMethod), *analysisEqual);
}

RB_TEST(GetMemberAOfPtr_Pass)
{
	StructWithIntA s(1);

	RB_PASS(rb2_RB(&s, 1, equal_useMemberOfPtr));
}

RB_TEST(GetMemberAOfPtr_Fail)
{
	StructWithIntA s(1);

	RichBool::SharedExpression se = SuffixPrefixText(".a", "*", "&s");

	RichBool::SharedAnalysis analysisEqual =
		(RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false).expr(se, ":")("1", true)(" == ")
			.expr("2", ":")("2", true);

	RB_FAIL(rb2_RB(&s, 2, equal_useMemberOfPtr), *analysisEqual);
}

RB_TEST(CallMethodGetAOnPtr_Pass)
{
	StructWithIntA s(1);

	RB_PASS(rb2_RB(&s, 1, equal_useMethodOnPtr));
}

RB_TEST(CallMethodGetAOnPtr_Fail)
{
	StructWithIntA s(1);

	RichBool::SharedExpression se = SuffixPrefixText(".GetA()", "*", "&s");

	RichBool::SharedAnalysis analysisEqual =
		(RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false).expr(se, ":")("1", true)(" == ")
			.expr("2", ":")("2", true);

	RB_FAIL(rb2_RB(&s, 2, equal_useMethodOnPtr), *analysisEqual);
}

RB_TEST(GetA_InContainers)
{
	StructWithIntA arr1[] =  { StructWithIntA(1) };
	int arr2[] = { 1 };

	RB_PASS(rbIN_ARRAYS(arr1, arr2, RichBool::Compare<>().That(equal_useMember)));
}
