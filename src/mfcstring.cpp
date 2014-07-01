//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICHBOOL_USE_WX

// MFC can't be used in single-threaded applications:
#if defined(_MT)

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include "richbool/mfcstring1.hpp"

namespace RichBool
{
	const detail::String& TmplCStringCompareName<char>::Name()
	{
		const static detail::String name = "CStringA Compare";
		return name;
	}

	const detail::String& TmplCStringCompareName<wchar_t>::Name()
	{
		const static detail::String name = "CStringW Compare";
		return name;
	}

	const detail::String& TmplCStringCompareNoCaseName<char>::Name()
	{
		const static detail::String name = "CStringA CompareNoCase";
		return name;
	}

	const detail::String& TmplCStringCompareNoCaseName<wchar_t>::Name()
	{
		const static detail::String name = "CStringW CompareNoCase";
		return name;
	}

	const detail::String& TmplCStringCollateName<char>::Name()
	{
		const static detail::String name = "CStringA Collate";
		return name;
	}

	const detail::String& TmplCStringCollateName<wchar_t>::Name()
	{
		const static detail::String name = "CStringW Collate";
		return name;
	}

	const detail::String& TmplCStringCollateNoCaseName<char>::Name()
	{
		const static detail::String name = "CStringA CollateNoCase";
		return name;
	}

	const detail::String& TmplCStringCollateNoCaseName<wchar_t>::Name()
	{
		const static detail::String name = "CStringW CollateNoCase";
		return name;
	}
}

#endif // #if defined(_MT)

#endif // #ifndef RICHBOOL_USE_WX
