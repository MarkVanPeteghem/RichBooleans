//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "richbool/richbool.hpp"

#include "rbtest.hpp"
#include "composite_expressions.hpp"

using namespace RichBool;
using RichBool::detail::String;

struct A {
	A(int a_=0): a(a_) {}

	// we need a virtual method, otherwise RTTI doesn't work on this type
	virtual void f() {}

	int a;

	bool operator==(const A &other) const
	{
		return a==other.a;
	}
};

RB_CONVERSION_HEADER(A)
{
	str << val.a;
	return str;
}

struct B: public A
{
	virtual void f() {}
};

struct C: public B
{
};

struct Z {};


static A a1(1), a2(2), *pa=0;
static B b1;
static C c;
static A *pab = &b1;
static A *pac = &c;

static Z z;

static const String str_pab = PtrToString(pab),
	str_pac = PtrToString(pac);

RB_TEST(TypeInfoEqualPass)
{
	RB_PASS(rbEQUAL_TYPES(&a1, &a2));
	RB_PASS_VB(rbvEQUAL_TYPES(&a1, &a2), &a1);
}

RB_TEST(TypeInfoEqualFail)
{
	SharedAnalysis an = (Analysis*)MakeGeneralAnalysis(false)
		("typeid(").expr(PrefixText("*", "&a1"), ":")("1", true)(")")(":")
		.result(typeid(a1).name())
		(" == typeid(").expr(PrefixText("*", "&b1"), ":")("0", true)(")")(":")
		.result(typeid(b1).name());
	RB_FAIL(rbEQUAL_TYPES(&a1, &b1), *an);
	RB_FAIL_VB(rbvEQUAL_TYPES(&a1, &b1), *an, &a1);
}

RB_TEST(TypeInfoEqualFail_Polymorph)
{
	SharedAnalysis an = (Analysis*)MakeGeneralAnalysis(false)
		("typeid(").expr(PrefixText("*", "pab"), ":")("0", true)(")")(":")
		.result(typeid(B).name())
		(" == typeid(").expr(PrefixText("*", "&a1"), ":")("1", true)(")")(":")
		.result(typeid(A).name());

	RB_FAIL(rbEQUAL_TYPES(pab, &a1), *an);
	RB_FAIL_VB(rbvEQUAL_TYPES(pab, &a1), *an, pab);
}

RB_TEST(TypeInfoEqualFailNullPointer)
{
	if (RichBoolTest::GetLevel()!=1)
	{
		String strPtr = PtrToString(&pa)+" -> "+GetNullPtrString();

		SharedAnalysis an = (Analysis*)MakeGeneralAnalysis(Analysis::BadValue)
			("typeid(").expr(PrefixText("*", "pa"), ":")(strPtr, false)(")")
			(" == typeid(").expr(PrefixText("*", "&b1"), ":")("0", true)(")");

		RB_FAIL(rbEQUAL_TYPES(pa, &b1), *an);
		RB_FAIL_VB(rbvEQUAL_TYPES(pa, &b1), *an, pa);
	}
}

RB_TEST(HasTypePass)
{
	RB_PASS(rbHAS_TYPE(&a1, A));
	RB_PASS(rbHAS_TYPE(pab, B));

	RB_PASS_VB(rbvHAS_TYPE(&a1, A), &a1);
	RB_PASS_VB(rbvHAS_TYPE(pab, B), pab);
}

RB_TEST(HasTypeFail1)
{
	SharedAnalysis an = (Analysis*)MakeGeneralAnalysis(false)
		("typeid(").expr(PrefixText("*", "&a1"), ":")("1", true)(")")(":")
		.result(typeid(A).name())
		(" == ").expr("B", ":")
		(typeid(B).name(), true);

	RB_FAIL(rbHAS_TYPE(&a1, B), *an);
	RB_FAIL_VB(rbvHAS_TYPE(&a1, B), *an, &a1);
}

RB_TEST(HasTypeFail2)
{
	SharedAnalysis an = (Analysis*)MakeGeneralAnalysis(false)
		("typeid(").expr(PrefixText("*", "pab"), ":")("0", true)(")")(":")
		.result(typeid(B).name())
		(" == ").expr("A", ":")
		(typeid(A).name(), true);

	RB_FAIL(rbHAS_TYPE(pab, A), *an);
	RB_FAIL_VB(rbvHAS_TYPE(pab, A), *an, pab);
}

RB_TEST(HasTypeFail_NullPointer)
{
	if (RichBoolTest::GetLevel()!=1)
	{
		String strPtr = PtrToString(&pa)+" -> "+GetNullPtrString();
		SharedAnalysis an = (Analysis*)MakeGeneralAnalysis(Analysis::BadValue)
			("typeid(").expr(PrefixText("*", "pa"), ":")(strPtr, false)(")")
			(" == ").expr("B", ":")
			(typeid(B).name(), true);
		RB_FAIL(rbHAS_TYPE(pa, B), *an);
		RB_FAIL_VB(rbvHAS_TYPE(pa, B), *an, pa);
	}
}

RB_TEST(DynamicCastableRef_Pass)
{
	RB_PASS(rbDYNAMIC_CASTABLE_REF(*pab, B&));
	RB_PASS(rbDYNAMIC_CASTABLE_REF(*pac, B&));

	RB_PASS_VB(rbvDYNAMIC_CASTABLE_REF(*pab, B&), *pab);
	RB_PASS_VB(rbvDYNAMIC_CASTABLE_REF(*pac, B&), *pac);
}

#if !defined(NDEBUG) || !defined(_MSC_VER) || (_MSC_VER > 1200)
// The following two tests throw an exception in Visual C++ 6.0 in Release mode
// so they're excluded in that case.
RB_TEST(DynamicCastableRef_Fail)
{
	SharedAnalysis an = (Analysis*)MakeGeneralAnalysis(false)
		("typeid(").expr("*pab", ":")("0", true)(")")(":")
		.result(typeid(B).name())
		(" -> ").expr("C&", ":")
		(typeid(C&).name(), true);
	RB_FAIL(rbDYNAMIC_CASTABLE_REF(*pab, C&), *an);
	RB_FAIL_VB(rbvDYNAMIC_CASTABLE_REF(*pab, C&), *an, *pab);
}

RB_TEST(DynamicCastableRef_Z_Fail)
{
	SharedAnalysis an = (Analysis*)MakeGeneralAnalysis(false)
		("typeid(").expr("*pab", ":")("0", true)(")")(":")
		.result(typeid(B).name())
		(" -> ").expr("Z&", ":")
		(typeid(Z&).name(), true);
	RB_FAIL(rbDYNAMIC_CASTABLE_REF(*pab, Z&), *an);
	RB_FAIL_VB(rbvDYNAMIC_CASTABLE_REF(*pab, Z&), *an, *pab);
}
#endif

RB_TEST(DynamicCastablePtr_Pass)
{
	RB_PASS(rbDYNAMIC_CASTABLE_PTR(pab, B*));
	RB_PASS(rbDYNAMIC_CASTABLE_PTR(pac, B*));

	RB_PASS_VB(rbvDYNAMIC_CASTABLE_PTR(pab, B*), pab);
	RB_PASS_VB(rbvDYNAMIC_CASTABLE_PTR(pac, B*), pac);
}

RB_TEST(DynamicCastablePtr_Fail)
{
	SharedAnalysis an = (Analysis*)MakeGeneralAnalysis(false)
		("typeid(").expr("pab", ":")(str_pab, true)(")")(":")
		.result(typeid(B).name())
		(" -> ").expr("C*", ":")
		(typeid(C*).name(), true);
	RB_FAIL(rbDYNAMIC_CASTABLE_PTR(pab, C*), *an);
	RB_FAIL_VB(rbvDYNAMIC_CASTABLE_PTR(pab, C*), *an, pab);
}

RB_TEST(DynamicCastablePtr_Z_Fail)
{
	SharedAnalysis an = (Analysis*)MakeGeneralAnalysis(false)
		("typeid(").expr("pab", ":")(str_pab, true)(")")(":")
		.result(typeid(B).name())
		(" -> ").expr("Z*", ":")
		(typeid(Z*).name(), true);
	RB_FAIL(rbDYNAMIC_CASTABLE_PTR(pab, Z*), *an);
	RB_FAIL_VB(rbvDYNAMIC_CASTABLE_PTR(pab, Z*), *an, pab);
}


#ifndef RICHBOOL_NO_PARTIAL_TEMPLATE_SPECIALIZATION

RB_TEST(DynamicCastableGeneral_Ref_Pass)
{
	RB_PASS(rbDYNAMIC_CASTABLE(*pab, B&));
	RB_PASS(rbDYNAMIC_CASTABLE(*pac, B&));

	RB_PASS_VB(rbvDYNAMIC_CASTABLE(*pab, B&), *pab);
	RB_PASS_VB(rbvDYNAMIC_CASTABLE(*pac, B&), *pab);
}

RB_TEST(DynamicCastableGeneral_Ref_Fail)
{
	SharedAnalysis an = (Analysis*)MakeGeneralAnalysis(false)
		("typeid(").expr("*pab", ":")("0", true)(")")(":")
		.result(typeid(B).name())
		(" -> ").expr("C&", ":")
		(typeid(C).name(), true);
	RB_FAIL(rbDYNAMIC_CASTABLE(*pab, C&), *an);
	RB_FAIL_VB(rbvDYNAMIC_CASTABLE(*pab, C&), *an, *pab);
}

RB_TEST(DynamicCastableGeneral_Ref_Z_Fail)
{
	SharedAnalysis an = (Analysis*)MakeGeneralAnalysis(false)
		("typeid(").expr("*pab", ":")("0", true)(")")(":")
		.result(typeid(B).name())
		(" -> ").expr("Z&", ":")
		(typeid(Z).name(), true);
	RB_FAIL(rbDYNAMIC_CASTABLE(*pab, Z&), *an);
	RB_FAIL_VB(rbvDYNAMIC_CASTABLE(*pab, Z&), *an, *pab);
}

RB_TEST(DynamicCastableGeneral_Ptr_Pass)
{
	RB_PASS(rbDYNAMIC_CASTABLE(pab, B*));
	RB_PASS(rbDYNAMIC_CASTABLE(pac, B*));

	RB_PASS_VB(rbvDYNAMIC_CASTABLE(pab, B*), pab);
	RB_PASS_VB(rbvDYNAMIC_CASTABLE(pac, B*), pac);
}

RB_TEST(DynamicCastableGeneral_Ptr_Fail)
{
	SharedAnalysis an = (Analysis*)MakeGeneralAnalysis(false)
		("typeid(").expr("pab", ":")(str_pab, true)(")")(":")
		.result(typeid(B).name())
		(" -> ").expr("C*", ":")
		(typeid(C*).name(), true);
	RB_FAIL(rbDYNAMIC_CASTABLE(pab, C*), *an);
	RB_FAIL_VB(rbvDYNAMIC_CASTABLE(pab, C*), *an, pab);
}

RB_TEST(DynamicCastableGeneral_Ptr_Z_Fail)
{
	SharedAnalysis an = (Analysis*)MakeGeneralAnalysis(false)
		("typeid(").expr("pab", ":")(str_pab, true)(")")(":")
		.result(typeid(B).name())
		(" -> ").expr("Z*", ":")
		(typeid(Z*).name(), true);
	RB_FAIL(rbDYNAMIC_CASTABLE(pab, Z*), *an);
	RB_FAIL_VB(rbvDYNAMIC_CASTABLE(pab, Z*), *an, pab);
}

#endif
