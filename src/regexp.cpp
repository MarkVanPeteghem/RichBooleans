//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include <richbool/config.hpp>
#ifdef RICHBOOL_REGEX

#include "richbool/regexp.hpp"
#include <sstream>

// Note: with MingW this seems to require std=gnu++0x instead of std=c++0x

namespace RichBool
{
	namespace detail
	{
		template <class It>
		It FindMatchingRectangularBracket(It it, It end)
		{
			// necessary to ignore parens inside [ ]
			++it;
			if (it!=end)
			{
				if (*it!='^')
				{
					++it; // if ] is first character it is not end so skip it
				}
				else
				{
					++it;
					if (it!=end && *it==']')
					{
						 // if ^] are first two characters it is not end so skip them
						++it;
					}
				}
			}
			while (it!=end && *it!=']')
			{
				if (*it=='[')
					it = FindMatchingRectangularBracket(it, end);
				++it;
			}
			return it;
		}

		template <class It>
		It FindMatchingParen(It it, It end, bool* HasColon)
		{
			if (HasColon)
			{
				*HasColon = false;
			}
			int level = 1;
			for (++it; it!=end; ++it)
			{
				if (*(it-1)=='\\')
				{
					continue;
				}
				switch (*it)
				{
				case '(':
					++level;
					break;
				case ')':
					--level;
					break;
				case '[':
					it = FindMatchingRectangularBracket(it, end);
					break;
				case ':':
					if (HasColon)
					{
						*HasColon = true;
					}
					break;
				}
				if (level==0)
					return it;
			}
			return end;
		}

		template <class It>
		It FindRepeater(It it, It end)
		{
			if (it==end)
				return it;

			switch (*it)
			{
			case '{':
				++it;
				while (it!=end && *it!='}')
					++it;
				if (it!=end && it+1!=end && *(it+1)=='?')
					++it;
				// intended fall through
			case '?':
				return it+1;
			case '*':
			case '+':
				++it;
				if (it!=end && *it=='?')
					++it;
				// intended fall through
			default:
				return it;
			}
		}


		template <typename charT>
		void TmplSplitRegex(const std::basic_string<charT> &regex, std::vector<RegexPart<charT> > &parts)
		{
			typename std::basic_string<charT>::const_iterator it=regex.begin();
			typename std::basic_string<charT>::const_iterator partStart = it;
			while (it!=regex.end())
			{
				switch (*it)
				{
				case '\\':
					++it;
					if (it!=regex.end())
					{
						if (isdigit(*it))
						{
							if (partStart!=it-1)
							{
								parts.push_back(RegexPart<charT>(std::basic_string<charT>(partStart, it-1), false));
							}
							partStart = it-1;
							++it;
							while (it!=regex.end() && isdigit(*it))
								++it;
							it = FindRepeater(it, regex.end());
							parts.push_back(RegexPart<charT>(std::basic_string<charT>(partStart, it), false, true));
							partStart = it;
						}
						else
						{
							switch (*it)
							{
							case 'A':
							case 'Z':
							case 'z':
							case 'b':
							case 'B':
								if (partStart!=it-1)
								{
									parts.push_back(RegexPart<charT>(std::basic_string<charT>(partStart, it-1), false));
								}
								parts.push_back(RegexPart<charT>(std::basic_string<charT>(it-1, it+1), true));
								++it;
								partStart = it;
								break;
							default:
								++it;
								break;
							}
						}
					}
					break;
				case '(':
					{
						enum { Flag, LookAhead, LookBehind, AtomicGroup, Conditional, Comment }
							GroupType = Flag;
						if (it+1!=regex.end() && *(it+1)=='?')
						{
							if (it+2!=regex.end())
							{
								switch (*(it+2))
								{
								case '=':
								case '!':
									GroupType = LookAhead;
									break;
								case '<':
									GroupType = LookBehind;
									break;
								case '>':
									GroupType = AtomicGroup;
									break;
								case '(':
									GroupType = Conditional;
									break;
								case '#':
									GroupType = Comment;
									break;
								}
							}

							// It's a non capturing group
							typename std::basic_string<charT>::const_iterator ParenPos = it;
							bool HasColon = false;
							it = FindMatchingParen(it, regex.end(), &HasColon);
							it = FindRepeater(it+1, regex.end());

							switch (GroupType)
							{
							case LookBehind:
								if (partStart!=ParenPos)
								{
									parts.push_back(RegexPart<charT>(std::basic_string<charT>(partStart, ParenPos), false));
								}
								partStart = ParenPos;
								break;
							case Flag:
							case AtomicGroup:
							case Conditional:
							case Comment:
								if (partStart!=ParenPos)
								{
									parts.push_back(RegexPart<charT>(std::basic_string<charT>(partStart, ParenPos), false));
								}
								parts.push_back(RegexPart<charT>(std::basic_string<charT>(ParenPos, it), !HasColon && (GroupType==Flag || GroupType==Comment)));
								partStart = it;
								break;
							case LookAhead:
								parts.push_back(RegexPart<charT>(std::basic_string<charT>(partStart, it), false));
								partStart = it;
								break;
							}
						}
						else
						{
							typename std::basic_string<charT>::const_iterator end = FindMatchingParen(it, regex.end(), 0);
							if (partStart!=it)
							{
								parts.push_back(RegexPart<charT>(std::basic_string<charT>(partStart, it), false));
							}
							if (end!=regex.end())
							{
								end = FindRepeater(end+1, regex.end());
								parts.push_back(RegexPart<charT>(std::basic_string<charT>(it, end), false));
								it = end;
								partStart = it;
							}
							else
							{
								it = regex.end();
							}
						}
					}
					break;
				case '[':
					if (partStart!=it)
						parts.push_back(RegexPart<charT>(std::basic_string<charT>(partStart, it), false));
					partStart = it;
					it = FindMatchingRectangularBracket(it, regex.end());
					it = FindRepeater(it+1, regex.end());
					parts.push_back(RegexPart<charT>(std::basic_string<charT>(partStart, it), false));
					partStart = it;
					if (it!=regex.end())
						++it;
					break;
				case '?':
				case '+':
				case '*':
					if (it!=regex.begin())
					{
						if (partStart<it-1)
							parts.push_back(RegexPart<charT>(std::basic_string<charT>(partStart, it-1), false));
						parts.push_back(RegexPart<charT>(std::basic_string<charT>(it-1, it+1), false));
						partStart = it+1;
					}
					++it;
					break;
				case '^':
				case '$':
					if (partStart!=it)
						parts.push_back(RegexPart<charT>(std::basic_string<charT>(partStart, it), false));
					parts.push_back(RegexPart<charT>(std::basic_string<charT>(it, it+1), true));
					++it;
					partStart = it;
					break;
				default:
					++it;
					break;
				}
			}
			if (partStart!=it)
			{
				parts.push_back(RegexPart<charT>(std::basic_string<charT>(partStart, it), false));
			}
		}

		void SplitRegex(const std::string &regex, std::vector<RegexPart<char> > &parts)
		{
			TmplSplitRegex(regex, parts);
		}

		void SplitRegex(const std::wstring &regex, std::vector<RegexPart<wchar_t> > &parts)
		{
			TmplSplitRegex(regex, parts);
		}

		template <typename E>
		std::basic_string<E> BasicToString(int n)
		{
			std::basic_ostringstream<E> strstr;
			strstr << n;
			return strstr.str();
		}

		template <typename E>
		int GetInt(typename std::basic_string<E>::const_iterator &it, typename std::basic_string<E>::const_iterator end)
		{
			int nr = 0;
			while (++it!=end && isdigit(*it))
			{
				nr = nr*10+(*it-'0');
			}
			return nr;
		}

		template <typename E>
		std::basic_string<E> TmplAdjustBackReference(const std::basic_string<E> &str, int inc)
		{
			std::basic_string<E>::const_iterator it = str.begin();
			int nr = GetInt<E>(it, str.end());
			return std::basic_string<E>(str.begin(), str.begin()+1)+BasicToString<E>(nr+inc)+std::basic_string<E>(it, str.end());
		}

		std::string AdjustBackReference(const std::string &str, int inc)
		{
			return TmplAdjustBackReference(str, inc);
		}

		std::wstring AdjustBackReference(const std::wstring &str, int inc)
		{
			return TmplAdjustBackReference(str, inc);
		}
	}

	template <typename charT>
	void GetPartialRegexMatch(const std::basic_string<charT>& str, std::vector<detail::RegexPart<charT> >& Parts, size_t NrParts, detail::String& Result, std::regex_constants::match_flag_type type)
	{
		size_t endPos = 0;

		if (NrParts>0)
		{
			std::basic_string<charT> PartialRegex;
			bool JustFlags = true;
			int NrBackReferencesAdded = 0;
			for (size_t j=0; j<NrParts; ++j)
			{
				if (Parts[j].m_IsFlag)
					PartialRegex += Parts[j].m_Part;
				else
				{
					if (Parts[j].m_IsBackReference)
					{
						PartialRegex += detail::AdjustBackReference(Parts[j].m_Part, NrBackReferencesAdded);
					}
					else if (Parts[j].m_Part[0]!='(')
					{
						PartialRegex += charT('(')+Parts[j].m_Part+charT(')');
						++NrBackReferencesAdded;
					}
					else
					{
						PartialRegex += Parts[j].m_Part;
					}
					JustFlags = false;
				}
			}

			if (!JustFlags)
			{
				std::basic_regex<charT> PartRegex(PartialRegex);
				std::match_results<typename std::basic_string<charT>::const_iterator> match_results;
				std::regex_search(str.begin(), str.end(), match_results, PartRegex, type);

				int Start = match_results.position();
				if (Start!=0)
				{
					std::basic_string<charT> Pre = std::basic_string<charT>(str.begin(), str.begin()+Start);
					Result += "Before: "+ToString(Pre)+"\n";
				}

				int Match = 0;
				NrBackReferencesAdded = 0;
				for (size_t j=0; j<NrParts; ++j)
				{
					if (Parts[j].m_IsFlag)
					{
						Result += ToStringNoEscape(Parts[j].m_Part)+"\n";
					}
					else if (Parts[j].m_IsBackReference)
					{
						typename std::basic_string<charT>::const_iterator it = Parts[j].m_Part.begin();
						int Nr = detail::GetInt<charT>(it, Parts[j].m_Part.end());
						Result += "M "+ToStringNoEscape(Parts[j].m_Part)+": "
							+ToString(match_results.str(Nr+NrBackReferencesAdded))+"\n";
					}
					else
					{
						Result += "M "+ToStringNoEscape(Parts[j].m_Part)+": "
							+ToString(match_results.str(++Match))+"\n";
						if (Parts[j].m_Part[0]!='(')
							++NrBackReferencesAdded;
					}
				}

				endPos = match_results.position()+match_results.length();
			}
			else
			{
				NrParts = 0;
			}
		}

		for (size_t j=NrParts; j<Parts.size(); ++j)
		{
			if (Parts[j].m_IsFlag)
				Result += ToStringNoEscape(Parts[j].m_Part)+"\n";
			else
				Result += "X "+ToStringNoEscape(Parts[j].m_Part)+":\n";
		}

		if (endPos<str.size())
		{
			std::basic_string<charT> Rest = std::basic_string<charT>(str.begin()+endPos, str.end());
			Result += "After : "+ToString(Rest)+"\n";
		}
	}

	template <typename charT>
	detail::String TmplAnalyseRegexMatch(const std::basic_string<charT>& str, const std::basic_string<charT>& regex, std::regex_constants::match_flag_type type)
	{
		detail::String Epilogue;

		std::vector<detail::RegexPart<charT> > Parts;
		SplitRegex(regex, Parts);

		size_t RegexLen = 0;
		std::match_results<typename std::basic_string<charT>::const_iterator> match_results;
		for (size_t i=0; i<Parts.size(); ++i)
		{
			RegexLen += Parts[i].m_Part.size();
			if (Parts[i].m_IsFlag && (i<Parts.size()-1) )
			{
				continue;
			}
			std::basic_regex<charT> PartRegex(regex.begin(), regex.begin()+RegexLen);
			if (!std::regex_search(str.begin(), str.end(), match_results, PartRegex, type))
			{
				GetPartialRegexMatch(str, Parts, i, Epilogue, type);
				break;
			}
		}
		if (Epilogue.empty())
		{
			GetPartialRegexMatch(str, Parts, Parts.size(), Epilogue, type);
		}

		return Epilogue;
	}

	detail::String RegExCore::GetEpilogue(const std::string& str, const std::string& regex, std::regex_constants::match_flag_type type) const
	{
		return TmplAnalyseRegexMatch(str, regex, type);
	}

	detail::String RegExCore::GetEpilogue(const std::wstring& str, const std::wstring& regex, std::regex_constants::match_flag_type type) const
	{
		return TmplAnalyseRegexMatch(str, regex, type);
	}

	detail::String HasRegExCore::GetEpilogue(const std::string& str, const std::string& regex, std::regex_constants::match_flag_type type) const
	{
		return TmplAnalyseRegexMatch(str, regex, type);
	}

	detail::String HasRegExCore::GetEpilogue(const std::wstring& str, const std::wstring& regex, std::regex_constants::match_flag_type type) const
	{
		return TmplAnalyseRegexMatch(str, regex, type);
	}
}

#endif // #ifdef RICHBOOL_REGEX
