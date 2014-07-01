//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/relation.hpp"

using namespace RichBool;


// test operator()(T1 t1, T2 t2) without roundoff

RB_TEST(EqualRelation_True)
{
	RB_PASS_B(EqualRelation()(1,1));
}

RB_TEST(EqualRelation_False)
{
	RB_PASS_B(!EqualRelation()(1,2));
}

RB_TEST(LessRelation_True)
{
	RB_PASS_B(LessRelation()(1,2));
}

RB_TEST(LessRelation_False)
{
	RB_PASS_B(!LessRelation()(1,1));
	RB_PASS_B(!LessRelation()(2,1));
}

RB_TEST(LessOrEqualRelation_True)
{
	RB_PASS_B(LessOrEqualRelation()(1,2));
	RB_PASS_B(LessOrEqualRelation()(1,1));
}

RB_TEST(LessOrEqualRelation_False)
{
	RB_PASS_B(!LessOrEqualRelation()(2,1));
}

RB_TEST(MoreRelation_True)
{
	RB_PASS_B(MoreRelation()(2,1));
}

RB_TEST(MoreRelation_False)
{
	RB_PASS_B(!MoreRelation()(1,1));
	RB_PASS_B(!MoreRelation()(1,2));
}

RB_TEST(MoreOrEqualRelation_True)
{
	RB_PASS_B(MoreOrEqualRelation()(2,1));
	RB_PASS_B(MoreOrEqualRelation()(1,1));
}

RB_TEST(MoreOrEqualRelation_False)
{
	RB_PASS_B(!MoreOrEqualRelation()(1,2));
}

RB_TEST(DifferentRelation_True)
{
	RB_PASS_B(DifferentRelation()(1,2));
}

RB_TEST(DifferentRelation_False)
{
	RB_PASS_B(!DifferentRelation()(1,1));
}


// test operator()(T1 t1, T2 t2, T3 error) with roundoff

RB_TEST(EqualNearRelation_True)
{
	RB_PASS_B(EqualNearRelation()(1.0,1.09, 0.1));
	RB_PASS_B(EqualNearRelation()(1.09,1.0, 0.1));
}

RB_TEST(EqualNearRelation_False)
{
	RB_PASS_B(!EqualNearRelation()(1.0,1.11, 0.1));
	RB_PASS_B(!EqualNearRelation()(1.11,1.0, 0.1));
}

RB_TEST(LessNearRelation_True)
{
	RB_PASS_B(LessNearRelation()(1.09,1.11, 0.1));
	RB_PASS_B(LessNearRelation()(1.05,1.0, 0.1));
}

RB_TEST(LessNearRelation_False)
{
	RB_PASS_B(!LessNearRelation()(1.11,1.0, 0.1));
}

RB_TEST(LessOrEqualNearRelation_True)
{
	RB_PASS_B(LessOrEqualNearRelation()(1.09,1.11, 0.1));
	RB_PASS_B(LessOrEqualNearRelation()(1.09,1.09, 0.1));
	RB_PASS_B(LessOrEqualNearRelation()(1.05,1.0, 0.1));
}

RB_TEST(LessOrEqualNearRelation_False)
{
	RB_PASS_B(!LessOrEqualNearRelation()(1.11,1.0, 0.1));
}

RB_TEST(MoreNearRelation_True)
{
	RB_PASS_B(MoreNearRelation()(1.11,1.09, 0.1));
	RB_PASS_B(MoreNearRelation()(1.0,1.05, 0.1));
}

RB_TEST(MoreNearRelation_False)
{
	RB_PASS_B(!MoreNearRelation()(1.0,1.11, 0.1));
}

RB_TEST(MoreOrEqualNearRelation_True)
{
	RB_PASS_B(MoreOrEqualNearRelation()(1.11,1.09, 0.1));
	RB_PASS_B(MoreOrEqualNearRelation()(1.09,1.09, 0.1));
	RB_PASS_B(MoreOrEqualNearRelation()(1.0,1.05, 0.1));
}

RB_TEST(MoreOrEqualNearRelation_False)
{
	RB_PASS_B(!MoreOrEqualNearRelation()(1.0,1.11, 0.1));
}

RB_TEST(DifferentNearRelation_True)
{
	RB_PASS_B(DifferentNearRelation()(1.0,1.11, 0.1));
}

RB_TEST(DifferentNearRelation_False)
{
	RB_PASS_B(!DifferentNearRelation()(1.09,1.09, 0.1));
	RB_PASS_B(!DifferentNearRelation()(1.0,1.05, 0.1));
	RB_PASS_B(!DifferentNearRelation()(1.05,1.0, 0.1));
}

		template<typename T>
		static T max_(T t1, T t2)
		{
			return t1>t2 ? t1 : t2;
		}


// test operator()(T1 t1, T2 t2, T3 error) with relative roundoff

RB_TEST(EqualRelativeNearRelation_True)
{
	RB_PASS_B(EqualRelativeNearRelation()(0.1,0.109, 0.1));
	RB_PASS_B(EqualRelativeNearRelation()(0.109,0.1, 0.1));

	RB_PASS_B(EqualRelativeNearRelation()(10.0,10.9, 0.1));
	RB_PASS_B(EqualRelativeNearRelation()(10.9,10.0, 0.1));
}

RB_TEST(EqualRelativeNearRelation_False)
{
	RB_PASS_B(EqualRelativeNearRelation()(0.1,0.111, 0.1));
	RB_PASS_B(EqualRelativeNearRelation()(0.111,0.1, 0.1));

	RB_PASS_B(EqualRelativeNearRelation()(10.0,11.1, 0.1));
	RB_PASS_B(EqualRelativeNearRelation()(11.1,10.0, 0.1));
}

RB_TEST(LessRelativeNearRelation_True)
{
	RB_PASS_B(LessRelativeNearRelation()(0.05,0.109, 0.1));
	RB_PASS_B(LessRelativeNearRelation()(0.109,0.1, 0.1));

	RB_PASS_B(LessRelativeNearRelation()(5.0,10.9, 0.1));
	RB_PASS_B(LessRelativeNearRelation()(10.9,10.0, 0.1));
}

RB_TEST(LessRelativeNearRelation_False)
{
	RB_PASS_B(!LessRelativeNearRelation()(0.112,0.1, 0.1));
	RB_PASS_B(!LessRelativeNearRelation()(11.2,10.0, 0.1));
}

RB_TEST(LessOrEqualRelativeNearRelation_True)
{
	RB_PASS_B(LessOrEqualRelativeNearRelation()(0.05,0.109, 0.1));
	RB_PASS_B(LessOrEqualRelativeNearRelation()(0.109,0.1, 0.1));

	RB_PASS_B(LessOrEqualRelativeNearRelation()(5.0,10.9, 0.1));
	RB_PASS_B(LessOrEqualRelativeNearRelation()(10.9,10.0, 0.1));
}

RB_TEST(LessOrEqualRelativeNearRelation_False)
{
	RB_PASS_B(!LessOrEqualRelativeNearRelation()(0.112,0.1, 0.1));
	RB_PASS_B(!LessOrEqualRelativeNearRelation()(11.2,10.0, 0.1));
}

RB_TEST(MoreRelativeNearRelation_True)
{
	RB_PASS_B(MoreRelativeNearRelation()(0.109, 0.05, 0.1));
	RB_PASS_B(MoreRelativeNearRelation()(0.1, 0.109, 0.1));

	RB_PASS_B(MoreRelativeNearRelation()(10.9, 5.0, 0.1));
	RB_PASS_B(MoreRelativeNearRelation()(10.0, 10.9, 0.1));
}

RB_TEST(MoreRelativeNearRelation_False)
{
	RB_PASS_B(!MoreRelativeNearRelation()(0.1,0.112, 0.1));
	RB_PASS_B(!MoreRelativeNearRelation()(10.0,11.2, 0.1));
}

RB_TEST(MoreOrEqualRelativeNearRelation_True)
{
	RB_PASS_B(MoreOrEqualRelativeNearRelation()(0.109,0.05, 0.1));
	RB_PASS_B(MoreOrEqualRelativeNearRelation()(0.1,0.109, 0.1));

	RB_PASS_B(MoreOrEqualRelativeNearRelation()(10.9,5.0, 0.1));
	RB_PASS_B(MoreOrEqualRelativeNearRelation()(10.0,10.9, 0.1));
}

RB_TEST(MoreOrEqualRelativeNearRelation_False)
{
	RB_PASS_B(!MoreOrEqualRelativeNearRelation()(0.1,0.112, 0.1));
	RB_PASS_B(!MoreOrEqualRelativeNearRelation()(10.0,11.2, 0.1));
}

RB_TEST(DifferentRelativeNearRelation_True)
{
	RB_PASS_B(DifferentRelativeNearRelation()(0.1,0.112, 0.1));
	RB_PASS_B(DifferentRelativeNearRelation()(10.0,11.2, 0.1));
	RB_PASS_B(DifferentRelativeNearRelation()(0.112,0.1, 0.1));
	RB_PASS_B(DifferentRelativeNearRelation()(11.2,10.0, 0.1));
}

RB_TEST(DifferentRelativeNearRelation_False)
{
	RB_PASS_B(!DifferentRelativeNearRelation()(0.1,0.109, 0.1));
	RB_PASS_B(!DifferentRelativeNearRelation()(10.0,10.9, 0.1));
	RB_PASS_B(!DifferentRelativeNearRelation()(0.109,0.1, 0.1));
	RB_PASS_B(!DifferentRelativeNearRelation()(10.9,10.0, 0.1));
}

