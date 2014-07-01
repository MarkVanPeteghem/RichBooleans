//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "richbool/string.hpp"

namespace RichBool
{
	const detail::String& BasicStrcmp<char>::name() const
	{
		const static detail::String str = "strcmp";
		return str;
	}

#if defined(RICHBOOL_HAS_WSTRING)
	const detail::String& BasicStrcmp<detail::wchar>::name() const
	{
		const static detail::String str = "wcscmp";
		return str;
	}
#endif
}














