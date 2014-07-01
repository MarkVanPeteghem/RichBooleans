//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/richbool.hpp"

using namespace RichBool;

RB_TEST(BitsOff)
{
	RB_PASS(rbBITS_OFF(12, 3));
	RB_PASS_V(rbvBITS_OFF(12, 3), 12);
}

RB_TEST(BitsOn)
{
	RB_PASS(rbBITS_ON(15, 3));
	RB_PASS_V(rbvBITS_ON(15, 3), 15);
}

RB_TEST(BitsAre_Pass)
{
    RB_PASS(rbBITS_ARE((char)15, "0000 1#1#"));
	RB_PASS_V(rbvBITS_ARE((char)15, "0000 1#1#"), 15);

	// extra space at end
	RB_PASS(rbBITS_ARE((char)15, "0000 1#1# "));
	RB_PASS_V(rbvBITS_ARE((char)15, "0000 1#1# "), 15);

    // other separators
    RB_PASS(rbBITS_ARE((char)15, "00.00:1#-1#,"));
	RB_PASS_V(rbvBITS_ARE((char)15, "00.00:1#-1#,"), 15);

}

RB_TEST(Fail_BitsOff)
{
	BriefAnalysisOfTwoSequences analysis2Seq1(false, new TextExpression("15"), new TextExpression("51"),
		"", " has bits ", " off");
	analysis2Seq1.SetString1   ("00001111000000000000000000000000");
	analysis2Seq1.SetString2   ("00110011000000000000000000000000");
	analysis2Seq1.SetStringDiff("      XX                        ");
	analysis2Seq1.SetTitle1("bits");
	analysis2Seq1.SetTitle2("mask");
	analysis2Seq1.SetTitleDiff("err ");
	analysis2Seq1.SetBlockSize(8);
	analysis2Seq1.SetBlocksPerLine(8);
	RB_FAIL(rbBITS_OFF(15, 51), analysis2Seq1);
	RB_FAIL_V(rbvBITS_OFF(15, 51), analysis2Seq1, 15);
}

RB_TEST(Fail_BitsOn)
{
	BriefAnalysisOfTwoSequences analysis2Seq2(false, new TextExpression("60"), new TextExpression("15"),
		"", " has bits ", " on");
	analysis2Seq2.SetString1   ("00111100000000000000000000000000");
	analysis2Seq2.SetString2   ("00001111000000000000000000000000");
	analysis2Seq2.SetStringDiff("      XX                        ");
	analysis2Seq2.SetTitle1("bits");
	analysis2Seq2.SetTitle2("mask");
	analysis2Seq2.SetTitleDiff("err ");
	analysis2Seq2.SetBlockSize(8);
	analysis2Seq2.SetBlocksPerLine(8);
	RB_FAIL(rbBITS_ON(60, 15), analysis2Seq2);
	RB_FAIL_V(rbvBITS_ON(60, 15), analysis2Seq2, 60);
}

RB_TEST(Fail_BitsAre)
{
	BriefAnalysisOfTwoSequences analysis_Mismatch(false, new TextExpression("(char)60"), new TextExpression("\"0##1 0101\""),
		"bits of ", " are ", "");
	analysis_Mismatch.SetString1   ("0011 1100");
	analysis_Mismatch.SetString2   ("0##1 0101");
	analysis_Mismatch.SetStringDiff("     X  X");
	analysis_Mismatch.SetTitle1("bits");
	analysis_Mismatch.SetTitle2("mask");
	analysis_Mismatch.SetTitleDiff("err ");
	analysis_Mismatch.SetBlockSize(1000);
	analysis_Mismatch.SetBlocksPerLine(1000);
    RB_FAIL(rbBITS_ARE((char)60, "0##1 0101"), analysis_Mismatch);
	RB_FAIL_V(rbvBITS_ARE((char)60, "0##1 0101"), analysis_Mismatch, 60);

	BriefAnalysisOfTwoSequences analysis_Mismatch_Sep(false, new TextExpression("(char)60"), new TextExpression("\"0:0,0.1 0-101\""),
		"bits of ", " are ", "");
	analysis_Mismatch_Sep.SetString1   ("0 0 1 1 1 100");
	analysis_Mismatch_Sep.SetString2   ("0:0,0.1 0-101");
	analysis_Mismatch_Sep.SetStringDiff("    X   X   X");
	analysis_Mismatch_Sep.SetTitle1("bits");
	analysis_Mismatch_Sep.SetTitle2("mask");
	analysis_Mismatch_Sep.SetTitleDiff("err ");
	analysis_Mismatch_Sep.SetBlockSize(1000);
	analysis_Mismatch_Sep.SetBlocksPerLine(1000);
    RB_FAIL(rbBITS_ARE((char)60, "0:0,0.1 0-101"), analysis_Mismatch_Sep);
	RB_FAIL_V(rbvBITS_ARE((char)60, "0:0,0.1 0-101"), analysis_Mismatch_Sep, 60);

	BriefAnalysisOfTwoSequences analysis_MatchAndMaskTooShort(false, new TextExpression("(char)60"), new TextExpression("\"0##1 110\""),
		"bits of ", " are ", "");
	analysis_MatchAndMaskTooShort.SetString1   ("0011 110");
	analysis_MatchAndMaskTooShort.SetString2   ("0##1 110");
	analysis_MatchAndMaskTooShort.SetStringDiff("        ");
	analysis_MatchAndMaskTooShort.SetTitle1("bits");
	analysis_MatchAndMaskTooShort.SetTitle2("mask");
	analysis_MatchAndMaskTooShort.SetTitleDiff("err ");
	analysis_MatchAndMaskTooShort.SetBlockSize(1000);
	analysis_MatchAndMaskTooShort.SetBlocksPerLine(1000);
	analysis_MatchAndMaskTooShort.SetEpilogue("not sufficient bits in mask");
	RB_FAIL(rbBITS_ARE((char)60, "0##1 110"), analysis_MatchAndMaskTooShort);
	RB_FAIL_V(rbvBITS_ARE((char)60, "0##1 110"), analysis_MatchAndMaskTooShort, 60);

	BriefAnalysisOfTwoSequences analysis_MismatchAndMaskTooShort(false, new TextExpression("(char)60"), new TextExpression("\"0##1 010\""),
		"bits of ", " are ", "");
	analysis_MismatchAndMaskTooShort.SetString1   ("0011 110");
	analysis_MismatchAndMaskTooShort.SetString2   ("0##1 010");
	analysis_MismatchAndMaskTooShort.SetStringDiff("     X  ");
	analysis_MismatchAndMaskTooShort.SetTitle1("bits");
	analysis_MismatchAndMaskTooShort.SetTitle2("mask");
	analysis_MismatchAndMaskTooShort.SetTitleDiff("err ");
	analysis_MismatchAndMaskTooShort.SetBlockSize(1000);
	analysis_MismatchAndMaskTooShort.SetBlocksPerLine(1000);
	analysis_MismatchAndMaskTooShort.SetEpilogue("not sufficient bits in mask");
	RB_FAIL(rbBITS_ARE((char)60, "0##1 010"), analysis_MismatchAndMaskTooShort);
	RB_FAIL_V(rbvBITS_ARE((char)60, "0##1 010"), analysis_MismatchAndMaskTooShort, 60);

	BriefAnalysisOfTwoSequences analysis_MatchAndMaskTooLong(false, new TextExpression("(char)60"), new TextExpression("\"0##1 11001\""),
		"bits of ", " are ", "");
	analysis_MatchAndMaskTooLong.SetString1   ("0011 1100");
	analysis_MatchAndMaskTooLong.SetString2   ("0##1 11001");
	analysis_MatchAndMaskTooLong.SetStringDiff("         ");
	analysis_MatchAndMaskTooLong.SetTitle1("bits");
	analysis_MatchAndMaskTooLong.SetTitle2("mask");
	analysis_MatchAndMaskTooLong.SetTitleDiff("err ");
	analysis_MatchAndMaskTooLong.SetBlockSize(1000);
	analysis_MatchAndMaskTooLong.SetBlocksPerLine(1000);
	analysis_MatchAndMaskTooLong.SetEpilogue("too many bits in mask");
	RB_FAIL(rbBITS_ARE((char)60, "0##1 11001"), analysis_MatchAndMaskTooLong);
	RB_FAIL_V(rbvBITS_ARE((char)60, "0##1 11001"), analysis_MatchAndMaskTooLong, 60);

	BriefAnalysisOfTwoSequences analysis_MismatchAndMaskTooLong(false, new TextExpression("(char)60"), new TextExpression("\"0##1 01011\""),
		"bits of ", " are ", "");
	analysis_MismatchAndMaskTooLong.SetString1   ("0011 1100");
	analysis_MismatchAndMaskTooLong.SetString2   ("0##1 01011");
	analysis_MismatchAndMaskTooLong.SetStringDiff("     X  X");
	analysis_MismatchAndMaskTooLong.SetTitle1("bits");
	analysis_MismatchAndMaskTooLong.SetTitle2("mask");
	analysis_MismatchAndMaskTooLong.SetTitleDiff("err ");
	analysis_MismatchAndMaskTooLong.SetBlockSize(1000);
	analysis_MismatchAndMaskTooLong.SetBlocksPerLine(1000);
	analysis_MismatchAndMaskTooLong.SetEpilogue("too many bits in mask");
	RB_FAIL(rbBITS_ARE((char)60, "0##1 01011"), analysis_MismatchAndMaskTooLong);
	RB_FAIL_V(rbvBITS_ARE((char)60, "0##1 01011"), analysis_MismatchAndMaskTooLong, 60);

	BriefAnalysisOfTwoSequences analysis_MismatchWithExtraSpace(false, new TextExpression("(char)60"), new TextExpression("\"0##1 0101 \""),
		"bits of ", " are ", "");
	analysis_MismatchWithExtraSpace.SetString1   ("0011 1100");
	analysis_MismatchWithExtraSpace.SetString2   ("0##1 0101 ");
	analysis_MismatchWithExtraSpace.SetStringDiff("     X  X");
	analysis_MismatchWithExtraSpace.SetTitle1("bits");
	analysis_MismatchWithExtraSpace.SetTitle2("mask");
	analysis_MismatchWithExtraSpace.SetTitleDiff("err ");
	analysis_MismatchWithExtraSpace.SetBlockSize(1000);
	analysis_MismatchWithExtraSpace.SetBlocksPerLine(1000);
	RB_FAIL(rbBITS_ARE((char)60, "0##1 0101 "), analysis_MismatchWithExtraSpace);
	RB_FAIL_V(rbvBITS_ARE((char)60, "0##1 0101 "), analysis_MismatchWithExtraSpace, 60);

	BriefAnalysisOfTwoSequences analysis_WithBadCharacter(false, new TextExpression("(char)60"), new TextExpression("\"0011 a101\""),
		"bits of ", " are ", "");
	analysis_WithBadCharacter.SetString1   ("0011 1100");
	analysis_WithBadCharacter.SetString2   ("0011 a101");
	analysis_WithBadCharacter.SetStringDiff("     E  X");
	analysis_WithBadCharacter.SetTitle1("bits");
	analysis_WithBadCharacter.SetTitle2("mask");
	analysis_WithBadCharacter.SetTitleDiff("err ");
	analysis_WithBadCharacter.SetBlockSize(1000);
	analysis_WithBadCharacter.SetBlocksPerLine(1000);
	analysis_WithBadCharacter.SetEpilogue("illegal character `a' in mask");
    RB_FAIL(rbBITS_ARE((char)60, "0011 a101"), analysis_WithBadCharacter);
	RB_FAIL_V(rbvBITS_ARE((char)60, "0011 a101"), analysis_WithBadCharacter, 60);
}
