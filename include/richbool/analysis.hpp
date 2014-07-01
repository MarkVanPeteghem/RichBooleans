//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_ANALYSIS_H__QM
#define RICH_BOOL_ANALYSIS_H__QM

#include "richbool/portability.hpp"
#include "richbool/shared_ptr.hpp"

namespace RichBool {

	// This is the abstract base class for objects in which
	// RichBool macros store information
	class RICHBOOL_DLL_API Analysis
	{
	public:
		enum State { Ok, NotOk, NotEvaluated, BadValue };
		static State Modify(State s, bool negate);

		explicit Analysis(bool isOk)
			: m_state(isOk ? Ok : NotOk)
			, m_negated(false)
			, m_text(0)
		{}
		explicit Analysis(State state)
			: m_state(state)
			, m_negated(false)
			, m_text(0)
		{}
		virtual ~Analysis();

		bool operator==(const Analysis &analysis) const;
		bool operator!=(const Analysis &analysis) const
		{
			return !(*this==analysis);
		}

		virtual void StreamOut(detail::OutStream &stream, int indent=0) const=0;
		virtual void StreamOutShort(detail::OutStream &stream) const;
		virtual const detail::String& GetType() const=0;
		virtual const char* GetText() const; // less efficient if used only once, may be necessary when using DLLs

		void SetState(State state) { m_state = state; }
		State GetState() const { return m_state; }
		virtual char GetCode() const;
		void Negate();
		bool IsNegated() const { return m_negated; }

	protected:
		State m_state;
		bool m_negated;
		mutable char *m_text;
		virtual bool Equals(const Analysis* analysis) const=0;
	};

	typedef ConstSharedPointer<Analysis> SharedAnalysis;

	inline detail::OutStream& operator<<(detail::OutStream& str,
								  const Analysis &analysis)
	{
		analysis.StreamOut(str);
		return str;
	}
}

#endif // #ifndef RICH_BOOL_ANALYSIS_H__QM
