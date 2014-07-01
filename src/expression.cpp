//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "richbool/expression.hpp"

namespace RichBool
{
	///////////////////////////////////////////////////////////////
	// class Expression

	bool Expression::operator==(const Expression &expr) const
	{
		if (GetType()!=expr.GetType())
			return false;

		return Equals(expr);
	}


	///////////////////////////////////////////////////////////////
	// class IndexExpression

	Expression::Type IndexExpression::GetType() const
	{
		return IsIndex;
	}

	bool IndexExpression::Equals(const Expression &expr) const
	{
		const IndexExpression &ie = (const IndexExpression&)expr;
		return idx == ie.idx;
	}

	IndexExpression::operator detail::String() const
	{
		return "["+ToString(idx)+"]";
	}

	Expression* IndexExpression::Clone() const
	{
		return new IndexExpression(idx);
	}


	///////////////////////////////////////////////////////////////
	// class TextExpression

	Expression::Type TextExpression::GetType() const
	{
		return IsText;
	}

	bool TextExpression::Equals(const Expression &expr) const
	{
		const TextExpression &cle = (const TextExpression&)expr;
		return strcmp(text, cle.text)==0;
	}

	TextExpression::operator detail::String() const
	{
		return '`'+detail::String(text)+'\'';
	}

	Expression* TextExpression::Clone() const
	{
		return new TextExpression(text);
	}


	///////////////////////////////////////////////////////////////
	// class StringExpression

	Expression::Type StringExpression::GetType() const
	{
		return IsText;
	}

	bool StringExpression::Equals(const Expression &expr) const
	{
		const StringExpression &se = (const StringExpression&)expr;
		return str==se.str;
	}


	///////////////////////////////////////////////////////////////
	// class PrefixedExpression

	RICHBOOL_DLL_API Expression::Type PrefixedExpression::GetType() const
	{
		return IsPrefix;
	}

	RICHBOOL_DLL_API bool PrefixedExpression::Equals(const Expression &expr) const
	{
		const PrefixedExpression &pe = (const PrefixedExpression&)expr;
		return (strcmp(prefix, pe.prefix)==0) && (*expression==*pe.expression);
	}



	///////////////////////////////////////////////////////////////
	// class SuffixedExpression

	RICHBOOL_DLL_API Expression::Type SuffixedExpression::GetType() const
	{
		return IsSuffix;
	}

	RICHBOOL_DLL_API bool SuffixedExpression::Equals(const Expression &expr) const
	{
		const SuffixedExpression &pe = (const SuffixedExpression&)expr;
		return (strcmp(suffix, pe.suffix)==0) && (*expression==*pe.expression);
	}
}
