//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#if defined(_MSC_VER)
	#pragma warning(disable: 4786)
#endif

#include "richbool/richbool.hpp"

#include "rbtest.hpp"
#include "composite_expressions.hpp"

using namespace RichBool;
using RichBool::detail::String;

RB_TEST(Number)
{
	IndexExpression expression(5);
	String str = expression;
	RB_ASSERT(str=="[5]");
}

RB_TEST(Text)
{
	TextExpression expression("abc");
	String str = expression;
	RB_ASSERT(str=="`abc'");
}

RB_TEST(String)
{
	String text = "abc";
	StringExpression expression(text);
	String str = expression;
	RB_ASSERT(rbEQUAL(str, "`abc'"));
}


///////////////////////////////////////////////////////////
// class SuffixedExpression

RB_TEST(SuffixedWithText)
{
	SuffixedExpression pe("->n", new TextExpression("text"));
	String str = pe;
	RB_ASSERT(rbEQUAL(str, "`text'->n"));
}

RB_TEST(SuffixedWithIndex)
{
	SuffixedExpression pe("->n", new IndexExpression(2));
	String str = pe;
	RB_ASSERT(rbEQUAL(str, "[2]->n"));
}

RB_TEST(SuffixedSuffixedWithIndex)
{
	SharedExpression expr = SuffixSuffixIndex("->p", "->n", 2);
	String str = *expr;
	RB_ASSERT(rbEQUAL(str, "[2]->n->p"));
}

RB_TEST(SuffixedWithText_Clone)
{
	SuffixedExpression pe("->n", new TextExpression("text"));
	Expression *pe_clone = pe.Clone();
	String str = *pe_clone;
	RB_ASSERT(rbEQUAL(str, "`text'->n"));
	delete pe_clone;
}

RB_TEST(SuffixedSuffixedWithText_Clone)
{
	SharedExpression pe = SuffixSuffixText("->p", "->n", "text");
	Expression *pe_clone = pe->Clone();
	String str = *pe_clone;
	RB_ASSERT(rbEQUAL(str, "`text'->n->p"));
	delete pe_clone;
}
