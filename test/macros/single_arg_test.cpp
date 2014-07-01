//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/richbool.hpp"

using namespace RichBool;

RB_TEST(Equals)
{
	RB_PASS(rb1_RB(1, EqualTo(1)));

	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("2", ":")("2", true)(" == ")
			("1", true);
	RB_FAIL(rb1_RB(2, EqualTo(1)), *an);
}

RB_TEST(IsLessThan)
{
	RB_PASS(rb1_RB(1, LessThan(2)));

	SharedAnalysis an1 =
		(Analysis*)MakeGeneralAnalysis(false).expr("2", ":")("2", true)(" < ")
			("1", true);
	RB_FAIL(rb1_RB(2, LessThan(1)), *an1);

	SharedAnalysis an2 =
		(Analysis*)MakeGeneralAnalysis(false).expr("2", ":")("2", true)(" < ")
			("2", true);
	RB_FAIL(rb1_RB(2, LessThan(2)), *an2);
}

RB_TEST(IsLessThanOrEqualTo)
{
	RB_PASS(rb1_RB(1, LessOrEqualTo(2)));
	RB_PASS(rb1_RB(2, LessOrEqualTo(2)));

	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("2", ":")("2", true)(" <= ")
			("1", true);
	RB_FAIL(rb1_RB(2, LessOrEqualTo(1)), *an);
}

RB_TEST(IsMoreThan)
{
	RB_PASS(rb1_RB(3, MoreThan(2)));

	SharedAnalysis an1 =
		(Analysis*)MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" > ")
			("2", true);
	RB_FAIL(rb1_RB(1, MoreThan(2)), *an1);

	SharedAnalysis an2 =
		(Analysis*)MakeGeneralAnalysis(false).expr("2", ":")("2", true)(" > ")
			("2", true);
	RB_FAIL(rb1_RB(2, MoreThan(2)), *an2);
}

RB_TEST(IsMoreThanOrEqualTo)
{
	RB_PASS(rb1_RB(2, MoreOrEqualTo(1)));
	RB_PASS(rb1_RB(2, MoreOrEqualTo(2)));

	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" >= ")
			("2", true);
	RB_FAIL(rb1_RB(1, MoreOrEqualTo(2)), *an);
}

RB_TEST(IsDifferent)
{
	RB_PASS(rb1_RB(2, DifferentFrom(1)));

	SharedAnalysis an =
		(Analysis*)MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" != ")
			("1", true);
	RB_FAIL(rb1_RB(1, DifferentFrom(1)), *an);
}
