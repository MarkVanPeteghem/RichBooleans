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


// tests for Rich Booleans that check whether a range is sorted

RB_TEST(RangeSortedPassEmpty)
{
	int a[] = { 1 };

	RB_PASS(rbIN_RANGE(a, a, Sorted<>()));
	RB_PASS(rbIN_RANGE(a, a, Sorted<>(true)));

	RB_PASS(rbIN_RANGE(a, 0, Sorted<>()));
	RB_PASS(rbIN_RANGE(a, 0, Sorted<>(true)));
}

RB_TEST(RangeSortedPassOne)
{
	int a[] = { 1 };

	RB_PASS(rbIN_RANGE(a, a+1, Sorted<>()));
	RB_PASS(rbIN_RANGE(a, a+1, Sorted<>(true)));

	RB_PASS(rbIN_RANGE(a, 1, Sorted<>()));
	RB_PASS(rbIN_RANGE(a, 1, Sorted<>(true)));
}

RB_TEST(RangeSortedPassTwo)
{
	int a[] = { 1, 3 };

	RB_PASS(rbIN_RANGE(a, a+2, Sorted<>()));
	RB_PASS(rbIN_RANGE(a, a+2, Sorted<>(true)));

	RB_PASS(rbIN_RANGE(a, 2, Sorted<>()));
	RB_PASS(rbIN_RANGE(a, 2, Sorted<>(true)));
}

RB_TEST(RangeSortedPassTwo_Negate)
{
	int a[] = { 3, 1 };

	RB_PASS(rbIN_RANGE(a, a+2, !Sorted<>()));
	RB_PASS(rbIN_RANGE(a, a+2, !Sorted<>(true)));

	RB_PASS(rbIN_RANGE(a, 2, !Sorted<>()));
	RB_PASS(rbIN_RANGE(a, 2, !Sorted<>(true)));
}

RB_TEST(RangeSortedPassTwoEqual)
{
	int a[] = { 1, 1 };

	RB_PASS(rbIN_RANGE(a, a+2, Sorted<>()));
	RB_PASS(rbIN_RANGE(a, a+2, Sorted<>(true)));
}

RB_TEST(RangeSortedPassThree)
{
	int a[] = { 1, 2, 5 };

	RB_PASS(rbIN_RANGE(a, a+3, Sorted<>()));
	RB_PASS(rbIN_RANGE(a, a+3, Sorted<>(true)));
}

RB_TEST(RangeSortedPassThreeEqual)
{
	int a[] = { 1, 1, 1 };

	RB_PASS(rbIN_RANGE(a, a+3, Sorted<>()));
	RB_PASS(rbIN_RANGE(a, a+3, Sorted<>(true)));
}

RB_TEST(RangeSortedFailTwo)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("3", true)(" <= ")
			.idx(1, ":")("1", true)
	};

	TestableAnalysisOfRange analysis1("range is sorted: ", "a", "a+2");
	analysis1.AddAnalyses(arrAnalyses, 1);

	TestableAnalysisOfRange analysis2("range is sorted: ", "a", "2");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	int a[] = { 3, 1 };

	RB_FAIL(rbIN_RANGE(a, a+2, Sorted<>()), analysis1);
	RB_FAIL(rbIN_RANGE(a, 2, Sorted<>()), analysis2);
}

RB_TEST(RangeSortedFailThree_23)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(1, ":")("5", true)(" <= ")
			.idx(2, ":")("2", true)
	};
	TestableAnalysisOfRange analysis("range is sorted: ", "a", "a+3");
	analysis.AddAnalyses(arrAnalyses, 1);

	int a[] = { 1, 5, 2 };

	RB_FAIL(rbIN_RANGE(a, a+3, Sorted<>()), analysis);
}

RB_TEST(RangeSortedFailThree_23_Negate)
{
	TestableAnalysisOfRange analysis(Analysis::Ok, "range is sorted: ", "a", "a+3");
	analysis.Negate();

	int a[] = { 1, 2, 5 };

	RB_FAIL(rbIN_RANGE(a, a+3, !Sorted<>()), analysis);
}

RB_TEST(RangeSortedFail_Empty_Negate)
{
	TestableAnalysisOfRange analysis(Analysis::Ok, "range is sorted: ", "a", "a");
	analysis.Negate();

	int a[] = { 0 };

	RB_FAIL(rbIN_RANGE(a, a, !Sorted<>()), analysis);
}

RB_TEST(RangeSortedFail_One_Negate)
{
	TestableAnalysisOfRange analysis(Analysis::Ok, "range is sorted: ", "a", "a+1");
	analysis.Negate();

	int a[] = { 0 };

	RB_FAIL(rbIN_RANGE(a, a+1, !Sorted<>()), analysis);
}

RB_TEST(RangeSortedFailThree_23_Full)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" <= ")
			.idx(1, ":")("5", true),
		MakeGeneralAnalysis(false).idx(1, ":")("5", true)(" <= ")
			.idx(2, ":")("2", true)
	};
	TestableAnalysisOfRange analysis("range is sorted: ", "a", "a+3");
	analysis.AddAnalyses(arrAnalyses, 2);

	int a[] = { 1, 5, 2 };

	RB_FAIL(rbIN_RANGE(a, a+3, Sorted<>(true)), analysis);
}

RB_TEST(RangeSortedFailThree_12)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("2", true)(" <= ")
			.idx(1, ":")("1", true)
	};
	TestableAnalysisOfRange analysis("range is sorted: ", "a", "a+3");
	analysis.AddAnalyses(arrAnalyses, 1);

	int a[] = { 2, 1, 5 };

	RB_FAIL(rbIN_RANGE(a, a+3, Sorted<>()), analysis);
}

RB_TEST(RangeSortedFailThree_12_Full)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("2", true)(" <= ")
			.idx(1, ":")("1", true),
		MakeGeneralAnalysis(true).idx(1, ":")("1", true)(" <= ")
			.idx(2, ":")("5", true)
	};
	TestableAnalysisOfRange analysis("range is sorted: ", "a", "a+3");
	analysis.AddAnalyses(arrAnalyses, 2);

	int a[] = { 2, 1, 5 };

	RB_FAIL(rbIN_RANGE(a, a+3, Sorted<>(true)), analysis);
}

RB_TEST(RangeSortedFailThree_12_Full_Negate)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" <= ")
			.idx(1, ":")("2", true),
		MakeGeneralAnalysis(true).idx(1, ":")("2", true)(" <= ")
			.idx(2, ":")("5", true)
	};
	TestableAnalysisOfRange analysis(Analysis::Ok, "range is sorted: ", "a", "a+3");
	analysis.AddAnalyses(arrAnalyses, 2);
	analysis.Negate();

	int a[] = { 1, 2, 5 };

	RB_FAIL(rbIN_RANGE(a, a+3, !Sorted<>(true)), analysis);
}

RB_TEST(RangeSortedStrictlyPassEmpty)
{
	int a[] = { 1 };

	RB_PASS(rbIN_RANGE(a, a, SortedStrictly<>()));
	RB_PASS(rbIN_RANGE(a, a, SortedStrictly<>(true)));

	RB_PASS(rbIN_RANGE(a, 0, SortedStrictly<>()));
	RB_PASS(rbIN_RANGE(a, 0, SortedStrictly<>(true)));
}

RB_TEST(RangeSortedStrictlyPassOne)
{
	int a[] = { 1 };

	RB_PASS(rbIN_RANGE(a, a+1, SortedStrictly<>()));
	RB_PASS(rbIN_RANGE(a, a+1, SortedStrictly<>(true)));

	RB_PASS(rbIN_RANGE(a, 1, SortedStrictly<>()));
	RB_PASS(rbIN_RANGE(a, 1, SortedStrictly<>(true)));
}

RB_TEST(RangeSortedStrictlyPassTwo)
{
	int a[] = { 1, 3 };

	RB_PASS(rbIN_RANGE(a, a+2, SortedStrictly<>()));
	RB_PASS(rbIN_RANGE(a, a+2, SortedStrictly<>(true)));

	RB_PASS(rbIN_RANGE(a, 2, SortedStrictly<>()));
	RB_PASS(rbIN_RANGE(a, 2, SortedStrictly<>(true)));
}

RB_TEST(RangeSortedStrictlyPassTwo_Negate)
{
	int a[] = { 3, 1 };

	RB_PASS(rbIN_RANGE(a, a+2, !SortedStrictly<>()));
	RB_PASS(rbIN_RANGE(a, a+2, !SortedStrictly<>(true)));

	RB_PASS(rbIN_RANGE(a, 2, !SortedStrictly<>()));
	RB_PASS(rbIN_RANGE(a, 2, !SortedStrictly<>(true)));
}

RB_TEST(RangeSortedStrictlyPassTwoEqual_Negate)
{
	int a[] = { 1, 1 };

	RB_PASS(rbIN_RANGE(a, a+2, !SortedStrictly<>()));
	RB_PASS(rbIN_RANGE(a, a+2, !SortedStrictly<>(true)));

	RB_PASS(rbIN_RANGE(a, 2, !SortedStrictly<>()));
	RB_PASS(rbIN_RANGE(a, 2, !SortedStrictly<>(true)));
}

RB_TEST(RangeSortedStrictlyPassThree)
{
	int a[] = { 1, 2, 5 };

	RB_PASS(rbIN_RANGE(a, a+3, SortedStrictly<>()));
	RB_PASS(rbIN_RANGE(a, a+3, SortedStrictly<>(true)));
}

RB_TEST(RangeSortedStrictlyFailTwo)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("3", true)(" < ")
			.idx(1, ":")("1", true)
	};

	TestableAnalysisOfRange analysis1("range is sorted strictly: ", "a", "a+2");
	analysis1.AddAnalyses(arrAnalyses, 1);

	TestableAnalysisOfRange analysis2("range is sorted strictly: ", "a", "2");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	int a[] = { 3, 1 };

	RB_FAIL(rbIN_RANGE(a, a+2, SortedStrictly<>()), analysis1);
	RB_FAIL(rbIN_RANGE(a, 2, SortedStrictly<>()), analysis2);
}

RB_TEST(RangeSortedStrictlyFailTwo_Negate)
{
	TestableAnalysisOfRange analysis1(Analysis::Ok, "range is sorted strictly: ", "a", "a+2");
	analysis1.Negate();

	TestableAnalysisOfRange analysis2(Analysis::Ok, "range is sorted strictly: ", "a", "2");
	analysis2.Negate();

	int a[] = { 1, 3 };

	RB_FAIL(rbIN_RANGE(a, a+2, !SortedStrictly<>()), analysis1);
	RB_FAIL(rbIN_RANGE(a, 2, !SortedStrictly<>()), analysis2);
}

RB_TEST(RangeSortedStrictlyFailNone_Negate)
{
	TestableAnalysisOfRange analysis1(Analysis::Ok, "range is sorted strictly: ", "a", "a");
	analysis1.Negate();

	TestableAnalysisOfRange analysis2(Analysis::Ok, "range is sorted strictly: ", "a", "0");
	analysis2.Negate();

	int a[] = { 0 };

	RB_FAIL(rbIN_RANGE(a, a, !SortedStrictly<>()), analysis1);
	RB_FAIL(rbIN_RANGE(a, 0, !SortedStrictly<>()), analysis2);
}

RB_TEST(RangeSortedStrictlyFailTwoEqual)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("1", true)(" < ")
			.idx(1, ":")("1", true)
	};
	TestableAnalysisOfRange analysis("range is sorted strictly: ", "a", "a+2");
	analysis.AddAnalyses(arrAnalyses, 1);

	int a[] = { 1, 1 };

	RB_FAIL(rbIN_RANGE(a, a+2, SortedStrictly<>()), analysis);
}

RB_TEST(RangeSortedStrictlyFailThree_23)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(1, ":")("5", true)(" < ")
			.idx(2, ":")("2", true)
	};
	TestableAnalysisOfRange analysis("range is sorted strictly: ", "a", "a+3");
	analysis.AddAnalyses(arrAnalyses, 1);

	int a[] = { 1, 5, 2 };

	RB_FAIL(rbIN_RANGE(a, a+3, SortedStrictly<>()), analysis);
}

RB_TEST(RangeSortedStrictlyFailThree_23_Full)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" < ")
			.idx(1, ":")("5", true),
		MakeGeneralAnalysis(false).idx(1, ":")("5", true)(" < ")
			.idx(2, ":")("2", true)
	};
	TestableAnalysisOfRange analysis("range is sorted strictly: ", "a", "a+3");
	analysis.AddAnalyses(arrAnalyses, 2);

	int a[] = { 1, 5, 2 };

	RB_FAIL(rbIN_RANGE(a, a+3, SortedStrictly<>(true)), analysis);
}

RB_TEST(RangeSortedStrictlyFailThree_12)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("2", true)(" < ")
			.idx(1, ":")("1", true)
	};
	TestableAnalysisOfRange analysis("range is sorted strictly: ", "a", "a+3");
	analysis.AddAnalyses(arrAnalyses, 1);

	int a[] = { 2, 1, 5 };

	RB_FAIL(rbIN_RANGE(a, a+3, SortedStrictly<>()), analysis);
}

RB_TEST(RangeSortedStrictlyFailThree_12_Full)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("2", true)(" < ")
			.idx(1, ":")("1", true),
		MakeGeneralAnalysis(true).idx(1, ":")("1", true)(" < ")
			.idx(2, ":")("5", true)
	};
	TestableAnalysisOfRange analysis("range is sorted strictly: ", "a", "a+3");
	analysis.AddAnalyses(arrAnalyses, 2);

	int a[] = { 2, 1, 5 };

	RB_FAIL(rbIN_RANGE(a, a+3, SortedStrictly<>(true)), analysis);
}

RB_TEST(RangeSortedStrictlyFailThreeEqual)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("1", true)(" < ")
			.idx(1, ":")("1", true),
		MakeGeneralAnalysis(false).idx(1, ":")("1", true)(" < ")
			.idx(2, ":")("1", true)
	};
	TestableAnalysisOfRange analysis("range is sorted strictly: ", "a", "a+3");
	analysis.AddAnalyses(arrAnalyses, 2);

	int a[] = { 1, 1, 1 };

	RB_FAIL(rbIN_RANGE(a, a+3, SortedStrictly<>()), analysis);
}

// sorted with input iterator
RB_TEST(RangeSortedPassEmpty_InputIterator)
{
	StubContainer stub;

	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), Sorted<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), Sorted<false>(true)));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), SortedStrictly<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), SortedStrictly<false>(true)));

	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 0, Sorted<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 0, Sorted<false>(true)));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 0, SortedStrictly<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 0, SortedStrictly<false>(true)));
}

RB_TEST(RangeSortedPassOne_InputIterator)
{
	StubContainer stub(1);

	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), Sorted<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), Sorted<false>(true)));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), SortedStrictly<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), SortedStrictly<false>(true)));

	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 1, Sorted<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 1, Sorted<false>(true)));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 1, SortedStrictly<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 1, SortedStrictly<false>(true)));
}

RB_TEST(RangeSortedPassThree_InputIterator)
{
	StubContainer stub(1,3,5);

	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), Sorted<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), Sorted<false>(true)));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), SortedStrictly<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), SortedStrictly<false>(true)));

	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 3, Sorted<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 3, Sorted<false>(true)));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 3, SortedStrictly<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 3, SortedStrictly<false>(true)));
}

RB_TEST(RangeSortedPassThree_InputIterator_Negate)
{
	StubContainer stub(1,5,3);

	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), !Sorted<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), !Sorted<false>(true)));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), !SortedStrictly<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), !SortedStrictly<false>(true)));

	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 3, !Sorted<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 3, !Sorted<false>(true)));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 3, !SortedStrictly<false>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 3, !SortedStrictly<false>(true)));
}

RB_TEST(RangeSortedFailTwo_InputIterator)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("3", true)(" <= ")
			.idx(1, ":")("1", true)
	};

	TestableAnalysisOfRange analysis1("range is sorted: ", "stub.begin()", "stub.end()");
	analysis1.AddAnalyses(arrAnalyses, 1);

	TestableAnalysisOfRange analysis2("range is sorted: ", "stub.begin()", "2");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	StubContainer stub(3, 1);

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), Sorted<false>()), analysis1);
	stub.rewind();
	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), Sorted<false>(true)), analysis1);
	stub.rewind();
	RB_FAIL(rbIN_RANGE(stub.begin(), 2, Sorted<false>()), analysis2);
	stub.rewind();
	RB_FAIL(rbIN_RANGE(stub.begin(), 2, Sorted<false>(true)), analysis2);
}

RB_TEST(RangeSortedFailTwo_InputIterator_Negate)
{
	TestableAnalysisOfRange analysis1(Analysis::Ok, "range is sorted: ", "stub.begin()", "stub.end()");
	analysis1.Negate();

	TestableAnalysisOfRange analysis2(Analysis::Ok, "range is sorted: ", "stub.begin()", "2");
	analysis2.Negate();

	StubContainer stub(1,3);

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), !Sorted<false>()), analysis1);
	stub.rewind();
	RB_FAIL(rbIN_RANGE(stub.begin(), 2, !Sorted<false>()), analysis2);
}

RB_TEST(RangeSortedFailThree_12_InputIterator)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("2", true)(" <= ")
			.idx(1, ":")("1", true)
	};
	TestableAnalysisOfRange analysis("range is sorted: ", "stub.begin()", "stub.end()");
	analysis.AddAnalyses(arrAnalyses, 1);

	StubContainer stub(2, 1, 5);

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), Sorted<false>()), analysis);
}

RB_TEST(RangeSortedFailThree_12_Full_InputIterator)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("2", true)(" <= ")
			.idx(1, ":")("1", true),
		MakeGeneralAnalysis(true).idx(1, ":")("1", true)(" <= ")
			.idx(2, ":")("5", true)
	};
	TestableAnalysisOfRange analysis("range is sorted: ", "stub.begin()", "stub.end()");
	analysis.AddAnalyses(arrAnalyses, 2);

	StubContainer stub(2, 1, 5);

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), Sorted<false>(true)), analysis);
}

RB_TEST(RangeSortedStrictlyFailThree_12_InputIterator)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("2", true)(" < ")
			.idx(1, ":")("1", true)
	};
	TestableAnalysisOfRange analysis("range is sorted strictly: ", "stub.begin()", "stub.end()");
	analysis.AddAnalyses(arrAnalyses, 1);

	StubContainer stub(2, 1, 5);

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), SortedStrictly<false>()), analysis);
}

RB_TEST(RangeSortedStrictlyFailThree_12_Full_InputIterator)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("2", true)(" < ")
			.idx(1, ":")("1", true),
		MakeGeneralAnalysis(true).idx(1, ":")("1", true)(" < ")
			.idx(2, ":")("5", true)
	};
	TestableAnalysisOfRange analysis("range is sorted strictly: ", "stub.begin()", "stub.end()");
	analysis.AddAnalyses(arrAnalyses, 2);

	StubContainer stub(2, 1, 5);

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), SortedStrictly<false>(true)), analysis);
}

RB_TEST(RangeSortedStrictlyFailThree_12_Full_InputIterator_Negate)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" < ")
			.idx(1, ":")("2", true),
		MakeGeneralAnalysis(true).idx(1, ":")("2", true)(" < ")
			.idx(2, ":")("5", true)
	};
	TestableAnalysisOfRange analysis(Analysis::Ok,
		"range is sorted strictly: ", "stub.begin()", "stub.end()");
	analysis.AddAnalyses(arrAnalyses, 2);
	analysis.Negate();

	StubContainer stub(1, 2, 5);

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), !SortedStrictly<false>(true)), analysis);
}


// tests for Adjacent

RB_TEST(RangeSortedPredPassEmpty)
{
	int a[] = { 1 };

	RB_PASS(rbIN_RANGE(a, a, Adjacent<>().Are(Pred2<PredMore>())));
	RB_PASS(rbIN_RANGE(a, a, Adjacent<>(true).Are(Pred2<PredMore>())));

	RB_PASS(rbIN_RANGE(a, 0, Adjacent<>().Are(Pred2<PredMore>())));
	RB_PASS(rbIN_RANGE(a, 0, Adjacent<>(true).Are(Pred2<PredMore>())));
}

RB_TEST(RangeSortedPredPassOne)
{
	int a[] = { 1 };

	RB_PASS(rbIN_RANGE(a, a+1, Adjacent<>().Are(Pred2<PredMore>())));
	RB_PASS(rbIN_RANGE(a, a+1, Adjacent<>(true).Are(Pred2<PredMore>())));

	RB_PASS(rbIN_RANGE(a, 1, Adjacent<>().Are(Pred2<PredMore>())));
	RB_PASS(rbIN_RANGE(a, 1, Adjacent<>(true).Are(Pred2<PredMore>())));
}

RB_TEST(RangeSortedPredPassTwo)
{
	int a[] = { 3, 1 };

	RB_PASS(rbIN_RANGE(a, a+2, Adjacent<>().Are(Pred2<PredMore>())));
	RB_PASS(rbIN_RANGE(a, a+2, Adjacent<>(true).Are(Pred2<PredMore>())));

	RB_PASS(rbIN_RANGE(a, 2, Adjacent<>().Are(Pred2<PredMore>())));
	RB_PASS(rbIN_RANGE(a, 2, Adjacent<>(true).Are(Pred2<PredMore>())));
}

RB_TEST(RangeSortedPredPassThree)
{
	int a[] = { 5, 2, 1 };

	RB_PASS(rbIN_RANGE(a, a+3, Adjacent<>().Are(Pred2<PredMore>())));
	RB_PASS(rbIN_RANGE(a, a+3, Adjacent<>(true).Are(Pred2<PredMore>())));
}

RB_TEST(RangeSortedPredFailTwo)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(0, ":")("1", true)(", ")
			.idx(1, ":")("3", true)(")")
	};

	TestableAnalysisOfRange analysis1(
		"predicate applies to adjacent elements in range ", "a", "a+2");
	analysis1.AddAnalyses(arrAnalyses, 1);

	TestableAnalysisOfRange analysis2(
		"predicate applies to adjacent elements in range ", "a", "2");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	int a[] = { 1, 3 };

	RB_FAIL(rbIN_RANGE(a, a+2, Adjacent<>().Are(Pred2<PredMore>())), analysis1);
	RB_FAIL(rbIN_RANGE(a, 2, Adjacent<>().Are(Pred2<PredMore>())), analysis2);
}

RB_TEST(RangeSortedPredFailThree_23)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(0, ":")("1", true)(", ")
			.idx(1, ":")("5", true)(")")
	};
	TestableAnalysisOfRange analysis(
		"predicate applies to adjacent elements in range ", "a", "a+3");
	analysis.AddAnalyses(arrAnalyses, 1);

	int a[] = { 1, 5, 2 };

	RB_FAIL(rbIN_RANGE(a, a+3, Adjacent<>().Are(Pred2<PredMore>())), analysis);
}

RB_TEST(RangeSortedPredFailThree_23_Full)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(0, ":")("1", true)(", ")
			.idx(1, ":")("5", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(1, ":")("5", true)(", ")
			.idx(2, ":")("2", true)(")")
	};
	TestableAnalysisOfRange analysis(
		"predicate applies to adjacent elements in range ", "a", "a+3");
	analysis.AddAnalyses(arrAnalyses, 2);

	int a[] = { 1, 5, 2 };

	RB_FAIL(rbIN_RANGE(a, a+3, Adjacent<>(true).Are(Pred2<PredMore>())), analysis);
}

RB_TEST(RangeSortedPredPassThree_InputIterator)
{
	StubContainer stub(5,3,1);

	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), Adjacent<false>().Are(Pred2<PredMore>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), Adjacent<false>(true).Are(Pred2<PredMore>())));

	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 3, Adjacent<false>().Are(Pred2<PredMore>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 3, Adjacent<false>(true).Are(Pred2<PredMore>())));
}

RB_TEST(RangeSortedPredFailThree_12_InputIterator)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("1", true)(", ")
			.idx(2, ":")("5", true)(")")
	};

	TestableAnalysisOfRange analysis1(
		"predicate applies to adjacent elements in range ", "stub.begin()", "stub.end()");
	analysis1.AddAnalyses(arrAnalyses, 1);

	TestableAnalysisOfRange analysis2(
		"predicate applies to adjacent elements in range ", "stub.begin()", "3");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	StubContainer stub(2, 1, 5);

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), Adjacent<false>().Are(Pred2<PredMore>())), analysis1);
	stub.rewind();
	RB_FAIL(rbIN_RANGE(stub.begin(), 3, Adjacent<false>().Are(Pred2<PredMore>())), analysis2);
}

RB_TEST(RangeSortedPredFailThree_12_Full_InputIterator)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("2", true)(", ")
			.idx(1, ":")("1", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("1", true)(", ")
			.idx(2, ":")("5", true)(")")
	};

	TestableAnalysisOfRange analysis1(
		"predicate applies to adjacent elements in range ", "stub.begin()", "stub.end()");
	analysis1.AddAnalyses(arrAnalyses, 2);

	TestableAnalysisOfRange analysis2(
		"predicate applies to adjacent elements in range ", "stub.begin()", "3");
	analysis2.AddAnalyses(arrAnalyses, 2, false);

	StubContainer stub(2, 1, 5);

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), Adjacent<false>(true).Are(Pred2<PredMore>())), analysis1);
	stub.rewind();
	RB_FAIL(rbIN_RANGE(stub.begin(), 3, Adjacent<false>(true).Are(Pred2<PredMore>())), analysis2);
}



// same tests with deprecated functionality:

RB_TEST(RangeSortedPredPassEmpty_Old)
{
	int a[] = { 1 };

	RB_PASS(rbIN_RANGE_ARG(a, a, Adjacent<>(), Pred2<PredMore>()));
	RB_PASS(rbIN_RANGE_ARG(a, a, Adjacent<>(true), Pred2<PredMore>()));
}

RB_TEST(RangeSortedPredPassOne_Old)
{
	int a[] = { 1 };

	RB_PASS(rbIN_RANGE_ARG(a, a+1, Adjacent<>(), Pred2<PredMore>()));
	RB_PASS(rbIN_RANGE_ARG(a, a+1, Adjacent<>(true), Pred2<PredMore>()));
}

RB_TEST(RangeSortedPredPassTwo_Old)
{
	int a[] = { 3, 1 };

	RB_PASS(rbIN_RANGE_ARG(a, a+2, Adjacent<>(), Pred2<PredMore>()));
	RB_PASS(rbIN_RANGE_ARG(a, a+2, Adjacent<>(true), Pred2<PredMore>()));
}

RB_TEST(RangeSortedPredPassThree_Old)
{
	int a[] = { 5, 2, 1 };

	RB_PASS(rbIN_RANGE_ARG(a, a+3, Adjacent<>(), Pred2<PredMore>()));
	RB_PASS(rbIN_RANGE_ARG(a, a+3, Adjacent<>(true), Pred2<PredMore>()));
}

RB_TEST(RangeSortedPredFailTwo_Old)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(0, ":")("1", true)(", ")
			.idx(1, ":")("3", true)(")")
	};
	TestableAnalysisOfRange analysis(
		"predicate applies to adjacent elements in range ", "a", "a+2");
	analysis.AddAnalyses(arrAnalyses, 1);

	int a[] = { 1, 3 };

	RB_FAIL(rbIN_RANGE_ARG(a, a+2, Adjacent<>(), Pred2<PredMore>()), analysis);
}

RB_TEST(RangeSortedPredFailThree_23_Old)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(0, ":")("1", true)(", ")
			.idx(1, ":")("5", true)(")")
	};
	TestableAnalysisOfRange analysis(
		"predicate applies to adjacent elements in range ", "a", "a+3");
	analysis.AddAnalyses(arrAnalyses, 1);

	int a[] = { 1, 5, 2 };

	RB_FAIL(rbIN_RANGE_ARG(a, a+3, Adjacent<>(), Pred2<PredMore>()), analysis);
}

RB_TEST(RangeSortedPredFailThree_23_Full_Old)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(0, ":")("1", true)(", ")
			.idx(1, ":")("5", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(1, ":")("5", true)(", ")
			.idx(2, ":")("2", true)(")")
	};
	TestableAnalysisOfRange analysis(
		"predicate applies to adjacent elements in range ", "a", "a+3");
	analysis.AddAnalyses(arrAnalyses, 2);

	int a[] = { 1, 5, 2 };

	RB_FAIL(rbIN_RANGE_ARG(a, a+3, Adjacent<>(true), Pred2<PredMore>()), analysis);
}

RB_TEST(RangeSorted_Pass_WithStubGetValue)
{
	int a[] = { 2, 8, 10 };

	Less<StubGetValue, StubGetValue> less(StubGetValue(1), StubGetValue(2));
	RB_PASS(rbIN_RANGE(a, a+3, Adjacent<>().Are(less)));
	RB_PASS(rbIN_RANGE(a, a+3, Adjacent<false>().Are(less)));
}


// with invalid pointers

static LessOrEqual<Pointer<>, Pointer<> > lepp;

RB_TEST(Fail_Sorted_BadValue)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 2, 5, 8, 10 };
	int *b[] = { &a[0], 0, &a[2], &a[3] };

	SharedExpression se0=new PrefixedExpression("*", MakeExpression((size_t)0)),
		se1=new PrefixedExpression("*", MakeExpression(1)),
		se2=new PrefixedExpression("*", MakeExpression(2));
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(Analysis::BadValue)
			.expr(se0, ":")(b[0], Pointer<>(), MakeString())
			(" <= ")
			.expr(se1, ":")(b[1], Pointer<>(), MakeString()),
		MakeGeneralAnalysis(Analysis::BadValue)
			.expr(se1, ":")(b[1], Pointer<>(), MakeString())
			(" <= ")
			.expr(se2, ":")(b[2], Pointer<>(), MakeString())
	};

	TestableAnalysisOfRange analysis1(Analysis::BadValue,
		"predicate applies to adjacent elements in range ", "b", "b+4");
	analysis1.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGE(b, b+4, Adjacent<>().Are(lepp)), analysis1);
}

RB_TEST(Fail_Sorted_BadValue2)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 1, 5, 8, 6 };
	int *b[] = { &a[0], 0, &a[2], &a[3] };

	SharedExpression se0=new PrefixedExpression("*", MakeExpression((size_t)0)),
		se1=new PrefixedExpression("*", MakeExpression(1)),
		se2=new PrefixedExpression("*", MakeExpression(2)),
		se3=new PrefixedExpression("*", MakeExpression(3));
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(Analysis::BadValue)
			.expr(se0, ":")(b[0], Pointer<>(), MakeString())
			(" <= ")
			.expr(se1, ":")(b[1], Pointer<>(), MakeString()),
		MakeGeneralAnalysis(Analysis::BadValue)
			.expr(se1, ":")(b[1], Pointer<>(), MakeString())
			(" <= ")
			.expr(se2, ":")(b[2], Pointer<>(), MakeString()),
		MakeGeneralAnalysis(Analysis::NotOk)
			.expr(se2, ":")(b[2], Pointer<>(), MakeString())
			(" <= ")
			.expr(se3, ":")(b[3], Pointer<>(), MakeString())
	};

	TestableAnalysisOfRange analysis1(Analysis::BadValue,
		"predicate applies to adjacent elements in range ", "b", "b+4");
	analysis1.AddAnalyses(arrAnalyses, 3);

	RB_FAIL(rbIN_RANGE(b, b+4, Adjacent<>().Are(lepp)), analysis1);
}

RB_TEST(Fail_Sorted_BadValue_ShowAll)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 1, 5, 8, 10 };
	int *b[] = { &a[0], 0, &a[2], &a[3] };

	SharedExpression se0=new PrefixedExpression("*", MakeExpression((size_t)0)),
		se1=new PrefixedExpression("*", MakeExpression(1)),
		se2=new PrefixedExpression("*", MakeExpression(2)),
		se3=new PrefixedExpression("*", MakeExpression(3));
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(Analysis::BadValue)
			.expr(se0, ":")(b[0], Pointer<>(), MakeString())
			(" <= ")
			.expr(se1, ":")(b[1], Pointer<>(), MakeString()),
		MakeGeneralAnalysis(Analysis::BadValue)
			.expr(se1, ":")(b[1], Pointer<>(), MakeString())
			(" <= ")
			.expr(se2, ":")(b[2], Pointer<>(), MakeString()),
		MakeGeneralAnalysis(Analysis::Ok)
			.expr(se2, ":")(b[2], Pointer<>(), MakeString())
			(" <= ")
			.expr(se3, ":")(b[3], Pointer<>(), MakeString())
	};

	TestableAnalysisOfRange analysis1(Analysis::BadValue,
		"predicate applies to adjacent elements in range ", "b", "b+4");
	analysis1.AddAnalyses(arrAnalyses, 3);

	RB_FAIL(rbIN_RANGE(b, b+4, Adjacent<>(true).Are(lepp)), analysis1);
}

RB_TEST(Fail_Sorted_BadValue_Single)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 2, 5, 8, 10 };
	int *b[] = { &a[0], 0, &a[2], &a[3] };

	SharedExpression se0=new PrefixedExpression("*", MakeExpression((size_t)0)),
		se1=new PrefixedExpression("*", MakeExpression(1)),
		se2=new PrefixedExpression("*", MakeExpression(2));
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(Analysis::BadValue)
			.expr(se0, ":")(b[0], Pointer<>(), MakeString())
			(" <= ")
			.expr(se1, ":")(b[1], Pointer<>(), MakeString())
	};

	TestableAnalysisOfRange analysis1(Analysis::BadValue,
		"predicate applies to adjacent elements in range ", "b", "b+4");
	analysis1.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGE(b, b+4, Adjacent<false>().Are(lepp)), analysis1);
}

RB_TEST(Fail_Sorted_BadValue_Single_ShowAll)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 1, 5, 8, 10 };
	int *b[] = { &a[0], 0, &a[2], &a[3] };

	SharedExpression se0=new PrefixedExpression("*", MakeExpression((size_t)0)),
		se1=new PrefixedExpression("*", MakeExpression(1)),
		se2=new PrefixedExpression("*", MakeExpression(2)),
		se3=new PrefixedExpression("*", MakeExpression(3));
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(Analysis::BadValue)
			.expr(se0, ":")(b[0], Pointer<>(), MakeString())
			(" <= ")
			.expr(se1, ":")(b[1], Pointer<>(), MakeString()),
		MakeGeneralAnalysis(Analysis::Ok)
			.expr(se2, ":")(b[2], Pointer<>(), MakeString())
			(" <= ")
			.expr(se3, ":")(b[3], Pointer<>(), MakeString())
	};

	TestableAnalysisOfRange analysis1(Analysis::BadValue,
		"predicate applies to adjacent elements in range ", "b", "b+4");
	analysis1.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGE(b, b+4, Adjacent<false>(true).Are(lepp)), analysis1);
}
