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
#include "stub_container.hpp"

using namespace RichBool;

RB_TEST(StubContainer_Empty)
{
	StubContainer stub;
	RB_PASS_B(stub.begin()==stub.end());
}

RB_TEST(StubContainer_OneElements)
{
	StubContainer stub(1);

	StubContainer::Iterator it = stub.begin();
	RB_PASS_B(it!=stub.end());
	RB_PASS_B(stub.end()!=it);
	RB_PASS(rbEQUAL(*it, 1));

	++it;
	RB_PASS_B(it==stub.end());
	RB_PASS_B(stub.end()==it);
}

RB_TEST(StubContainer_ThreeElements)
{
	StubContainer stub(1, 3, 6);

	StubContainer::Iterator it = stub.begin();
	RB_PASS_B(it!=stub.end());
	RB_PASS_B(stub.end()!=it);
	RB_PASS(rbEQUAL(*it, 1));

	++it;
	RB_PASS_B(it!=stub.end());
	RB_PASS_B(stub.end()!=it);
	RB_PASS(rbEQUAL(*it, 3));

	++it;
	RB_PASS_B(it!=stub.end());
	RB_PASS_B(stub.end()!=it);
	RB_PASS(rbEQUAL(*it, 6));

	++it;
	RB_PASS_B(it==stub.end());
	RB_PASS_B(stub.end()==it);
}

RB_TEST(StubContainer_InputIterator_Concept)
{
	StubContainer stub(1, 3, 6);

	StubContainer::Iterator it1 = stub.begin(), it2 = stub.begin();

	RB_PASS_B(it1!=stub.end());
	RB_PASS_B(stub.end()!=it1);
	RB_PASS(rbEQUAL(*it1, 1));
	RB_PASS(rbEQUAL(*it2, 1));

	++it1;
	RB_PASS_B(it1!=stub.end());
	RB_PASS_B(stub.end()!=it1);
	RB_PASS(rbEQUAL(*it1, 3));
	RB_PASS(rbEQUAL(*it2, 3));

	++it1;
	RB_PASS_B(it1!=stub.end());
	RB_PASS_B(stub.end()!=it1);
	RB_PASS(rbEQUAL(*it1, 6));
	RB_PASS(rbEQUAL(*it2, 6));

	++it1;
	RB_PASS_B(it1==stub.end());
	RB_PASS_B(stub.end()==it1);
	RB_PASS_B(it2==stub.end());
}
