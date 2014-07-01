//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com


#include "rbtest.hpp"
#include "richbool/bool.hpp"
#include "richbool/analysis.hpp"

#ifdef RICHBOOL_USE_WX
	#include <wx/wfstream.h>
	#include <wx/txtstrm.h>
	static wxFFileOutputStream output( stderr );
	wxTextOutputStream out(output);
#else
	#include <iostream>
	std::ostream &out = std::cerr;
#endif

int RichBoolTest::s_level=2;

RichBoolTest::RichBoolTest(const char *n, const char *f, int l):
	m_next(0), m_name(n), m_file(f), m_line(l)
{
	// add to the linked list
	m_next = s_tests;
	s_tests = this;
	++s_nrTests;
}

RichBoolTest *RichBoolTest::s_tests=0;
static RichBoolTest *presentTest=0;
int RichBoolTest::s_nrTests=0;
static int NrUncaughtExceptions=0;

void RichBoolTest::RunTests()
{
	int count=0;
	for (presentTest=s_tests; presentTest; presentTest=presentTest->m_next, ++count)
	{
		// uncomment next line if the tests crash
		// and you need to know in which test it happens
		out << "running test " << presentTest->GetName() << "\n";

		bool catchExceptions = false;

		if (catchExceptions)
		{
			try
			{
				presentTest->run();
			}
			catch (...)
			{
				++NrUncaughtExceptions;
				out << "\n" << presentTest->m_file << '(' << presentTest->m_line << "):";
				out << " error: Uncaught exception in test " << presentTest->m_name << "\n";
			}
		}
		else
		{
			presentTest->run();
		}

		//if (count==300) break;
	}
}

void DisplayContext(const char *szFile, int line)
{
#ifdef _MSC_VER
	out << szFile << '(' << line << "):";
#else
	out << szFile << ':' << line << ':';
#endif
}


/////////////////////////////////////////////////
// functions called by macros, and statistics

static int nrPassOk=0, nrPassNOk=0;

void rbPass(const RichBool::Bool &b,
			const char *szFile,
			int line)
{
	bool ok = true;

	if (!b()) // b() should be true for any value of richbool_level
	{
		ok = false;

		DisplayContext(szFile, line);
		out << " error: richbool didn't pass\n";
		if (b.GetAnalysis())
		{
			out << "analysis: " << *b.GetAnalysis() << "\n";
		}
		else
			out << "no analysis\n";
	}

	switch (RichBoolTest::GetLevel())
	{
	case 0:
	case 1:
	case 2:
		if (b.GetAnalysis())
		{
			ok = false;
			DisplayContext(szFile, line);
			out << " error: richbool has analysis\n";
		}
		break;
	case 3:
		if (!b.GetAnalysis())
		{
			ok = false;
			DisplayContext(szFile, line);
			out << " error: richbool has no analysis\n";
		}
		else if (b.GetAnalysis()->GetState()!=RichBool::Analysis::Ok)
		{
			DisplayContext(szFile, line);
			out << " error: analysis is not ok\n";
		}
		break;
	}

	if (!ok)
		++nrPassNOk;
	else
		++nrPassOk;
}

void rbPassBool(bool b,
				bool ,
				const char *szFile,
				int line)
{
	if (!b)
	{
		DisplayContext(szFile, line);
		out << " error: condition failed\n";
		++nrPassNOk;
	}
	else
		++nrPassOk;
}

static int nrEqualOK=0, nrEqualNOK=0, nrAssertionsFailed=0;

int GetNrPassOK()
{
	return nrPassOk;
}

int GetNrPassNOK()
{
	return nrPassNOk;
}

int GetNrAssertionsFailed()
{
	return nrAssertionsFailed;
}

int GetNrUncaughtExceptions()
{
	return NrUncaughtExceptions;
}

static void DisplayFirstDifference(const RichBool::Analysis &analysis1,
                                   const RichBool::Analysis &analysis2)
{
	if ((analysis1.GetType()=="general") && (analysis2.GetType()=="general"))
	{
		const RichBool::GeneralAnalysis &ga1 = (const RichBool::GeneralAnalysis&)analysis1;
		const RichBool::GeneralAnalysis &ga2 = (const RichBool::GeneralAnalysis&)analysis2;
		const RichBool::GeneralAnalysis::Part *p1 = ga1.GetFirstPart();
		const RichBool::GeneralAnalysis::Part *p2 = ga2.GetFirstPart();
		while (p1 && p2)
		{
			if (!(*p1==*p2))
			{
				out << "\nanalysis 1: -";
				p1->StreamOut(out, 0);
				out << "-\nanalysis 2: -";
				p2->StreamOut(out, 0);
				out << "-\n";
				break;
			}

			p1 = ga1.GetNextPart(p1);
			p2 = ga1.GetNextPart(p2);
		}
		out << "epilogues "
			<< (ga1.GetEpilogue()==ga2.GetEpilogue() ? "equal" : "different")
			<< "\n";
	}
}

void rbFail(const RichBool::Bool &b,
			const RichBool::Analysis &analysis,
			const char *szFile,
			int line)
{
	switch (RichBoolTest::GetLevel())
	{
	case 0:
		if (!b())
		{
			++nrEqualNOK;
			DisplayContext(szFile, line);
			out << " error: richbool evaluated to false\n";
		}
		else if (b.GetAnalysis())
		{
			++nrEqualNOK;
			DisplayContext(szFile, line);
			out << " error: richbool has analysis\n";
		}
		else
			++nrEqualOK;
		break;
	case 1:
		if (b())
		{
			++nrEqualNOK;
			DisplayContext(szFile, line);
			out << " error: richbool evaluated to true\n";
		}
		else if (b.GetAnalysis())
		{
			++nrEqualNOK;
			DisplayContext(szFile, line);
			out << " error: richbool has analysis\n";
		}
		else
			++nrEqualOK;
		break;
	case 2:
	case 3:
		if (!b.GetAnalysis())
		{
			++nrEqualNOK;
			DisplayContext(szFile, line);
			out << " error: richbool has no analysis\n";
		}
		else
		{
			RichBool::Analysis::State state = b.GetAnalysis()->GetState();
			if ( (state!=RichBool::Analysis::NotOk) && (state!=RichBool::Analysis::BadValue) )
			{
				DisplayContext(szFile, line);
				out << " error: state of analysis is not NotOk or BadValue\n";
				++nrEqualNOK;
			}
			if ( (analysis.GetType()!="ignore") && (*b.GetAnalysis() != analysis) )
			{
				++nrEqualNOK;
				DisplayContext(szFile, line);
				out << " error: richbool does not have expected analysis\n";

				out << "analysis of richbool: " << *b.GetAnalysis() << "\n";

				out << "expected analysis   : " << analysis << "\n";
				DisplayFirstDifference(*b.GetAnalysis(), analysis);
			}
			++nrEqualOK;
		}
		break;
	}
}

void rbAssertFailed(const RichBool::Bool &b,
			 const char *szFile,
			 int line)
{
	++nrAssertionsFailed;
	DisplayContext(szFile, line);
	out << " error: assertion failed\n";
	if (b.GetAnalysis())
		out << "analysis: " << *b.GetAnalysis() << '\n';
}

int GetNrEqualOK()
{
	return nrEqualOK;
}

int GetNrEqualNOK()
{
	return nrEqualNOK;
}

void print_warning(const char *szWarning,
			const char *szFile,
			int line)
{
	DisplayContext(szFile, line);
	out << " warning: " << szWarning << '\n';
}

RichBool::detail::String GetNullPtrString()
{
#if defined(RICHBOOL_WIN)
        return "0x00000000";
#else
        return RichBool::PtrToString((void*)0);
#endif
}

void PrintTestLocation()
{
	if (presentTest)
	{
		DisplayContext(presentTest->GetFile(), presentTest->GetLine());
		out << '\n';
	}
}
