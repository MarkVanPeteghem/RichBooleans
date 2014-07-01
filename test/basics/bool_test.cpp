//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "richbool/richbool.hpp"
#include "rbtest.hpp"

using namespace RichBool;

RB_TEST(Bool_Default)
{
	Bool b;
	RB_PASS_B(!b());

	SharedAnalysis an = b.GetAnalysis();
	RB_PASS_B(!an);
}

RB_TEST(Bool_False)
{
	Bool b(false);
	RB_PASS_B(!b());

	SharedAnalysis an = b.GetAnalysis();
	RB_PASS_B(!an);
}

RB_TEST(Bool_True)
{
	Bool b(true);
	RB_PASS_B(b());

	SharedAnalysis an = b.GetAnalysis();
	RB_PASS_B(!an);
}

RB_TEST(Bool_AnalysisNull)
{
	Bool b((Analysis*)NULL);
	RB_PASS_B(b());

	SharedAnalysis an = b.GetAnalysis();
	RB_PASS_B(!an);
}

RB_TEST(Bool_AnalysisNok)
{
	Bool b(new GeneralAnalysis(false));
	RB_PASS_B(!b());

	SharedAnalysis an = b.GetAnalysis();
	RB_PASS_B(!!an);
}

RB_TEST(Bool_AnalysisOk)
{
	Bool b(new GeneralAnalysis(true));
	RB_PASS_B(b());

	SharedAnalysis an = b.GetAnalysis();
	RB_PASS_B(!!an);
}
