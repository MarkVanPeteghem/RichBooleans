//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include "rbtest.hpp"
#include "richbool/richbool.hpp"
#include "richbool/std.hpp"
#include "testable_analysis_for_ranges.hpp"
#include "predicates.hpp"

#ifdef RICHBOOL_INITIALIZER_LISTS

#include <vector>

using namespace RichBool;

RB_TEST(InValues_Pass)
{
	RB_PASS(rbIN_VALUES(({ 2, 4, 6 }), All<>().Are(Pred1<IsEven>())));
	RB_PASS_IV(rbvIN_VALUES(({ 2, 4, 6 }), All<>().Are(Pred1<IsEven>())));
}

RB_TEST(InValues_Fail)
{
	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("2", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("5", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(2, ":")("8", true)(")")
	};
	TestableAnalysisOfRange analysis(
		"predicate applies to all elements in range ",
		"({ 2, 5, 8 })");
	analysis.AddAnalyses(arrAnalysis, 3);
	RB_FAIL(rbIN_VALUES(({ 2, 5, 8 }), All<>(true).Are(Pred1<IsEven>())), analysis);
	RB_FAIL_IV(rbvIN_VALUES(({ 2, 5, 8 }), All<>(true).Are(Pred1<IsEven>())), analysis);
}

RB_TEST(InValues_Container_Pass)
{
	std::vector<int> vec1;
	vec1.push_back(1);
	vec1.push_back(2);

	RB_PASS(rbIN_VALUES_CONTAINER(({ 1, 2 }), vec1, AllEqual<>()));
	RB_PASS_IV(rbvIN_VALUES_CONTAINER(({ 1, 2 }), vec1, AllEqual<>()));
	RB_PASS(rbIN_CONTAINER_VALUES(vec1, ({ 1, 2 }), AllEqual<>()));
	RB_PASS_IV(rbvIN_CONTAINER_VALUES(vec1, ({ 1, 2 }), AllEqual<>()));
}

RB_TEST(InValues_Container_Fail)
{
	std::vector<int> vec1;
	vec1.push_back(0);
	vec1.push_back(1);
	std::vector<int> vec2;
	vec2.push_back(0);
	vec2.push_back(2);

	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(false).idx(1, ":")("1", true)(" == ")
			.idx(1, ":")("2", true),
	};

	TestableAnalysisOfContainers analysis1(
		"ranges are equal: ",
		"({ 0, 1 })", "vec2");
	analysis1.AddAnalyses(arrAnalysis, 1, false);

	TestableAnalysisOfContainers analysis2(
		"ranges are equal: ",
		"vec1", "({ 0, 2 })");
	analysis2.AddAnalyses(arrAnalysis, 1, false);

	RB_FAIL(rbIN_VALUES_CONTAINER(({ 0, 1 }), vec2, AllEqual<>()), analysis1);
	RB_FAIL_IV(rbvIN_VALUES_CONTAINER(({ 0, 1 }), vec2, AllEqual<>()), analysis1);
	RB_FAIL(rbIN_CONTAINER_VALUES(vec1, ({ 0, 2 }), AllEqual<>()), analysis2);
	RB_FAIL_IV(rbvIN_CONTAINER_VALUES(vec1, ({ 0, 2 }), AllEqual<>()), analysis2);
}

RB_TEST(InValues_Range_Pass)
{
	int a[] = {1,2};

	RB_PASS(rbIN_VALUES_RANGE(({ 1, 2 }), a, a+2, AllEqual<>()));
	RB_PASS_IV(rbvIN_VALUES_RANGE(({ 1, 2 }), a, a+2, AllEqual<>()));
	RB_PASS(rbIN_RANGE_VALUES(a, a+2, ({ 1, 2 }), AllEqual<>()));
	RB_PASS_IV(rbvIN_RANGE_VALUES(a, a+2, ({ 1, 2 }), AllEqual<>()));
}

RB_TEST(InValues_Range_Fail)
{
	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(false).idx(1, ":")("1", true)(" == ")
			.idx(1, ":")("2", true),
	};

	TestableAnalysisOfContainers analysis1(
		"ranges are equal: ",
		"({ 0, 1 })", "a2-a2+2");
	analysis1.AddAnalyses(arrAnalysis, 1, false);

	TestableAnalysisOfContainers analysis2(
		"ranges are equal: ",
		"a1-a1+2", "({ 0, 2 })");
	analysis2.AddAnalyses(arrAnalysis, 1, false);

	int a1[] = { 0, 1 };
	int a2[] = { 0, 2 };

	RB_FAIL(rbIN_VALUES_RANGE(({ 0, 1 }), a2, a2+2, AllEqual<>()), analysis1);
	RB_FAIL_IV(rbvIN_VALUES_RANGE(({ 0, 1 }), a2, a2+2, AllEqual<>()), analysis1);
	RB_FAIL(rbIN_RANGE_VALUES(a1, a1+2, ({ 0, 2 }), AllEqual<>()), analysis2);
	RB_FAIL_IV(rbvIN_RANGE_VALUES(a1, a1+2, ({ 0, 2 }), AllEqual<>()), analysis2);
}

RB_TEST(InValues_Array_Pass)
{
	int a[] = {1,2};

	RB_PASS(rbIN_VALUES_ARRAY(({ 1, 2 }), a, AllEqual<>()));
	RB_PASS_IV(rbvIN_VALUES_ARRAY(({ 1, 2 }), a, AllEqual<>()));
	RB_PASS(rbIN_ARRAY_VALUES(a, ({ 1, 2 }), AllEqual<>()));
	RB_PASS_IV(rbvIN_ARRAY_VALUES(a, ({ 1, 2 }), AllEqual<>()));
}

RB_TEST(InValues_Array_Fail)
{
	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(false).idx(1, ":")("1", true)(" == ")
			.idx(1, ":")("2", true),
	};

	TestableAnalysisOfContainers analysis1(
		"ranges are equal: ",
		"({ 0, 1 })", "a2");
	analysis1.AddAnalyses(arrAnalysis, 1, false);

	TestableAnalysisOfContainers analysis2(
		"ranges are equal: ",
		"a1", "({ 0, 2 })");
	analysis2.AddAnalyses(arrAnalysis, 1, false);

	int a1[] = { 0, 1 };
	int a2[] = { 0, 2 };

	RB_FAIL(rbIN_VALUES_ARRAY(({ 0, 1 }), a2, AllEqual<>()), analysis1);
	RB_FAIL_IV(rbvIN_VALUES_ARRAY(({ 0, 1 }), a2, AllEqual<>()), analysis1);
	RB_FAIL(rbIN_ARRAY_VALUES(a1, ({ 0, 2 }), AllEqual<>()), analysis2);
	RB_FAIL_IV(rbvIN_ARRAY_VALUES(a1, ({ 0, 2 }), AllEqual<>()), analysis2);
}

RB_TEST(InValues_Values_Pass)
{
	RB_PASS(rbIN_VALUES_VALUES(({ 1, 2 }), ({ 1, 2 }), AllEqual<>()));
	RB_PASS_IV(rbvIN_VALUES_VALUES(({ 1, 2 }), ({ 1, 2 }), AllEqual<>()));
}

RB_TEST(InValues_Values_Fail)
{
	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(false).idx(1, ":")("1", true)(" == ")
			.idx(1, ":")("2", true),
	};

	TestableAnalysisOfContainers analysis1(
		"ranges are equal: ",
		"({ 0, 1 })", "({ 0, 2 })");
	analysis1.AddAnalyses(arrAnalysis, 1, false);

	RB_FAIL(rbIN_VALUES_VALUES(({ 0, 1 }), ({ 0, 2 }), AllEqual<>()), analysis1);
	RB_FAIL_IV(rbvIN_VALUES_VALUES(({ 0, 1 }), ({ 0, 2 }), AllEqual<>()), analysis1);
}


#endif
