//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include "richbool/tmpbool.hpp"
#include "richbool/analysis.hpp"

namespace RichBool {

	TmpBool::TmpBool(Analysis *analysis_): analysis(analysis_)
	{
		b = !analysis_ || (Analysis::Ok==analysis_->GetState());
	}
}
