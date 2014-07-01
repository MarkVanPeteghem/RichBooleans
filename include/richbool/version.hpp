//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#define RICHBOOL_VERSION "2_2_2"

#if !defined(RICHBOOL_DONT_LINK) && !defined(RICHBOOLDLL_EXPORTS)
#	define BOOST_LIB_NAME richbool
#	define QMENTUM_LIB_VERSION RICHBOOL_VERSION
#	include "richbool/auto_link.hpp"
#	undef QMENTUM_LIB_VERSION
#endif

namespace RichBool
{
	inline const char* GetInstallDirectory()
	{
		return __FILE__;
	}
}
