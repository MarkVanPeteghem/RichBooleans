//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#if defined(_MSC_VER)
	#pragma warning(disable: 4786)
#endif

#include "richbool/richbool.hpp"

#include "rbtest.hpp"

using namespace RichBool;

template<typename It2, class EndCondition_>
void MakeOne(It2 it, EndCondition_ endCondition)
{
	for (typename EndCondition_::IndexType i=0; endCondition(it, i); ++it, ++i)
		*it = 1;
}


RB_TEST(EmptyIteratorRange)
{
	int a[] = { 0, 0 };
	MakeOne(a, detail::MakeEndCondition(a));
	RB_ASSERT(rbEQUAL(a[0], 0));
	RB_ASSERT(rbEQUAL(a[1], 0));
}

RB_TEST(IteratorRange)
{
	int a[] = { 0, 0 };
	MakeOne(a, detail::MakeEndCondition(a+1));
	RB_ASSERT(rbEQUAL(a[0], 1));
	RB_ASSERT(rbEQUAL(a[1], 0));
}

RB_TEST(EmptyNumberRange)
{
	int a[] = { 0, 0 };
	MakeOne(a, detail::MakeEndCondition(0));
	RB_ASSERT(rbEQUAL(a[0], 0));
	RB_ASSERT(rbEQUAL(a[1], 0));
}

RB_TEST(NumberRange)
{
	int a[] = { 0, 0 };
	MakeOne(a, detail::MakeEndCondition(1));
	RB_ASSERT(rbEQUAL(a[0], 1));
	RB_ASSERT(rbEQUAL(a[1], 0));
}

RB_TEST(NumberRange_size_t)
{
	int a[] = { 0, 0 };
	MakeOne(a, detail::MakeEndCondition((size_t)1));
	RB_ASSERT(rbEQUAL(a[0], 1));
	RB_ASSERT(rbEQUAL(a[1], 0));
}

RB_TEST(NumberRange_short)
{
	int a[] = { 0, 0 };
	MakeOne(a, detail::MakeEndCondition((short)1));
	RB_ASSERT(rbEQUAL(a[0], 1));
	RB_ASSERT(rbEQUAL(a[1], 0));
}

RB_TEST(NumberRange_int)
{
	int a[] = { 0, 0 };
	MakeOne(a, detail::MakeEndCondition((int)1));
	RB_ASSERT(rbEQUAL(a[0], 1));
	RB_ASSERT(rbEQUAL(a[1], 0));
}

RB_TEST(NumberRange_long)
{
	int a[] = { 0, 0 };
	MakeOne(a, detail::MakeEndCondition((long)1));
	RB_ASSERT(rbEQUAL(a[0], 1));
	RB_ASSERT(rbEQUAL(a[1], 0));
}

RB_TEST(NumberRange_unsigned_short)
{
	int a[] = { 0, 0 };
	MakeOne(a, detail::MakeEndCondition((unsigned short)1));
	RB_ASSERT(rbEQUAL(a[0], 1));
	RB_ASSERT(rbEQUAL(a[1], 0));
}

RB_TEST(NumberRange_unsigned_int)
{
	int a[] = { 0, 0 };
	MakeOne(a, detail::MakeEndCondition((unsigned int)1));
	RB_ASSERT(rbEQUAL(a[0], 1));
	RB_ASSERT(rbEQUAL(a[1], 0));
}

RB_TEST(NumberRange_unsigned_long)
{
	int a[] = { 0, 0 };
	MakeOne(a, detail::MakeEndCondition((unsigned long)1));
	RB_ASSERT(rbEQUAL(a[0], 1));
	RB_ASSERT(rbEQUAL(a[1], 0));
}


// tests for method length

RB_TEST(CheckThatNumberRangeGivesNumberAsSize)
{
	int a[] = { 0, 0 };
	detail::EndCondition<size_t> ec(2);
	RB_ASSERT(rbEQUAL(ec.length(a), 2u));
}

RB_TEST(CheckThatNumberRangeGivesNumberAsSize_Empty)
{
	int a[] = { 0, 0 };
	detail::EndCondition<size_t> ec(0);
	RB_ASSERT(rbEQUAL(ec.length(a), 0u));
}

RB_TEST(CheckThatIteratorRangeGivesNumberAsSize)
{
	int a[] = { 0, 0 };
	detail::EndCondition<int*> ec(a+2);
	RB_ASSERT(rbEQUAL(ec.length(a), 2u));
}

RB_TEST(CheckThatIteratorRangeGivesNumberAsSize_Empty)
{
	int a[] = { 0, 0 };
	detail::EndCondition<int*> ec(a);
	RB_ASSERT(rbEQUAL(ec.length(a), 0u));
}
