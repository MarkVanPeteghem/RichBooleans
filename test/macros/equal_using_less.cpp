//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/richbool.hpp"
#include "richbool/functors.hpp"

#include "int_less.hpp"

RB_TEST(OperatorLessOnIntHolder_WithLess)
{
	IntHolder_WithLess a1(1), a2(2);
	RB_ASSERT(a1<a2);
	RB_ASSERT(!(a2<a1));
	RB_ASSERT(!(a1<a1));
}

RB_TEST(OperatorMoreOnIntHolder_WithMore)
{
	IntHolder_WithMore a1(1), a2(2);
	RB_ASSERT(a2>a1);
	RB_ASSERT(!(a1>a2));
	RB_ASSERT(!(a1>a1));
}

RB_TEST(EqualUsingLess_Pass)
{
	RB_PASS(rbEQUAL_USING_LESS(IntHolder_WithLess(1), IntHolder_WithLess(1)));
}

RB_TEST(EqualUsingLess_Fail_Less)
{
	RichBool::SharedAnalysis an = (RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false).expr("IntHolder_WithLess(1)", ":")("1", true)
		(" == ").expr("IntHolder_WithLess(2)", ":")("2", true);

	RB_FAIL(rbEQUAL_USING_LESS(IntHolder_WithLess(1), IntHolder_WithLess(2)), *an);
}

RB_TEST(EqualUsingLess_Fail_More)
{
	RichBool::SharedAnalysis an = (RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false).expr("IntHolder_WithLess(2)", ":")("2", true)
		(" == ").expr("IntHolder_WithLess(1)", ":")("1", true);

	RB_FAIL(rbEQUAL_USING_LESS(IntHolder_WithLess(2), IntHolder_WithLess(1)), *an);
}


RB_TEST(EqualUsingMore_Pass)
{
	RB_PASS(rbEQUAL_USING_MORE(IntHolder_WithMore(1), IntHolder_WithMore(1)));
}

RB_TEST(EqualUsingMore_Fail_Less)
{
	RichBool::SharedAnalysis an = (RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false).expr("IntHolder_WithMore(1)", ":")("1", true)
		(" == ").expr("IntHolder_WithMore(2)", ":")("2", true);

	RB_FAIL(rbEQUAL_USING_MORE(IntHolder_WithMore(1), IntHolder_WithMore(2)), *an);
}

RB_TEST(EqualUsingMore_Fail_More)
{
	RichBool::SharedAnalysis an = (RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false).expr("IntHolder_WithMore(2)", ":")("2", true)
		(" == ").expr("IntHolder_WithMore(1)", ":")("1", true);

	RB_FAIL(rbEQUAL_USING_MORE(IntHolder_WithMore(2), IntHolder_WithMore(1)), *an);
}
