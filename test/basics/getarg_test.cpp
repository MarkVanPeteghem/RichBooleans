//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/functors.hpp"
#include "richbool/getarg.hpp"

static const int n1=1,n2=2;


// GetArg

RB_TEST(GetArg_1)
{
	RichBool::detail::GetArg<1> getArg;
	RB_ASSERT(rbEQUAL(getArg(n1),1));
	RB_ASSERT(rbEQUAL(getArg(n1,n2),1));
	RB_ASSERT(rbEQUAL(getArg(n1,n2,n2),1));
	RB_ASSERT(rbEQUAL(getArg(n1,n2,n2,n2),1));
	RB_ASSERT(rbEQUAL(getArg(n1,n2,n2,n2,n2),1));
	RB_ASSERT(rbEQUAL(getArg(n1,n2,n2,n2,n2,n2),1));
}

RB_TEST(GetArg_2)
{
	RichBool::detail::GetArg<2> getArg;
	RB_ASSERT(rbEQUAL(getArg(n2,n1),1));
	RB_ASSERT(rbEQUAL(getArg(n2,n1,n2),1));
	RB_ASSERT(rbEQUAL(getArg(n2,n1,n2,n2),1));
	RB_ASSERT(rbEQUAL(getArg(n2,n1,n2,n2,n2),1));
	RB_ASSERT(rbEQUAL(getArg(n2,n1,n2,n2,n2,n2),1));
}

RB_TEST(GetArg_3)
{
	RichBool::detail::GetArg<3> getArg;
	RB_ASSERT(rbEQUAL(getArg(n2,n2,n1),1));
	RB_ASSERT(rbEQUAL(getArg(n2,n2,n1,n2),1));
	RB_ASSERT(rbEQUAL(getArg(n2,n2,n1,n2,n2),1));
	RB_ASSERT(rbEQUAL(getArg(n2,n2,n1,n2,n2,n2),1));
}

RB_TEST(GetArg_4)
{
	RichBool::detail::GetArg<4> getArg;
	RB_ASSERT(rbEQUAL(getArg(n2,n2,n2,n1),1));
	RB_ASSERT(rbEQUAL(getArg(n2,n2,n2,n1,n2),1));
	RB_ASSERT(rbEQUAL(getArg(n2,n2,n2,n1,n2,n2),1));
}

RB_TEST(GetArg_5)
{
	RichBool::detail::GetArg<5> getArg;
	RB_ASSERT(rbEQUAL(getArg(n2,n2,n2,n2,n1),1));
	RB_ASSERT(rbEQUAL(getArg(n2,n2,n2,n2,n1,n2),1));
}
