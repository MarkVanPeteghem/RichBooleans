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
#include <vector>

using namespace RichBool;

// tests for Rich Booleans that perform checks on an array

RB_TEST(InArray)
{
	int a[] = { 2, 3, 4 };

	RB_PASS(rbIN_ARRAY(a, Sorted<>()));
	RB_PASS_V(rbvIN_ARRAY(a, Sorted<>()), a);
}

RB_TEST(InArrayFail)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("3", true)(" <= ")
			.idx(1, ":")("1", true)
	};
	TestableAnalysisOfRange analysis("range is sorted: ", "a", "RICHBOOL_ARRAY_COUNT(a)");
	analysis.AddAnalyses(arrAnalyses, 1);

	int a[] = { 3, 1 };

	RB_FAIL(rbIN_ARRAY(a, Sorted<>()), analysis);
	RB_FAIL_V(rbvIN_ARRAY(a, Sorted<>()), analysis, a);
}

RB_TEST(InArrays)
{
	int a[] = { 2, 3, 4 }, b[] = { 2, 3, 4};

	RB_PASS(rbIN_ARRAYS(a, b, AllEqual<>()));
	RB_PASS_V(rbvIN_ARRAYS(a, b, AllEqual<>()), a);
}

RB_TEST(InArraysFail)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ").idx(0, ":")("1", true),
		MakeGeneralAnalysis(true).idx(1, ":")("2", true)(" == ").idx(1, ":")("2", true),
		new Single(0, 2, "3", new IndexExpression(2), true)
	};

	TestableAnalysisOfContainers analysis("ranges are equal: ", "a", "b");
	analysis.AddAnalyses(arrAnalyses, 3);

	int a[] = { 1, 2, 3 }, b[] = { 1, 2 };
	RB_FAIL(rbIN_ARRAYS(a, b, AllEqual<>(true)), analysis);
	RB_FAIL_V(rbvIN_ARRAYS(a, b, AllEqual<>(true)), analysis, a);
}
