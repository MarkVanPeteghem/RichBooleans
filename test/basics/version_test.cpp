//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "richbool/richbool.hpp"

#include "rbtest.hpp"

#if defined(RICHBOOL_WIN)
#include <windows.h>
#undef min
#endif

RichBool::detail::String GetDigits(const RichBool::detail::String &str)
{
	RichBool::detail::String rv;
	for (size_t i=0; i<str.size(); ++i)
		if ( (str[i]>='0') && (str[i]<='9') )
			rv += str[i];
	return rv;
}

RichBool::detail::String CurrentDirectory()
{
#ifdef RICHBOOL_USE_WX
	return wxGetCwd();
#elif defined(RICHBOOL_WIN)
	std::string str=" ";
	DWORD len = GetCurrentDirectory(1, &str[0]);
	str.resize(len);
	GetCurrentDirectory(len, &str[0]);
	if (str[len-1]=='\0')
		str.resize(len-1);

	return str;
#else
	char buffer[200];
	return getcwd(buffer, 199);
#endif
}

#if defined(RICHBOOL_WIN) && !defined(__CYGWIN__)
	#define PATHSEP "\\"
#else
	#define PATHSEP "/"
#endif

// If you install Rich Booleans in a non-standard directory,
// the following three tests may fail.
// Some compilers only have the relative path in __FILE__
// (RichBool::GetInstallDirectory() also uses __FILE__),
// while these tests need the full path, so they fail.
// On Linux the include file is in /usr/local/include/richbool,
// so it neither will contain a version.
// In those cases you can safely ignore these failures.
// For Linux we compile the test out because the test mechanism
// aborts the whole procedure if a test fails.


// Only do this for MS VS 8.0 and higher, other compilers have relative paths in __FILE__
#if defined(_MSC_VER) && (_MSC_VER > 1400)

RB_TEST(Version_And_InstallDirectory)
{
	RB_ASSERT(
		rbEQUAL(GetDigits(RichBool::GetInstallDirectory()), GetDigits(RICHBOOL_VERSION))
	);
}

RB_TEST(Version_And_PresentFile)
{
	RB_ASSERT(
		rbEQUAL(GetDigits(__FILE__), GetDigits(RICHBOOL_VERSION))
	);
}

#endif

RB_TEST(Version_And_ThisDirectory)
{
	RB_ASSERT(
		rbEQUAL(GetDigits(CurrentDirectory()), GetDigits(RICHBOOL_VERSION))
	);
}

#ifndef RICHBOOL_USE_WX

#include <fstream>

RB_TEST(Version_And_DocVersion)
{
	std::ifstream file(".." PATHSEP ".." PATHSEP "doc" PATHSEP "richbool.xml");

	std::string version;
	while (file)
	{
		std::string line;
		std::getline(file, line);
		size_t idx = line.find("Version");
		if (idx!=std::string::npos)
		{
			version = line.substr(idx);
			break;
		}
	}

	RB_ASSERT(
		rbEQUAL(GetDigits(version), GetDigits(RICHBOOL_VERSION))
	);
}

RB_TEST(Version_And_AutoConf_Version)
{
	std::ifstream file(".." PATHSEP ".." PATHSEP "configure.ac");

	std::string line;
	std::getline(file, line);

	RB_ASSERT(
		rbEQUAL(GetDigits(line), GetDigits(RICHBOOL_VERSION))
	);
}

RB_TEST(Version_And_Basics_AutoConf_Version)
{
	std::ifstream file(".." PATHSEP "basics" PATHSEP "configure.ac");

	std::string line;
	std::getline(file, line);

	RB_ASSERT(
		rbEQUAL(GetDigits(line), GetDigits(RICHBOOL_VERSION))
	);
}

RB_TEST(Version_And_Macros_AutoConf_Version)
{
	std::ifstream file(".." PATHSEP "macros" PATHSEP "configure.ac");

	std::string line;
	std::getline(file, line);

	RB_ASSERT(
		rbEQUAL(GetDigits(line), GetDigits(RICHBOOL_VERSION))
	);
}

RB_TEST(Version_And_Ranges_AutoConf_Version)
{
	std::ifstream file(".." PATHSEP "ranges" PATHSEP "configure.ac");

	std::string line;
	std::getline(file, line);

	RB_ASSERT(
		rbEQUAL(GetDigits(line), GetDigits(RICHBOOL_VERSION))
	);
}

#endif
