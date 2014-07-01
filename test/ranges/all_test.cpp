//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#if defined(_MSC_VER)
	#pragma warning(disable: 4786)
#endif

#include "richbool/richbool.hpp"

#include "rbtest.hpp"
#include "testable_analysis_for_ranges.hpp"
#include "predicates.hpp"
#include "stub_container.hpp"
#include "stub_get_value.hpp"

using namespace RichBool;

RB_TEST(Pass_All)
{
	int a[] = { 2, 8, 10 };

	// empty range:
	RB_PASS(rbIN_RANGE(a, a, All<>().Are(Pred1<IsEven>())));
	RB_PASS(rbIN_RANGE(a, a, All<>(true).Are(Pred1<IsEven>())));
	RB_PASS(rbIN_RANGE(a, 0, All<>().Are(Pred1<IsEven>())));

	// full range
	RB_PASS(rbIN_RANGE(a, a+3, All<>().Are(Pred1<IsEven>())));
	RB_PASS(rbIN_RANGE(a, a+3, All<>(true).Are(Pred1<IsEven>())));
	RB_PASS(rbIN_RANGE(a, 3, All<>().Are(Pred1<IsEven>())));

#ifdef RICHBOOL_LAMBDAS
	RB_PASS(rbIN_RANGE(a, a, All<>().Are(PredToRichBool_1Arg([](int x) { return x%2==0; }))));
#endif
}

RB_TEST(Pass_All_Negated)
{
	int a[] = { 2, 7, 10 };

	RB_PASS(rbIN_RANGE(a, a+3, !All<>().Are(Pred1<IsEven>())));
	RB_PASS(rbIN_RANGE(a, a+3, !All<>(true).Are(Pred1<IsEven>())));
	RB_PASS(rbIN_RANGE(a, 3, !All<>().Are(Pred1<IsEven>())));
}

RB_TEST(Pass_All_NegatedTwice)
{
	int a[] = { 2, 8, 10 };

	// empty range:
	RB_PASS(rbIN_RANGE(a, a, !!All<>().Are(Pred1<IsEven>())));
	RB_PASS(rbIN_RANGE(a, a, !!All<>(true).Are(Pred1<IsEven>())));
	RB_PASS(rbIN_RANGE(a, 0, !!All<>().Are(Pred1<IsEven>())));

	// full range
	RB_PASS(rbIN_RANGE(a, a+3, !!All<>().Are(Pred1<IsEven>())));
	RB_PASS(rbIN_RANGE(a, a+3, !!All<>(true).Are(Pred1<IsEven>())));
	RB_PASS(rbIN_RANGE(a, 3, !!All<>().Are(Pred1<IsEven>())));
}

RB_TEST(Pass_All_Old)
{
	// check that deprecated functionality still works:

	int a[] = { 2, 8, 10 };

	// empty range:
	RB_PASS(rbIN_RANGE_ARG(a, a, All<>(), Pred1<IsEven>()));
	RB_PASS(rbIN_RANGE_ARG(a, a, All<>(true), Pred1<IsEven>()));

	// full range
	RB_PASS(rbIN_RANGE_ARG(a, a+3, All<>(), Pred1<IsEven>()));
	RB_PASS(rbIN_RANGE_ARG(a, a+3, All<>(true), Pred1<IsEven>()));
}

RB_TEST(Fail_All)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("5", true)(")")
	};

	TestableAnalysisOfRange analysis1(
		"predicate applies to all elements in range ", "a", "a+3");
	analysis1.AddAnalyses(arrAnalyses, 1);

	TestableAnalysisOfRange analysis2(
		"predicate applies to all elements in range ", "a", "3");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	int a[] = { 2, 5, 8 };

	RB_FAIL(rbIN_RANGE(a, a+3, All<>().Are(Pred1<IsEven>())), analysis1);
	RB_FAIL(rbIN_RANGE(a, 3, All<>().Are(Pred1<IsEven>())), analysis2);
}

RB_TEST(Fail_All_Negated)
{
	TestableAnalysisOfRange analysis1(Analysis::Ok,
		"predicate applies to all elements in range ", "a", "a+3");
	analysis1.Negate();

	TestableAnalysisOfRange analysis2(Analysis::Ok,
		"predicate applies to all elements in range ", "a", "3");
	analysis2.Negate();

	int a[] = { 2, 4, 8 };

	RB_FAIL(rbIN_RANGE(a, a+3, !All<>().Are(Pred1<IsEven>())), analysis1);
	RB_FAIL(rbIN_RANGE(a, 3, !All<>().Are(Pred1<IsEven>())), analysis2);
}

RB_TEST(Fail_All_Negated_EmptyRange)
{
	TestableAnalysisOfRange analysis1(Analysis::Ok,
		"predicate applies to all elements in range ", "a", "a");
	analysis1.Negate();

	int a[] = { 0 };

	RB_FAIL(rbIN_RANGE(a, a, !All<>().Are(Pred1<IsEven>())), analysis1);
}

RB_TEST(Fail_All_NegatedTwice)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("5", true)(")")
	};

	TestableAnalysisOfRange analysis1(
		"predicate applies to all elements in range ", "a", "a+3");
	analysis1.AddAnalyses(arrAnalyses, 1);

	TestableAnalysisOfRange analysis2(
		"predicate applies to all elements in range ", "a", "3");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	int a[] = { 2, 5, 8 };

	RB_FAIL(rbIN_RANGE(a, a+3, !!All<>().Are(Pred1<IsEven>())), analysis1);
	RB_FAIL(rbIN_RANGE(a, 3, !!All<>().Are(Pred1<IsEven>())), analysis2);
}

RB_TEST(Fail_All_Old)
{
	// check that deprecated functionality still works:

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("5", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to all elements in range ", "a", "a+3");
	analysis.AddAnalyses(arrAnalyses, 1);

	int a[] = { 2, 5, 8 };

	RB_FAIL(rbIN_RANGE_ARG(a, a+3, All<>(), Pred1<IsEven>()), analysis);
}

RB_TEST(Fail_All_Full)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true) ("predicate(").idx(0, ":")("2", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("5", true)(")"),
		MakeGeneralAnalysis(true) ("predicate(").idx(2, ":")("8", true)(")")
	};

	TestableAnalysisOfRange analysis1(
		"predicate applies to all elements in range ", "a", "a+3");
	analysis1.AddAnalyses(arrAnalyses, 3);

	TestableAnalysisOfRange analysis2(
		"predicate applies to all elements in range ", "a", "3");
	analysis2.AddAnalyses(arrAnalyses, 3, false);

	int a[] = { 2, 5, 8 };

	RB_FAIL(rbIN_RANGE(a, a+3, All<>(true).Are(Pred1<IsEven>())), analysis1);
	RB_FAIL(rbIN_RANGE(a, 3, All<>(true).Are(Pred1<IsEven>())), analysis2);
}

RB_TEST(Fail_All_Full_Negated)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("2", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(1, ":")("4", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(2, ":")("8", true)(")")
	};

	TestableAnalysisOfRange analysis1(Analysis::Ok,
		"predicate applies to all elements in range ", "a", "a+3");
	analysis1.AddAnalyses(arrAnalyses, 3);
	analysis1.Negate();

	TestableAnalysisOfRange analysis2(Analysis::Ok,
		"predicate applies to all elements in range ", "a", "3");
	analysis2.AddAnalyses(arrAnalyses, 3, false);
	analysis2.Negate();

	int a[] = { 2, 4, 8 };

	RB_FAIL(rbIN_RANGE(a, a+3, !All<>(true).Are(Pred1<IsEven>())), analysis1);
	RB_FAIL(rbIN_RANGE(a, 3, !All<>(true).Are(Pred1<IsEven>())), analysis2);
}

RB_TEST(Fail_All_Full_NegatedTwice)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true) ("predicate(").idx(0, ":")("2", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("5", true)(")"),
		MakeGeneralAnalysis(true) ("predicate(").idx(2, ":")("8", true)(")")
	};

	TestableAnalysisOfRange analysis1(
		"predicate applies to all elements in range ", "a", "a+3");
	analysis1.AddAnalyses(arrAnalyses, 3);

	TestableAnalysisOfRange analysis2(
		"predicate applies to all elements in range ", "a", "3");
	analysis2.AddAnalyses(arrAnalyses, 3, false);

	int a[] = { 2, 5, 8 };

	RB_FAIL(rbIN_RANGE(a, a+3, !!All<>(true).Are(Pred1<IsEven>())), analysis1);
	RB_FAIL(rbIN_RANGE(a, 3, !!All<>(true).Are(Pred1<IsEven>())), analysis2);
}

RB_TEST(Fail_All_Full_Old)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true) ("predicate(").idx(0, ":")("2", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("5", true)(")"),
		MakeGeneralAnalysis(true) ("predicate(").idx(2, ":")("8", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to all elements in range ", "a", "a+3");
	analysis.AddAnalyses(arrAnalyses, 3);

	int a[] = { 2, 5, 8 };

	RB_FAIL(rbIN_RANGE_ARG(a, a+3, All<>(true), Pred1<IsEven>()), analysis);
}

RB_TEST(OneEmptyRange_InputIterator_Pass)
{
	StubContainer empty;
	RB_PASS(rbIN_RANGE(empty.begin(), empty.end(), All<false>().Are(Pred1<IsEven>())));
	empty.rewind();
	RB_PASS(rbIN_RANGE(empty.begin(), empty.end(), All<false>(true).Are(Pred1<IsEven>())));
	empty.rewind();
	RB_PASS(rbIN_RANGE(empty.begin(), 0, All<false>().Are(Pred1<IsEven>())));
}

RB_TEST(All_InputIterator_Pass)
{
	StubContainer stub(2, 8, 10);
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), All<false>().Are(Pred1<IsEven>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), All<false>(true).Are(Pred1<IsEven>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 3, All<false>().Are(Pred1<IsEven>())));
}

RB_TEST(All_InputIterator_Pass_Negated)
{
	StubContainer stub(2, 7, 10);
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), !All<false>().Are(Pred1<IsEven>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), !All<false>(true).Are(Pred1<IsEven>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 3, !All<false>().Are(Pred1<IsEven>())));
}

RB_TEST(All_InputIterator_Pass_Old)
{
	StubContainer stub(2, 8, 10);
	RB_PASS(rbIN_RANGE_ARG(stub.begin(), stub.end(), All<false>(), Pred1<IsEven>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE_ARG(stub.begin(), stub.end(), All<false>(true), Pred1<IsEven>()));
}

RB_TEST(All_InputIterator_Fail)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("5", true)(")")
	};

	TestableAnalysisOfRange analysis1(
		"predicate applies to all elements in range ", "stub.begin()", "stub.end()");
	analysis1.AddAnalyses(arrAnalyses, 1);

	TestableAnalysisOfRange analysis2(
		"predicate applies to all elements in range ", "stub.begin()", "3");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	StubContainer stub(2, 5, 8);

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), All<false>().Are(Pred1<IsEven>())), analysis1);
	stub.rewind();
	RB_FAIL(rbIN_RANGE(stub.begin(), 3, All<false>().Are(Pred1<IsEven>())), analysis2);
}

RB_TEST(All_InputIterator_Fail_Negated)
{
	TestableAnalysisOfRange analysis1(Analysis::Ok,
		"predicate applies to all elements in range ", "stub.begin()", "stub.end()");
	analysis1.Negate();

	TestableAnalysisOfRange analysis2(Analysis::Ok,
		"predicate applies to all elements in range ", "stub.begin()", "3");
	analysis2.Negate();

	StubContainer stub(2, 6, 8);

	RB_FAIL(rbIN_RANGE(stub.begin(), 3, !All<false>().Are(Pred1<IsEven>())), analysis2);
	stub.rewind();
	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), !All<false>().Are(Pred1<IsEven>())), analysis1);
}

RB_TEST(All_InputIterator_Fail_Negated_EmptyRange)
{
	TestableAnalysisOfRange analysis1(Analysis::Ok,
		"predicate applies to all elements in range ", "stub.begin()", "stub.end()");
	analysis1.Negate();

	StubContainer stub;

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), !All<false>().Are(Pred1<IsEven>())), analysis1);
}

RB_TEST(All_InputIterator_Fail_Old)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("5", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to all elements in range ", "stub.begin()", "stub.end()");
	analysis.AddAnalyses(arrAnalyses, 1);

	StubContainer stub(2, 5, 8);

	RB_FAIL(rbIN_RANGE_ARG(stub.begin(), stub.end(), All<false>(), Pred1<IsEven>()), analysis);
}

RB_TEST(All_InputIterator_Fail_Full)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true) ("predicate(").idx(0, ":")("2", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("5", true)(")"),
		MakeGeneralAnalysis(true) ("predicate(").idx(2, ":")("8", true)(")")
	};

	TestableAnalysisOfRange analysis1(
		"predicate applies to all elements in range ", "stub.begin()", "stub.end()");
	analysis1.AddAnalyses(arrAnalyses, 3);

	TestableAnalysisOfRange analysis2(
		"predicate applies to all elements in range ", "stub.begin()", "3");
	analysis2.AddAnalyses(arrAnalyses, 3, false);

	StubContainer stub(2, 5, 8);

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), All<false>(true).Are(Pred1<IsEven>())), analysis1);
	stub.rewind();
	RB_FAIL(rbIN_RANGE(stub.begin(), 3, All<false>(true).Are(Pred1<IsEven>())), analysis2);
}

RB_TEST(Pass_All_WithStubGetValue)
{
	int a[] = { 2, 8, 10 };

	Pred1<IsEven, StubGetValue> pred(IsEven(), StubGetValue(1));
	RB_PASS(rbIN_RANGE(a, a+3, All<>().Are(pred)));
	RB_PASS(rbIN_RANGE(a, a+3, All<false>().Are(pred)));
}


// with invalid pointers

RB_TEST(Fail_All_BadValue)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 2, 5, 8 };
	int *b[] = { &a[0], 0, &a[2] };

	SharedExpression se=new PrefixedExpression("*", MakeExpression(1));
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(Analysis::BadValue)("predicate(")
			.expr(se, ":")
			(b[1], Pointer<>(), MakeString())(")")
	};

	TestableAnalysisOfRange analysis1(Analysis::BadValue,
		"predicate applies to all elements in range ", "b", "b+3");
	analysis1.AddAnalyses(arrAnalyses, 1);

	Pred1<IsEven, Pointer<> > p;
	RB_FAIL(rbIN_RANGE(b, b+3, All<>().Are(p)), analysis1);
}

RB_TEST(Fail_All_BadValue2)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 1, 5, 8 };
	int *b[] = { &a[0], 0, &a[2] };

	SharedExpression se0=new PrefixedExpression("*", MakeExpression((size_t)0)),
		se1=new PrefixedExpression("*", MakeExpression(1));
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(Analysis::NotOk)("predicate(")
			.expr(se0, ":")
			(b[0], Pointer<>(), MakeString())(")"),
		MakeGeneralAnalysis(Analysis::BadValue)("predicate(")
			.expr(se1, ":")
			(b[1], Pointer<>(), MakeString())(")")
	};

	TestableAnalysisOfRange analysis1(Analysis::BadValue,
		"predicate applies to all elements in range ", "b", "b+3");
	analysis1.AddAnalyses(arrAnalyses, 2);

	Pred1<IsEven, Pointer<> > p;
	RB_FAIL(rbIN_RANGE(b, b+3, All<>().Are(p)), analysis1);
}

RB_TEST(Fail_All_BadValue_ShowAll)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 1, 5, 8 };
	int *b[] = { &a[0], 0, &a[2] };

	SharedExpression se0=new PrefixedExpression("*", MakeExpression((size_t)0)),
		se1=new PrefixedExpression("*", MakeExpression(1)),
		se2=new PrefixedExpression("*", MakeExpression(2));
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(Analysis::NotOk)("predicate(")
			.expr(se0, ":")
			(b[0], Pointer<>(), MakeString())(")"),
		MakeGeneralAnalysis(Analysis::BadValue)("predicate(")
			.expr(se1, ":")
			(b[1], Pointer<>(), MakeString())(")"),
		MakeGeneralAnalysis(Analysis::Ok)("predicate(")
			.expr(se2, ":")
			(b[2], Pointer<>(), MakeString())(")")
	};

	TestableAnalysisOfRange analysis1(Analysis::BadValue,
		"predicate applies to all elements in range ", "b", "b+3");
	analysis1.AddAnalyses(arrAnalyses, 3);

	Pred1<IsEven, Pointer<> > p;
	RB_FAIL(rbIN_RANGE(b, b+3, All<>(true).Are(p)), analysis1);
}

RB_TEST(Fail_All_BadValue_Single)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 2, 5, 8 };
	int *b[] = { &a[0], 0, &a[2] };

	SharedExpression se=new PrefixedExpression("*", MakeExpression(1));
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(Analysis::BadValue)("predicate(")
			.expr(se, ":")
			(b[1], Pointer<>(), MakeString())(")")
	};

	TestableAnalysisOfRange analysis1(Analysis::BadValue,
		"predicate applies to all elements in range ", "b", "b+3");
	analysis1.AddAnalyses(arrAnalyses, 1);

	Pred1<IsEven, Pointer<> > p;
	RB_FAIL(rbIN_RANGE(b, b+3, All<false>().Are(p)), analysis1);
}

RB_TEST(Fail_All_BadValue_Single_ShowAll)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 1, 5, 8 };
	int *b[] = { &a[0], 0, &a[2] };

	SharedExpression se0=new PrefixedExpression("*", MakeExpression((size_t)0)),
		se1=new PrefixedExpression("*", MakeExpression(1)),
		se2=new PrefixedExpression("*", MakeExpression(2));
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(Analysis::NotOk)("predicate(")
			.expr(se0, ":")
			(b[0], Pointer<>(), MakeString())(")"),
		MakeGeneralAnalysis(Analysis::BadValue)("predicate(")
			.expr(se1, ":")
			(b[1], Pointer<>(), MakeString())(")"),
		MakeGeneralAnalysis(Analysis::Ok)("predicate(")
			.expr(se2, ":")
			(b[2], Pointer<>(), MakeString())(")")
	};

	TestableAnalysisOfRange analysis1(Analysis::BadValue,
		"predicate applies to all elements in range ", "b", "b+3");
	analysis1.AddAnalyses(arrAnalyses, 3);

	Pred1<IsEven, Pointer<> > p;
	RB_FAIL(rbIN_RANGE(b, b+3, All<false>(true).Are(p)), analysis1);
}
