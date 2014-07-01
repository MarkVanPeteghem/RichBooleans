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
#include "testable_analysis_with_strings.hpp"
#include "testable_analysis_for_ranges.hpp"
#include "composite_expressions.hpp"
#include "predicates.hpp"
#include <iostream>
#include <list>
#include <stdlib.h>

using namespace RichBool;
using RichBool::detail::String;

#ifdef RICHBOOL_NO_PARTIAL_TEMPLATE_SPECIALIZATION
    typedef Pointer<> POINTER;
    typedef PointerLike<int, PointerLike<int> > POINTER_POINTER;

    typedef PointerToValue<> POINTERV;
    typedef PointerLikeToValue<int, PointerLikeToValue<int> > POINTERV_POINTERV;
#else
    typedef Pointer<> POINTER;
    typedef Pointer<Pointer<> > POINTER_POINTER;

    typedef PointerToValue<> POINTERV;
    typedef PointerToValue<PointerToValue<> > POINTERV_POINTERV;
#endif

RB_TEST(Pointer_Ranges_Equal_Pass)
{
	int a[] = { 1, 2 };
	int *pa[] = { &a[0], &a[1] };

	Equal<Value, POINTER> equal_v_p;
	RB_PASS(rbIN_RANGES(a, a+2, pa, pa+2, Compare<>().That(equal_v_p)));

	Equal<POINTER, Value> equal_p_v;
	RB_PASS(rbIN_RANGES(pa, pa+2, a, a+2, Compare<>().That(equal_p_v)));

	Equal<Value, POINTERV> equal_v_pv;
	RB_PASS(rbIN_RANGES(a, a+2, pa, pa+2, Compare<>().That(equal_v_pv)));

	Equal<POINTERV, Value> equal_pv_v;
	RB_PASS(rbIN_RANGES(pa, pa+2, a, a+2, Compare<>().That(equal_pv_v)));
}

RB_TEST(Pointer_Ranges_Less_Pass)
{
	int a[] = { 1, 2 };
	int *pa[] = { &a[0], &a[1] };

	int b[] = { 3, 4 };
	int *pb[] = { &b[0], &b[1] };

	Less<Value, POINTER > rb1;
	RB_PASS(rbIN_RANGES(a, a+2, pb, pb+2, Compare<>().That(rb1)));

	Less<POINTER, Value> rb2;
	RB_PASS(rbIN_RANGES(pa, pa+2, b, b+2, Compare<>().That(rb2)));
}

RB_TEST(Value_And_Pointer_Ranges_Equal_Fail)
{
	int a[] = { 1, 2 };

	int b[] = { 1, 4 };
	int *pb[] = { &b[0], &b[1] };

	SharedExpression pe = PrefixIndex("*", 1);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(1, ":")("2", true)(" == ")
			.expr(pe, ":")("4", true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ", "a", "a+2", "pb", "pb+2");
	analysis.AddAnalyses(arrAnalyses, 1);

	Equal<Value, POINTER> equal_v_p;
	RB_FAIL(rbIN_RANGES(a, a+2, pb, pb+2, Compare<>().That(equal_v_p)), analysis);

	Equal<Value, POINTERV> equal_v_pv;
	RB_FAIL(rbIN_RANGES(a, a+2, pb, pb+2, Compare<>().That(equal_v_pv)), analysis);
}

RB_TEST(Two_Pointer_Ranges_Equal_Fail)
{
	int a[] = { 1, 2 };
	int *pa[] = { &a[0], &a[1] };

	int b[] = { 1, 4 };
	int *pb[] = { &b[0], &b[1] };

	SharedExpression pe1 = PrefixIndex("*", 1),
		pe2 = PrefixIndex("*", 1);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).expr(pe1, ":")("2", true)(" == ")
			.expr(pe2, ":")("4", true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ", "pa", "pa+2", "pb", "pb+2");
	analysis.AddAnalyses(arrAnalyses, 1);

	Equal<POINTER, POINTER> equal_p_p;
	RB_FAIL(rbIN_RANGES(pa, pa+2, pb, pb+2, Compare<>().That(equal_p_p)), analysis);

	Equal<POINTERV, POINTERV> equal_pv_pv;
	RB_FAIL(rbIN_RANGES(pa, pa+2, pb, pb+2, Compare<>().That(equal_pv_pv)), analysis);
}

RB_TEST(Value_And_Pointer_Ranges_With_NullPointer_Equal_Fail)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 1, 2 };

	int b[] = { 1, 4 };
	int *pb[] = { &b[0], 0 };

	SharedExpression pe = PrefixIndex("*", 1);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(Analysis::BadValue).idx(1, ":")("2", true)(" == ")
			.expr(pe, ":")(PtrToString(pb+1)+" -> "+GetNullPtrString(), false)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ", "a", "a+2", "pb", "pb+2");
	analysis.AddAnalyses(arrAnalyses, 1);
	analysis.SetState(Analysis::BadValue);

	Equal<Value, POINTER> equal_v_p;
	RB_FAIL(rbIN_RANGES(a, a+2, pb, pb+2, Compare<>().That(equal_v_p)), analysis);

	Equal<Value, POINTERV> equal_v_pv;
	RB_FAIL(rbIN_RANGES(a, a+2, pb, pb+2, Compare<>().That(equal_v_pv)), analysis);
}

RB_TEST(Pointer_Pointer_Ranges_Equal_Pass)
{
	int a[] = { 1, 2 };
	int *pa[] = { &a[0], &a[1] };
	int **ppa[] = { &pa[0], &pa[1] };

	int b[] = { 1, 2 };
	int *pb[] = { &b[0], &b[1] };
	int **ppb[] = { &pb[0], &pb[1] };

	Equal<Value, POINTER_POINTER > equal_v_pp;
	RB_PASS(rbIN_RANGES(a, a+2, ppb, ppb+2, Compare<>().That(equal_v_pp)));

	Equal<POINTER_POINTER, Value> equal_pp_v;
	RB_PASS(rbIN_RANGES(ppa, ppa+2, b, b+2, Compare<>().That(equal_pp_v)));

	Equal<POINTERV_POINTERV, Value> equal_pvpv_v;
	RB_PASS(rbIN_RANGES(ppa, ppa+2, b, b+2, Compare<>().That(equal_pvpv_v)));

	Equal<POINTER, POINTER_POINTER > equal_p_pp;
	RB_PASS(rbIN_RANGES(pa, pa+2, ppb, ppb+2, Compare<>().That(equal_p_pp)));
}

RB_TEST(Value_And_PointerPointer_Ranges_Equal_Fail)
{
	int a[] = { 1, 2 };

	int b[] = { 1, 4 };
	int *pb[] = { &b[0], &b[1] };
	int **ppb[] = { &pb[0], &pb[1] };

	SharedExpression pe = PrefixPrefixIndex("*", "*", 1);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(1, ":")("2", true)(" == ").expr(pe, ":")("4", true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ", "a", "a+2", "ppb", "ppb+2");
	analysis.AddAnalyses(arrAnalyses, 1);

	Equal<Value, POINTER_POINTER> equal_v_pp;
	RB_FAIL(rbIN_RANGES(a, a+2, ppb, ppb+2, Compare<>().That(equal_v_pp)), analysis);

	Equal<Value, POINTERV_POINTERV> equal_v_pvpv;
	RB_FAIL(rbIN_RANGES(a, a+2, ppb, ppb+2, Compare<>().That(equal_v_pvpv)), analysis);
}

RB_TEST(Pointer_And_PointerPointer_Ranges_Equal_Fail)
{
	int a[] = { 1, 2 };
	int *pa[] = { &a[0], &a[1] };

	int b[] = { 1, 4 };
	int *pb[] = { &b[0], &b[1] };
	int **ppb[] = { &pb[0], &pb[1] };

	SharedExpression ppe1 = PrefixIndex("*", 1),
		ppe2 = PrefixPrefixIndex("*", "*", 1);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).expr(ppe1, ":")("2", true)(" == ").expr(ppe2, ":")("4", true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ", "pa", "pa+2", "ppb", "ppb+2");
	analysis.AddAnalyses(arrAnalyses, 1);

	Equal<POINTER, POINTER_POINTER > rb2;
	RB_FAIL(rbIN_RANGES(pa, pa+2, ppb, ppb+2, Compare<>().That(rb2)), analysis);
}

RB_TEST(PointerPointer_And_Value_Ranges_Equal_Fail)
{
	int a[] = { 1, 2 };
	int *pa[] = { &a[0], &a[1] };
	int **ppa[] = { &pa[0], &pa[1] };

	int b[] = { 1, 4 };

	SharedExpression pe = PrefixPrefixIndex("*", "*", 1);
	SharedExpression ie = new IndexExpression(1);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).expr(pe, ":")("2", true)(" == ").expr(ie, ":")("4", true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ", "ppa", "ppa+2", "b", "b+2");
	analysis.AddAnalyses(arrAnalyses, 1);

	Equal<POINTER_POINTER, Value> rb3;
	RB_FAIL(rbIN_RANGES(ppa, ppa+2, b, b+2, Compare<>().That(rb3)), analysis);
}

RB_TEST(PointerPointer_And_Pointer_Ranges_Equal_Fail)
{
	int a[] = { 1, 2 };
	int *pa[] = { &a[0], &a[1] };
	int **ppa[] = { &pa[0], &pa[1] };

	int b[] = { 1, 4 };
	int *pb[] = { &b[0], &b[1] };

	SharedExpression pe1 = PrefixPrefixIndex("*", "*", 1), pe2 = PrefixIndex("*", 1);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).expr(pe1, ":")("2", true)(" == ").expr(pe2, ":")("4", true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ", "ppa", "ppa+2", "pb", "pb+2");
	analysis.AddAnalyses(arrAnalyses, 1);

	Equal<POINTER_POINTER, POINTER > rb4;
	RB_FAIL(rbIN_RANGES(ppa, ppa+2, pb, pb+2, Compare<>().That(rb4)), analysis);
}

RB_TEST(PointerPointer_And_PointerPointer_Ranges_Equal_Fail)
{
	int a[] = { 1, 2 };
	int *pa[] = { &a[0], &a[1] };
	int **ppa[] = { &pa[0], &pa[1] };

	int b[] = { 1, 4 };
	int *pb[] = { &b[0], &b[1] };
	int **ppb[] = { &pb[0], &pb[1] };

	SharedExpression pe1 = PrefixPrefixIndex("*", "*", 1),
		pe2 = PrefixPrefixIndex("*", "*", 1);


	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).expr(pe1, ":")("2", true)(" == ").expr(pe2, ":")("4", true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ", "ppa", "ppa+2", "ppb", "ppb+2");
	analysis.AddAnalyses(arrAnalyses, 1);

	Equal<POINTER_POINTER, POINTER_POINTER > rb5;
	RB_FAIL(rbIN_RANGES(ppa, ppa+2, ppb, ppb+2, Compare<>().That(rb5)), analysis);
}

RB_TEST(PointerPointer_Ranges_With_NullPointer_Equal_Fail)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 1, 2 };

	int b[] = { 1, 4 };
	int *pb[] = { &b[0], 0 };
	int **ppb[] = { &pb[0], &pb[1] };

	SharedExpression pe = PrefixPrefixIndex("*", "*", 1);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(Analysis::BadValue).idx(1, ":")("2", true)(" == ")
			.expr(pe, ":")(PtrToString(&ppb[1])+" -> "+PtrToString(&pb[1])+" -> "+GetNullPtrString(), false)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ", "a", "a+2", "ppb", "ppb+2");
	analysis.AddAnalyses(arrAnalyses, 1);
	analysis.SetState(Analysis::BadValue);

	Equal<Value, POINTER_POINTER > rb1;
	RB_FAIL(rbIN_RANGES(a, a+2, ppb, ppb+2, Compare<>().That(rb1)), analysis);
}

RB_TEST(PointerPointer_Ranges_With_NullPointerPointer_Equal_Fail)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 1, 2 };

	int b[] = { 1, 4 };
	int *pb[] = { &b[0], 0 };
	int **ppb[] = { &pb[0], 0 };

	SharedExpression pe = PrefixPrefixIndex("*", "*", 1);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(Analysis::BadValue).idx(1, ":")("2", true)(" == ")
			.expr(pe, ":")(PtrToString(&ppb[1])+" -> "+GetNullPtrString(), false)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ", "a", "a+2", "ppb", "ppb+2");
	analysis.AddAnalyses(arrAnalyses, 1);
	analysis.SetState(Analysis::BadValue);

	POINTER_POINTER pp;
	pp.ToString(ppb[1], MakeString());

	Equal<Value, POINTER_POINTER > rb1;
	RB_FAIL(rbIN_RANGES(a, a+2, ppb, ppb+2, Compare<>().That(rb1)), analysis);
}

RB_TEST(ListIterator_Range_Pass)
{
    int a[] = { 1, 2 };
    std::list<int> l;
    l.push_back(1);
    l.push_back(2);

    std::list<int>::iterator lia[2];
    std::list<int>::iterator it = l.begin();
    lia[0] = it;
    ++it;
    lia[1] = it;

    Equal<Value, PointerLike<int> > rb;
    RB_PASS(rbIN_RANGES(a, a+2, lia, lia+2, Compare<>().That(rb)));
}

RB_TEST(ListIterator_Pointer_Range_Pass)
{
    int a[] = { 1, 2 };

    std::list<int*> l;
    l.push_back(&a[0]);
    l.push_back(&a[1]);

    std::list<int*>::iterator lia[2];
    std::list<int*>::iterator it = l.begin();
    lia[0] = it;
    ++it;
    lia[1] = it;

#ifdef RICHBOOL_NO_PARTIAL_TEMPLATE_SPECIALIZATION
    Equal<Value, PointerLike<int, PointerLike<int> > > rb;
#else
    Equal<Value, PointerLike<int, Pointer<> > > rb;
#endif

    RB_PASS(rbIN_RANGES(a, a+2, lia, lia+2, Compare<>().That(rb)));
}

RB_TEST(Pointer_ListIterator_Range_Pass)
{
    int a[] = { 1, 2 };

    std::list<int> l;
    l.push_back(1);
    l.push_back(2);

    std::list<int>::iterator lia[2];
    std::list<int>::iterator it = l.begin();
    lia[0] = it;
    ++it;
    lia[1] = it;

    std::list<int>::iterator *plia[2] = { &lia[0], &lia[1] };

#ifdef RICHBOOL_NO_PARTIAL_TEMPLATE_SPECIALIZATION
    Equal<Value, PointerLike<int, PointerLike<int> > > rb;
#else
    Equal<Value, Pointer<PointerLike<int> > > rb;
#endif

    RB_PASS(rbIN_RANGES(a, a+2, plia, plia+2, Compare<>().That(rb)));
}


struct EqualPCore: public RichBool::FunctorCore
{
	bool operator()(int a, int b) const
	{
		return a==b;
	}

	const char* GetTextAfter1() const
	{ return " == "; }

	typedef unsigned int Points;

	Points GetPoints(int a, int b) const
	{
		int diff = abs(a-b);
		return diff > 10 ? 0 : 10-diff;
	}
	Points GetGood() const
	{
		return 10;
	}
};

template <class GetValue1=Value, class GetValue2=Value, class Stringize_=MakeString>
struct EqualP:
	public RichBool::Wrapper2Arg<EqualPCore, GetValue1, GetValue2, Stringize_>
{
	EqualP(GetValue1 gv1=GetValue1(), GetValue2 gv2=GetValue2()):
		RichBool::Wrapper2Arg<EqualPCore, GetValue1, GetValue2, Stringize_>(gv1, gv2)
	{}
};

RB_TEST(Value_And_Pointer_Ranges_Equal_Fail_PartialMatching)
{
	int a[] = { 1, 2 };

	int b[] = { 1, 4, 3 };
	int *pb[] = { &b[0], &b[1], &b[2] };

	SharedExpression pe = PrefixIndex("*", 2);

	Analysis *arrAnalyses[] = {
		new Single(1, 2, "4", new IndexExpression(1), true),
		MakeGeneralAnalysis(false).idx(1, ":")("2", true)(" == ")
			.expr(pe, ":")("3", true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ", "a", "a+2", "pb", "pb+3");
	analysis.AddAnalyses(arrAnalyses, 2);

	EqualP<Value, POINTER> equal_v_p;
	RB_FAIL(rbIN_RANGES(a, a+2, pb, pb+3, Compare<>().That(equal_v_p)), analysis);

	EqualP<Value, POINTERV> equal_v_pv;
	RB_FAIL(rbIN_RANGES(a, a+2, pb, pb+3, Compare<>().That(equal_v_pv)), analysis);
}

RB_TEST(Pointer_And_Value_Ranges_Equal_Fail_PartialMatching)
{
	int a[] = { 1, 2 };

	int b[] = { 1, 4, 3 };
	int *pb[] = { &b[0], &b[1], &b[2] };

	SharedExpression pe = PrefixIndex("*", 2);

	Analysis *arrAnalyses[] = {
		new Single(0, 2, "4", new IndexExpression(1), true),
		MakeGeneralAnalysis(false).expr(pe, ":")("3", true)(" == ")
			.idx(1, ":")("2", true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ", "pb", "pb+3", "a", "a+2");
	analysis.AddAnalyses(arrAnalyses, 2);

	EqualP<POINTER, Value> equal_v_p;
	RB_FAIL(rbIN_RANGES(pb, pb+3, a, a+2, Compare<>().That(equal_v_p)), analysis);

	EqualP<POINTERV, Value> equal_v_pv;
	RB_FAIL(rbIN_RANGES(pb, pb+3, a, a+2, Compare<>().That(equal_v_pv)), analysis);
}
