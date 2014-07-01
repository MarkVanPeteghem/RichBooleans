//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include <sys/stat.h>
#include "richbool/fileutils.hpp"

namespace RichBool
{
#if defined(RICHBOOL_WIN) && !defined(__CYGWIN__)
    #define RICHBOOL_STAT _stat
    #define RICHBOOL_ISDIR(mode) (((mode)&_S_IFMT)==_S_IFDIR)
#else
    #define RICHBOOL_STAT stat
    #define RICHBOOL_ISDIR(mode) S_ISDIR(mode)
#endif

	off_t GetFileLength(const char *filename)
	{
		struct RICHBOOL_STAT st;
		int result = RICHBOOL_STAT(filename, &st);
		if ((result!=0) || (RICHBOOL_ISDIR(st.st_mode)))
			return -1;
		else
			return st.st_size;
	}

	off_t GetFileLength(const RichBool::detail::String &filename)
	{
		return GetFileLength(filename.c_str());
	}

#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
	off_t GetFileLength(const wchar_t *filename)
	{
		struct RICHBOOL_STAT st;
		int result = _wstat(filename, &st);
		if ((result!=0) || (RICHBOOL_ISDIR(st.st_mode)))
			return -1;
		else
			return st.st_size;
	}

	off_t GetFileLength(const std::wstring &filename)
	{
		return GetFileLength(filename.c_str());
	}
#endif
}
