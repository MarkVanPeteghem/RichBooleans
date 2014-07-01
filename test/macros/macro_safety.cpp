//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (See accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/richbool.hpp"

struct SomeType
{
	SomeType(): n(0) {}
	int n;
	virtual void foo()
	{}
};

RB_CONVERSION_HEADER(SomeType)
{
	str << val.n;
	return str;
}

RB_TEST(ArgumentsEvaluatedOnce_1Argument)
{
	SomeType obj[2];
	int idx=0;
	RB_PASS(rbHAS_TYPE(&obj[idx++], SomeType));
	RB_ASSERT(rbEQUAL(idx, 1));
}

RB_TEST(ArgumentsEvaluatedOnce_1Argument_WithValue)
{
	SomeType obj[2];
	int idx=0;
	RB_PASS_VB(rbvHAS_TYPE(&obj[idx++], SomeType), &obj[0]);
	RB_ASSERT(rbEQUAL(idx, 1));
}

RB_TEST(ArgumentsEvaluatedOnce_2Arguments)
{
	int a=0, b=0;
	RB_PASS(rbEQUAL(a++, b++));
	RB_ASSERT(rbEQUAL(a, 1));
	RB_ASSERT(rbEQUAL(b, 1));
}

RB_TEST(ArgumentsEvaluatedOnce_2Arguments_WithValue)
{
	int a=0, b=0;
	RB_PASS_V(rbvEQUAL(a++, b++), 0);
	RB_ASSERT(rbEQUAL(a, 1));
	RB_ASSERT(rbEQUAL(b, 1));
}

RB_TEST(ArgumentsEvaluatedOnce_3Arguments)
{
	int a=0, b=1, c=2;
	RB_PASS(rbORDER_3(a++, <, b++, <, c++));
	RB_ASSERT(rbEQUAL(a, 1));
	RB_ASSERT(rbEQUAL(b, 2));
	RB_ASSERT(rbEQUAL(c, 3));
}

RB_TEST(ArgumentsEvaluatedOnce_3Arguments_WithValue)
{
	int a=0, b=1, c=2;
	RB_PASS_V(rbvORDER_3(a++, <, b++, <, c++), 1);
	RB_ASSERT(rbEQUAL(a, 1));
	RB_ASSERT(rbEQUAL(b, 2));
	RB_ASSERT(rbEQUAL(c, 3));
}

RB_TEST(ArgumentsEvaluatedOnce_4Arguments)
{
	int a=0, b=1, c=2, d=3;
	RB_PASS(rbORDER_4(a++ , < , b++ , < , c++ , < , d++));
	RB_ASSERT(rbEQUAL(a, 1));
	RB_ASSERT(rbEQUAL(b, 2));
	RB_ASSERT(rbEQUAL(c, 3));
	RB_ASSERT(rbEQUAL(d, 4));
}

RB_TEST(InArray_IncIndex)
{
	int a[][5] = {
		{ 0, 0, 0, 0, 0 },
		{ 3, 4, 5, 6, 7 }
	};

	int idx = 0;
	RB_PASS(rbIN_ARRAY(a[idx++], RichBool::All<>(true).Are(RichBool::Equals<int>(0))));
	RB_ASSERT(rbEQUAL(idx, 1));
}

RB_TEST(InArrays_IncIndex)
{
	int a[][5] = {
		{ 1, 2, 3, 4, 5 },
		{ 3, 4, 5, 6, 7 }
	};

	int b[][5] = {
		{ 1, 2, 3, 4, 5 },
		{ 9, 8, 7, 3, 4 }
	};

	int idx1 = 0, idx2 = 0;
	RB_PASS(rbIN_ARRAYS(a[idx1++], b[idx2++], RichBool::AllEqual<>(true)));
	RB_ASSERT(rbEQUAL(idx1, 1));
	RB_ASSERT(rbEQUAL(idx2, 1));
}

RB_TEST(EqualTypes_ArgsEvaluatedOnce)
{
	SomeType obj[3];
	int idx1=0, idx2=1;
	RB_PASS(rbEQUAL_TYPES(&obj[idx1++], &obj[idx2++]));
	RB_ASSERT(rbEQUAL(idx1, 1));
	RB_ASSERT(rbEQUAL(idx2, 2));
}

RB_TEST(EqualTypes_ArgsEvaluatedOnce_WithValue)
{
	SomeType obj[3];
	int idx1=0, idx2=1;
	RB_PASS_VB(rbvEQUAL_TYPES(&obj[idx1++], &obj[idx2++]), &obj[0]);
	RB_ASSERT(rbEQUAL(idx1, 1));
	RB_ASSERT(rbEQUAL(idx2, 2));
}
