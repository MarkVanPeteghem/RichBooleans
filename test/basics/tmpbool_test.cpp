//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "richbool/richbool.hpp"
#include "rbtest.hpp"

using namespace RichBool;

RB_TEST(Default)
{
	TmpBool tmpBool;
	RB_PASS_B(!tmpBool());

	SharedAnalysis an = tmpBool.GetAnalysis();
	RB_PASS_B(!an);
}

RB_TEST(False)
{
	TmpBool tmpBool(false);
	RB_PASS_B(!tmpBool());

	SharedAnalysis an = tmpBool.GetAnalysis();
	RB_PASS_B(!an);
}

RB_TEST(True)
{
	TmpBool tmpBool(true);
	RB_PASS_B(tmpBool());

	SharedAnalysis an = tmpBool.GetAnalysis();
	RB_PASS_B(!an);
}

RB_TEST(AnalysisNull)
{
	TmpBool tmpBool((Analysis*)NULL);
	RB_PASS_B(tmpBool());

	SharedAnalysis an = tmpBool.GetAnalysis();
	RB_PASS_B(!an);
}

RB_TEST(AnalysisNok)
{
	TmpBool tmpBool(new GeneralAnalysis(false));
	RB_PASS_B(!tmpBool());

	SharedAnalysis an = tmpBool.GetAnalysis();
	RB_PASS_B(!!an);
}

RB_TEST(AnalysisOk)
{
	TmpBool tmpBool(new GeneralAnalysis(true));
	RB_PASS_B(tmpBool());

	SharedAnalysis an = tmpBool.GetAnalysis();
	RB_PASS_B(!!an);
}
