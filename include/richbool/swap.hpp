//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_SWAP_H__QM
#define RICH_BOOL_SWAP_H__QM

#include "richbool/base.hpp"

namespace RichBool
{
	template <class RB>
	struct Swap: public Functors::Base
	{
		Swap() {}
		Swap(RB rb_): rb(rb_) {}
		
		RB rb;
		typedef typename RB::Points Points;

		template<typename T1, typename T2>
		bool operator()(const T1 &t1, const T2 &t2) const
		{
			return rb(t2, t1);
		}
		template<typename T1, typename T2>
		Analysis::State SafeCheck(const T1 &a, const T2 &b) const
		{
			return rb.SafeCheck(b, a);
		}
		template<typename T1, typename Expr1, typename T2, typename Expr2>
		Analysis* Analyse(const T1 &a, const T2 &b, Expr1 expr1, Expr2 expr2,
			bool analyseOnSucceed=false, bool negate=false) const
		{
			return rb.Analyse(b, a, expr2, expr1, analyseOnSucceed, negate);
		}
	};
}

#endif // #ifndef RICH_BOOL_SWAP_H__QM
