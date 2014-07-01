//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_EXCEPTIONS_H__QM
#define RICH_BOOL_EXCEPTIONS_H__QM

#include <exception>

#include "richbool/der_analysis.hpp"
#include "richbool/basic_rb.hpp"

namespace RichBool
{
	class ExceptionAnalyzer
	{
	public:
		ExceptionAnalyzer() {}

		template<typename Exc_>
		bool operator()(const Exc_ &) const
		{
			return false;
		}

		template<typename Exc_, typename Expr>
		Analysis* Analyse(Exc_ &exc, Expr ,
			bool =false) const
		{
			GeneralAnalysis *analysis = new GeneralAnalysis(false);

			analysis->AddText("exception of type ");
			analysis->AddValue(GetExceptionTypeName(exc), false);
			analysis->AddText(" was caught");
			analysis->AddNewLine();
			analysis->AddText("info: ");
			analysis->AddValue(GetExceptionInfo(exc), false);

			return analysis;
		}
	};
}

#define RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(EXCEPTION_TYPE) \
	namespace RichBool { \
		inline const char* GetExceptionTypeName(const EXCEPTION_TYPE &) { \
			return #EXCEPTION_TYPE; \
		} \
	}

#define rbEXCEPTION(exc) rb1_RB(exc, RichBool::ExceptionAnalyzer())
#define rbvEXCEPTION(exc) rbv1_1_RB(exc, RichBool::ExceptionAnalyzer())


#endif // #ifndef RICH_BOOL_EXCEPTIONS_H__QM
