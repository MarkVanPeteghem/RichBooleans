//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#if defined(_MSC_VER)
	#pragma warning(disable: 4786)
#endif

#include "rbtest.hpp"
#include "richbool/richbool.hpp"

RB_TEST(Swap_Pass)
{
	RB_PASS(rb2_RB(2,1, RichBool::Swap<RichBool::Less<> >()));
}

RB_TEST(Swap_Fail)
{
	RichBool::SharedAnalysis an =
		(RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false)
			.expr("2", ":")("2", true)
			(" < ")
			.expr("1", ":")("1", true);
	RB_FAIL(rb2_RB(1,2, RichBool::Swap<RichBool::Less<> >()), *an);
}

RB_TEST(Swap_Pass_Negate)
{
	RB_PASS(rb2_RB(1,2, !RichBool::Swap<RichBool::Less<> >()));
}

RB_TEST(Swap_Fail_Negate)
{
	RichBool::SharedAnalysis an =
		(RichBool::Analysis*)RichBool::MakeGeneralAnalysis(true)
			.expr("1", ":")("1", true)
			(" < ")
			.expr("2", ":")("2", true)
			.neg();
	RB_FAIL(rb2_RB(2,1, !RichBool::Swap<RichBool::Less<> >()), *an);
}

class QuotientIsCore: public RichBool::FunctorCore
{
	int val;
public:
	QuotientIsCore(int n): val(n) {}
	bool operator()(int a, int b) const
	{
		return (a/b)==val;
	}
	const char* GetTextAfter1() const { return "/"; }
	const char* GetTextAfter2() const { return " == "; }
	const RichBool::detail::String GetExtraValue2() const { return RichBool::ToString(val); }
};

RICHBOOL_WRAPPER2ARG_1CARG(QuotientIs, QuotientIsCore, int n, n)

RB_TEST(Swap_Pass_WithState)
{
	RB_PASS(rb2_RB(4,12, RichBool::Swap<QuotientIs<> >(QuotientIs<>(3))));
}

RB_TEST(Swap_Fail_WithState)
{
	RichBool::SharedAnalysis an =
		(RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false)
			.expr("12", ":")("12", true)
			("/")
			.expr("6", ":")("6", true)
			(" == ")
			("3", true);
	RB_FAIL(rb2_RB(6,12, RichBool::Swap<QuotientIs<> >(QuotientIs<>(3))), *an);
}
