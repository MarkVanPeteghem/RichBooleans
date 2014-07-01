//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_PAIR_H__QM
#define RICH_BOOL_PAIR_H__QM

#include "getvalue.hpp"

namespace RichBool
{
	struct EqualPairCore: public CustomFunctorCore<false>
	{
		typedef int Points;

		template <class T>
		bool operator()(const T &t1, const T &t2) const
		{
			return (t1.first==t2.first) && (t1.second==t2.second);
		}

		template <class T>
		Points GetPoints(const T &t1, const T &t2) const
		{
			const bool b1 = t1.first==t2.first, b2 = t1.second==t2.second;
			if (b1 && b2)
				return 4;
			else if (b1 || b2)
				return 2;
			else
				return 0;
		}

		Points GetGood() const
		{
			return 4;
		}

		template <class T>
		Analysis* Analyse(const T &t1, const detail::String &, SharedExpression expr1,
			const T &t2, const detail::String &, SharedExpression expr2,
			bool ok) const
		{
			Equal<> equal;
			return MakeGeneralAnalysis(ok)
				("keys: {")
				(equal.Analyse(t1.first, t2.first,
					expr1, expr2, true))
				("}, ")
				("values: {")
				(equal.Analyse(t1.second, t2.second,
					expr1, expr2, true))
				("}");
		}
	};

	struct EqualPair: public Wrapper2Arg<EqualPairCore, Value, Value,
		CustomMakeString<StreamPair<> >, CustomMakeString<StreamPair<> > >
	{
		EqualPair():
			Wrapper2Arg<EqualPairCore, Value, Value, CustomMakeString<StreamPair<> >, CustomMakeString<StreamPair<> > >
				(Value(), Value())
		{}
	};
}

#endif // #ifndef RICH_BOOL_PAIR_H__QM
