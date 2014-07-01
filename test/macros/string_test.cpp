//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#if defined(_MSC_VER)
	#pragma warning(disable: 4786)
#endif

#include "richbool/richbool.hpp"
#include "richbool/stdstring.hpp"
#include "other_string.hpp"

#ifdef RICHBOOL_USE_WX
#include "richbool/wxstring.hpp"
#endif

#include "rbtest.hpp"
#include "testable_analysis_with_strings.hpp"
#include "testable_analysis_for_ranges.hpp"

using namespace RichBool;
using RichBool::detail::String;


#ifndef RICHBOOL_USE_WX


///////////////////////////////////////////////////////////
// function ToString

RB_TEST(Ordinary_String)
{
	String str1 = "abc";
	String str2 = ToString(str1);
	RB_ASSERT(rbEQUAL(str2, "abc"));
}

RB_TEST(String_With_EscapedCharacters)
{
	String str1 = "a\tc\xf0";
	String str2 = ToString(str1);
	RB_ASSERT(rbEQUAL(str2, "a\\tc\\xf0"));
}


///////////////////////////////////////////////////////////
// StringCompare

RB_TEST(StringCompare_Equal_Pass)
{
	std::string str = "abc";
	RB_PASS(rbSTRING("abc", ==, "abc", StringCompare()));
	RB_PASS(rbSTRING(str,   ==, "abc", StringCompare()));
	RB_PASS(rbSTRING("abc", ==, str,   StringCompare()));
	RB_PASS(rbSTRING(str,   ==, str,   StringCompare()));

	RB_PASS_V(rbvSTRING("abc", ==, "abc", StringCompare()), str);
	RB_PASS_V(rbvSTRING(str,   ==, "abc", StringCompare()), str);
	RB_PASS_V(rbvSTRING("abc", ==, str,   StringCompare()), str);
	RB_PASS_V(rbvSTRING(str,   ==, str,   StringCompare()), str);

	RB_PASS(rbSTRCMP("abc", ==, "abc"));
	RB_PASS_V(rbvSTRCMP("abc", ==, "abc"), str);

	RB_PASS(rbSTD_STRING(str, ==, str));
	RB_PASS_V(rbvSTD_STRING(str, ==, str), str);
}

RB_TEST(StringCs_Equal_Pass)
{
	std::string str = "abc";
	RB_PASS(rbSTRING_CS("abc", ==, "abc"));
	RB_PASS_V(rbvSTRING_CS("abc", ==, "abc"), str);
}

RB_TEST(StringCompare_Equal_Fail_FirstIsNullPointer)
{
	if (RichBoolTest::GetLevel()<2)
		return;

	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue).expr("sz1", ":")("\\NULL", false)
			(" == ").expr("sz2", ":")("abc", true)(" (strcmp)");

	const char *sz1=0, *sz2="abc";
	RB_FAIL(rbSTRING(sz1, ==, sz2, StringCompare()), *an);
}

RB_TEST(StringCompare_Equal_Fail_SecondIsNullPointer)
{
	if (RichBoolTest::GetLevel()<2)
		return;

	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue).expr("sz1", ":")("abc", true)
			(" == ").expr("sz2", ":")("\\NULL", false)(" (strcmp)");

	const char *sz1="abc", *sz2=0;
	RB_FAIL(rbSTRING(sz1, ==, sz2, StringCompare()), *an);
}

RB_TEST(StringCompare_Equal_Fail_BothNullPointers)
{
	if (RichBoolTest::GetLevel()<2)
		return;

	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue).expr("sz1", ":")("\\NULL", false)
			(" == ").expr("sz2", ":")("\\NULL", false)(" (strcmp)");

	const char *sz1=0, *sz2=0;
	RB_FAIL(rbSTRING(sz1, ==, sz2, StringCompare()), *an);
}

RB_TEST(StringCompare_Equal_Fail)
{
	TestableAnalysisOfStrings an("abce", "abde", "\"abce\"", "\"abde\"", "MMXM", " == ", "strcmp");
	RB_FAIL(rbSTRING("abce", ==, "abde", StringCompare()), an);
	RB_FAIL(rbSTRCMP("abce", ==, "abde"), an);
}

RB_TEST(StringCs_Equal_Fail)
{
    detail::String str = "abce";
	TestableAnalysisOfStrings an("abce", "abCe", "\"abce\"", "\"abCe\"", "MMXM", " == ", "strcmp");
	RB_FAIL(rbSTRING_CS("abce", ==, "abCe"), an);
	RB_FAIL_V(rbvSTRING_CS("abce", ==, "abCe"), an, str);
}

RB_TEST(StringCompare_Less_Pass)
{
	RB_PASS(rbSTRING("abc", <, "abd", StringCompare()));
	RB_PASS(rbSTRCMP("abc", <, "abd"));
}

#ifndef RICHBOOL_USE_WX
RB_TEST(StringCompare_With_OtherString)
{
	other_string<char> str1 = "abc", str2 = "abc";
	RB_PASS(rbSTRING(str1,  ==, str2,  StringCompare()));
	RB_PASS(rbSTRING(str1,  ==, "abc", StringCompare()));
	RB_PASS(rbSTRING("abc", ==, str1,  StringCompare()));
}
#endif

///////////////////////////////////////////////////////////
// StringCompareToUpper

RB_TEST(StringCompareToUpper_Equal_Pass)
{
	std::string str = "abc";
	RB_PASS(rbSTRING("abc", ==, "ABC", StringCompareToUpper()));
	RB_PASS(rbSTRING(str,   ==, "ABC", StringCompareToUpper()));
	RB_PASS(rbSTRING("ABC", ==, str,   StringCompareToUpper()));
	RB_PASS(rbSTRING(str,   ==, str,   StringCompareToUpper()));
}

RB_TEST(StringCI_Equal_Pass)
{
	std::string str = "abc";
	RB_PASS(rbSTRING_CI("abc", ==, "ABC"));
	RB_PASS(rbSTRING_CI(str,   ==, "ABC"));
	RB_PASS(rbSTRING_CI("ABC", ==, str));
	RB_PASS(rbSTRING_CI(str,   ==, str));
	RB_PASS_V(rbvSTRING_CI(str,   ==, "ABC"), str);
}

RB_TEST(StringCompareToUpper_Equal_Fail)
{
	TestableAnalysisOfStrings an("abce", "ABDE", "\"abce\"", "\"ABDE\"", "MMXM", " == ", "strcmp toupper");
	RB_FAIL(rbSTRING("abce", ==, "ABDE", StringCompareToUpper()), an);
}

RB_TEST(StringCI_Equal_Fail)
{
	TestableAnalysisOfStrings an("abce", "ABDE", "\"abce\"", "\"ABDE\"", "MMXM", " == ", "strcmp toupper");
	RB_FAIL(rbSTRING_CI("abce", ==, "ABDE"), an);
}

RB_TEST(StringCompareToUpper_Less_Pass)
{
	RB_PASS(rbSTRING("abc", <, "ABD", StringCompareToUpper()));
	RB_PASS(rbSTRING("ABC", <, "abd", StringCompareToUpper()));
}

RB_TEST(StringCompareToUpper_With_OtherString)
{
	other_string<char> str1 = "ABC", str2 = "abc";
	RB_PASS(rbSTRING(str1,  ==, str2,  StringCompareToUpper()));
	RB_PASS(rbSTRING(str1,  ==, "abc", StringCompareToUpper()));
	RB_PASS(rbSTRING("abc", ==, str1,  StringCompareToUpper()));
}


///////////////////////////////////////////////////////////
// StringCompareToLower

RB_TEST(StringCompareToLower_Equal_Pass)
{
	std::string str = "abc";
	RB_PASS(rbSTRING("abc", ==, "ABC", StringCompareToLower()));
	RB_PASS(rbSTRING(str,   ==, "ABC", StringCompareToLower()));
	RB_PASS(rbSTRING("ABC", ==, str,   StringCompareToLower()));
	RB_PASS(rbSTRING(str,   ==, str,   StringCompareToLower()));
}

RB_TEST(StringCompareToLower_Equal_Fail)
{
	TestableAnalysisOfStrings an("abce", "ABDE", "\"abce\"", "\"ABDE\"", "MMXM", " == ", "strcmp tolower");
	RB_FAIL(rbSTRING("abce", ==, "ABDE", StringCompareToLower()), an);
}

RB_TEST(StringCompareToLower_Less_Pass)
{
	RB_PASS(rbSTRING("abc", <, "ABD", StringCompareToLower()));
	RB_PASS(rbSTRING("ABC", <, "abd", StringCompareToLower()));
}

RB_TEST(StringCompareToLower_With_OtherString)
{
	other_string<char> str1 = "ABC", str2 = "abc";
	RB_PASS(rbSTRING(str1,  ==, str2,  StringCompareToLower()));
	RB_PASS(rbSTRING(str1,  ==, "abc", StringCompareToLower()));
	RB_PASS(rbSTRING("abc", ==, str1,  StringCompareToLower()));
}


///////////////////////////////////////////////////////////
// Collate

RB_TEST(Collate_Equal_Pass)
{
	std::string str = "abc";
	RB_PASS(rbSTRING("abc", ==, "abc", Collate()));
	RB_PASS(rbSTRING(str,   ==, "abc", Collate()));
	RB_PASS(rbSTRING("abc", ==, str,   Collate()));
	RB_PASS(rbSTRING(str,   ==, str,   Collate()));
}


RB_TEST(Collate_Equal_Fail)
{
	TestableAnalysisOfStrings an("abc", "abd", "\"abc\"", "\"abd\"", "MMX", " == ", "locale C");
	RB_FAIL(rbSTRING("abc", ==, "abd", Collate()), an);
}

RB_TEST(Collate_Less_Pass)
{
	RB_PASS(rbSTRING("abc", <, "abd", Collate()));
}

RB_TEST(Collate_Less_Pass_With_Extra)
{
	RB_PASS(rbSTRING("abc", <, "abcd", Collate()));
}

RB_TEST(Collate_Less_Fail_When_More)
{
	TestableAnalysisOfStrings an("abcd", "abbd", "\"abcd\"", "\"abbd\"", "MMXM", " < ", "locale C");
	RB_FAIL(rbSTRING("abcd", <, "abbd", Collate()), an);
}

RB_TEST(Collate_Less_Fail_When_Equal)
{
	TestableAnalysisOfStrings an("abc", "abc", "\"abc\"", "\"abc\"", "MMM", " < ", "locale C");
	RB_FAIL(rbSTRING("abc", <, "abc", Collate()), an);
}

RB_TEST(Collate_Less_Fail_When_Extra)
{
	TestableAnalysisOfStrings an("abcd", "abc", "\"abcd\"", "\"abc\"", "MMM1", " < ", "locale C");
	RB_FAIL(rbSTRING("abcd", <, "abc", Collate()), an);
}

RB_TEST(Collate_LessOrEqual_Pass)
{
	RB_PASS(rbSTRING("abc", <=, "abc", Collate()));
	RB_PASS(rbSTRING("abc", <=, "abd", Collate()));
}

RB_TEST(Collate_LessOrEqual_Fail_When_More)
{
	TestableAnalysisOfStrings an("abdd", "abcd", "\"abdd\"", "\"abcd\"", "MMXM", " <= ", "locale C");
	RB_FAIL(rbSTRING("abdd", <=, "abcd", Collate()), an);
}

RB_TEST(Collate_LessOrEqual_Fail_When_Extra)
{
	TestableAnalysisOfStrings an("abcd", "abc", "\"abcd\"", "\"abc\"", "MMM1", " <= ", "locale C");
	RB_FAIL(rbSTRING("abcd", <=, "abc", Collate()), an);
}

RB_TEST(Collate_More_Pass)
{
	RB_PASS(rbSTRING("abd", >, "abc", Collate()));
}

RB_TEST(Collate_More_Fail_When_Less)
{
	TestableAnalysisOfStrings an("abc", "abd", "\"abc\"", "\"abd\"", "MMX", " > ", "locale C");
	RB_FAIL(rbSTRING("abc", >, "abd", Collate()), an);
}

RB_TEST(Collate_More_Fail_When_Equal)
{
	TestableAnalysisOfStrings an("abc", "abc", "\"abc\"", "\"abc\"", "MMM", " > ", "locale C");
	RB_FAIL(rbSTRING("abc", >, "abc", Collate()), an);
}

RB_TEST(Collate_MoreOrEqual_Pass)
{
	RB_PASS(rbSTRING("abc", >=, "abc", Collate()));
	RB_PASS(rbSTRING("abd", >=, "abc", Collate()));
}

RB_TEST(Collate_MoreOrEqual_Fail_When_Less)
{
	TestableAnalysisOfStrings an("abc", "abd", "\"abc\"", "\"abd\"", "MMX", " >= ", "locale C");
	RB_FAIL(rbSTRING("abc", >=, "abd", Collate()), an);
}

RB_TEST(Collate_Other_String_Equal_Pass)
{
	other_string<char> str1="abc", str2="abc";
	RB_PASS(rbSTRING(str1, ==, str2, Collate()));
}


//////////////////////////////////////////////////////////////////
// CollateToUpper

RB_TEST(ToUpper_Equal_Pass)
{
	RB_PASS(rbSTRING("abc", ==, "ABC", CollateToUpper()));
}

RB_TEST(ToUpper_Equal_Fail)
{
	TestableAnalysisOfStrings an("abc", "ABD", "\"abc\"", "\"ABD\"", "MMX",
		" == ", "locale C toupper");
	RB_FAIL(rbSTRING("abc", ==, "ABD", CollateToUpper()), an);
}

RB_TEST(ToUpper_Less_Pass)
{
	RB_PASS(rbSTRING("abc", <, "ABD", CollateToUpper()));
	RB_PASS(rbSTRING("ABC", <, "abd", CollateToUpper()));
}

RB_TEST(ToUpper_Less_Fail)
{
	TestableAnalysisOfStrings an("abd", "ABC", "\"abd\"", "\"ABC\"", "MMX",
		" < ", "locale C toupper");
	RB_FAIL(rbSTRING("abd", <, "ABC", CollateToUpper()), an);
}

RB_TEST(ToUpper_Less_Pass_With_Intermediaries)
{
	RB_PASS(rbSTRING("ab", <, "[]", CollateToUpper()));
	RB_PASS(rbSTRING("AB", <, "[]", CollateToUpper()));
}

RB_TEST(ToUpper_More_Pass)
{
	RB_PASS(rbSTRING("abd", >, "ABC", CollateToUpper()));
	RB_PASS(rbSTRING("ABD", >, "abc", CollateToUpper()));
}

RB_TEST(ToUpper_More_Pass_With_Intermediaries)
{
	RB_PASS(rbSTRING("[]", >, "ab", CollateToUpper()));
	RB_PASS(rbSTRING("[]", >, "AB", CollateToUpper()));
}

RB_TEST(CollateToUpper_Other_String_Equal_Pass)
{
	other_string<char> str1="abc", str2="ABC";
	RB_PASS(rbSTRING(str1, ==, str2, CollateToUpper()));
}


//////////////////////////////////////////////////////////////////
// CollateToLower

RB_TEST(ToLower_Equal_Pass)
{
	RB_PASS(rbSTRING("abc", ==, "ABC", CollateToLower()));
}

RB_TEST(ToLower_Equal_Fail)
{
	TestableAnalysisOfStrings an("abc", "ABD", "\"abc\"", "\"ABD\"", "MMX",
		" == ", "locale C tolower");
	RB_FAIL(rbSTRING("abc", ==, "ABD", CollateToLower()), an);
}

RB_TEST(ToLower_Less_Pass)
{
	RB_PASS(rbSTRING("abc", <, "ABD", CollateToLower()));
	RB_PASS(rbSTRING("ABC", <, "abd", CollateToLower()));
}

RB_TEST(ToLower_Less_Fail)
{
	TestableAnalysisOfStrings an("abd", "ABC", "\"abd\"", "\"ABC\"", "MMX",
		" < ", "locale C tolower");
	RB_FAIL(rbSTRING("abd", <, "ABC", CollateToLower()), an);
}

RB_TEST(ToLower_Less_Pass_With_Intermediaries)
{
	RB_PASS(rbSTRING("[]", <, "ab", CollateToLower()));
	RB_PASS(rbSTRING("[]", <, "AB", CollateToLower()));
}

RB_TEST(ToLower_More_Pass)
{
	RB_PASS(rbSTRING("abd", >, "ABC", CollateToLower()));
	RB_PASS(rbSTRING("ABD", >, "abc", CollateToLower()));
}

RB_TEST(ToLower_More_Pass_With_Intermediaries)
{
	RB_PASS(rbSTRING("ab", >, "[]", CollateToLower()));
	RB_PASS(rbSTRING("AB", >, "[]", CollateToLower()));
}

RB_TEST(CollateToLower_Other_String_Equal_Pass)
{
	other_string<char> str1="abc", str2="ABC";
	RB_PASS(rbSTRING(str1, ==, str2, CollateToLower()));
}



///////////////////////////////////////////////////////////
// rbSTRING_BEGINS_WITH

RB_TEST(StringBeginsWith1_Pass)
{
	String str1="abcd", str2="a";
	RB_PASS(rbSTRING_BEGINS_WITH("abcd", "a", StringCompare()));
	RB_PASS(rbSTRING_BEGINS_WITH(str1, "a", StringCompare()));
	RB_PASS(rbSTRING_BEGINS_WITH("abcd", str2, StringCompare()));
	RB_PASS(rbSTRING_BEGINS_WITH(str1, str2, StringCompare()));

	RB_PASS_V(rbvSTRING_BEGINS_WITH(str1, str2, StringCompare()), str1);
}

RB_TEST(StringBeginsCs_Pass)
{
	String str1="abcd", str2="a";
	RB_PASS(rbSTRING_BEGINS_WITH_CS("abcd", "a"));
	RB_PASS(rbSTRING_BEGINS_WITH_CS(str1, "a"));
	RB_PASS(rbSTRING_BEGINS_WITH_CS("abcd", str2));
	RB_PASS(rbSTRING_BEGINS_WITH_CS(str1, str2));

	RB_PASS_V(rbvSTRING_BEGINS_WITH_CS(str1, str2), str1);
}

RB_TEST(StringBeginsWith2_Pass)
{
	RB_PASS(rbSTRING_BEGINS_WITH("abcd", "ab", StringCompare()));
}

RB_TEST(StringBeginsWithEmptyString)
{
	String str1="abcd", str2="";
	RB_PASS(rbSTRING_BEGINS_WITH("abcd", "", StringCompare()));
	RB_PASS(rbSTRING_BEGINS_WITH(str1, "", StringCompare()));
	RB_PASS(rbSTRING_BEGINS_WITH("abcd", str2, StringCompare()));
	RB_PASS(rbSTRING_BEGINS_WITH(str1, str2, StringCompare()));
}

RB_TEST(StringBeginsWith_ToUpper_Pass)
{
	RB_PASS(rbSTRING_BEGINS_WITH("abcd", "A", StringCompareToUpper()));
	RB_PASS(rbSTRING_BEGINS_WITH("abcd", "AB", StringCompareToUpper()));

	RB_PASS(rbSTRING_BEGINS_WITH("ABCD", "a", StringCompareToUpper()));
	RB_PASS(rbSTRING_BEGINS_WITH("ABCD", "ab", StringCompareToUpper()));
}

RB_TEST(StringBeginsWithCi_Pass)
{
	RB_PASS(rbSTRING_BEGINS_WITH_CI("abcd", "A"));
	RB_PASS(rbSTRING_BEGINS_WITH_CI("abcd", "AB"));

	RB_PASS(rbSTRING_BEGINS_WITH_CI("ABCD", "a"));
	RB_PASS(rbSTRING_BEGINS_WITH_CI("ABCD", "ab"));

    String str1="abcd";
	RB_PASS_V(rbvSTRING_BEGINS_WITH_CI(str1, "ab"), str1);
}

RB_TEST(StringBeginsWith_Fail)
{
	TestableAnalysisOfStrings an("abcd", "x", "\"abcd\"", "\"x\"", "XAAA",
		" begins with ", "strcmp");

	RB_FAIL(rbSTRING_BEGINS_WITH("abcd", "x", StringCompare()), an);
}

RB_TEST(StringBeginsWithCs_Fail)
{
	TestableAnalysisOfStrings an("abcd", "A", "\"abcd\"", "\"A\"", "XAAA",
		" begins with ", "strcmp");

	RB_FAIL(rbSTRING_BEGINS_WITH_CS("abcd", "A"), an);
	String str = "abcd";
	RB_FAIL_V(rbvSTRING_BEGINS_WITH_CS("abcd", "A"), an, str);
}

RB_TEST(StringBeginsWithCi_Fail)
{
	TestableAnalysisOfStrings an("abcd", "Ax", "\"abcd\"", "\"Ax\"", "MXAA",
		" begins with ", "strcmp toupper");

	RB_FAIL(rbSTRING_BEGINS_WITH_CI("abcd", "Ax"), an);
	String str = "abcd";
	RB_FAIL_V(rbvSTRING_BEGINS_WITH_CI("abcd", "Ax"), an, str);
}

RB_TEST(StringBeginsWith_FailFromSecond)
{
	TestableAnalysisOfStrings an("abcd", "ax", "\"abcd\"", "\"ax\"", "MXAA",
		" begins with ", "strcmp");

	RB_FAIL(rbSTRING_BEGINS_WITH("abcd", "ax", StringCompare()), an);
}

RB_TEST(StringBeginsWith_Fail_TooShort)
{
	TestableAnalysisOfStrings an("ab", "abcd", "\"ab\"", "\"abcd\"", "MM22",
		" begins with ", "strcmp");

	RB_FAIL(rbSTRING_BEGINS_WITH("ab", "abcd", StringCompare()), an);
}



///////////////////////////////////////////////////////////
// rbSTRING_ENDS_WITH

RB_TEST(StringEndsWith1_Pass)
{
	String str1="abcd", str2="d";
	RB_PASS(rbSTRING_ENDS_WITH("abcd", "d", StringCompare()));
	RB_PASS(rbSTRING_ENDS_WITH(str1, "d", StringCompare()));
	RB_PASS(rbSTRING_ENDS_WITH("abcd", str2, StringCompare()));
	RB_PASS(rbSTRING_ENDS_WITH(str1, str2, StringCompare()));

	RB_PASS_V(rbvSTRING_ENDS_WITH(str1, str2, StringCompare()), str1);
}

RB_TEST(StringEndsWithCs_Pass)
{
	String str1="abcd", str2="d";
	RB_PASS(rbSTRING_ENDS_WITH_CS("abcd", "d"));
	RB_PASS(rbSTRING_ENDS_WITH_CS(str1, "d"));
	RB_PASS(rbSTRING_ENDS_WITH_CS("abcd", str2));
	RB_PASS(rbSTRING_ENDS_WITH_CS(str1, str2));

	RB_PASS_V(rbvSTRING_ENDS_WITH_CS(str1, str2), str1);
}

RB_TEST(StringEndsWith2_Pass)
{
	RB_PASS(rbSTRING_ENDS_WITH("abcd", "cd", StringCompare()));
}

RB_TEST(StringEndsWithEmptyString)
{
	String str1="abcd", str2="";
	RB_PASS(rbSTRING_ENDS_WITH("abcd", "", StringCompare()));
	RB_PASS(rbSTRING_ENDS_WITH(str1, "", StringCompare()));
	RB_PASS(rbSTRING_ENDS_WITH("abcd", str2, StringCompare()));
	RB_PASS(rbSTRING_ENDS_WITH(str1, str2, StringCompare()));
}

RB_TEST(StringEndsWith_ToUpper_Pass)
{
	RB_PASS(rbSTRING_ENDS_WITH("abcd", "D", StringCompareToUpper()));
	RB_PASS(rbSTRING_ENDS_WITH("abcd", "CD", StringCompareToUpper()));
	RB_PASS(rbSTRING_ENDS_WITH("ABCD", "d", StringCompareToUpper()));
	RB_PASS(rbSTRING_ENDS_WITH("ABCD", "CD", StringCompareToUpper()));
}

RB_TEST(StringEndsWithCi_Pass)
{
	RB_PASS(rbSTRING_ENDS_WITH_CI("abcd", "D"));
	RB_PASS(rbSTRING_ENDS_WITH_CI("abcd", "CD"));
	RB_PASS(rbSTRING_ENDS_WITH_CI("ABCD", "d"));
	RB_PASS(rbSTRING_ENDS_WITH_CI("ABCD", "CD"));

    String str = "ABCD";
	RB_PASS_V(rbvSTRING_ENDS_WITH_CI("ABCD", "CD"), str);
}

RB_TEST(StringEndsWith_Fail)
{
	TestableAnalysisOfStrings an("abcd", "x", "\"abcd\"", "\"x\"", "AAAX",
		" ends with ", "strcmp");

	RB_FAIL(rbSTRING_ENDS_WITH("abcd", "x", StringCompare()), an);
}

RB_TEST(StringEndsWithCs_Fail)
{
	TestableAnalysisOfStrings an("abcd", "xd", "\"abcd\"", "\"xd\"", "AAXM",
		" ends with ", "strcmp");

    String str = "abcd";
	RB_FAIL(rbSTRING_ENDS_WITH_CS("abcd", "xd"), an);
	RB_FAIL_V(rbvSTRING_ENDS_WITH_CS("abcd", "xd"), an, str);
}

RB_TEST(StringEndsWithCi_Fail)
{
	TestableAnalysisOfStrings an("abcd", "xD", "\"abcd\"", "\"xD\"", "AAXM",
		" ends with ", "strcmp toupper");

    String str = "abcd";
	RB_FAIL(rbSTRING_ENDS_WITH_CI("abcd", "xD"), an);
	RB_FAIL_V(rbvSTRING_ENDS_WITH_CI("abcd", "xD"), an, str);
}

RB_TEST(StringEndsWith_FailFromSecond)
{
	TestableAnalysisOfStrings an("abcd", "xd", "\"abcd\"", "\"xd\"", "AAXM",
		" ends with ", "strcmp");

	RB_FAIL(rbSTRING_ENDS_WITH("abcd", "xd", StringCompare()), an);
}

RB_TEST(StringEndsWith_Fail_TooShortOneMatch)
{
	TestableAnalysisOfStrings an("a", "ba", "\"a\"", "\"ba\"", "2M",
		" ends with ", "strcmp");

	RB_FAIL(rbSTRING_ENDS_WITH("a", "ba", StringCompare()), an);
}

RB_TEST(StringEndsWith_Fail_TooShortNoMatch)
{
	TestableAnalysisOfStrings an("a", "bc", "\"a\"", "\"bc\"", "2X",
		" ends with ", "strcmp");

	RB_FAIL(rbSTRING_ENDS_WITH("a", "bc", StringCompare()), an);
}


///////////////////////////////////////////////////////////
// rbSTRING_CONTAINS

RB_TEST(StringContains1_Pass)
{
	String str1="abcd", str2="b";
	RB_PASS(rbSTRING_CONTAINS("abcd", "b", StringCompare()));
	RB_PASS(rbSTRING_CONTAINS(str1, "b", StringCompare()));
	RB_PASS(rbSTRING_CONTAINS("abcd", str2, StringCompare()));
	RB_PASS(rbSTRING_CONTAINS(str1, str2, StringCompare()));
}

RB_TEST(StringContainsCs_Pass)
{
	String str1="abcd", str2="b";
	RB_PASS(rbSTRING_CONTAINS_CS("abcd", "b"));
	RB_PASS(rbSTRING_CONTAINS_CS(str1, "b"));
	RB_PASS(rbSTRING_CONTAINS_CS("abcd", str2));
	RB_PASS(rbSTRING_CONTAINS_CS(str1, str2));
}

RB_TEST(StringContains2_Pass)
{
	RB_PASS(rbSTRING_CONTAINS("abcd", "bc", StringCompare()));
}

RB_TEST(StringContainsEmptyString)
{
	String str1="abcd", str2="";
	RB_PASS(rbSTRING_CONTAINS("abcd", "", StringCompare()));
	RB_PASS(rbSTRING_CONTAINS(str1, "", StringCompare()));
	RB_PASS(rbSTRING_CONTAINS("abcd", str2, StringCompare()));
	RB_PASS(rbSTRING_CONTAINS(str1, str2, StringCompare()));
}

RB_TEST(StringContains_ToUpper_Pass)
{
	RB_PASS(rbSTRING_CONTAINS("abcd", "B", StringCompareToUpper()));
	RB_PASS(rbSTRING_CONTAINS("abcd", "BC", StringCompareToUpper()));

	RB_PASS(rbSTRING_CONTAINS("ABCD", "b", StringCompareToUpper()));
	RB_PASS(rbSTRING_CONTAINS("ABCD", "bc", StringCompareToUpper()));
}

RB_TEST(StringContainsCi_Pass)
{
	RB_PASS(rbSTRING_CONTAINS_CI("abcd", "B"));
	RB_PASS(rbSTRING_CONTAINS_CI("abcd", "BC"));

	RB_PASS(rbSTRING_CONTAINS_CI("ABCD", "b"));
	RB_PASS(rbSTRING_CONTAINS_CI("ABCD", "bc"));
}

RB_TEST(StringContains_Fail)
{
	TestableAnalysisOfStrings an("abcd", "x", "\"abcd\"", "\"x\"", "XAAA",
		" contains ", "strcmp");

	RB_FAIL(rbSTRING_CONTAINS("abcd", "x", StringCompare()), an);
}

RB_TEST(StringContains_Fail_PartialMatch)
{
	TestableAnalysisOfStrings an("abcd", "xc", "\"abcd\"", "\"xc\"", "AXMA",
		" contains ", "strcmp");

	RB_FAIL(rbSTRING_CONTAINS("abcd", "xc", StringCompare()), an);
}

RB_TEST(StringContainsCs_PartialMatch)
{
	TestableAnalysisOfStrings an("abcd", "xc", "\"abcd\"", "\"xc\"", "AXMA",
		" contains ", "strcmp");

	RB_FAIL(rbSTRING_CONTAINS_CS("abcd", "xc"), an);
}

RB_TEST(StringContainsCi_PartialMatch)
{
	TestableAnalysisOfStrings an("abcd", "xC", "\"abcd\"", "\"xC\"", "AXMA",
		" contains ", "strcmp toupper");

	RB_FAIL(rbSTRING_CONTAINS_CI("abcd", "xC"), an);
}

RB_TEST(StringContains_Fail_TooShortOneMatch)
{
	TestableAnalysisOfStrings an("a", "ba", "\"a\"", "\"ba\"", "X2",
		" contains ", "strcmp");

	RB_FAIL(rbSTRING_CONTAINS("a", "ba", StringCompare()), an);
}

RB_TEST(StringContains_Fail_TooShortNoMatch)
{
	TestableAnalysisOfStrings an("a", "bc", "\"a\"", "\"bc\"", "X2",
		" contains ", "strcmp");

	RB_FAIL(rbSTRING_CONTAINS("a", "bc", StringCompare()), an);
}


RB_TEST(PartialMatchingOfStrings_CompareCompletely)
{
	std::string str1[] = { "abc", "def", "xyz" };
	std::string str2[] = { "ddf" };

	Analysis *arrAnalysis[] = {
		new Single(0, 2, "abc", new IndexExpression(0), true),
		new TestableAnalysisOfStrings("def", "ddf",
			new IndexExpression(1), new IndexExpression(0), "MXM",
			" == ", "strcmp"),
		new Single(0, 2, "xyz", new IndexExpression(2), true)
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"str1", "str2");
	analysis.AddAnalyses(arrAnalysis, 3);

	CompareStrings<CompareCompletely<StringCompare> > func;

	RB_FAIL(rbIN_ARRAYS(str1, str2, Compare<>().That(func)), analysis);
}

RB_TEST(PartialMatchingOfStrings_StringBeginsWith)
{
	std::string str1[] = { "abcddf", "defabcxyz", "xyzddf" };
	std::string str2[] = { "ddf" };

	Analysis *arrAnalysis[] = {
		new Single(0, 2, "abcddf", new IndexExpression(0), true),
		new TestableAnalysisOfStrings("defabcxyz", "ddf",
			new IndexExpression(1), new IndexExpression(0), "MXMAAAAAA",
			" begins with ", "strcmp"),
		new Single(0, 2, "xyzddf", new IndexExpression(2), true)
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"str1", "str2");
	analysis.AddAnalyses(arrAnalysis, 3);

	CompareStrings<StringBeginsWith<StringCompare> > func;

	RB_FAIL(rbIN_ARRAYS(str1, str2, Compare<>().That(func)), analysis);
}

RB_TEST(PartialMatchingOfStrings_StringEndsWith)
{
	std::string str1[] = { "ddfabc", "abcxyzdef", "ddfxyz" };
	std::string str2[] = { "ddf" };

	Analysis *arrAnalysis[] = {
		new Single(0, 2, "ddfabc", new IndexExpression(0), true),
		new TestableAnalysisOfStrings("abcxyzdef", "ddf",
			new IndexExpression(1), new IndexExpression(0), "AAAAAAMXM",
			" ends with ", "strcmp"),
		new Single(0, 2, "ddfxyz", new IndexExpression(2), true)
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"str1", "str2");
	analysis.AddAnalyses(arrAnalysis, 3);

	CompareStrings<StringEndsWith<StringCompare> > func;

	RB_FAIL(rbIN_ARRAYS(str1, str2, Compare<>().That(func)), analysis);
}

RB_TEST(PartialMatchingOfStrings_StringContains)
{
	std::string str1[] = { "abc", "abcdefxyz", "xyz" };
	std::string str2[] = { "ddf" };

	Analysis *arrAnalysis[] = {
		new Single(0, 2, "abc", new IndexExpression(0), true),
		new TestableAnalysisOfStrings("abcdefxyz", "ddf",
			new IndexExpression(1), new IndexExpression(0), "AAAMXMAAA",
			" contains ", "strcmp"),
		new Single(0, 2, "xyz", new IndexExpression(2), true)
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"str1", "str2");
	analysis.AddAnalyses(arrAnalysis, 3);

	CompareStrings<StringContains<StringCompare> > func;

	RB_FAIL(rbIN_ARRAYS(str1, str2, Compare<>().That(func)), analysis);
}


#else


///////////////////////////////////////////////////////////
// function ToString

RB_TEST(Ordinary_String)
{
	String str1 = "abc";
	String str2 = ToString(str1);
	RB_ASSERT(rbEQUAL(str2, "abc"));
}

RB_TEST(String_With_EscapedCharacters)
{
	String str1 = "a\tc\xf0";
	String str2 = ToString(str1);
	RB_ASSERT(rbEQUAL(str2, "a\\tc\\xf0"));
}


///////////////////////////////////////////////////////////
// WxStringCmp

RB_TEST(WxStringCmp_Equal_Pass)
{
	wxString str = "abc";
	RB_PASS(rbSTRING("abc", ==, "abc", WxStringCmp()));
	RB_PASS(rbSTRING(str,   ==, "abc", WxStringCmp()));
	RB_PASS(rbSTRING("abc", ==, str,   WxStringCmp()));
	RB_PASS(rbSTRING(str,   ==, str,   WxStringCmp()));

	RB_PASS(rbWX_STRING(str, ==, "abc"));
	RB_PASS(rbWX_STRING(str, ==, str));
}

RB_TEST(WxStringWxStringCmp_Equal_Fail)
{
	TestableAnalysisOfStrings an("abc", "abd", "\"abc\"", "\"abd\"", "MMX", " == ", "wxString::Cmp");
	RB_FAIL(rbSTRING("abc", ==, "abd", WxStringCmp()), an);
}

RB_TEST(WxStringWxStringCmp_Less_Pass)
{
	RB_PASS(rbSTRING("abc", <, "abd", WxStringCmp()));
}

RB_TEST(WxStringWxStringCmp_Less_Pass_With_Extra)
{
	RB_PASS(rbSTRING("abc", <, "abcd", WxStringCmp()));
}

RB_TEST(WxStringWxStringCmp_Less_Fail_When_More)
{
	TestableAnalysisOfStrings an("abcd", "abbd", "\"abcd\"", "\"abbd\"", "MMX ", " < ", "wxString::Cmp");
	RB_FAIL(rbSTRING("abcd", <, "abbd", WxStringCmp()), an);
}

RB_TEST(WxStringWxStringCmp_Less_Fail_When_Extra)
{
	TestableAnalysisOfStrings an("abcd", "abc", "\"abcd\"", "\"abc\"", "MMM1", " < ", "wxString::Cmp");
	RB_FAIL(rbSTRING("abcd", <, "abc", WxStringCmp()), an);
}

RB_TEST(WxStringWxStringCmp_Less_Fail_When_Equal)
{
	TestableAnalysisOfStrings an("abc", "abc", "\"abc\"", "\"abc\"", "MMM", " < ", "wxString::Cmp");
	RB_FAIL(rbSTRING("abc", <, "abc", WxStringCmp()), an);
}

RB_TEST(WxStringWxStringCmp_LessOrEqual_Pass)
{
	RB_PASS(rbSTRING("abc", <=, "abc", WxStringCmp()));
	RB_PASS(rbSTRING("abc", <=, "abd", WxStringCmp()));
}

RB_TEST(WxStringWxStringCmp_LessOrEqual_Fail_When_More)
{
	TestableAnalysisOfStrings an("abdd", "abcd", "\"abdd\"", "\"abcd\"", "MMX ", " <= ", "wxString::Cmp");
	RB_FAIL(rbSTRING("abdd", <=, "abcd", WxStringCmp()), an);
}

RB_TEST(WxStringWxStringCmp_LessOrEqual_Fail_When_Extra)
{
	TestableAnalysisOfStrings an("abcd", "abc", "\"abcd\"", "\"abc\"", "MMM1", " <= ", "wxString::Cmp");
	RB_FAIL(rbSTRING("abcd", <=, "abc", WxStringCmp()), an);
}

RB_TEST(WxStringWxStringCmp_More_Pass)
{
	RB_PASS(rbSTRING("abd", >, "abc", WxStringCmp()));
}

RB_TEST(WxStringWxStringCmp_More_Fail_When_Less)
{
	TestableAnalysisOfStrings an("abc", "abd", "\"abc\"", "\"abd\"", "MMX", " > ", "wxString::Cmp");
	RB_FAIL(rbSTRING("abc", >, "abd", WxStringCmp()), an);
}

RB_TEST(WxStringWxStringCmp_More_Fail_When_Equal)
{
	TestableAnalysisOfStrings an("abc", "abc", "\"abc\"", "\"abc\"", "MMM", " > ", "wxString::Cmp");
	RB_FAIL(rbSTRING("abc", >, "abc", WxStringCmp()), an);
}

RB_TEST(WxStringWxStringCmp_MoreOrEqual_Pass)
{
	RB_PASS(rbSTRING("abc", >=, "abc", WxStringCmp()));
	RB_PASS(rbSTRING("abd", >=, "abc", WxStringCmp()));
}

RB_TEST(WxStringWxStringCmp_MoreOrEqual_Fail_When_Less)
{
	TestableAnalysisOfStrings an("abc", "abd", "\"abc\"", "\"abd\"", "MMX", " >= ", "wxString::Cmp");
	RB_FAIL(rbSTRING("abc", >=, "abd", WxStringCmp()), an);
}


//////////////////////////////////////////////////////////////////
// WxStringCmpNoCase

RB_TEST(WxStringCmpNoCase_Equal_Pass)
{
	RB_PASS(rbSTRING("abc", ==, "ABC", WxStringCmpNoCase()));
}

RB_TEST(WxStringCmpNoCase_Equal_Fail)
{
	TestableAnalysisOfStrings an("abc", "ABD", "\"abc\"", "\"ABD\"", "MMX",
		" == ", "wxString::CmpNoCase");
	RB_FAIL(rbSTRING("abc", ==, "ABD", WxStringCmpNoCase()), an);
}

RB_TEST(WxStringCmpNoCase_Less_Pass)
{
	RB_PASS(rbSTRING("abc", <, "ABD", WxStringCmpNoCase()));
	RB_PASS(rbSTRING("ABC", <, "abd", WxStringCmpNoCase()));
}

RB_TEST(WxStringCmpNoCase_Less_Fail)
{
	TestableAnalysisOfStrings an("abdd", "ABCD", "\"abdd\"", "\"ABCD\"", "MMX ",
		" < ", "wxString::CmpNoCase");
	RB_FAIL(rbSTRING("abdd", <, "ABCD", WxStringCmpNoCase()), an);
}

RB_TEST(WxStringCmpNoCase_More_Pass)
{
	RB_PASS(rbSTRING("abd", >, "ABC", WxStringCmpNoCase()));
	RB_PASS(rbSTRING("ABD", >, "abc", WxStringCmpNoCase()));
}


///////////////////////////////////////////////////////////
// rbSTRING_BEGINS_WITH

RB_TEST(StringBeginsWith_Pass)
{
	RB_PASS(rbSTRING_BEGINS_WITH("abcd", "a", WxStringCmp()));
	RB_PASS(rbSTRING_BEGINS_WITH("abcd", "ab", WxStringCmp()));
}

RB_TEST(StringBeginsWithEmptyString)
{
	RB_PASS(rbSTRING_BEGINS_WITH("abcd", "", WxStringCmp()));
}

RB_TEST(StringBeginsWith_ToUpper_Pass)
{
	RB_PASS(rbSTRING_BEGINS_WITH("abcd", "A", WxStringCmpNoCase()));
	RB_PASS(rbSTRING_BEGINS_WITH("abcd", "AB", WxStringCmpNoCase()));

	RB_PASS(rbSTRING_BEGINS_WITH("ABCD", "a", WxStringCmpNoCase()));
	RB_PASS(rbSTRING_BEGINS_WITH("ABCD", "ab", WxStringCmpNoCase()));
}

RB_TEST(StringBeginsWith_Fail)
{
	TestableAnalysisOfStrings an("abcd", "x", "\"abcd\"", "\"x\"", "XAAA",
		" begins with ", "wxString::Cmp");

	RB_FAIL(rbSTRING_BEGINS_WITH("abcd", "x", WxStringCmp()), an);
}

RB_TEST(StringBeginsWith_FailFromSecond)
{
	TestableAnalysisOfStrings an("abcd", "ax", "\"abcd\"", "\"ax\"", "MXAA",
		" begins with ", "wxString::Cmp");

	RB_FAIL(rbSTRING_BEGINS_WITH("abcd", "ax", WxStringCmp()), an);
}

RB_TEST(StringBeginsWith_Fail_TooShort)
{
	TestableAnalysisOfStrings an("ab", "abcd", "\"ab\"", "\"abcd\"", "MM22",
		" begins with ", "wxString::Cmp");

	RB_FAIL(rbSTRING_BEGINS_WITH("ab", "abcd", WxStringCmp()), an);
}


///////////////////////////////////////////////////////////
// rbSTRING_CONTAINS

RB_TEST(StringContains1_Pass)
{
	String str1="abcd", str2="b";
	RB_PASS(rbSTRING_CONTAINS("abcd", "b", WxStringCmp()));
	RB_PASS(rbSTRING_CONTAINS(str1, "b", WxStringCmp()));
	RB_PASS(rbSTRING_CONTAINS("abcd", str2, WxStringCmp()));
	RB_PASS(rbSTRING_CONTAINS(str1, str2, WxStringCmp()));
}

RB_TEST(StringContains2_Pass)
{
	RB_PASS(rbSTRING_CONTAINS("abcd", "bc", WxStringCmp()));
}

RB_TEST(StringContainsEmptyString)
{
	String str1="abcd", str2="";
	RB_PASS(rbSTRING_CONTAINS("abcd", "", WxStringCmp()));
	RB_PASS(rbSTRING_CONTAINS(str1, "", WxStringCmp()));
	RB_PASS(rbSTRING_CONTAINS("abcd", str2, WxStringCmp()));
	RB_PASS(rbSTRING_CONTAINS(str1, str2, WxStringCmp()));
}

RB_TEST(StringContains_ToUpper_Pass)
{
	RB_PASS(rbSTRING_CONTAINS("abcd", "B", WxStringCmpNoCase()));
	RB_PASS(rbSTRING_CONTAINS("abcd", "BC", WxStringCmpNoCase()));

	RB_PASS(rbSTRING_CONTAINS("ABCD", "b", WxStringCmpNoCase()));
	RB_PASS(rbSTRING_CONTAINS("ABCD", "bc", WxStringCmpNoCase()));
}

RB_TEST(StringContains_Fail)
{
	TestableAnalysisOfStrings an("abcd", "x", "\"abcd\"", "\"x\"", "XAAA",
		" contains ", "wxString::Cmp");

	RB_FAIL(rbSTRING_CONTAINS("abcd", "x", WxStringCmp()), an);
}

RB_TEST(StringContains_Fail_PartialMatch)
{
	TestableAnalysisOfStrings an("abcd", "xc", "\"abcd\"", "\"xc\"", "AXMA",
		" contains ", "wxString::Cmp");

	RB_FAIL(rbSTRING_CONTAINS("abcd", "xc", WxStringCmp()), an);
}

RB_TEST(StringContains_Fail_TooShortOneMatch)
{
	TestableAnalysisOfStrings an("a", "ba", "\"a\"", "\"ba\"", "X2",
		" contains ", "wxString::Cmp");

	RB_FAIL(rbSTRING_CONTAINS("a", "ba", WxStringCmp()), an);
}

RB_TEST(StringContains_Fail_TooShortNoMatch)
{
	TestableAnalysisOfStrings an("a", "bc", "\"a\"", "\"bc\"", "X2",
		" contains ", "wxString::Cmp");

	RB_FAIL(rbSTRING_CONTAINS("a", "bc", WxStringCmp()), an);
}


#endif // #ifndef RICHBOOL_USE_WX
