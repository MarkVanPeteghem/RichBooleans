//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

struct IntHolder_WithLess
{
	IntHolder_WithLess(int n): a(n) {}
	int a;
};

bool operator<(const IntHolder_WithLess &a1, const IntHolder_WithLess &a2)
{
	return a1.a<a2.a;
}

struct IntHolder_WithMore
{
	IntHolder_WithMore(int n): a(n) {}
	int a;
};

bool operator>(const IntHolder_WithMore &a1, const IntHolder_WithMore &a2)
{
	return a1.a>a2.a;
}

inline RB_CONVERSION_HEADER(IntHolder_WithLess)
{
	str << val.a;
	return str;
}

inline RB_CONVERSION_HEADER(IntHolder_WithMore)
{
	str << val.a;
	return str;
}

inline RichBool::detail::String ToString(IntHolder_WithLess a)
{
	return RichBool::ToString(a.a);
}
inline RichBool::detail::String ToString(IntHolder_WithMore a)
{
	return RichBool::ToString(a.a);
}

