//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_H__QM
#define RICH_BOOL_H__QM

#include "richbool/bool.hpp"
#include "richbool/functors.hpp"
#include "richbool/logic.hpp"
#include "richbool/ranges.hpp"
#include "richbool/bind.hpp"
#include "richbool/relation.hpp"
#include "richbool/basic_rb.hpp"
#include "richbool/string.hpp"
#include "richbool/stdstring.hpp"
#include "richbool/values.hpp"


#define rbEQUAL(a,b) rb2_RB(a,b,RichBool::Equal<>())
#define rbvEQUAL(a,b) rbv2_1_RB(a,b,RichBool::Equal<>())

#define rbEQUAL_PTR(a,b) rb2_RB(a,b,RichBool::EqualPtr<>())
#define rbvEQUAL_PTR(a,b) rbv2_1_RB(a,b,RichBool::EqualPtr<>())

#define rbLESS(a,b) rb2_RB(a,b,RichBool::Less<>())
#define rbvLESS(a,b) rbv2_1_RB(a,b,RichBool::Less<>())

#define rbLESS_OR_EQUAL(a,b) rb2_RB(a,b,RichBool::LessOrEqual<>())
#define rbvLESS_OR_EQUAL(a,b) rbv2_1_RB(a,b,RichBool::LessOrEqual<>())

#define rbMORE(a,b) rb2_RB(a,b,RichBool::More<>())
#define rbvMORE(a,b) rbv2_1_RB(a,b,RichBool::More<>())

#define rbMORE_OR_EQUAL(a,b) rb2_RB(a,b,RichBool::MoreOrEqual<>())
#define rbvMORE_OR_EQUAL(a,b) rbv2_1_RB(a,b,RichBool::MoreOrEqual<>())

#define rbDIFF(a,b) rb2_RB(a,b,RichBool::Diff<>())
#define rbvDIFF(a,b) rbv2_1_RB(a,b,RichBool::Diff<>())

#define rbORDER_2(a, op, b) \
	rb2_RB(a, b, RichBool::MakeOrder2(RichBool::Dummy() op RichBool::Dummy()))
#define rbvORDER_2(a, op, b) \
	rbv2_1_RB(a, b, RichBool::MakeOrder2(RichBool::Dummy() op RichBool::Dummy()))

#define rbORDER_3(a, op1, b, op2, c) rb3_RB(a, b, c, \
	RichBool::MakeOrder3(RichBool::Dummy() op1 RichBool::Dummy(), RichBool::Dummy() op2 RichBool::Dummy()))
#define rbvORDER_3(a, op1, b, op2, c) rbv3_2_RB(a, b, c, \
	RichBool::MakeOrder3(RichBool::Dummy() op1 RichBool::Dummy(), RichBool::Dummy() op2 RichBool::Dummy()))

#define rbORDER_4(a, op1, b, op2, c, op3, d) rb4_RB(a, b, c, d, \
	RichBool::MakeOrder4(RichBool::Dummy() op1 RichBool::Dummy(), \
	RichBool::Dummy() op2 RichBool::Dummy(), RichBool::Dummy() op3 RichBool::Dummy()))
#define rbvORDER_4(a, op1, b, op2, c, op3, d) rbv4_2_RB(a, b, c, d, \
	RichBool::MakeOrder4(RichBool::Dummy() op1 RichBool::Dummy(), \
	RichBool::Dummy() op2 RichBool::Dummy(), RichBool::Dummy() op3 RichBool::Dummy()))

#define rbIN_INTERVAL(a,b,c) rb3_RB(a,b,c,RichBool::InInterval<>())
#define rbvIN_INTERVAL(a,b,c) rbv3_1_RB(a,b,c,RichBool::InInterval<>())

#define rbIN_OPEN_INTERVAL(a,b,c) rb3_RB(a,b,c,RichBool::InOpenInterval<>())
#define rbvIN_OPEN_INTERVAL(a,b,c) rbv3_1_RB(a,b,c,RichBool::InOpenInterval<>())

#define rbLESS_NEAR(a,b,e) rb3_RB(a,b,e,RichBool::LessNear<>())
#define rbvLESS_NEAR(a,b,e) rbv3_1_RB(a,b,e,RichBool::LessNear<>())

#define rbMORE_NEAR(a,b,e) rb3_RB(a,b,e,RichBool::MoreNear<>())
#define rbvMORE_NEAR(a,b,e) rbv3_1_RB(a,b,e,RichBool::MoreNear<>())

#define rbDIFF_NEAR(a,b,e) rb3_RB(a,b,e,RichBool::DiffNear<>())
#define rbvDIFF_NEAR(a,b,e) rbv3_1_RB(a,b,e,RichBool::DiffNear<>())

#define rbORDER_2_NEAR(a, op, b, e) \
	rb3_RB(a, b, e, RichBool::MakeOrder2Near(RichBool::DummyNear() op RichBool::DummyNear()))
#define rbvORDER_2_NEAR(a, op, b, e) \
	rbv3_1_RB(a, b, e, RichBool::MakeOrder2Near(RichBool::DummyNear() op RichBool::DummyNear()))

#define rbORDER_3_NEAR(a, op1, b, op2, c, e) rb4_RB(a, b, c, e, \
	RichBool::MakeOrder3Near(RichBool::DummyNear() op1 RichBool::DummyNear(), RichBool::DummyNear() op2 RichBool::DummyNear()))
#define rbvORDER_3_NEAR(a, op1, b, op2, c, e) rbv4_2_RB(a, b, c, e, \
	RichBool::MakeOrder3Near(RichBool::DummyNear() op1 RichBool::DummyNear(), RichBool::DummyNear() op2 RichBool::DummyNear()))

#define rbORDER_4_NEAR(a, op1, b, op2, c, op3, d, e) rb5_RB(a, b, c, d, e, \
	RichBool::MakeOrder4Near(RichBool::DummyNear() op1 RichBool::DummyNear(), \
	RichBool::DummyNear() op2 RichBool::DummyNear(), RichBool::DummyNear() op3 RichBool::DummyNear()))
#define rbvORDER_4_NEAR(a, op1, b, op2, c, op3, d, e) rbv5_2_RB(a, b, c, d, e, \
	RichBool::MakeOrder4Near(RichBool::DummyNear() op1 RichBool::DummyNear(), \
	RichBool::DummyNear() op2 RichBool::DummyNear(), RichBool::DummyNear() op3 RichBool::DummyNear()))

#define rbIN_INTERVAL_NEAR(a,b,c,e) rb4_RB(a,b,c,e,RichBool::InIntervalNear<>())
#define rbvIN_INTERVAL_NEAR(a,b,c,e) rbv4_1_RB(a,b,c,e,RichBool::InIntervalNear<>())

#define rbLESS_REL_NEAR(a,b,e) rb3_RB(a,b,e,RichBool::LessRelativeNear<>())
#define rbvLESS_REL_NEAR(a,b,e) rbv3_1_RB(a,b,e,RichBool::LessRelativeNear<>())

#define rbMORE_REL_NEAR(a,b,e) rb3_RB(a,b,e,RichBool::MoreRelativeNear<>())
#define rbvMORE_REL_NEAR(a,b,e) rbv3_1_RB(a,b,e,RichBool::MoreRelativeNear<>())

#define rbDIFF_REL_NEAR(a,b,e) rb3_RB(a,b,e,RichBool::DiffRelativeNear<>())
#define rbvDIFF_REL_NEAR(a,b,e) rbv3_1_RB(a,b,e,RichBool::DiffRelativeNear<>())

#define rbORDER_2_REL_NEAR(a, op, b, e) \
	rb3_RB(a, b, e, RichBool::MakeOrder2RelativeNear(RichBool::DummyRelNear() op RichBool::DummyRelNear()))
#define rbvORDER_2_REL_NEAR(a, op, b, e) \
	rbv3_1_RB(a, b, e, RichBool::MakeOrder2RelativeNear(RichBool::DummyRelNear() op RichBool::DummyRelNear()))

#define rbORDER_3_REL_NEAR(a, op1, b, op2, c, e) rb4_RB(a, b, c, e, \
	RichBool::MakeOrder3RelativeNear(RichBool::DummyRelNear() op1 RichBool::DummyRelNear(), RichBool::DummyRelNear() op2 RichBool::DummyRelNear()))
#define rbvORDER_3_REL_NEAR(a, op1, b, op2, c, e) rbv4_2_RB(a, b, c, e, \
	RichBool::MakeOrder3RelativeNear(RichBool::DummyRelNear() op1 RichBool::DummyRelNear(), RichBool::DummyRelNear() op2 RichBool::DummyRelNear()))

#define rbORDER_4_REL_NEAR(a, op1, b, op2, c, op3, d, e) rb5_RB(a, b, c, d, e, \
	RichBool::MakeOrder4RelativeNear(RichBool::DummyRelNear() op1 RichBool::DummyRelNear(), \
	RichBool::DummyRelNear() op2 RichBool::DummyRelNear(), RichBool::DummyRelNear() op3 RichBool::DummyRelNear()))
#define rbvORDER_4_REL_NEAR(a, op1, b, op2, c, op3, d, e) rbv5_2_RB(a, b, c, d, e, \
	RichBool::MakeOrder4RelativeNear(RichBool::DummyRelNear() op1 RichBool::DummyRelNear(), \
	RichBool::DummyRelNear() op2 RichBool::DummyRelNear(), RichBool::DummyRelNear() op3 RichBool::DummyRelNear()))

#define rbIN_INTERVAL_REL_NEAR(a,b,c,e) rb4_RB(a,b,c,e,RichBool::InIntervalRelativeNear<>())
#define rbvIN_INTERVAL_REL_NEAR(a,b,c,e) rbv4_1_RB(a,b,c,e,RichBool::InIntervalRelativeNear<>())

#define rbEQUAL_USING_LESS(a,b) rb2_RB(a,b,RichBool::EqualUsingLess<>())
#define rbEQUAL_USING_MORE(a,b) rb2_RB(a,b,RichBool::EqualUsingMore<>())

#define rbEQUAL_BITWISE(bits1,bits2) rb2_RB(bits1,bits2,RichBool::EqualBitwise<>())
#define rbvEQUAL_BITWISE(bits1,bits2) rbv2_1_RB(bits1,bits2,RichBool::EqualBitwise<>())

#define rbBITS_OFF(bits,mask) rb2_RB(bits,mask,RichBool::BitsOff<>())
#define rbvBITS_OFF(bits,mask) rbv2_1_RB(bits,mask,RichBool::BitsOff<>())

#define rbBITS_ON(bits,mask)  rb2_RB(bits,mask,RichBool::BitsOn<>())
#define rbvBITS_ON(bits,mask)  rbv2_1_RB(bits,mask,RichBool::BitsOn<>())

#define rbBITS_ARE(bits,mask)  rb2_RB(bits,mask,RichBool::BitsAre<>())
#define rbvBITS_ARE(bits,mask)  rbv2_1_RB(bits,mask,RichBool::BitsAre<>())

#define rbEQUAL_DATA(data1, data2, size) rb3_RB(data1,data2,size,RichBool::EqualData<>())
#define rbvEQUAL_DATA(data1, data2, size) rbv3_1_RB(data1,data2,size,RichBool::EqualData<>())

#define rbEQUAL_DATA_BITWISE(data1, data2, size) \
	rb3_RB(data1,data2,size,RichBool::EqualDataBitwise<>())
#define rbvEQUAL_DATA_BITWISE(data1, data2, size) \
	rbv3_1_RB(data1,data2,size,RichBool::EqualDataBitwise<>())

#define rbNEAR(a,b,c) rb3_RB(a,b,c,RichBool::Near<>())
#define rbvNEAR(a,b,c) rbv3_1_RB(a,b,c,RichBool::Near<>())

#define rbREL_NEAR(a,b,c) rb3_RB(a,b,c,RichBool::RelNear<>())
#define rbvREL_NEAR(a,b,c) rbv3_1_RB(a,b,c,RichBool::RelNear<>())

#define rbEQUAL_TYPES(a, b) rb2_RB(a,b,RichBool::EqualTypesPointers())
#define rbvEQUAL_TYPES(a, b) rbv2_1_RB(a,b,RichBool::EqualTypesPointers())

#define rbHAS_TYPE(a, type) rb1_RB(a,RichBool::MakeHasTypePtr((const type*)0, #type))
#define rbvHAS_TYPE(a, type) rbv1_1_RB(a,RichBool::MakeHasTypePtr((const type*)0, #type))

#define rbDYNAMIC_CASTABLE_PTR(a, type) \
	rb1_RB(a,RichBool::DynamicCastablePointer<type>(#type))
#define rbvDYNAMIC_CASTABLE_PTR(a, type) \
	rbv1_1_RB(a,RichBool::DynamicCastablePointer<type>(#type))

#define rbDYNAMIC_CASTABLE_REF(a, type) \
	rb1_RB(a,RichBool::DynamicCastableReference<type>(#type))
#define rbvDYNAMIC_CASTABLE_REF(a, type) \
	rbv1_1_RB(a,RichBool::DynamicCastableReference<type>(#type))

#ifndef RICHBOOL_NO_PARTIAL_TEMPLATE_SPECIALIZATION
#define rbDYNAMIC_CASTABLE(a, type) \
	rb1_RB(a,RichBool::DynamicCastable<type>(#type))
#define rbvDYNAMIC_CASTABLE(a, type) \
	rbv1_1_RB(a,RichBool::DynamicCastable<type>(#type))
#endif

#define rb1_PRED(a,pred) \
	rb1_RB(a, \
		RichBool::PredToRichBool_1Arg(pred, RichBool::Value(), RichBool::MakeString()))
#define rbv1_PRED(a,pred) \
	rbv1_1_RB(a, \
		RichBool::PredToRichBool_1Arg(pred, RichBool::Value(), RichBool::MakeString()))

#define rb2_PRED(a,b,pred) \
	rb2_RB(a,b, \
		RichBool::PredToRichBool_2Arg(pred, \
			RichBool::Value(), RichBool::Value(),\
			RichBool::MakeString(), RichBool::MakeString()))
#define rbv2_PRED(a,b,pred) \
	rbv2_1_RB(a,b, \
		RichBool::PredToRichBool_2Arg(pred, \
			RichBool::Value(), RichBool::Value(),\
			RichBool::MakeString(), RichBool::MakeString()))

#define rb3_PRED(a,b,c,pred) \
	rb3_RB(a,b,c, \
		RichBool::PredToRichBool_3Arg(pred, \
			RichBool::Value(), RichBool::Value(), RichBool::Value(), \
			RichBool::MakeString(), RichBool::MakeString(), RichBool::MakeString()))
#define rbv3_PRED(a,b,c,pred) \
	rbv3_1_RB(a,b,c, \
		RichBool::PredToRichBool_3Arg(pred, \
			RichBool::Value(), RichBool::Value(), RichBool::Value(), \
			RichBool::MakeString(), RichBool::MakeString(), RichBool::MakeString()))

#define rb4_PRED(a,b,c,d,pred) \
	rb4_RB(a,b,c,d, \
		RichBool::PredToRichBool_4Arg(pred, \
			RichBool::Value(), RichBool::Value(), RichBool::Value(), RichBool::Value(), \
			RichBool::MakeString(), RichBool::MakeString(), RichBool::MakeString(), \
			RichBool::MakeString()))
#define rbv4_PRED(a,b,c,d,pred) \
	rbv4_1_RB(a,b,c,d, \
		RichBool::PredToRichBool_4Arg(pred, \
			RichBool::Value(), RichBool::Value(), RichBool::Value(), RichBool::Value(), \
			RichBool::MakeString(), RichBool::MakeString(), RichBool::MakeString(), \
			RichBool::MakeString()))

#define rb5_PRED(a,b,c,d,e,pred) \
	rb5_RB(a,b,c,d,e, \
		RichBool::PredToRichBool_5Arg(pred, \
			RichBool::Value(), RichBool::Value(), RichBool::Value(), RichBool::Value(), RichBool::Value(), \
			RichBool::MakeString(), RichBool::MakeString(), RichBool::MakeString(), \
			RichBool::MakeString(), RichBool::MakeString()))
#define rbv5_PRED(a,b,c,d,e,pred) \
	rbv5_1_RB(a,b,c,d,e, \
		RichBool::PredToRichBool_5Arg(pred, \
			RichBool::Value(), RichBool::Value(), RichBool::Value(), RichBool::Value(), RichBool::Value(), \
			RichBool::MakeString(), RichBool::MakeString(), RichBool::MakeString(), \
			RichBool::MakeString(), RichBool::MakeString()))

#define rb6_PRED(a,b,c,d,e,f,pred) \
	rb6_RB(a,b,c,d,e,f, \
		RichBool::PredToRichBool_6Arg(pred, \
			RichBool::Value(), RichBool::Value(), RichBool::Value(), \
			RichBool::Value(), RichBool::Value(), RichBool::Value(), \
			RichBool::MakeString(), RichBool::MakeString(), RichBool::MakeString(), \
			RichBool::MakeString(), RichBool::MakeString(), RichBool::MakeString()))
#define rbv6_PRED(a,b,c,d,e,f,pred) \
	rbv6_1_RB(a,b,c,d,e,f, \
		RichBool::PredToRichBool_6Arg(pred, \
			RichBool::Value(), RichBool::Value(), RichBool::Value(), \
			RichBool::Value(), RichBool::Value(), RichBool::Value(), \
			RichBool::MakeString(), RichBool::MakeString(), RichBool::MakeString(), \
			RichBool::MakeString(), RichBool::MakeString(), RichBool::MakeString()))



#define rbSTRING(str1, op, str2, comp) \
	rb2_RB(str1, str2, \
	RichBool::MakeCompareStrings(comp, RichBool::Dummy() op RichBool::Dummy()))
#define rbvSTRING(str1, op, str2, comp) \
	rbv2_1_RB(str1, str2, \
	RichBool::MakeCompareStrings(comp, RichBool::Dummy() op RichBool::Dummy()))

#define rbSTRING_CS(str1, op, str2) rbSTRING(str1, op, str2, RichBool::detail::GetStringCompare(str1))
#define rbvSTRING_CS(str1, op, str2) rbvSTRING(str1, op, str2, RichBool::detail::GetStringCompare(str1))

#define rbSTRING_CI(str1, op, str2) rbSTRING(str1, op, str2, RichBool::detail::GetStringCompareToUpper(str1))
#define rbvSTRING_CI(str1, op, str2) rbvSTRING(str1, op, str2, RichBool::detail::GetStringCompareToUpper(str1))

#define rbSTRCMP(str1, op, str2) \
	rb2_RB(str1, str2, \
	RichBool::MakeCompareStrings(RichBool::Strcmp(), RichBool::Dummy() op RichBool::Dummy()))
#define rbvSTRCMP(str1, op, str2) \
	rbv2_1_RB(str1, str2, \
	RichBool::MakeCompareStrings(RichBool::Strcmp(), RichBool::Dummy() op RichBool::Dummy()))

#define rbWCSCMP(str1, op, str2) \
	rb2_RB(str1, str2, \
	RichBool::MakeCompareStrings(RichBool::Wcscmp(), RichBool::Dummy() op RichBool::Dummy()))
#define rbvWCSCMP(str1, op, str2) \
	rbv2_1_RB(str1, str2, \
	RichBool::MakeCompareStrings(RichBool::Wcscmp(), RichBool::Dummy() op RichBool::Dummy()))


#define rbSTRING_BEGINS_WITH(str1, str2, comp) \
	rb2_RB(str1, str2, RichBool::MakeStringBeginsWith(comp))
#define rbvSTRING_BEGINS_WITH(str1, str2, comp) \
	rbv2_1_RB(str1, str2, RichBool::MakeStringBeginsWith(comp))

#define rbSTRING_BEGINS_WITH_CS(str1, str2) rbSTRING_BEGINS_WITH(str1, str2, RichBool::detail::GetStringCompare(str1))
#define rbvSTRING_BEGINS_WITH_CS(str1, str2) rbvSTRING_BEGINS_WITH(str1, str2, RichBool::detail::GetStringCompare(str1))

#define rbSTRING_BEGINS_WITH_CI(str1, str2) rbSTRING_BEGINS_WITH(str1, str2, RichBool::detail::GetStringCompareToUpper(str1))
#define rbvSTRING_BEGINS_WITH_CI(str1, str2) rbvSTRING_BEGINS_WITH(str1, str2, RichBool::detail::GetStringCompareToUpper(str1))

#define rbSTRING_ENDS_WITH(str1, str2, comp) \
	rb2_RB(str1, str2, RichBool::MakeStringEndsWith(comp))
#define rbvSTRING_ENDS_WITH(str1, str2, comp) \
	rbv2_1_RB(str1, str2, RichBool::MakeStringEndsWith(comp))

#define rbSTRING_ENDS_WITH_CS(str1, str2) rbSTRING_ENDS_WITH(str1, str2, RichBool::detail::GetStringCompare(str1))
#define rbvSTRING_ENDS_WITH_CS(str1, str2) rbvSTRING_ENDS_WITH(str1, str2, RichBool::detail::GetStringCompare(str1))

#define rbSTRING_ENDS_WITH_CI(str1, str2) rbSTRING_ENDS_WITH(str1, str2, RichBool::detail::GetStringCompareToUpper(str1))
#define rbvSTRING_ENDS_WITH_CI(str1, str2) rbvSTRING_ENDS_WITH(str1, str2, RichBool::detail::GetStringCompareToUpper(str1))

#define rbSTRING_CONTAINS(str1, str2, comp) \
	rb2_RB(str1, str2, RichBool::MakeStringContains(comp))
#define rbvSTRING_CONTAINS(str1, str2, comp) \
	rb2_RB(str1, str2, RichBool::MakeStringContains(comp))

#define rbSTRING_CONTAINS_CS(str1, str2) rbSTRING_CONTAINS(str1, str2, RichBool::detail::GetStringCompare(str1))
#define rbvSTRING_CONTAINS_CS(str1, str2) rbvSTRING_CONTAINS(str1, str2, RichBool::detail::GetStringCompare(str1))

#define rbSTRING_CONTAINS_CI(str1, str2) rbSTRING_CONTAINS(str1, str2, RichBool::detail::GetStringCompareToUpper(str1))
#define rbvSTRING_CONTAINS_CI(str1, str2) rbvSTRING_CONTAINS(str1, str2, RichBool::detail::GetStringCompareToUpper(str1))


#define rbIN_RANGE(b, e, algorithm) \
	rb2_RB(b,e, algorithm)
#define rbvIN_RANGE(b, e, algorithm) \
	rbv2_1_RB(b,e, algorithm)

#define rbIN_RANGES(b1, e1, b2, e2, algorithm) \
	rb4_RB(b1, e1, b2, e2, algorithm)
#define rbvIN_RANGES(b1, e1, b2, e2, algorithm) \
	rbv4_1_RB(b1, e1, b2, e2, algorithm)

#define RICHBOOL_ARRAY_COUNT(x) ( \
0 * sizeof( reinterpret_cast<const RichBool::MustBeArray*>(x) ) + \
0 * sizeof( RichBool::MustBeArray::check_type((x), &(x)) ) + \
sizeof(x) / sizeof((x)[0]) )

namespace RichBool
{
	class MustBeArray
	{
	public:
	class Is_pointer; // intentionally incomplete type
	class Is_array {};
	template<typename T>
	static Is_pointer check_type(const T*, const T* const*);
	static Is_array check_type(const void*, const void*);
	};
}

#define rbIN_RANGE_ARRAY(b, e, arr, algorithm) \
	rb4_RB(b, e, arr, RICHBOOL_ARRAY_COUNT(arr), algorithm)
#define rbvIN_RANGE_ARRAY(b, e, arr, algorithm) \
	rbv4_1_RB(b, e, arr, RICHBOOL_ARRAY_COUNT(arr), algorithm)
#define rbIN_ARRAY_RANGE(arr, b, e, algorithm) \
	rb4_RB(arr, RICHBOOL_ARRAY_COUNT(arr), b, e, algorithm)
#define rbvIN_ARRAY_RANGE(arr, b, e, algorithm) \
	rbv4_1_RB(arr, RICHBOOL_ARRAY_COUNT(arr), b, e, algorithm)

#define rbIN_ARRAY(arr, algorithm) \
	rb2_RB(arr, RICHBOOL_ARRAY_COUNT(arr), algorithm)
#define rbvIN_ARRAY(arr, algorithm) \
	rbv2_1_RB(arr, RICHBOOL_ARRAY_COUNT(arr), algorithm)

#define rbIN_ARRAYS(arr1, arr2, algorithm) \
	rb4_RB_IMPL(arr1, #arr1, RICHBOOL_ARRAY_COUNT(arr1), (const char*)NULL, \
		arr2, #arr2, RICHBOOL_ARRAY_COUNT(arr2), (const char*)NULL, \
		algorithm)
#define rbvIN_ARRAYS(arr1, arr2, algorithm) \
	rbv4_1_RB_IMPL(arr1, #arr1, RICHBOOL_ARRAY_COUNT(arr1), (const char*)NULL, \
		arr2, #arr2, RICHBOOL_ARRAY_COUNT(arr2), (const char*)NULL, \
		algorithm)



#define rbOR(cond1, cond2) \
	( richbool_level>=2 ? (\
		richbool_level==3 ? \
		((richbool_tmp1 = cond1), \
		RichBool::Bool(new RichBool::OrAnalysis(richbool_tmp1, richbool_tmp1() ? new RichBool::AnalysisNotEvaluated : \
		RichBool::Bool(cond2)))) : \
		((richbool_tmp1 = cond1), richbool_tmp1() ? RichBool::Bool(true) : \
		((richbool_tmp2 = cond2), richbool_tmp2() ? RichBool::Bool(true) : \
		RichBool::Bool(new RichBool::OrAnalysis(richbool_tmp1, richbool_tmp2))))) : \
		RichBool::Bool( richbool_level==1 ? ( (richbool_tmp1 = cond1), \
		(richbool_tmp1() ? true : ((richbool_tmp2 = cond2), richbool_tmp2()) )) : \
		(++richbool_level, (richbool_tmp1 = cond1), --richbool_level, (!richbool_tmp1() ? (richbool_tmp2 = cond2) : true), true) ) )

#define rbOR_BE(cond1, cond2) RichBool::OrBothEvaluated(cond1, cond2, richbool_level)

#define rbOR_DE(cond1, cond2) \
	( richbool_level>=2 ? ( \
		richbool_level==3 ? \
		(new RichBool::OrAnalysis(cond1, RichBool::TmpBool(cond1)() ? new RichBool::AnalysisNotEvaluated : RichBool::Bool(cond2))) : \
		(RichBool::TmpBool(cond1)() ? RichBool::TmpBool(true) : \
		(RichBool::TmpBool(cond2)() ? RichBool::TmpBool(true) : \
		RichBool::TmpBool(new RichBool::OrAnalysis(cond1, cond2)))) ) : \
		(richbool_level==1 ? \
		RichBool::TmpBool(RichBool::TmpBool(cond1)() ? true : RichBool::TmpBool(cond2)()) :\
		(++richbool_level, (richbool_tmp1 = cond1), --richbool_level, (!richbool_tmp1() ? (richbool_tmp2 = cond2) : true), true) ) )

#define rbAND(cond1, cond2) \
	( richbool_level>=2 ? ( \
		richbool_level==3 ? (\
	(richbool_tmp1 = cond1),  \
	RichBool::Bool(new RichBool::AndAnalysis(richbool_tmp1, !richbool_tmp1() ? \
		new RichBool::AnalysisNotEvaluated : RichBool::Bool(cond2)))) : \
	((richbool_tmp1 = cond1), !richbool_tmp1() ? \
		RichBool::Bool(new RichBool::AndAnalysis(richbool_tmp1, new RichBool::AnalysisNotEvaluated)) : \
		(richbool_tmp2 = cond2, richbool_tmp2() ? RichBool::Bool(true) : \
		RichBool::Bool(new RichBool::AndAnalysis(richbool_tmp1, cond2))))) : \
		( richbool_level==1 ? (RichBool::Bool( ((richbool_tmp1 = cond1), \
		(richbool_tmp1() ? ((richbool_tmp2 = cond2), richbool_tmp2()) : false))) ) : \
		(++richbool_level, (richbool_tmp1 = cond1), --richbool_level, (richbool_tmp1() ? (richbool_tmp2 = cond2) : true), true) ) )

#define rbAND_BE(cond1, cond2) RichBool::AndBothEvaluated(cond1, cond2, richbool_level)

#define rbAND_DE(cond1, cond2) \
	( richbool_level>=2 ? (\
		richbool_level==3 ? \
		(RichBool::TmpBool(new RichBool::AndAnalysis(cond1, !RichBool::TmpBool(cond1)() ? \
		new RichBool::AnalysisNotEvaluated : RichBool::Bool(cond2))) ) : \
		(!RichBool::TmpBool(cond1)() ? \
		RichBool::TmpBool(new RichBool::AndAnalysis(cond1, new RichBool::AnalysisNotEvaluated)) : \
		( RichBool::TmpBool(cond2)() ? RichBool::TmpBool(true) : \
		RichBool::TmpBool(new RichBool::AndAnalysis(cond1, cond2))))) : \
		( richbool_level==1 ? \
		RichBool::TmpBool(RichBool::TmpBool(cond1)() ? RichBool::TmpBool(cond2) : false ) :\
		(++richbool_level, (richbool_tmp1 = cond1), --richbool_level, (richbool_tmp1() ? (richbool_tmp2 = cond2) : true), true)) )

#define rbXOR(cond1, cond2) \
	( richbool_level>=2 ? \
		(richbool_level==2 ? \
		++richbool_level, RichBool::XorBothEvaluated(cond1, cond2, false).dec(richbool_level) : \
		RichBool::XorBothEvaluated(cond1, cond2, true)) : \
		( richbool_level==1 ? \
		RichBool::TmpBool(RichBool::XorBool(RichBool::TmpBool(cond1)(), RichBool::TmpBool(cond2)())) :\
		(cond1, cond2, RichBool::TmpBool(true)) ) )


#define rbFILE(file,ftor) rb1_RB(file,RichBool::MakeFile(ftor))
#define rbvFILE(file,ftor) rbv1_1_RB(file,RichBool::MakeFile(ftor))

#define rbFILE_EXISTS(file) rb1_RB(file,RichBool::FileExists<>())
#define rbvFILE_EXISTS(file) rbv1_1_RB(file,RichBool::FileExists<>())

#define rbDIRECTORY(directory,ftor) rb1_RB(directory,RichBool::MakeDirectory(ftor))
#define rbvDIRECTORY(directory,ftor) rbv1_1_RB(directory,RichBool::MakeDirectory(ftor))

#define rbDIRECTORY_EXISTS(dir) rb1_RB(dir,RichBool::DirectoryExists<>())
#define rbvDIRECTORY_EXISTS(dir) rbv1_1_RB(dir,RichBool::DirectoryExists<>())

#define rbDOES_NOT_EXIST(name) rb1_RB(name,RichBool::DoesNotExist<>())
#define rbvDOES_NOT_EXIST(name) rbv1_1_RB(name,RichBool::DoesNotExist<>())


// deprecated rich booleans:
#define rbIN_RANGE_ARG(b, e, algorithm, pred) \
	rb2_RB(b,e,((algorithm).Tie(pred)))
#define rbIN_RANGES_ARG(b1, e1, b2, e2, algorithm, pred) \
	rb4_RB(b1, e1, b2, e2, ((algorithm).Tie(pred)))
#define rbIN_RANGE_ARRAY_ARG(b, e, arr, algorithm, pred) \
	rb4_RB(b, e, arr, arr+RICHBOOL_ARRAY_COUNT(arr), ((algorithm).Tie(pred)))

#endif // #ifndef RICH_BOOL_H__QM
