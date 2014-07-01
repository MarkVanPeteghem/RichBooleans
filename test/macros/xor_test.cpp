//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/richbool.hpp"

using namespace RichBool;

// tests for XorBool(bool, bool) function

RB_TEST(Xor)
{
	RB_ASSERT(XorBool(false, false)==false);
	RB_ASSERT(XorBool(true, false)==true);
	RB_ASSERT(XorBool(false, true)==true);
	RB_ASSERT(XorBool(true, true)==false);
}

// tests for rbXOR

RB_TEST(SucceedXor)
{
	RB_PASS(rbXOR(rbEQUAL(1,1), rbEQUAL(2,1)));
	RB_PASS(rbXOR(rbEQUAL(1,2), rbEQUAL(2,2)));
	RB_PASS(rbXOR(true,  rbEQUAL(3,2)));
	RB_PASS(rbXOR(false, rbEQUAL(2,2)));
	RB_PASS(rbXOR(rbEQUAL(1,1), false));
	RB_PASS(rbXOR(rbEQUAL(1,2), true));
	RB_PASS(rbXOR(true, false));
	RB_PASS(rbXOR(false, true));
}

RB_TEST(SucceedXorXor)
{
	RB_PASS(rbXOR(rbXOR(rbEQUAL(1,1), rbEQUAL(2,2)), rbEQUAL(3,3)));
	RB_PASS(rbXOR(rbXOR(rbEQUAL(1,1), rbEQUAL(2,3)), rbEQUAL(3,2)));

	RB_PASS(rbXOR(rbEQUAL(1,1), rbXOR(rbEQUAL(2,2), rbEQUAL(3,3))));
	RB_PASS(rbXOR(rbEQUAL(1,2), rbXOR(rbEQUAL(2,2), rbEQUAL(3,2))));
}

RB_TEST(SucceedXor_SideEffect)
{
	int a=0, b=0;

	RB_PASS(rbXOR(rbEQUAL(0,a++), rbEQUAL(1,b++)));
	RB_ASSERT(rbEQUAL(a,1));
	RB_ASSERT(rbEQUAL(b,1));
}

RB_TEST(FailXor_SideEffect)
{
	int a=0, b=0;

	RB_FAIL_I(rbXOR(rbEQUAL(0,a++), rbEQUAL(0,b++)));
	RB_ASSERT(rbEQUAL(a,1));
	RB_ASSERT(rbEQUAL(b,1));
}


RB_TEST(FailXor)
{
	Analysis *eq1 = MakeGeneralAnalysis(true).expr("1", ":")("1", true)(" == ")
		.expr("1", ":")("1", true);
	Analysis *eq2 = MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" == ")
		.expr("2", ":")("2", true);
	Analysis *eq3 = MakeGeneralAnalysis(true).expr("3", ":")("3", true)(" == ")
		.expr("3", ":")("3", true);
	Analysis *eq4 = MakeGeneralAnalysis(false).expr("3", ":")("3", true)(" == ")
		.expr("4", ":")("4", true);

	Bool b1 = eq1, b2 = eq2, b3 = eq3, b4 = eq4;
	Bool bFalse = false, bTrue = true;
	CombinedAnalysis ci13(b1, b3, "&&", false), ci24(b2, b4, "&&", false),
		ci1t(b1, bTrue, "&&", false), ci2f(b2, bFalse, "&&", false),
		cit1(bTrue, b1, "&&", false), cif2(bFalse, b2, "&&", false),
		ciff(bFalse, bFalse, "&&", false), citt(bTrue, bTrue, "&&", false);

	RB_FAIL(rbXOR(rbEQUAL(1,1), rbEQUAL(3,3)), ci13);
	RB_FAIL(rbXOR(rbEQUAL(1,2), rbEQUAL(3,4)), ci24);
	RB_FAIL(rbXOR(rbEQUAL(1,1), true), ci1t);
	RB_FAIL(rbXOR(rbEQUAL(1,2), false),  ci2f);
	RB_FAIL(rbXOR(true, rbEQUAL(1,1)), cit1);
	RB_FAIL(rbXOR(false, rbEQUAL(1,2)),  cif2);
	RB_FAIL(rbXOR(false, false), ciff);
	RB_FAIL(rbXOR(true, true), citt);
}

RB_TEST(XorXor_Fails1)
{
	Analysis *eq1 = MakeGeneralAnalysis(true).expr("1", ":")("1", true)(" == ")
		.expr("1", ":")("1", true);
	Analysis *eq2 = MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" == ")
		.expr("2", ":")("2", true);
	Analysis *eq3 = MakeGeneralAnalysis(true).expr("3", ":")("3", true)(" == ")
		.expr("3", ":")("3", true);
	Bool b1 = eq1, b2 = eq2, b3 = eq3;

	CombinedAnalysis *c1 = new CombinedAnalysis(b2, b3, "&&", true);
	Bool bc1 = c1;
	CombinedAnalysis c2(b1, bc1, "&&", false);

	RB_FAIL(rbXOR(rbEQUAL(1,1), rbXOR(rbEQUAL(1,2), rbEQUAL(3,3))), c2);
}

RB_TEST(XorXor_Fails2)
{
	Analysis *eq1 = MakeGeneralAnalysis(true).expr("1", ":")("1", true)(" == ")
		.expr("1", ":")("1", true);
	Analysis *eq2 = MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" == ")
		.expr("2", ":")("2", true);
	Analysis *eq3 = MakeGeneralAnalysis(true).expr("3", ":")("3", true)(" == ")
		.expr("3", ":")("3", true);
	Bool b1 = eq1, b2 = eq2, b3 = eq3;

	CombinedAnalysis *c1 = new CombinedAnalysis(b1, b2, "&&", true);
	Bool bc1 = c1;
	CombinedAnalysis c2(bc1, b3, "&&", false);

	RB_FAIL(rbXOR(rbXOR(rbEQUAL(1,1), (rbEQUAL(1,2))), rbEQUAL(3,3)), c2);
}
