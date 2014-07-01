//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_BIND_H__QM
#define RICH_BOOL_BIND_H__QM

#include "richbool/base.hpp"

namespace RichBool
{
	template <class RichBool_, typename T>
	class BindBase: public Functors::Base
	{
	protected:
		SharedExpression expr;
	public:
		BindBase(const T &t):
		  bound(t) {}
		BindBase(RichBool_ rb_, const T &t):
		  rb(rb_), bound(t) {}

		template<typename Expr>
		BindBase(const T &t, Expr expr_):
		  bound(t), expr(MakeExpression(expr_)) {}
		template<typename Expr>
		BindBase(RichBool_ rb_, const T &t, Expr expr_):
		  rb(rb_), bound(t), expr(MakeExpression(expr_)) {}

		RichBool_ rb;
		T bound;
		typedef typename RichBool_::Points Points;
	};

#define RICHBOOL_BIND(FROM, TO) \
	template<typename U> \
	detail::String GetString##FROM(const U &u) const \
	{ \
		return BindBase<RichBool_, T>::rb.GetString##TO(u); \
	} \
	template<typename U> \
	bool IsValid##FROM(const U &u) const \
	{ \
		return BindBase<RichBool_, T>::rb.IsValid##TO(u); \
	}

#define RICHBOOL_BINDINGS(TO) \
	RICHBOOL_BIND(1,TO) \
	template<typename U> \
	Analysis::State SafeCheck(const U &u) const \
	{ \
		if (!this->rb.IsValid##TO(u)) \
			return Analysis::BadValue; \
		return operator()(u) ? Analysis::Ok : Analysis::NotOk; \
	}

	template <class RichBool_, typename T>
	struct BindArg1Of2: public BindBase<RichBool_, T>
	{
		BindArg1Of2(const T &t):
		  BindBase<RichBool_, T>(t) {}
		BindArg1Of2(RichBool_ rb_, const T &t):
		  BindBase<RichBool_, T>(rb_, t) {}

		template<typename Expr>
		BindArg1Of2(const T &t, Expr expr_):
		  BindBase<RichBool_, T>(t, expr_) {}
		template<typename Expr>
		BindArg1Of2(RichBool_ rb_, const T &t, Expr expr_):
		  BindBase<RichBool_, T>(rb_, t, expr_) {}

		template<typename T1>
		bool operator()(const T1 &a) const
		{
			return this->rb(this->bound, a);
		}
		template<typename T1, typename Expr1>
		Analysis* Analyse(const T1 &a, Expr1 expr1,
			bool analyseOnSucceed=false) const
		{
			return this->rb.Analyse(this->bound, a, this->expr, expr1, analyseOnSucceed);
		}
		RICHBOOL_BINDINGS(2)
	};

	template <class RichBool_, typename T>
	struct BindArg2Of2: public BindBase<RichBool_, T>
	{
		BindArg2Of2(const T &t):
		  BindBase<RichBool_, T>(t) {}
		BindArg2Of2(RichBool_ rb_, const T &t):
		  BindBase<RichBool_, T>(rb_, t) {}

		template<typename Expr>
		BindArg2Of2(const T &t, Expr expr_):
		  BindBase<RichBool_, T>(t, expr_) {}
		template<typename Expr>
		BindArg2Of2(RichBool_ rb_, const T &t, Expr expr_):
		  BindBase<RichBool_, T>(rb_, t, expr_) {}

		template<typename T1>
		bool operator()(const T1 &a) const
		{
			return this->rb(a, this->bound);
		}
		template<typename T1, typename Expr1>
		Analysis* Analyse(const T1 &a,
			Expr1 expr1,
			bool analyseOnSucceed=false) const
		{
			return this->rb.Analyse(a, this->bound, expr1, this->expr, analyseOnSucceed);
		}
		RICHBOOL_BINDINGS(1)
	};

#undef RICHBOOL_BINDINGS
#define RICHBOOL_BINDINGS(TO1, TO2) \
	RICHBOOL_BIND(1,TO1) \
	RICHBOOL_BIND(2,TO2) \
	template<typename U, typename V> \
	Analysis::State SafeCheck(const U &u, const V &v) const \
	{ \
		if (!this->rb.IsValid##TO1(u)||!this->rb.IsValid##TO2(v)) \
			return Analysis::BadValue; \
		return operator()(u,v) ? Analysis::Ok : Analysis::NotOk; \
	}

	template <class RichBool_, typename T>
	struct BindArg1Of3: public BindBase<RichBool_, T>
	{
		BindArg1Of3(const T &t):
		  BindBase<RichBool_, T>(t) {}
		BindArg1Of3(RichBool_ rb_, const T &t):
		  BindBase<RichBool_, T>(rb_, t) {}

		template<typename Expr>
		BindArg1Of3(const T &t, Expr expr_):
		  BindBase<RichBool_, T>(t, expr_) {}
		template<typename Expr>
		BindArg1Of3(RichBool_ rb_, const T &t, Expr expr_):
		  BindBase<RichBool_, T>(rb_, t, expr_) {}

		template<typename T1, typename T2>
		bool operator()(const T1 &a, const T2 &b) const
		{
			return this->rb(this->bound, a, b);
		}
		template<typename T1, typename T2, typename Expr1, typename Expr2>
		Analysis* Analyse(const T1 &a, const T2 &b,
			Expr1 expr1, Expr2 expr2,
			bool analyseOnSucceed=false) const
		{
			return this->rb.Analyse(this->bound, a, b, this->expr, expr1, expr2, analyseOnSucceed);
		}
		RICHBOOL_BINDINGS(2,3)
	};

	template <class RichBool_, typename T>
	struct BindArg2Of3: public BindBase<RichBool_, T>
	{
		BindArg2Of3(const T &t):
		  BindBase<RichBool_, T>(t) {}
		BindArg2Of3(RichBool_ rb_, const T &t):
		  BindBase<RichBool_, T>(rb_, t) {}

		template<typename Expr>
		BindArg2Of3(const T &t, Expr expr_):
		  BindBase<RichBool_, T>(t, expr_) {}
		template<typename Expr>
		BindArg2Of3(RichBool_ rb_, const T &t, Expr expr_):
		  BindBase<RichBool_, T>(rb_, t, expr_) {}

		template<typename T1, typename T2>
		bool operator()(const T1 &a, const T2 &b) const
		{
			return this->rb(a, this->bound, b);
		}
		template<typename T1, typename T2, typename Expr1, typename Expr2>
		Analysis* Analyse(const T1 &a, const T2 &b,
			Expr1 expr1, Expr2 expr2,
			bool analyseOnSucceed=false) const
		{
			return this->rb.Analyse(a, this->bound, b, expr1, this->expr, expr2, analyseOnSucceed);
		}
		RICHBOOL_BINDINGS(1,3)
	};

	template <class RichBool_, typename T>
	struct BindArg3Of3: public BindBase<RichBool_, T>
	{
		BindArg3Of3(const T &t):
		  BindBase<RichBool_, T>(t) {}
		BindArg3Of3(RichBool_ rb_, const T &t):
		  BindBase<RichBool_, T>(rb_, t) {}

		template<typename Expr>
		BindArg3Of3(const T &t, Expr expr_):
		  BindBase<RichBool_, T>(t, expr_) {}
		template<typename Expr>
		BindArg3Of3(RichBool_ rb_, const T &t, Expr expr_):
		  BindBase<RichBool_, T>(rb_, t, expr_) {}

		template<typename T1, typename T2>
		bool operator()(const T1 &a, const T2 &b) const
		{
			return this->rb(a, b, this->bound);
		}
		template<typename T1, typename T2, typename Expr1, typename Expr2>
		Analysis* Analyse(const T1 &a, const T2 &b,
			Expr1 expr1, Expr2 expr2,
			bool analyseOnSucceed=false) const
		{
			return this->rb.Analyse(a, b, this->bound, expr1, expr2, this->expr, analyseOnSucceed);
		}
		RICHBOOL_BINDINGS(1, 2)
	};

#undef RICHBOOL_BIND
#undef RICHBOOL_BINDINGS

	template <class RichBool_, typename T2>
	struct BindArg2Of2Ref
	{
		BindArg2Of2Ref(RichBool_ rb_, const T2 &t2_, const char *str2_):
			rb(rb_), t2(t2_), str2(str2_) {}

		template<typename T1>
		bool operator()(const T1 &t1) const
		{
			return rb(t1, t2);
		}

		template<typename T1>
		RichBool::Analysis* Analyse(const T1 &t1, const char *expr,
			bool analyseOnSucceed=false) const
		{
			return rb.Analyse(t1, t2, expr, str2, analyseOnSucceed);
		}

		RichBool_ rb;
		const T2 &t2;
		const char *str2;

	private:
		BindArg2Of2Ref& operator=(const BindArg2Of2Ref &)
		{
			return *this;
		}
	};

	template <class RichBool_, typename T1>
	struct BindArg1Of2Ref
	{
		BindArg1Of2Ref(RichBool_ rb_, const T1 &t1_, const char *str1_):
			rb(rb_), t1(t1_), str1(str1_) {}

		template<typename T2>
		bool operator()(const T2 &t2) const
		{
			return rb(t1, t2);
		}

		template<typename T2>
		RichBool::Analysis* Analyse(const T2 &t2, const char *expr,
			bool analyseOnSucceed=false) const
		{
			return rb.Analyse(t1, t2, str1, expr, analyseOnSucceed);
		}

		RichBool_ rb;
		const T1 &t1;
		const char *str1;

	private:
		BindArg1Of2Ref& operator=(const BindArg1Of2Ref &)
		{
			return *this;
		}
	};

	template <class RichBool_, typename T1>
	BindArg1Of2Ref<RichBool_, T1> MakeBind1Of2(RichBool_ rb, const T1 &t1, const char *str1)
	{
		return BindArg1Of2Ref<RichBool_, T1>(rb, t1, str1);
	}

	template <class RichBool_, typename T2>
	BindArg2Of2Ref<RichBool_, T2> MakeBind2Of2(RichBool_ rb, const T2 &t2, const char *str2)
	{
		return BindArg2Of2Ref<RichBool_, T2>(rb, t2, str2);
	}

#define RICHBOOL_BIND_REF_3(A,B,C) \
	template <class RichBool_, typename T##B, typename T##C> \
	struct BindArg##A##Of3Ref { \
		BindArg##A##Of3Ref(RichBool_ rb_, const T##B &t##B##_, const char *str##B##_, \
			const T##C &t##C##_, const char *str##C##_): \
		rb(rb_), t##B(t##B##_), str##B(str##B##_), t##C(t##C##_), str##C(str##C##_) {} \
		template<typename T> \
		bool operator()(const T &t##A) const \
		{ \
			return rb(t1, t2, t3); \
		} \
		template<typename T> \
		RichBool::Analysis* Analyse(const T &t##A, const char *str##A, \
			bool analyseOnSucceed=false) const \
		{ \
			return rb.Analyse(t1, t2, t3, str1, str2, str3, analyseOnSucceed); \
		} \
		RichBool_ rb; \
		const T##B &t##B; \
		const T##C &t##C; \
		const char *str##B, *str##C; \
	private: \
		BindArg##A##Of3Ref& operator=(const BindArg##A##Of3Ref &) \
		{ \
			return *this; \
		} \
	}; \
	template <class RichBool_, typename T, typename U> \
	BindArg##A##Of3Ref<RichBool_, T, U> MakeBind##A##Of3(RichBool_ rb,  \
		const T &t, const char *str_t, \
		const U &u, const char *str_u) \
	{ \
		return BindArg##A##Of3Ref<RichBool_, T, U>(rb, t, str_t, u, str_u); \
	} \

RICHBOOL_BIND_REF_3(1,2,3)
RICHBOOL_BIND_REF_3(2,1,3)
RICHBOOL_BIND_REF_3(3,1,2)

#define RICHBOOL_BIND_REF_4(A,B,C,D) \
	template <class RichBool_, typename T##B, typename T##C, typename T##D> \
	struct BindArg##A##Of4Ref { \
		BindArg##A##Of4Ref(RichBool_ rb_, const T##B &t##B##_, const char *str##B##_, \
			const T##C &t##C##_, const char *str##C##_, const T##D &t##D##_, const char *str##D##_): \
		rb(rb_), t##B(t##B##_), str##B(str##B##_), t##C(t##C##_), str##C(str##C##_), \
		t##D(t##D##_), str##D(str##D##_) {} \
		template<typename T> \
		bool operator()(const T &t##A) const \
		{ \
			return rb(t1, t2, t3, t4); \
		} \
		template<typename T> \
		RichBool::Analysis* Analyse(const T &t##A, const char *str##A, \
			bool analyseOnSucceed=false) const \
		{ \
			return rb.Analyse(t1, t2, t3, t4, str1, str2, str3, str4, analyseOnSucceed); \
		} \
		RichBool_ rb; \
		const T##B &t##B; \
		const T##C &t##C; \
		const T##D &t##D; \
		const char *str##B, *str##C, *str##D; \
	private: \
		BindArg##A##Of4Ref& operator=(const BindArg##A##Of4Ref &) \
		{ \
			return *this; \
		} \
	}; \
	template <class RichBool_, typename T, typename U, typename V> \
	BindArg##A##Of4Ref<RichBool_, T, U, V> MakeBind##A##Of4(RichBool_ rb, \
		const T &t, const char *str_t, \
		const U &u, const char *str_u, \
		const V &v, const char *str_v) \
	{ \
		return BindArg##A##Of4Ref<RichBool_, T, U, V> \
			(rb, t, str_t, u, str_u, v, str_v); \
	} \

RICHBOOL_BIND_REF_4(1,2,3,4)
RICHBOOL_BIND_REF_4(2,1,3,4)
RICHBOOL_BIND_REF_4(3,1,2,4)
RICHBOOL_BIND_REF_4(4,1,2,3)

#define RICHBOOL_BIND_REF_5(A,B,C,D,E) \
	template <class RichBool_, typename T##B, typename T##C, typename T##D, typename T##E> \
	struct BindArg##A##Of5Ref { \
		BindArg##A##Of5Ref(RichBool_ rb_, const T##B &t##B##_, const char *str##B##_, \
			const T##C &t##C##_, const char *str##C##_, const T##D &t##D##_, const char *str##D##_, \
			const T##E &t##E##_, const char *str##E##_): \
		rb(rb_), t##B(t##B##_), str##B(str##B##_), t##C(t##C##_), str##C(str##C##_), \
		t##D(t##D##_), str##D(str##D##_), t##E(t##E##_), str##E(str##E##_) {} \
		template<typename T> \
		bool operator()(const T &t##A) const \
		{ \
			return rb(t1, t2, t3, t4, t5); \
		} \
		template<typename T> \
		RichBool::Analysis* Analyse(const T &t##A, const char *str##A, \
			bool analyseOnSucceed=false) const \
		{ \
			return rb.Analyse(t1, t2, t3, t4, t5, str1, str2, str3, str4, str5, analyseOnSucceed); \
		} \
		RichBool_ rb; \
		const T##B &t##B; \
		const T##C &t##C; \
		const T##D &t##D; \
		const T##E &t##E; \
		const char *str##B, *str##C, *str##D, *str##E; \
	private: \
		BindArg##A##Of5Ref& operator=(const BindArg##A##Of5Ref &) \
		{ \
			return *this; \
		} \
	}; \
	template <class RichBool_, typename T, typename U, typename V, typename W> \
	BindArg##A##Of5Ref<RichBool_, T, U, V, W> MakeBind##A##Of5(RichBool_ rb, \
		const T &t, const char *str_t, \
		const U &u, const char *str_u, \
		const V &v, const char *str_v, \
		const W &w, const char *str_w) \
	{ \
		return BindArg##A##Of5Ref<RichBool_, T, U, V, W> \
			(rb, t, str_t, u, str_u, v, str_v, w, str_w); \
	} \

RICHBOOL_BIND_REF_5(1,2,3,4,5)
RICHBOOL_BIND_REF_5(2,1,3,4,5)
RICHBOOL_BIND_REF_5(3,1,2,4,5)
RICHBOOL_BIND_REF_5(4,1,2,3,5)
RICHBOOL_BIND_REF_5(5,1,2,3,4)


#define RICHBOOL_BIND_REF_6(A,B,C,D,E,F) \
	template <class RichBool_, typename T##B, typename T##C, typename T##D, typename T##E, typename T##F> \
	struct BindArg##A##Of6Ref { \
		BindArg##A##Of6Ref(RichBool_ rb_, const T##B &t##B##_, const char *str##B##_, \
			const T##C &t##C##_, const char *str##C##_, const T##D &t##D##_, const char *str##D##_, \
			const T##E &t##E##_, const char *str##E##_, const T##F &t##F##_, const char *str##F##_): \
		rb(rb_), t##B(t##B##_), str##B(str##B##_), t##C(t##C##_), str##C(str##C##_), \
		t##D(t##D##_), str##D(str##D##_), t##E(t##E##_), str##E(str##E##_), t##F(t##F##_), str##F(str##F##_) {} \
		template<typename T> \
		bool operator()(const T &t##A) const \
		{ \
			return rb(t1, t2, t3, t4, t5, t6); \
		} \
		template<typename T> \
		RichBool::Analysis* Analyse(const T &t##A, const char *str##A, \
			bool analyseOnSucceed=false) const \
		{ \
			return rb.Analyse(t1, t2, t3, t4, t5, t6, str1, str2, str3, str4, str5, str6, analyseOnSucceed); \
		} \
		RichBool_ rb; \
		const T##B &t##B; \
		const T##C &t##C; \
		const T##D &t##D; \
		const T##E &t##E; \
		const T##F &t##F; \
		const char *str##B, *str##C, *str##D, *str##E, *str##F; \
	private: \
		BindArg##A##Of6Ref& operator=(const BindArg##A##Of6Ref &) \
		{ \
			return *this; \
		} \
	}; \
	template <class RichBool_, typename T, typename U, typename V, typename W, typename X> \
	BindArg##A##Of6Ref<RichBool_, T, U, V, W, X> MakeBind##A##Of6(RichBool_ rb, \
		const T &t, const char *str_t, \
		const U &u, const char *str_u, \
		const V &v, const char *str_v, \
		const W &w, const char *str_w, \
		const X &x, const char *str_x) \
	{ \
		return BindArg##A##Of6Ref<RichBool_, T, U, V, W, X> \
			(rb, t, str_t, u, str_u, v, str_v, w, str_w, x, str_x); \
	}

RICHBOOL_BIND_REF_6(1,2,3,4,5,6)
RICHBOOL_BIND_REF_6(2,1,3,4,5,6)
RICHBOOL_BIND_REF_6(3,1,2,4,5,6)
RICHBOOL_BIND_REF_6(4,1,2,3,5,6)
RICHBOOL_BIND_REF_6(5,1,2,3,4,6)
RICHBOOL_BIND_REF_6(6,1,2,3,4,5)
}

#endif // #ifndef RICH_BOOL_BIND_H__QM
