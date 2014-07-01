//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com


// richbooltest.cpp : Defines the entry point for the console application.



#ifdef RICHBOOL_USE_WX
	#include <wx/wfstream.h>
	#include <wx/txtstrm.h>
	extern wxTextOutputStream out;
#else

	#include <iostream>
	extern std::ostream &out;

#endif

#include "rbtest.hpp"

int main(int , char* [])
{
	for (int level=0; level<=3; ++level)
	{
		RichBoolTest::SetLevel(level);

		out << "Running tests with level " << RichBoolTest::GetLevel() << '\n';

		RichBoolTest::RunTests();
	}

	out << RichBoolTest::GetNrTests() << " tests\n";
	out << GetNrPassOK() << " passing rich booleans ok, "
		<< GetNrPassNOK() << " not ok\n";
	out << GetNrEqualOK() << " failing rich booleans ok, "
		<< GetNrEqualNOK() << " not ok\n";
	out << GetNrAssertionsFailed() << " assertions failed\n";
	out << GetNrUncaughtExceptions() << " uncaught exceptions\n";

	bool ok = (GetNrPassNOK()==0) && (GetNrEqualNOK()==0)
		&& (GetNrAssertionsFailed()==0);
    return ok ? 0 : 1;
}
