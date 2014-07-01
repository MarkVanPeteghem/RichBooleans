//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_GETARG_H__QM
#define RICH_BOOL_GETARG_H__QM

#include "richbool/functors.hpp"

namespace RichBool
{
	namespace detail
	{
		template <int Arg>
		struct GetArg
		{
		};

		template <>
		struct GetArg<1>
		{
			template <typename T>
			T& operator()(T &t) const
			{
				return t;
			}
			template <typename T1, typename T2>
			T1& operator()(T1 &t1, T2 &) const
			{
				return t1;
			}
			template <typename T1, typename T2, typename T3>
			T1& operator()(T1 &t1, T2 &, T3 &) const
			{
				return t1;
			}
			template <typename T1, typename T2, typename T3, typename T4>
			T1& operator()(T1 &t1, T2 &, T3 &, T4 &) const
			{
				return t1;
			}
			template <typename T1, typename T2, typename T3, typename T4, typename T5>
			T1& operator()(T1 &t1, T2 &, T3 &, T4 &, T5 &) const
			{
				return t1;
			}
			template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
			T1& operator()(T1 &t1, T2 &, T3 &, T4 &, T5 &, T6 &) const
			{
				return t1;
			}
		};

		template <>
		struct GetArg<2>
		{
			template <typename T1, typename T2>
			T2& operator()(T1 &, T2 &t2) const
			{
				return t2;
			}
			template <typename T1, typename T2, typename T3>
			T2& operator()(T1 &, T2 &t2, T3 &) const
			{
				return t2;
			}
			template <typename T1, typename T2, typename T3, typename T4>
			T2& operator()(T1 &, T2 &t2, T3 &, T4 &) const
			{
				return t2;
			}
			template <typename T1, typename T2, typename T3, typename T4, typename T5>
			T2& operator()(T1 &, T2 &t2, T3 &, T4 &, T5 &) const
			{
				return t2;
			}
			template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
			T2& operator()(T1 &, T2 &t2, T3 &, T4 &, T5 &, T6 &) const
			{
				return t2;
			}
		};

		template <>
		struct GetArg<3>
		{
			template <typename T1, typename T2, typename T3>
			T3& operator()(T1 &, T2 &, T3 &t3) const
			{
				return t3;
			}
			template <typename T1, typename T2, typename T3, typename T4>
			T3& operator()(T1 &, T2 &, T3 &t3, T4 &) const
			{
				return t3;
			}
			template <typename T1, typename T2, typename T3, typename T4, typename T5>
			T3& operator()(T1 &, T2 &, T3 &t3, T4 &, T5 &) const
			{
				return t3;
			}
			template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
			T3& operator()(T1 &, T2 &, T3 &t3, T4 &, T5 &, T6 &) const
			{
				return t3;
			}
		};

		template <>
		struct GetArg<4>
		{
			template <typename T1, typename T2, typename T3, typename T4>
			T4& operator()(T1 &, T2 &, T3 &, T4 &t4) const
			{
				return t4;
			}
			template <typename T1, typename T2, typename T3, typename T4, typename T5>
			T4& operator()(T1 &, T2 &, T3 &, T4 &t4, T5 &) const
			{
				return t4;
			}
			template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
			T4& operator()(T1 &, T2 &, T3 &, T4 &t4, T5 &, T6 &) const
			{
				return t4;
			}
		};

		template <>
		struct GetArg<5>
		{
			template <typename T1, typename T2, typename T3, typename T4, typename T5>
			T5& operator()(T1 &, T2 &, T3 &, T4 &, T5 &t5) const
			{
				return t5;
			}
			template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
			T5& operator()(T1 &, T2 &, T3 &, T4 &, T5 &t5, T6 &) const
			{
				return t5;
			}
		};

		template <>
		struct GetArg<6>
		{
			template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
			T6& operator()(T1 &, T2 &, T3 &, T4 &, T5 &, T6 &t6) const
			{
				return t6;
			}
		};

		template <class RB, int A1>
		struct Get1Arg: public Functors::Base
		{
			RB rb;

			typedef bool Points;

			Get1Arg(RB a=RB()): rb(a) {}

			GetArg<A1> ga1;

			template <typename T1>
			bool operator()(const T1 &t1) const
			{
				return rb(ga1(t1));
			}
			template <typename T1, typename T2>
			bool operator()(const T1 &t1, const T2 &t2) const
			{
				return rb(ga1(t1, t2));
			}
			template <typename T1, typename T2, typename T3>
			bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
			{
				return rb(ga1(t1, t2, t3));
			}
			template <typename T1, typename T2, typename T3, typename T4>
			bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4) const
			{
				return rb(ga1(t1, t2, t3, t4));
			}
			template <typename T1, typename T2, typename T3, typename T4, typename T5>
			bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5) const
			{
				return rb(ga1(t1, t2, t3, t4, t5));
			}
			template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
			bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5, const T6 &t6) const
			{
				return rb(ga1(t1, t2, t3, t4, t5, t6));
			}

			template <typename T1, typename Expr1>
			Analysis* Analyse(const T1 &t1, Expr1 expr1,
				bool analyseIfSuccess=false, bool negate=false)
			{
				return rb.Analyse(ga1(t1), ga1(expr1), analyseIfSuccess, negate);
			}
			template <typename T1, typename Expr1, typename T2, typename Expr2>
			Analysis* Analyse(const T1 &t1, const T2 &t2, Expr1 expr1, Expr2 expr2,
				bool analyseIfSuccess=false, bool negate=false)
			{
				return rb.Analyse(ga1(t1, t2), ga1(expr1, expr2), analyseIfSuccess, negate);
			}
			template <typename T1, typename Expr1, typename T2, typename Expr2, typename T3, typename Expr3>
			Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3, Expr1 expr1, Expr2 expr2, Expr3 expr3,
				bool analyseIfSuccess=false, bool negate=false)
			{
				return rb.Analyse(ga1(t1, t2, t3), ga1(expr1, expr2, expr3),
					analyseIfSuccess, negate);
			}
			template <typename T1, typename Expr1, typename T2, typename Expr2, typename T3, typename Expr3, typename T4, typename Expr4>
			Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, Expr1 expr1, Expr2 expr2, Expr3 expr3, Expr4 expr4,
				bool analyseIfSuccess=false, bool negate=false)
			{
				return rb.Analyse(ga1(t1, t2, t3, t4), ga1(expr1, expr2, expr3, expr4),
					analyseIfSuccess, negate);
			}
			template <typename T1, typename Expr1, typename T2, typename Expr2, typename T3, typename Expr3, typename T4, typename Expr4, typename T5, typename Expr5>
			Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5, Expr1 expr1, Expr2 expr2, Expr3 expr3, Expr4 expr4, Expr5 expr5,
				bool analyseIfSuccess=false, bool negate=false)
			{
				return rb.Analyse(ga1(t1, t2, t3, t4, t5), ga1(expr1, expr2, expr3, expr4, expr5),
					analyseIfSuccess, negate);
			}
		};

		template <class RB, int A1, int A2>
		struct Get2Args: public Functors::Base
		{
			RB rb;

			typedef bool Points;

			Get2Args(RB a=RB()): rb(a) {}

			GetArg<A1> ga1;
			GetArg<A2> ga2;

			template <typename T1, typename T2>
			bool operator()(const T1 &t1, const T2 &t2) const
			{
				return rb(ga1(t1, t2), ga2(t1, t2));
			}
			template <typename T1, typename T2, typename T3>
			bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
			{
				return rb(ga1(t1, t2, t3), ga2(t1, t2, t3));
			}
			template <typename T1, typename T2, typename T3, typename T4>
			bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4) const
			{
				return rb(ga1(t1, t2, t3, t4), ga2(t1, t2, t3, t4));
			}
			template <typename T1, typename T2, typename T3, typename T4, typename T5>
			bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5) const
			{
				return rb(ga1(t1, t2, t3, t4, t5), ga2(t1, t2, t3, t4, t5));
			}
			template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
			bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5, const T6 &t6) const
			{
				return rb(ga1(t1, t2, t3, t4, t5, t6), ga2(t1, t2, t3, t4, t5, t6));
			}

			template <typename T1, typename Expr1, typename T2, typename Expr2>
			Analysis* Analyse(const T1 &t1, const T2 &t2, Expr1 expr1, Expr2 expr2,
				bool analyseIfSuccess=false, bool negate=false)
			{
				return rb.Analyse(ga1(t1, t2), ga2(t1, t2), ga1(expr1, expr2), ga2(expr1, expr2), analyseIfSuccess, negate);
			}
			template <typename T1, typename Expr1, typename T2, typename Expr2, typename T3, typename Expr3>
			Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3, Expr1 expr1, Expr2 expr2, Expr3 expr3,
				bool analyseIfSuccess=false, bool negate=false)
			{
				return rb.Analyse(ga1(t1, t2, t3), ga2(t1, t2, t3), ga1(expr1, expr2, expr3), ga2(expr1, expr2, expr3),
					analyseIfSuccess, negate);
			}
			template <typename T1, typename Expr1, typename T2, typename Expr2, typename T3, typename Expr3, typename T4, typename Expr4>
			Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, Expr1 expr1, Expr2 expr2, Expr3 expr3, Expr4 expr4,
				bool analyseIfSuccess=false, bool negate=false)
			{
				return rb.Analyse(ga1(t1, t2, t3, t4), ga2(t1, t2, t3, t4), ga1(expr1, expr2, expr3, expr4), ga2(expr1, expr2, expr3, expr4),
					analyseIfSuccess, negate);
			}
			template <typename T1, typename Expr1, typename T2, typename Expr2, typename T3, typename Expr3, typename T4, typename Expr4, typename T5, typename Expr5>
			Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5, Expr1 expr1, Expr2 expr2, Expr3 expr3, Expr4 expr4, Expr5 expr5,
				bool analyseIfSuccess=false, bool negate=false)
			{
				return rb.Analyse(ga1(t1, t2, t3, t4, t5), ga2(t1, t2, t3, t4, t5), ga1(expr1, expr2, expr3, expr4, expr5), ga2(expr1, expr2, expr3, expr4, expr5),
					analyseIfSuccess, negate);
			}
		};

		template <class RB, int A1, int A2, int A3>
		struct Get3Args: public Functors::Base
		{
			RB rb;

			typedef bool Points;

			Get3Args(RB a=RB()): rb(a) {}

			GetArg<A1> ga1;
			GetArg<A2> ga2;
			GetArg<A3> ga3;

			template <typename T1, typename T2, typename T3>
			bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
			{
				return rb(ga1(t1,t2,t3), ga2(t1,t2,t3), ga3(t1,t2,t3));
			}
			template <typename T1, typename T2, typename T3, typename T4>
			bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4) const
			{
				return rb(ga1(t1, t2, t3, t4), ga2(t1, t2, t3, t4), ga3(t1, t2, t3, t4));
			}
			template <typename T1, typename T2, typename T3, typename T4, typename T5>
			bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5) const
			{
				return rb(ga1(t1, t2, t3, t4, t5), ga2(t1, t2, t3, t4, t5), ga3(t1, t2, t3, t4, t5));
			}
			template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
			bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5, const T6 &t6) const
			{
				return rb(ga1(t1, t2, t3, t4, t5, t6), ga2(t1, t2, t3, t4, t5, t6), ga3(t1, t2, t3, t4, t5, t6));
			}

			template <typename T1, typename Expr1, typename T2, typename Expr2, typename T3, typename Expr3>
			Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3, Expr1 expr1, Expr2 expr2, Expr3 expr3,
				bool analyseIfSuccess=false, bool negate=false)
			{
				return rb.Analyse(ga1(t1, t2, t3), ga2(t1, t2, t3), ga3(t1, t2, t3),
					ga1(expr1, expr2, expr3), ga2(expr1, expr2, expr3), ga3(expr1, expr2, expr3),
					analyseIfSuccess, negate);
			}
			template <typename T1, typename Expr1, typename T2, typename Expr2, typename T3, typename Expr3, typename T4, typename Expr4>
			Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, Expr1 expr1, Expr2 expr2, Expr3 expr3, Expr4 expr4,
				bool analyseIfSuccess=false, bool negate=false)
			{
				return rb.Analyse(ga1(t1, t2, t3, t4), ga2(t1, t2, t3, t4), ga3(t1, t2, t3, t4),
					ga1(expr1, expr2, expr3, expr4), ga2(expr1, expr2, expr3, expr4), ga3(expr1, expr2, expr3, expr4),
					analyseIfSuccess, negate);
			}
			template <typename T1, typename Expr1, typename T2, typename Expr2, typename T3, typename Expr3, typename T4, typename Expr4, typename T5, typename Expr5>
			Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5, Expr1 expr1, Expr2 expr2, Expr3 expr3, Expr4 expr4, Expr5 expr5,
				bool analyseIfSuccess=false, bool negate=false)
			{
				return rb.Analyse(ga1(t1, t2, t3, t4, t5), ga2(t1, t2, t3, t4, t5), ga3(t1, t2, t3, t4, t5),
					ga1(expr1, expr2, expr3, expr4, expr5), ga2(expr1, expr2, expr3, expr4, expr5), ga3(expr1, expr2, expr3, expr4, expr5),
					analyseIfSuccess, negate);
			}
		};

		template <class RB, int A1, int A2, int A3, int A4>
		struct Get4Args: public Functors::Base
		{
			RB rb;

			typedef bool Points;

			Get4Args(RB a=RB()): rb(a) {}

			GetArg<A1> ga1;
			GetArg<A2> ga2;
			GetArg<A3> ga3;
			GetArg<A4> ga4;

			template <typename T1, typename T2, typename T3, typename T4>
			bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4) const
			{
				return rb(ga1(t1, t2, t3, t4), ga2(t1, t2, t3, t4),
					ga3(t1, t2, t3, t4), ga4(t1, t2, t3, t4));
			}
			template <typename T1, typename T2, typename T3, typename T4, typename T5>
			bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5) const
			{
				return rb(ga1(t1, t2, t3, t4, t5), ga2(t1, t2, t3, t4, t5),
					ga3(t1, t2, t3, t4, t5), ga4(t1, t2, t3, t4, t5));
			}
			template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
			bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5, const T6 &t6) const
			{
				return rb(ga1(t1, t2, t3, t4, t5, t6), ga2(t1, t2, t3, t4, t5, t6),
					ga3(t1, t2, t3, t4, t5, t6), ga4(t1, t2, t3, t4, t5, t6));
			}

			template <typename T1, typename Expr1, typename T2, typename Expr2, typename T3, typename Expr3, typename T4, typename Expr4>
			Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, Expr1 expr1, Expr2 expr2, Expr3 expr3, Expr4 expr4,
				bool analyseIfSuccess=false, bool negate=false)
			{
				return rb.Analyse(ga1(t1, t2, t3, t4), ga2(t1, t2, t3, t4), ga3(t1, t2, t3, t4), ga4(t1, t2, t3, t4),
					ga1(expr1, expr2, expr3, expr4), ga2(expr1, expr2, expr3, expr4), ga3(expr1, expr2, expr3, expr4), ga4(expr1, expr2, expr3, expr4),
					analyseIfSuccess, negate);
			}
			template <typename T1, typename Expr1, typename T2, typename Expr2, typename T3, typename Expr3, typename T4, typename Expr4, typename T5, typename Expr5>
			Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5, Expr1 expr1, Expr2 expr2, Expr3 expr3, Expr4 expr4, Expr5 expr5,
				bool analyseIfSuccess=false, bool negate=false)
			{
				return rb.Analyse(ga1(t1, t2, t3, t4, t5), ga2(t1, t2, t3, t4, t5), ga3(t1, t2, t3, t4, t5), ga4(t1, t2, t3, t4, t5),
					ga1(expr1, expr2, expr3, expr4, expr5), ga2(expr1, expr2, expr3, expr4, expr5), ga3(expr1, expr2, expr3, expr4, expr5), ga4(expr1, expr2, expr3, expr4, expr5),
					analyseIfSuccess, negate);
			}
		};

		template <class RB, int A1, int A2, int A3, int A4, int A5>
		struct Get5Args: public Functors::Base
		{
			RB rb;

			typedef bool Points;

			Get5Args(RB a=RB()): rb(a) {}

			GetArg<A1> ga1;
			GetArg<A2> ga2;
			GetArg<A3> ga3;
			GetArg<A4> ga4;
			GetArg<A5> ga5;

			template <typename T1, typename T2, typename T3, typename T4, typename T5>
			bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5) const
			{
				return rb(ga1(t1, t2, t3, t4, t5), ga2(t1, t2, t3, t4, t5),
					ga3(t1, t2, t3, t4, t5), ga4(t1, t2, t3, t4, t5), ga5(t1, t2, t3, t4, t5));
			}
			template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
			bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5, const T6 &t6) const
			{
				return rb(ga1(t1, t2, t3, t4, t5, t6), ga2(t1, t2, t3, t4, t5, t6),
					ga3(t1, t2, t3, t4, t5, t6), ga4(t1, t2, t3, t4, t5, t6), ga5(t1, t2, t3, t4, t5, t6));
			}
			template <typename T1, typename Expr1, typename T2, typename Expr2, typename T3, typename Expr3, typename T4, typename Expr4, typename T5, typename Expr5>
			Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5, Expr1 expr1, Expr2 expr2, Expr3 expr3, Expr4 expr4, Expr5 expr5,
				bool analyseIfSuccess=false, bool negate=false)
			{
				return rb.Analyse(ga1(t1, t2, t3, t4, t5), ga2(t1, t2, t3, t4, t5), ga3(t1, t2, t3, t4, t5), ga4(t1, t2, t3, t4, t5),  ga5(t1, t2, t3, t4, t5),
					ga1(expr1, expr2, expr3, expr4, expr5), ga2(expr1, expr2, expr3, expr4, expr5), ga3(expr1, expr2, expr3, expr4, expr5), ga4(expr1, expr2, expr3, expr4, expr5), ga5(expr1, expr2, expr3, expr4, expr5),
					analyseIfSuccess, negate);
			}
		};
	}

	// this doesn't work with VC++6, but there is an alternative syntax below
#if !defined(_MSC_VER) || (_MSC_VER > 1300)

	template <int A1, class Action>
	detail::Get1Arg<Action, A1> Get1Arg(Action action)
	{
		return detail::Get1Arg<Action, A1>(action);
	}

	template <int A1, int A2, class Action>
	detail::Get2Args<Action, A1, A2> Get2Args(Action action)
	{
		return detail::Get2Args<Action, A1, A2>(action);
	}

	template <int A1, int A2, int A3, class Action>
	detail::Get3Args<Action, A1, A2, A3> Get3Args(Action action)
	{
		return detail::Get3Args<Action, A1, A2, A3>(action);
	}

	template <int A1, int A2, int A3, int A4, class Action>
	detail::Get4Args<Action, A1, A2, A3, A4> Get4Args(Action action)
	{
		return detail::Get4Args<Action, A1, A2, A3, A4>(action);
	}

	template <int A1, int A2, int A3, int A4, int A5, class Action>
	detail::Get5Args<Action, A1, A2, A3, A4, A5> Get5Args(Action action)
	{
		return detail::Get5Args<Action, A1, A2, A3, A4, A5>(action);
	}

#endif // #if !defined(_MSC_VER) || (_MSC_VER > 1300)

	template <int A1>
	struct Get1Arg_
	{
		template <class Action>
		detail::Get1Arg<Action, A1> operator()(Action action)
		{
			return detail::Get1Arg<Action, A1>(action);
		}
	};

	template <int A1, int A2>
	struct Get2Args_
	{
		template <class Action>
		detail::Get2Args<Action, A1, A2> operator()(Action action)
		{
			return detail::Get2Args<Action, A1, A2>(action);
		}
	};

	template <int A1, int A2, int A3>
	struct Get3Args_
	{
		template <class Action>
		detail::Get3Args<Action, A1, A2, A3> operator()(Action action)
		{
			return detail::Get3Args<Action, A1, A2, A3>(action);
		}
	};

	template <int A1, int A2, int A3, int A4>
	struct Get4Args_
	{
		template <class Action>
		detail::Get4Args<Action, A1, A2, A3, A4> operator()(Action action)
		{
			return detail::Get4Args<Action, A1, A2, A3, A4>(action);
		}
	};

	template <int A1, int A2, int A3, int A4, int A5>
	struct Get5Args_
	{
		template <class Action>
		detail::Get5Args<Action, A1, A2, A3, A4, A5> operator()(Action action)
		{
			return detail::Get5Args<Action, A1, A2, A3, A4, A5>(action);
		}
	};
}

#endif // #ifndef RICH_BOOL_GETARG_H__QM
