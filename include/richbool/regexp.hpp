//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICHBOOL_REGEXP_H__QM
#define RICHBOOL_REGEXP_H__QM

#include <richbool/config.hpp>
#ifdef RICHBOOL_REGEX

#include <regex>
#include <richbool/functors.hpp>
#include <richbool/portability.hpp>

namespace RichBool
{
	namespace detail
	{
		template <typename charT>
		struct RegexPart
		{
			RegexPart(const std::basic_string<charT>& Part, bool IsFlag=false, bool IsBackReference=false)
				: m_Part(Part)
				, m_IsFlag(IsFlag)
				, m_IsBackReference(IsBackReference)
			{}
			std::basic_string<charT> m_Part;
			bool m_IsFlag;
			bool m_IsBackReference;
		};
		void SplitRegex(const std::string& regex, std::vector<RegexPart<char> > &parts);
		void SplitRegex(const std::wstring& regex, std::vector<RegexPart<wchar_t> > &parts);
		std::string AdjustBackReference(const std::string &str, int inc);
		std::wstring AdjustBackReference(const std::wstring &str, int inc);
	}

	struct RegExCore: public FunctorCore
	{
		// char
		bool operator()(const std::string& str, const std::string& regex, std::regex_constants::match_flag_type type=std::regex_constants::match_default) const
		{
			std::regex re(regex.begin(), regex.end());
			return std::regex_match(str.begin(), str.end(), re, type);
		}
		detail::String GetEpilogue(const std::string &str, const std::string &regex, std::regex_constants::match_flag_type type=std::regex_constants::match_default) const;

		// wchar
		bool operator()(const std::wstring& str, const std::wstring& regex, std::regex_constants::match_flag_type type=std::regex_constants::match_default) const
		{
			std::wregex re(regex.begin(), regex.end());
			return std::regex_match(str.begin(), str.end(), re, type);
		}
		detail::String GetEpilogue(const std::wstring &str, const std::wstring &regex, std::regex_constants::match_flag_type type=std::regex_constants::match_default) const;

		const char* GetTextAfter1() const
		{ return " should match regular expression "; }
		const char* GetTextBefore3() const
		{ return ", using flags "; }
	};

	template <class GV1=Value, class GV2=Value,
		class Str1_=MakeString, class Str2_=MakeString>
	struct RegEx: public Wrapper2Arg<RegExCore, GV1, GV2, Str1_, Str2_> {
		RegEx(GV1 gv1=GV1(), GV2 gv2=GV2()):
			Wrapper2Arg<RegExCore, GV1, GV2, Str1_, Str2_>(gv1, gv2)
		{}
	};

	template <class GV1=Value, class GV2=Value,
		class Str1_=MakeString, class Str2_=MakeString>
	struct RegExWithMatchFlag: public Wrapper3Arg<RegExCore, GV1, GV2, Value, Str1_, Str2_, MakeString> {
		RegExWithMatchFlag(GV1 gv1=GV1(), GV2 gv2=GV2()):
			Wrapper3Arg<RegExCore, GV1, GV2, Value, Str1_, Str2_>(gv1, gv2)
		{}
	};


	struct HasRegExCore: public FunctorCore
	{
		// char
		bool operator()(const std::string& str, const std::string& regex, std::regex_constants::match_flag_type type=std::regex_constants::match_default) const
		{
			std::regex re(regex.begin(), regex.end());
			return std::regex_search(str.begin(), str.end(), re, type);
		}
		detail::String GetEpilogue(const std::string &str, const std::string &regex, std::regex_constants::match_flag_type type=std::regex_constants::match_default) const;

		// wchar
		bool operator()(const std::wstring& str, const std::wstring& regex, std::regex_constants::match_flag_type type=std::regex_constants::match_default) const
		{
			std::wregex re(regex.begin(), regex.end());
			return std::regex_search(str.begin(), str.end(), re, type);
		}
		detail::String GetEpilogue(const std::wstring &str, const std::wstring &regex, std::regex_constants::match_flag_type type=std::regex_constants::match_default) const;

		const char* GetTextAfter1() const
		{ return " should have substring matching regular expression "; }
		const char* GetTextBefore3() const
		{ return ", using flags "; }
	};

	template <class GV1=Value, class GV2=Value,
		class Str1_=MakeString, class Str2_=MakeString>
	struct HasRegEx: public Wrapper2Arg<HasRegExCore, GV1, GV2, Str1_, Str2_> {
		HasRegEx(GV1 gv1=GV1(), GV2 gv2=GV2()):
			Wrapper2Arg<HasRegExCore, GV1, GV2, Str1_, Str2_>(gv1, gv2)
		{}
	};

	template <class GV1=Value, class GV2=Value,
		class Str1_=MakeString, class Str2_=MakeString>
	struct HasRegExWithMatchFlag: public Wrapper3Arg<HasRegExCore, GV1, GV2, Value, Str1_, Str2_, MakeString> {
		HasRegExWithMatchFlag(GV1 gv1=GV1(), GV2 gv2=GV2()):
			Wrapper3Arg<HasRegExCore, GV1, GV2, Value, Str1_, Str2_>(gv1, gv2)
		{}
	};

	#define rbREGEXP(str,regex) rb2_RB(str,regex,RegEx<>())
	#define rbvREGEXP(str,regex) rbv2_1_RB(str,regex,RegEx<>())
	#define rbREGEXP_F(str,regex, match_flags) rb3_RB(str,regex,match_flags,RegExWithMatchFlag<>())
	#define rbvREGEXP_F(str,regex, match_flags) rbv3_1_RB(str,regex,match_flags,RegExWithMatchFlag<>())

	#define rbHAS_REGEXP(str,regex) rb2_RB(str,regex,HasRegEx<>())
	#define rbvHAS_REGEXP(str,regex) rbv2_1_RB(str,regex,HasRegEx<>())
	#define rbHAS_REGEXP_F(str,regex, match_flags) rb3_RB(str,regex,match_flags,HasRegExWithMatchFlag<>())
	#define rbvHAS_REGEXP_F(str,regex, match_flags) rbv3_1_RB(str,regex,match_flags,HasRegExWithMatchFlag<>())
}

#endif // #ifdef RICHBOOL_REGEX

#endif // #ifndef RICHBOOL_REGEXP_H__QM
