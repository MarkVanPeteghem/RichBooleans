//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include "richbool/bool.hpp"
#include "richbool/analysis.hpp"

namespace RichBool
{
	///////////////////////////////////////////////////////////////
	// class Bool

	RICHBOOL_DLL_API bool Bool::operator==(const Bool &other) const
	{
		if (b!=other.b)
			return false;
		if (GetAnalysis())
			return other.GetAnalysis() ? *GetAnalysis()==*other.GetAnalysis() : false;
		else
			return !other.GetAnalysis();
	}
}
