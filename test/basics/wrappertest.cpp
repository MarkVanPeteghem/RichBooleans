//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "richbool/richbool.hpp"

#include "rbtest.hpp"

namespace RichBool
{
#define RICHBOOL_SV_MEMBERS(N) \
	typename TF::Type##N Get##N() const \
	{ return tf.Get##N(RICHBOOL_TF_ARGS); } \
	typename TF::Expr##N GetExpr##N() const \
	{ return tf.GetExpr##N(RICHBOOL_TF_EXPRS); }

	template <class TF, typename T1, typename Expr1>
	struct Store1Value
	{
		TF tf;
		const T1 &t1;
		Expr1 expr1;

#define RICHBOOL_TF_ARGS t1
#define RICHBOOL_TF_EXPRS expr1
		RICHBOOL_SV_MEMBERS(1)
		RICHBOOL_SV_MEMBERS(2)
		RICHBOOL_SV_MEMBERS(3)
		RICHBOOL_SV_MEMBERS(4)
		RICHBOOL_SV_MEMBERS(5)
		RICHBOOL_SV_MEMBERS(6)
#undef RICHBOOL_TF_ARGS
#undef RICHBOOL_TF_EXPRS
	};
	template <class TF, typename T1, typename Expr1>
	Store1Value<TF, T1, Expr1> MakeStoreValues(TF tf, const T1 &t1, Expr1 expr1)
	{
		return Store1Value<TF, T1, Expr1>(tf, t1, expr1);
	}

	template <class TF, typename T1, typename Expr1, typename T2, typename Expr2>
	struct Store2Value
	{
		TF tf;
		const T1 &t1;
		Expr1 expr1;
		const T2 &t2;
		Expr2 expr2;

#define RICHBOOL_TF_ARGS t1, t2
#define RICHBOOL_TF_EXPRS expr1, expr2
		RICHBOOL_SV_MEMBERS(1)
		RICHBOOL_SV_MEMBERS(2)
		RICHBOOL_SV_MEMBERS(3)
		RICHBOOL_SV_MEMBERS(4)
		RICHBOOL_SV_MEMBERS(5)
		RICHBOOL_SV_MEMBERS(6)
#undef RICHBOOL_TF_ARGS
#undef RICHBOOL_TF_EXPRS
	};
	template <class TF, typename T1, typename Expr1, typename T2, typename Expr2>
	Store2Value<TF, T1, Expr1, T2, Expr2> MakeStoreValues(TF tf, const T1 &t1, Expr1 expr1,
		const T2 &t2, Expr2 expr2)
	{
		return Store2Value<TF, T1, Expr1, T2, Expr2>(tf, t1, expr1, t2, expr2);
	}


	template <int nrArgs>
	struct Call {};
#define RICHBOOL_CALL_SPEC(N, VALS, VALS_AND_EXPRS) \
	template <> struct Call<N> { \
		template <class Func, class SV> \
		static bool Check(Func f, const SV &sv) \
		{ \
			return f VALS; \
		} \
		template <class Func, class SV> \
		static Analysis* Analyse(Func f, const SV &sv, bool ais=true, bool neg=false) \
		{ \
			return f.Analyse VALS_AND_EXPRS; \
		} \
	};
	RICHBOOL_CALL_SPEC(1, (sv.Get1()), (sv.Get1(), sv.GetExpr1(), ais, neg))
	RICHBOOL_CALL_SPEC(2, (sv.Get1(), sv.Get2()), (sv.Get1(), sv.GetExpr1(), sv.Get2(), sv.GetExpr2(), ais, neg))
	RICHBOOL_CALL_SPEC(3, (sv.Get1(), sv.Get2(), sv.Get3()),
		(sv.Get1(), sv.GetExpr1(), sv.Get2(), sv.GetExpr2(), sv.Get3(), sv.GetExpr3(), ais, neg))

	template <class Core,
		int nrArgs,
		class Transform,
		class GetValue1_=Value,
		class Str_=MakeString>
	class FunctorCoreWrapper: public FunctorCoreBase
	{
		Core core;
		Transform tf;
	public:
		FunctorCoreWrapper(Core cond=Core(), Transform tf_=Transform()): core(cond), tf(tf_)
		{}

		template<typename T1>
		bool operator()(const T1 &t1) const
		{
			return Call<nrArgs>::Call(core(tf.Get1(getValue1(t1))));
		}
		template<typename T1, typename Expr>
		Analysis* Analyse(const T1 &t1, Expr expr1,
			bool analyseIfSuccess=false, bool negate=false) const
		{
			return core.Analyse(core, tf.Get1(t1), tf.GetExpr1(expr1), analyseIfSuccess, negate);
		}
		template<typename T1, typename T2>
		bool operator()(const T1 &t1, const T2 &t2) const
		{
			return Call<nrArgs>::Check(core, MakeStoreValues(tf, t1));
		}
	};
}
