//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#if !defined(RICHBOOL_USE_WX)

#include "rbtest.hpp"
#include "richbool/stdexceptions.hpp"

RB_TEST(StdException)
{
	std::bad_exception exc;

	RichBool::GeneralAnalysis analysis(false);
	analysis.AddText("exception of type ");
	analysis.AddValue("std::exception", false);
	analysis.AddText(" was caught");
	analysis.AddNewLine();
	analysis.AddText("info: ");
	analysis.AddValue(exc.what(), false);

	try
	{
		throw exc;
	}
	catch (std::exception &e)
	{
		RB_FAIL(rbEXCEPTION(e), analysis);
	}
}

RB_TEST(bad_exception)
{
	std::bad_exception exc;

	RichBool::GeneralAnalysis analysis(false);
	analysis.AddText("exception of type ");
	analysis.AddValue("std::bad_exception", false);
	analysis.AddText(" was caught");
	analysis.AddNewLine();
	analysis.AddText("info: ");
	analysis.AddValue(exc.what(), false);

	RB_FAIL(rbEXCEPTION(exc), analysis);
}

RB_TEST(bad_alloc)
{
	std::bad_alloc exc;

	RichBool::GeneralAnalysis analysis(false);
	analysis.AddText("exception of type ");
	analysis.AddValue("std::bad_alloc", false);
	analysis.AddText(" was caught");
	analysis.AddNewLine();
	analysis.AddText("info: ");
	analysis.AddValue(exc.what(), false);

	RB_FAIL(rbEXCEPTION(exc), analysis);
}

#endif // #if !defined(RICHBOOL_USE_WX)
