//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef WX_RICH_BOOL_H__QM
#define WX_RICH_BOOL_H__QM

#include "richbool/analysis.hpp"
#include "richbool/string.hpp"
#include "richbool/tostring.hpp"
#include "richbool/getvalue.hpp"
#include "richbool/pair.hpp"
#include "richbool/xcontainers.hpp"

namespace RichBool
{
	struct WxStringCompareBase
	{
		typedef wxChar CharType;

		static inline wxChar* StringTypeToCharType(const wxChar*)
		{
			return (wxChar*)0;
		}

		static inline wxChar* StringTypeToCharType(const wxString&)
		{
			return (wxChar*)0;
		}

		static inline const wxString ToDefaultString(const wxChar *sz)
		{
			return sz;
		}

		static inline const wxString& ToDefaultString(const wxString& str)
		{
			return str;
		}

		enum { ContinueAfterConflict = false };
	};

	struct WxStringCmp: public WxStringCompareBase
	{
		int operator()(wxChar ch1, wxChar ch2) const
		{
			return ch1==ch2 ? 0 : ( ch1 < ch2 ? -1 : 1 );
		}

		// second argument is template parameter,
		// because there is a performance improvement if the second is a wxChar*
		template<typename Str_>
		int operator()(const wxString &str1, const Str_ &str2) const
		{
			return str1.Cmp(str2);
		}

		const detail::String& name() const
		{
			static const detail::String s_name = "wxString::Cmp";
			return s_name;
		}
	};

	class WxStringCmpNoCase: public WxStringCompareBase
	{
		mutable wxString buf1, buf2;
	public:
		WxStringCmpNoCase(): buf1(" "), buf2(" ") {}

		int operator()(wxChar ch1, wxChar ch2) const
		{
			buf1[0] = ch1;
			buf2[0] = ch2;
			return buf1.CmpNoCase(buf2);
		}

		// second argument is template parameter,
		// because there is a performance improvement if the second is a wxChar*
		template<typename Str_>
		int operator()(const wxString &str1, const Str_ &str2) const
		{
			return str1.CmpNoCase(str2);
		}

		const detail::String& name() const
		{
			static const detail::String s_name = "wxString::CmpNoCase";
			return s_name;
		}
	};
}

#define rbWX_STRING(str1, op, str2) \
	rb2_RB(str1, str2, \
	RichBool::MakeCompareStrings(RichBool::WxStringCmp(), RichBool::Dummy() op RichBool::Dummy()))
#define rbvWX_STRING(str1, op, str2) \
	rbv2_1_RB(str1, str2, \
	RichBool::MakeCompareStrings(RichBool::WxStringCmp(), RichBool::Dummy() op RichBool::Dummy()))

#endif // #ifndef WX_RICH_BOOL_H__QM
