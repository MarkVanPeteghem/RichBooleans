//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/richbool.hpp"
#include "testable_analysis_with_strings.hpp"
#include "testable_analysis_for_ranges.hpp"
#include "predicates.hpp"
#include <iostream>

using namespace RichBool;

#ifdef RICHBOOL_USE_WX
	#define STR_1_0 "1.000000"
	#define STR_2_0 "2.000000"
	#define STR_10_0 "10.000000"
	#define STR_0_1 "0.100000"
	#define STR_8_99 "8.990000"
	#define STR_0_899 "0.899000"
	#define STR_2_11 "2.110000"
	#define STR_0_101 "0.101000"
	#define STR_1_01 "1.010000"
	#define STR_1_099 "1.099000"
	#define STR_0_099 "0.099000"
#else
	#define STR_1_0 "1"
	#define STR_2_0 "2"
	#define STR_10_0 "10"
	#define STR_0_1 "0.1"
	#define STR_8_99 "8.99"
	#define STR_0_899 "0.899"
	#define STR_2_11 "2.11"
	#define STR_0_101 "0.101"
	#define STR_1_01 "1.01"
	#define STR_1_099 "1.099"
	#define STR_0_099 "0.099"
#endif

RB_TEST(Pass_Exact_Comparisons)
{
	int a=1, b=1, c=2;
	int *p=0;

	RB_PASS(rbEQUAL(a, b));
	RB_PASS_V(rbvEQUAL(a, b), a);
	RB_PASS(rbEQUAL_PTR(&a, &a));
	RB_PASS_VB(rbvEQUAL_PTR(&a, &a), &a);
	RB_PASS(rbEQUAL_PTR(p, p));
	RB_PASS_VB(rbvEQUAL_PTR(p, p), p);
	RB_PASS(rbLESS(a, c));
	RB_PASS_V(rbvLESS(a, c), a);
	RB_PASS(rbLESS_OR_EQUAL(a, b));
	RB_PASS_V(rbvLESS_OR_EQUAL(a, b), a);
	RB_PASS(rbLESS_OR_EQUAL(a, c));
	RB_PASS_V(rbvLESS_OR_EQUAL(a, c), a);
	RB_PASS(rbMORE(c, a));
	RB_PASS_V(rbvMORE(c, a), c);
	RB_PASS(rbMORE_OR_EQUAL(b, a));
	RB_PASS_V(rbvMORE_OR_EQUAL(b, a), b);
	RB_PASS(rbMORE_OR_EQUAL(c, a));
	RB_PASS_V(rbvMORE_OR_EQUAL(c, a), c);
	RB_PASS(rbIN_INTERVAL(a, 1, 5));
	RB_PASS_V(rbvIN_INTERVAL(a, 1, 5), a);
	RB_PASS(rbIN_INTERVAL(a, 0, 1));
	RB_PASS_V(rbvIN_INTERVAL(a, 0, 1), a);
	RB_PASS(rbIN_INTERVAL(b, a, c));
	RB_PASS_V(rbvIN_INTERVAL(b, a, c), b);
	RB_PASS(rbIN_INTERVAL(c, b, c));
	RB_PASS_V(rbvIN_INTERVAL(c, b, c), c);
	RB_PASS(rbIN_OPEN_INTERVAL(a, 0, 5));
	RB_PASS_V(rbvIN_OPEN_INTERVAL(a, 0, 5), a);
	RB_PASS(rbIN_OPEN_INTERVAL(a, 0, 2));
	RB_PASS_V(rbvIN_OPEN_INTERVAL(a, 0, 2), a);
	RB_PASS(rbDIFF(a, c));
	RB_PASS_V(rbvDIFF(a, c), a);

	RB_PASS(rbORDER_2(1, <, 2));
	RB_PASS_V(rbvORDER_2(1, <, 2), 1);
	RB_PASS(rbORDER_2(1, <=, 2));
	RB_PASS_V(rbvORDER_2(1, <=, 2), 1);
	RB_PASS(rbORDER_2(1, <=, 1));
	RB_PASS_V(rbvORDER_2(1, <=, 1), 1);
	RB_PASS(rbORDER_2(1, >, 0));
	RB_PASS_V(rbvORDER_2(1, >, 0), 1);

	RB_PASS(rbORDER_3(1, <, 2, <, 3));
	RB_PASS_V(rbvORDER_3(1, <, 2, <, 3), 2);
	RB_PASS(rbORDER_3(1, <=, 1, <=, 1));
	RB_PASS_V(rbvORDER_3(1, <=, 1, <=, 1), 1);
	RB_PASS(rbORDER_3(1, <, 2, >, 0));
	RB_PASS_V(rbvORDER_3(1, <, 2, >, 0), 2);
	RB_PASS(rbORDER_3(1, >, 0, <, 2));
	RB_PASS_V(rbvORDER_3(1, >, 0, <, 2), 0);

	RB_PASS(rbORDER_4(1, <, 2, <, 3, <, 4));
	RB_PASS_V(rbvORDER_4(1, <, 2, <, 3, <, 4), 2);
	RB_PASS(rbORDER_4(1, <=, 1, <=, 1, <=, 1));
	RB_PASS_V(rbvORDER_4(1, <=, 1, <=, 1, <=, 1), 1);
	RB_PASS(rbORDER_4(1, <, 2, >, 0, <, 4));
	RB_PASS_V(rbvORDER_4(1, <, 2, >, 0, <, 4), 2);
	RB_PASS(rbORDER_4(3, >, 2, <, 5, >, 1));
	RB_PASS_V(rbvORDER_4(3, >, 2, <, 5, >, 1), 2);
}

RB_TEST(Pass_Near_Comparisons)
{
	RB_PASS(rbNEAR(1.0, 2.0, 2.0));
	RB_PASS_V(rbvNEAR(1.0, 2.0, 2.0), 1.0);
	RB_PASS(rbLESS_NEAR(1.05, 1.0, 0.1));
	RB_PASS_V(rbvLESS_NEAR(1.05, 1.0, 0.1), 1.05);
	RB_PASS(rbMORE_NEAR(1.0, 1.05, 0.1));
	RB_PASS_V(rbvMORE_NEAR(1.0, 1.05, 0.1), 1.0);

	RB_PASS(rbIN_INTERVAL_NEAR(2, 1, 5, 0.5));
	RB_PASS_V(rbvIN_INTERVAL_NEAR(2, 1, 5, 0.5), 2);
	RB_PASS(rbIN_INTERVAL_NEAR(1.05, 0, 1, 0.1));
	RB_PASS_V(rbvIN_INTERVAL_NEAR(1.05, 0, 1, 0.1), 1.05);
	RB_PASS(rbIN_INTERVAL_NEAR(0.95, 1.0, 2.0, 0.1));
	RB_PASS_V(rbvIN_INTERVAL_NEAR(0.95, 1.0, 2.0, 0.1), 0.95);
	RB_PASS(rbDIFF_NEAR(1.0, 1.2, 0.1));
	RB_PASS_V(rbvDIFF_NEAR(1.0, 1.2, 0.1), 1.0);

	RB_PASS(rbORDER_2_NEAR(1.0, <, 2.0, 0.1));
	RB_PASS_V(rbvORDER_2_NEAR(1.0, <, 2.0, 0.1), 1.0);
	RB_PASS(rbORDER_2_NEAR(1.0, <=, 2.0, 0.1));
	RB_PASS_V(rbvORDER_2_NEAR(1.0, <=, 2.0, 0.1), 1.0);
	RB_PASS(rbORDER_2_NEAR(1.05, <, 1.0, 0.1));
	RB_PASS_V(rbvORDER_2_NEAR(1.05, <, 1.0, 0.1), 1.05);
	RB_PASS(rbORDER_2_NEAR(1.05, <=, 1.0, 0.1));
	RB_PASS_V(rbvORDER_2_NEAR(1.05, <=, 1.0, 0.1), 1.05);

	RB_PASS(rbORDER_3_NEAR(1, <, 2, <, 3, 0.1));
	RB_PASS_V(rbvORDER_3_NEAR(1, <, 2, <, 3, 0.1), 2);
	RB_PASS(rbORDER_3_NEAR(1.1, <, 1.05, <, 1.0, 0.1));
	RB_PASS_V(rbvORDER_3_NEAR(1.1, <, 1.05, <, 1.0, 0.1), 1.05);
	RB_PASS(rbORDER_3_NEAR(1.05, <, 1.0, >, 1.05, 0.1));
	RB_PASS_V(rbvORDER_3_NEAR(1.05, <, 1.0, >, 1.05, 0.1), 1.0);

	RB_PASS(rbORDER_4_NEAR(1, <, 2, <, 3, <, 4, 0.9));
	RB_PASS_V(rbvORDER_4_NEAR(1, <, 2, <, 3, <, 4, 0.9), 2);
	RB_PASS(rbORDER_4_NEAR(1, <=, 1, <=, 1, <=, 1, 0.9));
	RB_PASS_V(rbvORDER_4_NEAR(1, <=, 1, <=, 1, <=, 1, 0.9), 1);
	RB_PASS(rbORDER_4_NEAR(1.05, <, 1.0, >, 1.05, <, 1.0, 0.1));
	RB_PASS_V(rbvORDER_4_NEAR(1.05, <, 1.0, >, 1.05, <, 1.0, 0.1), 1.0);
}

RB_TEST(Pass_Relative_Near_Comparisons)
{
	RB_PASS(rbREL_NEAR(10.0, 11.0, 0.11));
	RB_PASS_V(rbvREL_NEAR(10.0, 11.0, 0.11), 10.0);
	RB_PASS(rbLESS_REL_NEAR(11.0, 10.0, 0.1));
	RB_PASS_V(rbvLESS_REL_NEAR(11.0, 10.0, 0.1), 11.0);
	RB_PASS(rbMORE_REL_NEAR(10.0, 11.0, 0.1));
	RB_PASS_V(rbvMORE_REL_NEAR(10.0, 11.0, 0.1), 10.0);

	RB_PASS(rbDIFF_REL_NEAR(1.0, 1.12, 0.1));
	RB_PASS_V(rbvDIFF_REL_NEAR(1.0, 1.12, 0.1), 1.0);

	RB_PASS(rbIN_INTERVAL_REL_NEAR(9.5, 9.0, 10.0, 0.1));
	RB_PASS_V(rbvIN_INTERVAL_REL_NEAR(9.5, 9.0, 10.0, 0.1), 9.5);
	RB_PASS(rbIN_INTERVAL_REL_NEAR(11.0, 9.0, 10.0, 0.1));
	RB_PASS_V(rbvIN_INTERVAL_REL_NEAR(11.0, 9.0, 10.0, 0.1), 11.0);
	RB_PASS(rbIN_INTERVAL_REL_NEAR(8.11, 9.0, 10.0, 0.1));
	RB_PASS_V(rbvIN_INTERVAL_REL_NEAR(8.11, 9.0, 10.0, 0.1), 8.11);

	RB_PASS(rbORDER_2_REL_NEAR(1.0, <, 1.05, 0.1));
	RB_PASS_V(rbvORDER_2_REL_NEAR(1.0, <, 1.05, 0.1), 1.0);
	RB_PASS(rbORDER_2_REL_NEAR(1.0, <=, 1.05, 0.1));
	RB_PASS_V(rbvORDER_2_REL_NEAR(1.0, <=, 1.05, 0.1), 1.0);

	RB_PASS(rbORDER_2_REL_NEAR(11.0, <, 10.0, 0.1));
	RB_PASS_V(rbvORDER_2_REL_NEAR(11.0, <, 10.0, 0.1), 11.0);
	RB_PASS(rbORDER_2_REL_NEAR(11.0, <=, 10.0, 0.1));
	RB_PASS_V(rbvORDER_2_REL_NEAR(11.0, <=, 10.0, 0.1), 11.0);

	RB_PASS(rbORDER_3_REL_NEAR(10.0, <, 11.0, <, 12.0, 0.1));
	RB_PASS_V(rbvORDER_3_REL_NEAR(10.0, <, 11.0, <, 12.0, 0.1), 11.0);
	RB_PASS(rbORDER_3_REL_NEAR(12.0, <, 11.0, <, 10.0, 0.1));
	RB_PASS_V(rbvORDER_3_REL_NEAR(12.0, <, 11.0, <, 10.0, 0.1), 11.0);
	RB_PASS(rbORDER_3_REL_NEAR(11.0, <, 10.0, >, 11.0, 0.1));
	RB_PASS_V(rbvORDER_3_REL_NEAR(11.0, <, 10.0, >, 11.0, 0.1), 10.0);

	RB_PASS(rbORDER_4_REL_NEAR(1.0, <, 2.0, <, 3., <, 4.0, 0.1));
	RB_PASS_V(rbvORDER_4_REL_NEAR(1.0, <, 2.0, <, 3.0, <, 4.0, 0.1), 2);
	RB_PASS(rbORDER_4_REL_NEAR(1.0, <=, 1.0, <=, 1.0, <=, 1.0, 0.1));
	RB_PASS_V(rbvORDER_4_REL_NEAR(1.0, <=, 1.0, <=, 1.0, <=, 1.0, 0.1), 1);
	RB_PASS(rbORDER_4_REL_NEAR(11.0, <, 10.0, >, 11.0, <, 12.0, 0.1));
	RB_PASS_V(rbvORDER_4_REL_NEAR(11.0, <, 10.0, >, 11.0, <, 12.0, 0.1), 10.0);
}

RB_TEST(Pass_Other)
{
	RB_PASS(rb1_PRED(4, IsEven()));
	RB_PASS_V(rbv1_PRED(4, IsEven()), 4);
 	RB_PASS(rb2_PRED(4, 3, ProductIs(12)));
	RB_PASS_V(rbv2_PRED(4, 3, ProductIs(12)), 4);
	RB_PASS(rb3_PRED(2, 3, 2, ProductIs(12)));
	RB_PASS_V(rbv3_PRED(2, 3, 2, ProductIs(12)), 2);
	RB_PASS(rb4_PRED(2, 3, 4, 5, ProductIs(120)));
	RB_PASS_V(rbv4_PRED(2, 3, 4, 5, ProductIs(120)), 2);
	RB_PASS(rb5_PRED(2, 3, 2, 2, 5, ProductIs(120)));
	RB_PASS_V(rbv5_PRED(2, 3, 2, 2, 5, ProductIs(120)), 2);
	RB_PASS(rb6_PRED(2, 3, 2, 2, 5, 1, ProductIs(120)));
	RB_PASS_V(rbv6_PRED(2, 3, 2, 2, 5, 1, ProductIs(120)), 2);

#ifdef RICHBOOL_LAMBDAS
    // not really necessary because lambdas act as functors
    // but I was just curious to test it
	RB_PASS(rb1_PRED(4, [](int x) { return x%2==0; } ));
	RB_PASS_V(rbv1_PRED(4, [](int x) { return x%2==0; } ), 4);
 	RB_PASS(rb2_PRED(4, 3, [](int x, int y) { return x*y==12; } ));
	RB_PASS_V(rbv2_PRED(4, 3, [](int x, int y) { return x*y==12; } ), 4);
#endif

	RB_PASS(rbEQUAL_BITWISE(12, 12));
	RB_PASS_V(rbvEQUAL_BITWISE(12, 12), 12);

	const char buf1[] = { '\x00', '\xab', '\x45', '\xff' };
	const char buf2[] = { '\x00', '\xab', '\x45', '\xff' };
	RB_PASS(rbEQUAL_DATA(buf1, buf2, 4));
	RB_PASS_V(rbvEQUAL_DATA(buf1, buf2, 4), buf1);
	RB_PASS(rbEQUAL_DATA(buf1, buf2, 0));
	RB_PASS_V(rbvEQUAL_DATA(buf1, buf2, 0), buf1);

	RB_PASS(rbEQUAL_DATA_BITWISE(buf1, buf2, 4));
	RB_PASS_V(rbvEQUAL_DATA_BITWISE(buf1, buf2, 4), buf1);
	RB_PASS(rbEQUAL_DATA_BITWISE(buf1, buf2, 0));
	RB_PASS_V(rbvEQUAL_DATA_BITWISE(buf1, buf2, 0), buf1);
}

RB_TEST(Fail_Exact_Comparisons)
{
	int a=1, b=2, c=2, *p=0;

	SharedAnalysis analysisEqual =
		(Analysis*)MakeGeneralAnalysis(false).expr("a", ":")("1", true)(" == ")
			.expr("b", ":")("2", true);
	RB_FAIL(rbEQUAL(a, b), *analysisEqual);
	RB_FAIL_V(rbvEQUAL(a, b), *analysisEqual, a);

	SharedAnalysis analysisEqualPtr1 =
		(Analysis*)MakeGeneralAnalysis(false)
			.expr("&a", ":")(PtrToString(&a)+" -> 1", true)(" == ")
			.expr("&b", ":")(PtrToString(&b)+" -> 2", true);
	RB_FAIL(rbEQUAL_PTR(&a, &b), *analysisEqualPtr1);
	RB_FAIL_VB(rbvEQUAL_PTR(&a, &b), *analysisEqualPtr1, &a);

	SharedAnalysis analysisEqualPtr2 =
		(Analysis*)MakeGeneralAnalysis(false)
			.expr("&b", ":")(PtrToString(&b)+" -> 2", true)(" == ")
			.expr("&c", ":")(PtrToString(&c)+" -> 2", true);
	RB_FAIL(rbEQUAL_PTR(&b, &c), *analysisEqualPtr2);
	RB_FAIL_VB(rbvEQUAL_PTR(&b, &c), *analysisEqualPtr2, &b);

	SharedAnalysis analysisEqualPtr3 =
		(Analysis*)MakeGeneralAnalysis(false)
			.expr("&a", ":")(PtrToString(&a)+" -> 1", true)(" == ")
			.expr("p", ":")(GetNullPtrString(), true);
	RB_FAIL(rbEQUAL_PTR(&a, p), *analysisEqualPtr3);
	RB_FAIL_VB(rbvEQUAL_PTR(&a, p), *analysisEqualPtr3, &a);

	SharedAnalysis analysisLess1 =
		(Analysis*)MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" < ")
			.expr("1", ":")("1", true);
	RB_FAIL(rbLESS(1, 1), *analysisLess1);
	RB_FAIL_V(rbvLESS(1, 1), *analysisLess1, 1);

	SharedAnalysis analysisLess2 =
		(Analysis*)MakeGeneralAnalysis(false).expr("2", ":")("2", true)(" < ")
			.expr("1", ":")("1", true);
	RB_FAIL(rbLESS(2, 1), *analysisLess2);
	RB_FAIL_V(rbvLESS(2, 1), *analysisLess2, 2);

	SharedAnalysis analysisLE =
		(Analysis*)MakeGeneralAnalysis(false).expr("2", ":")("2", true)(" <= ")
			.expr("1", ":")("1", true);
	RB_FAIL(rbLESS_OR_EQUAL(2, 1), *analysisLE);
	RB_FAIL_V(rbvLESS_OR_EQUAL(2, 1), *analysisLE, 2);

	SharedAnalysis analysisMore1 =
		(Analysis*)MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" > ")
			.expr("1", ":")("1", true);
	RB_FAIL(rbMORE(1, 1), *analysisMore1);
	RB_FAIL_V(rbvMORE(1, 1), *analysisMore1, 1);

	SharedAnalysis analysisMore2 =
		(Analysis*)MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" > ")
			.expr("2", ":")("2", true);
	RB_FAIL(rbMORE(1, 2), *analysisMore2);
	RB_FAIL_V(rbvMORE(1, 2), *analysisMore2, 1);

	SharedAnalysis analysisGE =
		(Analysis*)MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" >= ")
			.expr("2", ":")("2", true);
	RB_FAIL(rbMORE_OR_EQUAL(1, 2), *analysisGE);
	RB_FAIL_V(rbvMORE_OR_EQUAL(1, 2), *analysisGE, 1);

	SharedAnalysis analysisOrder2a =
		(Analysis*)MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" < ")
			.expr("0", ":")("0", true);
	RB_FAIL(rbORDER_2(1, <, 0), *analysisOrder2a);
	RB_FAIL_V(rbvORDER_2(1, <, 0), *analysisOrder2a, 1);

	SharedAnalysis analysisOrder2b =
		(Analysis*)MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" < ")
			.expr("1", ":")("1", true);
	RB_FAIL(rbORDER_2(1, <, 1), *analysisOrder2b);
	RB_FAIL_V(rbvORDER_2(1, <, 1), *analysisOrder2b, 1);

	SharedAnalysis analysisOrder2c =
		(Analysis*)MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" <= ")
			.expr("0", ":")("0", true);
	RB_FAIL(rbORDER_2(1, <=, 0), *analysisOrder2c);
	RB_FAIL_V(rbvORDER_2(1, <=, 0), *analysisOrder2c, 1);

	SharedAnalysis analysisOrder3a =
		(Analysis*)MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" < ")
			.expr("0", ":")("0", true)(" < ").expr("2", ":")("2", true);
	RB_FAIL(rbORDER_3(1, <, 0, <, 2), *analysisOrder3a);
	RB_FAIL_V(rbvORDER_3(1, <, 0, <, 2), *analysisOrder3a, 0);

	SharedAnalysis analysisOrder3b =
		(Analysis*)MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" < ")
			.expr("2", ":")("2", true)(" < ").expr("0", ":")("0", true);
	RB_FAIL(rbORDER_3(1, <, 2, <, 0), *analysisOrder3b);
	RB_FAIL_V(rbvORDER_3(1, <, 2, <, 0), *analysisOrder3b, 2);

	SharedAnalysis analysisOrder3c =
		(Analysis*)MakeGeneralAnalysis(false).expr("2", ":")("2", true)(" < ")
			.expr("1", ":")("1", true)(" > ").expr("0", ":")("0", true);
	RB_FAIL(rbORDER_3(2, <, 1, >, 0), *analysisOrder3c);
	RB_FAIL_V(rbvORDER_3(2, <, 1, >, 0), *analysisOrder3c, 1);

	SharedAnalysis analysisOrder4a =
		(Analysis*)MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" > ")
			.expr("2", ":")("2", true)(" < ").expr("3", ":")("3", true)(" < ")
			.expr("4", ":")("4", true);
	RB_FAIL(rbORDER_4(1, >, 2, <, 3, <, 4), *analysisOrder4a);
	RB_FAIL_V(rbvORDER_4(1, >, 2, <, 3, <, 4), *analysisOrder4a, 2);

	SharedAnalysis analysisOrder4b =
		(Analysis*)MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" < ")
			.expr("2", ":")("2", true)(" > ").expr("3", ":")("3", true)(" < ")
			.expr("4", ":")("4", true);
	RB_FAIL(rbORDER_4(1, <, 2, >, 3, <, 4), *analysisOrder4b);
	RB_FAIL_V(rbvORDER_4(1, <, 2, >, 3, <, 4), *analysisOrder4b, 2);

	SharedAnalysis analysisOrder4c =
		(Analysis*)MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" < ")
			.expr("2", ":")("2", true)(" < ").expr("3", ":")("3", true)(" > ")
			.expr("4", ":")("4", true);
	RB_FAIL(rbORDER_4(1, <, 2, <, 3, >, 4), *analysisOrder4c);




	SharedAnalysis analysisInInterval =
		(Analysis*)MakeGeneralAnalysis(false).expr("3", ":")("3", true)(" in [")
			.expr("1", ":")("1", true)(", ").expr("2", ":")("2", true)("]");
	RB_FAIL(rbIN_INTERVAL(3, 1, 2), *analysisInInterval);
	RB_FAIL_V(rbvIN_INTERVAL(3, 1, 2), *analysisInInterval, 3);

	SharedAnalysis analysisInOpenInterval1 =
		(Analysis*)MakeGeneralAnalysis(false).expr("3", ":")("3", true)(" in (")
			.expr("1", ":")("1", true)(", ").expr("2", ":")("2", true)(")");
	RB_FAIL(rbIN_OPEN_INTERVAL(3, 1, 2), *analysisInOpenInterval1);
	RB_FAIL_V(rbvIN_OPEN_INTERVAL(3, 1, 2), *analysisInOpenInterval1, 3);

	SharedAnalysis analysisInOpenInterval2 =
		(Analysis*)MakeGeneralAnalysis(false).expr("1", ":")("1", true)(" in (")
			.expr("1", ":")("1", true)(", ").expr("2", ":")("2", true)(")");
	RB_FAIL(rbIN_OPEN_INTERVAL(1, 1, 2), *analysisInOpenInterval2);
	RB_FAIL_V(rbvIN_OPEN_INTERVAL(1, 1, 2), *analysisInOpenInterval2, 1);

	SharedAnalysis analysisInOpenInterval3 =
		(Analysis*)MakeGeneralAnalysis(false).expr("3", ":")("3", true)(" in (")
			.expr("1", ":")("1", true)(", ").expr("3", ":")("3", true)(")");
	RB_FAIL(rbIN_OPEN_INTERVAL(3, 1, 3), *analysisInOpenInterval3);
	RB_FAIL_V(rbvIN_OPEN_INTERVAL(3, 1, 3), *analysisInOpenInterval3, 3);

	SharedAnalysis analysisDiff =
		(Analysis*)MakeGeneralAnalysis(false).expr("2", ":")("2", true)(" != ")
			.expr("2", ":")("2", true);
	RB_FAIL(rbDIFF(2, 2), *analysisDiff);
	RB_FAIL_V(rbvDIFF(2, 2), *analysisDiff, 2);

	SharedAnalysis analysisRelNear1 =
		(Analysis*)MakeGeneralAnalysis(false)("relative difference of ")
			.expr("10.0", ":")(STR_10_0, true)
			(" and ").expr("8.99", ":")(STR_8_99, true)
			(" = ").result(STR_0_101)
			(" <= ").expr("0.1", ":")(STR_0_1, true);
	RB_FAIL(rbREL_NEAR(10.0, 8.99, 0.1), *analysisRelNear1);
	RB_FAIL_V(rbvREL_NEAR(10.0, 8.99, 0.1), *analysisRelNear1, 10.0);

	SharedAnalysis analysisRelNear2 =
		(Analysis*)MakeGeneralAnalysis(false)("relative difference of ")
			.expr("-10.0", ":")("-" STR_10_0, true)
			(" and ").expr("-8.99", ":")("-" STR_8_99, true)
			(" = ").result(STR_0_101)
			(" <= ").expr("0.1", ":")(STR_0_1, true);
	RB_FAIL(rbREL_NEAR(-10.0, -8.99, 0.1), *analysisRelNear2);
	RB_FAIL_V(rbvREL_NEAR(-10.0, -8.99, 0.1), *analysisRelNear2, -10.0);
}

RB_TEST(Fail_Near_Comparisons)
{
	SharedAnalysis analysisNear =
		(Analysis*)MakeGeneralAnalysis(false).expr("10.0", ":")(STR_10_0, true)
			(" ==~ ").expr("8.99", ":")(STR_8_99, true)
			(" (difference ")("is ").result(STR_1_01)(", ")
			.expr("0.1", ":")(STR_0_1, true)(" allowed)");
	RB_FAIL(rbNEAR(10.0, 8.99, 0.1), *analysisNear);
	RB_FAIL_V(rbvNEAR(10.0, 8.99, 0.1), *analysisNear, 10.0);

	SharedAnalysis analysisLess1 =
		(Analysis*)MakeGeneralAnalysis(false).expr("10.0", ":")(STR_10_0, true)
			(" <~ ").expr("8.99", ":")(STR_8_99, true)
			(" (difference ")("is ").result(STR_1_01)(", ")
			.expr("1.0", ":")(STR_1_0, true)(" allowed)");
	RB_FAIL(rbLESS_NEAR(10.0, 8.99, 1.0), *analysisLess1);
	RB_FAIL_V(rbvLESS_NEAR(10.0, 8.99, 1.0), *analysisLess1, 10.0);

	SharedAnalysis analysisMore =
		(Analysis*)MakeGeneralAnalysis(false).expr("8.99", ":")(STR_8_99, true)
			(" >~ ").expr("10.0", ":")(STR_10_0, true)
			(" (difference ")("is ").result(STR_1_01)(", ")
			.expr("1.0", ":")(STR_1_0, true)(" allowed)");
	RB_FAIL(rbMORE_NEAR(8.99, 10.0, 1.0), *analysisMore);
	RB_FAIL_V(rbvMORE_NEAR(8.99, 10.0, 1.0), *analysisMore, 8.99);

	SharedAnalysis analysisDiff1 =
		(Analysis*)MakeGeneralAnalysis(false).expr("1.0", ":")(STR_1_0, true)
			(" !=~ ").expr("1.099", ":")(STR_1_099, true)
			(" (difference ")("is ").result(STR_0_099)(", should be at least ")
			.expr("0.1", ":")(STR_0_1, true)(")");
	RB_FAIL(rbDIFF_NEAR(1.0, 1.099, 0.1), *analysisDiff1);
	RB_FAIL_V(rbvDIFF_NEAR(1.0, 1.099, 0.1), *analysisDiff1, 1.0);

	SharedAnalysis analysisDiff2 =
		(Analysis*)MakeGeneralAnalysis(false).expr("1.099", ":")(STR_1_099, true)
			(" !=~ ").expr("1.0", ":")(STR_1_0, true)
			(" (difference ")("is ").result(STR_0_099)(", should be at least ")
			.expr("0.1", ":")(STR_0_1, true)(")");
	RB_FAIL(rbDIFF_NEAR(1.099, 1.0, 0.1), *analysisDiff2);
	RB_FAIL_V(rbvDIFF_NEAR(1.099, 1.0, 0.1), *analysisDiff2, 1.099);

	SharedAnalysis analysisOrder2 =
		(Analysis*)MakeGeneralAnalysis(false).expr("8.99", ":")(STR_8_99, true)
			(" >~ ").expr("10.0", ":")(STR_10_0, true)
			(" (difference ")("is ").result(STR_1_01)(", ")
			.expr("0.1", ":")(STR_0_1, true)(" allowed)");
	RB_FAIL(rbORDER_2_NEAR(8.99, >, 10.0, 0.1), *analysisOrder2);
	RB_FAIL_V(rbvORDER_2_NEAR(8.99, >, 10.0, 0.1), *analysisOrder2, 8.99);

	SharedAnalysis analysisInterval1 =
		(Analysis*)MakeGeneralAnalysis(false).expr("0.899", ":")(STR_0_899, true)
			(" in [").expr("1.0", ":")(STR_1_0, true)
			(", ").expr("2.0", ":")(STR_2_0, true)("]")
			(" (difference up to ").expr("0.1", ":")(STR_0_1, true)(" allowed)");
	RB_FAIL(rbIN_INTERVAL_NEAR(0.899, 1.0, 2.0, 0.1), *analysisInterval1);
	RB_FAIL_V(rbvIN_INTERVAL_NEAR(0.899, 1.0, 2.0, 0.1), *analysisInterval1, 0.899);

	SharedAnalysis analysisInterval2 =
		(Analysis*)MakeGeneralAnalysis(false).expr("2.11", ":")(STR_2_11, true)
			(" in [").expr("1.0", ":")(STR_1_0, true)
			(", ").expr("2.0", ":")(STR_2_0, true)("]")
			(" (difference up to ").expr("0.1", ":")(STR_0_1, true)(" allowed)");
	RB_FAIL(rbIN_INTERVAL_NEAR(2.11, 1.0, 2.0, 0.1), *analysisInterval2);
	RB_FAIL_V(rbvIN_INTERVAL_NEAR(2.11, 1.0, 2.0, 0.1), *analysisInterval2, 2.11);

	SharedAnalysis analysisOrder3a =
		(Analysis*)MakeGeneralAnalysis(false).expr("1.0", ":")(STR_1_0, true)
			(" <~ ").expr("2.11", ":")(STR_2_11, true)
			(" <~ ").expr("2.0", ":")(STR_2_0, true)
			(" (difference up to ").expr("0.1", ":")(STR_0_1, true)(" allowed)");
	RB_FAIL(rbORDER_3_NEAR(1.0, <, 2.11, <, 2.0, 0.1), *analysisOrder3a);
	RB_FAIL_V(rbvORDER_3_NEAR(1.0, <, 2.11, <, 2.0, 0.1), *analysisOrder3a, 2.11);

	SharedAnalysis analysisOrder3b =
		(Analysis*)MakeGeneralAnalysis(false).expr("1.0", ":")(STR_1_0, true)
			(" <~ ").expr("0.899", ":")(STR_0_899, true)
			(" <~ ").expr("2.0", ":")(STR_2_0, true)
			(" (difference up to ").expr("0.1", ":")(STR_0_1, true)(" allowed)");
	RB_FAIL(rbORDER_3_NEAR(1.0, <, 0.899, <, 2.0, 0.1), *analysisOrder3b);
	RB_FAIL_V(rbvORDER_3_NEAR(1.0, <, 0.899, <, 2.0, 0.1), *analysisOrder3b, 0.899);

	SharedAnalysis analysisOrder4a =
		(Analysis*)MakeGeneralAnalysis(false).expr("1.0", ":")(STR_1_0, true)
			(" <~ ").expr("2.11", ":")(STR_2_11, true)
			(" <~ ").expr("2.0", ":")(STR_2_0, true)
			(" <~ ").expr("10.0", ":")(STR_10_0, true)
			(" (difference up to ").expr("0.1", ":")(STR_0_1, true)(" allowed)");
	RB_FAIL(rbORDER_4_NEAR(1.0, <, 2.11, <, 2.0, <, 10.0, 0.1), *analysisOrder4a);
	RB_FAIL_V(rbvORDER_4_NEAR(1.0, <, 2.11, <, 2.0, <, 10.0, 0.1), *analysisOrder4a, 2.11);

	SharedAnalysis analysisOrder4b =
		(Analysis*)MakeGeneralAnalysis(false).expr("1.0", ":")(STR_1_0, true)
			(" <~ ").expr("0.899", ":")(STR_0_899, true)
			(" <~ ").expr("2.0", ":")(STR_2_0, true)
			(" <~ ").expr("10.0", ":")(STR_10_0, true)
			(" (difference up to ").expr("0.1", ":")(STR_0_1, true)(" allowed)");
	RB_FAIL(rbORDER_4_NEAR(1.0, <, 0.899, <, 2.0, <, 10.0, 0.1), *analysisOrder4b);
	RB_FAIL_V(rbvORDER_4_NEAR(1.0, <, 0.899, <, 2.0, <, 10.0, 0.1), *analysisOrder4b, 0.899);
}

RB_TEST(Fail_Relative_Comparisons)
{
	SharedAnalysis analysisRelNear1 =
		(Analysis*)MakeGeneralAnalysis(false)("relative difference of ")
			.expr("10.0", ":")(STR_10_0, true)
			(" and ").expr("8.99", ":")(STR_8_99, true)
			(" = ").result(STR_0_101)
			(" <= ").expr("0.1", ":")(STR_0_1, true);
	RB_FAIL(rbREL_NEAR(10.0, 8.99, 0.1), *analysisRelNear1);
	RB_FAIL_V(rbvREL_NEAR(10.0, 8.99, 0.1), *analysisRelNear1, 10.0);

	SharedAnalysis analysisRelNear2 =
		(Analysis*)MakeGeneralAnalysis(false)("relative difference of ")
			.expr("-10.0", ":")("-" STR_10_0, true)
			(" and ").expr("-8.99", ":")("-" STR_8_99, true)
			(" = ").result(STR_0_101)
			(" <= ").expr("0.1", ":")(STR_0_1, true);
	RB_FAIL(rbREL_NEAR(-10.0, -8.99, 0.1), *analysisRelNear2);
	RB_FAIL_V(rbvREL_NEAR(-10.0, -8.99, 0.1), *analysisRelNear2, -10.0);

	SharedAnalysis analysisLess =
		(Analysis*)MakeGeneralAnalysis(false).expr("10.0", ":")(STR_10_0, true)
			(" <~ ").expr("8.99", ":")(STR_8_99, true)
			(" (relative difference ")("is ").result(STR_0_101)(", ")
			.expr("0.1", ":")(STR_0_1, true)(" allowed)");
	RB_FAIL(rbLESS_REL_NEAR(10.0, 8.99, 0.1), *analysisLess);
	RB_FAIL_V(rbvLESS_REL_NEAR(10.0, 8.99, 0.1), *analysisLess, 10.0);

	SharedAnalysis analysisMore =
		(Analysis*)MakeGeneralAnalysis(false).expr("8.99", ":")(STR_8_99, true)
			(" >~ ").expr("10.0", ":")(STR_10_0, true)
			(" (relative difference ")("is ").result(STR_0_101)(", ")
			.expr("0.1", ":")(STR_0_1, true)(" allowed)");
	RB_FAIL(rbMORE_REL_NEAR(8.99, 10.0, 0.1), *analysisMore);
	RB_FAIL_V(rbvMORE_REL_NEAR(8.99, 10.0, 0.1), *analysisMore, 8.99);

	SharedAnalysis analysisDiff1 =
		(Analysis*)MakeGeneralAnalysis(false).expr("10.0", ":")(ToString(10.0), true)
			(" !=~ ").expr("9.5", ":")(ToString(9.5), true)
			(" (relative difference ")("is ").result(ToString(0.05))(", should be at least ")
			.expr("0.1", ":")(STR_0_1, true)(")");
	RB_FAIL(rbDIFF_REL_NEAR(10.0, 9.5, 0.1), *analysisDiff1);
	RB_FAIL_V(rbvDIFF_REL_NEAR(10.0, 9.5, 0.1), *analysisDiff1, 10.0);

	SharedAnalysis analysisDiff2 =
		(Analysis*)MakeGeneralAnalysis(false).expr("9.5", ":")(ToString(9.5), true)
			(" !=~ ").expr("10.0", ":")(ToString(10.0), true)
			(" (relative difference ")("is ").result(ToString(0.05))(", should be at least ")
			.expr("0.1", ":")(STR_0_1, true)(")");
	RB_FAIL(rbDIFF_REL_NEAR(9.5, 10.0, 0.1), *analysisDiff2);
	RB_FAIL_V(rbvDIFF_REL_NEAR(9.5, 10.0, 0.1), *analysisDiff2, 9.5);

	SharedAnalysis analysisOrder2 =
		(Analysis*)MakeGeneralAnalysis(false).expr("8.99", ":")(STR_8_99, true)
			(" >~ ").expr("10.0", ":")(STR_10_0, true)
			(" (relative difference ")("is ").result(STR_0_101)(", ")
			.expr("0.1", ":")(STR_0_1, true)(" allowed)");
	RB_FAIL(rbORDER_2_REL_NEAR(8.99, >, 10.0, 0.1), *analysisOrder2);
	RB_FAIL_V(rbvORDER_2_REL_NEAR(8.99, >, 10.0, 0.1), *analysisOrder2, 8.99);

	SharedAnalysis analysisInterval1 =
		(Analysis*)MakeGeneralAnalysis(false).expr("7.1", ":")(ToString(7.1), true)
			(" in [").expr("8.0", ":")(ToString(8.0), true)
			(", ").expr("10.0", ":")(ToString(10.0), true)("]")
			(" (relative difference up to ").expr("0.1", ":")(ToString(0.1), true)(" allowed)");
	RB_FAIL(rbIN_INTERVAL_REL_NEAR(7.1, 8.0, 10.0, 0.1), *analysisInterval1);
	RB_FAIL_V(rbvIN_INTERVAL_REL_NEAR(7.1, 8.0, 10.0, 0.1), *analysisInterval1, 7.1);

	SharedAnalysis analysisInterval2 =
		(Analysis*)MakeGeneralAnalysis(false).expr("11.2", ":")(ToString(11.2), true)
			(" in [").expr("8.0", ":")(ToString(8.0), true)
			(", ").expr("10.0", ":")(ToString(10.0), true)("]")
			(" (relative difference up to ").expr("0.1", ":")(ToString(0.1), true)(" allowed)");
	RB_FAIL(rbIN_INTERVAL_REL_NEAR(11.2, 8.0, 10.0, 0.1), *analysisInterval2);
	RB_FAIL_V(rbvIN_INTERVAL_REL_NEAR(11.2, 8.0, 10.0, 0.1), *analysisInterval2, 11.2);

	SharedAnalysis analysisOrder3a =
		(Analysis*)MakeGeneralAnalysis(false).expr("1.0", ":")(STR_1_0, true)
			(" <~ ").expr("2.11", ":")(STR_2_11, true)
			(" <~ ").expr("1.0", ":")(STR_1_0, true)
			(" (relative difference up to ").expr("0.1", ":")(STR_0_1, true)(" allowed)");
	RB_FAIL(rbORDER_3_REL_NEAR(1.0, <, 2.11, <, 1.0, 0.1), *analysisOrder3a);
	RB_FAIL_V(rbvORDER_3_REL_NEAR(1.0, <, 2.11, <, 1.0, 0.1), *analysisOrder3a, 2.11);

	SharedAnalysis analysisOrder3b =
		(Analysis*)MakeGeneralAnalysis(false).expr("1.0", ":")(STR_1_0, true)
			(" <~ ").expr("0.899", ":")(STR_0_899, true)
			(" <~ ").expr("2.0", ":")(STR_2_0, true)
			(" (relative difference up to ").expr("0.1", ":")(STR_0_1, true)(" allowed)");
	RB_FAIL(rbORDER_3_REL_NEAR(1.0, <, 0.899, <, 2.0, 0.1), *analysisOrder3b);
	RB_FAIL_V(rbvORDER_3_REL_NEAR(1.0, <, 0.899, <, 2.0, 0.1), *analysisOrder3b, 0.899);

	SharedAnalysis analysisOrder4a =
		(Analysis*)MakeGeneralAnalysis(false).expr("1.0", ":")(STR_1_0, true)
			(" <~ ").expr("2.11", ":")(STR_2_11, true)
			(" <~ ").expr("1.0", ":")(STR_1_0, true)
			(" <~ ").expr("10.0", ":")(STR_10_0, true)
			(" (relative difference up to ").expr("0.1", ":")(STR_0_1, true)(" allowed)");
	RB_FAIL(rbORDER_4_REL_NEAR(1.0, <, 2.11, <, 1.0, <, 10.0, 0.1), *analysisOrder4a);
	RB_FAIL_V(rbvORDER_4_REL_NEAR(1.0, <, 2.11, <, 1.0, <, 10.0, 0.1), *analysisOrder4a, 2.11);

	SharedAnalysis analysisOrder4b =
		(Analysis*)MakeGeneralAnalysis(false).expr("1.0", ":")(STR_1_0, true)
			(" <~ ").expr("0.899", ":")(STR_0_899, true)
			(" <~ ").expr("2.0", ":")(STR_2_0, true)
			(" <~ ").expr("10.0", ":")(STR_10_0, true)
			(" (relative difference up to ").expr("0.1", ":")(STR_0_1, true)(" allowed)");
	RB_FAIL(rbORDER_4_REL_NEAR(1.0, <, 0.899, <, 2.0, <, 10.0, 0.1), *analysisOrder4b);
	RB_FAIL_V(rbvORDER_4_REL_NEAR(1.0, <, 0.899, <, 2.0, <, 10.0, 0.1), *analysisOrder4b, 0.899);
}

RB_TEST(Fail_Predicate)
{
	SharedAnalysis analysisEven =
		(Analysis*)MakeGeneralAnalysis(false)("predicate(")
			.expr("3", ":")("3", true)(")");
	RB_FAIL(rb1_PRED(3, IsEven()), *analysisEven);
	RB_FAIL_V(rbv1_PRED(3, IsEven()), *analysisEven, 3);

	SharedAnalysis analysisProd12a =
		(Analysis*)MakeGeneralAnalysis(false)("predicate(").expr("3", ":")("3", true)(", ")
			.expr("5", ":")("5", true)(")");
	RB_FAIL(rb2_PRED(3, 5, ProductIs(12)), *analysisProd12a);
	RB_FAIL_V(rbv2_PRED(3, 5, ProductIs(12)), *analysisProd12a, 3);

	SharedAnalysis analysisProd12b =
		(Analysis*)MakeGeneralAnalysis(false)("predicate(").expr("3", ":")("3", true)(", ")
			.expr("2", ":")("2", true)(", ").expr("3", ":")("3", true)(")");
	RB_FAIL(rb3_PRED(3, 2, 3, ProductIs(12)), *analysisProd12b);
	RB_FAIL_V(rbv3_PRED(3, 2, 3, ProductIs(12)), *analysisProd12b, 3);

	SharedAnalysis analysisProd120 =
		(Analysis*)MakeGeneralAnalysis(false)("predicate(").expr("2", ":")("2", true)(", ")
			.expr("3", ":")("3", true)(", ").expr("4", ":")("4", true)
			(", ").expr("6", ":")("6", true)(")");
	RB_FAIL(rb4_PRED(2, 3, 4, 6, ProductIs(120)), *analysisProd120);
	RB_FAIL_V(rbv4_PRED(2, 3, 4, 6, ProductIs(120)), *analysisProd120, 2);

	SharedAnalysis analysisProd120b =
		(Analysis*)MakeGeneralAnalysis(false)("predicate(").expr("2", ":")("2", true)(", ")
			.expr("3", ":")("3", true)(", ").expr("4", ":")("4", true)
			(", ").expr("6", ":")("6", true)(", ").expr("1", ":")("1", true)(")");
	RB_FAIL(rb5_PRED(2, 3, 4, 6, 1, ProductIs(120)), *analysisProd120b);
	RB_FAIL_V(rbv5_PRED(2, 3, 4, 6, 1, ProductIs(120)), *analysisProd120b, 2);

	SharedAnalysis analysisProd120c =
		(Analysis*)MakeGeneralAnalysis(false)("predicate(").expr("2", ":")("2", true)(", ")
			.expr("3", ":")("3", true)(", ").expr("4", ":")("4", true)
			(", ").expr("6", ":")("6", true)(", ").expr("1", ":")("1", true)
			(", ").expr("2", ":")("2", true)(")");
	RB_FAIL(rb6_PRED(2, 3, 4, 6, 1, 2, ProductIs(120)), *analysisProd120c);
	RB_FAIL_V(rbv6_PRED(2, 3, 4, 6, 1, 2, ProductIs(120)), *analysisProd120c, 2);

#ifdef RICHBOOL_LAMBDAS
    // not really necessary because lambdas act as functors
    // but I was just curious to test it
	RB_FAIL(rb1_PRED(3, [](int x) { return x%2==0; }), *analysisEven);
	RB_FAIL_V(rbv1_PRED(3, [](int x) { return x%2==0; }), *analysisEven, 3);

	RB_FAIL(rb2_PRED(3, 5, [](int x, int y) { return x*y==12; }), *analysisProd12a);
	RB_FAIL_V(rbv2_PRED(3, 5, [](int x, int y) { return x*y==12; }), *analysisProd12a, 3);
#endif

}

RB_TEST(Fail_EqualData)
{
	const char buf1[] = { '\x00', '\xab', '\x45', '\xff' };
	const char buf2[] = { '\x00', '\xab', '\x54', '\xff' };

	BriefAnalysisOfTwoSequences analysis2Seq4(false, new TextExpression("buf1"), new TextExpression("buf2"),
		new TextExpression("b"),
		"", " == ", " (", " bytes)");
	analysis2Seq4.SetString1   ("00ab45ff");
	analysis2Seq4.SetString2   ("00ab54ff");
	analysis2Seq4.SetStringDiff("    XX  ");
	analysis2Seq4.SetBlockSize(2);
	analysis2Seq4.SetBlocksPerLine(16);
	RB_FAIL(rbEQUAL_DATA(buf1, buf2, 4), analysis2Seq4);
	RB_FAIL_V(rbvEQUAL_DATA(buf1, buf2, 4), analysis2Seq4, buf1);
}

RB_TEST(Fail_EqualDataBitwise)
{
	BriefAnalysisOfTwoSequences analysis2Seq3(false, new TextExpression("15"), new TextExpression("51"),
		"", " .==. ", "");
	analysis2Seq3.SetString1   ("00001111000000000000000000000000");
	analysis2Seq3.SetString2   ("00110011000000000000000000000000");
	analysis2Seq3.SetStringDiff("  XXXX                          ");
	analysis2Seq3.SetBlockSize(8);
	analysis2Seq3.SetBlocksPerLine(8);
	RB_FAIL(rbEQUAL_BITWISE(15, 51), analysis2Seq3);
	RB_FAIL_V(rbvEQUAL_BITWISE(15, 51), analysis2Seq3, 15);

	const char buf1[] = { '\x00', '\xab', '\x45', '\xff' };
	const char buf2[] = { '\x00', '\xab', '\x54', '\xff' };

	BriefAnalysisOfTwoSequences analysis2Seq5(false, new TextExpression("buf1"), new TextExpression("buf2"),
		new TextExpression("b"),
		"", " .==. ", " (", " bytes)");
	analysis2Seq5.SetString1   ("00000000101010110100010111111111");
	analysis2Seq5.SetString2   ("00000000101010110101010011111111");
	analysis2Seq5.SetStringDiff("                   X   X        ");
	analysis2Seq5.SetBlockSize(8);
	analysis2Seq5.SetBlocksPerLine(8);
	RB_FAIL(rbEQUAL_DATA_BITWISE(buf1, buf2, 4), analysis2Seq5);
	RB_FAIL_V(rbvEQUAL_DATA_BITWISE(buf1, buf2, 4), analysis2Seq5, buf1);
}

RB_TEST(Fail_FirstNull)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int *p=0;

	SharedAnalysis analysisEqual =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue).expr("*p", ":")(GetNullPtrString(), false)
			(" == ").expr("2", ":")("2", true);
	RB_FAIL(rbEQUAL(*p, 2), *analysisEqual);
	RB_FAIL_IV(rbvEQUAL(*p, 2), *analysisEqual);

	SharedAnalysis analysisLess =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue).expr("*p", ":")(GetNullPtrString(), false)
			(" < ").expr("1", ":")("1", true);
	RB_FAIL(rbLESS(*p, 1), *analysisLess);
	RB_FAIL_IV(rbvLESS(*p, 1), *analysisLess);

	SharedAnalysis analysisLE =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue).expr("*p", ":")(GetNullPtrString(), false)
			(" <= ").expr("1", ":")("1", true);
	RB_FAIL(rbLESS_OR_EQUAL(*p, 1), *analysisLE);
	RB_FAIL_IV(rbvLESS_OR_EQUAL(*p, 1), *analysisLE);

	SharedAnalysis analysisMore1 =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue).expr("*p", ":")(GetNullPtrString(), false)
			(" > ").expr("1", ":")("1", true);
	RB_FAIL(rbMORE(*p, 1), *analysisMore1);
	RB_FAIL_IV(rbvMORE(*p, 1), *analysisMore1);

	SharedAnalysis analysisGE =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue).expr("*p", ":")(GetNullPtrString(), false)
			(" >= ").expr("2", ":")("2", true);
	RB_FAIL(rbMORE_OR_EQUAL(*p, 2), *analysisGE);
	RB_FAIL_IV(rbvMORE_OR_EQUAL(*p, 2), *analysisGE);

	SharedAnalysis analysisInInterval =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue).expr("3", ":")("3", true)(" in [")
			.expr("*p", ":")(GetNullPtrString(), false)(", ").expr("2", ":")("2", true)
			("]");
	RB_FAIL(rbIN_INTERVAL(3, *p, 2), *analysisInInterval);
	RB_FAIL_V(rbvIN_INTERVAL(3, *p, 2), *analysisInInterval, 3);

	SharedAnalysis analysisDiff =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue).expr("*p", ":")(GetNullPtrString(), false)
			(" != ").expr("2", ":")("2", true);
	RB_FAIL(rbDIFF(*p, 2), *analysisDiff);
	RB_FAIL_IV(rbvDIFF(*p, 2), *analysisDiff);

	SharedAnalysis analysisEven =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue)("predicate(")
			.expr("*p", ":")(GetNullPtrString(), false)(")");
	RB_FAIL(rb1_PRED(*p, IsEven()), *analysisEven);
	RB_FAIL_IV(rbv1_PRED(*p, IsEven()), *analysisEven);

	SharedAnalysis analysisProd12a =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue)("predicate(")
			.expr("*p", ":")(GetNullPtrString(), false)(", ").expr("5", ":")("5", true)(")");
	RB_FAIL(rb2_PRED(*p, 5, ProductIs(12)), *analysisProd12a);
	RB_FAIL_IV(rbv2_PRED(*p, 5, ProductIs(12)), *analysisProd12a);

	SharedAnalysis analysisProd12b =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue)("predicate(")
			.expr("*p", ":")(GetNullPtrString(), false)(", ")
			.expr("2", ":")("2", true)(", ").expr("3", ":")("3", true)(")");
	RB_FAIL(rb3_PRED(*p, 2, 3, ProductIs(12)), *analysisProd12b);
	RB_FAIL_IV(rbv3_PRED(*p, 2, 3, ProductIs(12)), *analysisProd12b);

	SharedAnalysis analysisProd12c =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue)("predicate(")
			.expr("*p", ":")(GetNullPtrString(), false)(", ")
			.expr("2", ":")("2", true)(", ").expr("3", ":")("3", true)(", ")
			.expr("4", ":")("4", true)(")");
	RB_FAIL(rb4_PRED(*p, 2, 3, 4, ProductIs(12)), *analysisProd12c);
}

RB_TEST(Fail_SecondNull)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int *p=0;

	SharedAnalysis analysisEqual =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue).expr("1", ":")("1", true)(" == ")
			.expr("*p", ":")(GetNullPtrString(), false);
	RB_FAIL(rbEQUAL(1, *p), *analysisEqual);
	RB_FAIL_V(rbvEQUAL(1, *p), *analysisEqual, 1);

	SharedAnalysis analysisLess1 =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue).expr("1", ":")("1", true)(" < ")
			.expr("*p", ":")(GetNullPtrString(), false);
	RB_FAIL(rbLESS(1, *p), *analysisLess1);
	RB_FAIL_V(rbvLESS(1, *p), *analysisLess1, 1);

	SharedAnalysis analysisLE =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue).expr("2", ":")("2", true)(" <= ")
			.expr("*p", ":")(GetNullPtrString(), false);
	RB_FAIL(rbLESS_OR_EQUAL(2, *p), *analysisLE);
	RB_FAIL_V(rbvLESS_OR_EQUAL(2, *p), *analysisLE, 2);

	SharedAnalysis analysisMore1 =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue).expr("1", ":")("1", true)(" > ")
			.expr("*p", ":")(GetNullPtrString(), false);
	RB_FAIL(rbMORE(1, *p), *analysisMore1);
	RB_FAIL_V(rbvMORE(1, *p), *analysisMore1, 1);

	SharedAnalysis analysisGE =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue).expr("1", ":")("1", true)(" >= ")
			.expr("*p", ":")(GetNullPtrString(), false);
	RB_FAIL(rbMORE_OR_EQUAL(1, *p), *analysisGE);
	RB_FAIL_V(rbvMORE_OR_EQUAL(1, *p), *analysisGE, 1);

	SharedAnalysis analysisInInterval =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue).expr("3", ":")("3", true)
			(" in [").expr("1", ":")("1", true)(", ")
			.expr("*p", ":")(GetNullPtrString(), false)("]");
	RB_FAIL(rbIN_INTERVAL(3, 1, *p), *analysisInInterval);
	RB_FAIL_V(rbvIN_INTERVAL(3, 1, *p), *analysisInInterval, 3);

	SharedAnalysis analysisDiff =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue).expr("2", ":")("2", true)(" != ")
			.expr("*p", ":")(GetNullPtrString(), false);
	RB_FAIL(rbDIFF(2, *p), *analysisDiff);
	RB_FAIL_V(rbvDIFF(2, *p), *analysisDiff, 2);

	SharedAnalysis analysisNear =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue).expr("1.0", ":")(STR_1_0, true)(" ==~ ")
			.expr("*p", ":")(GetNullPtrString(), false)
			(" (difference ").expr("0.1", ":")(STR_0_1, true)(" allowed)");
	RB_FAIL(rbNEAR(1.0, *p, 0.1), *analysisNear);
	RB_FAIL_V(rbvNEAR(1.0, *p, 0.1), *analysisNear, 1.0);

	SharedAnalysis analysisProd12a =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue)("predicate(").expr("3", ":")("3", true)
			(", ").expr("*p", ":")(GetNullPtrString(), false)(")");
	RB_FAIL(rb2_PRED(3, *p, ProductIs(12)), *analysisProd12a);
	RB_FAIL_V(rbv2_PRED(3, *p, ProductIs(12)), *analysisProd12a, 3);

	SharedAnalysis analysisProd12b = (Analysis*)MakeGeneralAnalysis(Analysis::BadValue)
		("predicate(").expr("3", ":")("3", true)(", ")
		.expr("*p", ":")(GetNullPtrString(), false)(", ")
		.expr("3", ":")("3", true)(")");
	RB_FAIL(rb3_PRED(3, *p, 3, ProductIs(12)), *analysisProd12b);
	RB_FAIL_V(rbv3_PRED(3, *p, 3, ProductIs(12)), *analysisProd12b, 3);

	SharedAnalysis analysisProd12c = (Analysis*)MakeGeneralAnalysis(Analysis::BadValue)
		("predicate(").expr("3", ":")("3", true)(", ")
		.expr("*p", ":")(GetNullPtrString(), false)(", ")
		.expr("3", ":")("3", true)(", ")
		.expr("4", ":")("4", true)(")");
	RB_FAIL(rb4_PRED(3, *p, 3, 4, ProductIs(12)), *analysisProd12c);
	RB_FAIL_V(rbv4_PRED(3, *p, 3, 4, ProductIs(12)), *analysisProd12c, 3);
}

RB_TEST(Fail_ThirdNull)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int *p=0;
	double *pd=0;

	SharedAnalysis analysisInInterval =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue).expr("*p", ":")(GetNullPtrString(), false)
			(" in [").expr("1", ":")("1", true)(", ").expr("3", ":")("3", true)("]");

	RB_FAIL(rbIN_INTERVAL(*p, 1, 3), *analysisInInterval);
	RB_FAIL_IV(rbvIN_INTERVAL(*p, 1, 3), *analysisInInterval);

	SharedAnalysis analysisNear =
		(Analysis*)MakeGeneralAnalysis(Analysis::BadValue)
			.expr("1.0", ":")(STR_1_0, true)(" ==~ ")
			.expr("2.0", ":")(STR_2_0, true)(" (difference ")
			.expr("*pd", ":")(GetNullPtrString(), false)(" allowed)");
	RB_FAIL(rbNEAR(1.0, 2.0, *pd), *analysisNear);
	RB_FAIL_V(rbvNEAR(1.0, 2.0, *pd), *analysisNear, 1.0);

	SharedAnalysis analysisProd12a = (Analysis*)MakeGeneralAnalysis(Analysis::BadValue)
		("predicate(").expr("3", ":")("3", true)(", ").expr("5", ":")("5", true)
		(", ").expr("*p", ":")(GetNullPtrString(), false)(")");
	RB_FAIL(rb3_PRED(3, 5, *p, ProductIs(12)), *analysisProd12a);
	RB_FAIL_V(rbv3_PRED(3, 5, *p, ProductIs(12)), *analysisProd12a, 3);

	SharedAnalysis analysisProd12b = (Analysis*)MakeGeneralAnalysis(Analysis::BadValue)
		("predicate(").expr("3", ":")("3", true)(", ").expr("5", ":")("5", true)
		(", ").expr("*p", ":")(GetNullPtrString(), false)
		(", ").expr("1", ":")("1", true)(")");
	RB_FAIL(rb4_PRED(3, 5, *p, 1, ProductIs(12)), *analysisProd12b);
}

RB_TEST(Fail_FourthNull)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int *p=0;
	SharedAnalysis analysisProd12a = (Analysis*)MakeGeneralAnalysis(Analysis::BadValue)
		("predicate(").expr("3", ":")("3", true)(", ").expr("5", ":")("5", true)
		(", ").expr("1", ":")("1", true)
		(", ").expr("*p", ":")(GetNullPtrString(), false)(")");
	RB_FAIL(rb4_PRED(3, 5, 1, *p, ProductIs(12)), *analysisProd12a);
}

RB_TEST(rbv2_1_RB)
{
    RB_PASS_V(rbv2_1_RB(1, 2, Less<>()), 1);
}

RB_TEST(rbv2_2_RB)
{
    RB_PASS_V(rbv2_2_RB(1, 2, Less<>()), 2);
}

RB_TEST(rbv3_1_RB)
{
    RB_PASS_V(rbv3_1_RB(3, 2, 5, InOpenInterval<>()), 3);
}

RB_TEST(rbv3_2_RB)
{
    RB_PASS_V(rbv3_2_RB(3, 2, 5, InOpenInterval<>()), 2);
}

RB_TEST(rbv3_3_RB)
{
    RB_PASS_V(rbv3_3_RB(3, 2, 5, InOpenInterval<>()), 5);
}
