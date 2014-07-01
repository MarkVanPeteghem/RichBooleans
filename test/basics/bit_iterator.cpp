//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/bit_iterator.hpp"

using namespace RichBool;


////////////////////////////////////////////////////////
// class BitIterator

RB_TEST(BitIterator_OneByte)
{
    unsigned char c = (1<<7) + (1<<4) + (1<<0);

    BitIterator it(&c, 1);

	int expected[] = {
		1, 0, 0, 1, 0, 0, 0, 1
	};
	for (int i=0; i<8; ++i)
	{
		bool bitOn = expected[i]==1;
		RB_PASS(rbEQUAL(*it, bitOn));
		++it;
	}
}

RB_TEST(BitIterator_TwoBytes)
{
    unsigned short s = (1<<15) + (1<<12) + (1<<4) + (1<<0);

    BitIterator it(&s, 2);

	int expected[] = {
		1, 0, 0, 1, 0, 0, 0, 0,
		0, 0, 0, 1, 0, 0, 0, 1
	};
	for (int i=0; i<16; ++i)
	{
		bool bitOn = expected[i]==1;
		RB_PASS(rbEQUAL(*it, bitOn));
		++it;
	}
}
