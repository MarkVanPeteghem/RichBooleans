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

RB_TEST(Succeed_IsMultiSubsetOf_MultiMulti_1_2)
{
	int a[] = { 1 };
	int b[] = { 0, 1 };

	RB_PASS(rbIN_ARRAYS(a, b, RichBool::IsMultiSubsetOf<>()));
}

RB_TEST(Succeed_IsMultiSubsetOf_MultiMulti_1_2_Negated)
{
	int a[] = { 2 };
	int b[] = { 0, 1 };

	RB_PASS(rbIN_ARRAYS(a, b, !RichBool::IsMultiSubsetOf<>()));
}

RB_TEST(Succeed_IsMultiSubsetOf_MultiMulti_1_0_Negated)
{
	int a[] = { 2 };
	int b[] = { 0 };

	RB_PASS(rbIN_RANGES(a, 1, b, 0, !RichBool::IsMultiSubsetOf<>()));
}

RB_TEST(Succeed_IsMultiSubsetOf_MultiMulti_3_5)
{
	int a[] = { 4, 7, 8 };
	int b[] = { 8, 2, 4, 7, 1 };

	RB_PASS(rbIN_ARRAYS(a, b, RichBool::IsMultiSubsetOf<>()));
}

RB_TEST(Succeed_IsMultiSubsetOf_MultiMulti_3_5_Negated)
{
	int a[] = { 4, 6, 8 };
	int b[] = { 8, 2, 4, 7, 1 };

	RB_PASS(rbIN_ARRAYS(a, b, !RichBool::IsMultiSubsetOf<>()));
}

RB_TEST(Succeed_IsMultiSubsetOf_MultiMulti_0_1)
{
	int a[] = { 1 };
	int b[] = { 1 };

	RB_PASS(rbIN_RANGE_ARRAY(a, 0, b, RichBool::IsMultiSubsetOf<>()));
}

RB_TEST(Succeed_IsMultiSubsetOf_MultiMulti_3_5_WithDoubles)
{
	int a[] = { 1, 2, 1 };
	int b[] = { 2, 1 };

	RB_PASS(rbIN_ARRAYS(a, b, RichBool::IsMultiSubsetOf<>()));
}

RB_TEST(Fail_IsMultiSubsetOf_MultiMulti_1_2)
{
	int a[] = { 2 };
	int b[] = { 0, 1 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfContainers analysis("", "a", " is multisubset of ", "b", "");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_ARRAYS(a, b, RichBool::IsMultiSubsetOf<>()), analysis);
}

RB_TEST(Fail_IsMultiSubsetOf_MultiMulti_1_2_Negated)
{
	int a[] = { 0 };
	int b[] = { 0, 1 };

	TestableAnalysisOfContainers analysis(
		"", "a", " is multisubset of ", "b", "", RichBool::Analysis::Ok);
	analysis.Negate();

	RB_FAIL(rbIN_ARRAYS(a, b, !RichBool::IsMultiSubsetOf<>()), analysis);
}

RB_TEST(Fail_IsMultiSubsetOf_MultiMulti_0_2_Negated)
{
	int a[] = { 0 };
	int b[] = { 0, 1 };

	TestableAnalysisOfRanges analysis(
		"", "a", "a", " is multisubset of ", "b", "1", "", RichBool::Analysis::Ok);
	analysis.Negate();

	RB_FAIL(rbIN_RANGES(a, a, b, 1, !RichBool::IsMultiSubsetOf<>()), analysis);
}

RB_TEST(Fail_IsMultiSubsetOf_MultiMulti_2_3)
{
	int a[] = { 2, 1 };
	int b[] = { 0, 1 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfContainers analysis("", "a", " is multisubset of ", "b", "");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_ARRAYS(a, b, RichBool::IsMultiSubsetOf<>()), analysis);
}

RB_TEST(Fail_IsMultiSubsetOf_MultiMulti_2_0)
{
	int a[] = { 2, 1 };
	int b[] = { 0 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true),
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(1), true)
	};

	TestableAnalysisOfRanges analysis("",
		"a", "2",
		" is multisubset of ",
		"b", "0",
		"");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGES(a, 2, b, 0, RichBool::IsMultiSubsetOf<>()), analysis);
}

RB_TEST(Fail_IsMultiSubsetOf_MultiMulti_2_3_Full)
{
	int a[] = { 2, 1 };
	int b[] = { 1, 0 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true),
		RichBool::MakeGeneralAnalysis(true).idx(1, ":")("1", true)(" == ").idx(0, ":")("1", true)
	};

	TestableAnalysisOfContainers analysis("", "a", " is multisubset of ", "b", "");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_ARRAYS(a, b, RichBool::IsMultiSubsetOf<>(true)), analysis);
}

RB_TEST(Fail_IsMultiSubsetOf_MultiMulti_2_3_Full_Negated)
{
	int a[] = { 0, 1 };
	int b[] = { 1, 0, 2 };

	RichBool::Analysis *arrAnalyses[] = {
		RichBool::MakeGeneralAnalysis(true).idx(0, ":")("0", true)(" == ").idx(1, ":")("0", true),
		RichBool::MakeGeneralAnalysis(true).idx(1, ":")("1", true)(" == ").idx(0, ":")("1", true)
	};

	TestableAnalysisOfContainers analysis(
		"", "a", " is multisubset of ", "b", "", RichBool::Analysis::Ok);
	analysis.AddAnalyses(arrAnalyses, 2);
	analysis.Negate();

	RB_FAIL(rbIN_ARRAYS(a, b, !RichBool::IsMultiSubsetOf<>(true)), analysis);
}


// tests for GetPoints

RB_TEST(GetPoints_IsMultiSubsetOf_None)
{
	int a[] = { 2, 1 };
	int b[] = { 3, 4, 5 };

	RichBool::IsMultiSubsetOf<> rb;
	RB_PASS(rbEQUAL(rb.GetPoints(a, 2, b, 3), 0u));
	RB_PASS(rbEQUAL((!rb).GetPoints(a, 2, b, 3), 10u));
}

RB_TEST(GetPoints_IsMultiSubsetOf_Partial)
{
	int a[] = { 2, 1, 3 };
	int b[] = { 3, 4, 5 };

	RichBool::IsMultiSubsetOf<> rb;
	RB_PASS(rbEQUAL(rb.GetPoints(a, 3, b, 3), 3u));
	RB_PASS(rbEQUAL((!rb).GetPoints(a, 3, b, 3), 7u));
}

RB_TEST(GetPoints_IsMultiSubsetOf_All)
{
	int a[] = { 2, 1, 3, 1 };
	int b[] = { 2, 3, 4, 1, 5 };

	RichBool::IsMultiSubsetOf<> rb;
	RB_PASS(rbEQUAL(rb.GetPoints(a, 4, b, 5), 10u));
}


// with a single-pass and a multi-pass range

RB_TEST(Succeed_IsMultiSubsetOf_SingleMulti_1_2)
{
	StubContainer a(1);
	int b[] = { 0, 1 };

	RB_PASS(rbIN_CONTAINER_ARRAY(a, b, RichBool::IsMultiSubsetOf<false>()));
}

RB_TEST(Succeed_IsMultiSubsetOf_SingleMulti_1_2_Negated)
{
	StubContainer a(2);
	int b[] = { 0, 1 };

	RB_PASS(rbIN_CONTAINER_ARRAY(a, b, !RichBool::IsMultiSubsetOf<false>()));
}

RB_TEST(Succeed_IsMultiSubsetOf_SingleMulti_1_0_Negated)
{
	StubContainer a(2);
	int b[] = { 0 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, 0, !RichBool::IsMultiSubsetOf<false>()));
}

RB_TEST(Succeed_IsMultiSubsetOf_SingleMulti_3_5)
{
	StubContainer a(4, 7, 8);
	int b[] = { 8, 2, 4, 7, 1 };

	RB_PASS(rbIN_CONTAINER_ARRAY(a, b, RichBool::IsMultiSubsetOf<false>()));
}

RB_TEST(Succeed_IsMultiSubsetOf_SingleMulti_0_1)
{
	StubContainer a;
	int b[] = { 1 };

	RB_PASS(rbIN_CONTAINER_ARRAY(a, b, RichBool::IsMultiSubsetOf<false>()));
}

RB_TEST(Succeed_IsMultiSubsetOf_SingleMulti_3_5_WithDoubles)
{
	StubContainer a(1, 2, 1);
	int b[] = { 2, 1 };

	RB_PASS(rbIN_CONTAINER_ARRAY(a, b, RichBool::IsMultiSubsetOf<false>()));
}

RB_TEST(Fail_IsMultiSubsetOf_SingleMulti_1_2)
{
	StubContainer a(2);
	int b[] = { 0, 1 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfContainers analysis("",
		"a", " is multisubset of ", "b", "");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_CONTAINER_ARRAY(a, b, RichBool::IsMultiSubsetOf<false>()), analysis);
}

RB_TEST(Fail_IsMultiSubsetOf_SingleMulti_1_2_Negated)
{
	StubContainer a(1);
	int b[] = { 0, 1 };

	TestableAnalysisOfContainers analysis("",
		"a", " is multisubset of ", "b", "", RichBool::Analysis::Ok);
	analysis.Negate();

	RB_FAIL(rbIN_CONTAINER_ARRAY(a, b, !RichBool::IsMultiSubsetOf<false>()), analysis);
}

RB_TEST(Fail_IsMultiSubsetOf_SingleMulti_0_2_Negated_EmptyRange)
{
	StubContainer a;
	int b[] = { 0, 1 };

	TestableAnalysisOfContainers analysis("",
		"a", " is multisubset of ", "b", "", RichBool::Analysis::Ok);
	analysis.Negate();

	RB_FAIL(rbIN_CONTAINER_ARRAY(a, b, !RichBool::IsMultiSubsetOf<false>()), analysis);
}

RB_TEST(Fail_IsMultiSubsetOf_SingleMulti_2_3)
{
	StubContainer a(2, 1);
	int b[] = { 0, 1 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfContainers analysis("",
		"a", " is multisubset of ", "b",	"");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_CONTAINER_ARRAY(a, b, RichBool::IsMultiSubsetOf<false>()), analysis);
}

RB_TEST(Fail_IsMultiSubsetOf_SingleMulti_2_0)
{
	StubContainer a(2, 1);
	int b[] = { 0 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true),
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(1), true)
	};

	TestableAnalysisOfRanges analysis("",
		"a.begin()", "2",
		" is multisubset of ",
		"b", "0",
		"");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGES(a.begin(), 2, b, 0, RichBool::IsMultiSubsetOf<false>()), analysis);
}

RB_TEST(Fail_IsMultiSubsetOf_SingleMulti_2_3_Full)
{
	StubContainer a(2, 1);
	int b[] = { 1, 0 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true),
		RichBool::MakeGeneralAnalysis(true).idx(1, ":")("1", true)(" == ").idx(0, ":")("1", true)
	};

	TestableAnalysisOfContainers analysis("",
		"a",
		" is multisubset of ",
		"b",
		"");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_CONTAINER_ARRAY(a, b, RichBool::IsMultiSubsetOf<false>(true)), analysis);
}

RB_TEST(Fail_IsMultiSubsetOf_SingleMulti_2_3_Full_Negated)
{
	StubContainer a(0, 1);
	int b[] = { 1, 0 };

	RichBool::Analysis *arrAnalyses[] = {
		RichBool::MakeGeneralAnalysis(true).idx(0, ":")("0", true)(" == ").idx(1, ":")("0", true),
		RichBool::MakeGeneralAnalysis(true).idx(1, ":")("1", true)(" == ").idx(0, ":")("1", true)
	};

	TestableAnalysisOfContainers analysis("",
		"a",
		" is multisubset of ",
		"b",
		"",
		RichBool::Analysis::Ok);
	analysis.AddAnalyses(arrAnalyses, 2);
	analysis.Negate();

	RB_FAIL(rbIN_CONTAINER_ARRAY(a, b, !RichBool::IsMultiSubsetOf<false>(true)), analysis);
}


// with a multi-pass and a single-pass range

static RichBool::IsMultiSubsetOf<true, false> IsMultiSubsetOfMultiSingle;

RB_TEST(Succeed_IsMultiSubsetOf_MultiSingle_1_2)
{
	int a[] = { 1 };
	StubContainer b(0, 1);

	RB_PASS(rbIN_ARRAY_CONTAINER(a, b, IsMultiSubsetOfMultiSingle));
}

RB_TEST(Succeed_IsMultiSubsetOf_MultiSingle_1_2_Negated)
{
	int a[] = { 2 };
	StubContainer b(0, 1);

	RB_PASS(rbIN_ARRAY_CONTAINER(a, b, !IsMultiSubsetOfMultiSingle));
}

RB_TEST(Succeed_IsMultiSubsetOf_MultiSingle_3_5)
{
	int a[] = { 4, 7, 8 };
	StubContainer b(8, 2, 4, 7, 1);

	RB_PASS(rbIN_ARRAY_CONTAINER(a, b, IsMultiSubsetOfMultiSingle));
}

RB_TEST(Succeed_IsMultiSubsetOf_MultiSingle_0_1)
{
	int a[] = { 0 };
	StubContainer b(1);

	RB_PASS(rbIN_RANGES(a, 0, b.begin(), b.end(), IsMultiSubsetOfMultiSingle));
}

RB_TEST(Succeed_IsMultiSubsetOf_MultiSingle_3_5_WithDoubles)
{
	int a[] = { 1, 2, 1 };
	StubContainer b(2, 1);

	RB_PASS(rbIN_ARRAY_CONTAINER(a, b, IsMultiSubsetOfMultiSingle));
}

RB_TEST(Fail_IsMultiSubsetOf_MultiSingle_1_2)
{
	int a[] = { 2 };
	StubContainer b(0, 1);

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfContainers analysis("",
		"a", " is multisubset of ", "b", "");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_ARRAY_CONTAINER(a, b, IsMultiSubsetOfMultiSingle), analysis);
}

RB_TEST(Fail_IsMultiSubsetOf_MultiSingle_1_2_Negated)
{
	int a[] = { 0 };
	StubContainer b(0, 1);

	TestableAnalysisOfContainers analysis("",
		"a", " is multisubset of ", "b", "", RichBool::Analysis::Ok);
	analysis.Negate();

	RB_FAIL(rbIN_ARRAY_CONTAINER(a, b, !IsMultiSubsetOfMultiSingle), analysis);
}

RB_TEST(Fail_IsMultiSubsetOf_MultiSingle_2_3)
{
	int a[] = { 2, 1 };
	StubContainer b(0, 1);

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfContainers analysis("",
		"a", " is multisubset of ", "b",	"");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_ARRAY_CONTAINER(a, b, IsMultiSubsetOfMultiSingle), analysis);
}

RB_TEST(Fail_IsMultiSubsetOf_MultiSingle_2_0)
{
	int a[] = { 2, 1 };
	StubContainer b;

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true),
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(1), true)
	};

	TestableAnalysisOfContainers analysis("", "a", " is multisubset of ", "b", "");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_ARRAY_CONTAINER(a, b, IsMultiSubsetOfMultiSingle), analysis);
}

RB_TEST(Fail_IsMultiSubsetOf_MultiSingle_2_3_Full)
{
	int a[] = { 2, 1 };
	StubContainer b(1, 0);

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfContainers analysis("",
		"a",
		" is multisubset of ",
		"b",
		"");
	analysis.AddAnalyses(arrAnalyses, 1);

	RichBool::IsMultiSubsetOf<true, false> IsMultiSubsetOfMultiSingleFull(true);
	RB_FAIL(rbIN_ARRAY_CONTAINER(a, b, IsMultiSubsetOfMultiSingleFull), analysis);
}

RB_TEST(Fail_IsMultiSubsetOf_MultiSingle_2_3_Full_Negated)
{
	int a[] = { 0, 1 };
	StubContainer b(1, 0);

	TestableAnalysisOfContainers analysis("",
		"a",
		" is multisubset of ",
		"b",
		"",
		RichBool::Analysis::Ok);
	analysis.Negate();

	RichBool::IsMultiSubsetOf<true, false> IsMultiSubsetOfMultiSingleFull(true);
	RB_FAIL(rbIN_ARRAY_CONTAINER(a, b, !IsMultiSubsetOfMultiSingleFull), analysis);
}


// tests for MatchesMultiSubsetOf

static RichBool::Pred2<ProductIs12> productIs12;

RB_TEST(Succeed_MatchesMultiSubsetOf_MultiMulti_1_2)
{
	int a[] = { 2, 3, 2 };
	int b[] = { 4, 0, 6 };

	RB_PASS(rbIN_RANGES(a, a+3, b, b+3, RichBool::MatchesMultiSubsetOf<>().That(productIs12)));
	RB_PASS(rbIN_RANGES(a, 3, b, 3, RichBool::MatchesMultiSubsetOf<>().That(productIs12)));
}

RB_TEST(Succeed_MatchesMultiSubsetOf_MultiMulti_1_2_Negate)
{
	int a[] = { 2, 3 };
	int b[] = { 0, 6 };

	RB_PASS(rbIN_RANGES(a, a+2, b, b+2, !RichBool::MatchesMultiSubsetOf<>().That(productIs12)));
	RB_PASS(rbIN_RANGES(a, 2, b, 2, !RichBool::MatchesMultiSubsetOf<>().That(productIs12)));
}
