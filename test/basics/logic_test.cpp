//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/richbool.hpp"

#define OK  RichBool::Analysis::Ok
#define NOK RichBool::Analysis::NotOk
#define NE  RichBool::Analysis::NotEvaluated
#define BV  RichBool::Analysis::BadValue

RichBool::Analysis::State GetAndState(RichBool::Analysis::State st1, RichBool::Analysis::State st2)
{
	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(st1);
	RichBool::Analysis *an2 = RichBool::MakeGeneralAnalysis(st2);
	RichBool::AndAnalysis an(an1, an2);
	return an.GetState();
}

RB_TEST(AndAnalysis)
{
	RB_ASSERT(rbEQUAL(GetAndState(OK,  OK),  OK ));
	RB_ASSERT(rbEQUAL(GetAndState(OK,  NOK), NOK));
	RB_ASSERT(rbEQUAL(GetAndState(NOK, OK),  NOK));
	RB_ASSERT(rbEQUAL(GetAndState(NOK, NOK), NOK));

	RB_ASSERT(rbEQUAL(GetAndState(OK,  NE),  OK));
	RB_ASSERT(rbEQUAL(GetAndState(NOK, NE),  NOK));
	RB_ASSERT(rbEQUAL(GetAndState(BV, NE),   BV));

	RB_ASSERT(rbEQUAL(GetAndState(BV, OK),  BV));
	RB_ASSERT(rbEQUAL(GetAndState(BV, NOK), BV));
	RB_ASSERT(rbEQUAL(GetAndState(BV, NE),  BV));

	RB_ASSERT(rbEQUAL(GetAndState(OK, BV),  BV));
	RB_ASSERT(rbEQUAL(GetAndState(NOK, BV), BV));
	RB_ASSERT(rbEQUAL(GetAndState(NE, BV),  BV));

	RB_ASSERT(rbEQUAL(GetAndState(BV, BV),  BV));
}

RichBool::Analysis::State GetOrState(RichBool::Analysis::State st1, RichBool::Analysis::State st2)
{
	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(st1);
	RichBool::Analysis *an2 = RichBool::MakeGeneralAnalysis(st2);
	RichBool::OrAnalysis an(an1, an2);
	return an.GetState();
}

RB_TEST(OrAnalysis)
{
	RB_ASSERT(rbEQUAL(GetOrState(OK,  OK),  OK ));
	RB_ASSERT(rbEQUAL(GetOrState(OK,  NOK), OK));
	RB_ASSERT(rbEQUAL(GetOrState(NOK, OK),  OK));
	RB_ASSERT(rbEQUAL(GetOrState(NOK, NOK), NOK));

	RB_ASSERT(rbEQUAL(GetOrState(OK,  NE),  OK));
	RB_ASSERT(rbEQUAL(GetOrState(NOK, NE),  NOK));
	RB_ASSERT(rbEQUAL(GetOrState(BV, NE),   BV));

	RB_ASSERT(rbEQUAL(GetOrState(BV, OK),  BV));
	RB_ASSERT(rbEQUAL(GetOrState(BV, NOK), BV));
	RB_ASSERT(rbEQUAL(GetOrState(BV, NE),  BV));

	RB_ASSERT(rbEQUAL(GetOrState(OK,  BV), BV));
	RB_ASSERT(rbEQUAL(GetOrState(NOK, BV), BV));
	RB_ASSERT(rbEQUAL(GetOrState(NE,  BV), BV));

	RB_ASSERT(rbEQUAL(GetOrState(BV, BV),  BV));
}

RichBool::Analysis::State GetXorState(RichBool::Analysis::State st1, RichBool::Analysis::State st2)
{
	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(st1);
	RichBool::Analysis *an2 = RichBool::MakeGeneralAnalysis(st2);
	RichBool::XorAnalysis an(an1, an2);
	return an.GetState();
}

RB_TEST(XorAnalysis)
{
	RB_ASSERT(rbEQUAL(GetXorState(OK,  OK),  NOK ));
	RB_ASSERT(rbEQUAL(GetXorState(OK,  NOK), OK));
	RB_ASSERT(rbEQUAL(GetXorState(NOK, OK),  OK));
	RB_ASSERT(rbEQUAL(GetXorState(NOK, NOK), NOK));

	RB_ASSERT(rbEQUAL(GetXorState(BV, OK),  BV));
	RB_ASSERT(rbEQUAL(GetXorState(BV, NOK), BV));
	RB_ASSERT(rbEQUAL(GetXorState(BV, NE),  BV));

	RB_ASSERT(rbEQUAL(GetXorState(OK,  BV), BV));
	RB_ASSERT(rbEQUAL(GetXorState(NOK, BV), BV));
	RB_ASSERT(rbEQUAL(GetXorState(NE,  BV), BV));

	RB_ASSERT(rbEQUAL(GetXorState(BV, BV),  BV));
}

