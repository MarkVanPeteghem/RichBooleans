//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#define RICHBOOL_NO_TEXT

#include "rbtest.hpp"
#include "richbool/richbool.hpp"
#include "testable_analysis_for_ranges.hpp"

RB_TEST(NoText_2_Pass)
{
	int a=1, b=1;
	RB_PASS(rbEQUAL(a, b));
	RB_PASS_V(rbvEQUAL(a, b), a);
}

RB_TEST(NoText_2_Fail)
{
	int a=1, b=2;

	RichBool::SharedAnalysis analysisEqual =
		(RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false)("1", true)(" == ")("2", true);
	RB_FAIL(rbEQUAL(a, b), *analysisEqual);
	RB_FAIL_V(rbvEQUAL(a, b), *analysisEqual, a);
}

RB_TEST(NoText_3_Pass)
{
	int a=1, b=2, c=3;
	RB_PASS(rbORDER_3(a, <, b, <, c));
	RB_PASS_V(rbvORDER_3(a, <, b, <, c), b);
}

RB_TEST(NoText_3_Fail)
{
	int a=1, b=2, c=1;

	RichBool::SharedAnalysis analysis=
		(RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false)
		("1", true)(" < ")("2", true)(" < ")("1", true);
	RB_FAIL(rbORDER_3(a, <, b, <, c), *analysis);
}

RB_TEST(NoText_4_Pass)
{
	int a=1, b=2, c=3, d=4;
	RB_PASS(rbORDER_4(a, <, b, <, c, <, d));
}

RB_TEST(NoText_4_Fail)
{
	int a=1, b=2, c=1, d=4;

	RichBool::SharedAnalysis analysis=
		(RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false)
		("1", true)(" < ")("2", true)(" < ")("1", true)(" < ")("4", true);
	RB_FAIL(rbORDER_4(a, <, b, <, c, <, d), *analysis);
}

RB_TEST(NoText_Range)
{
	RichBool::Analysis *arrAnalyses[] = {
		RichBool::MakeGeneralAnalysis(true).idx(0, ":")("1", true)(" == ").idx(0, ":")("1", true),
		RichBool::MakeGeneralAnalysis(true).idx(1, ":")("2", true)(" == ").idx(1, ":")("2", true),
		new RichBool::Single(0, 2, "3", new RichBool::IndexExpression(2), true)
	};

	RichBool::TextExpression *ee=NULL;

	TestableAnalysisOfRanges analysis1(
		"predicate applies to ranges ", ee, ee, ee, ee);
	analysis1.AddAnalyses(arrAnalyses, 3);
	TestableAnalysisOfRanges analysis2(
		"predicate applies to ranges ", ee, ee, ee, ee);
	analysis2.AddAnalyses(arrAnalyses, 3, false);

	int a[] = { 1, 2, 3 }, b[] = { 1, 2 };

	RB_FAIL(rbIN_RANGES(a, a+3, b, b+2, RichBool::Compare<>(true).That(RichBool::Equal<>())), analysis1);
	RB_FAIL(rbIN_RANGES(a, 3, b, 2, RichBool::Compare<>(true).That(RichBool::Equal<>())), analysis2);
}
