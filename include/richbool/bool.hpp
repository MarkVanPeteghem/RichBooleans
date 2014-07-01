//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_BOOL_H__QM
#define RICH_BOOL_BOOL_H__QM

#include "richbool/tmpbool.hpp"
#include "richbool/version.hpp"

namespace RichBool
{
	// This is a simple class to which both bool and Analysis*
	// can be assigned, so MOD_ASSERT and similar macros can accept
	// simple condition like 'a==0' but also rich booleans
	class Bool
	{
	public:
		Bool(): b(false) {}
		Bool(bool cond): b(cond) {}
		Bool(long cond): b(cond!=0) {} // necessary in MSVC
		Bool(Analysis *analysis_): analysis(analysis_)
		{ b = !analysis_ || (Analysis::Ok==analysis_->GetState()); }
		Bool(const TmpBool &tmp): b(tmp()), analysis(tmp.analysis) {}
		~Bool() {}

		Bool& operator=(bool cond)
		{
			b = cond;
			analysis = 0;
			return *this;
		}
		Bool& operator=(const TmpBool &tmp)
		{
			b = tmp();
			analysis = tmp.analysis;
			return *this;
		}
		bool operator()() const
		{
			return b;
		}
		RICHBOOL_DLL_API bool operator==(const Bool &other) const;
		bool operator!=(const Bool &other) const
		{
			return !(*this==other);
		}
		const SharedAnalysis& GetAnalysis() const { return analysis; }

	protected:
		bool b;
		SharedAnalysis analysis;
	};
}

#endif // #ifndef RICH_BOOL_BOOL_H__QM
