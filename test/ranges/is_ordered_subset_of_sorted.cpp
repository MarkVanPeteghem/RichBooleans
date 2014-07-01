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


// tests for Rich Booleans that check whether a range is an ordered subset
// of another sorted range, i.e. is a subset of the other range where the
// corresponding elements are in the same order

// with two multi-pass ranges

RB_TEST(Succeed_IsOrderedSubsetOfSorted_Multi_1_2)
{
	int a[] = { 1 };
	int b[] = { 0, 1 };

	RB_PASS(rbIN_ARRAYS(a, b, RichBool::IsOrderedSubsetOfSorted<>()));
}

RB_TEST(Succeed_IsOrderedSubsetOfSorted_Multi_3_5)
{
	int a[] = { 1, 4, 8 };
	int b[] = { 1, 2, 4, 7, 8 };

	RB_PASS(rbIN_ARRAYS(a, b, RichBool::IsOrderedSubsetOfSorted<>()));
}

RB_TEST(Succeed_IsOrderedSubsetOfSorted_Multi_3_5_Negate)
{
	int a[] = { 4, 6, 8 };
	int b[] = { 1, 2, 4, 7, 8 };

	RB_PASS(rbIN_ARRAYS(a, b, !RichBool::IsOrderedSubsetOfSorted<>()));
}

RB_TEST(Succeed_IsOrderedSubsetOfSorted_Multi_3_0_Negate)
{
	int a[] = { 4, 6, 8 };
	int b[] = { 0 };

	RB_PASS(rbIN_RANGES(a, 3, b, b, !RichBool::IsOrderedSubsetOfSorted<>()));
}

RB_TEST(Succeed_IsOrderedSubsetOfSorted_Multi_3_5_WithDoubles)
{
	int a[] = { 1, 1, 2 };
	int b[] = { 0, 1, 1, 2, 3 };

	RB_PASS(rbIN_ARRAYS(a, b, RichBool::IsOrderedSubsetOfSorted<>()));
}

RB_TEST(Succeed_IsOrderedSubsetOfSorted_Multi_3_5_WithDoubles_Negate)
{
	int a[] = { 1, 1, 2 };
	int b[] = { 1, 2, 3, 4, 0 };

	RB_PASS(rbIN_ARRAYS(a, b, !RichBool::IsOrderedSubsetOfSorted<>()));
}

RB_TEST(Succeed_IsOrderedSubsetOfSorted_Multi_0_1)
{
	int a[] = { 1 };
	int b[] = { 1 };

	RB_PASS(rbIN_RANGE_ARRAY(a, 0, b, RichBool::IsOrderedSubsetOfSorted<>()));
}

RB_TEST(Fail_IsOrderedSubsetOfSorted_Multi_1_2)
{
	int a[] = { 2 };
	int b[] = { 0, 1 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfContainers analysis("", "a", " is ordered subset of sorted ", "b", "");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_ARRAYS(a, b, RichBool::IsOrderedSubsetOfSorted<>()), analysis);
}

RB_TEST(Fail_IsOrderedSubsetOfSorted_Multi_2_3)
{
	int a[] = { 2, 1 };
	int b[] = { 0, 1, 4 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfContainers analysis("", "a", " is ordered subset of sorted ", "b", "");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_ARRAYS(a, b, RichBool::IsOrderedSubsetOfSorted<>()), analysis);
}

RB_TEST(Fail_IsOrderedSubsetOfSorted_Multi_2_3_Negate)
{
	int a[] = { 0, 1 };
	int b[] = { 0, 1, 4 };

	TestableAnalysisOfContainers analysis("", "a", " is ordered subset of sorted ", "b", "",
		RichBool::Analysis::Ok);
	analysis.Negate();

	RB_FAIL(rbIN_ARRAYS(a, b, !RichBool::IsOrderedSubsetOfSorted<>()), analysis);
}

RB_TEST(Fail_IsOrderedSubsetOfSorted_Multi_0_3_Negate)
{
	int a[] = { 0 };
	int b[] = { 0, 1, 4 };

	TestableAnalysisOfRanges analysis("", "a", "a", " is ordered subset of sorted ", "b", "3", "",
		RichBool::Analysis::Ok);
	analysis.Negate();

	RB_FAIL(rbIN_RANGES(a, a, b, 3, !RichBool::IsOrderedSubsetOfSorted<>()), analysis);
}

RB_TEST(Fail_IsOrderedSubsetOfSorted_Multi_2_3_WrongOrder)
{
	int a[] = { 2, 1 };
	int b[] = { 0, 1, 2, 4 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(1), true)
	};

	TestableAnalysisOfContainers analysis("", "a", " is ordered subset of sorted ", "b", "");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_ARRAYS(a, b, RichBool::IsOrderedSubsetOfSorted<>()), analysis);
}

RB_TEST(Fail_IsOrderedSubsetOfSorted_Multi_3_3_WithDoubles)
{
	int a[] = { 1, 2, 2 };
	int b[] = { 1, 2, 3 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(2), true)
	};

	TestableAnalysisOfContainers analysis("", "a", " is ordered subset of sorted ", "b", "");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_ARRAYS(a, b, RichBool::IsOrderedSubsetOfSorted<>()), analysis);
}

RB_TEST(Fail_IsOrderedSubsetOfSorted_Multi_2_0)
{
	int a[] = { 2, 1 };
	int b[] = { 0 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true),
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(1), true)
	};

	TestableAnalysisOfRanges analysis("",
		"a", "2",
		" is ordered subset of sorted ",
		"b", "0",
		"");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGES(a, 2, b, 0, RichBool::IsOrderedSubsetOfSorted<>()), analysis);
}

RB_TEST(Fail_IsOrderedSubsetOfSorted_Multi_2_3_Full)
{
	int a[] = { 2, 1 };
	int b[] = { 0, 1 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true),
		RichBool::MakeGeneralAnalysis(true).idx(1, ":")("1", true)(" == ").idx(1, ":")("1", true)
	};

	TestableAnalysisOfContainers analysis("", "a", " is ordered subset of sorted ", "b", "");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_ARRAYS(a, b, RichBool::IsOrderedSubsetOfSorted<>(true)), analysis);
}

// tests for GetPoints

RB_TEST(GetPoints_IsOrderedSubsetOfSorted_None)
{
	int a[] = { 2, 1 };
	int b[] = { 3, 4, 5 };

	RichBool::IsOrderedSubsetOfSorted<> rb;
	RB_PASS(rbEQUAL(rb.GetPoints(a, 2, b, 3), 0u));
}

RB_TEST(GetPoints_IsOrderedSubsetOfSorted_None_Negate)
{
	int a[] = { 2, 1 };
	int b[] = { 3, 4, 5 };

	RichBool::IsOrderedSubsetOfSorted<> rb;
	RB_PASS(rbEQUAL((!rb).GetPoints(a, 2, b, 3), 10u));
}

RB_TEST(GetPoints_IsOrderedSubsetOfSorted_Partial)
{
	int a[] = { 2, 1, 3 };
	int b[] = { 3, 4, 5 };

	RichBool::IsOrderedSubsetOfSorted<> rb;
	RB_PASS(rbEQUAL(rb.GetPoints(a, 3, b, 3), 3u));
}

RB_TEST(GetPoints_IsOrderedSubsetOfSorted_Partial_Negate)
{
	int a[] = { 2, 1, 3 };
	int b[] = { 3, 4, 5 };

	RichBool::IsOrderedSubsetOfSorted<> rb;
	RB_PASS(rbEQUAL((!rb).GetPoints(a, 3, b, 3), 7u));
}

RB_TEST(GetPoints_IsOrderedSubsetOfSorted_All)
{
	int a[] = { 1, 2, 5 };
	int b[] = { 1, 2, 3, 4, 5 };

	RichBool::IsOrderedSubsetOfSorted<> rb;
	RB_PASS(rbEQUAL(rb.GetPoints(a, 3, b, 5), 10u));
}

RB_TEST(GetPoints_IsOrderedSubsetOfSorted_All_Negate)
{
	int a[] = { 1, 2, 3 };
	int b[] = { 1, 2, 3, 4, 5 };

	RichBool::IsOrderedSubsetOfSorted<> rb;
	RB_PASS(rbEQUAL((!rb).GetPoints(a, 3, b, 5), 0u));
}

RB_TEST(GetPoints_IsOrderedSubsetOfSorted_WithDouble)
{
	int a[] = { 1, 1, 2, 3 };
	int b[] = { 1, 2, 3, 4, 5 };

	RichBool::IsOrderedSubsetOfSorted<> rb;
	RB_PASS(rbEQUAL(rb.GetPoints(a, 4, b, 5), 7u));
}


// with a single-pass and a multi-pass range

RB_TEST(Succeed_IsOrderedSubsetOfSorted_Single_1_2)
{
	StubContainer a(1);
	int b[] = { 0, 1 };

	RB_PASS(rbIN_CONTAINER_ARRAY(a, b, RichBool::IsOrderedSubsetOfSorted<false>()));
}

RB_TEST(Succeed_IsOrderedSubsetOfSorted_Single_3_5)
{
	StubContainer a(1, 7, 8);
	int b[] = { 1, 2, 4, 7, 8 };

	RB_PASS(rbIN_CONTAINER_ARRAY(a, b, RichBool::IsOrderedSubsetOfSorted<false>()));
}

RB_TEST(Succeed_IsOrderedSubsetOfSorted_Single_3_5_Negate)
{
	StubContainer a(4, 6, 8);
	int b[] = { 1, 2, 4, 7, 8 };

	RB_PASS(rbIN_CONTAINER_ARRAY(a, b, !RichBool::IsOrderedSubsetOfSorted<false>()));
}

RB_TEST(Succeed_IsOrderedSubsetOfSorted_Single_3_0_Negate)
{
	StubContainer a(4, 6, 8);
	int b[] = { 0 };

	RB_PASS(rbIN_RANGES(a.begin(), 3, b, 0, !RichBool::IsOrderedSubsetOfSorted<false>()));
}

RB_TEST(Succeed_IsOrderedSubsetOfSorted_Single_0_1)
{
	StubContainer a;
	int b[] = { 1 };

	RB_PASS(rbIN_CONTAINER_ARRAY(a, b, RichBool::IsOrderedSubsetOfSorted<false>()));
}

RB_TEST(Succeed_IsOrderedSubsetOfSorted_Single_3_5_WithDoubles)
{
	StubContainer a(1, 1, 2);
	int b[] = { 0, 1, 1, 2, 3 };

	RB_PASS(rbIN_CONTAINER_ARRAY(a, b, RichBool::IsOrderedSubsetOfSorted<false>()));
}

RB_TEST(Fail_IsOrderedSubsetOfSorted_Single_1_2)
{
	StubContainer a(2);
	int b[] = { 0, 1 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfContainers analysis("",
		"a", " is ordered subset of sorted ", "b", "");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_CONTAINER_ARRAY(a, b, RichBool::IsOrderedSubsetOfSorted<false>()), analysis);
}

RB_TEST(Fail_IsOrderedSubsetOfSorted_Single_2_2)
{
	StubContainer a(2, 1);
	int b[] = { 0, 1 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfContainers analysis("",
		"a", " is ordered subset of sorted ", "b",	"");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_CONTAINER_ARRAY(a, b, RichBool::IsOrderedSubsetOfSorted<false>()), analysis);
}

RB_TEST(Fail_IsOrderedSubsetOfSorted_Single_2_2_Negate)
{
	StubContainer a(0, 1);
	int b[] = { 0, 1, 2 };

	TestableAnalysisOfContainers analysis("", "a", " is ordered subset of sorted ", "b", "",
		RichBool::Analysis::Ok);
	analysis.Negate();

	RB_FAIL(rbIN_CONTAINER_ARRAY(a, b, !RichBool::IsOrderedSubsetOfSorted<false>()), analysis);
}

RB_TEST(Fail_IsOrderedSubsetOfSorted_Single_0_2_Negate)
{
	StubContainer a;
	int b[] = { 0, 1, 2 };

	TestableAnalysisOfContainers analysis("", "a", " is ordered subset of sorted ", "b", "",
		RichBool::Analysis::Ok);
	analysis.Negate();

	RB_FAIL(rbIN_CONTAINER_ARRAY(a, b, !RichBool::IsOrderedSubsetOfSorted<false>()), analysis);
}

RB_TEST(Fail_IsOrderedSubsetOfSorted_Single_2_3_WrongOrder)
{
	StubContainer a(2, 1);
	int b[] = { 0, 1, 2 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(1), true)
	};

	TestableAnalysisOfContainers analysis("",
		"a", " is ordered subset of sorted ", "b",	"");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_CONTAINER_ARRAY(a, b, RichBool::IsOrderedSubsetOfSorted<false>()), analysis);
}

RB_TEST(Fail_IsOrderedSubsetOfSorted_Single_2_0)
{
	StubContainer a(2, 1);
	int b[] = { 0 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true),
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(1), true)
	};

	TestableAnalysisOfRanges analysis("",
		"a.begin()", "2",
		" is ordered subset of sorted ",
		"b", "0",
		"");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGES(a.begin(), 2, b, 0, RichBool::IsOrderedSubsetOfSorted<false>()), analysis);
}

RB_TEST(Fail_IsOrderedSubsetOfSorted_Single_2_3_WithConsecutiveDoubles)
{
	StubContainer a(1, 2, 2);
	int b[] = { 1, 2 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(2), true)
	};

	TestableAnalysisOfRanges analysis("",
		"a.begin()", "3",
		" is ordered subset of sorted ",
		"b", "2",
		"");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a.begin(), 3, b, 2, RichBool::IsOrderedSubsetOfSorted<false>()), analysis);
}

RB_TEST(Fail_IsOrderedSubsetOfSorted_Single_2_3_Full)
{
	StubContainer a(1, 2);
	int b[] = { 0, 1 };

	RichBool::Analysis *arrAnalyses[] = {
		RichBool::MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ").idx(1, ":")("1", true),
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(1), true)
	};

	TestableAnalysisOfContainers analysis("",
		"a",
		" is ordered subset of sorted ",
		"b",
		"");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_CONTAINER_ARRAY(a, b, RichBool::IsOrderedSubsetOfSorted<false>(true)), analysis);
}


// tests for IsOrderedSubsetOfCustomSorted

static RichBool::More<> more;

RB_TEST(Succeed_IsOrderedSubsetOfCustomSorted_Multi)
{
	int a[] = { 1, 0 };
	int b[] = { 2, 1, 0 };

	RB_PASS(rbIN_RANGES(a, a+2, b, b+3, RichBool::IsOrderedSubsetOfCustomSorted<>().By(more)));
	RB_PASS(rbIN_RANGES(a, 2, b, 3, RichBool::IsOrderedSubsetOfCustomSorted<>().By(more)));
}

RB_TEST(Succeed_IsOrderedSubsetOfCustomSorted_Multi_Negate)
{
	int a[] = { 0, 1 };
	int b[] = { 1, 0 };

	RB_PASS(rbIN_RANGES(a, a+2, b, b+2, !RichBool::IsOrderedSubsetOfCustomSorted<>().By(more)));
	RB_PASS(rbIN_RANGES(a, 2, b, 2, !RichBool::IsOrderedSubsetOfCustomSorted<>().By(more)));
}
