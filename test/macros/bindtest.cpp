//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/richbool.hpp"
#include "composite_expressions.hpp"

using namespace RichBool;

RB_TEST(BindArg1Of2_Pass)
{
	BindArg1Of2<Less<>, int> rb(5);
	RB_PASS(rb1_RB(6, rb));
}

RB_TEST(BindArg1Of2_Fail)
{
	SharedAnalysis analysis = (Analysis*)MakeGeneralAnalysis(false)("5", true)(" < ")
		.expr("3", ":")("3", true);

	BindArg1Of2<Less<>, int> rb(5);
	RB_FAIL(rb1_RB(3, rb), *analysis);
}

RB_TEST(BindArg2Of2_Pass)
{
	BindArg2Of2<Less<>, int> rb(5);
	RB_PASS(rb1_RB(4, rb));
}

RB_TEST(BindArg2Of2_Fail)
{
	SharedAnalysis analysis = (Analysis*)MakeGeneralAnalysis(false).expr("6", ":")("6", true)
		(" < ")("5", true);

	BindArg2Of2<Less<>, int> rb(5);
	RB_FAIL(rb1_RB(6, rb), *analysis);
}

RB_TEST(BindArg1Of3_Pass)
{
	BindArg1Of3<InInterval<>, int> rb(5);
	RB_PASS(rb2_RB(4, 6, rb));
}

RB_TEST(BindArg1Of3_Fail)
{
	SharedAnalysis analysis = (Analysis*)MakeGeneralAnalysis(false)("5", true)(" in [")
		.expr("6", ":")("6", true)(", ").expr("8", ":")("8", true)("]");

	BindArg1Of3<InInterval<>, int> rb(5);
	RB_FAIL(rb2_RB(6, 8, rb), *analysis);
}

RB_TEST(BindArg2Of3_Pass)
{
	BindArg2Of3<InInterval<>, int> rb(2);
	RB_PASS(rb2_RB(4, 6, rb));
}

RB_TEST(BindArg2Of3_Fail)
{
	SharedAnalysis analysis = (Analysis*)MakeGeneralAnalysis(false).expr("3", ":")("3", true)
		(" in [")("5", true)(", ").expr("8", ":")("8", true)("]");

	BindArg2Of3<InInterval<>, int> rb(5);
	RB_FAIL(rb2_RB(3, 8, rb), *analysis);
}

RB_TEST(BindArg3Of3_Pass)
{
	BindArg3Of3<InInterval<>, int> rb(8);
	RB_PASS(rb2_RB(6, 4, rb));
}

RB_TEST(BindArg3Of3_Fail)
{
	SharedAnalysis analysis = (Analysis*)MakeGeneralAnalysis(false).expr("3", ":")("3", true)
		(" in [").expr("5", ":")("5", true)(", ")("8", true)("]");

	BindArg3Of3<InInterval<>, int> rb(8);
	RB_FAIL(rb2_RB(3, 5, rb), *analysis);
}



// nested binding

RB_TEST(Nested_Pass)
{
	BindArg3Of3<InInterval<>, int> below10(10);
	BindArg2Of2<BindArg3Of3<InInterval<>, int>, int>
		between5and10(below10, 5);

	RB_PASS(rb1_RB(7, between5and10));
}

RB_TEST(Nested_Fail)
{
	BindArg3Of3<InInterval<>, int> below10(10);
	BindArg2Of2<BindArg3Of3<InInterval<>, int>, int>
		between5and10(below10, 5);

	SharedAnalysis analysis = (Analysis*)MakeGeneralAnalysis(false).expr("2", ":")("2", true)
		(" in [")("5", true)(", ")("10", true)("]");
	RB_FAIL(rb1_RB(2, between5and10), *analysis);
}


// with pointers

#ifdef RICHBOOL_NO_PARTIAL_TEMPLATE_SPECIALIZATION
    typedef PointerLike<int> POINTER;
#else
    typedef Pointer<> POINTER;
#endif

RB_TEST(BindArg1Of2_Pointer_Pass)
{
	BindArg1Of2<Less<Value, POINTER>, int> rb(5);

	int n=6;
	RB_PASS(rb1_RB(&n, rb));
}

RB_TEST(BindArg1Of2_Pointer_Fail)
{
	SharedExpression pe = PrefixText("*", "&n");
	SharedAnalysis analysis = (Analysis*)MakeGeneralAnalysis(false)("5", true)(" < ").expr(pe, ":")("3", true);

	BindArg1Of2<Less<Value, POINTER>, int> rb(5);
	int n=3;
	RB_FAIL(rb1_RB(&n, rb), *analysis);
}

RB_TEST(BindArg2Of2_Pointer_Pass)
{
	BindArg2Of2<Less<POINTER, Value>, int> rb(5);
	int n=4;
	RB_PASS(rb1_RB(&n, rb));
}

RB_TEST(BindArg2Of2_Pointer_Fail)
{
	SharedExpression pe = PrefixText("*", "&n");
	SharedAnalysis analysis = (Analysis*)MakeGeneralAnalysis(false).
		expr(pe, ":")
		("6", true)(" < ")("5", true);

	BindArg2Of2<Less<POINTER, Value>, int> rb(5);
	int n=6;
	RB_FAIL(rb1_RB(&n, rb), *analysis);
}

RB_TEST(BindInRange)
{
	int array[] = { 1, 5, 9 };
	BindArg2Of2<Less<>, int> lessThan10(10);
	RB_PASS(rbIN_RANGE(array, array+3, All<>().Are(lessThan10)));
}

RB_TEST(BindInRanges)
{
	double arr1[] = { 1.0, 5.0, 9.0 }, arr2[] = { 0.999, 5.009, 9.005 };

	BindArg3Of3<Near<>, double> near_(0.01);
	RB_PASS(rbIN_RANGES(arr1, arr1+3, arr2, arr2+3,
		Compare<>().That(near_)));
}

RB_TEST(BindArg1Of2_Pass_WithTextExpression)
{
	BindArg1Of2<Less<>, int> rb(5, "5");
	RB_PASS(rb1_RB(6, rb));
}

RB_TEST(BindArg1Of2_Fail_WithTextExpression)
{
	SharedAnalysis analysis = (Analysis*)MakeGeneralAnalysis(false).expr("5", ":")("5", true)(" < ")
		.expr("3", ":")("3", true);

	BindArg1Of2<Less<>, int> rb(5, "5");
	RB_FAIL(rb1_RB(3, rb), *analysis);
}
