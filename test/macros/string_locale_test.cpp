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

#include "rbtest.hpp"
#include "testable_analysis_with_strings.hpp"

using namespace RichBool;

// Note: many of these tests fail with VC 6.0, even if the French
//       locale is on your system. That's why they're excluded
//       for that compiler:
#if (!defined(_MSC_VER) || (_MSC_VER>1200)) && !defined(RICHBOOL_USE_WX)


// These two macros check if a locale is present:
#define CHECK_LOCALE(localeName) \
	try { \
		 std::locale loc(localeName); \
	} \
	catch (...) { \
		print_warning("Can't use locale " localeName, \
			__FILE__, __LINE__); \
		return; \
	}

#define CHECK_LOCALE_QUIET(localeName) \
	try { \
		 std::locale loc(localeName); \
	} \
	catch (...) { \
		return; \
	}

///////////////////////////////////////////////////////////
// Collate

RB_TEST(Collate_Equal_C_Pass)
{
	CHECK_LOCALE("C");
	std::locale localeC("C");
	std::string str = "abc";
	RB_PASS(rbSTRING(str, ==, "abc", Collate(localeC)));
}

RB_TEST(Collate_Equal_French_Pass)
{
	// If you don't have the French locale on your system,
	// the next test will print a warning and stop this test.
	// This also applies to the remaining tests,
	// but the warning is printed only once per richbool level.
	CHECK_LOCALE("fr");
	std::locale localeFR("fr");
	std::string str = "abc";
	RB_PASS(rbSTRING(str, ==, "abc", Collate(localeFR)));
}

RB_TEST(Collate_Equal_French_Fail)
{
	CHECK_LOCALE_QUIET("fr");
	std::locale localeFR("fr");
	std::string info = "locale "+localeFR.name();

	TestableAnalysisOfStrings
		an("abce", "abde", "\"abce\"", "\"abde\"", "MMXM", " == ", info.c_str());

	RB_FAIL(rbSTRING("abce", ==, "abde", Collate(localeFR)), an);
}

RB_TEST(Collate_Less_French_Pass)
{
	CHECK_LOCALE_QUIET("fr");
	std::locale localeFR("fr");
	RB_PASS(rbSTRING("ed", <, "eé", Collate(localeFR)));
	RB_PASS(rbSTRING("eé", <, "ef", Collate(localeFR)));
}

RB_TEST(Collate_Less_French_Pass_With_Ignored_Character)
{
	CHECK_LOCALE_QUIET("fr");
	std::locale localeFR("fr");
	RB_PASS(rbSTRING("ab", <, "a-c", Collate(localeFR)));
	RB_PASS(rbSTRING("a-b", <, "ac", Collate(localeFR)));
}

RB_TEST(Collate_Less_French_Fail_When_More_With_Ignored_Character)
{
	CHECK_LOCALE_QUIET("fr");
	std::locale localeFR("fr");
	std::string info = "locale "+localeFR.name();

	TestableAnalysisOfStrings
		an1("a-c", "ab", "\"a-c\"", "\"ab\"", "MM1", " < ", info.c_str());
	RB_FAIL(rbSTRING("a-c", <, "ab", Collate(localeFR)), an1);

	TestableAnalysisOfStrings
		an2("ac", "a-b", "\"ac\"", "\"a-b\"", "MX2", " < ", info.c_str());
	RB_FAIL(rbSTRING("ac", <, "a-b", Collate(localeFR)), an2);
}

RB_TEST(Collate_LessOrEqual_French_Fail_When_More_With_Ignored_Character)
{
	CHECK_LOCALE_QUIET("fr");
	std::locale localeFR("fr");
	std::string info = "locale "+localeFR.name();

	TestableAnalysisOfStrings
		an1("a-c", "ab", "\"a-c\"", "\"ab\"", "MM1", " <= ", info.c_str());
	RB_FAIL(rbSTRING("a-c", <=, "ab", Collate(localeFR)), an1);

	TestableAnalysisOfStrings
		an2("ac", "a-b", "\"ac\"", "\"a-b\"", "MX2", " <= ", info.c_str());
	RB_FAIL(rbSTRING("ac", <=, "a-b", Collate(localeFR)), an2);
}

RB_TEST(Collate_Less_French_Fail_When_Equal_With_Ignored_Character)
{
	CHECK_LOCALE_QUIET("fr");
	std::locale localeFR("fr");
	std::string info = "locale "+localeFR.name();

	TestableAnalysisOfStrings
		an1("a-c", "ac", "\"a-c\"", "\"ac\"", "MM1", " < ", info.c_str());
	RB_FAIL(rbSTRING("a-c", <, "ac", Collate(localeFR)), an1);
}


///////////////////////////////////////////////////////////
// CollateToUpper

RB_TEST(CollateToUpper_Equal_French_Pass)
{
	CHECK_LOCALE_QUIET("fr");
	std::locale localeFR("fr");
	RB_PASS(rbSTRING("ABÉ", ==, "abé", CollateToUpper(localeFR)));
}

RB_TEST(CollateToUpper_Less_French_Pass)
{
	CHECK_LOCALE_QUIET("fr");
	std::locale localeFR("fr");

	RB_PASS(rbSTRING("ABD", <, "abé", CollateToUpper(localeFR)));
	RB_PASS(rbSTRING("ABÉ", <, "abf", CollateToUpper(localeFR)));

	RB_PASS(rbSTRING("abd", <, "ABÉ", CollateToUpper(localeFR)));
	RB_PASS(rbSTRING("abé", <, "ABF", CollateToUpper(localeFR)));
}


///////////////////////////////////////////////////////////
// CollateToLower

RB_TEST(CollateToLower_Equal_French_Pass)
{
	CHECK_LOCALE_QUIET("fr");
	std::locale localeFR("fr");
	RB_PASS(rbSTRING("ABÉ", ==, "abé", CollateToLower(localeFR)));
}

RB_TEST(CollateToLower_Less_French_Pass)
{
	CHECK_LOCALE_QUIET("fr");
	std::locale localeFR("fr");

	RB_PASS(rbSTRING("ABD", <, "abé", CollateToLower(localeFR)));
	RB_PASS(rbSTRING("ABÉ", <, "abf", CollateToLower(localeFR)));

	RB_PASS(rbSTRING("abd", <, "ABÉ", CollateToLower(localeFR)));
	RB_PASS(rbSTRING("abé", <, "ABF", CollateToLower(localeFR)));
}

#endif
