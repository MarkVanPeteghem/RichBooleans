//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#if defined(_MSC_VER)
	#pragma warning(disable: 4786)
#endif

#include "richbool/richbool.hpp"
#include "richbool/containers.hpp"

#include "rbtest.hpp"
#include "testable_analysis_for_ranges.hpp"
#include "predicates.hpp"
#include "stub_container.hpp"
#include "stub_get_value.hpp"

// tests for Rich Booleans that check whether a range is a subset
// of another range

// with two multi-pass ranges

RB_TEST(Succeed_IsSubsetOfSorted_Multi_1_2)
{
	int a[] = { 1 };
	int b[] = { 0, 1 };

	RB_PASS(rbIN_RANGES(a, a+1, b, b+2, RichBool::IsSubsetOfSorted<>()));
	RB_PASS(rbIN_RANGES(a, 1, b, 2, RichBool::IsSubsetOfSorted<>()));
}

RB_TEST(Succeed_IsSubsetOfSorted_Multi_3_5)
{
	int a[] = { 7, 4, 8 };
	int b[] = { 1, 2, 4, 7, 8 };

	RB_PASS(rbIN_RANGES(a, a+3, b, b+5, RichBool::IsSubsetOfSorted<>()));
	RB_PASS(rbIN_RANGES(a, 3, b, 5, RichBool::IsSubsetOfSorted<>()));
}

RB_TEST(Succeed_IsSubsetOfSorted_Multi_3_5_Negate)
{
	int a[] = { 7, 6, 8 };
	int b[] = { 1, 2, 4, 7, 8 };

	RB_PASS(rbIN_RANGES(a, a+3, b, b+5, !RichBool::IsSubsetOfSorted<>()));
	RB_PASS(rbIN_RANGES(a, 3, b, 5, !RichBool::IsSubsetOfSorted<>()));
}

RB_TEST(Succeed_IsSubsetOfSorted_Multi_3_0_Negate)
{
	int a[] = { 7, 6, 8 };
	int b[] = { 0 };

	RB_PASS(rbIN_RANGES(a, a+3, b, b, !RichBool::IsSubsetOfSorted<>()));
	RB_PASS(rbIN_RANGES(a, 3, b, 0, !RichBool::IsSubsetOfSorted<>()));
}

RB_TEST(Succeed_IsSubsetOfSorted_Multi_3_5_WithDoubles)
{
	int a[] = { 1, 2, 1 };
	int b[] = { 0, 1, 1, 2, 3 };

	RB_PASS(rbIN_RANGES(a, a+3, b, b+5, RichBool::IsSubsetOfSorted<>()));
	RB_PASS(rbIN_RANGES(a, 3, b, 5, RichBool::IsSubsetOfSorted<>()));
}

RB_TEST(Succeed_IsSubsetOfSorted_Multi_3_5_WithDoubles_Negate)
{
	int a[] = { 1, 2, 1 };
	int b[] = { 0, 0, 1, 2, 3 };

	RB_PASS(rbIN_RANGES(a, a+3, b, b+5, !RichBool::IsSubsetOfSorted<>()));
	RB_PASS(rbIN_RANGES(a, 3, b, 5, !RichBool::IsSubsetOfSorted<>()));
}

RB_TEST(Succeed_IsSubsetOfSorted_Multi_0_1)
{
	int a[] = { 1 };
	int b[] = { 1 };

	RB_PASS(rbIN_RANGES(a, a, b, b+1, RichBool::IsSubsetOfSorted<>()));
	RB_PASS(rbIN_RANGES(a, 0, b, 1, RichBool::IsSubsetOfSorted<>()));
}

RB_TEST(Fail_IsSubsetOfSorted_Multi_1_2)
{
	int a[] = { 2 };
	int b[] = { 0, 1 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfRanges analysis1("", "a", "a+1", " is subset of sorted ", "b", "b+2", "");
	analysis1.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a, a+1, b, b+2, RichBool::IsSubsetOfSorted<>()), analysis1);

	TestableAnalysisOfRanges analysis2("", "a", "1", " is subset of sorted ", "b", "2", "");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	RB_FAIL(rbIN_RANGES(a, 1, b, 2, RichBool::IsSubsetOfSorted<>()), analysis2);
}

RB_TEST(Fail_IsSubsetOfSorted_Multi_2_3)
{
	int a[] = { 2, 1 };
	int b[] = { 0, 1 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfRanges analysis1("", "a", "a+2", " is subset of sorted ", "b", "b+2", "");
	analysis1.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a, a+2, b, b+2, RichBool::IsSubsetOfSorted<>()), analysis1);

	TestableAnalysisOfRanges analysis2("", "a", "2", " is subset of sorted ", "b", "2", "");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	RB_FAIL(rbIN_RANGES(a, 2, b, 2, RichBool::IsSubsetOfSorted<>()), analysis2);
}

RB_TEST(Fail_IsSubsetOfSorted_Multi_2_3_Negate)
{
	int a[] = { 0, 1 };
	int b[] = { 0, 1, 2 };

	TestableAnalysisOfRanges analysis1(
		"", "a", "a+2", " is subset of sorted ", "b", "b+3", "", RichBool::Analysis::Ok);
	analysis1.Negate();

	RB_FAIL(rbIN_RANGES(a, a+2, b, b+3, !RichBool::IsSubsetOfSorted<>()), analysis1);

	TestableAnalysisOfRanges analysis2(
		"", "a", "2", " is subset of sorted ", "b", "3", "", RichBool::Analysis::Ok);
	analysis2.Negate();

	RB_FAIL(rbIN_RANGES(a, 2, b, 3, !RichBool::IsSubsetOfSorted<>()), analysis2);
}

RB_TEST(Fail_IsSubsetOfSorted_Multi_0_3_Negate)
{
	int a[] = { 0 };
	int b[] = { 0, 1, 2 };

	TestableAnalysisOfRanges analysis1(
		"", "a", "a", " is subset of sorted ", "b", "b+3", "", RichBool::Analysis::Ok);
	analysis1.Negate();

	RB_FAIL(rbIN_RANGES(a, a, b, b+3, !RichBool::IsSubsetOfSorted<>()), analysis1);

	TestableAnalysisOfRanges analysis2(
		"", "a", "0", " is subset of sorted ", "b", "3", "", RichBool::Analysis::Ok);
	analysis2.Negate();

	RB_FAIL(rbIN_RANGES(a, 0, b, 3, !RichBool::IsSubsetOfSorted<>()), analysis2);
}

RB_TEST(Fail_IsSubsetOfSorted_Multi_3_3_WithDoubles)
{
	int a[] = { 2, 1, 2 };
	int b[] = { 1, 2, 3 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(2), true)
	};

	TestableAnalysisOfRanges analysis1("", "a", "a+3", " is subset of sorted ", "b", "b+3", "");
	analysis1.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a, a+3, b, b+3, RichBool::IsSubsetOfSorted<>()), analysis1);

	TestableAnalysisOfRanges analysis2("", "a", "3", " is subset of sorted ", "b", "3", "");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	RB_FAIL(rbIN_RANGES(a, 3, b, 3, RichBool::IsSubsetOfSorted<>()), analysis2);
}

RB_TEST(Fail_IsSubsetOfSorted_Multi_2_0)
{
	int a[] = { 2, 1 };
	int b[] = { 0 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true),
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(1), true)
	};

	TestableAnalysisOfRanges analysis1("", "a", "a+2", " is subset of sorted ", "b", "b", "");
	analysis1.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGES(a, a+2, b, b, RichBool::IsSubsetOfSorted<>()), analysis1);
}

RB_TEST(Fail_IsSubsetOfSorted_Multi_2_1)
{
	int a[] = { 2 };
	int b[] = { 0 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfRanges analysis2("", "a", "1", " is subset of sorted ", "b", "0", "");
	analysis2.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a, 1, b, 0, RichBool::IsSubsetOfSorted<>()), analysis2);
}

RB_TEST(Fail_IsSubsetOfSorted_Multi_2_2_Full)
{
	int a[] = { 2, 1 };
	int b[] = { 0, 1 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true),
		RichBool::MakeGeneralAnalysis(true).idx(1, ":")("1", true)(" == ").idx(1, ":")("1", true)
	};

	TestableAnalysisOfContainers analysis("", "a", " is subset of sorted ", "b", "");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_ARRAYS(a, b, RichBool::IsSubsetOfSorted<>(true)), analysis);
}


// tests for GetPoints

RB_TEST(GetPoints_IsSubsetOfSorted_None)
{
	int a[] = { 2, 1 };
	int b[] = { 3, 4, 5 };

	RichBool::IsSubsetOfSorted<> rb;
	RB_PASS(rbEQUAL(rb.GetPoints(a, 2, b, 3), 0u));
}

RB_TEST(GetPoints_IsSubsetOfSorted_Partial)
{
	int a[] = { 2, 1, 3 };
	int b[] = { 3, 4, 5 };

	RichBool::IsSubsetOfSorted<> rb;
	RB_PASS(rbEQUAL(rb.GetPoints(a, 3, b, 3), 3u));
}

RB_TEST(GetPoints_IsSubsetOfSorted_All)
{
	int a[] = { 2, 1, 3 };
	int b[] = { 1, 2, 3, 4, 5 };

	RichBool::IsSubsetOfSorted<> rb;
	RB_PASS(rbEQUAL(rb.GetPoints(a, 3, b, 5), 10u));
}

RB_TEST(GetPoints_IsSubsetOfSorted_WithDouble)
{
	int a[] = { 2, 1, 3, 1 };
	int b[] = { 1, 2, 3, 4, 5 };

	RichBool::IsSubsetOfSorted<> rb;
	RB_PASS(rbEQUAL(rb.GetPoints(a, 4, b, 5), 7u));
}

// with a single-pass and a multi-pass range

RB_TEST(Succeed_IsSubsetOfSorted_Single_1_2)
{
	StubContainer a(1);
	int b[] = { 0, 1 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b+2, RichBool::IsSubsetOfSorted<false>()));
	a.rewind();
	RB_PASS(rbIN_RANGES(a.begin(), a.size(), b, 2, RichBool::IsSubsetOfSorted<false>()));
}

RB_TEST(Succeed_IsSubsetOfSorted_Single_3_5)
{
	StubContainer a(4, 7, 8);
	int b[] = { 1, 2, 4, 7, 8 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b+5, RichBool::IsSubsetOfSorted<false>()));
	a.rewind();
	RB_PASS(rbIN_RANGES(a.begin(), a.size(), b, 5, RichBool::IsSubsetOfSorted<false>()));
}

RB_TEST(Succeed_IsSubsetOfSorted_Single_3_5_Negate)
{
	StubContainer a(4, 6, 8);
	int b[] = { 1, 2, 4, 7, 8 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b+5, !RichBool::IsSubsetOfSorted<false>()));
	a.rewind();
	RB_PASS(rbIN_RANGES(a.begin(), a.size(), b, 5, !RichBool::IsSubsetOfSorted<false>()));
}

RB_TEST(Succeed_IsSubsetOfSorted_Single_0_5_Negate)
{
	StubContainer a(1, 3);
	int b[] = { 0 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b, !RichBool::IsSubsetOfSorted<false>()));
	a.rewind();
	RB_PASS(rbIN_RANGES(a.begin(), a.size(), b, 0, !RichBool::IsSubsetOfSorted<false>()));
}

RB_TEST(Succeed_IsSubsetOfSorted_Single_0_1)
{
	StubContainer a;
	int b[] = { 1 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b+1, RichBool::IsSubsetOfSorted<false>()));
	a.rewind();
	RB_PASS(rbIN_RANGES(a.begin(), a.size(), b, 1, RichBool::IsSubsetOfSorted<false>()));
}

RB_TEST(Succeed_IsSubsetOfSorted_Single_3_5_WithDoubles)
{
	StubContainer a(1, 2, 1);
	int b[] = { 0, 1, 1, 2, 3 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b+5, RichBool::IsSubsetOfSorted<false>()));
	a.rewind();
	RB_PASS(rbIN_RANGES(a.begin(), a.size(), b, 5, RichBool::IsSubsetOfSorted<false>()));
}

RB_TEST(Fail_IsSubsetOfSorted_Single_1_2)
{
	StubContainer a(2);
	int b[] = { 0, 1 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfRanges analysis1("", "a.begin()", "a.end()", " is subset of sorted ", "b", "b+2", "");
	analysis1.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+2, RichBool::IsSubsetOfSorted<false>()), analysis1);

	a.rewind();
	TestableAnalysisOfRanges analysis2("", "a.begin()", "a.size()", " is subset of sorted ", "b", "2", "");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	RB_FAIL(rbIN_RANGES(a.begin(), a.size(), b, 2, RichBool::IsSubsetOfSorted<false>()), analysis2);
}

RB_TEST(Fail_IsSubsetOfSorted_Single_2_2)
{
	StubContainer a(2, 1);
	int b[] = { 0, 1 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfRanges analysis1("", "a.begin()", "a.end()", " is subset of sorted ", "b", "b+2", "");
	analysis1.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+2, RichBool::IsSubsetOfSorted<false>()), analysis1);

	a.rewind();
	TestableAnalysisOfRanges analysis2("", "a.begin()", "a.size()", " is subset of sorted ", "b", "2", "");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	RB_FAIL(rbIN_RANGES(a.begin(), a.size(), b, 2, RichBool::IsSubsetOfSorted<false>()), analysis2);
}

RB_TEST(Fail_IsSubsetOfSorted_Single_2_2_Negate)
{
	StubContainer a(0, 1);
	int b[] = { 0, 1, 2 };

	TestableAnalysisOfRanges analysis1(
		"", "a.begin()", "a.end()", " is subset of sorted ", "b", "b+3", "", RichBool::Analysis::Ok);
	analysis1.Negate();

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+3, !RichBool::IsSubsetOfSorted<false>()), analysis1);

	a.rewind();
	TestableAnalysisOfRanges analysis2(
		"", "a.begin()", "a.size()", " is subset of sorted ", "b", "3", "", RichBool::Analysis::Ok);
	analysis2.Negate();

	RB_FAIL(rbIN_RANGES(a.begin(), a.size(), b, 3, !RichBool::IsSubsetOfSorted<false>()), analysis2);
}

RB_TEST(Fail_IsSubsetOfSorted_Single_0_2_Negate)
{
	StubContainer a;
	int b[] = { 0, 1, 2 };

	TestableAnalysisOfRanges analysis1(
		"", "a.begin()", "a.end()", " is subset of sorted ", "b", "b+3", "", RichBool::Analysis::Ok);
	analysis1.Negate();

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+3, !RichBool::IsSubsetOfSorted<false>()), analysis1);

	a.rewind();
	TestableAnalysisOfRanges analysis2(
		"", "a.begin()", "a.size()", " is subset of sorted ", "b", "3", "", RichBool::Analysis::Ok);
	analysis2.Negate();

	RB_FAIL(rbIN_RANGES(a.begin(), a.size(), b, 3, !RichBool::IsSubsetOfSorted<false>()), analysis2);
}

RB_TEST(Fail_IsSubsetOfSorted_Single_2_0)
{
	StubContainer a(2, 1);
	int b[] = { 0 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true),
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(1), true)
	};

	TestableAnalysisOfRanges analysis1("", "a.begin()", "a.end()", " is subset of sorted ", "b", "b", "");
	analysis1.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b, RichBool::IsSubsetOfSorted<false>()), analysis1);

	a.rewind();
	TestableAnalysisOfRanges analysis2("", "a.begin()", "a.size()", " is subset of sorted ", "b", "0", "");
	analysis2.AddAnalyses(arrAnalyses, 2, false);

	RB_FAIL(rbIN_RANGES(a.begin(), a.size(), b, 0, RichBool::IsSubsetOfSorted<false>()), analysis2);
}

RB_TEST(Fail_IsSubsetOfSorted_Single_2_2_WithDoubles)
{
	StubContainer a(2, 1, 2);
	int b[] = { 1, 2 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(2), true)
	};

	TestableAnalysisOfRanges analysis1("", "a.begin()", "a.end()", " is subset of sorted ", "b", "b+2", "");
	analysis1.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+2, RichBool::IsSubsetOfSorted<false>()), analysis1);

	a.rewind();
	TestableAnalysisOfRanges analysis2("", "a.begin()", "a.size()", " is subset of sorted ", "b", "2", "");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	RB_FAIL(rbIN_RANGES(a.begin(), a.size(), b, 2, RichBool::IsSubsetOfSorted<false>()), analysis2);
}

RB_TEST(Fail_IsSubsetOfSorted_Single_2_2_Full)
{
	StubContainer a(2, 1);
	int b[] = { 0, 1 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true),
		RichBool::MakeGeneralAnalysis(true).idx(1, ":")("1", true)(" == ").idx(1, ":")("1", true)
	};

	TestableAnalysisOfRanges analysis1("", "a.begin()", "a.end()", " is subset of sorted ", "b", "b+2", "");
	analysis1.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+2, RichBool::IsSubsetOfSorted<false>()), analysis1);

	a.rewind();
	TestableAnalysisOfRanges analysis2("", "a.begin()", "a.size()", " is subset of sorted ", "b", "2", "");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	RB_FAIL(rbIN_RANGES(a.begin(), a.size(), b, 2, RichBool::IsSubsetOfSorted<false>()), analysis2);
}


// tests for IsSubsetOfCustomSorted

static RichBool::More<> more;

RB_TEST(Succeed_IsSubsetOfCustomSorted_Multi)
{
	int a[] = { 0, 1 };
	int b[] = { 2, 1, 0 };

	RB_PASS(rbIN_RANGES(a, a+2, b, b+3, RichBool::IsSubsetOfCustomSorted<>().By(more)));
	RB_PASS(rbIN_RANGES(a, 2, b, 3, RichBool::IsSubsetOfCustomSorted<>().By(more)));
}

RB_TEST(Succeed_IsSubsetOfCustomSorted_Multi_Negate)
{
	int a[] = { 0, 0 };
	int b[] = { 1, 0 };

	RB_PASS(rbIN_RANGES(a, a+2, b, b+2, !RichBool::IsSubsetOfCustomSorted<>().By(more)));
	RB_PASS(rbIN_RANGES(a, 2, b, 2, !RichBool::IsSubsetOfCustomSorted<>().By(more)));
}
