//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "richbool/richbool.hpp"
#include "rbtest.hpp"
#include "predicates.hpp"

using namespace RichBool;

RB_TEST(OneArgument_Ok)
{
	Pred1<IsEven> rb;
	RB_ASSERT(rb.SafeCheck(12)==Analysis::Ok);
}

RB_TEST(OneArgument_Fail)
{
	Pred1<IsEven> rb;
	RB_ASSERT(rb.SafeCheck(11)==Analysis::NotOk);
}

RB_TEST(OneArgument_BadValue)
{
	Pred1<IsEven> rb;
	int *p=0;
	RB_ASSERT(rb.SafeCheck(*p)==Analysis::BadValue);
}

RB_TEST(TwoArguments_Ok)
{
	Pred2<ProductIs> rb(12);
	RB_ASSERT(rb.SafeCheck(3,4)==Analysis::Ok);
}

RB_TEST(TwoArguments_Fail)
{
	Pred2<ProductIs> rb(12);
	RB_ASSERT(rb.SafeCheck(3,5)==Analysis::NotOk);
}

RB_TEST(TwoArguments_BadValue)
{
	Pred2<ProductIs> rb(12);
	int *p=0;
	RB_ASSERT(rb.SafeCheck(*p,5)==Analysis::BadValue);
	RB_ASSERT(rb.SafeCheck(5,*p)==Analysis::BadValue);
}

RB_TEST(ThreeArguments_Ok)
{
	Pred3<ProductIs> rb(12);
	RB_ASSERT(rb.SafeCheck(3,2,2)==Analysis::Ok);
}

RB_TEST(ThreeArguments_Fail)
{
	Pred3<ProductIs> rb(12);
	RB_ASSERT(rb.SafeCheck(3,5,2)==Analysis::NotOk);
}

RB_TEST(ThreeArguments_BadValue)
{
	Pred3<ProductIs> rb(12);
	int *p=0;
	RB_ASSERT(rb.SafeCheck(*p,5,3)==Analysis::BadValue);
	RB_ASSERT(rb.SafeCheck(5,*p,3)==Analysis::BadValue);
	RB_ASSERT(rb.SafeCheck(5,3,*p)==Analysis::BadValue);
}

RB_TEST(FourArguments_Ok)
{
	Pred4<ProductIs> rb(12);
	RB_ASSERT(rb.SafeCheck(3,2,2,1)==Analysis::Ok);
}

RB_TEST(FourArguments_Fail)
{
	Pred4<ProductIs> rb(12);
	RB_ASSERT(rb.SafeCheck(3,5,2,1)==Analysis::NotOk);
}

RB_TEST(FourArguments_BadValue)
{
	Pred4<ProductIs> rb(12);
	int *p=0;
	RB_ASSERT(rb.SafeCheck(*p,5,3,1)==Analysis::BadValue);
	RB_ASSERT(rb.SafeCheck(5,*p,3,1)==Analysis::BadValue);
	RB_ASSERT(rb.SafeCheck(5,3,*p,1)==Analysis::BadValue);
	RB_ASSERT(rb.SafeCheck(5,3,1,*p)==Analysis::BadValue);
}

RB_TEST(FiveArguments_Ok)
{
	Pred5<ProductIs> rb(12);
	RB_ASSERT(rb.SafeCheck(3,2,2,1,1)==Analysis::Ok);
}

RB_TEST(FiveArguments_Fail)
{
	Pred5<ProductIs> rb(12);
	RB_ASSERT(rb.SafeCheck(3,5,2,1,1)==Analysis::NotOk);
}

RB_TEST(FiveArguments_BadValue)
{
	Pred5<ProductIs> rb(12);
	int *p=0;
	RB_ASSERT(rb.SafeCheck(*p,5,3,1,1)==Analysis::BadValue);
	RB_ASSERT(rb.SafeCheck(5,*p,3,1,1)==Analysis::BadValue);
	RB_ASSERT(rb.SafeCheck(5,3,*p,1,1)==Analysis::BadValue);
	RB_ASSERT(rb.SafeCheck(5,3,1,*p,1)==Analysis::BadValue);
	RB_ASSERT(rb.SafeCheck(5,3,1,1,*p)==Analysis::BadValue);
}
