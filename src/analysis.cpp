//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif
#include "richbool/analysis.hpp"

namespace RichBool
{
	///////////////////////////////////////////////////////////////
	// class Analysis

	Analysis::~Analysis()
	{
		delete m_text;
	}

	bool Analysis::operator==(const Analysis &analysis) const
	{
		if (GetState()!=analysis.GetState())
			return false;
		if (m_negated!=analysis.m_negated)
			return false;
		if (GetType()!=analysis.GetType())
			return false;
		else
			return Equals(&analysis);
	}

	char Analysis::GetCode() const
	{
		switch (m_state)
		{
		case Ok:
			return 'M';
		case NotOk:
			return 'X';
		case BadValue:
			return 'B';
		case NotEvaluated:
		default:
			return '?';
		}
	}

	void Analysis::StreamOutShort(detail::OutStream &stream) const
	{
		StreamOut(stream, 0);
	}

	const char* Analysis::GetText() const
	{
		if (!m_text)
		{
			detail::String str = ToString(*this);
			m_text = new char[str.size()+1];
			strcpy(m_text, str.c_str());
		}
		return m_text;
	}

	void Analysis::Negate()
	{
		m_negated = !m_negated;
		m_state = Modify(m_state, true);
	}

	Analysis::State Analysis::Modify(State s, bool negate)
	{
		switch (s)
		{
		case Ok:
			return negate ? NotOk : Ok;
		case NotOk:
			return negate ? Ok : NotOk;
		default:
			return s;
		}
	}
}
