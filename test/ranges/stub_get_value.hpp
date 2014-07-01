//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef STUB_GET_VALUE_H__QM
#define STUB_GET_VALUE_H__QM

#include "richbool/getvalue.hpp"

// This struct allows to check if a GetValue template class is
// not default constructed, because it doesn't have a default constructor.
struct StubGetValue: public RichBool::Value
{
	StubGetValue(int ) {}
};

#endif // #ifndef STUB_GET_VALUE_H__QM
