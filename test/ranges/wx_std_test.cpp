//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com


// This file tests the use of wxWidgets containers with Rich Booleans
// meant for STL-containers. This is possible since at least wxWidgets 2.6.1
// for wxArrays of primitive types.


#ifdef RICHBOOL_USE_WX

#if defined(_MSC_VER)
	#pragma warning(disable: 4786)
#endif

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
	#include "wx/wx.h"
#endif

#include <wx/version.h>

#if wxCHECK_VERSION(2, 6, 0)
#include "rbtest.hpp"
#include "richbool/richbool.hpp"
#include "richbool/std.hpp"
#include "testable_analysis_for_ranges.hpp"
#include "predicates.hpp"
#include <wx/arrimpl.cpp>
#include <wx/listimpl.cpp>

using namespace RichBool;

WX_DEFINE_ARRAY_INT(int, IntArray);

WX_DECLARE_OBJARRAY(IntArray, IntArrayArray);

WX_DECLARE_OBJARRAY(IntArrayArray, IntArrayArrayArray);

WX_DECLARE_LIST(int, IntList);

// note: WX_DEFINE_XXX macros are already in wx_test.cpp

RB_TEST(WxStdRichBoolPassVector)
{
	IntArray vec;
	RB_PASS(rbIN_CONTAINER_ARG(vec, All<>(), Pred1<IsEven>()));

	vec.Add(2);
	RB_PASS(rbIN_CONTAINER_ARG(vec, All<>(), Pred1<IsEven>()));

	vec.Add(6);
	RB_PASS(rbIN_CONTAINER_ARG(vec, All<>(), Pred1<IsEven>()));
}

RB_TEST(WxStdRichBoolFailVector)
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

	RB_FAIL(rbIN_CONTAINER_ARG(vec, All<>(), Pred1<IsEven>()), analysis);
}

RB_TEST(WxStdRichBoolFailVector_Full)
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

	RB_FAIL(rbIN_CONTAINER_ARG(vec, All<>(true), Pred1<IsEven>()), analysis);
}

RB_TEST(WxStdRichBoolPassVectors)
{
	IntArray vec1, vec2;
	RB_PASS(rbIN_CONTAINERS(vec1, vec2, AllEqual<>()));

	vec1.Add(1); vec2.Add(1);
	RB_PASS(rbIN_CONTAINERS(vec1, vec2, AllEqual<>()));

	vec1.Add(2); vec2.Add(2);
	RB_PASS(rbIN_CONTAINERS(vec1, vec2, AllEqual<>()));

	int a[] = { 1, 2 };
	RB_PASS(rbIN_CONTAINER_ARRAY(vec1, a, AllEqual<>()));
}

RB_TEST(WxStdRichBoolPassVectorPred)
{
	IntArray vec1, vec2;
	RB_PASS(rbIN_CONTAINERS_ARG(vec1, vec2, Compare<>(), Pred2<ProductIs12>()));

	vec1.Add(1); vec2.Add(12);
	RB_PASS(rbIN_CONTAINERS_ARG(vec1, vec2, Compare<>(), Pred2<ProductIs12>()));

	vec1.Add(6); vec2.Add(2);
	RB_PASS(rbIN_CONTAINERS_ARG(vec1, vec2, Compare<>(), Pred2<ProductIs12>()));

	int a[] = { 12, 2 };
	RB_PASS(rbIN_CONTAINER_ARRAY_ARG(vec1, a, Compare<>(), Pred2<ProductIs12>()));
}


#endif // #if wxCHECK_VERSION(2, 6, 0)

#endif // #ifdef RICHBOOL_USE_WX


















