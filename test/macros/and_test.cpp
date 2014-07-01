//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/richbool.hpp"

using namespace RichBool;

// tests for rbAND, rbAND_BE and rbAND_DE
RB_TEST(SucceedAnd)
{
	RB_PASS(rbAND(rbEQUAL(1,1), rbEQUAL(2,2)));
	RB_PASS(rbAND(true, rbEQUAL(3,3)));
	RB_PASS(rbAND(rbEQUAL(1,1), true));
	RB_PASS(rbAND(true, true));

	RB_PASS(rbAND_DE(rbEQUAL(1,1), rbEQUAL(2,2)));
	RB_PASS(rbAND_DE(true, rbEQUAL(3,3)));
	RB_PASS(rbAND_DE(rbEQUAL(1,1), true));
	RB_PASS(rbAND_DE(true, true));

	RB_PASS(rbAND_BE(rbEQUAL(1,1), rbEQUAL(2,2)));
	RB_PASS(rbAND_BE(true, rbEQUAL(3,3)));
	RB_PASS(rbAND_BE(rbEQUAL(1,1), true));
	RB_PASS(rbAND_BE(true, true));
}

// In theses tests, each of these lines has to be in a separate test instance
// to speed up compilation time:
RB_TEST(SucceedAndAnd1)
{
	RB_PASS(rbAND(rbAND_DE(rbEQUAL(1,1), rbEQUAL(2,2)), rbEQUAL(3,3)));
}

RB_TEST(SucceedAndAnd2)
{
	RB_PASS(rbAND(rbAND_BE(rbEQUAL(1,1), rbEQUAL(2,2)), rbEQUAL(3,3)));
}

RB_TEST(SucceedAndAnd3)
{
	RB_PASS(rbAND(rbEQUAL(1,1), rbAND_DE(rbEQUAL(2,2), rbEQUAL(3,3))));
}

RB_TEST(SucceedAndAnd4)
{
	RB_PASS(rbAND(rbEQUAL(1,1), rbAND_BE(rbEQUAL(2,2), rbEQUAL(3,3))));
}

RB_TEST(SucceedAnd_SideEffect)
{
	int a=0, b=0;

	RB_PASS(rbAND(rbEQUAL(0,a++), rbEQUAL(0,b++)));
	RB_ASSERT(rbEQUAL(a,1));
	RB_ASSERT(rbEQUAL(b,1));
}

RB_TEST(SucceedAndBE_SideEffect)
{
	int a=0, b=0;

	RB_PASS(rbAND_BE(rbEQUAL(0,a++), rbEQUAL(0,b++)));
	RB_ASSERT(rbEQUAL(a,1));
	RB_ASSERT(rbEQUAL(b,1));
}

RB_TEST(FailAnd_SideEffect)
{
	int a=0, b=0;

	RB_FAIL_I(rbAND(rbEQUAL(1,a++), rbEQUAL(0,b++)));
	RB_ASSERT(rbEQUAL(a,1));
	RB_ASSERT(rbEQUAL(b,0));
}

RB_TEST(FailAndBE_SideEffect)
{
	int a=0, b=0;

	RB_FAIL_I(rbAND_BE(rbEQUAL(1,a++), rbEQUAL(0,b++)));
	RB_ASSERT(rbEQUAL(a,1));
	RB_ASSERT(rbEQUAL(b,1));
}


RB_TEST(FailAndFirst)
{
	Analysis *eq1 = MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" == ")
		.expr("2", ":")("2", true);
	Analysis *eq2 = MakeGeneralAnalysis(false).expr("3", ":")("3", true)(" == ")
		.expr("4", ":")("4", true);
	Analysis *eq3 = MakeGeneralAnalysis(true ).expr("3", ":")("3", true)(" == ")
		.expr("3", ":")("3", true);

	AnalysisNotEvaluated *noteval = new AnalysisNotEvaluated;
	Bool bNE = noteval;
	Bool b1 = eq1, b2 = eq2, b3 = eq3;
	Bool bFalse = false, bTrue = true;
	CombinedAnalysis ci1n(b1, bNE, "&&", false), cibn(bFalse, bNE, "&&", false),
		ci1t(b1,     RichBoolTest::GetLevel()==3 ? b3 : bTrue, "&&", false),
		cibt(bFalse, RichBoolTest::GetLevel()==3 ? b3 : bTrue, "&&", false);

	RB_FAIL(rbAND(rbEQUAL(1,2), rbEQUAL(3,3)), ci1n);
	RB_FAIL(rbAND_BE(rbEQUAL(1,2), rbEQUAL(3,3)), ci1t);
	RB_FAIL(rbAND_DE(rbEQUAL(1,2), rbEQUAL(3,3)), ci1n);
	RB_FAIL(rbAND(false, rbEQUAL(3,3)), cibn);
	RB_FAIL(rbAND_BE(false, rbEQUAL(3,3)), cibt);
	RB_FAIL(rbAND_DE(false, rbEQUAL(3,3)), cibn);
}


RB_TEST(FailAndSecond)
{
	Analysis
		*eq1 = MakeGeneralAnalysis(true).expr("1", ":")("1", true)(" == ")
			.expr("1", ":")("1", true),
		*eq2 = MakeGeneralAnalysis(false).expr("3", ":")("3", true)(" == ")
			.expr("4", ":")("4", true);

	Bool bFalse = false, bTrue = true, b1 = eq1, b2 = eq2;
	CombinedAnalysis cit1(RichBoolTest::GetLevel()==3 ? b1 : bTrue, b2, "&&", false),
		citf(RichBoolTest::GetLevel()==3 ? b1 : bTrue, bFalse, "&&", false);

	RB_FAIL(rbAND(rbEQUAL(1,1), rbEQUAL(3,4)), cit1);
	RB_FAIL(rbAND_BE(rbEQUAL(1,1), rbEQUAL(3,4)), cit1);
	RB_FAIL(rbAND_DE(rbEQUAL(1,1), rbEQUAL(3,4)), cit1);
	RB_FAIL(rbAND(rbEQUAL(1,1), false), citf);
	RB_FAIL(rbAND_BE(rbEQUAL(1,1), false), citf);
	RB_FAIL(rbAND_DE(rbEQUAL(1,1), false), citf);
}

RB_TEST(AndAnd1_FirstFails)
{
	AnalysisNotEvaluated *analysisNoteval = new AnalysisNotEvaluated;
	Bool bFalse = false, bTrue = true, bNoteval = analysisNoteval;

	CombinedAnalysis cifn(bFalse, bNoteval, "&&", false);

	RB_FAIL(rbAND(false, rbAND_BE(true, true)), cifn);
	RB_FAIL(rbAND(false, rbAND_DE(true, true)), cifn);
}

RB_TEST(AndAnd1_SecondFails)
{
	AnalysisNotEvaluated *analysisNoteval = new AnalysisNotEvaluated;
	Bool bFalse = false, bTrue = true, bNoteval = analysisNoteval;

	CombinedAnalysis *cift = new CombinedAnalysis(bFalse, bTrue, "&&", false);
	Bool bcft = cift;
	CombinedAnalysis cit_ft(bTrue, bcft, "&&", false);

	RB_FAIL(rbAND(true, rbAND_BE(false, true)), cit_ft);

	CombinedAnalysis *cifn = new CombinedAnalysis(bFalse, bNoteval, "&&", false);
	Bool bcfn = cifn;
	CombinedAnalysis cit_fn(bTrue, bcfn, "&&", false);

	RB_FAIL(rbAND(true, rbAND_DE(false, true)), cit_fn);
}

RB_TEST(AndAnd1_ThirdFails)
{
	AnalysisNotEvaluated *analysisNoteval = new AnalysisNotEvaluated;
	Bool bFalse = false, bTrue = true, bNoteval = analysisNoteval;

	CombinedAnalysis *citf = new CombinedAnalysis(bTrue, bFalse, "&&", false);
	Bool bctf = citf;
	CombinedAnalysis cit_tf(bTrue, bctf, "&&", false);

	RB_FAIL(rbAND(true, rbAND_BE(true, false)), cit_tf);
	RB_FAIL(rbAND(true, rbAND_DE(true, false)), cit_tf);
}

RB_TEST(AndAnd2_FirstFails)
{
	AnalysisNotEvaluated *analysisNoteval = new AnalysisNotEvaluated;
	Bool bFalse = false, bTrue = true, bNoteval = analysisNoteval;

	CombinedAnalysis *cift = new CombinedAnalysis(bFalse, bTrue, "&&", false);
	Bool bft = cift;
	CombinedAnalysis cift_n(bft, bNoteval, "&&", false);

	RB_FAIL(rbAND(rbAND_BE(false, true), true), cift_n);

	CombinedAnalysis *cifn = new CombinedAnalysis(bFalse, bNoteval, "&&", false);
	Bool bfn = cifn;
	CombinedAnalysis cifn_n(bfn, bNoteval, "&&", false);

	RB_FAIL(rbAND(rbAND_DE(false, true), true), cifn_n);
}

RB_TEST(AndAnd2_SecondFails)
{
	AnalysisNotEvaluated *analysisNoteval = new AnalysisNotEvaluated;
	Bool bFalse = false, bTrue = true, bNoteval = analysisNoteval;

	CombinedAnalysis *citf = new CombinedAnalysis(bTrue, bFalse, "&&", false);
	Bool btf = citf;
	CombinedAnalysis citf_n(btf, bNoteval, "&&", false);

	RB_FAIL(rbAND(rbAND_BE(true, false), true), citf_n);
	RB_FAIL(rbAND(rbAND_DE(true, false), true), citf_n);
}

RB_TEST(AndAnd2_ThirdFails)
{
	AnalysisNotEvaluated *analysisNoteval = new AnalysisNotEvaluated;
	Bool bFalse = false, bTrue = true, bNoteval = analysisNoteval;

	if (RichBoolTest::GetLevel()<3)
	{
		CombinedAnalysis citt_f(bTrue, bFalse, "&&", false);

		RB_FAIL(rbAND(rbAND_BE(true, true), false), citt_f);
		RB_FAIL(rbAND(rbAND_DE(true, true), false), citt_f);
	}
	else
	{
		CombinedAnalysis *citt = new CombinedAnalysis(bTrue, bTrue, "&&", true);
		Bool btt = citt;
		CombinedAnalysis citt_f(btt, bFalse, "&&", false);

		RB_FAIL(rbAND(rbAND_BE(true, true), false), citt_f);
		RB_FAIL(rbAND(rbAND_DE(true, true), false), citt_f);
	}
}
