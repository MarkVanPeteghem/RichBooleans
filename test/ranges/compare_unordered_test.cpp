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

RB_TEST(CompareUnordered_Ok)
{
	int a[] = { 1, 2, 3 }, b[] = { 2, 3, 1 };

	RB_PASS(rbIN_RANGES(a, a+3, b, b+3, CompareUnordered<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, 3, b, b+3, CompareUnordered<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, a+3, b, 3, CompareUnordered<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, 3, b, 3, CompareUnordered<>().That(Equal<>())));
}

RB_TEST(CompareUnordered_Ok_Negate)
{
	int a[] = { 1, 2, 3 }, b[] = { 2, 4, 1 };

	RB_PASS(rbIN_RANGES(a, a+3, b, b+3, !CompareUnordered<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, 3, b, b+3, !CompareUnordered<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, a+3, b, 3, !CompareUnordered<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, 3, b, 3, !CompareUnordered<>().That(Equal<>())));
}

RB_TEST(CompareUnordered_Ok_FirstEmpty_Negate)
{
	int a[] = { 0 }, b[] = { 2, 4, 1 };

	RB_PASS(rbIN_RANGES(a, a, b, b+3, !CompareUnordered<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, 0, b, b+3, !CompareUnordered<>().That(Equal<>())));
}

RB_TEST(CompareUnordered_Ok_SecondEmpty_Negate)
{
	int a[] = { 4, 2, 1 }, b[] = { 0 };

	RB_PASS(rbIN_RANGES(a, a+3, b, 0, !CompareUnordered<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, 3, b, b, !CompareUnordered<>().That(Equal<>())));
}

RB_TEST(CompareUnordered_Empty_Ok)
{
	int a[] = { 1 }, b[] = { 1 };

	RB_PASS(rbIN_RANGES(a, a, b, b, CompareUnordered<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, 0, b, b, CompareUnordered<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, a, b, 0, CompareUnordered<>().That(Equal<>())));
	RB_PASS(rbIN_RANGES(a, 0, b, 0, CompareUnordered<>().That(Equal<>())));
}

RB_TEST(CompareUnordered_One_Ok)
{
	int a[] = { 1 }, b[] = { 1 };

	RB_PASS(rbIN_RANGES(a, a+1, b, b+1, CompareUnordered<>().That(Equal<>())));
}

RB_TEST(CompareUnordered_Doubles1_Ok)
{
	int a[] = { 1, 1 }, b[] = { 1, 1 };

	RB_PASS(rbIN_RANGES(a, a+2, b, b+2, CompareUnordered<>().That(Equal<>())));
}

RB_TEST(CompareUnordered_Doubles2_Ok)
{
	int a[] = { 1, 2, 3, 1 }, b[] = { 2, 1, 3, 1 };

	RB_PASS(rbIN_RANGES(a, a+4, b, b+4, CompareUnordered<>().That(Equal<>())));
}

RB_TEST(CompareUnordered_FirstEmpty_Fail)
{
	int a[] = { 1 }, b[] = { 2, 3 };

	Analysis *arrAnalyses[] = {
		new Single(1, 2, "2", new IndexExpression(0), true),
		new Single(1, 2, "3", new IndexExpression(1), true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to unordered ranges ", "a", "a", "b", "b+2");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGES(a, a, b, b+2, CompareUnordered<>().That(Equal<>())), analysis);
}

RB_TEST(CompareUnordered_SecondEmpty_Fail)
{
	int a[] = { 2, 3 }, b[] = { 1 };

	Analysis *arrAnalyses[] = {
		new Single(0, 2, "2", new IndexExpression(0), true),
		new Single(0, 2, "3", new IndexExpression(1), true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to unordered ranges ", "a", "a+2", "b", "b");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGES(a, a+2, b, b, CompareUnordered<>().That(Equal<>())), analysis);
}

RB_TEST(CompareUnordered_Fail1)
{
	int a[] = { 2, 3, 1 }, b[] = { 3, 2 };

	Analysis *arrAnalyses[] = {
		new Single(0, 2, "1", new IndexExpression(2), true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to unordered ranges ", "a", "a+3", "b", "b+2");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a, a+3, b, b+2, CompareUnordered<>().That(Equal<>())), analysis);
}

RB_TEST(CompareUnordered_Fail1_Negate)
{
	int a[] = { 2, 3, 1 }, b[] = { 3, 1, 2 };

	TestableAnalysisOfRanges analysis(
		"predicate applies to unordered ranges ", "a", "a+3", "b", "b+3", Analysis::Ok);
	analysis.Negate();

	RB_FAIL(rbIN_RANGES(a, a+3, b, b+3, !CompareUnordered<>().That(Equal<>())), analysis);
}

RB_TEST(CompareUnordered_Fail1_BothEmpty_Negate)
{
	int a[] = { 0 }, b[] = { 0 };

	TestableAnalysisOfRanges analysis(
		"predicate applies to unordered ranges ", "a", "a", "b", "b", Analysis::Ok);
	analysis.Negate();

	RB_FAIL(rbIN_RANGES(a, a, b, b, !CompareUnordered<>().That(Equal<>())), analysis);
}

RB_TEST(CompareUnordered_Fail2)
{
	// the first element of the first range is treated differently,
	// hence this separate test
	int a[] = { 1, 2, 3 }, b[] = { 2, 3 };

	Analysis *arrAnalyses[] = {
		new Single(0, 2, "1", new IndexExpression(0), true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to unordered ranges ", "a", "a+3", "b", "b+2");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a, a+3, b, b+2, CompareUnordered<>().That(Equal<>())), analysis);
}

RB_TEST(CompareUnordered_Fail3)
{
	int a[] = { 2, 3 }, b[] = { 1, 2, 3 };

	Analysis *arrAnalyses[] = {
		new Single(1, 2, "1", new IndexExpression(0), true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to unordered ranges ", "a", "a+2", "b", "b+3");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a, a+2, b, b+3, CompareUnordered<>().That(Equal<>())), analysis);
}

RB_TEST(CompareUnordered_Full_Fail1)
{
	int a[] = { 2, 3, 1 }, b[] = { 3, 2 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("2", true)(" == ").idx(1, ":")("2", true),
		MakeGeneralAnalysis(true).idx(1, ":")("3", true)(" == ").idx(0, ":")("3", true),
		new Single(0, 2, "1", new IndexExpression(2), true)
	};

	TestableAnalysisOfRanges analysis1(
		"predicate applies to unordered ranges ", "a", "a+3", "b", "b+2");
	analysis1.AddAnalyses(arrAnalyses, 3);

	TestableAnalysisOfRanges analysis2(
		"predicate applies to unordered ranges ", "a", "3", "b", "b+2");
	analysis2.AddAnalyses(arrAnalyses, 3, false);

	TestableAnalysisOfRanges analysis3(
		"predicate applies to unordered ranges ", "a", "a+3", "b", "2");
	analysis3.AddAnalyses(arrAnalyses, 3, false);

	TestableAnalysisOfRanges analysis4(
		"predicate applies to unordered ranges ", "a", "3", "b", "2");
	analysis4.AddAnalyses(arrAnalyses, 3, false);

	RB_FAIL(rbIN_RANGES(a, a+3, b, b+2, CompareUnordered<>(true).That(Equal<>())), analysis1);
	RB_FAIL(rbIN_RANGES(a, 3, b, b+2, CompareUnordered<>(true).That(Equal<>())), analysis2);
	RB_FAIL(rbIN_RANGES(a, a+3, b, 2, CompareUnordered<>(true).That(Equal<>())), analysis3);
	RB_FAIL(rbIN_RANGES(a, 3, b, 2, CompareUnordered<>(true).That(Equal<>())), analysis4 );
}

RB_TEST(CompareUnordered_Full_Fail2)
{
	// the first element of the first range is treated differently,
	// hence this separate test
	int a[] = { 1, 2, 3 }, b[] = { 3, 2 };

	Analysis *arrAnalyses[] = {
		new Single(0, 2, "1", new IndexExpression(0), true),
		MakeGeneralAnalysis(true).idx(1, ":")("2", true)(" == ").idx(1, ":")("2", true),
		MakeGeneralAnalysis(true).idx(2, ":")("3", true)(" == ").idx(0, ":")("3", true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to unordered ranges ", "a", "a+3", "b", "b+2");
	analysis.AddAnalyses(arrAnalyses, 3);

	RB_FAIL(rbIN_RANGES(a, a+3, b, b+2, CompareUnordered<>(true).That(Equal<>())), analysis);
}

RB_TEST(CompareUnordered_Full_Fail3)
{
	int a[] = { 2, 3 }, b[] = { 1, 3, 2 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("2", true)(" == ").idx(2, ":")("2", true),
		MakeGeneralAnalysis(true).idx(1, ":")("3", true)(" == ").idx(1, ":")("3", true),
		new Single(1, 2, "1", new IndexExpression(0), true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to unordered ranges ", "a", "a+2", "b", "b+3");
	analysis.AddAnalyses(arrAnalyses, 3);

	RB_FAIL(rbIN_RANGES(a, a+2, b, b+3, CompareUnordered<>(true).That(Equal<>())), analysis);
}


// same where the first range is single pass:

RB_TEST(CompareUnordered_SinglePass_Ok)
{
	StubContainer a(1, 2, 3);
	int b[] = { 2, 3, 1 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b+3, CompareUnordered<false>().That(Equal<>())));
	a.rewind();
	RB_PASS(rbIN_RANGES(a.begin(), 3, b, b+3, CompareUnordered<false>().That(Equal<>())));
	a.rewind();
	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, 3, CompareUnordered<false>().That(Equal<>())));
	a.rewind();
	RB_PASS(rbIN_RANGES(a.begin(), 3, b, 3, CompareUnordered<false>().That(Equal<>())));
}

RB_TEST(CompareUnordered_SinglePass_Ok_Negate)
{
	StubContainer a(1, 2, 3);
	int b[] = { 2, 3, 4 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b+3, !CompareUnordered<false>().That(Equal<>())));
	a.rewind();
	RB_PASS(rbIN_RANGES(a.begin(), 3, b, b+3, !CompareUnordered<false>().That(Equal<>())));
}

RB_TEST(CompareUnordered_SinglePass_Ok_FirstEmpty_Negate)
{
	StubContainer a;
	int b[] = { 3, 1, 2 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b+3, !CompareUnordered<false>().That(Equal<>())));
	a.rewind();
	RB_PASS(rbIN_RANGES(a.begin(), 0, b, b+3, !CompareUnordered<false>().That(Equal<>())));
}

RB_TEST(CompareUnordered_SinglePass_Ok_SecondEmpty_Negate)
{
	StubContainer a(3, 1, 2);
	int b[] = { 0 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b, !CompareUnordered<false>().That(Equal<>())));
	a.rewind();
	RB_PASS(rbIN_RANGES(a.begin(), 3, b, b, !CompareUnordered<false>().That(Equal<>())));
}

RB_TEST(CompareUnordered_SinglePass_Empty_Ok)
{
	StubContainer a;
	int b[] = { 1 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b, CompareUnordered<false>().That(Equal<>())));
}

RB_TEST(CompareUnordered_SinglePass_One_Ok)
{
	StubContainer a(1);
	int b[] = { 1 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b+1, CompareUnordered<>().That(Equal<>())));
}

RB_TEST(CompareUnordered_SinglePass_Doubles1_Ok)
{
	StubContainer a(1, 1);
	int b[] = { 1, 1 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b+2, CompareUnordered<>().That(Equal<>())));
}

RB_TEST(CompareUnordered_SinglePass_Doubles2_Ok)
{
	StubContainer a(1, 2, 3, 1);
	int b[] = { 2, 1, 3, 1 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b+4, CompareUnordered<>().That(Equal<>())));
}

RB_TEST(CompareUnordered_SinglePass_FirstEmpty_Fail)
{
	StubContainer a;
	int b[] = { 2, 3 };

	Analysis *arrAnalyses[] = {
		new Single(1, 2, "2", new IndexExpression(0), true),
		new Single(1, 2, "3", new IndexExpression(1), true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to unordered ranges ", "a.begin()", "a.end()", "b", "b+2");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+2, CompareUnordered<false>().That(Equal<>())), analysis);
}

RB_TEST(CompareUnordered_SinglePass_Fail_Negate)
{
	StubContainer a(3,2);
	int b[] = { 2, 3 };

	TestableAnalysisOfRanges analysis(
		"predicate applies to unordered ranges ", "a.begin()", "a.end()", "b", "b+2", Analysis::Ok);
	analysis.Negate();

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+2, !CompareUnordered<false>().That(Equal<>())), analysis);
}

RB_TEST(CompareUnordered_SinglePass_Fail_BothEmpty_Negate)
{
	StubContainer a;
	int b[] = { 0 };

	TestableAnalysisOfRanges analysis(
		"predicate applies to unordered ranges ", "a.begin()", "a.end()", "b", "b", Analysis::Ok);
	analysis.Negate();

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b, !CompareUnordered<false>().That(Equal<>())), analysis);
}

RB_TEST(CompareUnordered_SinglePass_SecondEmpty_Fail)
{
	StubContainer a(2, 3);
	int b[] = { 1 };

	Analysis *arrAnalyses[] = {
		new Single(0, 2, "2", new IndexExpression(0), true),
		new Single(0, 2, "3", new IndexExpression(1), true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to unordered ranges ", "a.begin()", "a.end()", "b", "b");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b, CompareUnordered<false>().That(Equal<>())), analysis);
}

RB_TEST(CompareUnordered_SinglePass_Fail1)
{
	StubContainer a(2, 3, 1);
	int b[] = { 3, 2 };

	Analysis *arrAnalyses[] = {
		new Single(0, 2, "1", new IndexExpression(2), true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to unordered ranges ", "a.begin()", "a.end()", "b", "b+2");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+2, CompareUnordered<false>().That(Equal<>())), analysis);
}

RB_TEST(CompareUnordered_SinglePass_Fail2)
{
	// the first element of the first range is treated differently,
	// hence this separate test
	StubContainer a(1, 2, 3);
	int b[] = { 2, 3 };

	Analysis *arrAnalyses[] = {
		new Single(0, 2, "1", new IndexExpression(0), true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to unordered ranges ", "a.begin()", "a.end()", "b", "b+2");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+2, CompareUnordered<false>().That(Equal<>())), analysis);
}

RB_TEST(CompareUnordered_SinglePass_Fail3)
{
	StubContainer a(2, 3);
	int b[] = { 1, 2, 3 };

	Analysis *arrAnalyses[] = {
		new Single(1, 2, "1", new IndexExpression(0), true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to unordered ranges ", "a.begin()", "a.end()", "b", "b+3");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+3, CompareUnordered<false>().That(Equal<>())), analysis);
}

RB_TEST(CompareUnordered_SinglePass_Full_Fail1)
{
	StubContainer a(2, 3, 1);
	int b[] = { 3, 2 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("2", true)(" == ").idx(1, ":")("2", true),
		MakeGeneralAnalysis(true).idx(1, ":")("3", true)(" == ").idx(0, ":")("3", true),
		new Single(0, 2, "1", new IndexExpression(2), true)
	};

	TestableAnalysisOfRanges analysis1(
		"predicate applies to unordered ranges ", "a.begin()", "a.end()", "b", "b+2");
	analysis1.AddAnalyses(arrAnalyses, 3);
	TestableAnalysisOfRanges analysis2(
		"predicate applies to unordered ranges ", "a.begin()", "3", "b", "b+2");
	analysis2.AddAnalyses(arrAnalyses, 3, false);
	TestableAnalysisOfRanges analysis3(
		"predicate applies to unordered ranges ", "a.begin()", "a.end()", "b", "2");
	analysis3.AddAnalyses(arrAnalyses, 3, false);
	TestableAnalysisOfRanges analysis4(
		"predicate applies to unordered ranges ", "a.begin()", "3", "b", "2");
	analysis4.AddAnalyses(arrAnalyses, 3, false);

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+2, CompareUnordered<false>(true).That(Equal<>())), analysis1);
	a.rewind();
	RB_FAIL(rbIN_RANGES(a.begin(), 3, b, b+2, CompareUnordered<false>(true).That(Equal<>())), analysis2);
	a.rewind();
	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, 2, CompareUnordered<false>(true).That(Equal<>())), analysis3);
	a.rewind();
	RB_FAIL(rbIN_RANGES(a.begin(), 3, b, 2, CompareUnordered<false>(true).That(Equal<>())), analysis4);
}

RB_TEST(CompareUnordered_SinglePass_Full_Fail2)
{
	// the first element of the first range is treated differently,
	// hence this separate test
	StubContainer a(1, 2, 3);
	int b[] = { 3, 2 };

	Analysis *arrAnalyses[] = {
		new Single(0, 2, "1", new IndexExpression(0), true),
		MakeGeneralAnalysis(true).idx(1, ":")("2", true)(" == ").idx(1, ":")("2", true),
		MakeGeneralAnalysis(true).idx(2, ":")("3", true)(" == ").idx(0, ":")("3", true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to unordered ranges ", "a.begin()", "a.end()", "b", "b+2");
	analysis.AddAnalyses(arrAnalyses, 3);

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+2, CompareUnordered<false>(true).That(Equal<>())), analysis);
}

RB_TEST(CompareUnordered_SinglePass_Full_Fail2_Negate)
{
	StubContainer a(1, 2, 3);
	int b[] = { 3, 2, 1 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ").idx(2, ":")("1", true),
		MakeGeneralAnalysis(true).idx(1, ":")("2", true)(" == ").idx(1, ":")("2", true),
		MakeGeneralAnalysis(true).idx(2, ":")("3", true)(" == ").idx(0, ":")("3", true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to unordered ranges ", "a.begin()", "a.end()", "b", "b+3", Analysis::Ok);
	analysis.AddAnalyses(arrAnalyses, 3);
	analysis.Negate();

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+3, !CompareUnordered<false>(true).That(Equal<>())), analysis);
}

RB_TEST(CompareUnordered_SinglePass_Full_Fail3)
{
	StubContainer a(2, 3);
	int b[] = { 1, 3, 2 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("2", true)(" == ").idx(2, ":")("2", true),
		MakeGeneralAnalysis(true).idx(1, ":")("3", true)(" == ").idx(1, ":")("3", true),
		new Single(1, 2, "1", new IndexExpression(0), true)
	};

	TestableAnalysisOfRanges analysis(
		"predicate applies to unordered ranges ", "a.begin()", "a.end()", "b", "b+3");
	analysis.AddAnalyses(arrAnalyses, 3);

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+3, CompareUnordered<false>(true).That(Equal<>())), analysis);
}

RB_TEST(CompareUnordered_Pass_WithStubGetValue)
{
	int a[] = { 2, 8, 10 }, b[] = { 8, 2, 10 };

	Equal<StubGetValue, StubGetValue> equal(StubGetValue(1), StubGetValue(2));
	RB_PASS(rbIN_RANGES(a, a+3, b, b+3, CompareUnordered<>().That(equal)));
	RB_PASS(rbIN_RANGES(a, a+3, b, b+3, CompareUnordered<false>().That(equal)));
}


// tests for GetPoints

RB_TEST(CompareUnordered_GetPoints_Ok)
{
	int a[] = { 1, 2, 3 }, b[] = { 2, 3, 1 };

	RB_ASSERT(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, a+3, b, b+3), 10u));
	RB_ASSERT(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, a+3, b, 3), 10u));
	RB_ASSERT(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, 3, b, b+3), 10u));
	RB_ASSERT(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, 3, b, 3), 10u));
}

RB_TEST(CompareUnordered_GetPoints_OneMissingInFirst)
{
	int a[] = { 1, 2 }, b[] = { 2, 3, 1 };

	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, a+2, b, b+3), 6u));
	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, a+2, b, 3), 6u));
	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, 2, b, b+3), 6u));
	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, 2, b, 3), 6u));
}

RB_TEST(CompareUnordered_GetPoints_OneMissingInSecond)
{
	int a[] = { 1, 2, 3 }, b[] = { 2, 3 };

	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, a+3, b, b+2), 6u));
	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, a+3, b, 2), 6u));
	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, 3, b, b+2), 6u));
	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, 3, b, 2), 6u));
}

RB_TEST(CompareUnordered_GetPoints_OneExtraInBoth)
{
	int a[] = { 1, 5, 3, 2 }, b[] = { 2, 3, 1, 4 };

	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, a+4, b, b+4), 6u));
	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, a+4, b, 4), 6u));
	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, 4, b, b+4), 6u));
	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, 4, b, 4), 6u));
}

RB_TEST(CompareUnordered_GetPoints_FirstEmpty)
{
	int a[] = { 1 }, b[] = { 2, 3, 1 };

	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, a+0, b, b+3), 0u));
	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, a+0, b, 3), 0u));
	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, 0, b, b+3), 0u));
	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, 0, b, 3), 0u));
}

RB_TEST(CompareUnordered_GetPoints_SecondEmpty)
{
	int a[] = { 1, 5, 2 }, b[] = { 1 };

	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, a+3, b, b+0), 0u));
	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, a+3, b, 0), 0u));
	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, 3, b, b+0), 0u));
	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, 3, b, 0), 0u));
}

RB_TEST(CompareUnordered_GetPoints_BothEmpty)
{
	int a[] = { 1 }, b[] = { 1 };

	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, a+0, b, b+0), 10u));
	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, a+0, b, 0), 10u));
	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, 0, b, b+0), 10u));
	RB_PASS(rbEQUAL(CompareUnordered<>().That(Equal<>()).GetPoints(a, 0, b, 0), 10u));
}

