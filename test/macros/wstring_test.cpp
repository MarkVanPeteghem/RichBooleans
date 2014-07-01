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

#if defined(RICHBOOL_HAS_WSTRING)

#include "rbtest.hpp"
#include "testable_analysis_with_strings.hpp"

using namespace RichBool;
using RichBool::detail::String;
using RichBool::detail::WString;


///////////////////////////////////////////////////////////
// function ToString

RB_TEST(Ordinary_WString)
{
	WString str1 = L"abc";
	String str2 = ToString(str1);
	RB_ASSERT(rbEQUAL(str2, "abc"));
}

RB_TEST(WString_With_EscapedCharacters)
{
	WString str1 = L"a\tc\xf0ab";
	String str2 = ToString(str1);
	RB_ASSERT(rbEQUAL(str2, "a\\tc\\xf0ab"));
}


///////////////////////////////////////////////////////////
// WStringCompare

RB_TEST(WStringCompare_Equal_Pass)
{
	WString str = L"abc";
	RB_PASS(rbSTRING(L"abc", ==, L"abc", WStringCompare()));
	RB_PASS(rbSTRING(str,    ==, L"abc", WStringCompare()));
	RB_PASS(rbSTRING(L"abc", ==, str,    WStringCompare()));
	RB_PASS(rbSTRING(str,    ==, str,    WStringCompare()));
	RB_PASS_V(rbvSTRING(str,    ==, str,    WStringCompare()), str);
	RB_PASS(rbSTRING_CS(str, ==, str));
	RB_PASS_V(rbvSTRING_CS(str, ==, str), str);

	RB_PASS(rbWCSCMP(L"abc", ==, L"abc"));
	RB_PASS_V(rbvWCSCMP(L"abc", ==, L"abc"), str);

	RB_PASS(rbSTD_WSTRING(str, ==, str));
	RB_PASS_V(rbvSTD_WSTRING(str, ==, str), str);
}

RB_TEST(WStringCompare_Equal_Fail)
{
    std::wstring str = L"abce";
	TestableAnalysisOfWStrings
		an(L"abce", L"abCe", "L\"abce\"", "L\"abCe\"", "MMXM", " == ", "wcscmp");
	RB_FAIL(rbSTRING(L"abce", ==, L"abCe", WStringCompare()), an);
	RB_FAIL(rbSTRING_CS(L"abce", ==, L"abCe"), an);
	RB_FAIL_V(rbvSTRING_CS(L"abce", ==, L"abCe"), an, str);
	RB_FAIL(rbWCSCMP(L"abce", ==, L"abCe"), an);
	RB_FAIL_V(rbvWCSCMP(L"abce", ==, L"abCe"), an, WString(L"abce"));
}

RB_TEST(WStringCompare_Less_Pass)
{
	RB_PASS(rbSTRING(L"abc", <, L"abd", WStringCompare()));
	RB_PASS(rbWCSCMP(L"abc", <, L"abd"));
}

#if !defined(RICHBOOL_USE_WX) || !defined(_MSC_VER) || (_MSC_VER > 1300)
RB_TEST(WStringCompare_OtherString_Equal_Pass)
{
	std::basic_string<detail::wchar, std::char_traits<detail::wchar>, other_allocator<detail::wchar> >
		str = L"abc";
	RB_PASS(rbSTRING(str,    ==, L"abc", WStringCompare()));
	RB_PASS(rbSTRING(L"abc", ==, str,    WStringCompare()));
	RB_PASS(rbSTRING(str,    ==, str,    WStringCompare()));
}
#endif

RB_TEST(WStringBeginsCs_Pass)
{
	std::wstring str1=L"abcd", str2=L"a";
	RB_PASS(rbSTRING_BEGINS_WITH_CS(L"abcd", L"a"));
	RB_PASS(rbSTRING_BEGINS_WITH_CS(str1, L"a"));
	RB_PASS(rbSTRING_BEGINS_WITH_CS(L"abcd", str2));
	RB_PASS(rbSTRING_BEGINS_WITH_CS(str1, str2));

	RB_PASS_V(rbvSTRING_BEGINS_WITH_CS(str1, str2), str1);
}

RB_TEST(WStringBeginsWithCs_Fail)
{
	TestableAnalysisOfWStrings an(L"abcd", L"A", "L\"abcd\"", "L\"A\"", "XAAA",
		" begins with ", "wcscmp");

	RB_FAIL(rbSTRING_BEGINS_WITH_CS(L"abcd", L"A"), an);
	std::wstring str = L"abcd";
	RB_FAIL_V(rbvSTRING_BEGINS_WITH_CS(L"abcd", L"A"), an, str);
}

RB_TEST(WStringEndsWithCs_Pass)
{
	std::wstring str1=L"abcd", str2=L"d";
	RB_PASS(rbSTRING_ENDS_WITH_CS(L"abcd", L"d"));
	RB_PASS(rbSTRING_ENDS_WITH_CS(str1, L"d"));
	RB_PASS(rbSTRING_ENDS_WITH_CS(L"abcd", str2));
	RB_PASS(rbSTRING_ENDS_WITH_CS(str1, str2));

	RB_PASS_V(rbvSTRING_ENDS_WITH_CS(str1, str2), str1);
}

RB_TEST(WStringEndsWithCs_Fail)
{
	TestableAnalysisOfWStrings an(L"abcd", L"xd", "L\"abcd\"", "L\"xd\"", "AAXM",
		" ends with ", "wcscmp");

    std::wstring str = L"abcd";
	RB_FAIL(rbSTRING_ENDS_WITH_CS(L"abcd", L"xd"), an);
	RB_FAIL_V(rbvSTRING_ENDS_WITH_CS(L"abcd", L"xd"), an, str);
}

RB_TEST(WStringContainsCs_Pass)
{
	std::wstring str1=L"abcd", str2=L"b";
	RB_PASS(rbSTRING_CONTAINS_CS(L"abcd", L"b"));
	RB_PASS(rbSTRING_CONTAINS_CS(str1, L"b"));
	RB_PASS(rbSTRING_CONTAINS_CS(L"abcd", str2));
	RB_PASS(rbSTRING_CONTAINS_CS(str1, str2));
}

RB_TEST(WStringContainsCs_PartialMatch)
{
	TestableAnalysisOfWStrings an(L"abcd", L"xc", "L\"abcd\"", "L\"xc\"", "AXMA",
		" contains ", "wcscmp");

	RB_FAIL(rbSTRING_CONTAINS_CS(L"abcd", L"xc"), an);
}


///////////////////////////////////////////////////////////
// WStringCompareToUpper

RB_TEST(WStringCompareToUpper_Equal_Pass)
{
	WString str = L"abc";
	RB_PASS(rbSTRING(L"abc", ==, L"ABC", WStringCompareToUpper()));
	RB_PASS(rbSTRING(str,    ==, L"ABC", WStringCompareToUpper()));
	RB_PASS(rbSTRING(L"ABC", ==, str,    WStringCompareToUpper()));
	RB_PASS(rbSTRING(str,    ==, str,    WStringCompareToUpper()));
	RB_PASS(rbSTRING_CI(str, ==, str));
	RB_PASS_V(rbvSTRING_CI(str, ==, str), str);
}

RB_TEST(WStringCompareToUpper_Equal_Fail)
{
    std::wstring str = L"abce";
	TestableAnalysisOfWStrings
		an(L"abce", L"ABDE", "L\"abce\"", "L\"ABDE\"", "MMXM", " == ", "wcscmp toupper");
	RB_FAIL(rbSTRING(L"abce", ==, L"ABDE", WStringCompareToUpper()), an);
	RB_FAIL(rbSTRING_CI(L"abce", ==, L"ABDE"), an);
	RB_FAIL_V(rbvSTRING_CI(L"abce", ==, L"ABDE"), an, str);
}

RB_TEST(WStringCompareToUpper_Less_Pass)
{
	RB_PASS(rbSTRING(L"abc", <, L"ABD", WStringCompareToUpper()));
	RB_PASS(rbSTRING(L"ABC", <, L"abd", WStringCompareToUpper()));
}

RB_TEST(WStringBeginsWithCi_Pass)
{
	RB_PASS(rbSTRING_BEGINS_WITH_CI(L"abcd", L"A"));
	RB_PASS(rbSTRING_BEGINS_WITH_CI(L"abcd", L"AB"));

	RB_PASS(rbSTRING_BEGINS_WITH_CI(L"ABCD", L"a"));
	RB_PASS(rbSTRING_BEGINS_WITH_CI(L"ABCD", L"ab"));

    std::wstring str1=L"abcd";
	RB_PASS_V(rbvSTRING_BEGINS_WITH_CI(str1, L"ab"), str1);
}

RB_TEST(WStringBeginsWithCi_Fail)
{
	TestableAnalysisOfWStrings an(L"abcd", L"Ax", "L\"abcd\"", "L\"Ax\"", "MXAA",
		" begins with ", "wcscmp toupper");

	RB_FAIL(rbSTRING_BEGINS_WITH_CI(L"abcd", L"Ax"), an);
	std::wstring str = L"abcd";
	RB_FAIL_V(rbvSTRING_BEGINS_WITH_CI(L"abcd", L"Ax"), an, str);
}

RB_TEST(WStringEndsWithCi_Pass)
{
	RB_PASS(rbSTRING_ENDS_WITH_CI(L"abcd", L"D"));
	RB_PASS(rbSTRING_ENDS_WITH_CI(L"abcd", L"CD"));
	RB_PASS(rbSTRING_ENDS_WITH_CI(L"ABCD", L"d"));
	RB_PASS(rbSTRING_ENDS_WITH_CI(L"ABCD", L"CD"));

    std::wstring str = L"ABCD";
	RB_PASS_V(rbvSTRING_ENDS_WITH_CI(L"ABCD", L"CD"), str);
}

RB_TEST(WStringEndsWithCi_Fail)
{
	TestableAnalysisOfWStrings an(L"abcd", L"xD", "L\"abcd\"", "L\"xD\"", "AAXM",
		" ends with ", "wcscmp toupper");

    std::wstring str = L"abcd";
	RB_FAIL(rbSTRING_ENDS_WITH_CI(L"abcd", L"xD"), an);
	RB_FAIL_V(rbvSTRING_ENDS_WITH_CI(L"abcd", L"xD"), an, str);
}

RB_TEST(WStringContainsCi_Pass)
{
	RB_PASS(rbSTRING_CONTAINS_CI(L"abcd", L"B"));
	RB_PASS(rbSTRING_CONTAINS_CI(L"abcd", L"BC"));

	RB_PASS(rbSTRING_CONTAINS_CI(L"ABCD", L"b"));
	RB_PASS(rbSTRING_CONTAINS_CI(L"ABCD", L"bc"));
}

RB_TEST(WStringContainsCi_PartialMatch)
{
	TestableAnalysisOfWStrings an(L"abcd", L"xC", "L\"abcd\"", "L\"xC\"", "AXMA",
		" contains ", "wcscmp toupper");

	RB_FAIL(rbSTRING_CONTAINS_CI(L"abcd", L"xC"), an);
}


///////////////////////////////////////////////////////////
// WStringCompareToLower

RB_TEST(WStringCompareToLower_Equal_Pass)
{
	WString str = L"abc";
	RB_PASS(rbSTRING(L"abc", ==, L"ABC", WStringCompareToLower()));
	RB_PASS(rbSTRING(str,    ==, L"ABC", WStringCompareToLower()));
	RB_PASS(rbSTRING(L"ABC", ==, str,    WStringCompareToLower()));
	RB_PASS(rbSTRING(str,    ==, str,    WStringCompareToLower()));
}

RB_TEST(WStringCompareToLower_Equal_Fail)
{
	TestableAnalysisOfWStrings
		an(L"abce", L"ABDE", "L\"abce\"", "L\"ABDE\"", "MMXM", " == ", "wcscmp tolower");
	RB_FAIL(rbSTRING(L"abce", ==, L"ABDE", WStringCompareToLower()), an);
}

RB_TEST(WStringCompareToLower_Less_Pass)
{
	RB_PASS(rbSTRING(L"abc", <, L"ABD", WStringCompareToLower()));
	RB_PASS(rbSTRING(L"ABC", <, L"abd", WStringCompareToLower()));
}


#define CHECK_WCOLLATE \
	try { \
		WCollate wcollate; \
	} \
	catch (...) { \
		print_warning("Can't do wide character collation", __FILE__, __LINE__); \
		return; \
	}

#define CHECK_WCOLLATE_QUIET \
	try { \
		WCollate wcollate; \
	} \
	catch (...) { \
		return; \
	}

///////////////////////////////////////////////////////////
// WCollate

RB_TEST(WCollate_Equal_Pass)
{
	// The next line may print a warning on some systems if wide character
	// collation is not possible.
	// You can still use all the other functionality of Rich Booleans.
	// This also applies to the remaining tests,
	// but the warning is printed only once per richbool level.
	CHECK_WCOLLATE;

	WString str = L"abc";
	RB_PASS(rbSTRING(L"abc", ==, L"abc", WCollate()));
	RB_PASS(rbSTRING(str,    ==, L"abc", WCollate()));
	RB_PASS(rbSTRING(L"abc", ==, str,    WCollate()));
	RB_PASS(rbSTRING(str,    ==, str,    WCollate()));
}

RB_TEST(WCollate_Equal_Fail)
{
	CHECK_WCOLLATE_QUIET;

	TestableAnalysisOfWStrings
		an(L"abc", L"abd", "L\"abc\"", "L\"abd\"", "MMX", " == ", "locale C");
	RB_FAIL(rbSTRING(L"abc", ==, L"abd", WCollate()), an);
}

RB_TEST(WCollate_Less_Pass)
{
	CHECK_WCOLLATE_QUIET;

	RB_PASS(rbSTRING(L"abc", <, L"abd", WCollate()));
}

RB_TEST(WCollate_Less_Pass_With_Extra)
{
	CHECK_WCOLLATE_QUIET;

	RB_PASS(rbSTRING(L"abc", <, L"abcd", WCollate()));
}

RB_TEST(WCollate_Less_Fail_When_More)
{
	CHECK_WCOLLATE_QUIET;

	TestableAnalysisOfWStrings an(L"abcd", L"abbd",
		"L\"abcd\"", "L\"abbd\"",
		"MMXM", " < ", "locale C");

	RB_FAIL(rbSTRING(L"abcd", <, L"abbd", WCollate()), an);
}

RB_TEST(WCollate_Less_Fail_When_Extra)
{
	CHECK_WCOLLATE_QUIET;

	TestableAnalysisOfWStrings an(L"abcd", L"abc",
		"L\"abcd\"", "L\"abc\"",
		"MMM1", " < ", "locale C");
	RB_FAIL(rbSTRING(L"abcd", <, L"abc", WCollate()), an);
}

RB_TEST(WCollate_Less_Fail_When_Equal)
{
	CHECK_WCOLLATE_QUIET;

	TestableAnalysisOfWStrings
		an(L"abc", L"abc", "L\"abc\"", "L\"abc\"", "MMM", " < ", "locale C");
	RB_FAIL(rbSTRING(L"abc", <, L"abc", WCollate()), an);
}

RB_TEST(WCollate_LessOrEqual_Pass)
{
	CHECK_WCOLLATE_QUIET;

	RB_PASS(rbSTRING(L"abc", <=, L"abc", WCollate()));
	RB_PASS(rbSTRING(L"abc", <=, L"abd", WCollate()));
}

RB_TEST(WCollate_LessOrEqual_Fail_When_More)
{
	CHECK_WCOLLATE_QUIET;

	TestableAnalysisOfWStrings
		an(L"abdd", L"abcd", "L\"abdd\"", "L\"abcd\"", "MMXM", " <= ", "locale C");
	RB_FAIL(rbSTRING(L"abdd", <=, L"abcd", WCollate()), an);
}

RB_TEST(WCollate_LessOrEqual_Fail_When_Extra)
{
	CHECK_WCOLLATE_QUIET;

	TestableAnalysisOfWStrings
		an(L"abcd", L"abc", "L\"abcd\"", "L\"abc\"", "MMM1", " <= ", "locale C");
	RB_FAIL(rbSTRING(L"abcd", <=, L"abc", WCollate()), an);
}

RB_TEST(WCollate_More_Pass)
{
	CHECK_WCOLLATE_QUIET;

	RB_PASS(rbSTRING(L"abd", >, L"abc", WCollate()));
}

RB_TEST(WCollate_More_Fail_When_Less)
{
	CHECK_WCOLLATE_QUIET;

	TestableAnalysisOfWStrings
		an(L"abc", L"abd", "L\"abc\"", "L\"abd\"", "MMX", " > ", "locale C");
	RB_FAIL(rbSTRING(L"abc", >, L"abd", WCollate()), an);
}

RB_TEST(WCollate_More_Fail_When_Equal)
{
	CHECK_WCOLLATE_QUIET;

	TestableAnalysisOfWStrings
		an(L"abc", L"abc", "L\"abc\"", "L\"abc\"", "MMM", " > ", "locale C");
	RB_FAIL(rbSTRING(L"abc", >, L"abc", WCollate()), an);
}

RB_TEST(WCollate_MoreOrEqual_Pass)
{
	CHECK_WCOLLATE_QUIET;

	RB_PASS(rbSTRING(L"abc", >=, L"abc", WCollate()));
	RB_PASS(rbSTRING(L"abd", >=, L"abc", WCollate()));
}

RB_TEST(WCollate_MoreOrEqual_Fail_When_Less)
{
	CHECK_WCOLLATE_QUIET;

	TestableAnalysisOfWStrings
		an(L"abc", L"abd", "L\"abc\"", "L\"abd\"", "MMX", " >= ", "locale C");
	RB_FAIL(rbSTRING(L"abc", >=, L"abd", WCollate()), an);
}


//////////////////////////////////////////////////////////////////
// WCollateToUpper

RB_TEST(WCollateToUpper_Equal_Pass)
{
	CHECK_WCOLLATE_QUIET;

	RB_PASS(rbSTRING(L"abc", ==, L"ABC", WCollateToUpper()));
}

RB_TEST(WCollateToUpper_Equal_Fail)
{
	CHECK_WCOLLATE_QUIET;

	TestableAnalysisOfWStrings an(L"abc", L"ABD", "L\"abc\"", "L\"ABD\"", "MMX",
		" == ", "locale C toupper");
	RB_FAIL(rbSTRING(L"abc", ==, L"ABD", WCollateToUpper()), an);
}

RB_TEST(WCollateToUpper_Less_Pass)
{
	CHECK_WCOLLATE_QUIET;

	RB_PASS(rbSTRING(L"abc", <, L"ABD", WCollateToUpper()));
	RB_PASS(rbSTRING(L"ABC", <, L"abd", WCollateToUpper()));
}

RB_TEST(WCollateToUpper_Less_Fail)
{
	CHECK_WCOLLATE_QUIET;

	TestableAnalysisOfWStrings an(L"abd", L"ABC", "L\"abd\"", "L\"ABC\"", "MMX",
		" < ", "locale C toupper");
	RB_FAIL(rbSTRING(L"abd", <, L"ABC", WCollateToUpper()), an);
}

RB_TEST(WCollateToUpper_Less_Pass_With_Intermediaries)
{
	CHECK_WCOLLATE_QUIET;

	RB_PASS(rbSTRING(L"ab", <, L"[]", WCollateToUpper()));
	RB_PASS(rbSTRING(L"AB", <, L"[]", WCollateToUpper()));
}

RB_TEST(WCollateToUpper_More_Pass)
{
	CHECK_WCOLLATE_QUIET;

	RB_PASS(rbSTRING(L"abd", >, L"ABC", WCollateToUpper()));
	RB_PASS(rbSTRING(L"ABD", >, L"abc", WCollateToUpper()));
}

RB_TEST(WCollateToUpper_More_Pass_With_Intermediaries)
{
	CHECK_WCOLLATE_QUIET;

	RB_PASS(rbSTRING(L"[]", >, L"ab", WCollateToUpper()));
	RB_PASS(rbSTRING(L"[]", >, L"AB", WCollateToUpper()));
}


//////////////////////////////////////////////////////////////////
// WCollateToLower

RB_TEST(WCollateToLower_Equal_Pass)
{
	CHECK_WCOLLATE_QUIET;

	RB_PASS(rbSTRING(L"abc", ==, L"ABC", WCollateToLower()));
}

RB_TEST(WCollateToLower_Equal_Fail)
{
	CHECK_WCOLLATE_QUIET;

	TestableAnalysisOfWStrings an(L"abc", L"ABD", "L\"abc\"", "L\"ABD\"", "MMX",
		" == ", "locale C tolower");
	RB_FAIL(rbSTRING(L"abc", ==, L"ABD", WCollateToLower()), an);
}

RB_TEST(WCollateToLower_Less_Pass)
{
	CHECK_WCOLLATE_QUIET;

	RB_PASS(rbSTRING(L"abc", <, L"ABD", WCollateToLower()));
	RB_PASS(rbSTRING(L"ABC", <, L"abd", WCollateToLower()));
}

RB_TEST(WCollateToLower_Less_Fail)
{
	CHECK_WCOLLATE_QUIET;

	TestableAnalysisOfWStrings an(L"abd", L"ABC", "L\"abd\"", "L\"ABC\"", "MMX",
		" < ", "locale C tolower");
	RB_FAIL(rbSTRING(L"abd", <, L"ABC", WCollateToLower()), an);
}

RB_TEST(WCollateToLower_Less_Pass_With_Intermediaries)
{
	CHECK_WCOLLATE_QUIET;

	RB_PASS(rbSTRING(L"[]", <, L"ab", WCollateToLower()));
	RB_PASS(rbSTRING(L"[]", <, L"AB", WCollateToLower()));
}

RB_TEST(WCollateToLower_More_Pass)
{
	CHECK_WCOLLATE_QUIET;

	RB_PASS(rbSTRING(L"abd", >, L"ABC", WCollateToLower()));
	RB_PASS(rbSTRING(L"ABD", >, L"abc", WCollateToLower()));
}

RB_TEST(WCollateToLower_More_Pass_With_Intermediaries)
{
	CHECK_WCOLLATE_QUIET;

	RB_PASS(rbSTRING(L"ab", >, L"[]", WCollateToLower()));
	RB_PASS(rbSTRING(L"AB", >, L"[]", WCollateToLower()));
}

#endif
