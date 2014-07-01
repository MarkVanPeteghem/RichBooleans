//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#if defined(RICHBOOL_USE_WX)

#if defined(_MSC_VER)
	#pragma warning(disable: 4786)
#endif

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
	#include "wx/wx.h"
#endif

#include "richbool/wx_iter.hpp"
#include "rbtest.hpp"
#include "richbool/richbool.hpp"
#include "richbool/xcontainers.hpp"
#include "richbool/containers.hpp"
#include "richbool/pair.hpp"
#include "testable_analysis_for_ranges.hpp"
#include "predicates.hpp"
#include <wx/arrimpl.cpp>
#include <wx/listimpl.cpp>


WX_DEFINE_ARRAY_INT(int, IntArray);

WX_DECLARE_OBJARRAY(IntArray, IntArrayArray);
WX_DEFINE_OBJARRAY(IntArrayArray);

WX_DECLARE_OBJARRAY(IntArrayArray, IntArrayArrayArray);
WX_DEFINE_OBJARRAY(IntArrayArrayArray);

WX_DEFINE_ARRAY_ITERATOR(int, IntArray, IntArrayIterator)
WX_DEFINE_ARRAY_ITERATOR(IntArray, IntArrayArray, IntArrayArrayIterator)
WX_DEFINE_ARRAY_ITERATOR(IntArrayArray, IntArrayArrayArray, IntArrayArrayArrayIterator)

WX_DECLARE_LIST(int, IntList);

WX_DEFINE_LIST(IntList);

WX_DEFINE_LIST_ITERATOR(int, IntList, IntListIterator)

#include <vector>

using namespace RichBool;

RB_TEST(WxRichBoolPassVector)
{
	IntArray vec;

	RB_PASS(rbIN_XCONTAINER(vec, All<>().Are(Pred1<IsEven>())));
	RB_PASS(rbIN_XCONTAINER_ARG(vec, All<>(), Pred1<IsEven>()));

	vec.Add(2);
	RB_PASS(rbIN_XCONTAINER_ARG(vec, All<>(), Pred1<IsEven>()));

	vec.Add(6);
	RB_PASS(rbIN_XCONTAINER_ARG(vec, All<>(), Pred1<IsEven>()));
}

RB_TEST(WxRichBoolFailVector)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("5", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to all elements in range ", "vec");
	analysis.AddAnalyses(arrAnalyses, 1);

	IntArray vec;
	vec.Add(2);
	vec.Add(5);
	vec.Add(8);

	RB_FAIL(rbIN_XCONTAINER_ARG(vec, All<>(), Pred1<IsEven>()), analysis);
}

RB_TEST(WxRichBoolFailVector_Full)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("2", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("5", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(2, ":")("8", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to all elements in range ", "vec");
	analysis.AddAnalyses(arrAnalyses, 3);

	IntArray vec;
	vec.Add(2);
	vec.Add(5);
	vec.Add(8);

	RB_FAIL(rbIN_XCONTAINER_ARG(vec, All<>(true), Pred1<IsEven>()), analysis);
}

RB_TEST(WxRichBoolPassVectorSorted)
{
	IntArray vec;
	vec.Add(1);
	vec.Add(3);
	vec.Add(5);
	RB_PASS(rbIN_XCONTAINER(vec, Sorted<>()));
	RB_PASS_IV(rbvIN_XCONTAINER(vec, Sorted<>()));
}

RB_TEST(WxRichBoolFailVectorSorted)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(1, ":")("8", true)(" <= ")
			.idx(2, ":")("5", true),
	};

	TestableAnalysisOfRange analysis("range is sorted: ", "vec");
	analysis.AddAnalyses(arrAnalyses, 1);

	IntArray vec;
	vec.Add(2);
	vec.Add(8);
	vec.Add(5);

	RB_FAIL(rbIN_XCONTAINER(vec, Sorted<>()), analysis);
	RB_FAIL_IV(rbvIN_XCONTAINER(vec, Sorted<>()), analysis);
}

RB_TEST(WxRichBoolFailVectorSorted_Full)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true).idx(0, ":")("2", true)(" <= ")
			.idx(1, ":")("8", true),
		MakeGeneralAnalysis(false).idx(1, ":")("8", true)(" <= ")
			.idx(2, ":")("5", true),
	};

	TestableAnalysisOfRange analysis("range is sorted: ", "vec");
	analysis.AddAnalyses(arrAnalyses, 2);

	IntArray vec;
	vec.Add(2);
	vec.Add(8);
	vec.Add(5);

	RB_FAIL(rbIN_XCONTAINER(vec, Sorted<>(true)), analysis);
}

RB_TEST(WxRichBoolPassVectorVectorSorted)
{
	IntArray vec1, vec2;
	vec1.Add(1);
	vec1.Add(3);
	vec1.Add(4);
	vec2.Add(10);
	vec2.Add(11);
	vec2.Add(17);
	IntArrayArray vec;
	vec.Add(vec1);
	vec.Add(vec2);

	RB_PASS(rbIN_XCONTAINER_ARG(vec, All<>(), InXContainer<Sorted<> >()));
	RB_PASS(rbIN_XCONTAINER_ARG(vec, All<>(), InXContainer<Sorted<> >(Sorted<>(true))));
	RB_PASS(rbIN_XCONTAINER_ARG(vec, All<>(), MakeInXContainer(Sorted<>())));
}

RB_TEST(WxRichBoolFailVectorVectorSorted)
{
	IntArray vec1, vec2;
	vec1.Add(2);
	vec1.Add(5);
	vec2.Add(9);
	vec2.Add(7);
	vec2.Add(11);
	IntArrayArray vec;
	vec.Add(vec1);
	vec.Add(vec2);

	Analysis *arrAnalyses2[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("9", true)(" <= ").idx(1, ":")("7", true)
	};

	TestableAnalysisOfRange *p = new TestableAnalysisOfRange(
		"range is sorted: ", new IndexExpression(1), NULL);
	p->AddAnalyses(arrAnalyses2, 1);

	Analysis *arrAnalyses[] = { p };

	TestableAnalysisOfRange analysis(
		"predicate applies to all elements in range ", "vec");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_XCONTAINER_ARG(vec, All<>(), InXContainer<Sorted<> >()),
		analysis);
	RB_FAIL(rbIN_XCONTAINER_ARG(vec, All<>(), MakeInXContainer(Sorted<>())),
		analysis);
}

RB_TEST(WxRichBoolFailVectorVectorSorted_Full)
{
	IntArray vec1, vec2;
	vec1.Add(2);
	vec1.Add(5);
	vec2.Add(9);
	vec2.Add(7);
	vec2.Add(11);
	IntArrayArray vec;
	vec.Add(vec1);
	vec.Add(vec2);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("9", true)(" <= ").idx(1, ":")("7", true),
		MakeGeneralAnalysis(true).idx(1, ":")("7", true)(" <= ").idx(2, ":")("11", true)
	};

	TestableAnalysisOfRange *p = new TestableAnalysisOfRange("range is sorted: ",
			new IndexExpression(1), NULL);
	p->AddAnalyses(arrAnalyses, 2);

	Analysis *arrAnalyses2[] = { p };

	TestableAnalysisOfRange analysis(
		"predicate applies to all elements in range ", "vec");
	analysis.AddAnalyses(arrAnalyses2, 1);

	RB_FAIL(rbIN_XCONTAINER_ARG(vec, All<>(), InXContainer<Sorted<> >(Sorted<>(true))),
		analysis);
	RB_FAIL(rbIN_XCONTAINER_ARG(vec, All<>(), MakeInXContainer(Sorted<>(true))),
		analysis);
}

RB_TEST(WxRichBoolPassVectorVectorAll)
{
	IntArray vec1, vec2;
	vec1.Add(2);
	vec1.Add(4);
	vec2.Add(10);
	vec2.Add(12);
	IntArrayArray vec;
	vec.Add(vec1);
	vec.Add(vec2);

	RB_PASS(
		rbIN_XCONTAINER_ARG(vec, All<>(),
			MakeInXContainer(All<>().Are(Pred1<IsEven>()))
		)
	);

	RB_PASS(
		rbIN_XCONTAINER_ARG(vec, All<>(),
			MakeInXContainer(All<>(true).Are(Pred1<IsEven>()))
		)
	);
}

RB_TEST(WxRichBoolFailVectorVectorAll)
{
	IntArray vec1, vec2;
	vec1.Add(2);
	vec1.Add(4);
	vec2.Add(10);
	vec2.Add(11);
	IntArrayArray vec;
	vec.Add(vec1);
	vec.Add(vec2);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("11", true)(")")
	};

	TestableAnalysisOfRange *p = new TestableAnalysisOfRange(
			"predicate applies to all elements in range ",
			new IndexExpression(1), NULL);
	p->AddAnalyses(arrAnalyses, 1);

	Analysis *arrAnalyses2[] = { p };

	TestableAnalysisOfRange analysis(
		"predicate applies to all elements in range ", "vec");
	analysis.AddAnalyses(arrAnalyses2, 1);

	RB_FAIL(rbIN_XCONTAINER_ARG(vec, All<>(), MakeInXContainer(All<>().Are(Pred1<IsEven>()))),
		analysis);
}

RB_TEST(WxRichBoolFailVectorVectorAll_Full)
{
	IntArray vec1, vec2;
	vec1.Add(2);
	vec1.Add(4);
	vec2.Add(10);
	vec2.Add(11);
	IntArrayArray vec;
	vec.Add(vec1);
	vec.Add(vec2);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true) ("predicate(").idx(0, ":")("10", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("11", true)(")")
	};

	TestableAnalysisOfRange *p = new TestableAnalysisOfRange(
			"predicate applies to all elements in range ",
			new IndexExpression(1), NULL);
	p->AddAnalyses(arrAnalyses, 2);

	Analysis *arrAnalyses2[] = { p };

	TestableAnalysisOfRange analysis(
		"predicate applies to all elements in range ", "vec");
	analysis.AddAnalyses(arrAnalyses2, 1);

	RB_FAIL(rbIN_XCONTAINER_ARG(vec, All<>(), MakeInXContainer(All<>(true).Are(Pred1<IsEven>()))),
		analysis);
}


///////////////////////////////////////////////////////////
// tests on two containers

RB_TEST(WxRichBoolPassVectors)
{
	IntArray vec1, vec2;
	RB_PASS(rbIN_XCONTAINERS(vec1, vec2, AllEqual<>()));
	RB_PASS_IV(rbvIN_XCONTAINERS(vec1, vec2, AllEqual<>()));

	vec1.Add(1); vec2.Add(1);
	RB_PASS(rbIN_XCONTAINERS(vec1, vec2, AllEqual<>()));
	RB_PASS_IV(rbvIN_XCONTAINERS(vec1, vec2, AllEqual<>()));

	vec1.Add(2); vec2.Add(2);
	RB_PASS(rbIN_XCONTAINERS(vec1, vec2, AllEqual<>()));
	RB_PASS_IV(rbvIN_XCONTAINERS(vec1, vec2, AllEqual<>()));

	int a[] = { 1, 2 };
	RB_PASS(rbIN_XCONTAINER_ARRAY(vec1, a, AllEqual<>()));
	RB_PASS_IV(rbvIN_XCONTAINER_ARRAY(vec1, a, AllEqual<>()));
	RB_PASS(rbIN_ARRAY_XCONTAINER(a, vec1, AllEqual<>()));
	RB_PASS_IV(rbvIN_ARRAY_XCONTAINER(a, vec1, AllEqual<>()));

	RB_PASS(rbIN_XCONTAINER_RANGE(vec1, a, a+2, AllEqual<>()));
	RB_PASS(rbIN_RANGE_XCONTAINER(a, a+2, vec1, AllEqual<>()));
	RB_PASS_IV(rbvIN_RANGE_XCONTAINER(a, a+2, vec1, AllEqual<>()));
}

RB_TEST(WxRichBoolPassVectorPred)
{
	IntArray vec1, vec2;
	RB_PASS(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(), Pred2<ProductIs12>()));

	vec1.Add(1); vec2.Add(12);
	RB_PASS(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(), Pred2<ProductIs12>()));

	vec1.Add(6); vec2.Add(2);
	RB_PASS(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(), Pred2<ProductIs12>()));

	int a[] = { 12, 2 };
	RB_PASS(rbIN_XCONTAINER_ARRAY_ARG(vec1, a, Compare<>(), Pred2<ProductIs12>()));
}

RB_TEST(WxRichBoolPassList)
{
	int a1=1, b1=1, a2=2, b2=2;

	IntList list1, list2;
	RB_PASS(rbIN_XCONTAINERS(list1, list2, AllEqual<>()));

	list1.Append(&a1); list2.Append(&b1);
	RB_PASS(rbIN_XCONTAINERS(list1, list2, AllEqual<>()));

	list1.Append(&a2); list2.Append(&b2);
	RB_PASS(rbIN_XCONTAINERS(list1, list2, AllEqual<>()));

	int arr[] = { 1, 2 };
	RB_PASS(rbIN_XCONTAINER_ARRAY(list1, arr, AllEqual<>()));
	RB_PASS(rbIN_ARRAY_XCONTAINER(arr, list1, AllEqual<>()));
}

RB_TEST(WxRichBoolPassMixed)
{
	int a=1, b=2;

	IntArray vec;
	IntList l;
	RB_PASS(rbIN_XCONTAINERS(vec, l, AllEqual<>()));

	vec.Add(1); l.Append(&a);
	RB_PASS(rbIN_XCONTAINERS(vec, l, AllEqual<>()));

	vec.Add(2); l.Append(&b);
	RB_PASS(rbIN_XCONTAINERS(vec, l, AllEqual<>()));
}

RB_TEST(WxRichBoolFail1)
{
	Analysis *arrAnalyses1[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("1", true)(" == ")
			.idx(0, ":")("2", true)
	};

	Analysis *arrAnalyses2[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("2", true)(" == ")
			.idx(0, ":")("1", true)
	};

	TestableAnalysisOfContainers resCont1(
		"ranges are equal: ", "vec1", "vec2");
	resCont1.AddAnalyses(arrAnalyses1, 1);

	TestableAnalysisOfContainers resCont2(
		"ranges are equal: ", "vec1", "a");
	resCont2.AddAnalyses(arrAnalyses1, 1, false);

	TestableAnalysisOfContainers resCont3(
		"ranges are equal: ", "a", "vec1");
	resCont3.AddAnalyses(arrAnalyses2, 1);

	IntArray vec1, vec2;
	vec1.Add(1); vec2.Add(2);
	RB_FAIL(rbIN_XCONTAINERS(vec1, vec2, AllEqual<>()), resCont1);
	RB_FAIL_IV(rbvIN_XCONTAINERS(vec1, vec2, AllEqual<>()), resCont1);

	int a[] = { 2 };
	RB_FAIL(rbIN_XCONTAINER_ARRAY(vec1, a, AllEqual<>()), resCont2);
	RB_FAIL_IV(rbvIN_XCONTAINER_ARRAY(vec1, a, AllEqual<>()), resCont2);
	RB_FAIL(rbIN_ARRAY_XCONTAINER(a, vec1, AllEqual<>()), resCont3);
	RB_FAIL_IV(rbvIN_ARRAY_XCONTAINER(a, vec1, AllEqual<>()), resCont3);

	TestableAnalysisOfRanges resCont4(
		"ranges are equal: ", "vec1", 0, "a", "a+1");
	resCont4.AddAnalyses(arrAnalyses1, 1, false);

	TestableAnalysisOfRanges resCont5(
		"ranges are equal: ", "a", "a+1", "vec1", 0);
	resCont5.AddAnalyses(arrAnalyses2, 1, false);

	RB_FAIL(rbIN_XCONTAINER_RANGE(vec1, a, a+1, AllEqual<>()), resCont4);
	RB_FAIL(rbIN_RANGE_XCONTAINER(a, a+1, vec1, AllEqual<>()), resCont5);
	RB_FAIL_IV(rbvIN_RANGE_XCONTAINER(a, a+1, vec1, AllEqual<>()), resCont5);
}

RB_TEST(WxRichBoolFailPred)
{
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(0, ":")("3", true)(", ")
			.idx(0, ":")("5", true)(")")
	};

	TestableAnalysisOfContainers resCont1(
		"predicate applies to ranges ",
		"vec1", "vec2");
	resCont1.AddAnalyses(arrAnalyses, 1);

	TestableAnalysisOfContainers resCont2(
		"predicate applies to ranges ",
		"vec1", "a");
	resCont2.AddAnalyses(arrAnalyses, 1, false);

	IntArray vec1, vec2;
	vec1.Add(3); vec2.Add(5);
	RB_FAIL(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(), Pred2<ProductIs12>()), resCont1);

	int a[] = { 5 };
	RB_FAIL(rbIN_XCONTAINER_ARRAY_ARG(vec1, a, Compare<>(), Pred2<ProductIs12>()), resCont2);
}

RB_TEST(WxRichBoolPassVectorsVector)
{
	IntArray vecA, vecB;
	vecA.Add(1);
	vecA.Add(2);
	vecB.Add(3);

	IntArrayArray vec1, vec2;
	RB_PASS(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(), XContainersEqual<>()));

	vec1.Add(vecA); vec2.Add(vecA);
	RB_PASS(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(), XContainersEqual<>()));

	vec1.Add(vecB); vec2.Add(vecB);
	RB_PASS(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(), XContainersEqual<>()));
}

RB_TEST(WxRichBoolPassVectorVector_Less)
{
	IntArray vec1A, vec1B, vec2A, vec2B;
	vec1A.Add(1); vec2A.Add(2);
	vec1A.Add(3); vec2A.Add(5);
	vec1B.Add(5); vec2B.Add(7);
	vec1B.Add(2); vec2B.Add(9);

	IntArrayArray vec1, vec2;
	RB_PASS(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(), MakeInXContainers(Compare<>().That(Less<>()))));

	vec1.Add(vec1A); vec2.Add(vec2A);
	RB_PASS(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(), MakeInXContainers(Compare<>().That(Less<>()))));

	vec1.Add(vec1B); vec2.Add(vec2B);
	RB_PASS(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(), MakeInXContainers(Compare<>().That(Less<>()))));
}

RB_TEST(WxRichBoolPassVectorVector_ProductIs12)
{
	IntArray vec1A, vec1B, vec2A, vec2B;
	vec1A.Add(1); vec2A.Add(12);
	vec1A.Add(3); vec2A.Add(4);
	vec1B.Add(6); vec2B.Add(2);
	vec1B.Add(12); vec2B.Add(1);

	IntArrayArray vec1, vec2;
	RB_PASS(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(),
		MakeInXContainers(Compare<>().That(Pred2<ProductIs12>()))));

	vec1.Add(vec1A); vec2.Add(vec2A);
	RB_PASS(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(),
		MakeInXContainers(Compare<>().That(Pred2<ProductIs12>()))));

	vec1.Add(vec1B); vec2.Add(vec2B);
	RB_PASS(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(),
		MakeInXContainers(Compare<>().That(Pred2<ProductIs12>()))));
}

RB_TEST(WxRichBoolPassVectorVector_ProductIs10)
{
	IntArray vec1A, vec1B, vec2A, vec2B;
	vec1A.Add(1); vec2A.Add(10);
	vec1A.Add(2); vec2A.Add(5);
	vec1B.Add(5); vec2B.Add(2);
	vec1B.Add(10); vec2B.Add(1);

	IntArrayArray vec1, vec2;
	RB_PASS(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(),
		MakeInXContainers(Compare<>().That(PredToRichBool_2Arg(ProductIs(10)))))
	);

	vec1.Add(vec1A); vec2.Add(vec2A);
	RB_PASS(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(),
		MakeInXContainers(Compare<>().That(PredToRichBool_2Arg(ProductIs(10)))))
	);

	vec1.Add(vec1B); vec2.Add(vec2B);
	RB_PASS(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(),
		MakeInXContainers(Compare<>().That(PredToRichBool_2Arg(ProductIs(10)))))
	);
}

RB_TEST(WxRichBoolFailVectorVector1)
{
	IntArray vecA, vecB, vecC;
	vecA.Add(1);
	vecA.Add(2);

	vecB.Add(3);

	vecC.Add(4);

	IntArrayArray vec1, vec2;
	vec1.Add(vecA); vec2.Add(vecA);
	vec1.Add(vecB);
	vec1.Add(vecC); vec2.Add(vecC);

	Analysis *arrAnalyses[] = {
		new Single(0, 2, "#", new IndexExpression(1), true)
	};

	TestableAnalysisOfContainers resCont1(
		"predicate applies to ranges ",
		"vec1", "vec2");
	resCont1.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(), XContainersEqual<>()), resCont1);
}

RB_TEST(WxRichBoolFailVectorVector2)
{
	IntArray vecA, vecB, vecC, vecD;
	vecA.Add(1);
	vecA.Add(2);

	vecB.Add(3);

	vecC.Add(4);

	IntArrayArray vec1, vec2;
	vec1.Add(vecA); vec2.Add(vecA);
	vec1.Add(vecB); vec2.Add(vecC);
	vec1.Add(vecD); vec2.Add(vecD);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false).idx(0, ":")("3", true)(" == ").idx(0, ":")("4", true)
	};

	TestableAnalysisOfRanges *resCont1 = new TestableAnalysisOfRanges(
		"ranges are equal: ",
		new IndexExpression(1), NULL, new IndexExpression(1), NULL);
	resCont1->AddAnalyses(arrAnalyses, 1);

	Analysis *analysis2[] = {
		resCont1
	};

	TestableAnalysisOfContainers resCont2(
		"predicate applies to ranges ",
		"vec1", "vec2");
	resCont2.AddAnalyses(analysis2, 1);

	RB_FAIL(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(), XContainersEqual<>()), resCont2);
}

RB_TEST(WxRichBoolFailVectorVector_Less)
{
	IntArray vec1A, vec1B, vec2A, vec2B;
	vec1A.Add(1); vec2A.Add(2);
	vec1A.Add(2); vec2A.Add(4);

	vec1B.Add(3); vec2B.Add(5);
	vec1B.Add(6); vec2B.Add(4);


	IntArrayArray vec1, vec2;
	vec1.Add(vec1A); vec2.Add(vec2A);
	vec1.Add(vec1B); vec2.Add(vec2B);

	Analysis *arrAnalysesB[] = {
		MakeGeneralAnalysis(false).idx(1, ":")("6", true)(" < ").idx(1, ":")("4", true)
	};

	TestableAnalysisOfRanges *resContB = new TestableAnalysisOfRanges(
		"predicate applies to ranges ",
		new IndexExpression(1), NULL, new IndexExpression(1), NULL);
	resContB->AddAnalyses(arrAnalysesB, 1);

	Analysis *analysis2[] = {
		resContB
	};

	TestableAnalysisOfContainers resCont(
		"predicate applies to ranges ",
		"vec1", "vec2");
	resCont.AddAnalyses(analysis2, 1);

	RB_FAIL(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(),
		MakeInXContainers(Compare<>().That(Less<>()))), resCont);
}

RB_TEST(WxRichBoolFailVectorVector_PartialMatching)
{
	IntArray vec1A, vec1B, vec1C, vec2B;
	vec1A.Add(1);
	vec1A.Add(2);
	vec1A.Add(3);

	vec1B.Add(4);
	vec1B.Add(5);
	vec1B.Add(6);

	vec1C.Add(7);
	vec1C.Add(8);
	vec1C.Add(9);

	vec2B.Add(4);
	vec2B.Add(0);
	vec2B.Add(6);

	IntArrayArray vec1, vec2;
	vec1.Add(vec1A);
	vec1.Add(vec1B);
	vec1.Add(vec1C);

	vec2.Add(vec2B);

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

	RB_FAIL(rbIN_XCONTAINERS(vec1, vec2, Compare<>().That(XContainersEqual<>())), analysis);
}

RB_TEST(WxRichBoolPassVectorVectorVector)
{
	IntArray vecA, vecB;
	vecA.Add(1);
	vecA.Add(2);
	vecB.Add(3);

	IntArrayArray vecAA, vecBB;
	vecAA.Add(vecA);
	vecAA.Add(vecA);
	vecBB.Add(vecB);
	vecBB.Add(vecB);

	IntArrayArrayArray vec1, vec2;
	RB_PASS(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(),
		MakeInXContainers(Compare<>().That(XContainersEqual<>()))));

	vec1.Add(vecAA); vec2.Add(vecAA);
	RB_PASS(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(),
		MakeInXContainers(Compare<>().That(XContainersEqual<>()))));

	vec1.Add(vecBB); vec2.Add(vecBB);
	RB_PASS(rbIN_XCONTAINERS_ARG(vec1, vec2, Compare<>(),
		MakeInXContainers(Compare<>().That(XContainersEqual<>()))));

}

WX_DECLARE_HASH_MAP(int, wxString, wxIntegerHash, wxIntegerEqual, Map);

RB_TEST(WxMapsEqualPass)
{
	Map map1, map2;

	RB_PASS(rbIN_CONTAINERS_ARG(map1, map2, Compare<>(true), EqualPair()));

	map1[1] = "a";
	map2[1] = "a";
	RB_PASS(rbIN_CONTAINERS_ARG(map1, map2, Compare<>(true), EqualPair()));

	map1[2] = "b";
	map2[2] = "b";
	RB_PASS(rbIN_CONTAINERS_ARG(map1, map2, Compare<>(true), EqualPair()));
}

RB_TEST(WxMapsEqualFail_DifferentValues)
{
	Map map1, map2;

	map1[1] = "a";
	map2[1] = "a";
	map1[2] = "b";
	map2[2] = "c";

	SharedAnalysis
		key1   = (Analysis*)MakeGeneralAnalysis(true).idx(0,":")("1", true)(" == ")
			.idx(0,":")("1", true),
		key2   = (Analysis*)MakeGeneralAnalysis(true).idx(1,":")("2", true)(" == ")
			.idx(1,":")("2", true),
		value1 = (Analysis*)MakeGeneralAnalysis(true).idx(0,":")("a", true)(" == ")
			.idx(0,":")("a", true),
		value2 = (Analysis*)MakeGeneralAnalysis(false).idx(1,":")("b", true)(" == ")
			.idx(1,":")("c", true);

	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(true)("keys: {")(key1)("}, ")
			("values: {")(value1)("}"),
		MakeGeneralAnalysis(false)("keys: {")(key2)("}, ")
			("values: {")(value2)("}")
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"map1", "map2");
	analysis.AddAnalyses(arrAnalysis, 2);

	RB_FAIL(rbIN_CONTAINERS_ARG(map1, map2, Compare<>(true), EqualPair()), analysis);
}

RB_TEST(WxMapsEqualFail_DifferentKeys)
{
	Map map1, map2;

	map1[1] = "a";
	map2[1] = "a";
	map1[2] = "b";
	map2[3] = "b";

	SharedAnalysis
		key1   = (Analysis*)MakeGeneralAnalysis(true).idx(0,":")("1", true)(" == ").idx(0,":")("1", true),
		key2   = (Analysis*)MakeGeneralAnalysis(false).idx(1,":")("2", true)(" == ").idx(1,":")("3", true),
		value1 = (Analysis*)MakeGeneralAnalysis(true).idx(0,":")("a", true)(" == ").idx(0,":")("a", true),
		value2 = (Analysis*)MakeGeneralAnalysis(true).idx(1,":")("b", true)(" == ").idx(1,":")("b", true);

	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(true)("keys: {")(key1)("}, ")
			("values: {")(value1)("}"),
		MakeGeneralAnalysis(false)("keys: {")(key2)("}, ")
			("values: {")(value2)("}")
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"map1", "map2");
	analysis.AddAnalyses(arrAnalysis, 2);

	RB_FAIL(rbIN_CONTAINERS_ARG(map1, map2, Compare<>(true), EqualPair()), analysis);
}

RB_TEST(WxMapsEqualFail_OneMissing)
{
	Map map1, map2;

	map1[1] = "a";
	map2[1] = "a";

	map1[2] = "b";

	map1[3] = "c";
	map2[3] = "c";

	SharedAnalysis
		key1   = (Analysis*)MakeGeneralAnalysis(true).idx(0,":")("1", true)(" == ")
			.idx(0,":")("1", true),
		key3   = (Analysis*)MakeGeneralAnalysis(true).idx(2,":")("3", true)(" == ")
			.idx(1,":")("3", true),
		value1 = (Analysis*)MakeGeneralAnalysis(true).idx(0,":")("a", true)(" == ")
			.idx(0,":")("a", true),
		value3 = (Analysis*)MakeGeneralAnalysis(true).idx(2,":")("c", true)(" == ")
			.idx(1,":")("c", true);

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

	RB_FAIL(rbIN_CONTAINERS_ARG(map1, map2, Compare<>(true), EqualPair()), analysis);
}

#endif // #ifdef RICHBOOL_USE_WX
