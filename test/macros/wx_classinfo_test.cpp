//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef RICHBOOL_USE_WX

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
	#include "wx/wx.h"
#endif

#include "rbtest.hpp"
#include "composite_expressions.hpp"

#include "richbool/richbool.hpp"
#include "richbool/wx.hpp"

using namespace RichBool;

class wxA: public wxObject
{
	DECLARE_CLASS(wxA)
public:
	wxA(int n=0): m(n) {}

	int m;

	bool operator==(const wxA &other) const
	{
		return m==other.m;
	}
};

IMPLEMENT_CLASS(wxA, wxObject)

class wxB: public wxA
{
	DECLARE_CLASS(wxB)
public:
	wxB(): n(1) {}

	int n;
};

IMPLEMENT_CLASS(wxB, wxA)

RB_CONVERSION_HEADER(wxA)
{
	str << val.m;
	return str;
}

RB_TEST(WxIsKindOf_Pass)
{
	wxB b;

	RB_PASS(rbWX_IS_KIND_OF(&b, "wxA"));
	RB_PASS(rbWX_IS_KIND_OF(&b, "wxB"));

	RB_PASS_VB(rbvWX_IS_KIND_OF(&b, "wxA"), &b);
	RB_PASS_VB(rbvWX_IS_KIND_OF(&b, "wxB"), &b);

	wxClassInfo *cia=wxClassInfo::FindClass("wxA"),
		*cib=wxClassInfo::FindClass("wxB");

	RB_PASS(rbWX_IS_KIND_OF(&b, cia));
	RB_PASS(rbWX_IS_KIND_OF(&b, cib));

	RB_PASS_VB(rbvWX_IS_KIND_OF(&b, cia), &b);
	RB_PASS_VB(rbvWX_IS_KIND_OF(&b, cib), &b);
}

RB_TEST(WxIsKindOf_Fail)
{
	SharedAnalysis an = (Analysis*)MakeGeneralAnalysis(false)
		("wxClassInfo(").expr(PrefixText("*", "&a"), ":")("0", true)(")")(":")
		.result("wxA")
		(" is kind of ").expr("\"wxB\"", ":")
		("wxB", true);

	wxA a;
	RB_FAIL(rbWX_IS_KIND_OF(&a, "wxB"), *an);
	RB_FAIL_VB(rbvWX_IS_KIND_OF(&a, "wxB"), *an, &a);
}

RB_TEST(WxIsKindOf_Fail_WithClassInfo)
{
	SharedAnalysis an = (Analysis*)MakeGeneralAnalysis(false)
		("wxClassInfo(").expr(PrefixText("*", "&a"), ":")("0", true)(")")(":")
		.result("wxA")
		(" is kind of ").expr("cib", ":")
		("wxB", true);

	wxClassInfo *cib=wxClassInfo::FindClass("wxB");

	wxA a;
	RB_FAIL(rbWX_IS_KIND_OF(&a, cib), *an);
	RB_FAIL_VB(rbvWX_IS_KIND_OF(&a, cib), *an, &a);
}

RB_TEST(WxHasType_Pass)
{
	wxA a;

	RB_PASS(rbWX_HAS_TYPE(&a, "wxA"));
	RB_PASS_VB(rbvWX_HAS_TYPE(&a, "wxA"), &a);

	wxClassInfo *cia=wxClassInfo::FindClass("wxA");

	RB_PASS(rbWX_HAS_TYPE(&a, cia));
	RB_PASS_VB(rbvWX_HAS_TYPE(&a, cia), &a);
}

RB_TEST(WxHasType_Fail1)
{
	SharedAnalysis an = (Analysis*)MakeGeneralAnalysis(false)
		("wxClassInfo(").expr(PrefixText("*", "&a"), ":")("0", true)(")")(":")
		.result("wxA")
		(" == ").expr("\"wxB\"", ":")
		("wxB", true);

	wxA a;
	RB_FAIL(rbWX_HAS_TYPE(&a, "wxB"), *an);
	RB_FAIL_VB(rbvWX_HAS_TYPE(&a, "wxB"), *an, &a);

	SharedAnalysis an_ci = (Analysis*)MakeGeneralAnalysis(false)
		("wxClassInfo(").expr(PrefixText("*", "&a"), ":")("0", true)(")")(":")
		.result("wxA")
		(" == ").expr("cib", ":")
		("wxB", true);

	wxClassInfo *cib=wxClassInfo::FindClass("wxB");
	RB_FAIL(rbWX_HAS_TYPE(&a, cib), *an_ci);
	RB_FAIL_VB(rbvWX_HAS_TYPE(&a, cib), *an_ci, &a);
}

RB_TEST(WxHasType_Fail2)
{
	SharedAnalysis an = (Analysis*)MakeGeneralAnalysis(false)
		("wxClassInfo(").expr(PrefixText("*", "&b"), ":")("0", true)(")")(":")
		.result("wxB")
		(" == ").expr("\"wxA\"", ":")
		("wxA", true);

	wxB b;
	RB_FAIL(rbWX_HAS_TYPE(&b, "wxA"), *an);
	RB_FAIL_VB(rbvWX_HAS_TYPE(&b, "wxA"), *an, &b);

	SharedAnalysis an_ci = (Analysis*)MakeGeneralAnalysis(false)
		("wxClassInfo(").expr(PrefixText("*", "&b"), ":")("0", true)(")")(":")
		.result("wxB")
		(" == ").expr("cia", ":")
		("wxA", true);

	wxClassInfo *cia=wxClassInfo::FindClass("wxA");
	RB_FAIL(rbWX_HAS_TYPE(&b, cia), *an_ci);
	RB_FAIL_VB(rbvWX_HAS_TYPE(&b, cia), *an_ci, &b);
}

RB_TEST(WxEqualTypes_Pass)
{
	wxA a1(1), a2(2);
	wxB b1, b2;

	RB_PASS(rbWX_EQUAL_TYPES(&a1, &a2));
	RB_PASS(rbWX_EQUAL_TYPES(&b1, &b2));

	RB_PASS_VB(rbvWX_EQUAL_TYPES(&a1, &a2), &a1);
	RB_PASS_VB(rbvWX_EQUAL_TYPES(&b1, &b2), &b1);
}

RB_TEST(WxEqualTypes_Fail)
{
	SharedAnalysis an = (Analysis*)MakeGeneralAnalysis(false)
		("wxClassInfo(").expr(PrefixText("*", "&a"), ":")("1", true)(")")(":")
		.result("wxA")
		(" == wxClassInfo(").expr(PrefixText("*", "&b"), ":")("0", true)(")")(":")
		.result("wxB");

	wxA a(1);
	wxB b;

	RB_FAIL(rbWX_EQUAL_TYPES(&a, &b), *an);
	RB_FAIL_VB(rbvWX_EQUAL_TYPES(&a, &b), *an, &a);
}

#endif // #ifdef RICHBOOL_USE_WX
