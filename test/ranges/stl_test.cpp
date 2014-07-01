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

#include <vector>
#include <list>
#include <set>
#include <deque>
#include <map>

using namespace RichBool;
using RichBool::detail::String;

#if !defined (_MSC_VER) || (_MSC_VER>1300)
#define RB_INT_PTR
#else
#define RB_INT_PTR (int*)
#endif

RB_TEST(StdRichBoolPassVector)
{
	std::vector<int> vec;
	vec.push_back(2);
	vec.push_back(6);
	RB_PASS(rbIN_CONTAINER(vec, All<>().Are(Pred1<IsEven>())));
	RB_PASS_VB(rbvIN_CONTAINER(vec, All<>().Are(Pred1<IsEven>())), vec);
}

RB_TEST(StdRichBoolFailVector_Full)
{
	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("2", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("5", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(2, ":")("8", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to all elements in range ",
		"vec");
	analysis.AddAnalyses(arrAnalysis, 3);

	std::vector<int> vec;
	vec.push_back(2);
	vec.push_back(5);
	vec.push_back(8);

	RB_FAIL(rbIN_CONTAINER(vec, All<>(true).Are(Pred1<IsEven>())), analysis);
	RB_FAIL_VB(rbvIN_CONTAINER(vec, All<>(true).Are(Pred1<IsEven>())), analysis, vec);
}

RB_TEST(StdRichBoolPassVectorVectorSorted)
{
	std::vector<int> vec1, vec2;
	vec1.push_back(1);
	vec1.push_back(3);
	vec1.push_back(4);
	vec2.push_back(10);
	vec2.push_back(11);
	vec2.push_back(17);
	std::vector<std::vector<int> > vec;
	vec.push_back(vec1);
	vec.push_back(vec2);

	RB_PASS(rbIN_CONTAINER(vec, All<>().Are(InContainer<Sorted<> >())));
	RB_PASS(rbIN_CONTAINER(vec, All<>().Are(InContainer<Sorted<> >(Sorted<>(true)))));
	RB_PASS(rbIN_CONTAINER(vec, All<>().Are(MakeInContainer(Sorted<>()))));
}

RB_TEST(StdRichBoolFailVectorVectorSorted_Full)
{
	std::vector<int> vec1, vec2;
	vec1.push_back(2);
	vec1.push_back(5);
	vec2.push_back(9);
	vec2.push_back(7);
	vec2.push_back(11);
	std::vector<std::vector<int> > vec;
	vec.push_back(vec1);
	vec.push_back(vec2);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("9", true)(" <= ").idx(1, ":")("7", true),
		MakeGeneralAnalysis(true).idx(1, ":")("7", true)(" <= ").idx(2, ":")("11", true)
	};

	TestableAnalysisOfRange *p = new TestableAnalysisOfRange(
			"range is sorted: ", new IndexExpression(1), NULL);
	p->AddAnalyses(arrAnalyses, 2);

	Analysis *arrAnalyses2[] = { p };

	TestableAnalysisOfRange analysis(
		"predicate applies to all elements in range ", "vec");
	analysis.AddAnalyses(arrAnalyses2, 1);

	RB_FAIL(rbIN_CONTAINER(vec, All<>().Are(InContainer<Sorted<> >(Sorted<>(true)))),
		analysis);
	RB_FAIL(rbIN_CONTAINER(vec, All<>().Are(MakeInContainer(Sorted<>(true)))),
		analysis);
}

RB_TEST(StdRichBoolPassVectorVectorHas)
{
	std::vector<int> vec1, vec2;
	vec1.push_back(2);
	vec1.push_back(3);
	vec1.push_back(4);
	vec2.push_back(10);
	vec2.push_back(12);
	vec2.push_back(17);
	std::vector<std::vector<int> > vec;
	vec.push_back(vec1);
	vec.push_back(vec2);

	RB_PASS(
		rbIN_CONTAINER(vec, All<>().Are(MakeInContainer(Has<>().That(Pred1<IsEven>()))))
	);
	RB_PASS(
		rbIN_CONTAINER(vec, All<>().Are(MakeInContainer(Has<>(true).That(Pred1<IsEven>()))))
	);
}

RB_TEST(StdRichBoolFailVectorVectorHas)
{
	std::vector<int> vec1, vec2;
	vec1.push_back(2);
	vec1.push_back(5);
	vec2.push_back(9);
	vec2.push_back(11);
	std::vector<std::vector<int> > vec;
	vec.push_back(vec1);
	vec.push_back(vec2);

	Analysis *arrAnalyses[] = {
		new TestableAnalysisOfRange(
			"predicate applies to at least one element in range ",
			new IndexExpression(1), NULL)
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to all elements in range ", "vec");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_CONTAINER(vec, All<>().Are(MakeInContainer(Has<>().That(Pred1<IsEven>())))),
		analysis);
}


///////////////////////////////////////////////////////////
// tests on two containers

RB_TEST(StdRichBoolPassVectors)
{
	std::vector<int> vec1, vec2;
	RB_PASS(rbIN_CONTAINERS(vec1, vec2, AllEqual<>()));
	RB_PASS_VB(rbvIN_CONTAINERS(vec1, vec2, AllEqual<>()), vec1);

	vec1.push_back(1); vec2.push_back(1);
	RB_PASS(rbIN_CONTAINERS(vec1, vec2, AllEqual<>()));
	RB_PASS_VB(rbvIN_CONTAINERS(vec1, vec2, AllEqual<>()), vec1);

	vec1.push_back(2); vec2.push_back(2);
	RB_PASS(rbIN_CONTAINERS(vec1, vec2, AllEqual<>()));

	int a[] = { 1, 2 };
	RB_PASS(rbIN_CONTAINER_ARRAY(vec1, a, AllEqual<>()));
	RB_PASS_VB(rbvIN_CONTAINER_ARRAY(vec1, a, AllEqual<>()), vec1);

	RB_PASS(rbIN_ARRAY_CONTAINER(a, vec1, AllEqual<>()));

	RB_PASS(rbIN_CONTAINER_RANGE(vec1, RB_INT_PTR a, a+2, AllEqual<>()));
	RB_PASS(rbIN_RANGE_CONTAINER(RB_INT_PTR a, a+2, vec1, AllEqual<>()));
}

RB_TEST(StdRichBoolPassList)
{
	std::list<int> list1, list2;
	RB_PASS(rbIN_CONTAINERS(list1, list2, AllEqual<>()));

	list1.push_back(1); list2.push_back(1);
	RB_PASS(rbIN_CONTAINERS(list1, list2, AllEqual<>()));

	list1.push_back(2); list2.push_back(2);
	RB_PASS(rbIN_CONTAINERS(list1, list2, AllEqual<>()));

	int a[] = { 1, 2 };
	RB_PASS(rbIN_CONTAINER_ARRAY(list1, a, AllEqual<>()));
}

RB_TEST(StdRichBoolPassDeque)
{
	std::deque<int> deque1, deque2;
	RB_PASS(rbIN_CONTAINERS(deque1, deque2, AllEqual<>()));

	deque1.push_back(1); deque2.push_back(1);
	RB_PASS(rbIN_CONTAINERS(deque1, deque2, AllEqual<>()));

	deque1.push_back(2); deque2.push_back(2);
	RB_PASS(rbIN_CONTAINERS(deque1, deque2, AllEqual<>()));

	int a[] = { 1, 2 };
	RB_PASS(rbIN_CONTAINER_ARRAY(deque1, a, AllEqual<>()));
}

RB_TEST(StdRichBoolPassSet)
{
	std::set<int> set1, set2;
	RB_PASS(rbIN_CONTAINERS(set1, set2, AllEqual<>()));

	set1.insert(1); set2.insert(1);
	RB_PASS(rbIN_CONTAINERS(set1, set2, AllEqual<>()));

	set1.insert(2); set2.insert(2);
	RB_PASS(rbIN_CONTAINERS(set1, set2, AllEqual<>()));

	int a[] = { 1, 2 };
	RB_PASS(rbIN_CONTAINER_ARRAY(set1, a, AllEqual<>()));
}

RB_TEST(StdRichBoolPassMixed)
{
	std::vector<int> vec;
	std::list<int> l;
	RB_PASS(rbIN_CONTAINERS(vec, l, AllEqual<>()));

	vec.push_back(1); l.push_back(1);
	RB_PASS(rbIN_CONTAINERS(vec, l, AllEqual<>()));

	vec.push_back(2); l.push_back(2);
	RB_PASS(rbIN_CONTAINERS(vec, l, AllEqual<>()));
}

RB_TEST(StdRichBoolFail1)
{
	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("1", true)(" == ")
			.idx(0, ":")("2", true),
	};

	TestableAnalysisOfContainers analysis1(
		"ranges are equal: ",
		"vec1", "vec2");
	analysis1.AddAnalyses(arrAnalysis, 1);

	std::vector<int> vec1, vec2;
	vec1.push_back(1); vec2.push_back(2);
	RB_FAIL(rbIN_CONTAINERS(vec1, vec2, AllEqual<>()), analysis1);

	int a[] = { 2 };

	TestableAnalysisOfContainers analysis2(
		"ranges are equal: ",
		"vec1", "a");
	analysis2.AddAnalyses(arrAnalysis, 1, false);

	TestableAnalysisOfRanges analysis3(
		"ranges are equal: ",
		"vec1", 0, "[RB_INT_PTR a,a+1)", 0);
	analysis3.AddAnalyses(arrAnalysis, 1, false);

	TestableAnalysisOfRanges analysis4(
		"ranges are equal: ",
		"vec1", 0, "[RB_INT_PTR a,1)", 0);
	analysis4.AddAnalyses(arrAnalysis, 1, false);

	RB_FAIL(rbIN_CONTAINER_ARRAY(vec1, a, AllEqual<>()), analysis2);
	RB_FAIL(rbIN_CONTAINER_RANGE(vec1, RB_INT_PTR a, a+1, AllEqual<>()), analysis3);
	RB_FAIL(rbIN_CONTAINER_RANGE(vec1, RB_INT_PTR a, 1, AllEqual<>()), analysis4);

	int b[] = { 1 };

	TestableAnalysisOfContainers analysis5(
		"ranges are equal: ",
		"b", "vec2");
	analysis5.AddAnalyses(arrAnalysis, 1, false);

	TestableAnalysisOfRanges analysis6(
		"ranges are equal: ",
		"[RB_INT_PTR b,b+1)", 0, "vec2", 0);
	analysis6.AddAnalyses(arrAnalysis, 1, false);

	TestableAnalysisOfRanges analysis7(
		"ranges are equal: ",
		"[RB_INT_PTR b,1)", 0, "vec2", 0);
	analysis7.AddAnalyses(arrAnalysis, 1, false);

	RB_FAIL(rbIN_ARRAY_CONTAINER(b, vec2, AllEqual<>()), analysis5);
	RB_FAIL(rbIN_RANGE_CONTAINER(RB_INT_PTR b, b+1, vec2, AllEqual<>()), analysis6);
	RB_FAIL(rbIN_RANGE_CONTAINER(RB_INT_PTR b, 1, vec2, AllEqual<>()), analysis7);
}

RB_TEST(StdRichBoolPassVectorVector)
{
	std::vector<int> vecA, vecB;
	vecA.push_back(1);
	vecA.push_back(2);
	vecB.push_back(3);

	std::vector< std::vector<int> > vec1, vec2;
	RB_PASS(rbIN_CONTAINERS(vec1, vec2, Compare<>().That(ContainersEqual<>())));

	vec1.push_back(vecA); vec2.push_back(vecA);
	RB_PASS(rbIN_CONTAINERS(vec1, vec2, Compare<>().That(ContainersEqual<>())));

	vec1.push_back(vecB); vec2.push_back(vecB);
	RB_PASS(rbIN_CONTAINERS(vec1, vec2, Compare<>().That(ContainersEqual<>())));
}

RB_TEST(StdRichBoolPassVectorVector_Less)
{
	std::vector<int> vec1A, vec1B, vec2A, vec2B;
	vec1A.push_back(1); vec2A.push_back(2);
	vec1A.push_back(3); vec2A.push_back(5);
	vec1B.push_back(5); vec2B.push_back(7);
	vec1B.push_back(2); vec2B.push_back(9);

	std::vector< std::vector<int> > vec1, vec2;
	RB_PASS(
		rbIN_CONTAINERS(vec1, vec2, Compare<>().That(
			MakeInContainers(Compare<>().That(Less<>()))))
	);
	RB_PASS(
		rbIN_CONTAINERS(vec1, vec2, Compare<>().That(
			MakeInContainers(Compare<>(true).That(Less<>()))))
	);

	vec1.push_back(vec1A); vec2.push_back(vec2A);
	RB_PASS(
		rbIN_CONTAINERS(vec1, vec2, Compare<>().That(
			MakeInContainers(Compare<>().That(Less<>()))))
	);
	RB_PASS(
		rbIN_CONTAINERS(vec1, vec2, Compare<>().That(
			MakeInContainers(Compare<>(true).That(Less<>()))))
	);

	vec1.push_back(vec1B); vec2.push_back(vec2B);
	RB_PASS(
		rbIN_CONTAINERS(vec1, vec2, Compare<>().That(
			MakeInContainers(Compare<>().That(Less<>()))))
	);
	RB_PASS(
		rbIN_CONTAINERS(vec1, vec2, Compare<>().That(
			MakeInContainers(Compare<>(true).That(Less<>()))))
	);
}

RB_TEST(StdRichBoolFailVectorVector1)
{
	std::vector<int> vecA, vecB, vecC;
	vecA.push_back(1);
	vecA.push_back(2);

	vecB.push_back(3);

	vecC.push_back(4);

	std::vector< std::vector<int> > vec1, vec2;
	vec1.push_back(vecA); vec2.push_back(vecA);
	vec1.push_back(vecB);
	vec1.push_back(vecC); vec2.push_back(vecC);

	Analysis *arrAnalysis[] = {
		new Single(0, 2, "#", new IndexExpression(1), true)
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"vec1", "vec2");
	analysis.AddAnalyses(arrAnalysis, 1);

	RB_FAIL(rbIN_CONTAINERS(vec1, vec2, Compare<>().That(ContainersEqual<>())), analysis);
}

RB_TEST(StdRichBoolFailVectorVector_PartialMatching)
{
	std::vector<int> vec1A, vec1B, vec1C, vec2B;
	vec1A.push_back(1);
	vec1A.push_back(2);
	vec1A.push_back(3);

	vec1B.push_back(4);
	vec1B.push_back(5);
	vec1B.push_back(6);

	vec1C.push_back(7);
	vec1C.push_back(8);
	vec1C.push_back(9);

	vec2B.push_back(4);
	vec2B.push_back(0);
	vec2B.push_back(6);

	std::vector< std::vector<int> > vec1, vec2;
	vec1.push_back(vec1A);
	vec1.push_back(vec1B);
	vec1.push_back(vec1C);

	vec2.push_back(vec2B);

	Analysis *arrAnalysis1[] = {
		MakeGeneralAnalysis(false).idx(1, ":")("5", true)(" == ")
			.idx(1, ":")("0", true),
	};

	TestableAnalysisOfRanges *analysis_i = new TestableAnalysisOfRanges(
		"ranges are equal: ",
		new IndexExpression(1), 0, new IndexExpression(0), 0);
	analysis_i->AddAnalyses(arrAnalysis1, 1);

	Analysis *arrAnalysis2[] = {
		new Single(0, 2, "#", new IndexExpression(0), true),
		analysis_i,
		new Single(0, 2, "#", new IndexExpression(2), true)
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"vec1", "vec2");
	analysis.AddAnalyses(arrAnalysis2, 3);

	RB_FAIL(rbIN_CONTAINERS(vec1, vec2, Compare<>().That(ContainersEqual<>())), analysis);
}

RB_TEST(StdRichBoolFailVectorVectorUnordered_PartialMatching)
{
	std::vector<int> vec1A, vec1B, vec1C, vec2B;
	vec1A.push_back(1);
	vec1A.push_back(2);
	vec1A.push_back(3);

	vec1B.push_back(4);
	vec1B.push_back(5);
	vec1B.push_back(6);

	vec1C.push_back(7);
	vec1C.push_back(8);
	vec1C.push_back(9);

	vec2B.push_back(6);
	vec2B.push_back(0);
	vec2B.push_back(4);

	std::vector< std::vector<int> > vec1, vec2;
	vec1.push_back(vec1A);
	vec1.push_back(vec1B);
	vec1.push_back(vec1C);

	vec2.push_back(vec2B);

	Analysis *arrAnalysis1[] = {
		new Single(0, 2, "5", new IndexExpression(1), true),
		new Single(1, 2, "0", new IndexExpression(1), true)
	};

	TestableAnalysisOfRanges *analysis_i = new TestableAnalysisOfRanges(
		"unordered ranges are equal: ",
		new IndexExpression(1), 0, new IndexExpression(0), 0);
	analysis_i->AddAnalyses(arrAnalysis1, 2);

	Analysis *arrAnalysis2[] = {
		new Single(0, 2, "#", new IndexExpression(0), true),
		analysis_i,
		new Single(0, 2, "#", new IndexExpression(2), true)
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"vec1", "vec2");
	analysis.AddAnalyses(arrAnalysis2, 3);

	RB_FAIL(rbIN_CONTAINERS(vec1, vec2, Compare<>().That(InContainers<AllEqualUnordered<> >())), analysis);
}

RB_TEST(StdRichBoolPassVectorVectorVector)
{
	std::vector<int> vecA, vecB;
	vecA.push_back(1);
	vecA.push_back(2);
	vecB.push_back(3);

	std::vector< std::vector<int> > vecAA, vecBB;
	vecAA.push_back(vecA);
	vecAA.push_back(vecA);
	vecBB.push_back(vecB);
	vecBB.push_back(vecB);

	std::vector< std::vector< std::vector<int> > > vec1, vec2;
	RB_PASS(rbIN_CONTAINERS(vec1, vec2, Compare<>().That(
		MakeInContainers(Compare<>().That(ContainersEqual<>())))));

	vec1.push_back(vecAA); vec2.push_back(vecAA);
	RB_PASS(rbIN_CONTAINERS(vec1, vec2, Compare<>().That(
		MakeInContainers(Compare<>().That(ContainersEqual<>())))));

	vec1.push_back(vecBB); vec2.push_back(vecBB);
	RB_PASS(rbIN_CONTAINERS(vec1, vec2, Compare<>().That(
		MakeInContainers(Compare<>().That(ContainersEqual<>())))));
}

RB_TEST(StdRichBoolPassVectorVectorPointer)
{
	std::vector<int> vecA, vecB;
	vecA.push_back(1);
	vecA.push_back(2);
	vecB.push_back(3);

	std::vector< std::vector<int> > vec1;
	std::vector< std::vector<int>* > vec2;

	ContainersEqual<false, false, Value, PointerLike<std::vector<int> > > rb;

	RB_PASS(rbIN_CONTAINERS(vec1, vec2, Compare<>().That(rb)));

	vec1.push_back(vecA); vec2.push_back(&vecA);
	RB_PASS(rbIN_CONTAINERS(vec1, vec2, Compare<>().That(rb)));

	vec1.push_back(vecB); vec2.push_back(&vecB);
	RB_PASS(rbIN_CONTAINERS(vec1, vec2, Compare<>().That(rb)));
}

RB_TEST(StdMapsEqualPass)
{
	std::map<int, String> map1, map2;

	RB_PASS(rbIN_CONTAINERS(map1, map2, Compare<>(true).That(EqualPair())));

	map1[1] = "a";
	map2[1] = "a";
	RB_PASS(rbIN_CONTAINERS(map1, map2, Compare<>(true).That(EqualPair())));

	map1[2] = "b";
	map2[2] = "b";
	RB_PASS(rbIN_CONTAINERS(map1, map2, Compare<>(true).That(EqualPair())));
}

RB_TEST(StdMapsEqualFail_DifferentValues)
{
	std::map<int, String> map1, map2;

	map1[1] = "a";
	map2[1] = "a";
	map1[2] = "b";
	map2[2] = "c";

	SharedAnalysis
		key1   = (Analysis*)MakeGeneralAnalysis(true).idx(0, ":")("1", true)
			(" == ").idx(0, ":")("1", true),
		key2   = (Analysis*)MakeGeneralAnalysis(true).idx(1, ":")("2", true)
			(" == ").idx(1, ":")("2", true),
		value1 = (Analysis*)MakeGeneralAnalysis(true).idx(0, ":")("a", true)
			(" == ").idx(0, ":")("a", true),
		value2 = (Analysis*)MakeGeneralAnalysis(false).idx(1, ":")("b", true)
			(" == ").idx(1, ":")("c", true);

	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(true)("keys: {")(key1)("}, ")
			("values: {")(value1)("}"),
		MakeGeneralAnalysis(false)("keys: {")(key2)("}, ")
			("values: {")(value2)("}")
	};

	TestableAnalysisOfContainers analysis("predicate applies to ranges ",
		"map1", "map2");
	analysis.AddAnalyses(arrAnalysis, 2);

	RB_FAIL(rbIN_CONTAINERS(map1, map2, Compare<>(true).That(EqualPair())), analysis);
}

RB_TEST(StdMapsEqualFail_DifferentKeys)
{
	std::map<int, String> map1, map2;

	map1[1] = "a";
	map2[1] = "a";
	map1[2] = "b";
	map2[3] = "b";

	SharedAnalysis
		key1   = (Analysis*)MakeGeneralAnalysis(true).idx(0, ":")("1", true)
			(" == ").idx(0, ":")("1", true),
		key2   = (Analysis*)MakeGeneralAnalysis(false).idx(1, ":")("2", true)
			(" == ").idx(1, ":")("3", true),
		value1 = (Analysis*)MakeGeneralAnalysis(true).idx(0, ":")("a", true)
			(" == ").idx(0, ":")("a", true),
		value2 = (Analysis*)MakeGeneralAnalysis(true).idx(1, ":")("b", true)
			(" == ").idx(1, ":")("b", true);

	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(true)("keys: {")(key1)("}, ")
			("values: {")(value1)("}"),
		MakeGeneralAnalysis(false)("keys: {")(key2)("}, ")
			("values: {")(value2)("}")
	};

	TestableAnalysisOfContainers analysis("predicate applies to ranges ",
		"map1", "map2");
	analysis.AddAnalyses(arrAnalysis, 2);

	RB_FAIL(rbIN_CONTAINERS(map1, map2, Compare<>(true).That(EqualPair())), analysis);
}

RB_TEST(StdMapsEqualFail_OneMissing)
{
	std::map<int, String> map1, map2;

	map1[1] = "a";
	map2[1] = "a";

	map1[2] = "b";

	map1[3] = "c";
	map2[3] = "c";

	SharedAnalysis
		key1   = (Analysis*)MakeGeneralAnalysis(true).idx(0, ":")("1", true)
			(" == ").idx(0, ":")("1", true),
		key3   = (Analysis*)MakeGeneralAnalysis(true).idx(2, ":")("3", true)
			(" == ").idx(1, ":")("3", true),
		value1 = (Analysis*)MakeGeneralAnalysis(true).idx(0, ":")("a", true)
			(" == ").idx(0, ":")("a", true),
		value3 = (Analysis*)MakeGeneralAnalysis(true).idx(2, ":")("c", true)
			(" == ").idx(1, ":")("c", true);

	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(true)("keys: {")(key1)("}, ")
			("values: {")(value1)("}"),
		new Single(0, 2, "(2,b)", new IndexExpression(1), true),
		MakeGeneralAnalysis(true)("keys: {")(key3)("}, ")
			("values: {")(value3)("}")
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"map1", "map2");
	analysis.AddAnalyses(arrAnalysis, 3);

	RB_FAIL(rbIN_CONTAINERS(map1, map2, Compare<>(true).That(EqualPair())), analysis);
}

RB_TEST(StdMapsEqualFail_HalfMatchInKey)
{
	std::map<int, String> map1, map2;

	map1[10] = "a";
	map1[20] = "b";
	map1[30] = "c";

	map2[10] = "a";
	map2[15] = "x";
	map2[20] = "y";
	map2[25] = "z";
	map2[30] = "c";

	SharedAnalysis
		key1   = (Analysis*)MakeGeneralAnalysis(true).idx(0, ":")("10", true)
			(" == ").idx(0, ":")("10", true),
		key2   = (Analysis*)MakeGeneralAnalysis(true).idx(1, ":")("20", true)
			(" == ").idx(2, ":")("20", true),
		key3   = (Analysis*)MakeGeneralAnalysis(true).idx(2, ":")("30", true)
			(" == ").idx(4, ":")("30", true),

		value1 = (Analysis*)MakeGeneralAnalysis(true).idx(0, ":")("a", true)
			(" == ").idx(0, ":")("a", true),
		value2 = (Analysis*)MakeGeneralAnalysis(false).idx(1, ":")("b", true)
			(" == ").idx(2, ":")("y", true),
		value3 = (Analysis*)MakeGeneralAnalysis(true).idx(2, ":")("c", true)
			(" == ").idx(4, ":")("c", true);

	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(true)("keys: {")(key1)("}, ")
			("values: {")(value1)("}"),
		new Single(1, 2, "(15,x)", new IndexExpression(1), true),
		MakeGeneralAnalysis(false)("keys: {")(key2)("}, ")
			("values: {")(value2)("}"),
		new Single(1, 2, "(25,z)", new IndexExpression(3), true),
		MakeGeneralAnalysis(true)("keys: {")(key3)("}, ")
			("values: {")(value3)("}")
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"map1", "map2");
	analysis.AddAnalyses(arrAnalysis, 5);

	RB_FAIL(rbIN_CONTAINERS(map1, map2, Compare<>(true).That(EqualPair())),
		analysis);
}




// some tests repeated with deprecated functionality:

RB_TEST(StdRichBoolPassVector_Old)
{
	std::vector<int> vec;
	vec.push_back(2);
	vec.push_back(6);

	RB_PASS(rbIN_CONTAINER_ARG(vec, All<>(), Pred1<IsEven>()));
}

RB_TEST(StdRichBoolFailVector_Old)
{
	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("5", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to all elements in range ",
		"vec");
	analysis.AddAnalyses(arrAnalysis, 1);

	std::vector<int> vec;
	vec.push_back(2);
	vec.push_back(5);
	vec.push_back(8);

	RB_FAIL(rbIN_CONTAINER_ARG(vec, All<>(), Pred1<IsEven>()), analysis);
}

RB_TEST(StdRichBoolPassVectors_Old)
{
	std::vector<int> vec1, vec2;
	vec1.push_back(1); vec2.push_back(1);
	vec1.push_back(2); vec2.push_back(2);
	RB_PASS(rbIN_CONTAINERS_ARG(vec1, vec2, Compare<>(), Equal<>()));

	int a[] = { 1, 2 };
	RB_PASS(rbIN_CONTAINER_ARRAY_ARG(vec1, a, Compare<>(), Equal<>()));
}


// invalid containers

RB_TEST(StdRichBool_Null)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	SharedAnalysis analysis =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue)
		.expr("*vec", ":")(GetNullPtrString(), false);

	std::vector<int> *vec=NULL;

	RB_FAIL(rbIN_CONTAINER(*vec, All<>(true).Are(Pred1<IsEven>())), *analysis);
	RB_FAIL_IV(rbvIN_CONTAINER(*vec, All<>(true).Are(Pred1<IsEven>())), *analysis);
}

RB_TEST(StdRichBool_First_Null)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	SharedAnalysis analysis =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue)
		.expr("*vec1", ":")(GetNullPtrString(), false)(", ").expr("vec2", ":")("#", true);

	std::vector<int> *vec1=NULL;
	std::vector<int> vec2;
	RB_FAIL(rbIN_CONTAINERS(*vec1, vec2, AllEqual<>()), *analysis);
	RB_FAIL_IV(rbvIN_CONTAINERS(*vec1, vec2, AllEqual<>()), *analysis);
}

RB_TEST(StdRichBool_Second_Null)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	SharedAnalysis analysis =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue)
		.expr("vec1", ":")("#", true)(", ").expr("*vec2", ":")(GetNullPtrString(), false);

	std::vector<int> vec1;
	std::vector<int> *vec2=NULL;
	RB_FAIL(rbIN_CONTAINERS(vec1, *vec2, AllEqual<>()), *analysis);
	RB_FAIL_IV(rbvIN_CONTAINERS(vec1, *vec2, AllEqual<>()), *analysis);
}

RB_TEST(RichBoolPass_Values)
{
	// note: no tests with rich booleans of the rbv type that return a value when that value is of type RichBool::Values,
	// because that is not supported for that type, users should only use it in Rich Booleans

#if !defined (_MSC_VER) || (_MSC_VER>1300)
	RB_PASS(rbIN_CONTAINERS(RichBool::Values<int>(), RichBool::Values<int>(), AllEqual<>()));
#endif

	RB_PASS(rbIN_CONTAINERS(RichBool::Values(1), RichBool::Values(1), AllEqual<>()));

	RB_PASS(rbIN_CONTAINERS(RichBool::Values(1, 2), RichBool::Values(1, 2), AllEqual<>()));

	int a[] = { 1, 2 };
	RB_PASS(rbIN_CONTAINER_ARRAY(RichBool::Values(1, 2), a, AllEqual<>()));

	RB_PASS(rbIN_ARRAY_CONTAINER(a, RichBool::Values(1, 2), AllEqual<>()));

	RB_PASS(rbIN_CONTAINER_RANGE(RichBool::Values(1, 2), RB_INT_PTR a, a+2, AllEqual<>()));
	RB_PASS(rbIN_RANGE_CONTAINER(RB_INT_PTR a, a+2, RichBool::Values(1, 2), AllEqual<>()));
}

RB_TEST(RichBoolFail_Values)
{
	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("1", true)(" == ")
			.idx(0, ":")("2", true),
	};

	TestableAnalysisOfContainers analysis1(
		"ranges are equal: ",
		"RichBool::Values(1)", "RichBool::Values(2)");
	analysis1.AddAnalyses(arrAnalysis, 1);

	RB_FAIL(rbIN_CONTAINERS(RichBool::Values(1), RichBool::Values(2), AllEqual<>()), analysis1);

	int a[] = { 2 };

	TestableAnalysisOfContainers analysis2(
		"ranges are equal: ",
		"RichBool::Values(1)", "a");
	analysis2.AddAnalyses(arrAnalysis, 1, false);

	TestableAnalysisOfRanges analysis3(
		"ranges are equal: ",
		"RichBool::Values(1)", 0, "[RB_INT_PTR a,a+1)", 0);
	analysis3.AddAnalyses(arrAnalysis, 1, false);

	TestableAnalysisOfRanges analysis4(
		"ranges are equal: ",
		"RichBool::Values(1)", 0, "[RB_INT_PTR a,1)", 0);
	analysis4.AddAnalyses(arrAnalysis, 1, false);

	RB_FAIL(rbIN_CONTAINER_ARRAY(RichBool::Values(1), a, AllEqual<>()), analysis2);
	RB_FAIL(rbIN_CONTAINER_RANGE(RichBool::Values(1), RB_INT_PTR a, a+1, AllEqual<>()), analysis3);
	RB_FAIL(rbIN_CONTAINER_RANGE(RichBool::Values(1), RB_INT_PTR a, 1, AllEqual<>()), analysis4);

	int b[] = { 1 };

	TestableAnalysisOfContainers analysis5(
		"ranges are equal: ",
		"b", "RichBool::Values(2)");
	analysis5.AddAnalyses(arrAnalysis, 1, false);

	TestableAnalysisOfRanges analysis6(
		"ranges are equal: ",
		"[RB_INT_PTR b,b+1)", 0, "RichBool::Values(2)", 0);
	analysis6.AddAnalyses(arrAnalysis, 1, false);

	TestableAnalysisOfRanges analysis7(
		"ranges are equal: ",
		"[RB_INT_PTR b,1)", 0, "RichBool::Values(2)", 0);
	analysis7.AddAnalyses(arrAnalysis, 1, false);

	RB_FAIL(rbIN_ARRAY_CONTAINER(b, RichBool::Values(2), AllEqual<>()), analysis5);
	RB_FAIL(rbIN_RANGE_CONTAINER(RB_INT_PTR b, b+1, RichBool::Values(2), AllEqual<>()), analysis6);
	RB_FAIL(rbIN_RANGE_CONTAINER(RB_INT_PTR b, 1, RichBool::Values(2), AllEqual<>()), analysis7);
}
