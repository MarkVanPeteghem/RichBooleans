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

RB_TEST(Succeed_IsSubsetOf_MultiMulti_1_2)
{
	int a[] = { 1 };
	int b[] = { 0, 1 };

	RB_PASS(rbIN_RANGES(a, a+1, b, b+2, RichBool::IsSubsetOf<>()));
	RB_PASS(rbIN_RANGES(a, 1, b, 2, RichBool::IsSubsetOf<>()));
}

RB_TEST(Succeed_IsSubsetOf_MultiMulti_3_5)
{
	int a[] = { 4, 7, 8 };
	int b[] = { 8, 2, 4, 7, 1 };

	RB_PASS(rbIN_RANGES(a, a+3, b, b+5, RichBool::IsSubsetOf<>()));
	RB_PASS(rbIN_RANGES(a, 3, b, 5, RichBool::IsSubsetOf<>()));
}

RB_TEST(Succeed_IsSubsetOf_MultiMulti_3_5_Negate)
{
	int a[] = { 4, 6, 8 };
	int b[] = { 8, 2, 4, 7, 1 };

	RB_PASS(rbIN_RANGES(a, a+3, b, b+5, !RichBool::IsSubsetOf<>()));
	RB_PASS(rbIN_RANGES(a, 3, b, 5, !RichBool::IsSubsetOf<>()));
}

RB_TEST(Succeed_IsSubsetOf_MultiMulti_3_0_Negate)
{
	int a[] = { 4, 6, 8 };
	int b[] = { 0 };

	RB_PASS(rbIN_RANGES(a, a+3, b, b, !RichBool::IsSubsetOf<>()));
	RB_PASS(rbIN_RANGES(a, 3, b, 0, !RichBool::IsSubsetOf<>()));
}

RB_TEST(Succeed_IsSubsetOf_MultiMulti_3_5_WithDoubles)
{
	int a[] = { 1, 2, 1 };
	int b[] = { 2, 1, 3, 1, 0 };

	RB_PASS(rbIN_RANGES(a, a+3, b, b+5, RichBool::IsSubsetOf<>()));
	RB_PASS(rbIN_RANGES(a, 3, b, 5, RichBool::IsSubsetOf<>()));
}

RB_TEST(Succeed_IsSubsetOf_MultiMulti_3_5_WithDoubles_Negate)
{
	int a[] = { 1, 2, 1 };
	int b[] = { 2, 1, 3, 4, 0 };

	RB_PASS(rbIN_RANGES(a, a+3, b, b+5, !RichBool::IsSubsetOf<>()));
	RB_PASS(rbIN_RANGES(a, 3, b, 5, !RichBool::IsSubsetOf<>()));
}

RB_TEST(Succeed_IsSubsetOf_MultiMulti_0_1)
{
	int a[] = { 1 };
	int b[] = { 1 };

	RB_PASS(rbIN_RANGES(a, a, b, b+1, RichBool::IsSubsetOf<>()));
	RB_PASS(rbIN_RANGES(a, 0, b, 1, RichBool::IsSubsetOf<>()));
}

RB_TEST(Fail_IsSubsetOf_MultiMulti_1_2)
{
	int a[] = { 2 };
	int b[] = { 0, 1 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfRanges analysis1("", "a", "a+1", " is subset of ", "b", "b+2", "");
	analysis1.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a, a+1, b, b+2, RichBool::IsSubsetOf<>()), analysis1);

	TestableAnalysisOfRanges analysis2("", "a", "1", " is subset of ", "b", "2", "");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	RB_FAIL(rbIN_RANGES(a, 1, b, 2, RichBool::IsSubsetOf<>()), analysis2);
}

RB_TEST(Fail_IsSubsetOf_MultiMulti_2_3)
{
	int a[] = { 2, 1 };
	int b[] = { 0, 1 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfRanges analysis1("", "a", "a+2", " is subset of ", "b", "b+2", "");
	analysis1.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a, a+2, b, b+2, RichBool::IsSubsetOf<>()), analysis1);

	TestableAnalysisOfRanges analysis2("", "a", "2", " is subset of ", "b", "2", "");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	RB_FAIL(rbIN_RANGES(a, 2, b, 2, RichBool::IsSubsetOf<>()), analysis2);
}

RB_TEST(Fail_IsSubsetOf_MultiMulti_2_3_Negate)
{
	int a[] = { 1, 0 };
	int b[] = { 0, 2, 1 };

	TestableAnalysisOfRanges analysis1(
		"", "a", "a+2", " is subset of ", "b", "b+3", "", RichBool::Analysis::Ok);
	analysis1.Negate();

	RB_FAIL(rbIN_RANGES(a, a+2, b, b+3, !RichBool::IsSubsetOf<>()), analysis1);

	TestableAnalysisOfRanges analysis2(
		"", "a", "2", " is subset of ", "b", "3", "", RichBool::Analysis::Ok);
	analysis2.Negate();

	RB_FAIL(rbIN_RANGES(a, 2, b, 3, !RichBool::IsSubsetOf<>()), analysis2);
}

RB_TEST(Fail_IsSubsetOf_MultiMulti_0_3_Negate)
{
	int a[] = { 0 };
	int b[] = { 0, 2, 1 };

	TestableAnalysisOfRanges analysis1(
		"", "a", "a", " is subset of ", "b", "b+3", "", RichBool::Analysis::Ok);
	analysis1.Negate();

	RB_FAIL(rbIN_RANGES(a, a, b, b+3, !RichBool::IsSubsetOf<>()), analysis1);
}

RB_TEST(Fail_IsSubsetOf_MultiMulti_3_3_WithDoubles)
{
	int a[] = { 2, 1, 2 };
	int b[] = { 1, 2, 3 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(2), true)
	};

	TestableAnalysisOfRanges analysis1("", "a", "a+3", " is subset of ", "b", "b+3", "");
	analysis1.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a, a+3, b, b+3, RichBool::IsSubsetOf<>()), analysis1);

	TestableAnalysisOfRanges analysis2("", "a", "3", " is subset of ", "b", "3", "");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	RB_FAIL(rbIN_RANGES(a, 3, b, 3, RichBool::IsSubsetOf<>()), analysis2);
}

RB_TEST(Fail_IsSubsetOf_MultiMulti_2_0)
{
	int a[] = { 2, 1 };
	int b[] = { 0 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true),
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(1), true)
	};

	TestableAnalysisOfRanges analysis1("", "a", "a+2", " is subset of ", "b", "b", "");
	analysis1.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGES(a, a+2, b, b, RichBool::IsSubsetOf<>()), analysis1);

	TestableAnalysisOfRanges analysis2("", "a", "2", " is subset of ", "b", "0", "");
	analysis2.AddAnalyses(arrAnalyses, 2, false);

	RB_FAIL(rbIN_RANGES(a, 2, b, 0, RichBool::IsSubsetOf<>()), analysis2);
}

RB_TEST(Fail_IsSubsetOf_MultiMulti_2_3_Full)
{
	int a[] = { 2, 1 };
	int b[] = { 1, 0 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true),
		RichBool::MakeGeneralAnalysis(true).idx(1, ":")("1", true)(" == ").idx(0, ":")("1", true)
	};

	TestableAnalysisOfContainers analysis("", "a", " is subset of ", "b", "");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_ARRAYS(a, b, RichBool::IsSubsetOf<>(true)), analysis);
}

RB_TEST(Fail_IsSubsetOf_MultiMulti_2_3_Full_Negate)
{
	int a[] = { 0, 1 };
	int b[] = { 1, 2, 0 };

	RichBool::Analysis *arrAnalyses[] = {
		RichBool::MakeGeneralAnalysis(true).idx(0, ":")("0", true)(" == ").idx(2, ":")("0", true),
		RichBool::MakeGeneralAnalysis(true).idx(1, ":")("1", true)(" == ").idx(0, ":")("1", true)
	};

	TestableAnalysisOfContainers analysis("", "a", " is subset of ", "b", "",
		RichBool::Analysis::Ok);
	analysis.AddAnalyses(arrAnalyses, 2);
	analysis.Negate();

	RB_FAIL(rbIN_ARRAYS(a, b, !RichBool::IsSubsetOf<>(true)), analysis);
}


// tests for GetPoints

RB_TEST(GetPoints_IsSubsetOf_None)
{
	int a[] = { 2, 1 };
	int b[] = { 3, 4, 5 };

	RichBool::IsSubsetOf<> rb;
	RB_PASS(rbEQUAL(rb.GetPoints(a, 2, b, 3), 0u));
}

RB_TEST(GetPoints_IsSubsetOf_Partial)
{
	int a[] = { 2, 1, 3 };
	int b[] = { 3, 4, 5 };

	RichBool::IsSubsetOf<> rb;
	RB_PASS(rbEQUAL(rb.GetPoints(a, 3, b, 3), 3u));
}

RB_TEST(GetPoints_IsSubsetOf_All)
{
	int a[] = { 2, 1, 3 };
	int b[] = { 2, 3, 4, 1, 5 };

	RichBool::IsSubsetOf<> rb;
	RB_PASS(rbEQUAL(rb.GetPoints(a, 3, b, 5), 10u));
}

RB_TEST(GetPoints_IsSubsetOf_WithDouble)
{
	int a[] = { 2, 1, 3, 1 };
	int b[] = { 2, 3, 4, 1, 5 };

	RichBool::IsSubsetOf<> rb;
	RB_PASS(rbEQUAL(rb.GetPoints(a, 4, b, 5), 7u));
}


// with a single-pass and a multi-pass range

RB_TEST(Succeed_IsSubsetOf_SingleMulti_1_2)
{
	StubContainer a(1);
	int b[] = { 0, 1 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b+2, RichBool::IsSubsetOf<false>()));
	a.rewind();
	RB_PASS(rbIN_RANGES(a.begin(), a.size(), b, 2, RichBool::IsSubsetOf<false>()));
}

RB_TEST(Succeed_IsSubsetOf_SingleMulti_3_5)
{
	StubContainer a(4, 7, 8);
	int b[] = { 8, 2, 4, 7, 1 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b+5, RichBool::IsSubsetOf<false>()));
	a.rewind();
	RB_PASS(rbIN_RANGES(a.begin(), a.size(), b, 5, RichBool::IsSubsetOf<false>()));
}

RB_TEST(Succeed_IsSubsetOf_SingleMulti_3_5_Negate)
{
	StubContainer a(4, 6, 8);
	int b[] = { 8, 2, 4, 7, 1 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b+5, !RichBool::IsSubsetOf<false>()));
	a.rewind();
	RB_PASS(rbIN_RANGES(a.begin(), a.size(), b, 5, !RichBool::IsSubsetOf<false>()));
}

RB_TEST(Succeed_IsSubsetOf_SingleMulti_3_0_Negate)
{
	StubContainer a(4, 6, 8);
	int b[] = { 0 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b, !RichBool::IsSubsetOf<false>()));
	a.rewind();
	RB_PASS(rbIN_RANGES(a.begin(), a.size(), b, 0, !RichBool::IsSubsetOf<false>()));
}

RB_TEST(Succeed_IsSubsetOf_SingleMulti_0_1)
{
	StubContainer a;
	int b[] = { 1 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b+1, RichBool::IsSubsetOf<false>()));
	a.rewind();
	RB_PASS(rbIN_RANGES(a.begin(), a.size(), b, 1, RichBool::IsSubsetOf<false>()));
}

RB_TEST(Succeed_IsSubsetOf_SingleMulti_3_5_WithDoubles)
{
	StubContainer a(1, 2, 1);
	int b[] = { 2, 1, 3, 1, 0 };

	RB_PASS(rbIN_RANGES(a.begin(), a.end(), b, b+5, RichBool::IsSubsetOf<false>()));
	a.rewind();
	RB_PASS(rbIN_RANGES(a.begin(), a.size(), b, 5, RichBool::IsSubsetOf<false>()));
}

RB_TEST(Fail_IsSubsetOf_SingleMulti_1_2)
{
	StubContainer a(2);
	int b[] = { 0, 1 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfRanges analysis1("", "a.begin()", "a.end()", " is subset of ", "b", "b+2", "");
	analysis1.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+2, RichBool::IsSubsetOf<false>()), analysis1);

	a.rewind();
	TestableAnalysisOfRanges analysis2("", "a.begin()", "a.size()", " is subset of ", "b", "2", "");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	RB_FAIL(rbIN_RANGES(a.begin(), a.size(), b, 2, RichBool::IsSubsetOf<false>()), analysis2);
}

RB_TEST(Fail_IsSubsetOf_SingleMulti_2_2)
{
	StubContainer a(2, 1);
	int b[] = { 0, 1 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfRanges analysis1("", "a.begin()", "a.end()", " is subset of ", "b", "b+2", "");
	analysis1.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+2, RichBool::IsSubsetOf<false>()), analysis1);

	a.rewind();
	TestableAnalysisOfRanges analysis2("", "a.begin()", "a.size()", " is subset of ", "b", "2", "");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	RB_FAIL(rbIN_RANGES(a.begin(), a.size(), b, 2, RichBool::IsSubsetOf<false>()), analysis2);
}

RB_TEST(Fail_IsSubsetOf_SingleMulti_2_2_Negate)
{
	StubContainer a(0, 1);
	int b[] = { 0, 2, 1 };

	TestableAnalysisOfRanges analysis1(
		"", "a.begin()", "a.end()", " is subset of ", "b", "b+3", "", RichBool::Analysis::Ok);
	analysis1.Negate();

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+3, !RichBool::IsSubsetOf<false>()), analysis1);

	a.rewind();
	TestableAnalysisOfRanges analysis2(
		"", "a.begin()", "a.size()", " is subset of ", "b", "3", "", RichBool::Analysis::Ok);
	analysis2.Negate();

	RB_FAIL(rbIN_RANGES(a.begin(), a.size(), b, 3, !RichBool::IsSubsetOf<false>()), analysis2);
}

RB_TEST(Fail_IsSubsetOf_SingleMulti_0_2_Negate)
{
	StubContainer a;
	int b[] = { 0, 2, 1 };

	TestableAnalysisOfRanges analysis1(
		"", "a.begin()", "a.end()", " is subset of ", "b", "b+3", "", RichBool::Analysis::Ok);
	analysis1.Negate();

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+3, !RichBool::IsSubsetOf<false>()), analysis1);

	a.rewind();
	TestableAnalysisOfRanges analysis2(
		"", "a.begin()", "a.size()", " is subset of ", "b", "3", "", RichBool::Analysis::Ok);
	analysis2.Negate();

	RB_FAIL(rbIN_RANGES(a.begin(), a.size(), b, 3, !RichBool::IsSubsetOf<false>()), analysis2);
}

RB_TEST(Fail_IsSubsetOf_SingleMulti_2_0)
{
	StubContainer a(2, 1);
	int b[] = { 0 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true),
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(1), true)
	};

	TestableAnalysisOfRanges analysis1("", "a.begin()", "a.end()", " is subset of ", "b", "b", "");
	analysis1.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b, RichBool::IsSubsetOf<false>()), analysis1);

	a.rewind();
	TestableAnalysisOfRanges analysis2("", "a.begin()", "a.size()", " is subset of ", "b", "0", "");
	analysis2.AddAnalyses(arrAnalyses, 2, false);

	RB_FAIL(rbIN_RANGES(a.begin(), a.size(), b, 0, RichBool::IsSubsetOf<false>()), analysis2);
}

RB_TEST(Fail_IsSubsetOf_SingleMulti_2_2_WithDoubles)
{
	StubContainer a(2, 1, 2);
	int b[] = { 1, 2 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(2), true)
	};

	TestableAnalysisOfRanges analysis1("", "a.begin()", "a.end()", " is subset of ", "b", "b+2", "");
	analysis1.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+2, RichBool::IsSubsetOf<false>()), analysis1);

	a.rewind();
	TestableAnalysisOfRanges analysis2("", "a.begin()", "a.size()", " is subset of ", "b", "2", "");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	RB_FAIL(rbIN_RANGES(a.begin(), a.size(), b, 2, RichBool::IsSubsetOf<false>()), analysis2);
}

RB_TEST(Fail_IsSubsetOf_SingleMulti_2_3_Full)
{
	StubContainer a(2, 1);
	int b[] = { 1, 0 };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true),
		RichBool::MakeGeneralAnalysis(true).idx(1, ":")("1", true)(" == ").idx(0, ":")("1", true)
	};

	TestableAnalysisOfRanges analysis1("", "a.begin()", "a.end()", " is subset of ", "b", "b+2", "");
	analysis1.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGES(a.begin(), a.end(), b, b+2, RichBool::IsSubsetOf<false>()), analysis1);

	a.rewind();
	TestableAnalysisOfRanges analysis2("", "a.begin()", "a.size()", " is subset of ", "b", "2", "");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	RB_FAIL(rbIN_RANGES(a.begin(), a.size(), b, 2, RichBool::IsSubsetOf<false>()), analysis2);
}


// with a multi-pass and a single-pass range

static RichBool::IsSubsetOf<true, false> IsSubsetOfMultiSingle;

RB_TEST(Succeed_IsSubsetOf_MultiSingle_1_2)
{
	int a[] = { 1 };
	StubContainer b(0, 1);

	RB_PASS(rbIN_RANGES(a, a+1, b.begin(), b.end(), IsSubsetOfMultiSingle));
	b.rewind();
	RB_PASS(rbIN_RANGES(a, 1, b.begin(), b.size(), IsSubsetOfMultiSingle));
}

RB_TEST(Succeed_IsSubsetOf_MultiSingle_3_5)
{
	int a[] = { 4, 7, 8 };
	StubContainer b(8, 2, 4, 7, 1);

	RB_PASS(rbIN_RANGES(a, a+3, b.begin(), b.end(), IsSubsetOfMultiSingle));
	b.rewind();
	RB_PASS(rbIN_RANGES(a, 3, b.begin(), b.size(), IsSubsetOfMultiSingle));
}

RB_TEST(Succeed_IsSubsetOf_MultiSingle_3_5_Negate)
{
	int a[] = { 4, 6, 8 };
	StubContainer b(8, 2, 4, 7, 1);

	RB_PASS(rbIN_RANGES(a, a+3, b.begin(), b.end(), !IsSubsetOfMultiSingle));
	b.rewind();
	RB_PASS(rbIN_RANGES(a, 3, b.begin(), b.size(), !IsSubsetOfMultiSingle));
}

RB_TEST(Succeed_IsSubsetOf_MultiSingle_3_0_Negate)
{
	int a[] = { 4, 6, 8 };
	StubContainer b;

	RB_PASS(rbIN_RANGES(a, a+3, b.begin(), b.end(), !IsSubsetOfMultiSingle));
	b.rewind();
	RB_PASS(rbIN_RANGES(a, 3, b.begin(), b.size(), !IsSubsetOfMultiSingle));
}

RB_TEST(Succeed_IsSubsetOf_MultiSingle_0_1)
{
	int a[] = { 0 };
	StubContainer b(1);

	RB_PASS(rbIN_RANGES(a, a, b.begin(), b.end(), IsSubsetOfMultiSingle));
	b.rewind();
	RB_PASS(rbIN_RANGES(a, 0, b.begin(), b.size(), IsSubsetOfMultiSingle));
}

RB_TEST(Succeed_IsSubsetOf_MultiSingle_3_5_WithDoubles)
{
	int a[] = { 1, 2, 1 };
	StubContainer b(2, 1, 3, 1);

	RB_PASS(rbIN_RANGES(a, a+3, b.begin(), b.end(), IsSubsetOfMultiSingle));
	b.rewind();
	RB_PASS(rbIN_RANGES(a, 3, b.begin(), b.size(), IsSubsetOfMultiSingle));
}

RB_TEST(Fail_IsSubsetOf_MultiSingle_1_2)
{
	int a[] = { 2 };
	StubContainer b(0, 1);

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfRanges analysis1("", "a", "a+1", " is subset of ", "b.begin()", "b.end()", "");
	analysis1.AddAnalyses(arrAnalyses, 1);
	RB_FAIL(rbIN_RANGES(a, a+1, b.begin(), b.end(), IsSubsetOfMultiSingle), analysis1);

	b.rewind();
	TestableAnalysisOfRanges analysis2("", "a", "1", " is subset of ", "b.begin()", "b.size()", "");
	analysis2.AddAnalyses(arrAnalyses, 1, false);
	RB_FAIL(rbIN_RANGES(a, 1, b.begin(), b.size(), IsSubsetOfMultiSingle), analysis2);
}

RB_TEST(Fail_IsSubsetOf_MultiSingle_2_3)
{
	int a[] = { 2, 1 };
	StubContainer b(0, 1);

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfRanges analysis1("", "a", "a+2", " is subset of ", "b.begin()", "b.end()", "");
	analysis1.AddAnalyses(arrAnalyses, 1);
	RB_FAIL(rbIN_RANGES(a, a+2, b.begin(), b.end(), IsSubsetOfMultiSingle), analysis1);

	b.rewind();
	TestableAnalysisOfRanges analysis2("", "a", "2", " is subset of ", "b.begin()", "b.size()", "");
	analysis2.AddAnalyses(arrAnalyses, 1, false);
	RB_FAIL(rbIN_RANGES(a, 2, b.begin(), b.size(), IsSubsetOfMultiSingle), analysis2);
}

RB_TEST(Fail_IsSubsetOf_MultiSingle_2_3_Negate)
{
	int a[] = { 0, 1 };
	StubContainer b(0, 2, 1);

	TestableAnalysisOfRanges analysis1(
		"", "a", "a+2", " is subset of ", "b.begin()", "b.end()", "", RichBool::Analysis::Ok);
	analysis1.Negate();
	RB_FAIL(rbIN_RANGES(a, a+2, b.begin(), b.end(), !IsSubsetOfMultiSingle), analysis1);

	b.rewind();
	TestableAnalysisOfRanges analysis2(
		"", "a", "2", " is subset of ", "b.begin()", "b.size()", "", RichBool::Analysis::Ok);
	analysis2.Negate();
	RB_FAIL(rbIN_RANGES(a, 2, b.begin(), b.size(), !IsSubsetOfMultiSingle), analysis2);
}

RB_TEST(Fail_IsSubsetOf_MultiSingle_0_3_Negate)
{
	int a[] = { 0 };
	StubContainer b(0, 2, 1);

	TestableAnalysisOfRanges analysis1(
		"", "a", "a", " is subset of ", "b.begin()", "b.end()", "", RichBool::Analysis::Ok);
	analysis1.Negate();
	RB_FAIL(rbIN_RANGES(a, a, b.begin(), b.end(), !IsSubsetOfMultiSingle), analysis1);
}

RB_TEST(Fail_IsSubsetOf_MultiSingle_2_3_WithDoubles)
{
	int a[] = { 2, 1, 2 };
	StubContainer b(1, 2);

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(2), true)
	};

	TestableAnalysisOfRanges analysis1("", "a", "a+3", " is subset of ", "b.begin()", "b.end()", "");
	analysis1.AddAnalyses(arrAnalyses, 1);
	RB_FAIL(rbIN_RANGES(a, a+3, b.begin(), b.end(), IsSubsetOfMultiSingle), analysis1);

	b.rewind();
	TestableAnalysisOfRanges analysis2("", "a", "3", " is subset of ", "b.begin()", "b.size()", "");
	analysis2.AddAnalyses(arrAnalyses, 1, false);
	RB_FAIL(rbIN_RANGES(a, 3, b.begin(), b.size(), IsSubsetOfMultiSingle), analysis2);
}

RB_TEST(Fail_IsSubsetOf_MultiSingle_2_0)
{
	int a[] = { 2, 1 };
	StubContainer b;

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true),
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(1), true)
	};

	TestableAnalysisOfRanges analysis1("", "a", "a+2", " is subset of ", "b.begin()", "b.end()", "");
	analysis1.AddAnalyses(arrAnalyses, 2);
	RB_FAIL(rbIN_RANGES(a, a+2, b.begin(), b.end(), IsSubsetOfMultiSingle), analysis1);

	b.rewind();
	TestableAnalysisOfRanges analysis2("", "a", "2", " is subset of ", "b.begin()", "b.size()", "");
	analysis2.AddAnalyses(arrAnalyses, 2, false);
	RB_FAIL(rbIN_RANGES(a, 2, b.begin(), b.size(), IsSubsetOfMultiSingle), analysis2);
}

RB_TEST(Fail_IsSubsetOf_MultiSingle_2_3_Full)
{
	int a[] = { 2, 1 };
	StubContainer b(1, 0);

	RichBool::Analysis *arrAnalyses[] = {
		RichBool::MakeGeneralAnalysis(true).idx(1, ":")("1", true)(" == ").idx(0, ":")("1", true),
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(0), true)
	};

	RichBool::IsSubsetOf<true, false> IsSubsetOfMultiSingleA(true);

	TestableAnalysisOfRanges analysis1("", "a", "a+2", " is subset of ", "b.begin()", "b.end()", "");
	analysis1.AddAnalyses(arrAnalyses, 2);
	RB_FAIL(rbIN_RANGES(a, a+2, b.begin(), b.end(), IsSubsetOfMultiSingleA), analysis1);

	b.rewind();
	TestableAnalysisOfRanges analysis2("", "a", "2", " is subset of ", "b.begin()", "b.size()", "");
	analysis2.AddAnalyses(arrAnalyses, 2, false);
	RB_FAIL(rbIN_RANGES(a, 2, b.begin(), b.size(), IsSubsetOfMultiSingleA), analysis2);
}


// tests for MatchesSubsetOf

static RichBool::Pred2<ProductIs12> productIs12;

RB_TEST(Succeed_MatchesSubsetOf_MultiMulti_1_2)
{
	int a[] = { 2, 3 };
	int b[] = { 4, 0, 6 };

	RB_PASS(rbIN_RANGES(a, a+2, b, b+3, RichBool::MatchesSubsetOf<>().That(productIs12)));
	RB_PASS(rbIN_RANGES(a, 2, b, 3, RichBool::MatchesSubsetOf<>().That(productIs12)));
}

RB_TEST(Succeed_MatchesSubsetOf_MultiMulti_1_2_Negate)
{
	int a[] = { 2, 3, 2 };
	int b[] = { 4, 0, 6 };

	RB_PASS(rbIN_RANGES(a, a+3, b, b+3, !RichBool::MatchesSubsetOf<>().That(productIs12)));
	RB_PASS(rbIN_RANGES(a, 3, b, 3, !RichBool::MatchesSubsetOf<>().That(productIs12)));
}



// with bad values

RB_TEST(Fail_MatchesSubsetOf_BadValue1)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 1, 4, 6 }, c[] = { 1, 4, 6 };
	int *b[] = { &a[0], 0, &a[2] };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, RichBool::PtrToString(&b[1])+" -> "+GetNullPtrString(),
			new RichBool::IndexExpression(1), false)
	};

	TestableAnalysisOfRanges analysis1(
		"", "b", "b+3", " matches with subset of ", "c", "c+3", "", RichBool::Analysis::BadValue);
	analysis1.AddAnalyses(arrAnalyses, 1);

	RichBool::Equal< RichBool::Pointer<> > p;
	RB_FAIL(rbIN_RANGES(b, b+3, c, c+3, RichBool::MatchesSubsetOf<>().That(p)), analysis1);
}

RB_TEST(Fail_MatchesSubsetOf_BadValue2)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 1, 4, 6 }, c[] = { 1, 4, 6 };
	int *b[] = { &c[0], 0, &c[2] };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(1, 2, RichBool::PtrToString(&b[1])+" -> "+GetNullPtrString(),
		new RichBool::IndexExpression(1), false)
	};

	TestableAnalysisOfRanges analysis1(
		"", "a", "a+3", " matches with subset of ", "b", "b+3", "", RichBool::Analysis::BadValue);
	analysis1.AddAnalyses(arrAnalyses, 1);

	RichBool::Equal< RichBool::Value, RichBool::Pointer<> > p;
	RB_FAIL(rbIN_RANGES(a, a+3, b, b+3, RichBool::MatchesSubsetOf<>().That(p)), analysis1);
}

RB_TEST(Fail_MatchesSubsetOf_SingleMulti_BadValue1)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 1, 4, 6 }, c[] = { 1, 4, 6 };
	int *b[] = { &a[0], 0, &a[2] };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, RichBool::PtrToString(&b[1])+" -> "+GetNullPtrString(),
		new RichBool::IndexExpression(1), false)
	};

	TestableAnalysisOfRanges analysis1(
		"", "b", "b+3", " matches with subset of ", "c", "c+3", "", RichBool::Analysis::BadValue);
	analysis1.AddAnalyses(arrAnalyses, 1);

	RichBool::Equal< RichBool::Pointer<> > p;
	RB_FAIL(rbIN_RANGES(b, b+3, c, c+3, RichBool::MatchesSubsetOf<false>().That(p)), analysis1);
}

RB_TEST(Fail_MatchesSubsetOf_SingleMulti_BadValue2)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 1, 4, 6 }, c[] = { 1, 4, 6 };
	int *b[] = { &c[0], 0, &c[2] };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(1, 2, RichBool::PtrToString(&b[1])+" -> "+GetNullPtrString(),
		new RichBool::IndexExpression(1), false)
	};

	TestableAnalysisOfRanges analysis1(
		"", "a", "a+3", " matches with subset of ", "b", "b+3", "", RichBool::Analysis::BadValue);
	analysis1.AddAnalyses(arrAnalyses, 1);

	RichBool::Equal< RichBool::Value, RichBool::Pointer<> > p;
	RB_FAIL(rbIN_RANGES(a, a+3, b, b+3, RichBool::MatchesSubsetOf<false>().That(p)), analysis1);
}

RB_TEST(Fail_MatchesSubsetOf_MultiSingle_BadValue1)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 1, 4, 6 }, c[] = { 1, 4, 6 };
	int *b[] = { &a[0], 0, &a[2] };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(0, 2, RichBool::PtrToString(&b[1])+" -> "+GetNullPtrString(),
		new RichBool::IndexExpression(1), false)
	};

	TestableAnalysisOfRanges analysis1(
		"", "b", "b+3", " matches with subset of ", "c", "c+3", "", RichBool::Analysis::BadValue);
	analysis1.AddAnalyses(arrAnalyses, 1);

	RichBool::Equal< RichBool::Pointer<> > p;
	RichBool::MatchesSubsetOf<true, false> mso;
	RB_FAIL(rbIN_RANGES(b, b+3, c, c+3, mso.That(p)), analysis1);
}

RB_TEST(Fail_MatchesSubsetOf_MultiSingle_BadValue2)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 1, 4, 6 }, c[] = { 1, 4, 6 };
	int *b[] = { &c[0], 0, &c[2] };

	RichBool::Analysis *arrAnalyses[] = {
		new RichBool::Single(1, 2, RichBool::PtrToString(&b[1])+" -> "+GetNullPtrString(),
		new RichBool::IndexExpression(1), false)
	};

	TestableAnalysisOfRanges analysis1(
		"", "a", "a+3", " matches with subset of ", "b", "b+3", "", RichBool::Analysis::BadValue);
	analysis1.AddAnalyses(arrAnalyses, 1);

	RichBool::Equal< RichBool::Value, RichBool::Pointer<> > p;
	RichBool::MatchesSubsetOf<true, false> mso;
	RB_FAIL(rbIN_RANGES(a, a+3, b, b+3, mso.That(p)), analysis1);
}
