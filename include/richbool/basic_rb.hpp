//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_BASICS_H__QM
#define RICH_BOOL_BASICS_H__QM

#ifdef RICHBOOL_NO_TEXT
#define RICHBOOL_TEXT_EXPR(arg) (const char*)NULL
#else
#define RICHBOOL_TEXT_EXPR(arg) arg
#endif

#include "richbool/bind.hpp"

namespace RichBool {
	// simple function to circumvent parsing problems
	template <class RB>
	RB Id(RB rb) { return rb; }
}

#define rb1_RB_IMPL(a,ea,functor) (richbool_level>=2 ? \
	RichBool::TmpBool((functor).Analyse(a, ea, richbool_level==3)) : \
	( richbool_level==1 ? RichBool::TmpBool(RichBool::Id(functor(a))) : (a,RichBool::TmpBool(true)) ) \
	)
#define rbv1_1_RB_IMPL(a,ea,functor) functor,ea,a

#define rb1_RB(a,functor)    rb1_RB_IMPL(a,RICHBOOL_TEXT_EXPR(#a),functor)
#define rbv1_1_RB(a,functor) rbv1_1_RB_IMPL(a,RICHBOOL_TEXT_EXPR(#a),functor)

#define rb2_RB_IMPL(a,ea,b,eb,functor) (richbool_level>=2 ? \
	RichBool::TmpBool((functor).Analyse(a,b,ea,eb,richbool_level==3)) : \
	( richbool_level==1 ? RichBool::TmpBool(RichBool::Id(functor(a,b))) : (a,b,RichBool::TmpBool(true)) ) \
	)
#define rb2_RB(a,b,functor) rb2_RB_IMPL(a,RICHBOOL_TEXT_EXPR(#a),b,RICHBOOL_TEXT_EXPR(#b),functor)
#define rbv2_1_RB_IMPL(a,ea,b,eb,functor) RichBool::MakeBind2Of2(functor, b, eb),ea,a
#define rbv2_2_RB_IMPL(a,ea,b,eb,functor) RichBool::MakeBind1Of2(functor, a, ea),eb,b
#define rbv2_1_RB(a,b,functor) rbv2_1_RB_IMPL(a, RICHBOOL_TEXT_EXPR(#a), b, RICHBOOL_TEXT_EXPR(#b), functor)
#define rbv2_2_RB(a,b,functor) rbv2_2_RB_IMPL(a, RICHBOOL_TEXT_EXPR(#a), b, RICHBOOL_TEXT_EXPR(#b), functor)

#define rb3_RB_IMPL(a,ea,b,eb,c,ec,functor) (richbool_level>=2 ? \
	RichBool::TmpBool((functor).Analyse(a,b,c,ea,eb,ec,richbool_level==3)) : \
	( richbool_level==1 ? RichBool::TmpBool(RichBool::Id(functor(a,b,c))) : (a,b,c,RichBool::TmpBool(true)) ) \
	)
#define rb3_RB(a,b,c,functor) rb3_RB_IMPL(a,RICHBOOL_TEXT_EXPR(#a),b,RICHBOOL_TEXT_EXPR(#b),c,RICHBOOL_TEXT_EXPR(#c),functor)

#define rbv3_1_RB(a,b,c,functor) RichBool::MakeBind1Of3(functor, b, RICHBOOL_TEXT_EXPR(#b), c, RICHBOOL_TEXT_EXPR(#c)),RICHBOOL_TEXT_EXPR(#a),a
#define rbv3_2_RB(a,b,c,functor) RichBool::MakeBind2Of3(functor, a, RICHBOOL_TEXT_EXPR(#a), c, RICHBOOL_TEXT_EXPR(#c)),RICHBOOL_TEXT_EXPR(#b),b
#define rbv3_3_RB(a,b,c,functor) RichBool::MakeBind3Of3(functor, a, RICHBOOL_TEXT_EXPR(#a), b, RICHBOOL_TEXT_EXPR(#b)),RICHBOOL_TEXT_EXPR(#c),c

#define rb4_RB_IMPL(a,ea,b,eb,c,ec,d,ed,functor) (richbool_level>=2 ? \
	RichBool::TmpBool((functor).Analyse(a,b,c,d, \
		RICHBOOL_TEXT_EXPR(ea),RICHBOOL_TEXT_EXPR(eb),RICHBOOL_TEXT_EXPR(ec), \
		RICHBOOL_TEXT_EXPR(ed), richbool_level==3)) : \
	( richbool_level==1 ? RichBool::TmpBool(RichBool::Id(functor(a,b,c,d))) : (a,b,c,d,RichBool::TmpBool(true)) ) \
	)
#define rb4_RB(a,b,c,d,functor) rb4_RB_IMPL(a,#a,b,#b,c,#c,d,#d,functor)
#define rbv4_1_RB_IMPL(a,ea,b,eb,c,ec,d,ed,functor) RichBool::MakeBind1Of4(functor, b, RICHBOOL_TEXT_EXPR(eb), c, RICHBOOL_TEXT_EXPR(ec), d, RICHBOOL_TEXT_EXPR(ed)),RICHBOOL_TEXT_EXPR(ea),a
#define rbv4_1_RB(a,b,c,d,functor) rbv4_1_RB_IMPL(a,#a,b,#b,c,#c,d,#d,functor)
#define rbv4_2_RB(a,b,c,d,functor) RichBool::MakeBind2Of4(functor, a, RICHBOOL_TEXT_EXPR(#a), c, RICHBOOL_TEXT_EXPR(#c), d, RICHBOOL_TEXT_EXPR(#d)),RICHBOOL_TEXT_EXPR(#b),b
#define rbv4_3_RB(a,b,c,d,functor) RichBool::MakeBind3Of4(functor, a, RICHBOOL_TEXT_EXPR(#a), b, RICHBOOL_TEXT_EXPR(#b), d, RICHBOOL_TEXT_EXPR(#d)),RICHBOOL_TEXT_EXPR(#c),c
#define rbv4_4_RB(a,b,c,d,functor) RichBool::MakeBind4Of4(functor, a, RICHBOOL_TEXT_EXPR(#a), b, RICHBOOL_TEXT_EXPR(#b), c, RICHBOOL_TEXT_EXPR(#c)),RICHBOOL_TEXT_EXPR(#d),d

#define rb5_RB(a,b,c,d,e,functor) (richbool_level>=2 ? \
	RichBool::TmpBool((functor).Analyse(a,b,c,d,e, \
		RICHBOOL_TEXT_EXPR(#a),RICHBOOL_TEXT_EXPR(#b),RICHBOOL_TEXT_EXPR(#c), \
		RICHBOOL_TEXT_EXPR(#d),RICHBOOL_TEXT_EXPR(#e), richbool_level==3)) : \
	( richbool_level==1 ? RichBool::TmpBool(RichBool::Id(functor(a,b,c,d,e))) : (a,b,c,d,e,RichBool::TmpBool(true)) ) \
	)
#define rbv5_1_RB(a,b,c,d,e,functor) RichBool::MakeBind1Of5(functor, b, \
	RICHBOOL_TEXT_EXPR(#b), c, RICHBOOL_TEXT_EXPR(#c), d, RICHBOOL_TEXT_EXPR(#d), e, RICHBOOL_TEXT_EXPR(#e)),RICHBOOL_TEXT_EXPR(#a),a
#define rbv5_2_RB(a,b,c,d,e,functor) RichBool::MakeBind2Of5(functor, a, \
	RICHBOOL_TEXT_EXPR(#a), c, RICHBOOL_TEXT_EXPR(#c), d, RICHBOOL_TEXT_EXPR(#d), e, RICHBOOL_TEXT_EXPR(#e)),RICHBOOL_TEXT_EXPR(#b),b
#define rbv5_3_RB(a,b,c,d,e,functor) RichBool::MakeBind3Of5(functor, a, \
	RICHBOOL_TEXT_EXPR(#a), b, RICHBOOL_TEXT_EXPR(#b), d, RICHBOOL_TEXT_EXPR(#d), e, RICHBOOL_TEXT_EXPR(#e)),RICHBOOL_TEXT_EXPR(#c),c
#define rbv5_4_RB(a,b,c,d,e,functor) RichBool::MakeBind4Of5(functor, a, \
	RICHBOOL_TEXT_EXPR(#a), b, RICHBOOL_TEXT_EXPR(#b), c, RICHBOOL_TEXT_EXPR(#c), e, RICHBOOL_TEXT_EXPR(#e)),RICHBOOL_TEXT_EXPR(#d),d
#define rbv5_5_RB(a,b,c,d,e,functor) RichBool::MakeBind5Of5(functor, a, \
	RICHBOOL_TEXT_EXPR(#a), b, RICHBOOL_TEXT_EXPR(#b), c, RICHBOOL_TEXT_EXPR(#c), d, RICHBOOL_TEXT_EXPR(#d)),RICHBOOL_TEXT_EXPR(#e),e

#define rb6_RB(a,b,c,d,e,f,functor) (richbool_level>=2 ? \
	RichBool::TmpBool((functor).Analyse(a,b,c,d,e,f, \
		RICHBOOL_TEXT_EXPR(#a),RICHBOOL_TEXT_EXPR(#b),RICHBOOL_TEXT_EXPR(#c), \
		RICHBOOL_TEXT_EXPR(#d),RICHBOOL_TEXT_EXPR(#e),RICHBOOL_TEXT_EXPR(#f), \
		richbool_level==3)) : \
	( richbool_level==1 ? RichBool::TmpBool(RichBool::Id(functor(a,b,c,d,e,f))) : (a,b,c,d,e,f,RichBool::TmpBool(true)) ) \
	)
#define rbv6_1_RB(a,b,c,d,e,f,functor) RichBool::MakeBind1Of6(functor, b, \
	RICHBOOL_TEXT_EXPR(#b), c, RICHBOOL_TEXT_EXPR(#c), d, RICHBOOL_TEXT_EXPR(#d), e, RICHBOOL_TEXT_EXPR(#e), f, RICHBOOL_TEXT_EXPR(#f)),RICHBOOL_TEXT_EXPR(#a),a
#define rbv6_2_RB(a,b,c,d,e,f,functor) RichBool::MakeBind2Of6(functor, a, \
	RICHBOOL_TEXT_EXPR(#a), c, RICHBOOL_TEXT_EXPR(#c), d, RICHBOOL_TEXT_EXPR(#d), e, RICHBOOL_TEXT_EXPR(#e), f, RICHBOOL_TEXT_EXPR(#f)),RICHBOOL_TEXT_EXPR(#b),b
#define rbv6_3_RB(a,b,c,d,e,f,functor) RichBool::MakeBind3Of6(functor, a, \
	RICHBOOL_TEXT_EXPR(#a), b, RICHBOOL_TEXT_EXPR(#b), d, RICHBOOL_TEXT_EXPR(#d), e, RICHBOOL_TEXT_EXPR(#e), f, RICHBOOL_TEXT_EXPR(#f)),RICHBOOL_TEXT_EXPR(#c),c
#define rbv6_4_RB(a,b,c,d,e,f,functor) RichBool::MakeBind4Of6(functor, a, \
	RICHBOOL_TEXT_EXPR(#a), b, RICHBOOL_TEXT_EXPR(#b), c, RICHBOOL_TEXT_EXPR(#c), e, RICHBOOL_TEXT_EXPR(#e), f, RICHBOOL_TEXT_EXPR(#f)),RICHBOOL_TEXT_EXPR(#d),d
#define rbv6_5_RB(a,b,c,d,e,f,functor) RichBool::MakeBind5Of6(functor, a, \
	RICHBOOL_TEXT_EXPR(#a), b, RICHBOOL_TEXT_EXPR(#b), c, RICHBOOL_TEXT_EXPR(#c), d, RICHBOOL_TEXT_EXPR(#d), f, RICHBOOL_TEXT_EXPR(#f)),RICHBOOL_TEXT_EXPR(#e),e
#define rbv6_6_RB(a,b,c,d,e,f,functor) RichBool::MakeBind6Of6(functor, a, \
	RICHBOOL_TEXT_EXPR(#a), b, RICHBOOL_TEXT_EXPR(#b), c, RICHBOOL_TEXT_EXPR(#c), d, RICHBOOL_TEXT_EXPR(#d), e, RICHBOOL_TEXT_EXPR(#e)),RICHBOOL_TEXT_EXPR(#f),f

#endif // #ifndef RICH_BOOL_BASICS_H__QM
