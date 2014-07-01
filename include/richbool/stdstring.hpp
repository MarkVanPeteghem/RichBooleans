//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICHBOOL_STD_STRING_H__QM
#define RICHBOOL_STD_STRING_H__QM

#include "richbool/string.hpp"
#include <locale>

namespace RichBool
{
	template <typename E>
	struct BasicStringCompareBase
	{
		typedef E CharType;
		typedef typename detail::CharTypeToStringType<E>::StringType StringType;

		static inline E* StringTypeToCharType(const E*)
		{
			return (E*)0;
		}

		template <class Tr, class A>
		static inline E* StringTypeToCharType(const std::basic_string<E, Tr, A> &)
		{
			return (E*)0;
		}

		static inline const std::basic_string<E> ToDefaultString(const E* str)
		{
			return str;
		}

		static inline
		const std::basic_string<E>&
		ToDefaultString(const std::basic_string<E>& str)
		{
			return str;
		}

		template<class Tr, class A>
		static inline
		std::basic_string<E>
		ToDefaultString(const std::basic_string<E, Tr, A>& str)
		{
			return std::basic_string<E>(str.c_str());
		}
	};

	template<typename E>
	struct StringPointerCompare
	{};

	template<>
	struct StringPointerCompare<char>
	{
		static int Compare(const char *str1, const char *str2)
		{
			return strcmp(str1, str2);
		}
		static const char* name()
		{
			return "strcmp";
		}
	};

	template<>
	struct StringPointerCompare<detail::wchar>
	{
		static int Compare(const detail::wchar *str1, const detail::wchar *str2)
		{
			return wcscmp(str1, str2);
		}
		static const char* name()
		{
			return "wcscmp";
		}
	};

	template<typename E>
	struct BasicStringCompare: public BasicStringCompareBase<E>
	{
		int operator()(E ch1, E ch2) const
		{
			return ch1==ch2 ? 0 : (ch1<ch2 ? -1 : 1);
		}

		template <typename StringType1, typename StringType2>
		int operator()(const StringType1 &str1, const StringType2 &str2) const
		{
			return StringPointerCompare<E>::Compare(detail::c_str(str1), detail::c_str(str2));
		}

		const detail::String& name() const
		{
			const static detail::String str = StringPointerCompare<E>::name();
			return str;
		}

		enum { ContinueAfterConflict = false };
	};

	typedef BasicStringCompare<char> StringCompare;
	typedef BasicStringCompare<detail::wchar> WStringCompare;

	template<typename E>
	class BasicStringCompareToUpper: public BasicStringCompareBase<E>
	{
		typedef typename BasicStringCompareBase<E>::StringType StringType;

		template<class Str_, class Range>
		static StringType ToUpper(const Str_ &str, const Range &range)
		{
			StringType stru(detail::str_size(str), ' ');
			typename StringType::iterator itTrg = stru.begin();
			for (typename Range::iterator it=range.begin(str); range(it); ++it, ++itTrg)
				*itTrg = (E)toupper(*it);
			return stru;
		}

	public:
		int operator()(E ch1, E ch2) const
		{
			int ch1u = toupper(ch1), ch2u = toupper(ch2);
			return ch1u==ch2u ? 0 : (ch1u<ch2u ? -1 : 1);
		}

		template <typename StringType1, typename StringType2>
		int operator()(const StringType1 &str1, const StringType2 &str2) const
		{
			return StringPointerCompare<E>::Compare(ToUpper(str1, MakeStringRange(str1)).c_str(),
				ToUpper(str2, MakeStringRange(str2)).c_str());
		}

		const detail::String& name() const
		{
			const static detail::String str =
				StringPointerCompare<E>::name()+detail::String(" toupper");
			return str;
		}

		enum { ContinueAfterConflict = false };
	};

	typedef BasicStringCompareToUpper<char>  StringCompareToUpper;
	typedef BasicStringCompareToUpper<detail::wchar> WStringCompareToUpper;

    namespace detail
    {
        inline StringCompare GetStringCompare(const char*)
        {
            return StringCompare();
        }
#ifdef RICHBOOL_HAS_WSTRING
		inline WStringCompare GetStringCompare(const wchar*)
        {
            return WStringCompare();
        }
#endif
        template <class Tr, class A>
        StringCompare GetStringCompare(const std::basic_string<char, Tr, A> &)
        {
            return StringCompare();
        }
        template <class Tr, class A>
        WStringCompare GetStringCompare(const std::basic_string<wchar, Tr, A> &)
        {
            return WStringCompare();
        }

        inline StringCompareToUpper GetStringCompareToUpper(const char*)
        {
            return StringCompareToUpper();
        }
#ifdef RICHBOOL_HAS_WSTRING
		inline WStringCompareToUpper GetStringCompareToUpper(const wchar*)
        {
            return WStringCompareToUpper();
        }
#endif
        template <class Tr, class A>
        StringCompareToUpper GetStringCompareToUpper(const std::basic_string<char, Tr, A> &)
        {
            return StringCompareToUpper();
        }
        template <class Tr, class A>
        WStringCompareToUpper GetStringCompareToUpper(const std::basic_string<wchar, Tr, A> &)
        {
            return WStringCompareToUpper();
        }
    }

	template<typename E>
	class BasicStringCompareToLower: public BasicStringCompareBase<E>
	{
		typedef typename BasicStringCompareBase<E>::StringType StringType;

		template<class Str_, class Range>
		static StringType ToLower(const Str_ &str, const Range &range)
		{
			StringType strl(detail::str_size(str), ' ');
			typename StringType::iterator itTrg = strl.begin();
			for (typename Range::iterator it=range.begin(str); range(it); ++it, ++itTrg)
				*itTrg = (E)tolower(*it);
			return strl;
		}

	public:
		int operator()(E ch1, E ch2) const
		{
			int ch1l = tolower(ch1), ch2l = tolower(ch2);
			return ch1l==ch2l ? 0 : (ch1l<ch2l ? -1 : 1);
		}

		template <typename StringType1, typename StringType2>
		int operator()(const StringType1 &str1, const StringType2 &str2) const
		{
			return StringPointerCompare<E>::Compare(ToLower(str1, MakeStringRange(str1)).c_str(),
				ToLower(str2, MakeStringRange(str2)).c_str());
		}

		const detail::String& name() const
		{
			const static detail::String str =
				StringPointerCompare<E>::name()+detail::String(" tolower");
			return str;
		}

		enum { ContinueAfterConflict = false };
	};

	typedef BasicStringCompareToLower<char>  StringCompareToLower;
	typedef BasicStringCompareToLower<detail::wchar> WStringCompareToLower;


	template<typename E>
	class BasicCollate: public BasicStringCompareBase<E>
	{
		const std::collate<E> *m_collate;

		detail::String m_name;

	public:
		BasicCollate(const std::locale &loc=std::locale()):
#if defined(_MSC_VER) && (_MSC_VER <= 1300)
			m_collate(&std::use_facet(loc,(std::collate<E>*)0, true))
#else
			m_collate(&std::use_facet<std::collate<E> >(loc))
#endif
		{
			m_name = "locale ";
			m_name += loc.name().c_str();
		}

		int operator()(E ch1, E ch2) const
		{
			return m_collate->compare(&ch1, &ch1+1, &ch2, &ch2+1);
		}

		template <typename StringType1, typename StringType2>
		int operator()(const StringType1 &str1, const StringType2 &str2) const
		{
			const E *b1 = detail::c_str(str1), *b2 = detail::c_str(str2);
			const E *e1 = b1+detail::str_size(str1), *e2 = b2+detail::str_size(str2);
			return m_collate->compare(b1, e1, b2, e2);
		}

		const detail::String& name() const
		{
			return m_name;
		}

		enum { ContinueAfterConflict = true };
	};

	typedef BasicCollate<char> Collate;
	typedef BasicCollate<detail::wchar> WCollate;

	template<typename E>
	class BasicCollateToUpper: public BasicStringCompareBase<E>
	{
		typedef typename BasicStringCompareBase<E>::StringType StringType;

		const std::collate<E> *m_collate;
		const std::ctype<E> *m_ctype;

		detail::String m_name;
	public:
		BasicCollateToUpper(const std::locale &loc=std::locale()):
#if defined(_MSC_VER) && (_MSC_VER <= 1300)
			m_ctype(&std::use_facet(loc,(std::ctype<E>*)0, true)),
			m_collate(&std::use_facet(loc,(std::collate<E>*)0, true))
#else
			m_ctype(&std::use_facet<std::ctype<E> >(loc)),
			m_collate(&std::use_facet<std::collate<E> >(loc))
#endif
		{
			m_name = "locale ";
			m_name += loc.name().c_str();
			m_name += " toupper";
		}

		int operator()(E ch1, E ch2) const
		{
			ch1 = m_ctype->toupper(ch1);
			ch2 = m_ctype->toupper(ch2);
			return m_collate->compare(&ch1, &ch1+1, &ch2, &ch2+1);
		}

		template <typename StringType1, typename StringType2>
		int operator()(const StringType1 &str1, const StringType2 &str2) const
		{
			const size_t len1 = detail::str_size(str1), len2 = detail::str_size(str2);
			StringType str1u(detail::c_str(str1), len1), str2u(detail::c_str(str2), len2);
			E *s1u = &str1u[0], *s2u = &str2u[0];
			m_ctype->toupper(s1u, s1u+len1);
			m_ctype->toupper(s2u, s2u+len2);
			return m_collate->compare(s1u, s1u+len1, s2u, s2u+len2);
		}

		const detail::String& name() const
		{
			return m_name;
		}

		enum { ContinueAfterConflict = true };
	};

	typedef BasicCollateToUpper<char> CollateToUpper;
	typedef BasicCollateToUpper<detail::wchar> WCollateToUpper;

	template<typename E>
	class BasicCollateToLower: public BasicStringCompareBase<E>
	{
		typedef typename BasicStringCompareBase<E>::StringType StringType;

		const std::collate<E> *m_collate;
		const std::ctype<E> *m_ctype;

		detail::String m_name;
	public:
		BasicCollateToLower(const std::locale &loc=std::locale()):
#if defined(_MSC_VER) && (_MSC_VER <= 1300)
			m_ctype(&std::use_facet(loc,(std::ctype<E>*)0, true)),
			m_collate(&std::use_facet(loc,(std::collate<E>*)0, true))
#else
			m_ctype(&std::use_facet<std::ctype<E> >(loc)),
			m_collate(&std::use_facet<std::collate<E> >(loc))
#endif
		{
			m_name = "locale ";
			m_name += loc.name().c_str();
			m_name += " tolower";
		}

		int operator()(E ch1, E ch2) const
		{
			ch1 = m_ctype->tolower(ch1);
			ch2 = m_ctype->tolower(ch2);
			return m_collate->compare(&ch1, &ch1+1, &ch2, &ch2+1);
		}

		template <typename StringType1, typename StringType2>
		int operator()(const StringType1 &str1, const StringType2 &str2) const
		{
			const size_t len1 = detail::str_size(str1), len2 = detail::str_size(str2);
			StringType str1l(detail::c_str(str1), len1), str2l(detail::c_str(str2), len2);
			E *s1l = &str1l[0], *s2l = &str2l[0];
			m_ctype->tolower(s1l, s1l+len1);
			m_ctype->tolower(s2l, s2l+len2);
			return m_collate->compare(s1l, s1l+len1, s2l, s2l+len2);
		}

		const detail::String& name() const
		{
			return m_name;
		}

		enum { ContinueAfterConflict = true };
	};

	typedef BasicCollateToLower<char> CollateToLower;
	typedef BasicCollateToLower<detail::wchar> WCollateToLower;

	typedef CompareStrings<CompareCompletely<StringCompare, EqualRelation>, GetStringValue, GetStringValue> StringsEqualCS;
	typedef CompareStrings<CompareCompletely<WStringCompare, EqualRelation>, GetStringValue, GetStringValue> WStringsEqualCS;
	typedef CompareStrings<CompareCompletely<StringCompareToUpper, EqualRelation>, GetStringValue, GetStringValue> StringsEqualCI;
	typedef CompareStrings<CompareCompletely<WStringCompareToUpper, EqualRelation>, GetStringValue, GetStringValue> WStringsEqualCI;
}

#define rbSTD_STRING(str1, op, str2) \
	rb2_RB(str1, str2, \
	RichBool::MakeCompareStrings(RichBool::StringCompare(), RichBool::Dummy() op RichBool::Dummy()))
#define rbvSTD_STRING(str1, op, str2) \
	rbv2_1_RB(str1, str2, \
	RichBool::MakeCompareStrings(RichBool::StringCompare(), RichBool::Dummy() op RichBool::Dummy()))

#define rbSTD_WSTRING(str1, op, str2) \
	rb2_RB(str1, str2, \
	RichBool::MakeCompareStrings(RichBool::WStringCompare(), RichBool::Dummy() op RichBool::Dummy()))
#define rbvSTD_WSTRING(str1, op, str2) \
	rbv2_1_RB(str1, str2, \
	RichBool::MakeCompareStrings(RichBool::WStringCompare(), RichBool::Dummy() op RichBool::Dummy()))

#endif // #ifndef RICHBOOL_STD_STRING_H__QM
