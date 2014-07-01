//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_TMP_BOOL_H__QM
#define RICH_BOOL_TMP_BOOL_H__QM

#include "richbool/analysis.hpp"

namespace RichBool
{
	// This class only exists to cause a compile error when a user
	// uses nested rbOR or rbAND expressions, which wouldn't work correctly.
	// All Rich Booleans macros except rbOR and rbAND evaluate to a TmpBool,
	// which can be assigned to a Bool object.
	// rbOR and rbAND evaluate to a Bool, and expect TmpBool as their
	// arguments, so nested rbOR or rbAND expressions fail to compile.
	class TmpBool
	{
		friend class Bool;
	public:
		TmpBool(): b(false) {}
		TmpBool(bool cond): b(cond) {}
		TmpBool(long cond): b(cond!=0) {} // necessary in MSVC
		TmpBool(Analysis *analysis_);
		bool operator()() const
		{
			return b;
		}
		SharedAnalysis GetAnalysis() const { return analysis; }

		TmpBool& dec(int &l)
		{
			--l;
			return *this;
		}

	protected:
		bool b;
		SharedAnalysis analysis;
	};
}

#endif // #ifndef RICH_BOOL_TMP_BOOL_H__QM
