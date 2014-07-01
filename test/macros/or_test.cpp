//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/richbool.hpp"

using namespace RichBool;

RB_TEST(SucceedOr)
{
	RB_PASS(rbOR(rbEQUAL(1,1), rbEQUAL(3,4)));
	RB_PASS(rbOR(rbEQUAL(1,2), rbEQUAL(3,3)));
	RB_PASS(rbOR(rbEQUAL(1,1), rbEQUAL(3,3)));

	RB_PASS(rbOR(true, rbEQUAL(3,4)));
	RB_PASS(rbOR(rbEQUAL(1,2), true));
	RB_PASS(rbOR(true, true));

	RB_PASS(rbOR(rbEQUAL(1,1), false));
	RB_PASS(rbOR(false, rbEQUAL(3,3)));
}

RB_TEST(SucceedOrDoubleEvaluation)
{
	RB_PASS(rbOR_DE(rbEQUAL(1,1), rbEQUAL(3,4)));
	RB_PASS(rbOR_DE(rbEQUAL(1,2), rbEQUAL(3,3)));
	RB_PASS(rbOR_DE(rbEQUAL(1,1), rbEQUAL(3,3)));

	RB_PASS(rbOR_DE(true, rbEQUAL(3,4)));
	RB_PASS(rbOR_DE(rbEQUAL(1,2), true));
	RB_PASS(rbOR_DE(true, true));

	RB_PASS(rbOR_DE(rbEQUAL(1,1), false));
	RB_PASS(rbOR_DE(false, rbEQUAL(3,3)));
}

RB_TEST(SucceedOr_BothEvaluated)
{
	RB_PASS(rbOR_BE(rbEQUAL(1,1), rbEQUAL(3,4)));
	RB_PASS(rbOR_BE(rbEQUAL(1,2), rbEQUAL(3,3)));
	RB_PASS(rbOR_BE(rbEQUAL(1,1), rbEQUAL(3,3)));

	RB_PASS(rbOR_BE(true, rbEQUAL(3,4)));
	RB_PASS(rbOR_BE(rbEQUAL(1,2), true));
	RB_PASS(rbOR_BE(true, true));

	RB_PASS(rbOR_BE(rbEQUAL(1,1), false));
	RB_PASS(rbOR_BE(false, rbEQUAL(3,3)));
}

// In theses tests, each of these lines has to be in a separate test instance
// to speed up compilation time:
RB_TEST(Succeed_OR_OR_DE_First_1)
{
	RB_PASS(rbOR(rbOR_DE(rbEQUAL(1,1), rbEQUAL(1,2)), rbEQUAL(3,4)));
}

RB_TEST(Succeed_OR_OR_DE_First_2)
{
	RB_PASS(rbOR(rbOR_DE(rbEQUAL(1,2), rbEQUAL(1,1)), rbEQUAL(3,4)));
}

RB_TEST(Succeed_OR_OR_DE_First_3)
{
	RB_PASS(rbOR(rbOR_DE(rbEQUAL(1,2), rbEQUAL(1,2)), rbEQUAL(3,3)));
}

RB_TEST(Succeed_OR_OR_DE_Second_1)
{
	RB_PASS(rbOR(rbEQUAL(1,1), rbOR_DE(rbEQUAL(1,2), rbEQUAL(3,4))));
}

RB_TEST(Succeed_OR_OR_DE_Second_2)
{
	RB_PASS(rbOR(rbEQUAL(1,2), rbOR_DE(rbEQUAL(1,1), rbEQUAL(3,4))));
}

RB_TEST(Succeed_OR_OR_DE_Second_3)
{
	RB_PASS(rbOR(rbEQUAL(1,2), rbOR_DE(rbEQUAL(1,2), rbEQUAL(3,3))));
}

RB_TEST(Succeed_OR_OR_BE_First_1)
{
	RB_PASS(rbOR(rbOR_BE(rbEQUAL(1,1), rbEQUAL(1,2)), rbEQUAL(3,4)));
}

RB_TEST(Succeed_OR_OR_BE_First_2)
{
	RB_PASS(rbOR(rbOR_BE(rbEQUAL(1,2), rbEQUAL(1,1)), rbEQUAL(3,4)));
}

RB_TEST(Succeed_OR_OR_BE_First_3)
{
	RB_PASS(rbOR(rbOR_BE(rbEQUAL(1,2), rbEQUAL(1,2)), rbEQUAL(3,3)));
}

RB_TEST(Succeed_OR_OR_BE_Second_1)
{
	RB_PASS(rbOR(rbEQUAL(1,1), rbOR_BE(rbEQUAL(1,2), rbEQUAL(3,4))));
}

RB_TEST(Succeed_OR_OR_BE_Second_2)
{
	RB_PASS(rbOR(rbEQUAL(1,2), rbOR_BE(rbEQUAL(1,1), rbEQUAL(3,4))));
}

RB_TEST(Succeed_OR_OR_BE_Second_3)
{
	RB_PASS(rbOR(rbEQUAL(1,2), rbOR_BE(rbEQUAL(1,2), rbEQUAL(3,3))));
}

RB_TEST(SucceedOr_SideEffect)
{
	int a = 0;

	RB_PASS(rbOR(rbEQUAL(0,a++), rbEQUAL(3,4)));
	RB_ASSERT(rbEQUAL(a,1));

	RB_PASS(rbOR(rbEQUAL(1,1), rbEQUAL(1,a++)));
	RB_ASSERT(rbEQUAL(a,1));

	RB_PASS(rbOR(rbEQUAL(1,2), rbEQUAL(1,a++)));
	RB_ASSERT(rbEQUAL(a,2));

	int b = 0;
	RB_PASS(rbOR(rbEQUAL(1,a++), rbEQUAL(0,b++)));
	RB_ASSERT(rbEQUAL(a,3));
	RB_ASSERT(rbEQUAL(b,1));
}

RB_TEST(SucceedOrBE_SideEffect)
{
	int a = 0;
	RB_PASS(rbOR_BE(rbEQUAL(0,a++), rbEQUAL(3,4)));
	RB_ASSERT(rbEQUAL(a,1));

	a=0;
	RB_PASS(rbOR_BE(rbEQUAL(1,1), rbEQUAL(0,a++)));
	RB_ASSERT(rbEQUAL(a,1));

	a=0;
	RB_PASS(rbOR_BE(rbEQUAL(1,2), rbEQUAL(0,a++)));
	RB_ASSERT(rbEQUAL(a,1));
}

RB_TEST(FailOr_Richbool_Richbool)
{
	Analysis *eq1 = MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" == ")
		.expr("2", ":")("2", true);
	Analysis *eq2 = MakeGeneralAnalysis(false).expr("3", ":")("3", true)(" == ")
		.expr("4", ":")("4", true);

	Bool b1 = eq1, b2 = eq2;

	CombinedAnalysis combined(b1, b2, "&&", false);

	RB_FAIL(rbOR   (rbEQUAL(1,2), rbEQUAL(3,4)), combined);
	RB_FAIL(rbOR_DE(rbEQUAL(1,2), rbEQUAL(3,4)), combined);
	RB_FAIL(rbOR_BE(rbEQUAL(1,2), rbEQUAL(3,4)), combined);
}

RB_TEST(FailOr_Richbool_Bool)
{
	Analysis *eq = MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" == ")
		.expr("2", ":")("2", true);

	Bool b = eq, bFalse = false;

	CombinedAnalysis combined(b, bFalse, "&&", false);

	RB_FAIL(rbOR   (rbEQUAL(1,2), false), combined);
	RB_FAIL(rbOR_DE(rbEQUAL(1,2), false), combined);
	RB_FAIL(rbOR_BE(rbEQUAL(1,2), false), combined);
}

RB_TEST(FailOr_Bool_Richbool)
{
	Analysis *eq = MakeGeneralAnalysis(false).expr("3", ":")("3", true)(" == ")
		.expr("4", ":")("4", true);

	Bool b = eq, bFalse = false;

	CombinedAnalysis combined(bFalse, b, "&&", false);

	RB_FAIL(rbOR   (false, rbEQUAL(3,4)), combined);
	RB_FAIL(rbOR_DE(false, rbEQUAL(3,4)), combined);
	RB_FAIL(rbOR_BE(false, rbEQUAL(3,4)), combined);
}

RB_TEST(FailOr_Bool_Bool)
{
	Bool bFalse = false;

	CombinedAnalysis combined(bFalse, bFalse, "&&", false);

	RB_FAIL(rbOR   (false, false), combined);
	RB_FAIL(rbOR_DE(false, false), combined);
	RB_FAIL(rbOR_BE(false, false), combined);
}

RB_TEST(FailOrComposite)
{
	Analysis *eq1 = MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" == ")
		.expr("2", ":")("2", true);
	Analysis *eq2 = MakeGeneralAnalysis(false).expr("3", ":")("3", true)(" == ")
		.expr("4", ":")("4", true);
	Analysis *eq3 = MakeGeneralAnalysis(false).expr("5", ":")("5", true)(" == ")
		.expr("6", ":")("6", true);

	Bool b1 = eq1, b2 = eq2, b3 = eq3;

	CombinedAnalysis *ci12b = new CombinedAnalysis(b1, b2, "&&", false);
	CombinedAnalysis *ci23 = new CombinedAnalysis(b2, b3, "&&", false);
	Bool b12(ci12b), b23(ci23);
	CombinedAnalysis ci123a(b12, b3, "&&", false), ci123b(b1, b23, "&&", false);

	RB_FAIL(rbOR(rbOR_DE(rbEQUAL(1,2), rbEQUAL(3,4)), rbEQUAL(5,6)), ci123a);
	RB_FAIL(rbOR(rbEQUAL(1,2), rbOR_DE(rbEQUAL(3,4), rbEQUAL(5,6))), ci123b);
	RB_FAIL(rbOR(rbOR_BE(rbEQUAL(1,2), rbEQUAL(3,4)), rbEQUAL(5,6)), ci123a);
	RB_FAIL(rbOR(rbEQUAL(1,2), rbOR_BE(rbEQUAL(3,4), rbEQUAL(5,6))), ci123b);
}
