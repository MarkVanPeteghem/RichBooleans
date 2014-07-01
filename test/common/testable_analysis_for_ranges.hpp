//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef TESTABLE_INFO_FOR_RANGES_H__QM
#define TESTABLE_INFO_FOR_RANGES_H__QM

#include "richbool/richbool.hpp"

class TestableAnalysisOfRangeBase: public RichBool::AnalysisOfRange
{
	bool m_ownsAnalyses;

public:
	TestableAnalysisOfRangeBase(RichBool::Analysis::State st, const char *message,
		RichBool::SharedExpression expr1,
		RichBool::SharedExpression expr2):

	RichBool::AnalysisOfRange(st, message, expr1, expr2),
	m_ownsAnalyses(true)	
	{}

	TestableAnalysisOfRangeBase(RichBool::Analysis::State st, const char *message,
		RichBool::SharedExpression expr1,
		RichBool::SharedExpression expr2,
		RichBool::SharedExpression expr3,
		RichBool::SharedExpression expr4):

	RichBool::AnalysisOfRange(st, message, expr1, expr2, expr3, expr4),
	m_ownsAnalyses(true)	
	{}

	TestableAnalysisOfRangeBase(RichBool::Analysis::State st, const char *message1,
		RichBool::SharedExpression expr1,
		RichBool::SharedExpression expr2,
		const char *message2,
		RichBool::SharedExpression expr3,
		RichBool::SharedExpression expr4,
		const char *message3):

	RichBool::AnalysisOfRange(st, message1, expr1, expr2, message2, expr3, expr4, message3),
	m_ownsAnalyses(true)	
	{}

	virtual ~TestableAnalysisOfRangeBase()
	{
		if (!m_ownsAnalyses)
			// clear the array, before the destructor of AnalysisOfRange
			// deletes the pointers in it:
			RichBool::detail::clear(m_analysisArray);
	}
	
	TestableAnalysisOfRangeBase* AddAnalyses(RichBool::Analysis **analysis, size_t count, bool own=true)
	{
		for (size_t idx=0; idx<count; ++idx)
		{
			Add(analysis[idx]);
		}
		m_ownsAnalyses = own;

		return this;
	}
};

class TestableAnalysisOfRange: public TestableAnalysisOfRangeBase
{
public:
	TestableAnalysisOfRange(const char *message,
			const char *expr1, const char *expr2):
	TestableAnalysisOfRangeBase(RichBool::Analysis::NotOk, message,
			RichBool::MakeExpression(expr1),
			RichBool::MakeExpression(expr2))
	{
	}

	TestableAnalysisOfRange(const char *message,
			const char *expr1):
		TestableAnalysisOfRangeBase(RichBool::Analysis::NotOk, message,
			RichBool::MakeExpression(expr1),
			NULL)
	{
	}

	TestableAnalysisOfRange(const char *message,
		RichBool::SharedExpression expr1, RichBool::SharedExpression expr2):
		TestableAnalysisOfRangeBase(RichBool::Analysis::NotOk, message,
			expr1, expr2)
	{
	}

		TestableAnalysisOfRange(RichBool::Analysis::State st, const char *message,
			const char *expr1, const char *expr2):
		TestableAnalysisOfRangeBase(st, message,
			RichBool::MakeExpression(expr1),
			RichBool::MakeExpression(expr2))
	{
	}

	TestableAnalysisOfRange(RichBool::Analysis::State st, const char *message,
			const char *expr1):
		TestableAnalysisOfRangeBase(st, message,
			RichBool::MakeExpression(expr1),
			NULL)
	{
	}

	TestableAnalysisOfRange(RichBool::Analysis::State st, const char *message,
		RichBool::SharedExpression expr1, RichBool::SharedExpression expr2):
		TestableAnalysisOfRangeBase(st, message,
			expr1, expr2)
	{
	}
};

class TestableAnalysisOfRanges: public TestableAnalysisOfRangeBase
{
public:
	TestableAnalysisOfRanges(const char *message,
			const char *expr1, const char *expr2,
			const char *expr3, const char *expr4,
			RichBool::Analysis::State st=RichBool::Analysis::NotOk):
		TestableAnalysisOfRangeBase(st, message,
			RichBool::MakeExpression(expr1),
			RichBool::MakeExpression(expr2),
			RichBool::MakeExpression(expr3),
			RichBool::MakeExpression(expr4))
	{
	}

	TestableAnalysisOfRanges(const char *message1,
			const char *expr1, const char *expr2,
			const char *message2,
			const char *expr3, const char *expr4,
			const char *message3,
			RichBool::Analysis::State st=RichBool::Analysis::NotOk):
		TestableAnalysisOfRangeBase(st, message1,
			RichBool::MakeExpression(expr1),
			RichBool::MakeExpression(expr2),
			message2,
			RichBool::MakeExpression(expr3),
			RichBool::MakeExpression(expr4),
			message3)
	{
	}

	TestableAnalysisOfRanges(const char *message,
			RichBool::SharedExpression expr1, RichBool::SharedExpression expr2,
			RichBool::SharedExpression expr3, RichBool::SharedExpression expr4,
			RichBool::Analysis::State st=RichBool::Analysis::NotOk):
		TestableAnalysisOfRangeBase(st, message,
			expr1, expr2,
			expr3, expr4)
	{
	}
};

class TestableAnalysisOfContainers: public TestableAnalysisOfRangeBase
{
public:
	TestableAnalysisOfContainers(const char *message,
			const char *expr1, const char *expr2,
			RichBool::Analysis::State st=RichBool::Analysis::NotOk):
		TestableAnalysisOfRangeBase(st, message,
			RichBool::MakeExpression(expr1),
			NULL,
			RichBool::MakeExpression(expr2),
			NULL)
	{
	}

	TestableAnalysisOfContainers(const char *message1,
			const char *expr1, const char *message2,
			const char *expr2, const char *message3,
			RichBool::Analysis::State st=RichBool::Analysis::NotOk):
		TestableAnalysisOfRangeBase(st, message1,
			RichBool::MakeExpression(expr1),
			NULL,
			message2,
			RichBool::MakeExpression(expr2),
			NULL,
			message3)
	{
	}

	TestableAnalysisOfContainers(const char *message,
			RichBool::SharedExpression expr1, RichBool::SharedExpression expr2,
			RichBool::Analysis::State st=RichBool::Analysis::NotOk):
		TestableAnalysisOfRangeBase(st, message,
			expr1, NULL,
			expr2, NULL)
	{
	}
};

#endif // #ifndef TESTABLE_INFO_FOR_RANGES_H__QM
