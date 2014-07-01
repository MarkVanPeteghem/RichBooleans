//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/functors.hpp"
#include "richbool/stdstring.hpp"
#include "testable_analysis_for_ranges.hpp"
#include "testable_analysis_with_strings.hpp"

using namespace RichBool;


////////////////////////////////////////////////////////
// class GeneralAnalysis

RB_TEST(GeneralAnalysis_Text_Equal_StateNotOk)
{
	Analysis *analysis1 = MakeGeneralAnalysis(false)("abc");
	Analysis *analysis2 = MakeGeneralAnalysis(false)("abc");

	RB_PASS_B(*analysis1==*analysis2);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_Text_Equal_StateOk)
{
	Analysis *analysis1 = MakeGeneralAnalysis(true)("abc");
	Analysis *analysis2 = MakeGeneralAnalysis(true)("abc");

	RB_PASS_B(*analysis1==*analysis2);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_Text_StateDifferent)
{
	Analysis *analysis1 = MakeGeneralAnalysis(false)("abc");
	Analysis *analysis2 = MakeGeneralAnalysis(true) ("abc");

	RB_PASS_B(*analysis1!=*analysis2);
	RB_PASS_B(*analysis2!=*analysis1);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_Text_TextDifferent)
{
	Analysis *analysis1 = MakeGeneralAnalysis(false)("abd");
	Analysis *analysis2 = MakeGeneralAnalysis(false)("abc");

	RB_PASS_B(*analysis1!=*analysis2);
	RB_PASS_B(*analysis2!=*analysis1);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_2TextParts_Equal)
{
	Analysis *analysis1 = MakeGeneralAnalysis(false)("abc")("xyz");
	Analysis *analysis2 = MakeGeneralAnalysis(false)("abc")("xyz");

	RB_PASS_B(*analysis1==*analysis2);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_2TextParts_NotEqualA)
{
	Analysis *analysis1 = MakeGeneralAnalysis(false)("abd")("xyz");
	Analysis *analysis2 = MakeGeneralAnalysis(false)("abc")("xyz");

	RB_PASS_B(*analysis1!=*analysis2);
	RB_PASS_B(*analysis2!=*analysis1);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_2TextParts_NotEqualB)
{
	Analysis *analysis1 = MakeGeneralAnalysis(false)("abc")("wyz");
	Analysis *analysis2 = MakeGeneralAnalysis(false)("abc")("xyz");

	RB_PASS_B(*analysis1!=*analysis2);
	RB_PASS_B(*analysis2!=*analysis1);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_2TextParts_1TextPart)
{
        Analysis *analysis1 = MakeGeneralAnalysis(false)("ab")("c");
        Analysis *analysis2 = MakeGeneralAnalysis(false)("abc");

        RB_PASS_B(*analysis1!=*analysis2);
        RB_PASS_B(*analysis2!=*analysis1);

        delete analysis1;
        delete analysis2;
}

RB_TEST(GeneralAnalysis_1TextPart_2TextParts)
{
        Analysis *analysis1 = MakeGeneralAnalysis(false)("abc");
        Analysis *analysis2 = MakeGeneralAnalysis(false)("ab")("c");

        RB_PASS_B(*analysis1!=*analysis2);
        RB_PASS_B(*analysis2!=*analysis1);

        delete analysis1;
        delete analysis2;
}

RB_TEST(GeneralAnalysis_ValueText_Equal)
{
	Analysis *analysis1 = MakeGeneralAnalysis(false)("1", true);
	Analysis *analysis2 = MakeGeneralAnalysis(false)("1", true);

	RB_PASS_B(*analysis1==*analysis2);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_ValueText_TextDifferent)
{
	Analysis *analysis1 = MakeGeneralAnalysis(false)("1", true);
	Analysis *analysis2 = MakeGeneralAnalysis(false)("2", true);

	RB_PASS_B(*analysis1!=*analysis2);
	RB_PASS_B(*analysis2!=*analysis1);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_ValueText_StateDifferent)
{
	Analysis *analysis1 = MakeGeneralAnalysis(false)("1", false);
	Analysis *analysis2 = MakeGeneralAnalysis(false)("1", true);

	RB_PASS_B(*analysis1!=*analysis2);
	RB_PASS_B(*analysis2!=*analysis1);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_ValueText_Text_NotEqual)
{
	Analysis *analysis1 = MakeGeneralAnalysis(false)("abc", true);
	Analysis *analysis2 = MakeGeneralAnalysis(false)("abc");

	RB_PASS_B(*analysis1!=*analysis2);
	RB_PASS_B(*analysis2!=*analysis1);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_InvalidText_Equal)
{
	Analysis *analysis1 = MakeGeneralAnalysis(false)("*p", true);
	Analysis *analysis2 = MakeGeneralAnalysis(false)("*p", true);

	RB_PASS_B(*analysis1==*analysis2);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_InvalidText_NotEqual)
{
	Analysis *analysis1 = MakeGeneralAnalysis(false)("*p", true);
	Analysis *analysis2 = MakeGeneralAnalysis(false)("abc");

	RB_PASS_B(*analysis1!=*analysis2);
	RB_PASS_B(*analysis2!=*analysis1);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_NewLine_Equal)
{
	Analysis *analysis1 = MakeGeneralAnalysis(false)();
	Analysis *analysis2 = MakeGeneralAnalysis(false)();

	RB_PASS_B(*analysis1==*analysis2);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_NewLine_NotEqual)
{
	Analysis *analysis1 = MakeGeneralAnalysis(false)()();
	Analysis *analysis2 = MakeGeneralAnalysis(false)();

	RB_PASS_B(*analysis1!=*analysis2);
	RB_PASS_B(*analysis2!=*analysis1);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_Analysis_Equal)
{
	Analysis *analysisA = MakeGeneralAnalysis(false)("abc");
	Analysis *analysisB = MakeGeneralAnalysis(false)("abc");

	Analysis *analysis1 = MakeGeneralAnalysis(false)(analysisA);
	Analysis *analysis2 = MakeGeneralAnalysis(false)(analysisB);

	RB_PASS_B(*analysis1==*analysis2);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_Analysis_NotEqual)
{
	Analysis *analysisA = MakeGeneralAnalysis(false)("abc");
	Analysis *analysisB = MakeGeneralAnalysis(false)("abd");

	Analysis *analysis1 = MakeGeneralAnalysis(false)(analysisA);
	Analysis *analysis2 = MakeGeneralAnalysis(false)(analysisB);

	RB_PASS_B(*analysis1!=*analysis2);
	RB_PASS_B(*analysis2!=*analysis1);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_Analysis_NotEqual_ShortAndNotShort)
{
	Analysis *analysisA = MakeGeneralAnalysis(false)("abc");
	Analysis *analysisB = MakeGeneralAnalysis(false)("abc");

	Analysis *analysis1 = MakeGeneralAnalysis(false)(analysisA, false);
	Analysis *analysis2 = MakeGeneralAnalysis(false)(analysisB, true);

	RB_PASS_B(*analysis1!=*analysis2);
	RB_PASS_B(*analysis2!=*analysis1);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_Analysis_WithEpilogue_Equal)
{
	Analysis *analysis1 = MakeGeneralAnalysis(false)("abc").ep("ep");
	Analysis *analysis2 = MakeGeneralAnalysis(false)("abc").ep("ep");

	RB_PASS_B(*analysis1==*analysis2);
	RB_PASS_B(*analysis2==*analysis1);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_Analysis_WithEpilogue_Different)
{
	Analysis *analysis1 = MakeGeneralAnalysis(false)("abc").ep("ep1");
	Analysis *analysis2 = MakeGeneralAnalysis(false)("abc").ep("ep2");

	RB_PASS_B(*analysis1!=*analysis2);
	RB_PASS_B(*analysis2!=*analysis1);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_Analysis_WithWithoutEpilogue)
{
	Analysis *analysis1 = MakeGeneralAnalysis(false)("abc").ep("ep");
	Analysis *analysis2 = MakeGeneralAnalysis(false)("abc");

	RB_PASS_B(*analysis1!=*analysis2);
	RB_PASS_B(*analysis2!=*analysis1);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_Analysis_WithAnything)
{
	Analysis *analysis1 = MakeGeneralAnalysis(false)("abc").Anything()("xyz");
	Analysis *analysis2 = MakeGeneralAnalysis(false)("abc")("def")("xyz");

	RB_PASS_B(*analysis1==*analysis2);
	RB_PASS_B(*analysis2==*analysis1);

	delete analysis1;
	delete analysis2;
}

RB_TEST(GeneralAnalysis_Analysis_WithAnything_Fail)
{
	Analysis *analysis1 = MakeGeneralAnalysis(false)("abc").Anything()("xy");
	Analysis *analysis2 = MakeGeneralAnalysis(false)("abc")("def")("xyz");

	RB_PASS_B(*analysis1!=*analysis2);
	RB_PASS_B(*analysis2!=*analysis1);

	delete analysis1;
	delete analysis2;
}


////////////////////////////////////////////////////////
// class CombinedAnalysis

RB_TEST(CombinedAnalysis_False_Equal)
{
	Bool b1a = false, b1b = false;
	Bool b2a = false, b2b = false;

	CombinedAnalysis c1(b1a, b1b, "&&", false);
	CombinedAnalysis c2(b2a, b2b, "&&", false);

	RB_PASS_B(c1==c2);
}

RB_TEST(CombinedAnalysis_True_Equal)
{
	Bool b1a = true, b1b = true;
	Bool b2a = true, b2b = true;

	CombinedAnalysis c1(b1a, b1b, "&&", false);
	CombinedAnalysis c2(b2a, b2b, "&&", false);

	RB_PASS_B(c1==c2);
}

RB_TEST(CombinedAnalysis_FalseTrue_Equal)
{
	Bool b1a = false, b1b = true;
	Bool b2a = false, b2b = true;

	CombinedAnalysis c1(b1a, b1b, "&&", false);
	CombinedAnalysis c2(b2a, b2b, "&&", false);

	RB_PASS_B(c1==c2);
}

RB_TEST(CombinedAnalysis_Bool_Diff)
{
	Bool b1a = false, b1b = true;
	Bool b2a = false, b2b = false;

	CombinedAnalysis c1(b1a, b1b, "&&", false);
	CombinedAnalysis c2(b2a, b2b, "&&", false);

	RB_PASS_B(c1!=c2);
	RB_PASS_B(c2!=c1);
}

RB_TEST(CombinedAnalysis_FalseAnalysis_Equal)
{
	Bool b1a = false, b1b = (Analysis*)MakeGeneralAnalysis(false)("abc");
	Bool b2a = false, b2b = (Analysis*)MakeGeneralAnalysis(false)("abc");

	CombinedAnalysis c1(b1a, b1b, "&&", false);
	CombinedAnalysis c2(b2a, b2b, "&&", false);

	RB_PASS_B(c1==c2);
}

RB_TEST(CombinedAnalysis_FalseAnalysis_Diff)
{
	Bool b1a = false, b1b = (Analysis*)MakeGeneralAnalysis(false)("abc");
	Bool b2a = false, b2b = (Analysis*)MakeGeneralAnalysis(false)("abd");

	CombinedAnalysis c1(b1a, b1b, "&&", false);
	CombinedAnalysis c2(b2a, b2b, "&&", false);

	RB_PASS_B(c1!=c2);
	RB_PASS_B(c2!=c1);
}

RB_TEST(CombinedAnalysis_Mixed_Diff)
{
	Bool b1a = false, b1b = (Analysis*)MakeGeneralAnalysis(false)("abc");
	Bool b2a = false, b2b = false;

	CombinedAnalysis c1(b1a, b1b, "&&", false);
	CombinedAnalysis c2(b2a, b2b, "&&", false);

	RB_PASS_B(c1!=c2);
	RB_PASS_B(c2!=c1);
}


////////////////////////////////////////////////////////
// class Single

RB_TEST(IndexOfSingle_Equal)
{
	Single analysis1(1, 2, "text", new TextExpression("expr"), true);
	Single analysis2(1, 2, "text", new TextExpression("expr"), true);

	RB_PASS_B(analysis1==analysis2);
}

RB_TEST(IndexOfSingle_Idx_Diff)
{
	Single analysis1(1, 2, "text", new TextExpression("expr"), true);
	Single analysis2(0, 2, "text", new TextExpression("expr"), true);

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}

RB_TEST(IndexOfSingle_Total_Diff)
{
	Single analysis1(1, 2, "text", new TextExpression("expr"), true);
	Single analysis2(1, 3, "text", new TextExpression("expr"), true);

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}

RB_TEST(IndexOfSingle_Text_Diff)
{
	Single analysis1(1, 2, "text", new TextExpression("expr"), true);
	Single analysis2(1, 2, "other", new TextExpression("expr"), true);

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}

RB_TEST(IndexOfSingle_Expr_Diff)
{
	Single analysis1(1, 2, "text", new TextExpression("expr"), true);
	Single analysis2(1, 2, "text", new TextExpression("other"), true);

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}

RB_TEST(IndexOfSingle_Valid_Diff)
{
	Single analysis1(1, 2, "text", new TextExpression("expr"), true);
	Single analysis2(1, 2, "text", new TextExpression("expr"), false);

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}


////////////////////////////////////////////////////////
// class AnalysisOfRange

RB_TEST(AnalysisOfRange_Empty_Equal)
{
	TestableAnalysisOfRange analysis1("", "", ""),
		analysis2("", "", "");

	RB_PASS_B(analysis1==analysis2);
}

RB_TEST(AnalysisOfRange_Equal)
{
	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(true)("1", true)(" == ")("1", true),
		MakeGeneralAnalysis(true)("2", true)(" == ")("2", true),
	};

	TestableAnalysisOfRange
		analysis1("a", "b", "c"),
		analysis2("a", "b", "c");
	analysis1.AddAnalyses(arrAnalysis, 2);
	analysis2.AddAnalyses(arrAnalysis, 2, false);

	RB_PASS_B(analysis1==analysis2);
}

RB_TEST(AnalysisOfRange_WithNull_Equal)
{
	Analysis *arrAnalysis[] = {
		0,
		MakeGeneralAnalysis(true)("2", true)(" == ")("2", true),
	};

	TestableAnalysisOfRange
		analysis1("a", "b", "c"),
		analysis2("a", "b", "c");
	analysis1.AddAnalyses(arrAnalysis, 2);
	analysis2.AddAnalyses(arrAnalysis, 2, false);

	RB_PASS_B(analysis1==analysis2);
}

RB_TEST(AnalysisOfRange_Empty_NotEmpty_Diff)
{
	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(true)("1", true)(" == ")("1", true),
		MakeGeneralAnalysis(true)("2", true)(" == ")("2", true),
	};

	TestableAnalysisOfRange
		analysis1("a", "b", "c"),
		analysis2("a", "b", "c");
	analysis2.AddAnalyses(arrAnalysis, 2);

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}

RB_TEST(AnalysisOfRange_Empty_Message_Diff)
{
	TestableAnalysisOfRange
		analysis1("message1", "b", "c"),
		analysis2("message2", "b", "c");

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}

RB_TEST(AnalysisOfRange_Empty_Expr1_Diff)
{
	TestableAnalysisOfRange
		analysis1("message", "b", "c"),
		analysis2("message", "x", "c");

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}

RB_TEST(AnalysisOfRange_Empty_Expr2_Diff)
{
	TestableAnalysisOfRange
		analysis1("message", "b", "c"),
		analysis2("message", "b", "x");

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}

RB_TEST(AnalysisOfRange_Diff)
{
	Analysis *arrAnalysis1[] = {
		MakeGeneralAnalysis(true)("1", true)(" == ")("1", true),
		MakeGeneralAnalysis(true)("2", true)(" == ")("2", true)
	};

	Analysis *arrAnalysis2[] = {
		MakeGeneralAnalysis(true)("1", true)(" == ")("1", true),
		MakeGeneralAnalysis(true)("2", true)(" == ")("3", true)
	};

	TestableAnalysisOfRange
		analysis1("a", "b", "c"),
		analysis2("a", "b", "c");

	analysis1.AddAnalyses(arrAnalysis1, 2);
	analysis2.AddAnalyses(arrAnalysis2, 2);

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}

RB_TEST(AnalysisOfRange_WithNull_Diff)
{
	Analysis *arrAnalysis1[] = {
		0,
		MakeGeneralAnalysis(true)("2", true)(" == ")("2", true)
	};

	Analysis *arrAnalysis2[] = {
		MakeGeneralAnalysis(true)("1", true)(" == ")("1", true),
		MakeGeneralAnalysis(true)("2", true)(" == ")("2", true)
	};

	TestableAnalysisOfRange
		analysis1("a", "b", "c"),
		analysis2("a", "b", "c");
	analysis1.AddAnalyses(arrAnalysis1, 2);
	analysis2.AddAnalyses(arrAnalysis2, 2);

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}


////////////////////////////////////////////////////////
// class AnalysisOfStrings

RB_TEST(AnalysisOfStrings_Equal)
{
	TestableAnalysisOfStrings analysis1("abc", "abd", "sz1", "sz2", "  X", "=="),
		analysis2("abc", "abd", "sz1", "sz2", "  X", "==");

	RB_PASS_B(analysis1==analysis2);
}

RB_TEST(AnalysisOfStrings_Equal_WithType)
{
	TestableAnalysisOfStrings analysis1("abc", "abd", "sz1", "sz2", "  X", "==", "type"),
		analysis2("abc", "abd", "sz1", "sz2", "  X", "==", "type");

	RB_PASS_B(analysis1==analysis2);
}

RB_TEST(AnalysisOfStrings_String1_Diff)
{
	TestableAnalysisOfStrings analysis1("abc", "abd", "sz1", "sz2", "  X", "=="),
		analysis2("abd", "abd", "sz1", "sz2", "  X", "==");

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}

RB_TEST(AnalysisOfStrings_String2_Diff)
{
	TestableAnalysisOfStrings analysis1("abc", "abe", "sz1", "sz2", "  X", "=="),
		analysis2("abc", "abd", "sz1", "sz2", "  X", "==");

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}

RB_TEST(AnalysisOfStrings_Comparison_Diff)
{
	TestableAnalysisOfStrings analysis1("abc", "abc", "sz1", "sz2", "  X", "=="),
		analysis2("abc", "abc", "sz1", "sz2", "   ", "==");

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}

RB_TEST(AnalysisOfStrings_ComparisonType_Diff)
{
	TestableAnalysisOfStrings analysis1("abc", "abc", "sz1", "sz2", "  X", "=="),
		analysis2("abc", "abc", "sz1", "sz2", "  X", "==", "case insensitive");

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}

RB_TEST(AnalysisOfStrings_ComparisonType_Diff_OneNull)
{
	TestableAnalysisOfStrings analysis1("abc", "abc", "sz1", "sz2", "  X", "=="),
		analysis2("abc", "abc", "sz1", "sz2", "  X", "==", "case insensitive");

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}


////////////////////////////////////////////////////////
// class AnalysisNotEvaluated

RB_TEST(AnalysisNotEvaluated)
{
	// AnalysisNotEvaluated objects are always equal
	AnalysisNotEvaluated analysis1, analysis2;

	RB_PASS_B(analysis1==analysis2);
}


////////////////////////////////////////////////////////
// class BriefAnalysisOfTwoSequences

RB_TEST(BriefAnalysisOfTwoSequencesEqual)
{
	BriefAnalysisOfTwoSequences
		analysis1(false, new TextExpression("a"), new TextExpression("b"), "1", "==", "2"),
		analysis2(false, new TextExpression("a"), new TextExpression("b"), "1", "==", "2");

	analysis1.SetString1("0011");
	analysis1.SetString2("0101");
	analysis1.SetStringDiff("  XX");

	analysis2.SetString1("0011");
	analysis2.SetString2("0101");
	analysis2.SetStringDiff("  XX");

	RB_PASS_B(analysis1==analysis2);
}

RB_TEST(BriefAnalysisOfTwoSequencesDiffStr1)
{
	BriefAnalysisOfTwoSequences
		analysis1(false, new TextExpression("a"), new TextExpression("b"), "1", "==", "2"),
		analysis2(false, new TextExpression("a"), new TextExpression("b"), "1", "==", "2");

	analysis1.SetString1("0011");
	analysis1.SetString2("0101");
	analysis1.SetStringDiff("  XX");

	analysis2.SetString1("0010");
	analysis2.SetString2("0101");
	analysis2.SetStringDiff("  XX");

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}

RB_TEST(BriefAnalysisOfTwoSequencesDiffStr2)
{
	BriefAnalysisOfTwoSequences
		analysis1(false, new TextExpression("a"), new TextExpression("b"), "1", "==", "2"),
		analysis2(false, new TextExpression("a"), new TextExpression("b"), "1", "==", "2");

	analysis1.SetString1("0011");
	analysis1.SetString2("0101");
	analysis1.SetStringDiff("  XX");

	analysis2.SetString1("0011");
	analysis2.SetString2("0100");
	analysis2.SetStringDiff("  XX");

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}

RB_TEST(BriefAnalysisOfTwoSequencesDiffDiff)
{
	BriefAnalysisOfTwoSequences
		analysis1(false, new TextExpression("a"), new TextExpression("b"), "1", "==", "2"),
		analysis2(false, new TextExpression("a"), new TextExpression("b"), "1", "==", "2");

	analysis1.SetString1("0011");
	analysis1.SetString2("0101");
	analysis1.SetStringDiff("  XX");

	analysis2.SetString1("0011");
	analysis2.SetString2("0101");
	analysis2.SetStringDiff("  X ");

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}

RB_TEST(BriefAnalysisOfTwoSequencesDiffExpr1)
{
	BriefAnalysisOfTwoSequences
		analysis1(false, new TextExpression("a"), new TextExpression("b"), "1", "==", "2"),
		analysis2(false, new TextExpression("c"), new TextExpression("b"), "1", "==", "2");

	analysis1.SetString1("0011");
	analysis1.SetString2("0101");
	analysis1.SetStringDiff("  XX");

	analysis2.SetString1("0011");
	analysis2.SetString2("0101");
	analysis2.SetStringDiff("  XX");

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}

RB_TEST(BriefAnalysisOfTwoSequencesDiffExpr2)
{
	BriefAnalysisOfTwoSequences
		analysis1(false, new TextExpression("a"), new TextExpression("b"), "1", "==", "2"),
		analysis2(false, new TextExpression("a"), new TextExpression("c"), "1", "==", "2");

	analysis1.SetString1("0011");
	analysis1.SetString2("0101");
	analysis1.SetStringDiff("  XX");

	analysis2.SetString1("0011");
	analysis2.SetString2("0101");
	analysis2.SetStringDiff("  XX");

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}

RB_TEST(BriefAnalysisOfTwoSequencesDiffOk)
{
	BriefAnalysisOfTwoSequences
		analysis1(false, new TextExpression("a"), new TextExpression("b"), "1", "==", "2"),
		analysis2(false, new TextExpression("a"), new TextExpression("b"), "1", "==", "2");

	analysis1.SetString1("0011");
	analysis1.SetString2("0101");
	analysis1.SetStringDiff("  XX");
	analysis1.SetState(Analysis::NotOk);

	analysis2.SetString1("0011");
	analysis2.SetString2("0101");
	analysis2.SetStringDiff("  XX");
	analysis2.SetState(Analysis::Ok);

	RB_PASS_B(analysis1!=analysis2);
	RB_PASS_B(analysis2!=analysis1);
}


// comparing different types

struct dummy
{
	bool operator()(char , char ) const { return true; }
};

void CheckDifferent(Analysis **analyses, size_t size)
{
	for (size_t i=0; i<size; ++i)
		for (size_t j=0; j<size; ++j)
		{
			if (i!=j)
			{
				RB_PASS_B(*analyses[i]!=*analyses[j]);
			}
			else
			{
				RB_PASS_B(*analyses[i]==*analyses[j]);
			}
		}
}

void CheckDifferentTypes(Analysis **analyses, size_t size)
{
	for (size_t i=0; i<size; ++i)
		for (size_t j=0; j<size; ++j)
		{
			if (i!=j)
			{
				RB_PASS_B(analyses[i]->GetType()!=analyses[j]->GetType());
			}
			else
			{
				RB_PASS_B(analyses[i]->GetType()==analyses[j]->GetType());
			}
		}
}

RB_TEST(AllTypes_Different)
{
	GeneralAnalysis analysis1(false);
	CombinedAnalysis analysis2(Bool(false), Bool(false), "&&",
		false);
	Single analysis3(0, 1, "", new TextExpression(""), true);
	AnalysisOfRange analysis4(false, "-", new TextExpression("a"), new TextExpression("b"));
	AnalysisOfStrings analysis5(false, "", "", "", " == ", "strcmp",
		new TextExpression(""), new TextExpression(""));
	AnalysisNotEvaluated analysis6;
	BriefAnalysisOfTwoSequences analysis7(false, new TextExpression(""), new TextExpression(""),
		"", "", "");

	Analysis * analyses[] =
	{
		&analysis1,
		&analysis2,
		&analysis3,
		&analysis4,
		&analysis5,
		&analysis6,
		&analysis7
	};

	CheckDifferent(analyses, 7);
	CheckDifferentTypes(analyses, 7);
}

#if !defined(RICHBOOL_USE_WX) && defined(RICHBOOL_HAS_WSTRING)

#define CHECK_WCOLLATE \
	try { \
		WCollate wcollate; \
	} \
	catch (...) { \
		print_warning("Can't do wide character collation", __FILE__, __LINE__); \
		return; \
	}

using RichBool::detail::String;
using RichBool::detail::WString;

RB_TEST(AnalysisOfStrings_Types_Different)
{
	// The next line may print a warning on some systems if wide character
	// collation is not possible.
	// You can still use all the other functionality of Rich Booleans.
	CHECK_WCOLLATE;

	AnalysisOfStrings analysis1(false, String(), String(), String(), " == ", "",
		new TextExpression(""), new TextExpression(""));
	AnalysisOfWStrings analysis2(false, WString(), WString(), String(), " == ", "",
		new TextExpression(""), new TextExpression(""));

	RB_PASS_B(analysis1!=analysis2);
}
#endif

