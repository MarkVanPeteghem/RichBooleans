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

namespace RichBool
{
}

RB_TEST(AllPairs_Pass)
{
	int a[] = { 2, 2, 2 };

	// empty range:
	RB_PASS(rbIN_RANGE(a, a, AllPairs().Are(Equal<>())));
	RB_PASS(rbIN_RANGE(a, a, AllPairs(true).Are(Equal<>())));
	RB_PASS(rbIN_RANGE(a, 0, AllPairs().Are(Equal<>())));

	// one in range:
	RB_PASS(rbIN_RANGE(a, a+1, AllPairs().Are(Equal<>())));
	RB_PASS(rbIN_RANGE(a, a+1, AllPairs(true).Are(Equal<>())));
	RB_PASS(rbIN_RANGE(a, 1, AllPairs().Are(Equal<>())));

	// two in range:
	RB_PASS(rbIN_RANGE(a, a+2, AllPairs().Are(Equal<>())));
	RB_PASS(rbIN_RANGE(a, a+2, AllPairs(true).Are(Equal<>())));
	RB_PASS(rbIN_RANGE(a, 2, AllPairs().Are(Equal<>())));

	// full range
	RB_PASS(rbIN_RANGE(a, a+3, AllPairs().Are(Equal<>())));
	RB_PASS(rbIN_RANGE(a, a+3, AllPairs(true).Are(Equal<>())));
	RB_PASS(rbIN_RANGE(a, 3, AllPairs().Are(Equal<>())));
}

RB_TEST(AllPairs_Pass_Negated)
{
	int a[] = { 2, 3, 2 };

	// two in range:
	RB_PASS(rbIN_RANGE(a, a+2, !AllPairs().Are(Equal<>())));
	RB_PASS(rbIN_RANGE(a, a+2, !AllPairs(true).Are(Equal<>())));
	RB_PASS(rbIN_RANGE(a, 2, !AllPairs().Are(Equal<>())));

	// full range
	RB_PASS(rbIN_RANGE(a, a+3, !AllPairs().Are(Equal<>())));
	RB_PASS(rbIN_RANGE(a, a+3, !AllPairs(true).Are(Equal<>())));
	RB_PASS(rbIN_RANGE(a, 3, !AllPairs().Are(Equal<>())));
}

RB_TEST(AllPairs_Fail)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("2", true)(" == ").idx(2, ":")("8", true),
		MakeGeneralAnalysis(false).idx(1, ":")("2", true)(" == ").idx(2, ":")("8", true)
	};

	TestableAnalysisOfRange analysis1(
		"predicate applies to all pairs in ", "a", "a+3");
	analysis1.AddAnalyses(arrAnalyses, 2);

	TestableAnalysisOfRange analysis2(
		"predicate applies to all pairs in ", "a", "3");
	analysis2.AddAnalyses(arrAnalyses, 2, false);

	int a[] = { 2, 2, 8 };

	RB_FAIL(rbIN_RANGE(a, a+3, AllPairs().Are(Equal<>())), analysis1);
	RB_FAIL(rbIN_RANGE(a, 3, AllPairs().Are(Equal<>())), analysis2);
}

RB_TEST(AllPairs_Fail_Negated)
{
	TestableAnalysisOfRange analysis1(Analysis::Ok,
		"predicate applies to all pairs in ", "a", "a+3");
	analysis1.Negate();

	TestableAnalysisOfRange analysis2(Analysis::Ok,
		"predicate applies to all pairs in ", "a", "3");
	analysis2.Negate();

	int a[] = { 2, 2, 2 };

	RB_FAIL(rbIN_RANGE(a, a+3, !AllPairs().Are(Equal<>())), analysis1);
	RB_FAIL(rbIN_RANGE(a, 3, !AllPairs().Are(Equal<>())), analysis2);
}

RB_TEST(AllPairs_Fail_Negated_EmptyRange)
{
	TestableAnalysisOfRange analysis1(Analysis::Ok,
		"predicate applies to all pairs in ", "a", "a");
	analysis1.Negate();

	int a[] = { 0 };

	RB_FAIL(rbIN_RANGE(a, a, !AllPairs().Are(Equal<>())), analysis1);
}

RB_TEST(AllPairs_Fail_Full)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("2", true)(" == ").idx(1, ":")("2", true),
		MakeGeneralAnalysis(false).idx(0, ":")("2", true)(" == ").idx(2, ":")("8", true),
		MakeGeneralAnalysis(false).idx(1, ":")("2", true)(" == ").idx(2, ":")("8", true)
	};

	TestableAnalysisOfRange analysis1(
		"predicate applies to all pairs in ", "a", "a+3");
	analysis1.AddAnalyses(arrAnalyses, 3);

	TestableAnalysisOfRange analysis2(
		"predicate applies to all pairs in ", "a", "3");
	analysis2.AddAnalyses(arrAnalyses, 3, false);

	int a[] = { 2, 2, 8 };

	RB_FAIL(rbIN_RANGE(a, a+3, AllPairs(true).Are(Equal<>())), analysis1);
	RB_FAIL(rbIN_RANGE(a, 3, AllPairs(true).Are(Equal<>())), analysis2);
}

RB_TEST(AllPairs_Fail_Full_Negated)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("2", true)(" == ").idx(1, ":")("2", true),
		MakeGeneralAnalysis(true).idx(0, ":")("2", true)(" == ").idx(2, ":")("2", true),
		MakeGeneralAnalysis(true).idx(1, ":")("2", true)(" == ").idx(2, ":")("2", true)
	};

	TestableAnalysisOfRange analysis1(Analysis::Ok,
		"predicate applies to all pairs in ", "a", "a+3");
	analysis1.AddAnalyses(arrAnalyses, 3);
	analysis1.Negate();

	TestableAnalysisOfRange analysis2(Analysis::Ok,
		"predicate applies to all pairs in ", "a", "3");
	analysis2.AddAnalyses(arrAnalyses, 3, false);
	analysis2.Negate();

	int a[] = { 2, 2, 2 };

	RB_FAIL(rbIN_RANGE(a, a+3, !AllPairs(true).Are(Equal<>())), analysis1);
	RB_FAIL(rbIN_RANGE(a, 3, !AllPairs(true).Are(Equal<>())), analysis2);
}

RB_TEST(AllPairs_Pass_WithStubGetValue)
{
	int a[] = { 2, 2, 2 };

	Equal<StubGetValue> equal(StubGetValue(1));
	RB_PASS(rbIN_RANGE(a, a+3, AllPairs().Are(equal)));
}


// tests for AllUnique

RB_TEST(AllUnique_Pass)
{
	int a[] = { 1, 2, 3 };

	// empty range:
	RB_PASS(rbIN_RANGE(a, a, AllUnique<>()));
	RB_PASS(rbIN_RANGE(a, a, AllUnique<>(true)));
	RB_PASS(rbIN_RANGE(a, 0, AllUnique<>()));

	// one in range:
	RB_PASS(rbIN_RANGE(a, a+1, AllUnique<>()));
	RB_PASS(rbIN_RANGE(a, a+1, AllUnique<>(true)));
	RB_PASS(rbIN_RANGE(a, 1, AllUnique<>()));

	// two in range:
	RB_PASS(rbIN_RANGE(a, a+2, AllUnique<>()));
	RB_PASS(rbIN_RANGE(a, a+2, AllUnique<>(true)));
	RB_PASS(rbIN_RANGE(a, 2, AllUnique<>()));

	// full range
	RB_PASS(rbIN_RANGE(a, a+3, AllUnique<>()));
	RB_PASS(rbIN_RANGE(a, a+3, AllUnique<>(true)));
	RB_PASS(rbIN_RANGE(a, 3, AllUnique<>()));
}

RB_TEST(AllUnique_Fail)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("2", true)(" != ").idx(1, ":")("2", true)
	};

	TestableAnalysisOfRange analysis1(
		"all elements are unique in range ", "a", "a+3");
	analysis1.AddAnalyses(arrAnalyses, 1);

	TestableAnalysisOfRange analysis2(
		"all elements are unique in range ", "a", "3");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	int a[] = { 2, 2, 8 };

	RB_FAIL(rbIN_RANGE(a, a+3, AllUnique<>()), analysis1);
	RB_FAIL(rbIN_RANGE(a, 3, AllUnique<>()), analysis2);
}

RB_TEST(AllUnique_Fail_Full)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("2", true)(" != ").idx(1, ":")("2", true),
		MakeGeneralAnalysis(true).idx(0, ":")("2", true)(" != ").idx(2, ":")("8", true),
		MakeGeneralAnalysis(true).idx(1, ":")("2", true)(" != ").idx(2, ":")("8", true)
	};

	TestableAnalysisOfRange analysis1(
		"all elements are unique in range ", "a", "a+3");
	analysis1.AddAnalyses(arrAnalyses, 3);

	TestableAnalysisOfRange analysis2(
		"all elements are unique in range ", "a", "3");
	analysis2.AddAnalyses(arrAnalyses, 3, false);

	int a[] = { 2, 2, 8 };

	RB_FAIL(rbIN_RANGE(a, a+3, AllUnique<>(true)), analysis1);
	RB_FAIL(rbIN_RANGE(a, 3, AllUnique<>(true)), analysis2);
}


// with bad values

RB_TEST(AllUnique_BadValue)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int b=1;
	int *a[] = { 0, &b };

	Analysis *arrAnalyses[] = {
		new Single(0, 1, PtrToString(&a)+" -> "+GetNullPtrString(), new IndexExpression(0), false)
	};

	TestableAnalysisOfRange analysis1(
		"predicate applies to all pairs in ", "a", "a+2");
	analysis1.AddAnalyses(arrAnalyses, 1);

	Equal<Pointer<>, Pointer<> > eqp;
	RB_FAIL(rbIN_RANGE(a, a+2, AllPairs().Are(eqp)), analysis1);
}
