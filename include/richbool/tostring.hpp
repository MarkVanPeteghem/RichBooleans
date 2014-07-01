//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_TO_STRING_H__QM
#define RICH_BOOL_TO_STRING_H__QM

#include "richbool/portability.hpp"

namespace RichBool
{
	struct MakeString
	{
		enum { showString = true };
		template <typename T>
		detail::String operator()(const T &t) const
		{
			// namespace addition is necessary with recent gcc
			// also avoids confusion with ToString overloads in default namespace
			return ToString(t);
		}
	};

	template <bool showPointer, bool showValue>
	struct MakeStringOfPointer
	{};

	template <>
	struct MakeStringOfPointer<true, true>
	{
		enum { showString = true };
		template <typename T>
		detail::String operator()(const T &t) const
		{
			if (BadPtr(t))
				return PtrToString(t);
			else
				// namespace addition is necessary with recent gcc
				// also avoids confusion with ToString overloads in default namespace
				return PtrToString(t)+" -> "+ToString(*t);
		}
	};

	template <>
	struct MakeStringOfPointer<true, false>
	{
		enum { showString = true };
		template <typename T>
		detail::String operator()(const T &t) const
		{
			return PtrToString(t);
		}
	};

	template <>
	struct MakeStringOfPointer<false, true>
	{
		enum { showString = true };
		template <typename T>
		detail::String operator()(const T &t) const
		{
			if (BadPtr(t))
				return PtrToString(t);
			else
				// namespace addition is necessary with recent gcc
				// also avoids confusion with ToString overloads in default namespace
				return ToString(*t);
		}
	};

	struct NoString
	{
		enum { showString = true };
		template <typename T>
		detail::String operator()(const T &) const
		{
			return "#";
		}
	};

	struct HideString
	{
		enum { showString = false };
		template <typename T>
		detail::String operator()(const T &) const
		{
			return "#";
		}
	};
}

#endif // #ifndef RICH_BOOL_TO_STRING_H__QM
