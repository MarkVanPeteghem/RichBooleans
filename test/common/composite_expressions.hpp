//  Copyright (C) 2004, 2005, 2006 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef COMPOSITE_EXPRESSIONS_H__QM
#define COMPOSITE_EXPRESSIONS_H__QM

#include "richbool/expression.hpp"

inline RichBool::SharedExpression PrefixIndex(const char *text, size_t idx)
{
	return new RichBool::PrefixedExpression(text, new RichBool::IndexExpression(idx));
}

inline RichBool::SharedExpression PrefixText(const char *text, const char *expr)
{
	return new RichBool::PrefixedExpression(text, new RichBool::TextExpression(expr));
}

inline RichBool::SharedExpression PrefixPrefixIndex(const char *text1, const char *text2, size_t idx)
{
	return new RichBool::PrefixedExpression(text1,
		new RichBool::PrefixedExpression(text2, new RichBool::IndexExpression(idx)));
}

inline RichBool::SharedExpression PrefixPrefixText(const char *text1, const char *text2, const char *expr)
{
	return new RichBool::PrefixedExpression(text1,
		new RichBool::PrefixedExpression(text2, new RichBool::TextExpression(expr)));
}

inline RichBool::SharedExpression SuffixIndex(const char *text, size_t idx)
{
	return new RichBool::SuffixedExpression(text, new RichBool::IndexExpression(idx));
}

inline RichBool::SharedExpression SuffixText(const char *text, const char *expr)
{
	return new RichBool::SuffixedExpression(text, new RichBool::TextExpression(expr));
}

inline RichBool::SharedExpression SuffixSuffixIndex(const char *text1, const char *text2, size_t idx)
{
	return new RichBool::SuffixedExpression(text1,
		new RichBool::SuffixedExpression(text2, new RichBool::IndexExpression(idx)));
}

inline RichBool::SharedExpression SuffixSuffixText(const char *text1, const char *text2, const char *expr)
{
	return new RichBool::SuffixedExpression(text1,
		new RichBool::SuffixedExpression(text2, new RichBool::TextExpression(expr)));
}

inline RichBool::SharedExpression PrefixSuffixText(const char *text1, const char *text2, const char *expr)
{
	return new RichBool::PrefixedExpression(text1,
		new RichBool::SuffixedExpression(text2, new RichBool::TextExpression(expr)));
}

inline RichBool::SharedExpression SuffixPrefixText(const char *text1, const char *text2, const char *expr)
{
	return new RichBool::SuffixedExpression(text1,
		new RichBool::PrefixedExpression(text2, new RichBool::TextExpression(expr)));
}


#endif // #ifndef COMPOSITE_EXPRESSIONS_H__QM
