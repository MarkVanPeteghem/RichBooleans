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

RB_TEST(Pass_TwoRanges)
{
	int a[] = { 1, 2, 3 }, b[] = { 1, 2, 3 };

	// empty range
	RB_PASS(rbIN_RANGES(a, a, b, b, Compare<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, 0, b, b, Compare<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, a, b, 0, Compare<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, 0, b, 0, Compare<>().That(Equal<>())));

	RB_PASS(rbIN_RANGES(a, a, b, b, AllEqual<>()));
	RB_PASS(rbIN_RANGES(a, 0, b, b, AllEqual<>()));
	RB_PASS(rbIN_RANGES(a, a, b, 0, AllEqual<>()));
	RB_PASS(rbIN_RANGES(a, 0, b, 0, AllEqual<>()));

	// full range
	RB_PASS(rbIN_RANGES(a, a+3, b, b+3, Compare<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, 3, b, b+3, Compare<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, a+3, b, 3, Compare<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, 3, b, 3, Compare<>().That(Equal<>())));
	RB_PASS(rbIN_RANGE_ARRAY(b, b+3, a, Compare<>().That(Equal<>())));
	RB_PASS(rbIN_RANGE_ARRAY(b, 3, a, Compare<>().That(Equal<>())));
	RB_PASS(rbIN_ARRAY_RANGE(b, a, a+3, Compare<>().That(Equal<>())));
	RB_PASS(rbIN_ARRAY_RANGE(b, a, 3, Compare<>().That(Equal<>())));

	RB_PASS(rbIN_RANGES(a, a+3, b, b+3, AllEqual<>()));
	RB_PASS(rbIN_RANGES(a, 3, b, b+3, AllEqual<>()));
	RB_PASS(rbIN_RANGES(a, a+3, b, 3, AllEqual<>()));
	RB_PASS(rbIN_RANGES(a, 3, b, 3, AllEqual<>()));
	RB_PASS(rbIN_RANGE_ARRAY(b, b+3, a, AllEqual<>()));
	RB_PASS(rbIN_RANGE_ARRAY(b, 3, a, AllEqual<>()));


	int c[] = { 12, 6, 4 };

	// empty range
	RB_PASS(rbIN_RANGES(a, a, c, c, Compare<>().That(Pred2<ProductIs12>())));

	// full range
	RB_PASS(rbIN_RANGES(a, a+3, c, c+3, Compare<>().That(Pred2<ProductIs12>())));
	RB_PASS(rbIN_RANGE_ARRAY(c, c+3, a, Compare<>().That(Pred2<ProductIs12>())));
}

RB_TEST(Pass_TwoRanges_Negate)
{
	int a[] = { 1, 2, 3 }, b[] = { 1, 4, 3 };

	RB_PASS(rbIN_RANGES(a, a+3, b, b+3, !Compare<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, 3, b, b+3, !Compare<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, a+3, b, 3, !Compare<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, 3, b, 3, !Compare<>().That(Equal<>())));
	RB_PASS(rbIN_RANGE_ARRAY(b, b+3, a, !Compare<>().That(Equal<>())));
	RB_PASS(rbIN_RANGE_ARRAY(b, 3, a, !Compare<>().That(Equal<>())));

	RB_PASS(rbIN_RANGES(a, a+3, b, b+3, !AllEqual<>()));
	RB_PASS(rbIN_RANGES(a, 3, b, b+3, !AllEqual<>()));
	RB_PASS(rbIN_RANGES(a, a+3, b, 3, !AllEqual<>()));
	RB_PASS(rbIN_RANGES(a, 3, b, 3, !AllEqual<>()));
	RB_PASS(rbIN_RANGE_ARRAY(b, b+3, a, !AllEqual<>()));
	RB_PASS(rbIN_RANGE_ARRAY(b, 3, a, !AllEqual<>()));
}

RB_TEST(Pass_TwoRanges_WithValue)
{
	int a[] = { 1, 2, 3 }, b[] = { 1, 2, 3 };

	// empty range
	RB_PASS_V(rbvIN_RANGES(a, a, b, b, Compare<>().That(Equal<>())), a);
	RB_PASS_V(rbvIN_RANGES(a, 0, b, b, Compare<>().That(Equal<>())), a);
	RB_PASS_V(rbvIN_RANGES(a, a, b, 0, Compare<>().That(Equal<>())), a);
	RB_PASS_V(rbvIN_RANGES(a, 0, b, 0, Compare<>().That(Equal<>())), a);

	RB_PASS_V(rbvIN_RANGES(a, a, b, b, AllEqual<>()), a);
	RB_PASS_V(rbvIN_RANGES(a, 0, b, b, AllEqual<>()), a);
	RB_PASS_V(rbvIN_RANGES(a, a, b, 0, AllEqual<>()), a);
	RB_PASS_V(rbvIN_RANGES(a, 0, b, 0, AllEqual<>()), a);

	// full range
	RB_PASS_V(rbvIN_RANGES(a, a+3, b, b+3, Compare<>().That(Equal<>())), a);
	RB_PASS_V(rbvIN_RANGES(a, 3, b, b+3, Compare<>().That(Equal<>())), a);
	RB_PASS_V(rbvIN_RANGES(a, a+3, b, 3, Compare<>().That(Equal<>())), a);
	RB_PASS_V(rbvIN_RANGES(a, 3, b, 3, Compare<>().That(Equal<>())), a);
	RB_PASS_V(rbvIN_RANGE_ARRAY(b, b+3, a, Compare<>().That(Equal<>())), b);
	RB_PASS_V(rbvIN_RANGE_ARRAY(b, 3, a, Compare<>().That(Equal<>())), b);
	RB_PASS_V(rbvIN_ARRAY_RANGE(b, a, a+3, Compare<>().That(Equal<>())), b);
	RB_PASS_V(rbvIN_ARRAY_RANGE(b, a, 3, Compare<>().That(Equal<>())), b);

	RB_PASS_V(rbvIN_RANGES(a, a+3, b, b+3, AllEqual<>()), a);
	RB_PASS_V(rbvIN_RANGES(a, 3, b, b+3, AllEqual<>()), a);
	RB_PASS_V(rbvIN_RANGES(a, a+3, b, 3, AllEqual<>()), a);
	RB_PASS_V(rbvIN_RANGES(a, 3, b, 3, AllEqual<>()), a);
	RB_PASS_V(rbvIN_RANGE_ARRAY(b, b+3, a, AllEqual<>()), b);
	RB_PASS_V(rbvIN_RANGE_ARRAY(b, 3, a, AllEqual<>()), b);


	int c[] = { 12, 6, 4 };

	// empty range
	RB_PASS_V(rbvIN_RANGES(a, a, c, c, Compare<>().That(Pred2<ProductIs12>())), a);

	// full range
	RB_PASS_V(rbvIN_RANGES(a, a+3, c, c+3, Compare<>().That(Pred2<ProductIs12>())), a);
	RB_PASS_V(rbvIN_RANGE_ARRAY(c, c+3, a, Compare<>().That(Pred2<ProductIs12>())), c);
}

RB_TEST(Fail_TwoRanges_Compare)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ").idx(0, ":")("1", true),
		MakeGeneralAnalysis(true).idx(1, ":")("2", true)(" == ").idx(1, ":")("2", true),
		new Single(0, 2, "3", new IndexExpression(2), true)
	};

	TestableAnalysisOfRanges analysis1a(
		"predicate applies to ranges ", "a", "a+3", "b", "b+2");
	analysis1a.AddAnalyses(arrAnalyses, 3);
	TestableAnalysisOfRanges analysis2a(
		"predicate applies to ranges ", "a", "3", "b", "b+2");
	analysis2a.AddAnalyses(arrAnalyses, 3, false);
	TestableAnalysisOfRanges analysis3a(
		"predicate applies to ranges ", "a", "a+3", "b", "2");
	analysis3a.AddAnalyses(arrAnalyses, 3, false);
	TestableAnalysisOfRanges analysis4a(
		"predicate applies to ranges ", "a", "3", "b", "2");
	analysis4a.AddAnalyses(arrAnalyses, 3, false);

	int a[] = { 1, 2, 3 }, b[] = { 1, 2 };

	RB_FAIL(rbIN_RANGES(a, a+3, b, b+2, Compare<>(true).That(Equal<>())), analysis1a);
	RB_FAIL(rbIN_RANGES(a, 3, b, b+2, Compare<>(true).That(Equal<>())), analysis2a);
	RB_FAIL(rbIN_RANGES(a, a+3, b, 2, Compare<>(true).That(Equal<>())), analysis3a);
	RB_FAIL(rbIN_RANGES(a, 3, b, 2, Compare<>(true).That(Equal<>())), analysis4a);
}

RB_TEST(Fail_TwoRanges_Compare_Negate)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ").idx(0, ":")("1", true),
		MakeGeneralAnalysis(true).idx(1, ":")("2", true)(" == ").idx(1, ":")("2", true),
		MakeGeneralAnalysis(true).idx(2, ":")("3", true)(" == ").idx(2, ":")("3", true),
	};

	TestableAnalysisOfRanges analysis1a(
		"predicate applies to ranges ", "a", "a+3", "b", "b+3", Analysis::Ok);
	analysis1a.AddAnalyses(arrAnalyses, 3);
	analysis1a.Negate();
	TestableAnalysisOfRanges analysis2a(
		"predicate applies to ranges ", "a", "3", "b", "b+3", Analysis::Ok);
	analysis2a.AddAnalyses(arrAnalyses, 3, false);
	analysis2a.Negate();
	TestableAnalysisOfRanges analysis3a(
		"predicate applies to ranges ", "a", "a+3", "b", "3", Analysis::Ok);
	analysis3a.AddAnalyses(arrAnalyses, 3, false);
	analysis3a.Negate();
	TestableAnalysisOfRanges analysis4a(
		"predicate applies to ranges ", "a", "3", "b", "3", Analysis::Ok);
	analysis4a.AddAnalyses(arrAnalyses, 3, false);
	analysis4a.Negate();

	int a[] = { 1, 2, 3 }, b[] = { 1, 2, 3 };

	RB_FAIL(rbIN_RANGES(a, a+3, b, b+3, !Compare<>(true).That(Equal<>())), analysis1a);
	RB_FAIL(rbIN_RANGES(a, 3, b, b+3, !Compare<>(true).That(Equal<>())), analysis2a);
	RB_FAIL(rbIN_RANGES(a, a+3, b, 3, !Compare<>(true).That(Equal<>())), analysis3a);
	RB_FAIL(rbIN_RANGES(a, 3, b, 3, !Compare<>(true).That(Equal<>())), analysis4a);
}

RB_TEST(Fail_TwoRanges_AllEqual)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ").idx(0, ":")("1", true),
		MakeGeneralAnalysis(true).idx(1, ":")("2", true)(" == ").idx(1, ":")("2", true),
		new Single(0, 2, "3", new IndexExpression(2), true)
	};

	int a[] = { 1, 2, 3 }, b[] = { 1, 2 };

	TestableAnalysisOfRanges analysis1b(
		"ranges are equal: ", "a", "a+3", "b", "b+2");
	analysis1b.AddAnalyses(arrAnalyses, 3, false);
	TestableAnalysisOfRanges analysis2b(
		"ranges are equal: ", "a", "3", "b", "b+2");
	analysis2b.AddAnalyses(arrAnalyses, 3, false);
	TestableAnalysisOfRanges analysis3b(
		"ranges are equal: ", "a", "a+3", "b", "2");
	analysis3b.AddAnalyses(arrAnalyses, 3, false);
	TestableAnalysisOfRanges analysis4b(
		"ranges are equal: ", "a", "3", "b", "2");
	analysis4b.AddAnalyses(arrAnalyses, 3, false);

	RB_FAIL(rbIN_RANGES(a, a+3, b, b+2, AllEqual<>(true)), analysis1b);
	RB_FAIL(rbIN_RANGES(a, 3, b, b+2, AllEqual<>(true)), analysis2b);
	RB_FAIL(rbIN_RANGES(a, a+3, b, 2, AllEqual<>(true)), analysis3b);
	RB_FAIL(rbIN_RANGES(a, 3, b, 2, AllEqual<>(true)), analysis4b);
}

RB_TEST(Fail_TwoRanges_AllEqual_WithValue)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ").idx(0, ":")("1", true),
		MakeGeneralAnalysis(true).idx(1, ":")("2", true)(" == ").idx(1, ":")("2", true),
		new Single(0, 2, "3", new IndexExpression(2), true)
	};

	int a[] = { 1, 2, 3 }, b[] = { 1, 2 };

	TestableAnalysisOfRanges analysis1b(
		"ranges are equal: ", "a", "a+3", "b", "b+2");
	analysis1b.AddAnalyses(arrAnalyses, 3, false);
	TestableAnalysisOfRanges analysis2b(
		"ranges are equal: ", "a", "3", "b", "b+2");
	analysis2b.AddAnalyses(arrAnalyses, 3, false);
	TestableAnalysisOfRanges analysis3b(
		"ranges are equal: ", "a", "a+3", "b", "2");
	analysis3b.AddAnalyses(arrAnalyses, 3, false);
	TestableAnalysisOfRanges analysis4b(
		"ranges are equal: ", "a", "3", "b", "2");
	analysis4b.AddAnalyses(arrAnalyses, 3, false);

	RB_FAIL_V(rbvIN_RANGES(a, a+3, b, b+2, AllEqual<>(true)), analysis1b, a);
	RB_FAIL_V(rbvIN_RANGES(a, 3, b, b+2, AllEqual<>(true)), analysis2b, a);
	RB_FAIL_V(rbvIN_RANGES(a, a+3, b, 2, AllEqual<>(true)), analysis3b, a);
	RB_FAIL_V(rbvIN_RANGES(a, 3, b, 2, AllEqual<>(true)), analysis4b, a);
}

RB_TEST(Fail_TwoRanges1_Array)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ").idx(0, ":")("1", true),
		MakeGeneralAnalysis(true).idx(1, ":")("2", true)(" == ").idx(1, ":")("2", true),
		new Single(0, 2, "3", new IndexExpression(2), true)
	};

	TestableAnalysisOfRanges analysis1(
		"predicate applies to ranges ", "a", "a+3", "b", "RICHBOOL_ARRAY_COUNT(b)");
	analysis1.AddAnalyses(arrAnalyses, 3);

	TestableAnalysisOfRanges analysis2(
		"predicate applies to ranges ", "a", "3", "b", "RICHBOOL_ARRAY_COUNT(b)");
	analysis2.AddAnalyses(arrAnalyses, 3, false);

	int a[] = { 1, 2, 3 }, b[] = { 1, 2 };
	RB_FAIL(rbIN_RANGE_ARRAY(a, a+3, b, Compare<>(true).That(Equal<>())), analysis1);
	RB_FAIL(rbIN_RANGE_ARRAY(a, 3, b, Compare<>(true).That(Equal<>())), analysis2);

	TestableAnalysisOfRanges analysis3(
		"predicate applies to ranges ", "a", "RICHBOOL_ARRAY_COUNT(a)", "b", "b+2");
	analysis3.AddAnalyses(arrAnalyses, 3, false);

	TestableAnalysisOfRanges analysis4(
		"predicate applies to ranges ", "a", "RICHBOOL_ARRAY_COUNT(a)", "b", "2");
	analysis4.AddAnalyses(arrAnalyses, 3, false);

	RB_FAIL(rbIN_ARRAY_RANGE(a, b, b+2, Compare<>(true).That(Equal<>())), analysis3);
	RB_FAIL(rbIN_ARRAY_RANGE(a, b, 2, Compare<>(true).That(Equal<>())), analysis4);
}

RB_TEST(Fail_TwoRanges1_Array_WithValue)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ").idx(0, ":")("1", true),
		MakeGeneralAnalysis(true).idx(1, ":")("2", true)(" == ").idx(1, ":")("2", true),
		new Single(0, 2, "3", new IndexExpression(2), true)
	};

	TestableAnalysisOfRanges analysis1(
		"predicate applies to ranges ", "a", "a+3", "b", "RICHBOOL_ARRAY_COUNT(b)");
	analysis1.AddAnalyses(arrAnalyses, 3);

	TestableAnalysisOfRanges analysis2(
		"predicate applies to ranges ", "a", "3", "b", "RICHBOOL_ARRAY_COUNT(b)");
	analysis2.AddAnalyses(arrAnalyses, 3, false);

	int a[] = { 1, 2, 3 }, b[] = { 1, 2 };
	RB_FAIL_V(rbvIN_RANGE_ARRAY(a, a+3, b, Compare<>(true).That(Equal<>())), analysis1, a);
	RB_FAIL_V(rbvIN_RANGE_ARRAY(a, 3, b, Compare<>(true).That(Equal<>())), analysis2, a);

	TestableAnalysisOfRanges analysis3(
		"predicate applies to ranges ", "a", "RICHBOOL_ARRAY_COUNT(a)", "b", "b+2");
	analysis3.AddAnalyses(arrAnalyses, 3, false);

	TestableAnalysisOfRanges analysis4(
		"predicate applies to ranges ", "a", "RICHBOOL_ARRAY_COUNT(a)", "b", "2");
	analysis4.AddAnalyses(arrAnalyses, 3, false);

	RB_FAIL_V(rbvIN_ARRAY_RANGE(a, b, b+2, Compare<>(true).That(Equal<>())), analysis3, a);
	RB_FAIL_V(rbvIN_ARRAY_RANGE(a, b, 2, Compare<>(true).That(Equal<>())), analysis4, a);
}

RB_TEST(Fail_TwoRanges2)
{
	int a[] = { 1, 2, 3 }, b[] = { 1, 2 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ").idx(0, ":")("1", true),
		MakeGeneralAnalysis(true).idx(1, ":")("2", true)(" == ").idx(1, ":")("2", true),
		new Single(0, 2, "3", new IndexExpression(2), true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ", "a", "a+3", "b", "b+2");
	analysis.AddAnalyses(arrAnalyses, 3);

	RB_FAIL(rbIN_RANGES(a, a+3, b, b+2, Compare<>(true).That(Equal<>())), analysis);
}

RB_TEST(Fail_TwoRanges3)
{
	Analysis *analysisPred[] = {
		new Single(1, 2, "3", new IndexExpression(2), true)
	};

	int a[] = { 1, 2, 3 },
		c[] = { 12, 6 };

	TestableAnalysisOfRanges analysisContPred(
		"predicate applies to ranges ", "c", "c+2", "a", "a+3");
	analysisContPred.AddAnalyses(analysisPred, 1);

	RB_FAIL(rbIN_RANGES(c, c+2, a, a+3, Compare<>().That(Pred2<ProductIs12>())), analysisContPred);
}

RB_TEST(Fail_TwoRanges3_Full)
{
	Analysis *analysisPred[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("12", true)(", ").idx(0, ":")("1", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(1, ":")("6", true)(", ").idx(1, ":")("2", true)(")"),
		new Single(1, 2, "3", new IndexExpression(2), true)
	};

	int a[] = { 1, 2, 3 },
		c[] = { 12, 6 };

	TestableAnalysisOfRanges analysisContPred("predicate applies to ranges ", "c", "c+2", "a", "a+3");
	analysisContPred.AddAnalyses(analysisPred, 3);

	RB_FAIL(rbIN_RANGES(c, c+2, a, a+3, Compare<>(true).That(Pred2<ProductIs12>())), analysisContPred);
}

RB_TEST(Fail_TwoRangesB)
{
	Analysis *arrAnalyses[] = {
		new Single(0, 2, "2", new IndexExpression(1), true),
		new Single(0, 2, "4", new IndexExpression(3), true)
	};

	TestableAnalysisOfRanges analysis("ranges are equal: ", "a", "a+5", "b", "b+3");
	analysis.AddAnalyses(arrAnalyses, 2);

	int a[] = { 1, 2, 3, 4, 5 }, b[] = { 1, 3, 5 };
	RB_FAIL(rbIN_RANGES(a, a+5, b, b+3, AllEqual<>()), analysis);
}

RB_TEST(Fail_TwoRangesC)
{
	Analysis *arrAnalyses[] = {
		new Single(1, 2, "2", new IndexExpression(1), true),
		new Single(1, 2, "4", new IndexExpression(3), true)
	};

	TestableAnalysisOfRanges analysis("ranges are equal: ", "a", "a+3", "b", "b+5");
	analysis.AddAnalyses(arrAnalyses, 2);

	int a[] = { 1, 3, 5 }, b[] = { 1, 2, 3, 4, 5 };
	RB_FAIL(rbIN_RANGES(a, a+3, b, b+5, AllEqual<>()), analysis);
}

RB_TEST(Fail_TwoRangesD)
{
	Analysis *arrAnalyses[] = {
		new Single(1, 2, "7", new IndexExpression(1), true),
		new Single(0, 2, "3", new IndexExpression(2), true),
		new Single(0, 2, "4", new IndexExpression(3), true)
	};

	TestableAnalysisOfRanges analysis("ranges are equal: ", "a", "a+4", "b", "b+3");
	analysis.AddAnalyses(arrAnalyses, 3);

	int a[] = { 1, 2, 3, 4 }, b[] = { 1, 7, 2 };
	RB_FAIL(rbIN_RANGES(a, a+4, b, b+3, AllEqual<>()), analysis);
}

RB_TEST(Fail_TwoRangesE)
{
	Analysis *arrAnalyses[] = {
		new Single(1, 2, "2", new IndexExpression(3), true),
		new Single(1, 2, "3", new IndexExpression(4), true)
	};

	TestableAnalysisOfRanges analysis("ranges are equal: ", "a", "a+4", "b", "b+6");
	analysis.AddAnalyses(arrAnalyses, 2);

	int a[] = { 1, 2, 3, 4 }, b[] = { 1, 2, 3, 2, 3, 4 };
	RB_FAIL(rbIN_RANGES(a, a+4, b, b+6, AllEqual<>()), analysis);
}


// wuth one input iterator

RB_TEST(OneInputIterator_Pass)
{
	StubContainer stub(1, 3, 6);
	int arr[] = { 1, 3, 6 };

	RB_PASS(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+3, Compare<false>().That(Equal<>())));
	stub.rewind();
	RB_PASS(rbIN_RANGES(stub.begin(), stub.end(), arr, 3, Compare<false>().That(Equal<>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE_ARRAY(stub.begin(), stub.end(), arr, Compare<false>().That(Equal<>())));
	stub.rewind();
	RB_PASS(rbIN_RANGES(stub.begin(), 3, arr, arr+3, Compare<false>().That(Equal<>())));
	stub.rewind();
	RB_PASS(rbIN_RANGES(stub.begin(), 3, arr, 3, Compare<false>().That(Equal<>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE_ARRAY(stub.begin(), 3, arr, Compare<false>().That(Equal<>())));

	stub.rewind();
	RB_PASS(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+3, AllEqual<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGES(stub.begin(), stub.end(), arr, 3, AllEqual<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE_ARRAY(stub.begin(), stub.end(), arr, AllEqual<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGES(stub.begin(), 3, arr, arr+3, AllEqual<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGES(stub.begin(), 3, arr, 3, AllEqual<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE_ARRAY(stub.begin(), 3, arr, AllEqual<false>()));
}

RB_TEST(OneInputIterator_Pass_Negate)
{
	StubContainer stub(1, 3, 5);
	int arr[] = { 1, 3, 6 };

	RB_PASS(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+3, !Compare<false>().That(Equal<>())));
	stub.rewind();
	RB_PASS(rbIN_RANGES(stub.begin(), stub.end(), arr, 3, !Compare<false>().That(Equal<>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE_ARRAY(stub.begin(), stub.end(), arr, !Compare<false>().That(Equal<>())));
	stub.rewind();
	RB_PASS(rbIN_RANGES(stub.begin(), 3, arr, arr+3, !Compare<false>().That(Equal<>())));
	stub.rewind();
	RB_PASS(rbIN_RANGES(stub.begin(), 3, arr, 3, !Compare<false>().That(Equal<>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE_ARRAY(stub.begin(), 3, arr, !Compare<false>().That(Equal<>())));
}

RB_TEST(OneInputIterator_Empty_Pass)
{
	StubContainer stub;
	int arr[] = { 0 };
	RB_PASS(rbIN_RANGES(arr, arr, stub.begin(), stub.end(), AllEqual<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGES(arr, arr, stub.begin(), 0, AllEqual<false>()));
}

RB_TEST(OneInputIterator_Fail1)
{
	int arr[] = { 2, 3, 6 };
	StubContainer stub(1, 3, 6);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("1", true)
			(" == ").idx(0, ":")("2", true)
	};

	TestableAnalysisOfRanges analysis1("predicate applies to ranges ",
		"stub.begin()", "stub.end()", "arr", "arr+3");
	analysis1.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+3, Compare<false>().That(Equal<>())), analysis1);

	TestableAnalysisOfRanges analysis2("ranges are equal: ",
		"stub.begin()", "stub.end()", "arr", "arr+3");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	stub.rewind();
	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+3, AllEqual<false>()), analysis2);
}

RB_TEST(OneInputIterator_Fail1_Negate)
{
	int arr[] = { 2, 3, 6 };
	StubContainer stub(2, 3, 6);

	TestableAnalysisOfRanges analysis1( "predicate applies to ranges ",
		"stub.begin()", "stub.end()", "arr", "arr+3", Analysis::Ok);
	analysis1.Negate();

	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+3, !Compare<false>().That(Equal<>())), analysis1);
}

RB_TEST(OneInputIterator_Fail1_Full)
{
	int arr[] = { 2, 3, 6 };
	StubContainer stub(1, 3, 6);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("1", true)(" == ")
			.idx(0, ":")("2", true),
		MakeGeneralAnalysis(true).idx(1, ":")("3", true)(" == ")
			.idx(1, ":")("3", true),
		MakeGeneralAnalysis(true).idx(2, ":")("6", true)(" == ")
			.idx(2, ":")("6", true)
	};

	TestableAnalysisOfRanges analysis1a("ranges are equal: ",
		"stub.begin()", "stub.end()", "arr", "arr+3");
	analysis1a.AddAnalyses(arrAnalyses, 3);
	TestableAnalysisOfRanges analysis2a("ranges are equal: ",
		"stub.begin()", "3", "arr", "arr+3");
	analysis2a.AddAnalyses(arrAnalyses, 3, false);
	TestableAnalysisOfRanges analysis3a("ranges are equal: ",
		"stub.begin()", "stub.end()", "arr", "3");
	analysis3a.AddAnalyses(arrAnalyses, 3, false);
	TestableAnalysisOfRanges analysis4a("ranges are equal: ",
		"stub.begin()", "3", "arr", "3");
	analysis4a.AddAnalyses(arrAnalyses, 3, false);

	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+3, AllEqual<false>(true)), analysis1a);
	stub.rewind();
	RB_FAIL(rbIN_RANGES(stub.begin(), 3, arr, arr+3, AllEqual<false>(true)), analysis2a);
	stub.rewind();
	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, 3, AllEqual<false>(true)), analysis3a);
	stub.rewind();
	RB_FAIL(rbIN_RANGES(stub.begin(), 3, arr, 3, AllEqual<false>(true)), analysis4a);

	TestableAnalysisOfRanges analysis1b("predicate applies to ranges ",
		"stub.begin()", "stub.end()", "arr", "arr+3");
	analysis1b.AddAnalyses(arrAnalyses, 3, false);
	TestableAnalysisOfRanges analysis2b("predicate applies to ranges ",
		"stub.begin()", "3", "arr", "arr+3");
	analysis2b.AddAnalyses(arrAnalyses, 3, false);
	TestableAnalysisOfRanges analysis3b("predicate applies to ranges ",
		"stub.begin()", "stub.end()", "arr", "3");
	analysis3b.AddAnalyses(arrAnalyses, 3, false);
	TestableAnalysisOfRanges analysis4b("predicate applies to ranges ",
		"stub.begin()", "3", "arr", "3");
	analysis4b.AddAnalyses(arrAnalyses, 3, false);

	stub.rewind();
	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+3, AllEqual<false>(true)), analysis1a);
	stub.rewind();
	RB_FAIL(rbIN_RANGES(stub.begin(), 3, arr, arr+3, AllEqual<false>(true)), analysis2a);
	stub.rewind();
	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, 3, AllEqual<false>(true)), analysis3a);
	stub.rewind();
	RB_FAIL(rbIN_RANGES(stub.begin(), 3, arr, 3, AllEqual<false>(true)), analysis4a);
}

RB_TEST(OneInputIterator_Fail1_Full_Negate)
{
	int arr[] = { 2, 3, 6 };
	StubContainer stub(2, 3, 6);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("2", true)(" == ")
			.idx(0, ":")("2", true),
		MakeGeneralAnalysis(true).idx(1, ":")("3", true)(" == ")
			.idx(1, ":")("3", true),
		MakeGeneralAnalysis(true).idx(2, ":")("6", true)(" == ")
			.idx(2, ":")("6", true)
	};

	TestableAnalysisOfRanges analysis1a( "ranges are equal: ",
		"stub.begin()", "stub.end()", "arr", "arr+3", Analysis::Ok);
	analysis1a.AddAnalyses(arrAnalyses, 3);
	analysis1a.Negate();
	TestableAnalysisOfRanges analysis2a( "ranges are equal: ",
		"stub.begin()", "3", "arr", "arr+3", Analysis::Ok);
	analysis2a.AddAnalyses(arrAnalyses, 3, false);
	analysis2a.Negate();
	TestableAnalysisOfRanges analysis3a( "ranges are equal: ",
		"stub.begin()", "stub.end()", "arr", "3", Analysis::Ok);
	analysis3a.AddAnalyses(arrAnalyses, 3, false);
	analysis3a.Negate();
	TestableAnalysisOfRanges analysis4a( "ranges are equal: ",
		"stub.begin()", "3", "arr", "3", Analysis::Ok);
	analysis4a.AddAnalyses(arrAnalyses, 3, false);
	analysis4a.Negate();

	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+3, !AllEqual<false>(true)), analysis1a);
	stub.rewind();
	RB_FAIL(rbIN_RANGES(stub.begin(), 3, arr, arr+3, !AllEqual<false>(true)), analysis2a);
	stub.rewind();
	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, 3, !AllEqual<false>(true)), analysis3a);
	stub.rewind();
	RB_FAIL(rbIN_RANGES(stub.begin(), 3, arr, 3, !AllEqual<false>(true)), analysis4a);
}

RB_TEST(OneInputIterator_Fail2)
{
	int arr[] = { 1, 3, 7 };
	StubContainer stub(1, 3, 6);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(2, ":")("6", true)(" == ")
			.idx(2, ":")("7", true)
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		"stub.begin()", "stub.end()", "arr", "arr+3");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+3, AllEqual<false>()), analysis);
}

RB_TEST(OneInputIterator_Fail2_Full)
{
	int arr[] = { 1, 3, 7 };
	StubContainer stub(1, 3, 6);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ")
			.idx(0, ":")("1", true),
		MakeGeneralAnalysis(true).idx(1, ":")("3", true)(" == ")
			.idx(1, ":")("3", true),
		MakeGeneralAnalysis(false).idx(2, ":")("6", true)(" == ")
			.idx(2, ":")("7", true)
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		"stub.begin()", "stub.end()", "arr", "arr+3");
	analysis.AddAnalyses(arrAnalyses, 3);

	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+3, AllEqual<false>(true)), analysis);
}

RB_TEST(OneInputIterator_Fail3)
{
	int arr[] = { 1, 12, 20, 25, 29, 6 };
	StubContainer stub(1, 6);

	Analysis *arrAnalyses[] = {
		new Single(1, 2, "12", new IndexExpression(1), true),
		new Single(1, 2, "20", new IndexExpression(2), true),
		new Single(1, 2, "25", new IndexExpression(3), true),
		new Single(1, 2, "29", new IndexExpression(4), true)
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		"stub.begin()", "stub.end()", "arr", "arr+6");
	analysis.AddAnalyses(arrAnalyses, 4);

	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+6, AllEqual<false>()), analysis);
}

RB_TEST(OneInputIterator_Fail3_Full)
{
	int arr[] = { 1, 12, 20, 25, 29, 6 };
	StubContainer stub(1, 6);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ").idx(0, ":")("1", true),
		new Single(1, 2, "12", new IndexExpression(1), true),
		new Single(1, 2, "20", new IndexExpression(2), true),
		new Single(1, 2, "25", new IndexExpression(3), true),
		new Single(1, 2, "29", new IndexExpression(4), true),
		MakeGeneralAnalysis(true).idx(1, ":")("6", true)(" == ").idx(5, ":")("6", true)
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		"stub.begin()", "stub.end()", "arr", "arr+6");
	analysis.AddAnalyses(arrAnalyses, 6);

	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+6, AllEqual<false>(true)), analysis);
}

RB_TEST(OneInputIterator_Fail4)
{
	int arr[] = { 1, 12, 3, 29, 6 };
	StubContainer stub(1, 3, 6);

	Analysis *arrAnalyses[] = {
		new Single(1, 2, "12", new IndexExpression(1), true),
		new Single(1, 2, "29", new IndexExpression(3), true)
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		"stub.begin()", "stub.end()", "arr", "arr+5");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+5, AllEqual<false>()), analysis);
}

RB_TEST(OneInputIterator_Fail4_Full)
{
	int arr[] = { 1, 12, 3, 29, 6 };
	StubContainer stub(1, 3, 6);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ").idx(0, ":")("1", true),
		new Single(1, 2, "12", new IndexExpression(1), true),
		MakeGeneralAnalysis(true).idx(1, ":")("3", true)(" == ").idx(2, ":")("3", true),
		new Single(1, 2, "29", new IndexExpression(3), true),
		MakeGeneralAnalysis(true).idx(2, ":")("6", true)(" == ").idx(4, ":")("6", true)
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		"stub.begin()", "stub.end()", "arr", "arr+5");
	analysis.AddAnalyses(arrAnalyses, 5);

	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+5, AllEqual<false>(true)), analysis);
}

RB_TEST(OneInputIterator_Fail5)
{
	// this test demonstrates the unperfect behaviour of this rich boolean
	int arr[] = { 1, 2, 3, 8 };
	StubContainer stub(1, 3, 6, 8);

	Analysis *arrAnalyses[] = {
		new Single(1, 2, "2", new IndexExpression(1), true),
		MakeGeneralAnalysis(false).idx(2, ":")("6", true)(" == ").idx(3, ":")("8", true),
		new Single(0, 2, "8", new IndexExpression(3), true),
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		"stub.begin()", "stub.end()", "arr", "arr+4");
	analysis.AddAnalyses(arrAnalyses, 3);

	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+4, AllEqual<false>()), analysis);
}

RB_TEST(OneInputIterator_Fail5_Full)
{
	// this test demonstrates the unperfect behaviour of this rich boolean
	int arr[] = { 1, 2, 3, 8 };
	StubContainer stub(1, 3, 6, 8);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ").idx(0, ":")("1", true),
		new Single(1, 2, "2", new IndexExpression(1), true),
		MakeGeneralAnalysis(true).idx(1, ":")("3", true)(" == ").idx(2, ":")("3", true),
		MakeGeneralAnalysis(false).idx(2, ":")("6", true)(" == ").idx(3, ":")("8", true),
		new Single(0, 2, "8", new IndexExpression(3), true),
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		"stub.begin()", "stub.end()", "arr", "arr+4");
	analysis.AddAnalyses(arrAnalyses, 5);

	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+4, AllEqual<false>(true)), analysis);
}

RB_TEST(OneInputIterator_FirstEmpty_Fail)
{
	int arr[] = { 0 };
	StubContainer stub(1, 3, 6);

	Analysis *arrAnalyses[] = {
		new Single(0, 2, "1", new IndexExpression(0), true),
		new Single(0, 2, "3", new IndexExpression(1), true),
		new Single(0, 2, "6", new IndexExpression(2), true)
	};
	TestableAnalysisOfRanges analysis(
		"ranges are equal: ", "stub.begin()", "stub.end()", "arr", "arr");
	analysis.AddAnalyses(arrAnalyses, 3);

	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr, AllEqual<false>()), analysis);
}

RB_TEST(OneInputIterator_SecondEmpty_Fail)
{
	StubContainer stub;
	int arr[] = { 1, 3, 6 };

	Analysis *arrAnalyses[] = {
		new Single(1, 2, "1", new IndexExpression(0), true),
		new Single(1, 2, "3", new IndexExpression(1), true),
		new Single(1, 2, "6", new IndexExpression(2), true)
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		"stub.begin()", "stub.end()", "arr", "arr+3");
	analysis.AddAnalyses(arrAnalyses, 3);

	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+3, AllEqual<false>()), analysis);
}

RB_TEST(OneInputIteratorPred_Pass)
{
	StubContainer stub(1, 3, 6);
	int arr[] = { 12, 4, 2 };
	RB_PASS(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+3, Compare<false>().That(Pred2<ProductIs12>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE_ARRAY(stub.begin(), stub.end(), arr, Compare<false>().That(Pred2<ProductIs12>())));
}

RB_TEST(OneInputIteratorPred_Fail1)
{
	StubContainer stub(5, 4, 2);
	int arr[] = { 2, 3, 6 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(0, ":")("5", true)(", ")
			.idx(0, ":")("2", true)(")")
	};
	TestableAnalysisOfRanges analysis("predicate applies to ranges ",
		"stub.begin()", "stub.end()", "arr", "arr+3");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+3, Compare<false>().That(Pred2<ProductIs12>())),
		analysis);
}

RB_TEST(OneInputIteratorPred_Fail1_Full)
{
	int arr[] = { 2, 3, 6 };
	StubContainer stub(5, 4, 2);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(0, ":")("5", true)(", ")
			.idx(0, ":")("2", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(1, ":")("4", true)(", ")
			.idx(1, ":")("3", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(2, ":")("2", true)(", ")
			.idx(2, ":")("6", true)(")")
	};
	TestableAnalysisOfRanges analysis("predicate applies to ranges ",
		"stub.begin()", "stub.end()", "arr", "arr+3");
	analysis.AddAnalyses(arrAnalyses, 3);

	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+3,
			Compare<false>(true).That(Pred2<ProductIs12>())),
		analysis);
}

RB_TEST(OneInputIteratorPred_Fail2)
{
	int arr[] = { 1, 3, 7 };
	StubContainer stub(12, 4, 2);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(2, ":")("2", true)(", ")
			.idx(2, ":")("7", true)(")")
	};
	TestableAnalysisOfRanges analysis("predicate applies to ranges ",
		"stub.begin()", "stub.end()", "arr", "arr+3");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+3, Compare<false>().That(Pred2<ProductIs12>())),
		analysis);
}

RB_TEST(OneInputIteratorPred_Fail3)
{
	int arr[] = { 1, 12, 20, 25, 29, 2 };
	StubContainer stub(12, 6);

	Analysis *arrAnalyses[] = {
		new Single(1, 2, "12", new IndexExpression(1), true),
		new Single(1, 2, "20", new IndexExpression(2), true),
		new Single(1, 2, "25", new IndexExpression(3), true),
		new Single(1, 2, "29", new IndexExpression(4), true)
	};
	TestableAnalysisOfRanges analysis("predicate applies to ranges ",
		"stub.begin()", "stub.end()", "arr", "arr+6");
	analysis.AddAnalyses(arrAnalyses, 4);

	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+6, Compare<false>().That(Pred2<ProductIs12>())),
		analysis);
}

RB_TEST(OneInputIteratorPred_Fail4)
{
	int arr[] = { 1, 12, 3, 29, 2 };
	StubContainer stub(12, 4, 6);

	Analysis *arrAnalyses[] = {
		new Single(1, 2, "12", new IndexExpression(1), true),
		new Single(1, 2, "29", new IndexExpression(3), true)
	};
	TestableAnalysisOfRanges analysis("predicate applies to ranges ",
		"stub.begin()", "stub.end()", "arr", "arr+5");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+5, Compare<false>().That(Pred2<ProductIs12>())),
		analysis);
}

RB_TEST(OneInputIteratorPred_Fail4_Array)
{
	int arr[] = { 1, 12, 3, 29, 2 };
	StubContainer stub(12, 4, 6);

	Analysis *arrAnalyses[] = {
		new Single(1, 2, "12", new IndexExpression(1), true),
		new Single(1, 2, "29", new IndexExpression(3), true)
	};
	TestableAnalysisOfRanges analysis("predicate applies to ranges ",
		"stub.begin()", "stub.end()", "arr", "RICHBOOL_ARRAY_COUNT(arr)");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGE_ARRAY(stub.begin(), stub.end(), arr, Compare<false>().That(Pred2<ProductIs12>())),
		analysis);
}

RB_TEST(OneInputIteratorPred_Fail5)
{
	// this test demonstrates the unperfect behaviour of this rich boolean,
	// it can match the 3 with the 4 because it can look ahead in arr,
	// but it can't match the 6 with the 2 because it can't look ahead in stub,

	int arr[] = { 1, 5, 3, 6 };
	StubContainer stub(12, 4, 6, 2);

	Analysis *arrAnalyses[] = {
		new Single(1, 2, "5", new IndexExpression(1), true),
		MakeGeneralAnalysis(false)("predicate(").idx(2, ":")("6", true)(", ")
			.idx(3, ":")("6", true)(")"),
		new Single(0, 2, "2", new IndexExpression(3), true),
	};

	TestableAnalysisOfRanges analysis2("predicate applies to ranges ",
		"stub.begin()", "stub.end()", "arr", "RICHBOOL_ARRAY_COUNT(arr)");
	analysis2.AddAnalyses(arrAnalyses, 3, false);

	RB_FAIL(rbIN_RANGE_ARRAY(stub.begin(), stub.end(), arr, Compare<false>().That(Pred2<ProductIs12>())),
		analysis2);
}


// with two input iterators

RB_TEST(TwoInputIterator_Pass)
{
	StubContainer stub1(1, 3, 6), stub2(1, 3, 6);
	AllEqual<false,false> allEqual;

	RB_PASS(rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(), allEqual));
	stub1.rewind(); stub2.rewind();
	RB_PASS(rbIN_RANGES(stub1.begin(), 3, stub2.begin(), stub2.end(), allEqual));
	stub1.rewind(); stub2.rewind();
	RB_PASS(rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), 3, allEqual));
	stub1.rewind(); stub2.rewind();
	RB_PASS(rbIN_RANGES(stub1.begin(), 3, stub2.begin(), 3, allEqual));
}

RB_TEST(TwoInputIterator_Pass_Negate)
{
	StubContainer stub1(1, 3, 6), stub2(1, 4, 6);
	AllEqual<false,false> allEqual;

	RB_PASS(rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(), !allEqual));
	stub1.rewind(); stub2.rewind();
	RB_PASS(rbIN_RANGES(stub1.begin(), 3, stub2.begin(), stub2.end(), !allEqual));
	stub1.rewind(); stub2.rewind();
	RB_PASS(rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), 3, !allEqual));
	stub1.rewind(); stub2.rewind();
	RB_PASS(rbIN_RANGES(stub1.begin(), 3, stub2.begin(), 3, !allEqual));
}

RB_TEST(TwoInputIteratorPred_Pass)
{
	StubContainer stub(1, 3, 6);
	int arr[] = { 12, 4, 2 };
	Compare<false,false> compare;
	RB_PASS(rbIN_RANGES(arr, arr+3, stub.begin(), stub.end(), compare.That(Pred2<ProductIs12>())));
	stub.rewind();
	RB_PASS(rbIN_RANGES(stub.begin(), stub.end(), arr, arr+3, compare.That(Pred2<ProductIs12>())));
}

RB_TEST(TwoInputIterators_Fail1)
{
	StubContainer stub1(2, 3, 6), stub2(1, 3, 6);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("2", true)(" == ")
			.idx(0, ":")("1", true)
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		"stub1.begin()", "stub1.end()", "stub2.begin()", "stub2.end()");
	analysis.AddAnalyses(arrAnalyses, 1);

	AllEqual<false,false> allEqual;
	RB_FAIL(
		rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(), allEqual),
		analysis);
}

RB_TEST(TwoInputIterators_Fail1_Negate)
{
	StubContainer stub1(2, 3, 6), stub2(2, 3, 6);

	TestableAnalysisOfRanges analysis( "ranges are equal: ",
		"stub1.begin()", "stub1.end()", "stub2.begin()", "stub2.end()", Analysis::Ok);
	analysis.Negate();

	AllEqual<false,false> allEqual;
	RB_FAIL(
		rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(), !allEqual),
		analysis);
}

RB_TEST(TwoInputIterators_Fail1_Full)
{
	StubContainer stub1(2, 3, 6), stub2(1, 3, 6);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("2", true)(" == ")
			.idx(0, ":")("1", true),
		MakeGeneralAnalysis(true).idx(1, ":")("3", true)(" == ")
			.idx(1, ":")("3", true),
		MakeGeneralAnalysis(true).idx(2, ":")("6", true)(" == ")
			.idx(2, ":")("6", true)
	};

	TestableAnalysisOfRanges analysis1("ranges are equal: ",
		"stub1.begin()", "stub1.end()", "stub2.begin()", "stub2.end()");
	analysis1.AddAnalyses(arrAnalyses, 3);
	TestableAnalysisOfRanges analysis2("ranges are equal: ",
		"stub1.begin()", "3", "stub2.begin()", "stub2.end()");
	analysis2.AddAnalyses(arrAnalyses, 3, false);
	TestableAnalysisOfRanges analysis3("ranges are equal: ",
		"stub1.begin()", "stub1.end()", "stub2.begin()", "3");
	analysis3.AddAnalyses(arrAnalyses, 3, false);
	TestableAnalysisOfRanges analysis4("ranges are equal: ",
		"stub1.begin()", "3", "stub2.begin()", "3");
	analysis4.AddAnalyses(arrAnalyses, 3, false);

	AllEqual<false,false> allEqual(true);

	RB_FAIL(
		rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(), allEqual),
		analysis1);

	stub1.rewind();
	stub2.rewind();

	RB_FAIL(
		rbIN_RANGES(stub1.begin(), 3, stub2.begin(), stub2.end(), allEqual),
		analysis2);

	stub1.rewind();
	stub2.rewind();

	RB_FAIL(
		rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), 3, allEqual),
		analysis3);

	stub1.rewind();
	stub2.rewind();

	RB_FAIL(
		rbIN_RANGES(stub1.begin(), 3, stub2.begin(), 3,	allEqual),
		analysis4);
}

RB_TEST(TwoInputIterators_Fail1_Full_Negate)
{
	StubContainer stub1(2, 3, 6), stub2(2, 3, 6);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("2", true)(" == ")
			.idx(0, ":")("2", true),
		MakeGeneralAnalysis(true).idx(1, ":")("3", true)(" == ")
			.idx(1, ":")("3", true),
		MakeGeneralAnalysis(true).idx(2, ":")("6", true)(" == ")
			.idx(2, ":")("6", true)
	};

	TestableAnalysisOfRanges analysis1( "ranges are equal: ",
		"stub1.begin()", "stub1.end()", "stub2.begin()", "stub2.end()", Analysis::Ok);
	analysis1.AddAnalyses(arrAnalyses, 3);
	analysis1.Negate();
	TestableAnalysisOfRanges analysis2( "ranges are equal: ",
		"stub1.begin()", "3", "stub2.begin()", "stub2.end()", Analysis::Ok);
	analysis2.AddAnalyses(arrAnalyses, 3, false);
	analysis2.Negate();
	TestableAnalysisOfRanges analysis3( "ranges are equal: ",
		"stub1.begin()", "stub1.end()", "stub2.begin()", "3", Analysis::Ok);
	analysis3.AddAnalyses(arrAnalyses, 3, false);
	analysis3.Negate();
	TestableAnalysisOfRanges analysis4( "ranges are equal: ",
		"stub1.begin()", "3", "stub2.begin()", "3", Analysis::Ok);
	analysis4.AddAnalyses(arrAnalyses, 3, false);
	analysis4.Negate();

	AllEqual<false,false> allEqual(true);

	RB_FAIL(
		rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(), !allEqual),
		analysis1);

	stub1.rewind();
	stub2.rewind();

	RB_FAIL(
		rbIN_RANGES(stub1.begin(), 3, stub2.begin(), stub2.end(), !allEqual),
		analysis2);

	stub1.rewind();
	stub2.rewind();

	RB_FAIL(
		rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), 3, !allEqual),
		analysis3);

	stub1.rewind();
	stub2.rewind();

	RB_FAIL(
		rbIN_RANGES(stub1.begin(), 3, stub2.begin(), 3,	!allEqual),
		analysis4);
}

RB_TEST(TwoInputIterators_Fail2)
{
	StubContainer stub1(1, 4, 6), stub2(1, 3, 6);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(1, ":")("4", true)(" == ")
			.idx(1, ":")("3", true)
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		"stub1.begin()", "stub1.end()", "stub2.begin()", "stub2.end()");
	analysis.AddAnalyses(arrAnalyses, 1);

	AllEqual<false,false> allEqual;
	RB_FAIL(
		rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(), allEqual),
		analysis);
}

RB_TEST(TwoInputIterators_Fail2_Full)
{
	StubContainer stub1(1, 4, 6), stub2(1, 3, 6);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ")
			.idx(0, ":")("1", true),
		MakeGeneralAnalysis(false).idx(1, ":")("4", true)(" == ")
			.idx(1, ":")("3", true),
		MakeGeneralAnalysis(true).idx(2, ":")("6", true)(" == ")
			.idx(2, ":")("6", true)
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		"stub1.begin()", "stub1.end()", "stub2.begin()", "stub2.end()");
	analysis.AddAnalyses(arrAnalyses, 3);

	AllEqual<false,false> allEqual(true);
	RB_FAIL(
		rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(),
			allEqual),
		analysis);
}

RB_TEST(TwoInputIterators_Fail3)
{
	StubContainer stub1(1, 3, 5), stub2(1, 3, 6);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(2, ":")("5", true)(" == ")
			.idx(2, ":")("6", true)
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		"stub1.begin()", "stub1.end()", "stub2.begin()", "stub2.end()");
	analysis.AddAnalyses(arrAnalyses, 1);

	AllEqual<false,false> allEqual;
	RB_FAIL(
		rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(), allEqual),
		analysis);
}

RB_TEST(TwoInputIterators_Fail3_Full)
{
	StubContainer stub1(1, 3, 5), stub2(1, 3, 6);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ")
			.idx(0, ":")("1", true),
		MakeGeneralAnalysis(true).idx(1, ":")("3", true)(" == ")
			.idx(1, ":")("3", true),
		MakeGeneralAnalysis(false).idx(2, ":")("5", true)(" == ")
			.idx(2, ":")("6", true)
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		"stub1.begin()", "stub1.end()", "stub2.begin()", "stub2.end()");
	analysis.AddAnalyses(arrAnalyses, 3);

	AllEqual<false,false> allEqual(true);
	RB_FAIL(
		rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(),
			allEqual),
		analysis);
}

RB_TEST(TwoInputIterators_Fail4)
{
	StubContainer stub1(1, 3, 5), stub2(1, 5);

	Analysis *arrAnalyses[] = {
		new Single(0, 2, "3", new IndexExpression(1), true)
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		"stub1.begin()", "stub1.end()", "stub2.begin()", "stub2.end()");
	analysis.AddAnalyses(arrAnalyses, 1);

	AllEqual<false,false> allEqual;
	RB_FAIL(
		rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(), allEqual),
		analysis);
}

RB_TEST(TwoInputIterators_Fail4_Full)
{
	StubContainer stub1(1, 3, 5), stub2(1, 5);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ").idx(0, ":")("1", true),
		new Single(0, 2, "3", new IndexExpression(1), true),
		MakeGeneralAnalysis(true).idx(2, ":")("5", true)(" == ").idx(1, ":")("5", true),
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		"stub1.begin()", "stub1.end()", "stub2.begin()", "stub2.end()");
	analysis.AddAnalyses(arrAnalyses, 3);

	AllEqual<false,false> allEqual(true);
	RB_FAIL(
		rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(),
			allEqual),
		analysis);
}

RB_TEST(TwoInputIterators_Fail5)
{
	StubContainer stub1(1, 5), stub2(1, 3, 5);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(1, ":")("5", true)(" == ").idx(1, ":")("3", true),
		new Single(1, 2, "5", new IndexExpression(2), true)
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		"stub1.begin()", "stub1.end()", "stub2.begin()", "stub2.end()");
	analysis.AddAnalyses(arrAnalyses, 2);

	AllEqual<false,false> allEqual;
	RB_FAIL(
		rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(),
			allEqual),
		analysis);
}

RB_TEST(TwoInputIterators_Fail5_Full)
{
	StubContainer stub1(1, 5), stub2(1, 3, 5);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ").idx(0, ":")("1", true),
		MakeGeneralAnalysis(false).idx(1, ":")("5", true)(" == ").idx(1, ":")("3", true),
		new Single(1, 2, "5", new IndexExpression(2), true)
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		"stub1.begin()", "stub1.end()", "stub2.begin()", "stub2.end()");
	analysis.AddAnalyses(arrAnalyses, 3);

	AllEqual<false,false> allEqual(true);
	RB_FAIL(
		rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(),
			allEqual),
		analysis);
}

RB_TEST(TwoInputIterators_Fail6)
{
	StubContainer stub1(1, 3, 5), stub2;

	Analysis *arrAnalyses[] = {
		new Single(0, 2, "1", new IndexExpression(0), true),
		new Single(0, 2, "3", new IndexExpression(1), true),
		new Single(0, 2, "5", new IndexExpression(2), true)
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		 "stub1.begin()", "stub1.end()", "stub2.begin()", "stub2.end()");
	analysis.AddAnalyses(arrAnalyses, 3);

	AllEqual<false,false> allEqual;
	RB_FAIL(
		rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(),
			allEqual),
		analysis);
}

RB_TEST(TwoInputIterators_Fail7)
{
	StubContainer stub1, stub2(1, 3, 5);

	Analysis *arrAnalyses[] = {
		new Single(1, 2, "1", new IndexExpression(0), true),
		new Single(1, 2, "3", new IndexExpression(1), true),
		new Single(1, 2, "5", new IndexExpression(2), true)
	};
	TestableAnalysisOfRanges analysis("ranges are equal: ",
		"stub1.begin()", "stub1.end()", "stub2.begin()", "stub2.end()");
	analysis.AddAnalyses(arrAnalyses, 3);

	AllEqual<false,false> allEqual;
	RB_FAIL(
		rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(), allEqual),
		analysis);
}

RB_TEST(TwoInputIterators_Pred_Fail)
{
	StubContainer stub1(12, 3, 2), stub2(1, 3, 6);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("3", true)
			(", ").idx(1, ":")("3", true)(")")
	};
	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ",
		"stub1.begin()", "stub1.end()", "stub2.begin()", "stub2.end()");
	analysis.AddAnalyses(arrAnalyses, 1);

	Compare<false,false> compare;
	RB_FAIL(
		rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(),
			compare.That(Pred2<ProductIs12>())),
		analysis);
}

RB_TEST(TwoInputIterators_Pred_Fail_Full)
{
	StubContainer stub1(12, 3, 2), stub2(1, 3, 6);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("12", true)
			(", ").idx(0, ":")("1", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("3", true)
			(", ").idx(1, ":")("3", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(2, ":")("2", true)
			(", ").idx(2, ":")("6", true)(")")
	};
	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ",
		"stub1.begin()", "stub1.end()", "stub2.begin()", "stub2.end()");
	analysis.AddAnalyses(arrAnalyses, 3);

	Compare<false,false> compare(true);
	RB_FAIL(
		rbIN_RANGES(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(),
			compare.That(Pred2<ProductIs12>())),
		analysis);
}


/////////////////////////////////////////////////////////////////////
// same tests, but in the old, deprecated way:

RB_TEST(Pass_TwoRanges_Old)
{
	int a[] = { 1, 2, 3 }, b[] = { 1, 2, 3 };

	// empty range
	RB_PASS(rbIN_RANGES_ARG(a, a, b, b, Compare<>(), Equal<>()));

	// full range
	RB_PASS(rbIN_RANGES_ARG(a, a+3, b, b+3, Compare<>(), Equal<>()));
	RB_PASS(rbIN_RANGE_ARRAY_ARG(b, b+3, a, Compare<>(), Equal<>()));


	int c[] = { 12, 6, 4 };

	// empty range
	RB_PASS(rbIN_RANGES_ARG(a, a, c, c, Compare<>(), Pred2<ProductIs12>()));

	// full range
	RB_PASS(rbIN_RANGES_ARG(a, a+3, c, c+3, Compare<>(), Pred2<ProductIs12>()));
	RB_PASS(rbIN_RANGE_ARRAY_ARG(c, c+3, a, Compare<>(), Pred2<ProductIs12>()));
}

RB_TEST(Fail_TwoRanges1_Old)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ").idx(0, ":")("1", true),
		MakeGeneralAnalysis(true).idx(1, ":")("2", true)(" == ").idx(1, ":")("2", true),
		new Single(0, 2, "3", new IndexExpression(2), true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ", "a", "a+3", "b", "b+2");
	analysis.AddAnalyses(arrAnalyses, 3);

	int a[] = { 1, 2, 3 }, b[] = { 1, 2 };
	RB_FAIL(rbIN_RANGES_ARG(a, a+3, b, b+2, Compare<>(true), Equal<>()), analysis);
}

RB_TEST(Fail_TwoRanges1_Array_Old)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ").idx(0, ":")("1", true),
		MakeGeneralAnalysis(true).idx(1, ":")("2", true)(" == ").idx(1, ":")("2", true),
		new Single(0, 2, "3", new IndexExpression(2), true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ", "a", "a+3", "b", "b+RICHBOOL_ARRAY_COUNT(b)");
	analysis.AddAnalyses(arrAnalyses, 3);

	int a[] = { 1, 2, 3 }, b[] = { 1, 2 };
	RB_FAIL(rbIN_RANGE_ARRAY_ARG(a, a+3, b, Compare<>(true), Equal<>()), analysis);
}

RB_TEST(Fail_TwoRanges2_Old)
{
	int a[] = { 1, 2, 3 }, b[] = { 1, 2 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ").idx(0, ":")("1", true),
		MakeGeneralAnalysis(true).idx(1, ":")("2", true)(" == ").idx(1, ":")("2", true),
		new Single(0, 2, "3", new IndexExpression(2), true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ", "a", "a+3", "b", "b+2");
	analysis.AddAnalyses(arrAnalyses, 3);

	RB_FAIL(rbIN_RANGES_ARG(a, a+3, b, b+2, Compare<>(true), Equal<>()), analysis);
}

RB_TEST(Fail_TwoRanges3_Old)
{
	Analysis *arrAnalyses[] = {
		new Single(1, 2, "3", new IndexExpression(2), true)
	};

	int a[] = { 1, 2, 3 },
		c[] = { 12, 6 };

	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ", "c", "c+2", "a", "a+3");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES_ARG(c, c+2, a, a+3, Compare<>(), Pred2<ProductIs12>()), analysis);
}

RB_TEST(Fail_TwoRanges3_Full_Old)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("12", true)(", ").idx(0, ":")("1", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(1, ":")("6", true)(", ").idx(1, ":")("2", true)(")"),
		new Single(1, 2, "3", new IndexExpression(2), true)
	};

	int a[] = { 1, 2, 3 },
		c[] = { 12, 6 };

	TestableAnalysisOfRanges analysis("predicate applies to ranges ",
		"c", "c+2", "a", "a+3");
	analysis.AddAnalyses(arrAnalyses, 3);

	RB_FAIL(rbIN_RANGES_ARG(c, c+2, a, a+3, Compare<>(true), Pred2<ProductIs12>()), analysis);
}

RB_TEST(OneInputIteratorPred_Pass_Old)
{
	StubContainer stub(1, 3, 6);
	int arr[] = { 12, 4, 2 };
	RB_PASS(rbIN_RANGES_ARG(stub.begin(), stub.end(), arr, arr+3, Compare<false>(), Pred2<ProductIs12>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE_ARRAY_ARG(stub.begin(), stub.end(), arr, Compare<false>(), Pred2<ProductIs12>()));
}

RB_TEST(OneInputIteratorPred_Fail1_Old)
{
	StubContainer stub(5, 4, 2);
	int arr[] = { 2, 3, 6 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(0, ":")("5", true)(", ")
			.idx(0, ":")("2", true)(")")
	};
	TestableAnalysisOfRanges analysis("predicate applies to ranges ",
		"stub.begin()", "stub.end()", "arr", "arr+3");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES_ARG(stub.begin(), stub.end(), arr, arr+3, Compare<false>(), Pred2<ProductIs12>()),
		analysis);
}

RB_TEST(OneInputIteratorPred_Fail1_Full_Old)
{
	int arr[] = { 2, 3, 6 };
	StubContainer stub(5, 4, 2);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(0, ":")("5", true)(", ")
			.idx(0, ":")("2", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(1, ":")("4", true)(", ")
			.idx(1, ":")("3", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(2, ":")("2", true)(", ")
			.idx(2, ":")("6", true)(")")
	};
	TestableAnalysisOfRanges analysis("predicate applies to ranges ",
		"stub.begin()", "stub.end()", "arr", "arr+3");
	analysis.AddAnalyses(arrAnalyses, 3);

	RB_FAIL(rbIN_RANGES_ARG(stub.begin(), stub.end(), arr, arr+3,
			Compare<false>(true), Pred2<ProductIs12>()),
		analysis);
}

RB_TEST(OneInputIteratorPred_Fail2_Old)
{
	int arr[] = { 1, 3, 7 };
	StubContainer stub(12, 4, 2);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(2, ":")("2", true)(", ")
			.idx(2, ":")("7", true)(")")
	};
	TestableAnalysisOfRanges analysis("predicate applies to ranges ",
		"stub.begin()", "stub.end()", "arr", "arr+3");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES_ARG(stub.begin(), stub.end(), arr, arr+3, Compare<false>(), Pred2<ProductIs12>()),
		analysis);
}

RB_TEST(OneInputIteratorPred_Fail3_Old)
{
	int arr[] = { 1, 12, 20, 25, 29, 2 };
	StubContainer stub(12, 6);

	Analysis *arrAnalyses[] = {
		new Single(1, 2, "12", new IndexExpression(1), true),
		new Single(1, 2, "20", new IndexExpression(2), true),
		new Single(1, 2, "25", new IndexExpression(3), true),
		new Single(1, 2, "29", new IndexExpression(4), true)
	};
	TestableAnalysisOfRanges analysis("predicate applies to ranges ",
		"stub.begin()", "stub.end()", "arr", "arr+6");
	analysis.AddAnalyses(arrAnalyses, 4);

	RB_FAIL(rbIN_RANGES_ARG(stub.begin(), stub.end(), arr, arr+6, Compare<false>(), Pred2<ProductIs12>()),
		analysis);
}

RB_TEST(OneInputIteratorPred_Fail4_Old)
{
	int arr[] = { 1, 12, 3, 29, 2 };
	StubContainer stub(12, 4, 6);

	Analysis *arrAnalyses[] = {
		new Single(1, 2, "12", new IndexExpression(1), true),
		new Single(1, 2, "29", new IndexExpression(3), true)
	};
	TestableAnalysisOfRanges analysis("predicate applies to ranges ",
		"stub.begin()", "stub.end()", "arr", "arr+5");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGES_ARG(stub.begin(), stub.end(), arr, arr+5, Compare<false>(), Pred2<ProductIs12>()),
		analysis);
}

RB_TEST(OneInputIteratorPred_Fail4_Array_Old)
{
	int arr[] = { 1, 12, 3, 29, 2 };
	StubContainer stub(12, 4, 6);

	Analysis *arrAnalyses[] = {
		new Single(1, 2, "12", new IndexExpression(1), true),
		new Single(1, 2, "29", new IndexExpression(3), true)
	};
	TestableAnalysisOfRanges analysis("predicate applies to ranges ",
		"stub.begin()", "stub.end()", "arr", "arr+RICHBOOL_ARRAY_COUNT(arr)");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGE_ARRAY_ARG(stub.begin(), stub.end(), arr, Compare<false>(), Pred2<ProductIs12>()),
		analysis);
}

RB_TEST(OneInputIteratorPred_Fail5_Old)
{
	// this test demonstrates the unperfect behaviour of this rich boolean
	int arr[] = { 1, 5, 3, 6 };
	StubContainer stub(12, 4, 6, 2);

	Analysis *arrAnalyses[] = {
		new Single(1, 2, "5", new IndexExpression(1), true),
		MakeGeneralAnalysis(false)("predicate(").idx(2, ":")("6", true)(", ")
			.idx(3, ":")("6", true)(")"),
		new Single(0, 2, "2", new IndexExpression(3), true),
	};
	TestableAnalysisOfRanges analysis1("predicate applies to ranges ",
		"stub.begin()", "stub.end()", "arr", "arr+4");
	analysis1.AddAnalyses(arrAnalyses, 3);

	TestableAnalysisOfRanges analysis2("predicate applies to ranges ",
		"stub.begin()", "stub.end()", "arr", "arr+RICHBOOL_ARRAY_COUNT(arr)");
	analysis2.AddAnalyses(arrAnalyses, 3, false);

	RB_FAIL(rbIN_RANGES_ARG(stub.begin(), stub.end(), arr, arr+4, Compare<false>(),
			Pred2<ProductIs12>()),
		analysis1);
	stub.rewind();
	RB_FAIL(rbIN_RANGE_ARRAY_ARG(stub.begin(), stub.end(), arr, Compare<false>(),
			Pred2<ProductIs12>()),
		analysis2);
}

RB_TEST(TwoInputIteratorPred_Pass_Old)
{
	StubContainer stub(1, 3, 6);
	int arr[] = { 12, 4, 2 };
	Compare<false,false> compare;
	RB_PASS(rbIN_RANGES_ARG(arr, arr+3, stub.begin(), stub.end(), compare, Pred2<ProductIs12>()));
	stub.rewind();
	RB_PASS(rbIN_RANGES_ARG(stub.begin(), stub.end(), arr, arr+3, compare, Pred2<ProductIs12>()));
}

RB_TEST(TwoInputIterators_Pred_Fail_Old)
{
	StubContainer stub1(12, 3, 2), stub2(1, 3, 6);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("3", true)
			(", ").idx(1, ":")("3", true)(")")
	};
	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ",
		"stub1.begin()", "stub1.end()", "stub2.begin()", "stub2.end()");
	analysis.AddAnalyses(arrAnalyses, 1);

	Compare<false,false> compare;
	RB_FAIL(
		rbIN_RANGES_ARG(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(),
			compare, Pred2<ProductIs12>()),
		analysis);
}

RB_TEST(TwoInputIterators_Pred_Fail_Full_Old)
{
	StubContainer stub1(12, 3, 2), stub2(1, 3, 6);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("12", true)
			(", ").idx(0, ":")("1", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("3", true)
			(", ").idx(1, ":")("3", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(2, ":")("2", true)
			(", ").idx(2, ":")("6", true)(")")
	};
	TestableAnalysisOfRanges analysis(
		"predicate applies to ranges ",
		"stub1.begin()", "stub1.end()", "stub2.begin()", "stub2.end()");
	analysis.AddAnalyses(arrAnalyses, 3);

	Compare<false,false> compare(true);
	RB_FAIL(
		rbIN_RANGES_ARG(stub1.begin(), stub1.end(), stub2.begin(), stub2.end(),
			compare, Pred2<ProductIs12>()),
		analysis);
}

RB_TEST(Compare_Pass_WithValue)
{
	int a[] = { 2, 8, 10 }, b[] = { 2, 8, 10 };

	Equal<Value, StubGetValue> equal(Value(), StubGetValue(1));

	Compare<> compare1;
	RB_PASS(rbIN_RANGES(a, a+3, b, b+3, compare1.That(equal)));

	Compare<false> compare2;
	RB_PASS(rbIN_RANGES(a, a+3, b, b+3, compare2.That(equal)));
}

RB_TEST(Compare_Pass_WithStubGetValue)
{
	int a[] = { 2, 8, 10 }, b[] = { 2, 8, 10 };

	Equal<StubGetValue, StubGetValue> equal(StubGetValue(1), StubGetValue(2));

	Compare<> compare1;
	RB_PASS(rbIN_RANGES(a, a+3, b, b+3, compare1.That(equal)));

	Compare<false> compare2;
	RB_PASS(rbIN_RANGES(a, a+3, b, b+3, compare2.That(equal)));
}
