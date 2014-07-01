//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MFC_STRING_H__QM
#define MFC_STRING_H__QM

// MFC can't be used in single-threaded applications:
#if defined(_MT)

#include "richbool/mfcstring1.hpp"
#include <afx.h>

namespace RichBool
{
	template<typename E, class CStringType>
	struct TmplCStringCompareNoCase_: public TmplCStringCompareBase<E, CStringType>
	{
		mutable CStringType cs1, cs2;
		TmplCStringCompareNoCase_(): cs1(" "), cs2(" ") {}

		int operator()(E ch1, E ch2) const
		{
			cs1.SetAt(0, ch1);
			cs2.SetAt(0, ch2);
			return cs1.CompareNoCase(cs2);
		}

		int operator()(const CStringType &str1, const CStringType &str2) const
		{
			return str1.CompareNoCase(str2);
		}

		const detail::String& name() const
		{
			return TmplCStringCompareNoCaseName<E>::Name();
		}

		enum { ContinueAfterConflict = false };
	};

	// Cstring::Collate

	template<typename E, class CStringType>
	struct TmplCStringCollate_: public TmplCStringCompareBase<E, CStringType>
	{
		mutable CStringType cs1, cs2;
		TmplCStringCollate_(): cs1(" "), cs2(" ") {}

		int operator()(E ch1, E ch2) const
		{
			cs1.SetAt(0, ch1);
			cs2.SetAt(0, ch2);
			return cs1.Collate(cs2);
		}

		int operator()(const CStringType &str1, const CStringType &str2) const
		{
			return str1.Collate(str2);
		}

		const detail::String& name() const
		{
			return TmplCStringCollateName<E>::Name();
		}

		enum { ContinueAfterConflict = true };
	};

	// Cstring::CollateNoCase

	template<typename E, class CStringType>
	struct TmplCStringCollateNoCase_: public TmplCStringCompareBase<E, CStringType>
	{
		mutable CStringType cs1, cs2;
		TmplCStringCollateNoCase_(): cs1(" "), cs2(" ") {}

		int operator()(E ch1, E ch2) const
		{
			cs1.SetAt(0, ch1);
			cs2.SetAt(0, ch2);
			return cs1.CollateNoCase(cs2);
		}

		int operator()(const CStringType &str1, const CStringType &str2) const
		{
			return str1.CollateNoCase(str2);
		}

		const detail::String& name() const
		{
			return TmplCStringCollateNoCaseName<E>::Name();
		}

		enum { ContinueAfterConflict = true };
	};

#if _MSC_VER <= 1300

	template<>
	class StringRange<CString>
	{
	public:
		typedef const TCHAR* iterator;
		typedef size_t IndexType;

		StringRange(const CString &) {}

		iterator begin(const CString &str) const
		{
			return (const TCHAR*)str;
		}

		bool operator()(iterator ch) const
		{
			return *ch!=0;
		}

		bool operator()(iterator ch, size_t) const
		{
			return *ch!=0;
		}
	};

	typedef TmplCStringCompare_<TCHAR, CString> CStringCompare;
	typedef TmplCStringCompareNoCase_<TCHAR, CString> CStringCompareNoCase;
	typedef TmplCStringCollate_<TCHAR, CString> CStringCollate;
	typedef TmplCStringCollateNoCase_<TCHAR, CString> CStringCollateNoCase;

#else

	template<>
	class StringRange<CStringA>
	{
	public:
		typedef const char* iterator;
		typedef size_t IndexType;

		StringRange(const CStringA &) {}

		iterator begin(const CStringA &str) const
		{
			return (const char*)str;
		}

		bool operator()(iterator ch) const
		{
			return *ch!=0;
		}

		bool operator()(iterator ch, size_t) const
		{
			return *ch!=0;
		}
	};

	template<>
	class StringRange<CStringW>
	{
	public:
		typedef const wchar_t* iterator;
		typedef size_t IndexType;

		StringRange(const CStringW &) {}

		iterator begin(const CStringW &str) const
		{
			return (const wchar_t*)str;
		}

		bool operator()(iterator ch) const
		{
			return *ch!=0;
		}

		bool operator()(iterator ch, size_t) const
		{
			return *ch!=0;
		}
	};

	template<typename E>
	struct TmplCStringCompare
	{};

	template<>
	struct TmplCStringCompare<char>: public TmplCStringCompare_<char, CStringA>
	{};

	template<>
	struct TmplCStringCompare<wchar_t>: public TmplCStringCompare_<wchar_t, CStringW>
	{};

	typedef TmplCStringCompare<char> CStringACompare;
	typedef TmplCStringCompare<wchar_t> CStringWCompare;


	template<typename E>
	struct TmplCStringCompareNoCase
	{};

	template<>
	struct TmplCStringCompareNoCase<char>: public TmplCStringCompareNoCase_<char, CStringA>
	{};

	template<>
	struct TmplCStringCompareNoCase<wchar_t>: public TmplCStringCompareNoCase_<wchar_t, CStringW>
	{};

	typedef TmplCStringCompareNoCase<char> CStringACompareNoCase;
	typedef TmplCStringCompareNoCase<wchar_t> CStringWCompareNoCase;


	template<typename E>
	struct TmplCStringCollate
	{};

	template<>
	struct TmplCStringCollate<char>: public TmplCStringCollate_<char, CStringA>
	{};

	template<>
	struct TmplCStringCollate<wchar_t>: public TmplCStringCollate_<wchar_t, CStringW>
	{};

	typedef TmplCStringCollate<char> CStringACollate;
	typedef TmplCStringCollate<wchar_t> CStringWCollate;


	template<typename E>
	struct TmplCStringCollateNoCase
	{};

	template<>
	struct TmplCStringCollateNoCase<char>: public TmplCStringCollateNoCase_<char, CStringA>
	{};

	template<>
	struct TmplCStringCollateNoCase<wchar_t>: public TmplCStringCollateNoCase_<wchar_t, CStringW>
	{};

	typedef TmplCStringCollateNoCase<char> CStringACollateNoCase;
	typedef TmplCStringCollateNoCase<wchar_t> CStringWCollateNoCase;

#ifdef _UNICODE
	typedef CStringWCompare CStringCompare;
	typedef CStringWCompareNoCase CStringCompareNoCase;
	typedef CStringWCollate CStringCollate;
	typedef CStringWCollateNoCase CStringCollateNoCase;
#else
	typedef CStringACompare CStringCompare;
	typedef CStringACompareNoCase CStringCompareNoCase;
	typedef CStringACollate CStringCollate;
	typedef CStringACollateNoCase CStringCollateNoCase;
#endif

#endif
}

#define rbCSTRING(str1, op, str2) \
	rb2_RB(str1, str2, \
	RichBool::MakeCompareStrings(RichBool::CStringCompare(), RichBool::Dummy() op RichBool::Dummy()))
#define rbvCSTRING(str1, op, str2) \
	rbv2_1_RB(str1, str2, \
	RichBool::MakeCompareStrings(RichBool::CStringCompare(), RichBool::Dummy() op RichBool::Dummy()))

#endif // #if defined(_MT)

#endif // #ifndef MFC_STRING_H__QM
