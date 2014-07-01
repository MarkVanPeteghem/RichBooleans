//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com


#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include "richbool/portability.hpp"

#if defined(RICHBOOL_WIN)
    #include <stdio.h>
    #include <windows.h>
#endif // #if !defined(RICHBOOL_WIN)

namespace RichBool
{
	namespace detail
	{
		RICHBOOL_DLL_API void EscapeChar(char ch, String &str)
		{
			// at this point str should be at least 4 characters,
			// so that in the DLL no memory has to be allocated
			if (ch=='\a')
				str = "\\a";
			else if (ch=='\b')
				str = "\\b";
			else if (ch=='\f')
				str = "\\f";
			else if (ch=='\n')
				str = "\\n";
			else if (ch=='\r')
				str = "\\r";
			else if (ch=='\t')
				str = "\\t";
			else if (ch=='\v')
				str = "\\v";
			else if (ch=='\\')
				str = "\\\\";
			else if (ch==0x7f)
				str = "\\x7f";
			else if (ch<32)
			{
				int n=ch;
				if (n<0) n+=0x100;
	#ifdef RICHBOOL_USE_WX
				str.Printf("\\x%02x", (unsigned int)n);
	#else
				std::ostringstream strstr;
				strstr << "\\x";
				strstr.width(2);
				strstr << std::hex << std::setfill('0') << n;
				str = strstr.str();
	#endif
			}
			else
			{
				str = "";
				str += ch;
			}
		}

		RICHBOOL_DLL_API String EscapeString(const char* str)
		{
			if (!str)
				return "\\NULL";

			String escapeString;
			for ( ; *str; ++str)
			{
				escapeString += EscapeChar(*str);
			}
			return escapeString;
		}

		RICHBOOL_DLL_API String EscapeString(const char* str, size_t n)
		{
			String escapeString;
			for (unsigned int pos=0; pos<n; ++pos)
			{
				char ch = str[pos];
				escapeString += EscapeChar(ch);
			}
			return escapeString;
		}

		RICHBOOL_DLL_API void EscapeChar(wchar ch, String &str)
		{
			// at this point str should be at least 6 characters,
			// so that in the DLL no memory has to be allocated
			if (ch=='\a')
				str = "\\a";
			else if (ch=='\b')
				str = "\\b";
			else if (ch=='\f')
				str = "\\f";
			else if (ch=='\n')
				str = "\\n";
			else if (ch=='\r')
				str = "\\r";
			else if (ch=='\t')
				str = "\\t";
			else if (ch=='\v')
				str = "\\v";
			else if (ch=='\\')
				str = "\\\\";
			else if ( (ch<32) || (ch>=128) )
			{
				int n=ch;
	#ifdef RICHBOOL_USE_WX
				str.Printf("\\x%04x", (unsigned int)n);
	#else
				std::ostringstream strstr;
				strstr << "\\x";
				strstr.width(4);
				strstr << std::hex << std::setfill('0') << n;
				str = strstr.str();
	#endif
			}
			else
			{
				str = "";
				str += (char)ch;
			}
		}

		RICHBOOL_DLL_API String EscapeString(const wchar* str)
		{
			if (!str)
				return "\\NULL";

			String escapeString;
			for ( ; *str; ++str)
			{
				escapeString += EscapeChar(*str);
			}
			return escapeString;
		}

		RICHBOOL_DLL_API String EscapeString(const wchar* str, size_t n)
		{
			String escapeString;
			for (unsigned int pos=0; pos<n; ++pos)
			{
				wchar ch = str[pos];
				escapeString += EscapeChar(ch);
			}
			return escapeString;
		}

		std::string WideStringToString(std::basic_string<wchar_t>::const_iterator Str,
			std::basic_string<wchar_t>::const_iterator End)
		{
			std::string NarrowString;
			for (; Str!=End; ++Str)
			{
				if (*Str>128)
				{
					NarrowString += EscapeChar(*Str);
				}
				else
				{
					NarrowString += (char)*Str;
				}
			}
			return NarrowString;
		}
	}

#if defined(RICHBOOL_WIN)
	const int MAX_LARGE_INTEGER_SIZE = 25;

	RICHBOOL_DLL_API detail::String ToString(const ULARGE_INTEGER &uli)
	{
		char buffer[MAX_LARGE_INTEGER_SIZE+1];
#ifndef __CYGWIN__
		_snprintf(buffer, MAX_LARGE_INTEGER_SIZE, "%I64u", uli);
#else
		snprintf(buffer, MAX_LARGE_INTEGER_SIZE, "%llu", uli);
#endif
		return buffer;
	}

	RICHBOOL_DLL_API detail::String ToString(const LARGE_INTEGER &li)
	{
		char buffer[MAX_LARGE_INTEGER_SIZE+1];
#ifndef __CYGWIN__
		_snprintf(buffer, MAX_LARGE_INTEGER_SIZE, "%I64d", li);
#else
		snprintf(buffer, MAX_LARGE_INTEGER_SIZE, "%lld", li);
#endif
		return buffer;
	}
#endif // #if defined(RICHBOOL_WIN)

}
