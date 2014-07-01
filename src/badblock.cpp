//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (See accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "richbool/badblock.hpp"

#if defined(RICHBOOL_WIN) && !defined(NDEBUG)
	#include <windows.h>
#endif

namespace RichBool
{
#if defined(RICHBOOL_WIN) && !defined(NDEBUG)
	bool BadBlock(const void *p, size_t size)
	{
		return IsBadReadPtr(p, size)!=0;
#else
	bool BadBlock(const void *p, size_t )
	{
		return p<=((void*)0xf);
#endif
	}
}













