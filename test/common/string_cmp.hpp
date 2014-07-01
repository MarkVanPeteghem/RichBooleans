//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#if defined(_MSC_VER)
	#pragma warning(disable: 4786)
#endif

#ifdef RICHBOOL_USE_WX
	#include "richbool/wxstring.hpp"
	#define rbSTRING_(str1, op, str2) rbSTRING(str1, op, str2, WxStringCmp())
#else
	#define rbSTRING_(str1, op, str2) rbSTRING(str1, op, str2, StringCompare())
#endif
