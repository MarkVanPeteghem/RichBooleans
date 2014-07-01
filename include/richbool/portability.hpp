//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_PORTABILITY_H__QM
#define RICH_BOOL_PORTABILITY_H__QM

#if defined(_MSC_VER) && _MSC_VER<=1300
#pragma warning(disable: 4786)
#pragma warning(disable: 4284)
#endif

#include "richbool/config.hpp"
#include "richbool/export.hpp"
#include <string>

namespace RichBool
{
	namespace detail
	{
		template <typename CharType>
		struct CharTypeToStringType
		{
			typedef int StringType; // should not be used
		};
	}

	struct StreamSingle
	{
		template <class Stream, typename T>
		void operator()(Stream &str, const T &t) const
		{
			str << t;
		}
	};

	template <class Streamer1=StreamSingle, class Streamer2=StreamSingle>
	struct StreamPair
	{
		StreamPair(Streamer1 streamer1_=Streamer1(), Streamer2 streamer2_=Streamer2()):
			streamer1(streamer1_), streamer2(streamer2_) {}

		template <class Stream, typename T>
		void operator()(Stream &str, const T &t) const
		{
			str << '(';
			streamer1(str, t.first);
			str << ',';
			streamer2(str, t.second);
			str << ')';
		}

		Streamer1 streamer1;
		Streamer2 streamer2;
	};

	template<class Stream, typename It, class Streamer>
	void StreamRange(Stream &stream, It begin, It end, Streamer streamer)
	{
		stream << '[';
		bool first = true;
		for (It it=begin; it!=end; ++it)
		{
			if (!first)
				stream << ' ';
			else
				first = false;
			streamer(stream, *it);
		}
		stream << ']';
	}

	template <class Streamer=StreamSingle>
	struct StreamContainer
	{
		StreamContainer(Streamer streamer_=Streamer()): streamer(streamer_) {}

		template <class Stream, typename C>
		void operator()(Stream &str, const C &c) const
		{
			StreamRange(str, c.begin(), c.end(), streamer);
		}

		Streamer streamer;
	};

	template <class Streamer=StreamSingle>
	struct StreamXContainer
	{
		StreamXContainer(Streamer streamer_=Streamer()): streamer(streamer_) {}

		template <class Stream, typename C>
		void operator()(Stream &str, const C &c) const
		{
			StreamRange(str, begin(c), end(c), streamer);
		}

		Streamer streamer;
	};

	template <typename T>
	struct GetStreamer
	{
		typedef StreamSingle Type;
	};

	template <class Stream, typename T>
	void StreamOut(Stream &stream, const T &t)
	{
		typename GetStreamer<T>::Type streamer;
		streamer(stream, t);
	}
}

#define RICHBOOL_CONTAINER_TO_STRING(CONTAINER_TYPE) \
namespace RichBool { \
	template <> struct GetStreamer<CONTAINER_TYPE > \
	{ typedef StreamContainer<GetStreamer<CONTAINER_TYPE::value_type>::Type> Type; }; \
}

#define RICHBOOL_XCONTAINER_TO_STRING(CONTAINER_TYPE) \
namespace RichBool { \
	template <> struct GetStreamer<CONTAINER_TYPE > \
	{ typedef StreamXContainer<GetStreamer<CONTAINER_TYPE::value_type>::Type> Type; }; \
}

#if defined(RICHBOOL_USE_WX)

#include <wx/string.h>
#include <wx/mstream.h>
#include <wx/txtstrm.h>
#include <wx/dynarray.h>
#include <wx/hashset.h>
#include <wx/longlong.h>

namespace RichBool
{
	namespace detail
	{
		typedef wxString String;
		typedef wxTextOutputStream OutStream;
		typedef wxTextInputStream InStream;

		typedef wxArrayString StringArray;
		WX_DECLARE_HASH_SET(wxString, wxStringHash, wxStringEqual, StringSet);
		typedef wchar_t wchar;

		WX_DEFINE_ARRAY_INT(bool, BoolVector);

		template <>
		struct CharTypeToStringType<wxChar>
		{
			typedef String StringType;
		};
#ifdef RICHBOOL_HAS_WSTRING
		typedef std::wstring WString;

		template <>
		struct CharTypeToStringType<wchar>
		{
			typedef WString StringType;
		};
#endif

		RICHBOOL_DLL_API String EscapeString(const wxChar *str);
		RICHBOOL_DLL_API String EscapeString(const wchar_t *str);
		RICHBOOL_DLL_API String EscapeString(const wxChar *str, size_t size);
		inline String EscapeString(const String &str)
		{
			return EscapeString(str.c_str(), str.size());
		}

		inline void AddString(StringArray &array, const String &str)
		{
			array.Add(str);
		}

		inline const wxChar* c_str(const String &str) { return str.c_str(); }
		inline const wxChar* c_str(const wxChar *str) { return str; }
		inline const wchar* c_str(const wchar *str) { return str; }
		inline wchar* c_str(wchar *str) { return str; }

		inline bool is_empty(const String &str) { return str.empty(); }

		inline size_t str_size(const String &str) { return str.size(); }
		inline size_t str_size(const wxChar *str) { return wxStrlen(str); }
		inline size_t str_size(const wchar *str) { return wcslen(str); }

#ifdef RICHBOOL_HAS_STD_STRING
#ifdef RICHBOOL_HAS_WSTRING
		template <typename E, class Tr, class A>
		inline const E* c_str(const std::basic_string<E, Tr, A> &str) { return str.c_str(); }
		template <typename E, class Tr, class A>
		inline size_t str_size(const std::basic_string<E, Tr, A> &str) { return str.size(); }
		template <typename E, class Tr, class A>
		inline bool is_empty(const std::basic_string<E, Tr, A> &str) { return str.empty(); }
#endif
#endif

		template<class Container>
		inline size_t array_size(const Container &c)
		{ return c.GetCount(); }

		template<class Container>
		inline void clear(Container &c)
		{ c.Clear(); }

		inline wxTextOutputStream &Endl(wxTextOutputStream &stream)
		{
			return endl(stream);
		}

		inline void Add(BoolVector &bv, bool b)
		{
			bv.Add(b);
		}
	}

	template <class Streamer>
	struct CustomMakeString
	{
		enum { showString = true };
		template <typename T>
		wxString operator()(const T &t) const
		{
			wxMemoryOutputStream memStream;
			wxTextOutputStream stream(memStream);
			Streamer()(stream, t);
			wxString str;
			int len = memStream.TellO();
			if (len!=0)
			{
				memStream.CopyTo(str.GetWriteBuf(len), len);
				str.UngetWriteBuf();
			}
			return str;
		}
	};

	// ToString is not in the namespace detail,
	// because users are allowed to overload it for their own types

	template<typename T>
	wxString ToString(const T &val)
	{
		// we need to do is in two lines to get it to compile with
		// both MSVC 6.0 and gcc
		typedef typename GetStreamer<T>::Type Type;
		CustomMakeString<Type> streamer;

		return streamer(val);
	}

	inline wxString ToString(const wxString &val)
	{
		return detail::EscapeString(val);
	}

#ifdef RICHBOOL_HAS_STD_STRING
	namespace detail
	{
		template <typename E, class Tr, class A>
		inline String EscapeString(const std::basic_string<E, Tr, A> &str)
		{
			return EscapeString(str.c_str());
		}
	}
#if !defined (_MSC_VER) || (_MSC_VER>1300)
	template <typename E, class Tr, class A>
	wxString ToString(const std::basic_string<E, Tr, A> &val)
	{
		return detail::EscapeString(val.c_str());
	}
#else
	inline wxString ToString(const std::wstring &val)
	{
		return detail::EscapeString(val.c_str());
	}
#endif
#endif

	template<typename T>
	wxString ToStringNoEscape(const T &val)
	{
		return ToString(val);
	}

	inline wxString ToStringNoEscape(const wxString &val)
	{
		return val;
	}

#ifdef RICHBOOL_HAS_STD_STRING
	inline wxString ToStringNoEscape(const std::string &val)
	{
		return wxString(val.c_str(), val.size());
	}
#endif

// optimized version for some types
#define RICHBOOL_WX_TOSTRING_WITH_WXSTRING(type) \
	inline wxString ToString(type n) \
	{ \
		wxString str; \
		str << n; \
		return str; \
	}

	RICHBOOL_WX_TOSTRING_WITH_WXSTRING(short)
	RICHBOOL_WX_TOSTRING_WITH_WXSTRING(unsigned short)
	RICHBOOL_WX_TOSTRING_WITH_WXSTRING(int)
	RICHBOOL_WX_TOSTRING_WITH_WXSTRING(unsigned int)
	RICHBOOL_WX_TOSTRING_WITH_WXSTRING(long)
	RICHBOOL_WX_TOSTRING_WITH_WXSTRING(unsigned long)
#if defined wxLongLong_t && !defined wxLongLongIsLong && wxCHECK_VERSION(2, 6, 3)
	RICHBOOL_WX_TOSTRING_WITH_WXSTRING(wxLongLong_t)
	RICHBOOL_WX_TOSTRING_WITH_WXSTRING(wxULongLong_t)
#endif

#undef RICHBOOL_WX_TOSTRING_WITH_WXSTRING

	inline wxString ToString(const wxLongLong &val)
	{
		return val.ToString();
	}

	inline wxString ToString(const wxULongLong &val)
	{
		return val.ToString();
	}

	inline wxString ToString(const wxClassInfo &ci)
	{
		return ci.GetClassName();
	}

	namespace detail
	{
		inline String IntToHex(int n)
		{
			wxString str;
			str.Printf("0x%08x", n);
			return str;
		}
	}
}

#define RICHBOOL_WX_MAP_TO_STRING(MAP) \
namespace RichBool { \
	template <> struct GetStreamer<MAP> \
	{ typedef StreamContainer<StreamPair<GetStreamer<MAP::key_type>::Type, \
		GetStreamer<MAP::mapped_type>::Type> > Type; }; \
}

#else // #if defined(RICHBOOL_USE_WX)


// default is std::string

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include <string.h>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <deque>
#include <sstream>
#include <iomanip>

namespace RichBool
{
	namespace detail
	{
		typedef std::string String;
		typedef std::ostream OutStream;
		typedef std::istream InStream;
		typedef wchar_t wchar;

		typedef std::vector<bool> BoolVector;

		template <>
		struct CharTypeToStringType<char>
		{
			typedef String StringType;
		};

#ifdef RICHBOOL_HAS_WSTRING
		typedef std::wstring WString;

		template <>
		struct CharTypeToStringType<wchar>
		{
			typedef WString StringType;
		};
#endif

		typedef std::vector<std::string> StringArray;
		typedef std::set<std::string> StringSet;

		RICHBOOL_DLL_API String EscapeString(const char* str);
		RICHBOOL_DLL_API String EscapeString(const wchar* str);

		RICHBOOL_DLL_API String EscapeString(const char* str, size_t n);
		RICHBOOL_DLL_API String EscapeString(const wchar* str, size_t n);

		template<typename E, class Tr, class A>
		String EscapeString(const std::basic_string<E, Tr, A> &str)
		{
			return EscapeString(str.c_str(), str.size());
		}

		void inline AddString(StringArray &array, const String &str)
		{
			array.push_back(str);
		}

		template<typename E, class Tr, class A>
		inline const E* c_str(const std::basic_string<E, Tr, A> &str)
		{
			return str.c_str();
		}
		inline const char* c_str(const char *str) { return str; }
		inline const wchar* c_str(const wchar *str) { return str; }

		template<typename E, class Tr, class A>
		inline E* c_str(std::basic_string<E, Tr, A> &str)
		{
			return &str[0];
		}
		inline char* c_str(char *str) { return str; }
		inline wchar* c_str(wchar *str) { return str; }

		inline bool is_empty(const String &str) { return str.empty(); }
#ifdef RICHBOOL_HAS_WSTRING
		inline bool is_empty(const WString &str) { return str.empty(); }
#endif
		inline size_t str_size(const char *str) { return strlen(str); }
		inline size_t str_size(const wchar *str) { return wcslen(str); }
		template<class Str_>
		inline size_t str_size(const Str_ &str) { return str.size(); }

		template<class Container>
		inline size_t array_size(const Container &c)
		{ return c.size(); }

		template<class Container>
		inline void clear(Container &c)
		{ c.clear(); }

		template <typename E, typename T>
		std::basic_ostream<E, T>& Endl(std::basic_ostream<E, T> &os)
		{
#if defined(RICHBOOL_WIN)
			// This is necessary so that analyses of more than one line
			// are shown correctly in the dialog box of ModAssertWin32
			os << "\r\n";
			return os;
#else
			return std::endl(os);
#endif
		}

		inline void Add(BoolVector &bv, bool b)
		{
			bv.push_back(b);
		}

		std::string WideStringToString(std::basic_string<wchar_t>::const_iterator Str,
			std::basic_string<wchar_t>::const_iterator End);
	}

	template <class Streamer>
	struct CustomMakeString
	{
		enum { showString = true };
		template <typename T>
		std::string operator()(const T &t) const
		{
			std::ostringstream strstr;
			Streamer()(strstr, t);
			return strstr.str();
		}
	};

	// ToString is not in the namespace detail,
	// because users are allowed to overload it for their own types

	template<typename T>
	std::string ToString(const T &val)
	{
		typedef typename GetStreamer<T>::Type Type;
		CustomMakeString<Type> streamer;
		return streamer(val);
	}

#if !defined(RICHBOOL_NO_PARTIAL_TEMPLATE_SPECIALIZATION)
	template<typename E, class Tr, class A>
	inline std::string ToString(const std::basic_string<E, Tr, A> &str)
	{
		return detail::EscapeString(str.c_str(), str.size());
	}
#else
	inline std::string ToString(const std::string &str)
	{
		return detail::EscapeString(str.c_str(), str.size());
	}

	template<class Tr, class A>
	inline std::ostream& operator<<(std::ostream& stream,
		const std::basic_string<detail::wchar, Tr, A> &str)
	{
		stream << detail::EscapeString(str.c_str(), str.size());
		return stream;
	}
#endif

	template<typename T>
	std::string ToStringNoEscape(const T &val)
	{
		typedef typename GetStreamer<T>::Type Type;
		CustomMakeString<Type> streamer;
		return streamer(val);
	}

	namespace detail
	{
		template <typename T>
		inline String ToHex(T t)
		{
			std::ostringstream strstr;
			strstr << "0x" << std::setw(2*sizeof(T)) << std::hex << std::setfill('0') << t;
			return strstr.str();
		}

		inline String IntToHex(int n)
		{
			return ToHex(n);
		}
	}

#if !defined(RICHBOOL_NO_PARTIAL_TEMPLATE_SPECIALIZATION)
	template<class Tr, class A>
	inline std::string ToStringNoEscape(const std::basic_string<char, Tr, A> &str)
	{
		return std::string(str.c_str(), str.size());
	}
	template<class Tr, class A>
	inline std::string ToStringNoEscape(const std::basic_string<wchar_t, Tr, A> &str)
	{
		return detail::WideStringToString(str.begin(), str.end());
	}
#else
	inline std::string ToStringNoEscape(const std::string &str)
	{
		return str;
	}
#endif
}

#ifdef RICHBOOL_NO_PARTIAL_TEMPLATE_SPECIALIZATION

#define RICHBOOL_STD_MAP_TO_STRING(K_, V_) \
namespace RichBool { \
	template <> struct GetStreamer<std::map<K_, V_ > > \
	{ typedef StreamContainer<StreamPair<GetStreamer<K_>::Type, GetStreamer<V_>::Type> > Type; }; \
}

#define RICHBOOL_STD_MAP_TO_STRING_P(K_, V_, P_) \
namespace RichBool { \
	template <> struct GetStreamer<std::map<K_, V_, P_ > > \
	{ typedef StreamContainer<StreamPair<GetStreamer<K_>::Type, GetStreamer<V_>::Type> > Type; }; \
}

#define RICHBOOL_STD_MAP_TO_STRING_PA(K_, V_, P_, A_) \
namespace RichBool { \
	template <> struct GetStreamer<std::map<K_, V_, P_, A_ > > \
	{ typedef StreamContainer<StreamPair<GetStreamer<K_>::Type, GetStreamer<V_>::Type> > Type; }; \
}

#define RICHBOOL_STD_MULTIMAP_TO_STRING(K_, V_) \
namespace RichBool { \
	template <> struct GetStreamer<std::multimap<K_, V_ > > \
	{ typedef StreamContainer<StreamPair<GetStreamer<K_>::Type, GetStreamer<V_>::Type> > Type; }; \
}

#define RICHBOOL_STD_MULTIMAP_TO_STRING_P(K_, V_, P_) \
namespace RichBool { \
	template <> struct GetStreamer<std::multimap<K_, V_, P_ > > \
	{ typedef StreamContainer<StreamPair<GetStreamer<K_>::Type, GetStreamer<V_>::Type> > Type; }; \
}

#define RICHBOOL_STD_MULTIMAP_TO_STRING_PA(K_, V_, P_, A_) \
namespace RichBool { \
	template <> struct GetStreamer<std::multimap<K_, V_, P_, A_ > > \
	{ typedef StreamContainer<StreamPair<GetStreamer<K_>::Type, GetStreamer<V_>::Type> > Type; }; \
}

#define RICHBOOL_PAIR_TO_STRING(T1, T2) \
namespace RichBool { \
	template <> struct GetStreamer<std::pair<T1, T2> > \
	{ typedef StreamPair<GetStreamer<T1>::Type, GetStreamer<T2>::Type> Type; }; \
}

RICHBOOL_CONTAINER_TO_STRING(std::vector<char>)
RICHBOOL_CONTAINER_TO_STRING(std::vector<short>)
RICHBOOL_CONTAINER_TO_STRING(std::vector<int>)
RICHBOOL_CONTAINER_TO_STRING(std::vector<long>)
RICHBOOL_CONTAINER_TO_STRING(std::vector<unsigned char>)
RICHBOOL_CONTAINER_TO_STRING(std::vector<unsigned short>)
RICHBOOL_CONTAINER_TO_STRING(std::vector<unsigned int>)
RICHBOOL_CONTAINER_TO_STRING(std::vector<unsigned long>)
RICHBOOL_CONTAINER_TO_STRING(std::vector<float>)
RICHBOOL_CONTAINER_TO_STRING(std::vector<double>)
RICHBOOL_CONTAINER_TO_STRING(std::vector<std::string>)
RICHBOOL_CONTAINER_TO_STRING(std::vector<const char*>)

RICHBOOL_CONTAINER_TO_STRING(std::list<char>)
RICHBOOL_CONTAINER_TO_STRING(std::list<short>)
RICHBOOL_CONTAINER_TO_STRING(std::list<int>)
RICHBOOL_CONTAINER_TO_STRING(std::list<long>)
RICHBOOL_CONTAINER_TO_STRING(std::list<unsigned char>)
RICHBOOL_CONTAINER_TO_STRING(std::list<unsigned short>)
RICHBOOL_CONTAINER_TO_STRING(std::list<unsigned int>)
RICHBOOL_CONTAINER_TO_STRING(std::list<unsigned long>)
RICHBOOL_CONTAINER_TO_STRING(std::list<float>)
RICHBOOL_CONTAINER_TO_STRING(std::list<double>)
RICHBOOL_CONTAINER_TO_STRING(std::list<std::string>)
RICHBOOL_CONTAINER_TO_STRING(std::list<const char*>)

RICHBOOL_CONTAINER_TO_STRING(std::set<char>)
RICHBOOL_CONTAINER_TO_STRING(std::set<short>)
RICHBOOL_CONTAINER_TO_STRING(std::set<int>)
RICHBOOL_CONTAINER_TO_STRING(std::set<long>)
RICHBOOL_CONTAINER_TO_STRING(std::set<unsigned char>)
RICHBOOL_CONTAINER_TO_STRING(std::set<unsigned short>)
RICHBOOL_CONTAINER_TO_STRING(std::set<unsigned int>)
RICHBOOL_CONTAINER_TO_STRING(std::set<unsigned long>)
RICHBOOL_CONTAINER_TO_STRING(std::set<float>)
RICHBOOL_CONTAINER_TO_STRING(std::set<double>)
RICHBOOL_CONTAINER_TO_STRING(std::set<std::string>)
RICHBOOL_CONTAINER_TO_STRING(std::set<const char*>)

RICHBOOL_CONTAINER_TO_STRING(std::multiset<char>)
RICHBOOL_CONTAINER_TO_STRING(std::multiset<short>)
RICHBOOL_CONTAINER_TO_STRING(std::multiset<int>)
RICHBOOL_CONTAINER_TO_STRING(std::multiset<long>)
RICHBOOL_CONTAINER_TO_STRING(std::multiset<unsigned char>)
RICHBOOL_CONTAINER_TO_STRING(std::multiset<unsigned short>)
RICHBOOL_CONTAINER_TO_STRING(std::multiset<unsigned int>)
RICHBOOL_CONTAINER_TO_STRING(std::multiset<unsigned long>)
RICHBOOL_CONTAINER_TO_STRING(std::multiset<float>)
RICHBOOL_CONTAINER_TO_STRING(std::multiset<double>)
RICHBOOL_CONTAINER_TO_STRING(std::multiset<std::string>)
RICHBOOL_CONTAINER_TO_STRING(std::multiset<const char*>)

RICHBOOL_CONTAINER_TO_STRING(std::deque<char>)
RICHBOOL_CONTAINER_TO_STRING(std::deque<short>)
RICHBOOL_CONTAINER_TO_STRING(std::deque<int>)
RICHBOOL_CONTAINER_TO_STRING(std::deque<long>)
RICHBOOL_CONTAINER_TO_STRING(std::deque<unsigned char>)
RICHBOOL_CONTAINER_TO_STRING(std::deque<unsigned short>)
RICHBOOL_CONTAINER_TO_STRING(std::deque<unsigned int>)
RICHBOOL_CONTAINER_TO_STRING(std::deque<unsigned long>)
RICHBOOL_CONTAINER_TO_STRING(std::deque<float>)
RICHBOOL_CONTAINER_TO_STRING(std::deque<double>)
RICHBOOL_CONTAINER_TO_STRING(std::deque<std::string>)
RICHBOOL_CONTAINER_TO_STRING(std::deque<const char*>)

#else

#define RICHBOOL_TEMPLATE_CONTAINER_TO_STRING(CONTAINER_TYPE) \
namespace RichBool { \
	template <typename T, class A_> struct GetStreamer<CONTAINER_TYPE<T, A_> > \
	{ typedef StreamContainer<typename GetStreamer<T>::Type > Type; }; \
}

#define RICHBOOL_TEMPLATE_SET_TO_STRING(SET_TYPE) \
namespace RichBool { \
	template <typename T, class P_, class A_> struct GetStreamer<SET_TYPE<T, P_, A_> > \
	{ typedef StreamContainer<typename GetStreamer<T>::Type > Type; }; \
}

RICHBOOL_TEMPLATE_CONTAINER_TO_STRING(std::vector)
RICHBOOL_TEMPLATE_CONTAINER_TO_STRING(std::list)
RICHBOOL_TEMPLATE_CONTAINER_TO_STRING(std::deque)
RICHBOOL_TEMPLATE_SET_TO_STRING(std::set)
RICHBOOL_TEMPLATE_SET_TO_STRING(std::multiset)

namespace RichBool {
	template<typename T1, typename T2>
	struct GetStreamer<std::pair<T1, T2> >
	{ typedef StreamPair<typename GetStreamer<T1>::Type,
		typename GetStreamer<T2>::Type> Type; };
}

#define RICHBOOL_STD_TEMPLATE_MAP_TO_STRING(MAP) \
namespace RichBool { \
	template<typename K_, typename V_, class P_, class A_> \
	struct GetStreamer<std::MAP<K_, V_, P_, A_> > \
	{ typedef StreamContainer<StreamPair<typename GetStreamer<K_>::Type, \
		typename GetStreamer<V_>::Type> > Type; }; \
}

RICHBOOL_STD_TEMPLATE_MAP_TO_STRING(map)
RICHBOOL_STD_TEMPLATE_MAP_TO_STRING(multimap)

#define RICHBOOL_STD_MAP_TO_STRING(K_, V_)
#define RICHBOOL_STD_MAP_TO_STRING_P(K_, V_, P_)
#define RICHBOOL_STD_MAP_TO_STRING_PA(K_, V_, P_, A_)
#define RICHBOOL_STD_MULTIMAP_TO_STRING(K_, V_)
#define RICHBOOL_STD_MULTIMAP_TO_STRING_P(K_, V_, P_)
#define RICHBOOL_STD_MULTIMAP_TO_STRING_PA(K_, V_, P_, A_)
#define RICHBOOL_PAIR_TO_STRING(T1, T2)

#endif

#endif // #if defined(RICHBOOL_USE_WX)

#define RB_CONVERSION_HEADER(TYPE) \
	RichBool::detail::OutStream& operator<<(RichBool::detail::OutStream &str, const TYPE &val)

namespace RichBool
{
#ifdef RICHBOOL_USE_WX
	inline wxString PtrToString(const void *ptr)
	{
		wxString str;
#if defined(RICHBOOL_WIN)
		str.Printf("0x%p", ptr);
#else
		str.Printf("%p", ptr);
#endif
		return str;
	}
#else
	inline std::string PtrToString(const void *ptr)
	{
		return detail::ToHex(ptr);
	}
#endif


	namespace detail
	{
		RICHBOOL_DLL_API void EscapeChar(char ch, String &str);
		RICHBOOL_DLL_API void EscapeChar(wchar ch, String &str);
		inline String EscapeChar(char ch)
		{
			String str;
			str.resize(4);
			EscapeChar(ch, str);
			return str;
		}
		inline String EscapeChar(wchar ch)
		{
			String str;
			str.resize(6);
			EscapeChar(ch, str);
			return str;
		}
	}

	inline detail::String ToString(char ch)
	{
		return detail::EscapeChar(ch);
	}

	inline detail::String ToString(unsigned char ch)
	{
		return detail::EscapeChar((char)ch);
	}

	// If you get a compile error here, you probably use WxWidgets
	// with Unicode characters. This is not yet supported.
	inline detail::String ToString(char *sz)
	{ return detail::EscapeString(sz); }

	inline detail::String ToString(unsigned char *sz)
	{ return detail::EscapeString((char*)sz); }

	inline detail::String ToString(const char *sz)
	{ return detail::EscapeString(sz); }

	inline detail::String ToString(const unsigned char *sz)
	{ return detail::EscapeString((const char*)sz); }

#if !defined(RICHBOOL_NO_PARTIAL_TEMPLATE_SPECIALIZATION)
	template <typename T>
	inline detail::String ToString(T *p)
	{ return PtrToString(p); }
	template <typename T>
	inline detail::String ToString(const T *p)
	{ return PtrToString(p); }
#else
	#define RICHBOOL_POINTER_TO_STRING(T) \
		inline detail::String ToString(T *p) \
		{ return PtrToString(p); } \
		inline detail::String ToString(const T *p) \
		{ return PtrToString(p); }

	RICHBOOL_POINTER_TO_STRING(void)
	RICHBOOL_POINTER_TO_STRING(short)
	RICHBOOL_POINTER_TO_STRING(unsigned short)
	RICHBOOL_POINTER_TO_STRING(long)
	RICHBOOL_POINTER_TO_STRING(unsigned long)
	RICHBOOL_POINTER_TO_STRING(int)
	RICHBOOL_POINTER_TO_STRING(unsigned int)
	RICHBOOL_POINTER_TO_STRING(float)
	RICHBOOL_POINTER_TO_STRING(double)

	#undef RICHBOOL_POINTER_TO_STRING
#endif

#if !RICHBOOL_WCHAR_T_IS_USHORT
	// if you get a compile error here with MSVC++ 2003, 2005 or another compiler,
	// you should use a switch to make wchar_t a built-in type
	inline detail::String ToString(detail::wchar ch)
	{
		return detail::EscapeChar(ch);
	}

	inline detail::String ToString(detail::wchar *sz)
	{ return detail::EscapeString(sz); }

	inline detail::String ToString(const detail::wchar *sz)
	{ return detail::EscapeString(sz); }
#endif
}

#if defined(RICHBOOL_WIN)

typedef union _LARGE_INTEGER  LARGE_INTEGER;
typedef union _ULARGE_INTEGER ULARGE_INTEGER;

namespace RichBool
{
	RICHBOOL_DLL_API detail::String ToString(const ULARGE_INTEGER &uli);
	RICHBOOL_DLL_API detail::String ToString(const LARGE_INTEGER &li);
}

#endif

#endif // #ifndef RICH_BOOL_PORTABILITY_H__QM
