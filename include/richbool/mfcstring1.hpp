//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MFC_STRING1_H__QM
#define MFC_STRING1_H__QM

// MFC can't be used in single-threaded applications:
#if defined(_MT)

#include "richbool/string.hpp"

namespace RichBool
{
	template <typename E, class CStringType>
	struct TmplCStringCompareBase
	{
		typedef E CharType;

		static inline E* StringTypeToCharType(const E*)
		{
			return (E*)0;
		}

		static inline E* StringTypeToCharType(const CStringType &)
		{
			return (E*)0;
		}

		static inline const std::basic_string<E> ToDefaultString(const E* str)
		{
			return str;
		}

		static inline const std::basic_string<E> ToDefaultString(const CStringType &str)
		{
			return (const E*)str;
		}
	};


	// Cstring::Compare

	template<typename E>
	struct TmplCStringCompareName
	{};

	template<>
	struct TmplCStringCompareName<char>
	{
		static const detail::String& Name();
	};

	template<>
	struct TmplCStringCompareName<wchar_t>
	{
		static const detail::String& Name();
	};

	template<typename E, class CStringType>
	struct TmplCStringCompare_: public TmplCStringCompareBase<E, CStringType>
	{
		int operator()(E ch1, E ch2) const
		{
			return ch1==ch2 ? 0 : (ch1<ch2 ? -1 : 1);
		}

		int operator()(const CStringType &str1, const CStringType &str2) const
		{
			return str1.Compare(str2);
		}

		const detail::String& name() const
		{
			return TmplCStringCompareName<E>::Name();
		}

		enum { ContinueAfterConflict = false };
	};


	// Cstring::CompareNoCase

	template<typename E>
	struct TmplCStringCompareNoCaseName
	{};

	template<>
	struct TmplCStringCompareNoCaseName<char>
	{
		static const detail::String& Name();
	};

	template<>
	struct TmplCStringCompareNoCaseName<wchar_t>
	{
		static const detail::String& Name();
	};

	template<typename E>
	struct TmplCStringCollateName
	{};

	template<>
	struct TmplCStringCollateName<char>
	{
		static const detail::String& Name();
	};

	template<>
	struct TmplCStringCollateName<wchar_t>
	{
		static const detail::String& Name();
	};

	template<typename E>
	struct TmplCStringCollateNoCaseName
	{};

	template<>
	struct TmplCStringCollateNoCaseName<char>
	{
		static const detail::String& Name();
	};

	template<>
	struct TmplCStringCollateNoCaseName<wchar_t>
	{
		static const detail::String& Name();
	};
}

#endif

#endif // #ifndef MFC_STRING1_H__QM
