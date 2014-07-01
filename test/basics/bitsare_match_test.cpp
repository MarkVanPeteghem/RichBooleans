//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/functors.hpp"

using namespace RichBool;

RB_TEST(BitsAre_Match)
{
    char ch = 15;
    const void* p = (const void*)&ch;
    BitsAreCore bitsAreCore;
    RB_ASSERT(rbEQUAL(bitsAreCore.Match(p, 1, "0000 1111"), BitsAreCore::Ok));
    RB_ASSERT(rbEQUAL(bitsAreCore.Match(p, 1, "0:0,0.0 1-111"), BitsAreCore::Ok));
    RB_ASSERT(rbEQUAL(bitsAreCore.Match(p, 1, "0000 1101"), BitsAreCore::Mismatch));
    RB_ASSERT(rbEQUAL(bitsAreCore.Match(p, 1, "0000 111"), BitsAreCore::MaskTooShort));
    RB_ASSERT(rbEQUAL(bitsAreCore.Match(p, 1, "0000 11111"), BitsAreCore::MaskTooLong));
    RB_ASSERT(rbEQUAL(bitsAreCore.Match(p, 1, "0a00 1111"), BitsAreCore::IllegalCharacter));

    RB_ASSERT(rbEQUAL(bitsAreCore.Match(p, 1, "0#00 111#"), BitsAreCore::Ok));
    RB_ASSERT(rbEQUAL(bitsAreCore.Match(p, 1, "0#00 110#"), BitsAreCore::Mismatch));
    RB_ASSERT(rbEQUAL(bitsAreCore.Match(p, 1, "0#00 1#1"), BitsAreCore::MaskTooShort));
    RB_ASSERT(rbEQUAL(bitsAreCore.Match(p, 1, "0#00 1#111"), BitsAreCore::MaskTooLong));
}
