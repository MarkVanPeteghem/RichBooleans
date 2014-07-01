//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MFC_STREAM_H__QM
#define MFC_STREAM_H__QM

// MFC can't be used in single-threaded applications:
#if defined(_MT)

#include "richbool/portability.hpp"

namespace RichBool
{
	#if _MSC_VER < 1300
	inline detail::String ToString(const CString &val)
	{
		return RichBool::detail::EscapeString((LPCTSTR)val, val.GetLength());
	}
	#else
	template <typename E, class Traits>
	inline detail::String ToString(const ATL::CStringT<E, Traits> &val)
	{
		return RichBool::detail::EscapeString((const E*)val, val.GetLength());
	}
	#endif
}

RB_CONVERSION_HEADER(POINT)
{
	str << '(' << val.x << ',' << val.y << ')';
	return str;
}

RB_CONVERSION_HEADER(SIZE)
{
	str << '(' << val.cx << ',' << val.cy << ')';
	return str;
}

RB_CONVERSION_HEADER(RECT)
{
	str << '(' << val.left << ',' << val.top << ")-("
		<< val.right << ',' << val.bottom << ')';
	return str;
}

RB_CONVERSION_HEADER(CTime)
{
	CString cs = val.Format("%c");
	RichBool::detail::String s((LPCTSTR)cs, cs.GetLength());
	str << s;
	return str;
}

#endif // #if defined(_MT)

#endif // #ifndef MFC_STREAM_H__QM
