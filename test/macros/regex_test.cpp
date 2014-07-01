//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/richbool.hpp"

#ifdef RICHBOOL_REGEX

#include "richbool/regexp.hpp"
#include "richbool/containers.hpp"
#include "testable_analysis_for_ranges.hpp"
#include "testable_analysis_with_strings.hpp"

namespace RichBool
{
namespace detail
{
	template <typename charT>
	bool operator==(const RegexPart<charT>& First, const RegexPart<charT>& Second)
	{
		return First.m_Part==Second.m_Part && First.m_IsFlag==Second.m_IsFlag;
	}
	template <typename charT>
	RB_CONVERSION_HEADER(RegexPart<charT>)
	{
		str << val.m_Part << " " << val.m_IsFlag;
		return str;
	}
}
}

using namespace RichBool;

////////////////////////////////////////////////////////
// function SplitRegex

namespace
{
    template<typename E>
    detail::RegexPart<E> REP(const E* e)
    {
        return detail::RegexPart<E>(e);
    }

    template<typename E>
    detail::RegexPart<E> REFlag(const E* e)
    {
        return detail::RegexPart<E>(e, true);
    }

    template<typename E>
    detail::RegexPart<E> REBackRef(const E* e)
    {
        return detail::RegexPart<E>(e, true, true);
    }
}

RB_TEST(SplitRegex_Simple)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("abc", Parts);
	detail::RegexPart<char> ExpectedParts[] = { REP("abc") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>()));
}

RB_TEST(SplitRegex_Asterisk)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("ab*c*", Parts);
	detail::RegexPart<char> ExpectedParts[] = { REP("a"), REP("b*"), REP("c*") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>()));
}

RB_TEST(SplitRegex_Plus)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("ab+c+", Parts);
	detail::RegexPart<char> ExpectedParts[] = { REP("a"), REP("b+"), REP("c+") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>()));
}

RB_TEST(SplitRegex_QuestionMark)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("ab?c?", Parts);
	detail::RegexPart<char> ExpectedParts[] = { REP("a"), REP("b?"), REP("c?") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>()));
}

RB_TEST(SplitRegex_ParensAtBegin)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("(ab)c", Parts);
	detail::RegexPart<char> ExpectedParts[] = { REP("(ab)"), REP("c") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_ParensAtEnd)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("a(bc)", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("a"), REP("(bc)") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_ParensAtBeginAndEnd)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("(ab)(cd)", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("(ab)"), REP("(cd)") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_Parens_WithAsterisk)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("cd(ab)*", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("cd"), REP("(ab)*") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_Parens_WithPlus)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("cd(ab)+", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("cd"), REP("(ab)+") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_Parens_WithQuestionMark)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("cd(ab)?", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("cd"), REP("(ab)?") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_Parens_WithBraces)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("cd(ab){1,2}", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("cd"), REP("(ab){1,2}") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_Parens_WithAsteriskAndQuestionMark)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("cd(ab)*?", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("cd"), REP("(ab)*?") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_Parens_WithPlusAndQuestionMark)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("cd(ab)+?", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("cd"), REP("(ab)+?") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_Parens_WithBracesAndQuestionMark)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("cd(ab){1,2}?", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("cd"), REP("(ab){1,2}?") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_EscapedParens)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("cd\\(ab\\)", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("cd\\(ab\\)") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_EscapedParenBetweenParens)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("cd(a\\)b)", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("cd"), REP("(a\\)b)") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_CharClass)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("a[bz]c", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("a"), REP("[bz]"), REP("c") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>()));
}

RB_TEST(SplitRegex_CharClassWithCloserAsFirstCharacter)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("a[]cd]", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("a"), REP("[]cd]") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_CharClassWithExcludedCloserAsFirstCharacter)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("a[^]cd]", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("a"), REP("[^]cd]") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_CharClassWithExcludedRange)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("a[a-z-[d-g]]", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("a"), REP("[a-z-[d-g]]") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_CharClassOfDigit)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("a[:digit:]", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("a"), REP("[:digit:]") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_ParensInCharClass)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("a[)(]", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("a"), REP("[)(]") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_Paren_InCharClass_InParens)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("a([)])", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("a"), REP("([)])") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_Paren_InCharClassWithOpener_InParens)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("a([])])", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("a"), REP("([])])") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_Paren_InCharClassWithNegatedOpener_InParens)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("a([^])])", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("a"), REP("([^])])") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_BackReference)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("(ab)cd\\1", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("(ab)"), REP("cd"), REP("\\1") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_BackReferenceFollowedByDigit)
{
	// back references can use only one digit,
	// so digits after it should be matched literally
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("(ab)cd\\12", Parts);
	//detail::RegexPart<char>  ExpectedParts[] = { REP("(ab)"), REP("cd"), REP("\\1"), REP("2") }; // what it should be
	detail::RegexPart<char>  ExpectedParts[] = { REP("(ab)"), REP("cd"), REP("\\12") }; // what it is with VC++ 2011
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_BackReference_WithRepeater)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("(ab)cd\\1*", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("(ab)"), REP("cd"), REP("\\1*") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_NonCapturingGroup)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("ab(?:cd)?", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("ab"), REP("(?:cd)?") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_NonCapturingGroup_WithEscapedParen)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("ab(?:c\\)d)?", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("ab"), REP("(?:c\\)d)?") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_Flag)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("ab(?i)cd", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("ab"), detail::RegexPart<char> ("(?i)", true), REP("cd") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_FlagAtEnd)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("ab(?i)", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("ab"), detail::RegexPart<char> ("(?i)", true) };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_PositiveLookAhead)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("abc(?=d)e", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("abc(?=d)"), REP("e") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_NegativeLookAhead)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("abc(?!d)e", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("abc(?!d)"), REP("e") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_PositiveLookAhead_AtEnd)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("abc(?=d)", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("abc(?=d)") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_NegativeLookAhead_AtEnd)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("abc(?!d)", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("abc(?!d)") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_PositiveLookBehind)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("ab(?<=c)d", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("ab"), REP("(?<=c)d") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_NegativeLookBehind)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("ab(?<!c)d", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("ab"), REP("(?<!c)d") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_StartAnchor)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("^abc", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { detail::RegexPart<char>("^", true), REP("abc") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_EndAnchor)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("abc$", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("abc"), detail::RegexPart<char>("$", true) };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_WordBoundary)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("\\babc", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REFlag("\\b"), REP("abc") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_NotWordBoundary)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("\\Babc", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REFlag("\\B"), REP("abc") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_BeginOfString)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("\\Aabc", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REFlag("\\A"), REP("abc") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_EndOfString)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("abc\\Z", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("abc"), REFlag("\\Z") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_EndOfString2)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("abc\\z", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("abc"), REFlag("\\z") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_WordCharacter)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("abc\\w", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("abc\\w") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_Digit)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("abc\\d", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("abc\\d") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_AtomicGrouping)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("ab(?>bc)d", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("ab"), REP("(?>bc)"), REP("d") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_Conditional)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("1(?(?=a)abc|def)2", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("1"), REP("(?(?=a)abc|def)"), REP("2") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(SplitRegex_Comment)
{
	std::vector<detail::RegexPart<char> > Parts;
	detail::SplitRegex("1(?#comment)2", Parts);
	detail::RegexPart<char>  ExpectedParts[] = { REP("1"), detail::RegexPart<char>("(?#comment)", true), REP("2") };
	RB_PASS(rbIN_CONTAINER_ARRAY(Parts, ExpectedParts, AllEqual<>(true)));
}

RB_TEST(AdjustBackReference_OneDigit_Add0)
{
	RB_PASS(rbSTRING_CS("\\1", ==, detail::AdjustBackReference("\\1", 0)));
	RB_PASS(rbSTRING_CS("\\3", ==, detail::AdjustBackReference("\\3", 0)));
}

RB_TEST(AdjustBackReference_OneDigit_Add2)
{
	RB_PASS(rbSTRING_CS("\\3", ==, detail::AdjustBackReference("\\1", 2)));
	RB_PASS(rbSTRING_CS("\\5", ==, detail::AdjustBackReference("\\3", 2)));
}

RB_TEST(AdjustBackReference_TwoDigit_Add0)
{
	RB_PASS(rbSTRING_CS("\\12", ==, detail::AdjustBackReference("\\12", 0)));
	RB_PASS(rbSTRING_CS("\\31", ==, detail::AdjustBackReference("\\31", 0)));
}

RB_TEST(AdjustBackReference_TwoDigit_Add15)
{
	RB_PASS(rbSTRING_CS("\\27", ==, detail::AdjustBackReference("\\12", 15)));
	RB_PASS(rbSTRING_CS("\\46", ==, detail::AdjustBackReference("\\31", 15)));
}

RB_TEST(AdjustBackReference_OneDigit_Add2_WithRepeater)
{
	RB_PASS(rbSTRING_CS("\\3{2}", ==, detail::AdjustBackReference("\\1{2}", 2)));
	RB_PASS(rbSTRING_CS("\\5{2}", ==, detail::AdjustBackReference("\\3{2}", 2)));
}







RB_TEST(NonCapturingGroup)
{
	const std::string regex = "Set(?:Value)?";
	std::regex re(regex.begin(), regex.end());
	std::cmatch match_results;
	RB_PASS_B(std::regex_match("SetValue", match_results, re));

	RB_PASS(rbEQUAL(1u, match_results.size()));
}

RB_TEST(RegexParts)
{
	const std::string regex = "ab.*xy";
	std::regex re(regex.begin(), regex.end());
	std::cmatch match_results;
	RB_PASS_B(std::regex_match("abcdxy", match_results, re));

	RB_PASS(rbEQUAL(1u, match_results.size()));
	//RB_PASS(rbEQUAL("cd", match_results.str(1)));
	//RB_PASS(rbEQUAL(4, match_results.position(1)));
	//RB_PASS(rbEQUAL(2, match_results.length(1)));
}


// Rich Booleans

RB_TEST(RegExp_Match)
{
	RB_PASS(rbREGEXP("abcd", "a[bc]{2}d?"));
	RB_PASS_V(rbvREGEXP("abcd", "a[bc]{2}d?"), "abcd");
}

RB_TEST(RegExp_Match_WithBeginAndEndMarker)
{
	// unlikely to be done, but test anyway
	RB_PASS(rbREGEXP("abcd", "^a[bc]{2}d?$"));
	RB_PASS_V(rbvREGEXP("abcd", "^a[bc]{2}d?$"), "abcd");
}

RB_TEST(RegExp_FailAtFirstPart)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"zbcd\"", ":")("zbcd", true)(" should match regular expression ")
			.expr("\"a[bc]{2}d?\"", ":")("a[bc]{2}d?", true)
			.ep("X a:\nX [bc]{2}:\nX d?:\nAfter : zbcd\n");
	RB_FAIL(rbREGEXP("zbcd", "a[bc]{2}d?"), *an);
	RB_FAIL_V(rbvREGEXP("zbcd", "a[bc]{2}d?"), *an, "zbcd");
}

RB_TEST(RegExp_FailAtSecondPart)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"abzd\"", ":")("abzd", true)(" should match regular expression ")
			.expr("\"a[bc]{2}d?\"", ":")("a[bc]{2}d?", true)
			.ep("M a: a\nX [bc]{2}:\nX d?:\nAfter : bzd\n");
	RB_FAIL(rbREGEXP("abzd", "a[bc]{2}d?"), *an);
	RB_FAIL_V(rbvREGEXP("abzd", "a[bc]{2}d?"), *an, "abzd");
}

RB_TEST(RegExp_FailAtThirdPart)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"abcz\"", ":")("abcz", true)(" should match regular expression ")
			.expr("\"a[bc]{2}d+\"", ":")("a[bc]{2}d+", true)
			.ep("M a: a\nM [bc]{2}: bc\nX d+:\nAfter : z\n");
	RB_FAIL(rbREGEXP("abcz", "a[bc]{2}d+"), *an);
	RB_FAIL_V(rbvREGEXP("abcz", "a[bc]{2}d+"), *an, "abcz");
}

RB_TEST(RegExp_Fail_TooMuchBeforeString)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"cdab\"", ":")("cdab", true)(" should match regular expression ")
			.expr("\"(ab)\"", ":")("(ab)", true)
			.ep("Before: cd\nM (ab): ab\n");
	RB_FAIL(rbREGEXP("cdab", "(ab)"), *an);
	RB_FAIL_V(rbvREGEXP("cdab", "(ab)"), *an, "cdab");
}

RB_TEST(RegExp_Fail_TooMuchAfterString)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"abcd\"", ":")("abcd", true)(" should match regular expression ")
			.expr("\"(ab)\"", ":")("(ab)", true)
			.ep("M (ab): ab\nAfter : cd\n");
	RB_FAIL(rbREGEXP("abcd", "(ab)"), *an);
	RB_FAIL_V(rbvREGEXP("abcd", "(ab)"), *an, "abcd");
}

RB_TEST(RegExp_Fail_TooMuchBeforeRegex)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"ab\"", ":")("ab", true)(" should match regular expression ")
			.expr("\"(cd)(ab)\"", ":")("(cd)(ab)", true)
			.ep("X (cd):\nX (ab):\nAfter : ab\n");
	RB_FAIL(rbREGEXP("ab", "(cd)(ab)"), *an);
	RB_FAIL_V(rbvREGEXP("ab", "(cd)(ab)"), *an, "ab");
}

RB_TEST(RegExp_Fail_TooMuchAfterRegex)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"ab\"", ":")("ab", true)(" should match regular expression ")
			.expr("\"(ab)(cd)\"", ":")("(ab)(cd)", true)
			.ep("M (ab): ab\nX (cd):\n");
	RB_FAIL(rbREGEXP("ab", "(ab)(cd)"), *an);
	RB_FAIL_V(rbvREGEXP("ab", "(ab)(cd)"), *an, "ab");
}

RB_TEST(RegExp_Match_Fail_SecondPartMatchesEverything)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"abcdxyf\"", ":")("abcdxyf", true)(" should match regular expression ")
			.expr("\"ab.*xy\"", ":")("ab.*xy", true)
			.ep("M ab: ab\nM .*: cd\nM xy: xy\nAfter : f\n");
	RB_FAIL(rbREGEXP("abcdxyf", "ab.*xy"), *an);
	RB_FAIL_V(rbvREGEXP("abcdxyf", "ab.*xy"), *an, "abcdxyf");
}

RB_TEST(RegExp_Fail_PartialMatch_WithPartBefore)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"xab\"", ":")("xab", true)(" should match regular expression ")
			.expr("\"(ab)d\"", ":")("(ab)d", true)
			.ep("Before: x\nM (ab): ab\nX d:\n");
	RB_FAIL(rbREGEXP("xab", "(ab)d"), *an);
	RB_FAIL_V(rbvREGEXP("xab", "(ab)d"), *an, "xab");
}

RB_TEST(RegExp_Fail_PartialMatch_WithPartAfter)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"abx\"", ":")("abx", true)(" should match regular expression ")
			.expr("\"(ab)d\"", ":")("(ab)d", true)
			.ep("M (ab): ab\nX d:\nAfter : x\n");
	RB_FAIL(rbREGEXP("abx", "(ab)d"), *an);
	RB_FAIL_V(rbvREGEXP("abx", "(ab)d"), *an, "abx");
}

RB_TEST(RegExp_Fail_WithGroups)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"abcdab\"", ":")("abcdab", true)(" should match regular expression ")
			.expr("\"(ab)(cd)(ab)xy\"", ":")("(ab)(cd)(ab)xy", true)
			.ep("M (ab): ab\nM (cd): cd\nM (ab): ab\nX xy:\n");
	RB_FAIL(rbREGEXP("abcdab", "(ab)(cd)(ab)xy"), *an);
	RB_FAIL_V(rbvREGEXP("abcdab", "(ab)(cd)(ab)xy"), *an, "abcdab");
}

RB_TEST(RegExp_Fail_BackReference)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"abcdcd\"", ":")("abcdcd", true)(" should match regular expression ")
			.expr("\"ab(cd)\\\\1xy\"", ":")("ab(cd)\\\\1xy", true)
			.ep("M ab: ab\nM (cd): cd\nM \\1: cd\nX xy:\n");
	RB_FAIL(rbREGEXP("abcdcd", "ab(cd)\\1xy"), *an);
	RB_FAIL_V(rbvREGEXP("abcdcd", "ab(cd)\\1xy"), *an, "abcdcd");
}

RB_TEST(RegExp_Fail_CaseInsensitive)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"abCD\"", ":")("abCD", true)(" should match regular expression ")
			.expr("\"ab(?i)ce\"", ":")("ab(?i)ce", true)
			.ep("M ab: ac\n(?i)\nX ce: CD\n");
	// This throws an exception in VS2010
	/*RB_FAIL(rbREGEXP("abCD", "ab(?i)ce"), *an);
	RB_FAIL_V(rbvREGEXP("abCD", "ab(?i)ce"), *an, "abCD");*/
}

RB_TEST(RegExp_Match_WideCharacter)
{
	RB_PASS(rbREGEXP(L"abcd", L"a[bc]{2}d?"));
	RB_PASS_V(rbvREGEXP(L"abcd", L"a[bc]{2}d?"), L"abcd");
}

RB_TEST(RegExp_Match_Boundary)
{
	RB_PASS(rbREGEXP("z abc", "z.*\\babc"));
	RB_PASS_V(rbvREGEXP("z abc", "z.*\\babc"), "z abc");
}

RB_TEST(RegExp_Match_WithFlag)
{
	RB_PASS(rbREGEXP_F("abc", "abc", std::regex_constants::match_not_bol));
	RB_PASS_V(rbvREGEXP_F("abc", "abc", std::regex_constants::match_not_bol), "abc");
}

RB_TEST(RegExp_Fail_WithFlag)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"abd\"", ":")("abd", true)(" should match regular expression ")
			.expr("\"abc\"", ":")("abc", true)(", using flags ").expr("std::regex_constants::match_not_bol", ":")("1", true)
			.ep("X abc:\nAfter : abd\n");
	RB_FAIL(rbREGEXP_F("abd", "abc", std::regex_constants::match_not_bol), *an);
	RB_FAIL_V(rbvREGEXP_F("abd", "abc", std::regex_constants::match_not_bol), *an, "abd");
}






RB_TEST(HasRegExp_Match)
{
	RB_PASS(rbHAS_REGEXP("xabcdy", "a[bc]{2}d?"));
	RB_PASS_V(rbvHAS_REGEXP("xabcdy", "a[bc]{2}d?"), "xabcdy");
}

RB_TEST(HasRegExp_Match_WithBeginAndEndMarker)
{
	RB_PASS(rbHAS_REGEXP("abcd", "^a[bc]{2}d?$"));
	RB_PASS_V(rbvHAS_REGEXP("abcd", "^a[bc]{2}d?$"), "abcd");
}

RB_TEST(HasRegExp_FailAtFirstPart)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"zbcd\"", ":")("zbcd", true)(" should have substring matching regular expression ")
			.expr("\"a[bc]{2}d?\"", ":")("a[bc]{2}d?", true)
			.ep("X a:\nX [bc]{2}:\nX d?:\nAfter : zbcd\n");
	RB_FAIL(rbHAS_REGEXP("zbcd", "a[bc]{2}d?"), *an);
	RB_FAIL_V(rbvHAS_REGEXP("zbcd", "a[bc]{2}d?"), *an, "zbcd");
}

RB_TEST(HasRegExp_FailAtSecondPart)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"abzd\"", ":")("abzd", true)(" should have substring matching regular expression ")
			.expr("\"a[bc]{2}d?\"", ":")("a[bc]{2}d?", true)
			.ep("M a: a\nX [bc]{2}:\nX d?:\nAfter : bzd\n");
	RB_FAIL(rbHAS_REGEXP("abzd", "a[bc]{2}d?"), *an);
	RB_FAIL_V(rbvHAS_REGEXP("abzd", "a[bc]{2}d?"), *an, "abzd");
}

RB_TEST(HasRegExp_FailAtThirdPart)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"abcz\"", ":")("abcz", true)(" should have substring matching regular expression ")
			.expr("\"a[bc]{2}d+\"", ":")("a[bc]{2}d+", true)
			.ep("M a: a\nM [bc]{2}: bc\nX d+:\nAfter : z\n");
	RB_FAIL(rbHAS_REGEXP("abcz", "a[bc]{2}d+"), *an);
	RB_FAIL_V(rbvHAS_REGEXP("abcz", "a[bc]{2}d+"), *an, "abcz");
}

RB_TEST(HasRegExp_Fail_TooMuchInRegex)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"ab\"", ":")("ab", true)(" should have substring matching regular expression ")
			.expr("\"(ab)(cd)\"", ":")("(ab)(cd)", true)
			.ep("M (ab): ab\nX (cd):\n");
	RB_FAIL(rbHAS_REGEXP("ab", "(ab)(cd)"), *an);
	RB_FAIL_V(rbvHAS_REGEXP("ab", "(ab)(cd)"), *an, "ab");
}

RB_TEST(HasRegExp_Fail_PartialMatch_WithPartBefore)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"xab\"", ":")("xab", true)(" should have substring matching regular expression ")
			.expr("\"(ab)d\"", ":")("(ab)d", true)
			.ep("Before: x\nM (ab): ab\nX d:\n");
	RB_FAIL(rbHAS_REGEXP("xab", "(ab)d"), *an);
	RB_FAIL_V(rbvHAS_REGEXP("xab", "(ab)d"), *an, "xab");
}

RB_TEST(HasRegExp_Fail_PartialMatch_WithPartAfter)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"abx\"", ":")("abx", true)(" should have substring matching regular expression ")
			.expr("\"(ab)d\"", ":")("(ab)d", true)
			.ep("M (ab): ab\nX d:\nAfter : x\n");
	RB_FAIL(rbHAS_REGEXP("abx", "(ab)d"), *an);
	RB_FAIL_V(rbvHAS_REGEXP("abx", "(ab)d"), *an, "abx");
}

RB_TEST(HasRegExp_Fail_WithGroups)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"abcdab\"", ":")("abcdab", true)(" should have substring matching regular expression ")
			.expr("\"(ab)(cd)(ab)xy\"", ":")("(ab)(cd)(ab)xy", true)
			.ep("M (ab): ab\nM (cd): cd\nM (ab): ab\nX xy:\n");
	RB_FAIL(rbHAS_REGEXP("abcdab", "(ab)(cd)(ab)xy"), *an);
	RB_FAIL_V(rbvHAS_REGEXP("abcdab", "(ab)(cd)(ab)xy"), *an, "abcdab");
}

RB_TEST(HasRegExp_Fail_BackReference)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"abcdcd\"", ":")("abcdcd", true)(" should have substring matching regular expression ")
			.expr("\"ab(cd)\\\\1xy\"", ":")("ab(cd)\\\\1xy", true)
			.ep("M ab: ab\nM (cd): cd\nM \\1: cd\nX xy:\n");
	RB_FAIL(rbHAS_REGEXP("abcdcd", "ab(cd)\\1xy"), *an);
	RB_FAIL_V(rbvHAS_REGEXP("abcdcd", "ab(cd)\\1xy"), *an, "abcdcd");
}

RB_TEST(HasRegExp_Fail_CaseInsensitive)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"abCD\"", ":")("abCD", true)(" should have substring matching regular expression ")
			.expr("\"ab(?i)ce\"", ":")("ab(?i)ce", true)
			.ep("M ab: ac\n(?i)\nX ce: CD\n");
	// This throws an exception in VS2010
	/*RB_FAIL(rbHAS_REGEXP("abCD", "ab(?i)ce"), *an);
	RB_FAIL_V(rbvHAS_REGEXP("abCD", "ab(?i)ce"), *an, "abCD");*/
}

RB_TEST(HasRegExp_Match_WideCharacter)
{
	RB_PASS(rbHAS_REGEXP(L"abcd", L"a[bc]{2}d?"));
	RB_PASS_V(rbvHAS_REGEXP(L"abcd", L"a[bc]{2}d?"), L"abcd");
}

RB_TEST(HasRegExp_Match_Boundary)
{
	RB_PASS(rbHAS_REGEXP("z abc", "\\babc"));
	RB_PASS_V(rbvHAS_REGEXP("z abc", "\\babc"), "z abc");
}

RB_TEST(RegExp_BeginOfWord)
{
	std::basic_regex<char> re("\\babc");
	RB_ASSERT(std::regex_search("123 abc", re));
}

RB_TEST(RegExp_NewLine)
{
	std::basic_regex<char> re("^abc$");
	RB_ASSERT(std::regex_search("123\nabc", re));
}

RB_TEST(RegExp_MoreThan9BackReferences)
{
	std::basic_regex<char> re("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)(l)\\10\\12");
	RB_ASSERT(std::regex_search("abcdefghijkljl", re));
}

RB_TEST(HasRegExp_Match_WithFlag)
{
	RB_PASS(rbHAS_REGEXP_F("abc", "abc", std::regex_constants::match_not_bol));
	RB_PASS_V(rbvHAS_REGEXP_F("abc", "abc", std::regex_constants::match_not_bol), "abc");
}

RB_TEST(HasRegExp_Fail_WithFlag)
{
	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("\"abd\"", ":")("abd", true)(" should have substring matching regular expression ")
			.expr("\"abc\"", ":")("abc", true)(", using flags ").expr("std::regex_constants::match_not_bol", ":")("1", true)
			.ep("X abc:\nAfter : abd\n");
	RB_FAIL(rbHAS_REGEXP_F("abd", "abc", std::regex_constants::match_not_bol), *an);
	RB_FAIL_V(rbvHAS_REGEXP_F("abd", "abc", std::regex_constants::match_not_bol), *an, "abd");
}

RB_TEST(BackReferenceFollowedByDigit)
{
	// throws exception in VC++ 2011 because its regex library allows more than 10 numbered backreferences
	//std::basic_regex<char> re("(ab)c\\12");
	//RB_ASSERT(std::regex_search("abcab2", re));
}


// Tests for checking the capabilities of the regular expressions implementation

/*namespace
{
	std::regex_constants::syntax_option_type syntax_option_type = std::regex_constants::ECMAScript;
}

RB_TEST(CaseInsensitiveFlag)
{
	std::basic_regex<char> re("a(?i)b(?-i)c", syntax_option_type);
	RB_ASSERT(std::regex_search("aBc", re));
}

RB_TEST(CaseInsensitiveSpan)
{
	std::basic_regex<char> re("a(?i:b)c", syntax_option_type);
	RB_ASSERT(std::regex_search("aBc", re));
}

RB_TEST(WordAndDigitShorthands)
{
	std::basic_regex<char> re("\\w*\\d*", syntax_option_type);
	RB_ASSERT(std::regex_search("abc123", re));
}

RB_TEST(HasRegExp_Match_WithWordBoundary)
{
	RB_PASS(rbHAS_REGEXP_F("1\nabc", "^abc", std::regex_constants::match_not_bol));
	RB_PASS_V(rbvHAS_REGEXP_F("1\nabc", "^abc", std::regex_constants::match_not_bol), "z abc");
}

RB_TEST(Alternation)
{
	std::basic_regex<char> re("abc|xyz", syntax_option_type);
	RB_ASSERT(std::regex_search("abc", re));
}

RB_TEST(Laziness)
{
	std::basic_regex<char> re("<.+?><>", syntax_option_type);
	RB_ASSERT(std::regex_search("<ab><>", re));
}

RB_TEST(Possessive)
{
	std::basic_regex<char> re("<\\w++><>", syntax_option_type);
	RB_ASSERT(std::regex_search("<ab><>", re));
}

RB_TEST(BackReference)
{
	std::basic_regex<char> re("([a-c])x\\1", syntax_option_type);
	RB_ASSERT(std::regex_search("axa", re));
}

RB_TEST(AtomicGrouping)
{
	std::basic_regex<char> re("a(?>bc|b)c", syntax_option_type);
	RB_ASSERT(std::regex_search("abcc", re));
}

RB_TEST(NamedCapturingGroups_Python_PHP)
{
	std::basic_regex<char> re("(?P<name>abc)x(?P=name)", syntax_option_type);
	RB_ASSERT(std::regex_search("abcxabc", re));
}

RB_TEST(NamedCapturingGroups_DotNet)
{
	std::basic_regex<char> re("(?P'name'abc)x\\k'name'", syntax_option_type);
	RB_ASSERT(std::regex_search("abcxabc", re));
}

RB_TEST(PositiveLookAhead)
{
	std::basic_regex<char> re("q(?=u)u", syntax_option_type);
	RB_ASSERT(std::regex_search("qu", re));
}

RB_TEST(NegativeLookAhead)
{
	std::basic_regex<char> re("q(?!u)a", syntax_option_type);
	RB_ASSERT(std::regex_search("qa", re));
}

RB_TEST(PositiveLookBehind)
{
	std::basic_regex<char> re(".(?<=q)u", syntax_option_type);
	RB_ASSERT(std::regex_search("qu", re));
}

RB_TEST(NegativeLookBehind)
{
	std::basic_regex<char> re("q(?<!u)a", syntax_option_type);
	RB_ASSERT(std::regex_search("qa", re));
}

RB_TEST(Conditional)
{
	std::basic_regex<char> re("(?(?=a)abc|xyz)", syntax_option_type);
	RB_ASSERT(std::regex_search("abc", re));
}

RB_TEST(ConditionalWithName)
{
	std::basic_regex<char> re("(?<test>a)?b(?(test)c|d)", syntax_option_type);
	RB_ASSERT(std::regex_search("abc", re));
}

RB_TEST(StartOfString)
{
	std::basic_regex<char> re("\\Aabc", syntax_option_type);
	RB_ASSERT(std::regex_search("abc", re));
	RB_ASSERT(std::regex_search("123\nabc", re));
}

RB_TEST(Comments)
{
	std::basic_regex<char> re("(?#comment)abc", syntax_option_type);
	RB_ASSERT(std::regex_search("abc", re));
}
*/

#endif // #ifdef RICHBOOL_REGEX
