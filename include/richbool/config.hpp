//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_CONFIG_H__QM
#define RICH_BOOL_CONFIG_H__QM

// all tested compilers have std::string
#define RICHBOOL_HAS_STD_STRING

#if defined(_MSC_VER) && (_MSC_VER <= 1300)
	#define RICHBOOL_NO_PARTIAL_TEMPLATE_SPECIALIZATION
	#define RICHBOOL_NO_TEMPLATE_TYPE_LOOKUP

	#define RICHBOOL_WCHAR_T_IS_USHORT 1

#elif defined(_MSC_VER) && (_MSC_VER > 1300)

	// Change this to 1 if you don't want wchar_t treated as a distinct type
	// so that wchar_t's are not shown as characters but as numbers.
	// This requires a compiler switch to make wchar_t not a distinct type.
	#define RICHBOOL_WCHAR_T_IS_USHORT 0

#else
	// for some compilers this requires a switch to make wchar_t a distinct type
	#define RICHBOOL_WCHAR_T_IS_USHORT 0
#endif

#if defined(_MSC_VER)
	namespace RichBool
	{
		template <bool b> struct ConstBool
		{};
		template <> struct ConstBool<false>
		{
			static bool Value()
			{ return false; }
		};
		template <> struct ConstBool<true>
		{
			static bool Value()
			{ return true; }
		};
	}
	#define RICHBOOL_CONST_BOOL(b) ConstBool<b>::Value()
#else
	#define RICHBOOL_CONST_BOOL(b) b
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__CYGWIN__) || defined(__MINGW32__)
#define RICHBOOL_WIN
#endif

//#if !defined(RICHBOOL_USE_WX)
#define RICHBOOL_HAS_WSTRING
//#endif

#if defined(__GNUC__) && (__GNUC__>=4) && defined(__GXX_EXPERIMENTAL_CXX0X__)
    #if defined(__GNUC_MINOR__) && (__GNUC_MINOR__>=5)
        #define RICHBOOL_LAMBDAS
    #endif

    #if defined(__GNUC_MINOR__) && (__GNUC_MINOR__>=4)
        #define RICHBOOL_INITIALIZER_LISTS
    #endif
	// in gcc 4.5 regular expressions will compile but not link
#endif

#if defined(_MSC_VER) && (_MSC_VER >=1600)
    #define RICHBOOL_REGEX
    #define RICHBOOL_LAMBDAS
    // initializer lists are not supported by VS 2011
#endif

#if defined(RICHBOOL_WIN) && !defined(__CYGWIN__)
    #define RICHBOOL_WIDE_CHAR_FILENAMES
#endif

#endif // #ifndef RICH_BOOL_CONFIG_H__QM
