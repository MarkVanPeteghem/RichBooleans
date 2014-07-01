//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef TESTABLE_INFO_WITH_STRINGS_H__QM
#define TESTABLE_INFO_WITH_STRINGS_H__QM

#include "richbool/richbool.hpp"
#include "richbool/der_analysis.hpp"

template <class Base>
class TmplTestableAnalysisOfStrings: public Base
{
public:
	TmplTestableAnalysisOfStrings(const RichBool::detail::String &str1_,
							const RichBool::detail::String &str2_,
							const char *expr1,
							const char *expr2,
							const RichBool::detail::String &diff,
							const char *szRelation,
							const char *szCompType=0):
		Base()
	{
		m_strDiff = diff;
		m_str1 = str1_;
		m_str2 = str2_;
		Init(str1_, str2_, RichBool::MakeExpression(expr1), RichBool::MakeExpression(expr2),
			szRelation, szCompType ? szCompType : "locale C");
	}

	TmplTestableAnalysisOfStrings(const RichBool::detail::String &str1_,
							const RichBool::detail::String &str2_,
							RichBool::Expression *expr1,
							RichBool::Expression *expr2,
							const RichBool::detail::String &diff,
							const char *szRelation,
							const char *szCompType=0):
		Base()
	{
		m_strDiff = diff;
		m_str1 = str1_;
		m_str2 = str2_;
		Init(str1_, str2_, expr1, expr2,
			szRelation, szCompType ? szCompType : "locale C");
	}

	TmplTestableAnalysisOfStrings* MakeOk()
	{
		SetState(Ok);
		return this;
	}
};

#if defined(RICHBOOL_USE_WX)
typedef TmplTestableAnalysisOfStrings<RichBool::BasicAnalysisOfStrings<wxChar> > TestableAnalysisOfStrings;
typedef TmplTestableAnalysisOfStrings<RichBool::BasicAnalysisOfStringsSideBySide<wxChar> > TestableAnalysisOfStringsSideBySide;
#else
typedef TmplTestableAnalysisOfStrings<RichBool::BasicAnalysisOfStrings<char> > TestableAnalysisOfStrings;
typedef TmplTestableAnalysisOfStrings<RichBool::BasicAnalysisOfStringsSideBySide<char> > TestableAnalysisOfStringsSideBySide;
#endif

#if defined(RICHBOOL_HAS_WSTRING)
template <class Base>
class TmplTestableAnalysisOfWStrings:
	public Base
{
public:
	TmplTestableAnalysisOfWStrings(const RichBool::detail::WString &str1_,
							const RichBool::detail::WString &str2_,
							const char *expr1,
							const char *expr2,
							const RichBool::detail::String &diff,
							const char *szRelation,
							const char *szCompType=0):
		Base()
	{
		m_strDiff = diff;
		m_str1 = str1_;
		m_str2 = str2_;
		Init(str1_, str2_, RichBool::MakeExpression(expr1), RichBool::MakeExpression(expr2),
			szRelation, szCompType ? szCompType : "locale C");
	}

	TmplTestableAnalysisOfWStrings(const RichBool::detail::WString &str1_,
							const RichBool::detail::WString &str2_,
							RichBool::Expression *expr1,
							RichBool::Expression *expr2,
							const RichBool::detail::String &diff,
							const char *szRelation,
							const char *szCompType=0):
		RichBool::BasicAnalysisOfStrings<RichBool::detail::wchar>()
	{
		m_strDiff = diff;
		m_str1 = str1_;
		m_str2 = str2_;
		Init(str1_, str2_, expr1, expr2,
			szRelation, szCompType ? szCompType : "locale C");
	}

	TmplTestableAnalysisOfWStrings* MakeOk()
	{
		SetState(Ok);
		return this;
	}
};

typedef TmplTestableAnalysisOfWStrings<RichBool::BasicAnalysisOfStrings<RichBool::detail::wchar> > TestableAnalysisOfWStrings;
typedef TmplTestableAnalysisOfWStrings<RichBool::BasicAnalysisOfStringsSideBySide<RichBool::detail::wchar> > TestableAnalysisOfWStringsSideBySide;
#endif

#endif // #ifndef TESTABLE_INFO_WITH_STRINGS_H__QM
