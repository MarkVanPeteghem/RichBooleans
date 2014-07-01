//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#if defined(_MSC_VER) && defined(_MT) && !defined(RICHBOOL_USE_WX)

#define VC_EXTRALEAN
#include <afxwin.h>

#include "rbtest.hpp"
#include "richbool/richbool.hpp"
#include "richbool/mfcstring.hpp"
#include "richbool/mfcstream.hpp"

#include "testable_analysis_with_strings.hpp"

using namespace RichBool;
using RichBool::detail::String;

// stream MFC objects

RB_TEST(Stream_CString)
{
	CString cstr = "abc\t\xf0";

	String str = ToString(cstr);

	RB_PASS(rbEQUAL(str, "abc\\t\\xf0"));
}


RB_TEST(Stream_POINT)
{
	POINT pt = { 5, 9 };

	String str = ToString(pt);

	RB_PASS(rbEQUAL(str, "(5,9)"));
}

RB_TEST(Stream_CPoint)
{
	CPoint pt;
	pt.x = 5;
	pt.y = 9;

	String str = ToString(pt);

	RB_PASS(rbEQUAL(str, "(5,9)"));
}

RB_TEST(Stream_SIZE)
{
	SIZE s = { 5, 9 };

	String str = ToString(s);

	RB_PASS(rbEQUAL(str, "(5,9)"));
}

RB_TEST(Stream_CSize)
{
	CSize s;
	s.cx = 5;
	s.cy = 9;

	String str = ToString(s);

	RB_PASS(rbEQUAL(str, "(5,9)"));
}

#if _MSC_VER < 1300
RB_TEST(Stream_CTime)
{
	CTime t = CTime::GetCurrentTime( );

	String str = ToString(t);

	RB_PASS(rbEQUAL(str, (LPCSTR)t.Format("%c")));
}
#endif

RB_TEST(Stream_RECT)
{
	RECT rc;
	rc.left = 1;
	rc.top = 5;
	rc.right = 10;
	rc.bottom = -1;

	String str = ToString(rc);

	RB_PASS(rbEQUAL(str, "(1,5)-(10,-1)"));
}

RB_TEST(Stream_CRect)
{
	CRect rc;
	rc.left = 1;
	rc.top = 5;
	rc.right = 10;
	rc.bottom = -1;

	String str = ToString(rc);

	RB_PASS(rbEQUAL(str, "(1,5)-(10,-1)"));
}

RB_TEST(Stream_CString_InAnalysis)
{
	CString cstr = "abc";
	SharedAnalysis analysis =
		(Analysis*)MakeGeneralAnalysis(true)(cstr, Value(), MakeString());

	String str = ToString(*analysis);
	RB_PASS(rbEQUAL(str, "<abc> - ok"));
}


// CStringCompare

RB_TEST(CStringCompare_Equal_Pass)
{
	CString str = "abc";
	RB_PASS(rbSTRING("abc", ==, "abc", CStringCompare()));
	RB_PASS(rbSTRING(str,   ==, "abc", CStringCompare()));
	RB_PASS(rbSTRING("abc", ==, str,   CStringCompare()));
	RB_PASS(rbSTRING(str,   ==, str,   CStringCompare()));

	RB_PASS_V(rbvSTRING("abc", ==, "abc", CStringCompare()), "abc");
	RB_PASS_V(rbvSTRING(str,   ==, "abc", CStringCompare()), str);
	RB_PASS_V(rbvSTRING("abc", ==, str,   CStringCompare()), "abc");
	RB_PASS_V(rbvSTRING(str,   ==, str,   CStringCompare()), str);

	RB_PASS(rbCSTRING(str,  ==, str));
	RB_PASS_V(rbvCSTRING(str,  ==, str), str);
}

RB_TEST(CStringCompare_Less_Pass)
{
	CString str1 = "abc", str2 = "abd";

	RB_PASS(rbSTRING(str1, <, str2, CStringCompare()));
	RB_PASS(rbCSTRING(str1, <, str2));
}

RB_TEST(CStringCompare_More_Pass)
{
	CString str1 = "abd", str2 = "abc";

	RB_PASS(rbSTRING(str1, >, str2, CStringCompare()));
	RB_PASS(rbCSTRING(str1, >, str2));
}

RB_TEST(CStringCompare_NotEqual_Pass)
{
	CString str1 = "abd", str2 = "abc";

	RB_PASS(rbSTRING(str1, !=, str2, CStringCompare()));
	RB_PASS(rbCSTRING(str1, !=, str2));
	RB_PASS(rbCSTRING(str2, !=, str1));
}

RB_TEST(CStringCompare_Equal_Fail)
{
	TestableAnalysisOfStrings an("abce", "abde", "str1", "str2", "MMXM", " == ", "CStringA Compare");

	CString str1 = "abce", str2 = "abde";

	RB_FAIL(rbSTRING (str1, ==, str2, CStringCompare()), an);
	RB_FAIL(rbCSTRING(str1, ==, str2), an);
}

RB_TEST(CStringCompare_Less_Fail)
{
	TestableAnalysisOfStrings an("abde", "abce", "str1", "str2", "MMX ", " < ", "CStringA Compare");

	CString str1 = "abde", str2 = "abce";

	RB_FAIL( rbSTRING(str1, <, str2, CStringCompare()), an);
	RB_FAIL(rbCSTRING(str1, <, str2), an);
}

RB_TEST(CStringCompare_More_Fail)
{
	TestableAnalysisOfStrings an("abce", "abde", "str1", "str2", "MMX ", " > ", "CStringA Compare");

	CString str1 = "abce", str2 = "abde";

	RB_FAIL( rbSTRING(str1, >, str2, CStringCompare()), an);
	RB_FAIL(rbCSTRING(str1, >, str2), an);
}


// CStringCompareNoCase

RB_TEST(CStringCompareNoCase_Equal_Pass)
{
	CString str = "abc";
	RB_PASS(rbSTRING(str,   ==, "ABC", CStringCompareNoCase()));
	RB_PASS(rbSTRING("ABC", ==, str,   CStringCompareNoCase()));
}

RB_TEST(CStringCompareNoCase_Less_Pass)
{
	CString str1 = "abc";

	RB_PASS(rbSTRING(str1,  <, "ABD", CStringCompareNoCase()));
	RB_PASS(rbSTRING("ABB", <, str1,  CStringCompareNoCase()));
}

RB_TEST(CStringCompareNoCase_More_Pass)
{
	CString str1 = "abc";

	RB_PASS(rbSTRING(str1,  >, "ABB", CStringCompareNoCase()));
	RB_PASS(rbSTRING("ABD", >, str1,  CStringCompareNoCase()));
}

RB_TEST(CStringCompareNoCase_Equal_Fail)
{
	TestableAnalysisOfStrings an("ABCE", "abde", "str1", "str2", "MMXM", " == ", "CStringA CompareNoCase");

	CString str1 = "ABCE", str2 = "abde";

	RB_FAIL(rbSTRING(str1, ==, str2, CStringCompareNoCase()), an);
}

RB_TEST(CStringCompareNoCase_Less_Fail)
{
	TestableAnalysisOfStrings an("abde", "ABCE", "str1", "str2", "MMX ", " < ", "CStringA CompareNoCase");

	CString str1 = "abde", str2 = "ABCE";

	RB_FAIL(rbSTRING(str1, <, str2, CStringCompareNoCase()), an);
}

RB_TEST(CStringCompareNoCase_More_Fail)
{
	TestableAnalysisOfStrings an("ABCE", "abde", "str1", "str2", "MMX ", " > ", "CStringA CompareNoCase");

	CString str1 = "ABCE", str2 = "abde";

	RB_FAIL(rbSTRING(str1, >, str2, CStringCompareNoCase()), an);
}

// CStringCollate

RB_TEST(CStringCollate_Equal_Pass)
{
	CString str = "abc";
	RB_PASS(rbSTRING("abc", ==, "abc", CStringCollate()));
	RB_PASS(rbSTRING(str,   ==, "abc", CStringCollate()));
	RB_PASS(rbSTRING("abc", ==, str,   CStringCollate()));
	RB_PASS(rbSTRING(str,   ==, str,   CStringCollate()));
}

RB_TEST(CStringCollate_Less_Pass)
{
	CString str1 = "abc", str2 = "abd";

	RB_PASS(rbSTRING(str1, <, str2, CStringCollate()));
}

RB_TEST(CStringCollate_More_Pass)
{
	CString str1 = "abd", str2 = "abc";

	RB_PASS(rbSTRING(str1, >, str2, CStringCollate()));
}

RB_TEST(CStringCollate_Equal_Fail)
{
	TestableAnalysisOfStrings an("abce", "abde", "str1", "str2", "MMXM", " == ", "CStringA Collate");

	CString str1 = "abce", str2 = "abde";

	RB_FAIL( rbSTRING(str1, ==, str2, CStringCollate()), an);
}

RB_TEST(CStringCollate_Less_Fail)
{
	TestableAnalysisOfStrings an("abde", "abce", "str1", "str2", "MMXM", " < ", "CStringA Collate");

	CString str1 = "abde", str2 = "abce";

	RB_FAIL( rbSTRING(str1, <, str2, CStringCollate()), an);
}

RB_TEST(CStringCollate_More_Fail)
{
	TestableAnalysisOfStrings an("abce", "abde", "str1", "str2", "MMXM", " > ", "CStringA Collate");

	CString str1 = "abce", str2 = "abde";

	RB_FAIL( rbSTRING(str1, >, str2, CStringCollate()), an);
}


// CStringCollateNoCase

RB_TEST(CStringCollateNoCase_Equal_Pass)
{
	CString str = "abc";
	RB_PASS(rbSTRING(str,   ==, "ABC", CStringCollateNoCase()));
	RB_PASS(rbSTRING("ABC", ==, str,   CStringCollateNoCase()));
}

RB_TEST(CStringCollateNoCase_Less_Pass)
{
	CString str1 = "abc";

	RB_PASS(rbSTRING(str1,  <, "ABD", CStringCollateNoCase()));
	RB_PASS(rbSTRING("ABB", <, str1,  CStringCollateNoCase()));
}

RB_TEST(CStringCollateNoCase_More_Pass)
{
	CString str1 = "abc";

	RB_PASS(rbSTRING(str1,  >, "ABB", CStringCollateNoCase()));
	RB_PASS(rbSTRING("ABD", >, str1,  CStringCollateNoCase()));
}

RB_TEST(CStringCollateNoCase_Equal_Fail)
{
	TestableAnalysisOfStrings an("ABCE", "abde", "str1", "str2", "MMXM", " == ", "CStringA CollateNoCase");

	CString str1 = "ABCE", str2 = "abde";

	RB_FAIL(rbSTRING(str1, ==, str2, CStringCollateNoCase()), an);
}

RB_TEST(CStringCollateNoCase_Less_Fail)
{
	TestableAnalysisOfStrings an("abde", "ABCE", "str1", "str2", "MMXM", " < ", "CStringA CollateNoCase");

	CString str1 = "abde", str2 = "ABCE";

	RB_FAIL(rbSTRING(str1, <, str2, CStringCollateNoCase()), an);
}

RB_TEST(CStringCollateNoCase_More_Fail)
{
	TestableAnalysisOfStrings an("ABCE", "abde", "str1", "str2", "MMXM", " > ", "CStringA CollateNoCase");

	CString str1 = "ABCE", str2 = "abde";

	RB_FAIL(rbSTRING(str1, >, str2, CStringCollateNoCase()), an);
}

#if _MSC_VER >= 1300
RB_TEST(Stream_CStringW)
{
	CStringW cstr = L"abc\x345";

	String str = ToString(cstr);

	RB_PASS(rbEQUAL(str, "abc\\x0345"));
}

RB_TEST(Stream_CStringW_InAnalysis)
{
	CStringW cstr = L"abc\x0345";
	SharedAnalysis analysis =
		(Analysis*)MakeGeneralAnalysis(true)(cstr, Value(), MakeString());

	String str = ToString(*analysis);
	RB_PASS(rbEQUAL(str, "<abc\\x0345> - ok"));
}

RB_TEST(CStringWCompare_Equal_Pass)
{
	CStringW str = L"abc";
	RB_PASS(rbSTRING(L"abc", ==, L"abc", CStringWCompare()));
	RB_PASS(rbSTRING(str,    ==, L"abc", CStringWCompare()));
	RB_PASS(rbSTRING(L"abc", ==, str,    CStringWCompare()));
	RB_PASS(rbSTRING(str,    ==, str,    CStringWCompare()));
}

RB_TEST(CStringWCompareNoCase_Equal_Fail)
{
	TestableAnalysisOfWStrings an(L"ABCE", L"abde", "str1", "str2", "MMXM", " == ", "CStringW CompareNoCase");

	CStringW str1 = L"ABCE", str2 = L"abde";

	RB_FAIL(rbSTRING(str1, ==, str2, CStringWCompareNoCase()), an);
}

#endif // #if _MSC_VER >= 1300

struct S {
   CString a;
   CString GetA() {return a;}
};

RB_TEST(CStringCompare_Equal_Pass_WithDataRetriever)
{
	// creëer object dat CString uit S haalt:
	typedef GetMemberArg<S,CString,CString> GetAFromS;
	GetAFromS get_a_from_s(&S::a, ".a");

	typedef RichBool::CompareCompletely<RichBool::CStringCompare> CompareCString;

	// creëer object dat een CString uit een S vergelijkt met een gegeven CString:
	typedef RichBool::CompareStrings<CompareCString, GetAFromS>
		CompareStringFromS;
	CompareStringFromS compareStringFromS(CompareCString(), get_a_from_s);

	// creëer object dat een CString vastbindt op het vorig object,
	// zodat dit nieuw object op een enkel S object werkt:
	RichBool::BindArg2Of2<CompareStringFromS, CString>
		is_abc(compareStringFromS, "abc");

	S s[4];
	s[0].a = "xyz";
	s[1].a = "xyz";
	s[2].a = "abc";
	s[3].a = "xyz";

	RB_PASS(rbIN_ARRAY(s, Unique<>().That(is_abc)));
}

#endif
