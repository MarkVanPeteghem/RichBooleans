//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef FILE_UTILS_H__QM
#define FILE_UTILS_H__QM

#include <sys/types.h>
#include "richbool/portability.hpp"

/////////////////////////////////////////////////////////
// functionality for checks on the filesystem

namespace RichBool
{
	namespace detail
	{
		template <typename E>
		bool IsSeparator(E ch)
		{
		#if defined(RICHBOOL_WIN)
				return (ch=='\\') || (ch=='/');
		#else
				return (ch=='/');
		#endif
		}

		template <class Str>
		size_t ReverseFindNextSeparator(const Str &path, size_t pos)
		{
				while (pos!=0)
        				if (IsSeparator(path[--pos]))
                				return pos;
				return path.size();
		}
	}

	off_t GetFileLength(const char *filename);
	off_t GetFileLength(const RichBool::detail::String &filename);
#ifdef RICHBOOL_WIDE_CHAR_FILENAMES
	off_t GetFileLength(const wchar_t *filename);
	off_t GetFileLength(const std::wstring &filename);
#endif
}

#endif // #ifndef FILE_UTILS_H__QM
