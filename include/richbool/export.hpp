//  Copyright (C) 2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com


#ifdef RICHBOOLDLL_EXPORTS
	#define RICHBOOL_DLL_API __declspec(dllexport)
#elif defined(RICHBOOLDLL_IMPORTS)
	#define RICHBOOL_DLL_API __declspec(dllimport)
#else
	#define RICHBOOL_DLL_API
#endif
