//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/richbool.hpp"

using namespace RichBool;

class Stub
{
public:
	Stub(bool c=true): called(false), cond(c) {}
	bool cond;
	mutable bool called;

	bool operator==(int) const { called = true; return cond; }
	bool operator<=(int) const { called = true; return cond; }
	bool operator>=(int) const { called = true; return cond; }
	bool operator<(int) const { called = true; return cond; }
	bool operator>(int) const { called = true; return cond; }
	bool operator!=(int) const { called = true; return cond; }
};

detail::OutStream& operator<<(detail::OutStream& str, const Stub &)
{
	return str;
}

RB_TEST(EqualNotCalled_In_Level0)
{
	Stub stub;
	RB_PASS(rbEQUAL(stub, 0));
	if (RichBoolTest::GetLevel()==0)
		RB_ASSERT(!stub.called);
	else
		RB_ASSERT(stub.called);
}

RB_TEST(EqualNotCalled_In_Level0_WithValue)
{
	Stub stub;
	RB_PASS_IV(rbvEQUAL(stub, 0));
	if (RichBoolTest::GetLevel()==0)
		RB_ASSERT(!stub.called);
	else
		RB_ASSERT(stub.called);
}

RB_TEST(LessNotCalled_In_Level0)
{
	Stub stub;
	RB_PASS(rbLESS(stub, 0));
	if (RichBoolTest::GetLevel()==0)
		RB_ASSERT(!stub.called);
	else
		RB_ASSERT(stub.called);
}

RB_TEST(MoreNotCalled_In_Level0)
{
	Stub stub;
	RB_PASS(rbMORE(stub, 0));
	if (RichBoolTest::GetLevel()==0)
		RB_ASSERT(!stub.called);
	else
		RB_ASSERT(stub.called);
}

RB_TEST(MoreNotCalled_In_Level0_WithValue)
{
	Stub stub;
	RB_PASS_IV(rbvMORE(stub, 0));
	if (RichBoolTest::GetLevel()==0)
		RB_ASSERT(!stub.called);
	else
		RB_ASSERT(stub.called);
}

RB_TEST(LessOrEqNotCalled_In_Level0)
{
	Stub stub;
	RB_PASS(rbLESS_OR_EQUAL(stub, 0));
	if (RichBoolTest::GetLevel()==0)
		RB_ASSERT(!stub.called);
	else
		RB_ASSERT(stub.called);
}

RB_TEST(MoreOrEqNotCalled_In_Level0)
{
	Stub stub;
	RB_PASS(rbMORE_OR_EQUAL(stub, 0));
	if (RichBoolTest::GetLevel()==0)
		RB_ASSERT(!stub.called);
	else
		RB_ASSERT(stub.called);
}

RB_TEST(DiffNotCalled_In_Level0)
{
	Stub stub;
	RB_PASS(rbDIFF(stub, 0));
	if (RichBoolTest::GetLevel()==0)
		RB_ASSERT(!stub.called);
	else
		RB_ASSERT(stub.called);
}

RB_TEST(Or_FirstOK_EqualCalled_In_Level0)
{
	Stub stub1, stub2;
	RB_PASS(rbOR(rbEQUAL(stub1, 0), rbEQUAL(stub2, 0)));
	RB_ASSERT(stub1.called);
	RB_ASSERT(!stub2.called);
}

RB_TEST(Or_FirstNOK_EqualCalled_In_Level0)
{
	Stub stub1(false), stub2;
	RB_PASS(rbOR(rbEQUAL(stub1, 0), rbEQUAL(stub2, 0)));
	RB_ASSERT(stub1.called);
	if (RichBoolTest::GetLevel()==0)
		RB_ASSERT(!stub2.called);
	else
		RB_ASSERT(stub2.called);
}

RB_TEST(And_FirstOK_EqualCalled_In_Level0)
{
	Stub stub1, stub2;
	RB_PASS(rbAND(rbEQUAL(stub1, 0), rbEQUAL(stub2, 0)));
	RB_ASSERT(stub1.called);
	if (RichBoolTest::GetLevel()==0)
		RB_ASSERT(!stub2.called);
	else
		RB_ASSERT(stub2.called);
}

RB_TEST(And_FirstNOK_EqualCalled_In_Level0)
{
	Stub stub1(false), stub2;
	RB_FAIL_I(rbAND(rbEQUAL(stub1, 0), rbEQUAL(stub2, 0)));
	RB_ASSERT(stub1.called);
	RB_ASSERT(!stub2.called);
}
