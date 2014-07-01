//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_LOGIC_H__QM
#define RICH_BOOL_LOGIC_H__QM

namespace RichBool
{
	////////////////////////////////////////////////////////////////////////
	// functionality to combine Rich Boolean functors in logical expressions

	namespace detail
	{
		template <bool>
		struct Select
		{};

		template <>
		struct Select<false>
		{
			template <typename Points1, typename Points2>
			struct Get
			{
				typedef Points2 Type;
			};
		};

		template <>
		struct Select<true>
		{
			template <typename Points1, typename Points2>
			struct Get
			{
				typedef Points1 Type;
			};
		};

		template <typename Points1, typename Points2>
		struct UsePoints
		{
			typedef typename Select<(sizeof(Points1)>sizeof(Points2))>::template Get<Points1, Points2>::Type Type;
		};

#define RICHBOOL_MAX(a,b) ( ((a)>(b)) ? (a) : (b) )

		template <class RB1, class RB2>
		struct LogicFunctor: public Functors::Base
		{
			RB1 rb1;
			RB2 rb2;

			LogicFunctor(RB1 rb1_, RB2 rb2_): rb1(rb1_), rb2(rb2_) {}

			typedef typename RB1::Points Points1;
			typedef typename RB2::Points Points2;

			typedef typename ToNumPoints<Points1>::Type NumPoints1;
			typedef typename ToNumPoints<Points2>::Type NumPoints2;

			typedef typename UsePoints<Points1, Points2>::Type Points;

#define RICHBOOL_BIND(N) \
			template <typename T> \
			detail::String GetString##N(const T &t) const \
			{ return rb1.GetString##N(t); } \
			template <typename T> \
			bool IsValid##N(const T &t) const \
			{ return rb1.IsValid##N(t); }

			RICHBOOL_BIND(1)
			RICHBOOL_BIND(2)
			RICHBOOL_BIND(3)
			RICHBOOL_BIND(4)
			RICHBOOL_BIND(5)

#undef RICHBOOL_BIND
		};

		template <class RB1, class RB2>
		struct AndBase: public LogicFunctor<RB1, RB2>
		{
			AndBase(RB1 rb1_, RB2 rb2_): LogicFunctor<RB1, RB2>(rb1_, rb2_) {}

			typedef typename LogicFunctor<RB1, RB2>::Points1 Points1;
			typedef typename LogicFunctor<RB1, RB2>::Points2 Points2;
			typedef typename LogicFunctor<RB1, RB2>::NumPoints1 NumPoints1;
			typedef typename LogicFunctor<RB1, RB2>::NumPoints2 NumPoints2;
			typedef typename ToNumPoints<typename LogicFunctor<RB1, RB2>::Points>::Type NumPoints;
			typedef NumPoints Points;

			NumPoints CalculatePoints(NumPoints1 p1, NumPoints1 , NumPoints2 p2, NumPoints2 ) const
			{
				return p1*p2;
			}

			NumPoints GetGood() const
			{
				return NumPoints(
					GetNumPoints<Points1>::GetGood(this->rb1)*GetNumPoints<Points2>::GetGood(this->rb2)
				);
			}
		};

		template <class RB1, class RB2>
		struct OrBase: public LogicFunctor<RB1, RB2>
		{
			OrBase(RB1 rb1_, RB2 rb2_): LogicFunctor<RB1, RB2>(rb1_, rb2_) {}

			typedef typename LogicFunctor<RB1, RB2>::Points1 Points1;
			typedef typename LogicFunctor<RB1, RB2>::Points2 Points2;
			typedef typename LogicFunctor<RB1, RB2>::NumPoints1 NumPoints1;
			typedef typename LogicFunctor<RB1, RB2>::NumPoints2 NumPoints2;
			typedef typename LogicFunctor<RB1, RB2>::Points Points;

			Points CalculatePoints(NumPoints1 p1, NumPoints1 g1, NumPoints2 p2, NumPoints2 g2) const
			{
				return detail::GetPoints<Points>::ToPoints((RICHBOOL_MAX(g1,g2)*
					RICHBOOL_MAX(p1*g2, p2*g1))
					/ (g1*g2) );
			}

			Points GetGood() const
			{
				return GetPoints<Points>::ToPoints(RICHBOOL_MAX(
					GetNumPoints<Points1>::GetGood(this->rb1),
					GetNumPoints<Points2>::GetGood(this->rb2)
				));
			}
		};
	}

#define RICHBOOL_METHODS \
	template <typename T1> \
	bool operator()(const T1 &t1) const \
	RICHBOOL_OPERATOR((t1)) \
 \
	template <typename T1, typename Expr1> \
	Analysis* Analyse(const T1 &t1, Expr1 expr1, \
		bool analyseOnSucceed=false, bool negate=false) const \
	RICHBOOL_ANALYSE((t1), (t1, expr1, analyseOnSucceed, false), (t1, expr1, true, false), (t1, expr1, false, true)) \
 \
	template <typename T1> \
	Analysis::State SafeCheck(const T1 &t1) const \
	{ \
		if (!this->rb1.IsValid1(t1)) return Analysis::BadValue; \
		return operator()(t1) ? Analysis::Ok : Analysis::NotOk; \
	} \
 \
	template <typename T1, typename T2> \
	bool operator()(const T1 &t1, const T2 &t2) const \
	RICHBOOL_OPERATOR((t1, t2)) \
 \
	template <typename T1, typename Expr1, \
		typename T2, typename Expr2> \
	Analysis* Analyse(const T1 &t1, const T2 &t2, \
		Expr1 expr1, Expr2 expr2, \
		bool analyseOnSucceed=false, bool negate=false) const \
	RICHBOOL_ANALYSE((t1, t2), (t1, t2, expr1, expr2, analyseOnSucceed, false), \
		(t1, t2, expr1, expr2, true, false), (t1, t2, expr1, expr2, false, true)) \
 \
	template <typename T1, typename T2> \
	Analysis::State SafeCheck(const T1 &t1, const T2 &t2) const \
	{ \
		if (!this->rb1.IsValid1(t1)||!this->rb1.IsValid2(t2)) return Analysis::BadValue; \
		return operator()(t1,t2) ? Analysis::Ok : Analysis::NotOk; \
	} \
 \
	template <typename T1, typename Expr1, \
		typename T2, typename Expr2> \
	Analysis* GetDummyAnalysis(const T1 &t1, const T2 &t2, \
		Expr1 expr1, Expr2 expr2) const \
	RICHBOOL_DUMMY_ANALYSIS((t1, t2, expr1, expr2)) \
 \
	template <typename T1, typename T2, typename T3> \
	bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const \
	RICHBOOL_OPERATOR((t1, t2, t3)) \
 \
	template <typename T1, typename Expr1, \
		typename T2, typename Expr2, typename T3, typename Expr3> \
	Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3, \
		Expr1 expr1, Expr2 expr2, Expr3 expr3, \
		bool analyseOnSucceed=false, bool negate=false) const \
	RICHBOOL_ANALYSE((t1, t2, t3), (t1, t2, t3, expr1, expr2, expr3, analyseOnSucceed, false), \
		(t1, t2, t3, expr1, expr2, expr3, true, false), (t1, t2, t3, expr1, expr2, expr3, false, true)) \
 \
	template <typename T1, typename T2, typename T3, typename T4> \
	bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4) const \
	RICHBOOL_OPERATOR((t1, t2, t3, t4)) \
 \
	template <typename T1, typename Expr1, typename T2, typename Expr2, \
		typename T3, typename Expr3, typename T4, typename Expr4> \
	Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, \
		Expr1 expr1, Expr2 expr2, Expr3 expr3, Expr4 expr4, \
		bool analyseOnSucceed=false, bool negate=false) const \
	RICHBOOL_ANALYSE((t1, t2, t3, t4), (t1, t2, t3, t4, expr1, expr2, expr3, analyseOnSucceed, false), \
		(t1, t2, t3, t4, expr1, expr2, expr3, true, false), (t1, t2, t3, t4, expr1, expr2, expr3, false, true))

	///////////////////////////////////////////////////////
	// template classes to combine Rich Boolean objects
	// in logical expressions

	template <class RB1, class RB2>
	struct And: public detail::AndBase<RB1, RB2>
	{
		And(RB1 rb1_=RB1(), RB2 rb2_=RB2()): detail::AndBase<RB1, RB2>(rb1_, rb2_) {}

		typedef typename detail::LogicFunctor<RB1, RB2>::Points1 Points1;
		typedef typename detail::LogicFunctor<RB1, RB2>::Points2 Points2;
		typedef typename detail::LogicFunctor<RB1, RB2>::NumPoints1 NumPoints1;
		typedef typename detail::LogicFunctor<RB1, RB2>::NumPoints2 NumPoints2;
		typedef typename detail::AndBase<RB1, RB2>::NumPoints NumPoints;
		typedef NumPoints Points;

		template <typename T1, typename T2>
		NumPoints GetPoints(const T1 &t1, const T2 &t2) const
		{
			const NumPoints1 p1 = detail::GetNumPoints<Points1>::Get(this->rb1, t1, t2),
				g1 = detail::GetNumPoints<Points1>::GetGood(this->rb1);
			if (p1==g1)
				return CalculatePoints(p1, g1,
					detail::GetNumPoints<Points2>::Get(this->rb2, t1, t2),
					detail::GetNumPoints<Points2>::GetGood(this->rb2));
			else
				return CalculatePoints(p1, g1,
					(Points2)0, // short circuiting prevents us from evaluating second condition
					detail::GetNumPoints<Points2>::GetGood(this->rb2));
		}

#define RICHBOOL_OPERATOR(ARGUMENTS) \
	{ if (this->rb1 ARGUMENTS ) return this->rb2 ARGUMENTS; else return false; }

#define RICHBOOL_ANALYSE(ARGUMENTS, ARGUMENTS_WE, ARGUMENTS_WE_AIS, ARGUMENTS_WE_NEG) \
{ \
	if (analyseOnSucceed) \
	{ \
		Analysis *an1 = this->rb1.Analyse ARGUMENTS_WE; \
		if (an1->GetState()!=Analysis::Ok) \
			return new AndAnalysis(an1, new AnalysisNotEvaluated); \
		else \
			return new AndAnalysis(an1, this->rb2.Analyse ARGUMENTS_WE); \
	} \
	if (!negate) \
	{ \
		Analysis *an1 = this->rb1.Analyse ARGUMENTS_WE; \
		if (an1 && an1->GetState()!=Analysis::Ok) \
			return new AndAnalysis(an1, new AnalysisNotEvaluated); \
		Analysis *an2 = this->rb2.Analyse ARGUMENTS_WE; \
		if (an2 && an2->GetState()!=Analysis::Ok) \
			return new AndAnalysis(an1, an2); \
		return 0; \
	} \
	else \
	{ \
		Analysis::State st=this->rb1.SafeCheck ARGUMENTS; \
		if (st==Analysis::NotOk) \
			return 0; \
		if (st==Analysis::BadValue) \
			return new AndAnalysis(this->rb1.Analyse ARGUMENTS_WE, new AnalysisNotEvaluated); \
		st=this->rb2.SafeCheck ARGUMENTS; \
		if (st==Analysis::NotOk) \
			return 0; \
		if (st==Analysis::BadValue) \
			return new AndAnalysis(Bool(true), this->rb2.Analyse ARGUMENTS_WE); \
		return new AndAnalysis(this->rb1.Analyse ARGUMENTS_WE_AIS, this->rb2.Analyse ARGUMENTS_WE_AIS); \
	} \
}

#define RICHBOOL_DUMMY_ANALYSIS(ARGUMENTS) \
{ \
	return new AndAnalysis(this->rb1.GetDummyAnalysis ARGUMENTS, this->rb2.GetDummyAnalysis ARGUMENTS); \
}

		RICHBOOL_METHODS

#undef RICHBOOL_OPERATOR
#undef RICHBOOL_ANALYSE
#undef RICHBOOL_DUMMY_ANALYSIS
	};

	template <class RB1, class RB2>
	struct AndBoth: public detail::AndBase<RB1, RB2>
	{
		AndBoth(RB1 rb1_=RB1(), RB2 rb2_=RB2()): detail::AndBase<RB1, RB2>(rb1_, rb2_) {}

		typedef typename detail::LogicFunctor<RB1, RB2>::Points1 Points1;
		typedef typename detail::LogicFunctor<RB1, RB2>::Points2 Points2;
		typedef typename detail::LogicFunctor<RB1, RB2>::NumPoints1 NumPoints1;
		typedef typename detail::LogicFunctor<RB1, RB2>::NumPoints2 NumPoints2;
		typedef typename detail::AndBase<RB1, RB2>::NumPoints NumPoints;
		typedef NumPoints Points;

		template <typename T1, typename T2>
		NumPoints GetPoints(const T1 &t1, const T2 &t2) const
		{
			return CalculatePoints(detail::GetNumPoints<Points1>::Get(this->rb1, t1, t2),
				detail::GetNumPoints<Points1>::GetGood(this->rb1),
				detail::GetNumPoints<Points2>::Get(this->rb2, t1, t2),
				detail::GetNumPoints<Points2>::GetGood(this->rb2));
		}

#define RICHBOOL_OPERATOR(ARGUMENTS) \
	{ if (this->rb1 ARGUMENTS ) return this->rb2 ARGUMENTS; else return false; }

#define RICHBOOL_ANALYSE(ARGUMENTS, ARGUMENTS_WE, ARGUMENTS_WE_AIS, ARGUMENTS_WE_NEG) \
{ \
	if (!negate||analyseOnSucceed) \
	{ \
		Analysis *an1 = this->rb1.Analyse ARGUMENTS_WE, \
			*an2 = this->rb2.Analyse ARGUMENTS_WE; \
		return (an1||an2) ? new AndAnalysis(an1, an2) : 0; \
	} \
	else \
	{ \
		Analysis::State st1=this->rb1.SafeCheck ARGUMENTS; \
		if (st1==Analysis::NotOk) return 0; \
		Analysis::State st2=this->rb2.SafeCheck ARGUMENTS; \
		if ((st1==Analysis::Ok)&&(st2==Analysis::NotOk)) return 0; \
		return new AndAnalysis(this->rb1.Analyse ARGUMENTS_WE_AIS, this->rb2.Analyse ARGUMENTS_WE_AIS); \
	} \
}

#define RICHBOOL_DUMMY_ANALYSIS(ARGUMENTS) \
{ \
	return new AndAnalysis(this->rb1.GetDummyAnalysis ARGUMENTS, this->rb2.GetDummyAnalysis ARGUMENTS); \
}

		RICHBOOL_METHODS

#undef RICHBOOL_OPERATOR
#undef RICHBOOL_ANALYSE
#undef RICHBOOL_DUMMY_ANALYSIS
	};

	template <class RB1, class RB2>
	struct Or: public detail::OrBase<RB1, RB2>
	{
		Or(RB1 rb1_=RB1(), RB2 rb2_=RB2()): detail::OrBase<RB1, RB2>(rb1_, rb2_) {}

		typedef typename detail::LogicFunctor<RB1, RB2>::Points1 Points1;
		typedef typename detail::LogicFunctor<RB1, RB2>::Points2 Points2;
		typedef typename detail::LogicFunctor<RB1, RB2>::NumPoints1 NumPoints1;
		typedef typename detail::LogicFunctor<RB1, RB2>::NumPoints2 NumPoints2;
		typedef typename detail::LogicFunctor<RB1, RB2>::Points Points;

		template <typename T1, typename T2>
		Points GetPoints(const T1 &t1, const T2 &t2) const
		{
			NumPoints1 p1 = detail::GetPoints<Points1>::Get(this->rb1, t1, t2),
				g1 = detail::GetPoints<Points1>::GetGood(this->rb1);
			if (p1==g1)
				return CalculatePoints(p1, g1,
					0, // short circuiting prevents us from evaluating second condition
					detail::GetPoints<Points2>::GetGood(this->rb2));
			else
				return CalculatePoints(p1, g1,
					detail::GetPoints<Points2>::Get(this->rb2, t1, t2),
					detail::GetPoints<Points2>::GetGood(this->rb2));
		}

#define RICHBOOL_OPERATOR(ARGUMENTS) \
	{ if (this->rb1 ARGUMENTS ) return true; else return this->rb2 ARGUMENTS; }

#define RICHBOOL_ANALYSE(ARGUMENTS, ARGUMENTS_WE, ARGUMENTS_WE_AIS, ARGUMENTS_WE_NEG) \
{ \
	if (analyseOnSucceed) \
	{ \
		Analysis *an1 = this->rb1.Analyse ARGUMENTS_WE; \
		if (an1->GetState()!=Analysis::NotOk) \
			return new OrAnalysis(an1, new AnalysisNotEvaluated); \
		else \
			return new OrAnalysis(an1, this->rb2.Analyse ARGUMENTS_WE); \
	} \
	if (!negate) \
	{ \
		Analysis::State st = this->rb1.SafeCheck ARGUMENTS; \
		if (st==Analysis::Ok) \
			return 0; \
		if (st==Analysis::BadValue) \
			return new OrAnalysis(this->rb1.Analyse ARGUMENTS_WE, new RichBool::AnalysisNotEvaluated); \
		Analysis *an2 = this->rb2.Analyse ARGUMENTS_WE; \
		if (an2) \
			return new OrAnalysis(this->rb1.Analyse ARGUMENTS_WE, an2); \
		return 0; \
	} \
	Analysis *an=this->rb1.Analyse ARGUMENTS_WE_NEG; \
	if (an) return new OrAnalysis(an, new AnalysisNotEvaluated); \
	an=this->rb2.Analyse ARGUMENTS_WE_NEG; \
	if (an) return new OrAnalysis(Bool(false), an); \
	return 0; \
}

#define RICHBOOL_DUMMY_ANALYSIS(ARGUMENTS) \
{ \
	return new OrAnalysis(this->rb1.GetDummyAnalysis ARGUMENTS, this->rb2.GetDummyAnalysis ARGUMENTS); \
}

	RICHBOOL_METHODS

#undef RICHBOOL_OPERATOR
#undef RICHBOOL_ANALYSE
#undef RICHBOOL_DUMMY_ANALYSIS
	};

	template <class RB1, class RB2>
	struct OrBoth: public detail::OrBase<RB1, RB2>
	{
		OrBoth(RB1 rb1_=RB1(), RB2 rb2_=RB2()): detail::OrBase<RB1, RB2>(rb1_, rb2_) {}

		typedef typename detail::LogicFunctor<RB1, RB2>::Points1 Points1;
		typedef typename detail::LogicFunctor<RB1, RB2>::Points2 Points2;
		typedef typename detail::LogicFunctor<RB1, RB2>::NumPoints1 NumPoints1;
		typedef typename detail::LogicFunctor<RB1, RB2>::NumPoints2 NumPoints2;
		typedef typename detail::LogicFunctor<RB1, RB2>::Points Points;

		template <typename T1, typename T2>
		Points GetPoints(const T1 &t1, const T2 &t2) const
		{
			return CalculatePoints(detail::GetPoints<Points1>::Get(this->rb1, t1, t2),
				detail::GetPoints<Points1>::GetGood(this->rb1),
				detail::GetPoints<Points2>::Get(this->rb2, t1, t2),
				detail::GetPoints<Points2>::GetGood(this->rb2));
		}

#define RICHBOOL_OPERATOR(ARGUMENTS) \
	{ if (this->rb1 ARGUMENTS ) return true; else return this->rb2 ARGUMENTS; }

#define RICHBOOL_ANALYSE(ARGUMENTS, ARGUMENTS_WE, ARGUMENTS_WE_AIS, ARGUMENTS_WE_NEG) \
{ \
	if (!analyseOnSucceed) \
	{ \
		if (!negate) \
		{ \
			if (this->rb1.SafeCheck ARGUMENTS ==Analysis::Ok) \
				return 0; \
			Analysis *an2 = this->rb2.Analyse ARGUMENTS_WE; \
			return an2 ? new OrAnalysis(this->rb1.Analyse ARGUMENTS_WE, an2) : 0; \
		} \
		Analysis *an1=this->rb1.Analyse ARGUMENTS_WE_NEG, \
			*an2=this->rb2.Analyse ARGUMENTS_WE_NEG; \
		return (an1||an2) ? new OrAnalysis(an1?Bool(an1):Bool(false), an2?Bool(an2):Bool(false)) : 0; \
	} \
	return new OrAnalysis(this->rb1.Analyse ARGUMENTS_WE, \
		this->rb2.Analyse ARGUMENTS_WE); \
}

#define RICHBOOL_DUMMY_ANALYSIS(ARGUMENTS) \
{ \
	return new OrAnalysis(this->rb1.GetDummyAnalysis ARGUMENTS, this->rb2.GetDummyAnalysis ARGUMENTS); \
}

	RICHBOOL_METHODS

#undef RICHBOOL_OPERATOR
#undef RICHBOOL_ANALYSE
#undef RICHBOOL_DUMMY_ANALYSIS
	};

	template <class RB1, class RB2>
	struct Xor: public detail::OrBase<RB1, RB2>
	{
		Xor(RB1 rb1_=RB1(), RB2 rb2_=RB2()): detail::OrBase<RB1, RB2>(rb1_, rb2_) {}

		typedef typename detail::LogicFunctor<RB1, RB2>::Points1 Points1;
		typedef typename detail::LogicFunctor<RB1, RB2>::Points2 Points2;
		typedef typename detail::LogicFunctor<RB1, RB2>::NumPoints1 NumPoints1;
		typedef typename detail::LogicFunctor<RB1, RB2>::NumPoints2 NumPoints2;
		typedef typename detail::LogicFunctor<RB1, RB2>::Points Points;

		Points CalculatePoints(NumPoints1 p1, NumPoints1 g1, NumPoints2 p2, NumPoints2 g2) const
		{
			if ( (p1==g1) && (p2==g2) )
				return detail::GetPoints<Points>::ToPoints(0);
			else
				return detail::GetPoints<Points>::ToPoints( (RICHBOOL_MAX(g1,g2)*
					RICHBOOL_MAX(p1*g2, p2*g1)) / (g1*g2) );
		}

		template <typename T1, typename T2>
		Points GetPoints(const T1 &t1, const T2 &t2) const
		{
			return CalculatePoints(detail::GetPoints<Points1>::Get(this->rb1, t1, t2),
				detail::GetPoints<Points1>::GetGood(this->rb1),
				detail::GetPoints<Points2>::Get(this->rb2, t1, t2),
				detail::GetPoints<Points2>::GetGood(this->rb2));
		}

#define RICHBOOL_OPERATOR(ARGUMENTS) \
	{ return XorBool(this->rb1 ARGUMENTS, this->rb2 ARGUMENTS); }

#define RICHBOOL_ANALYSE(ARGUMENTS, ARGUMENTS_WE, ARGUMENTS_WE_AIS, ARGUMENTS_WE_NEG) \
{ \
	if (!analyseOnSucceed) \
	{ \
		Analysis::State st=this->rb1.SafeCheck ARGUMENTS; \
		if (st==Analysis::BadValue) \
			return new XorAnalysis(this->rb1.Analyse ARGUMENTS_WE_AIS, new RichBool::AnalysisNotEvaluated); \
		Analysis *an2 = (st==(negate?Analysis::NotOk:Analysis::Ok)) ? \
			this->rb2.Analyse ARGUMENTS_WE_NEG : this->rb2.Analyse ARGUMENTS_WE; \
		return an2 ? new XorAnalysis(this->rb1.Analyse ARGUMENTS_WE_AIS, an2) : 0; \
	} \
	Analysis *an1=this->rb1.Analyse ARGUMENTS_WE; \
	if (an1->GetState()==Analysis::BadValue) \
		return new XorAnalysis(an1, new RichBool::AnalysisNotEvaluated); \
	return new XorAnalysis(an1, this->rb2.Analyse ARGUMENTS_WE); \
}

#define RICHBOOL_DUMMY_ANALYSIS(ARGUMENTS) \
{ \
	return new XorAnalysis(this->rb1.GetDummyAnalysis ARGUMENTS, this->rb2.GetDummyAnalysis ARGUMENTS); \
}

	RICHBOOL_METHODS

#undef RICHBOOL_OPERATOR
#undef RICHBOOL_ANALYSE
#undef RICHBOOL_DUMMY_ANALYSIS
	};

	template <class RB>
	struct Not: public Functors::Base
	{
		RB rb;

		Not() {}
		Not(RB rb_): rb(rb_) {}

		typedef typename RB::Points Points;

		typedef typename detail::ToNumPoints<Points>::Type NumPoints;

#define RICHBOOL_BIND(N) \
		template <typename T> \
		detail::String GetString##N(const T &t) const \
		{ return rb.GetString##N(t); } \
		template <typename T> \
		bool IsValid##N(const T &t) const \
		{ return rb.IsValid##N(t); }

		RICHBOOL_BIND(1)
		RICHBOOL_BIND(2)
		RICHBOOL_BIND(3)
		RICHBOOL_BIND(4)
		RICHBOOL_BIND(5)

#undef RICHBOOL_BIND

		template <typename T1, typename T2>
		NumPoints GetPoints(const T1 &t1, const T2 &t2) const
		{
			return detail::GetNumPoints<Points>::GetGood(this->rb)-
				detail::GetNumPoints<Points>::Get(this->rb, t1, t2);
		}

		template <typename T1, typename T2, typename T3, typename T4>
		NumPoints GetPoints(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4) const
		{
			return detail::GetNumPoints<Points>::GetGood(this->rb)-
				detail::GetNumPoints<Points>::Get(this->rb, t1, t2, t3, t4);
		}

#define RICHBOOL_OPERATOR(ARGUMENTS) \
	{ return !this->rb ARGUMENTS; }

#define RICHBOOL_SAFECHECK(ARGUMENTS) \
	{ return Analysis::Modify(this->rb.SafeCheck ARGUMENTS, true); }

#define RICHBOOL_ANALYSE(ARGUMENTS, ARGUMENTS_WE, ARGUMENTS_WE_AIS) \
{ \
	Analysis*a=this->rb.Analyse ARGUMENTS_WE ; \
	if (a) a->Negate(); \
	return a; \
}

	template <typename T1>
	bool operator()(const T1 &t1) const
	RICHBOOL_OPERATOR((t1))

	template <typename T1>
	Analysis::State SafeCheck(const T1 &t1) const
	RICHBOOL_SAFECHECK((t1))

	template <typename T1, typename Expr1>
	Analysis* Analyse(const T1 &t1, Expr1 expr1,
		bool analyseOnSucceed=false, bool negate=false) const
	RICHBOOL_ANALYSE((t1), (t1, expr1, analyseOnSucceed, !negate), (t1, expr1, true, !negate))

	template <typename T1, typename T2>
	bool operator()(const T1 &t1, const T2 &t2) const
	RICHBOOL_OPERATOR((t1, t2))

	template <typename T1, typename T2>
	Analysis::State SafeCheck(const T1 &t1, const T2 &t2) const
	RICHBOOL_SAFECHECK((t1, t2))

	template <typename T1, typename Expr1,
		typename T2, typename Expr2>
	Analysis* Analyse(const T1 &t1, const T2 &t2,
		Expr1 expr1, Expr2 expr2,
		bool analyseOnSucceed=false, bool negate=false) const
	RICHBOOL_ANALYSE((t1, t2), (t1, t2, expr1, expr2, analyseOnSucceed, !negate),
		(t1, t2, expr1, expr2, true, !negate))

	template <typename T1, typename Expr1, typename T2, typename Expr2>
	Analysis* GetDummyAnalysis(const T1 &t1, const T2 &t2, Expr1 expr1, Expr2 expr2) const
	{
		Analysis*a=this->rb.GetDummyAnalysis(t1, t2, expr1, expr2);
		if (a) a->Negate();
		return a;
	}

	template <typename T1, typename T2, typename T3>
	bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
	RICHBOOL_OPERATOR((t1, t2, t3))

	template <typename T1, typename T2, typename T3>
	Analysis::State SafeCheck(const T1 &t1, const T2 &t2, const T3 &t3) const
	RICHBOOL_SAFECHECK((t1, t2, t3))

	template <typename T1, typename Expr1,
		typename T2, typename Expr2, typename T3, typename Expr3>
	Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3,
		Expr1 expr1, Expr2 expr2, Expr3 expr3,
		bool analyseOnSucceed=false, bool negate=false) const
	RICHBOOL_ANALYSE((t1, t2, t3), (t1, t2, t3, expr1, expr2, expr3, analyseOnSucceed, !negate),
		(t1, t2, t3, expr1, expr2, expr3, true, !negate))

	template <typename T1, typename T2, typename T3, typename T4>
	bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4) const
	RICHBOOL_OPERATOR((t1, t2, t3, t4))

	template <typename T1, typename T2, typename T3, typename T4>
	Analysis::State SafeCheck(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4) const
	RICHBOOL_SAFECHECK((t1, t2, t3, t4))

	template <typename T1, typename Expr1, typename T2, typename Expr2,
	typename T3, typename Expr3, typename T4, typename Expr4>
	Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4,
		Expr1 expr1, Expr2 expr2, Expr3 expr3, Expr4 expr4,
		bool analyseOnSucceed=false, bool negate=false) const
	RICHBOOL_ANALYSE((t1, t2, t3, t4), (t1, t2, t3, t4, expr1, expr2, expr3, expr4, analyseOnSucceed, !negate),
		(t1, t2, t3, t4, expr1, expr2, expr3, expr4, true, !negate))

#undef RICHBOOL_OPERATOR
#undef RICHBOOL_ANALYSE
#undef RICHBOOL_DUMMY_ANALYSIS
	};

	namespace Functors
	{
		// Separate namespace to use operators &&, ||, &, |, ^ and !
		// with Koenig-lookup on Rich Boolean functors, but not
		// for other classes in the RichBool namespace.
		// This is done by deriving all classes that make
		// Rich Boolean functors from Functors::Base (see higher).

		template <class RB1, class RB2>
		And<RB1, RB2> operator&&(RB1 rb1, RB2 rb2)
		{
			return And<RB1, RB2>(rb1, rb2);
		}

		template <class RB1, class RB2>
		AndBoth<RB1, RB2> operator&(RB1 rb1, RB2 rb2)
		{
			return AndBoth<RB1, RB2>(rb1, rb2);
		}

		template <class RB1, class RB2>
		Or<RB1, RB2> operator||(RB1 rb1, RB2 rb2)
		{
			return Or<RB1, RB2>(rb1, rb2);
		}

		template <class RB1, class RB2>
		OrBoth<RB1, RB2> operator|(RB1 rb1, RB2 rb2)
		{
			return OrBoth<RB1, RB2>(rb1, rb2);
		}

		template <class RB1, class RB2>
		Xor<RB1, RB2> operator^(RB1 rb1, RB2 rb2)
		{
			return Xor<RB1, RB2>(rb1, rb2);
		}

		template <class RB>
		Not<RB> operator!(RB rb)
		{
			return Not<RB>(rb);
		}
	}
}

#endif // #ifndef RICH_BOOL_LOGIC_H__QM
