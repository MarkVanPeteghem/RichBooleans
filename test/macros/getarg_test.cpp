//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/functors.hpp"
#include "richbool/getarg.hpp"

#define rb2_RB_(a,b,functor) (richbool_level>=2 ? \
	RichBool::TmpBool(functor.Analyse(a,b,RICHBOOL_TEXT_EXPR(#a),RICHBOOL_TEXT_EXPR(#b),richbool_level==3)) : \
	( richbool_level==1 ? RichBool::TmpBool(RichBool::Id(functor)(a,b)) : (a,b,RichBool::TmpBool(true)) ) \
	)

#define rb3_RB_(a,b,c,functor) (richbool_level>=2 ? \
	RichBool::TmpBool((functor).Analyse(a,b,c, \
		RICHBOOL_TEXT_EXPR(#a),RICHBOOL_TEXT_EXPR(#b),RICHBOOL_TEXT_EXPR(#c), \
		richbool_level==3)) : \
	( richbool_level==1 ? RichBool::TmpBool(RichBool::Id(functor)(a,b,c)) : (a,b,c,RichBool::TmpBool(true)) ) \
	)

#define rb4_RB_IMPL_(a,ea,b,eb,c,ec,d,ed,functor) (richbool_level>=2 ? \
	RichBool::TmpBool((functor).Analyse(a,b,c,d, \
		RICHBOOL_TEXT_EXPR(ea),RICHBOOL_TEXT_EXPR(eb),RICHBOOL_TEXT_EXPR(ec), \
		RICHBOOL_TEXT_EXPR(ed), richbool_level==3)) : \
	( richbool_level==1 ? RichBool::TmpBool(RichBool::Id(functor)(a,b,c,d)) : (a,b,c,d,RichBool::TmpBool(true)) ) \
	)
#define rb4_RB_(a,b,c,d,functor) rb4_RB_IMPL_(a,#a,b,#b,c,#c,d,#d,functor)

#define rb5_RB_(a,b,c,d,e,functor) (richbool_level>=2 ? \
	RichBool::TmpBool((functor).Analyse(a,b,c,d,e, \
		RICHBOOL_TEXT_EXPR(#a),RICHBOOL_TEXT_EXPR(#b),RICHBOOL_TEXT_EXPR(#c), \
		RICHBOOL_TEXT_EXPR(#d),RICHBOOL_TEXT_EXPR(#e), richbool_level==3)) : \
	( richbool_level==1 ? RichBool::TmpBool(RichBool::Id(functor)(a,b,c,d,e)) : (a,b,c,d,e,RichBool::TmpBool(true)) ) \
	)

struct MockRB1Core
{
	int *m_p;
	MockRB1Core(int *p): m_p(p) {}
	bool operator()(int a) const
	{
		*m_p = a;
		return true;
	}
};

struct MockRB1: public RichBool::Wrapper1Arg<MockRB1Core>
{
	MockRB1(int *p):
		RichBool::Wrapper1Arg<MockRB1Core>(MockRB1Core(p))
	{}
};

struct MockRB2Core: public RichBool::FunctorCore
{
	int *m_p1, *m_p2;
	MockRB2Core(int *p1, int*p2): m_p1(p1), m_p2(p2) {}
	bool operator()(int a, int b) const
	{
		*m_p1 = a;
		*m_p2 = b;
		return true;
	}
};

struct MockRB2: public RichBool::Wrapper2Arg<MockRB2Core>
{
	MockRB2(int *p1, int *p2):
		RichBool::Wrapper2Arg<MockRB2Core>(MockRB2Core(p1, p2))
	{}
};

struct MockRB3Core: public RichBool::FunctorCore
{
	int *m_p1, *m_p2, *m_p3;
	MockRB3Core(int *p1, int *p2, int *p3): m_p1(p1), m_p2(p2), m_p3(p3) {}
	bool operator()(int a, int b, int c) const
	{
		*m_p1 = a;
		*m_p2 = b;
		*m_p3 = c;
		return true;
	}
};

struct MockRB3: public RichBool::Wrapper3Arg<MockRB3Core>
{
	MockRB3(int *p1, int *p2, int *p3):
		RichBool::Wrapper3Arg<MockRB3Core>(MockRB3Core(p1, p2, p3))
	{}
};

struct MockRB4Core: public RichBool::FunctorCore
{
	int *m_p1, *m_p2, *m_p3, *m_p4;
	MockRB4Core(int *p1, int *p2, int *p3, int *p4): m_p1(p1), m_p2(p2), m_p3(p3), m_p4(p4) {}
	bool operator()(int a, int b, int c, int d) const
	{
		*m_p1 = a;
		*m_p2 = b;
		*m_p3 = c;
		*m_p4 = d;
		return true;
	}
};

struct MockRB4: public RichBool::Wrapper4Arg<MockRB4Core>
{
	MockRB4(int *p1, int *p2, int *p3, int *p4):
		RichBool::Wrapper4Arg<MockRB4Core>(MockRB4Core(p1, p2, p3, p4))
	{}
};

struct MockRB5Core: public RichBool::FunctorCore
{
	int *m_p1, *m_p2, *m_p3, *m_p4, *m_p5;
	MockRB5Core(int *p1, int *p2, int *p3, int *p4, int *p5):
		m_p1(p1), m_p2(p2), m_p3(p3), m_p4(p4), m_p5(p5) {}
	bool operator()(int a, int b, int c, int d, int e) const
	{
		*m_p1 = a;
		*m_p2 = b;
		*m_p3 = c;
		*m_p4 = d;
		*m_p5 = e;
		return true;
	}
};

struct MockRB5: public RichBool::Wrapper5Arg<MockRB5Core>
{
	MockRB5(int *p1, int *p2, int *p3, int *p4, int *p5):
		RichBool::Wrapper5Arg<MockRB5Core>(MockRB5Core(p1, p2, p3, p4, p5))
	{}
};

RB_TEST(GetOneArgument_1_WithMock)
{
	int n=0;
	MockRB1 mock(&n);
	RichBool::detail::Get1Arg<MockRB1, 1> arg1(mock);

	arg1(1);
	RB_ASSERT(rbEQUAL(n, 1));

	arg1(2,1);
	RB_ASSERT(rbEQUAL(n, 2));

	arg1(3,2,1);
	RB_ASSERT(rbEQUAL(n, 3));

	arg1(4,3,2,1);
	RB_ASSERT(rbEQUAL(n, 4));

	arg1(5,4,3,2,1);
	RB_ASSERT(rbEQUAL(n, 5));

	arg1(6,5,4,3,2,1);
	RB_ASSERT(rbEQUAL(n, 6));
}

RB_TEST(GetTwoArguments_WithMock)
{
	int n1=0, n2=0;
	MockRB2 mock(&n1, &n2);
	RichBool::detail::Get2Args<MockRB2, 1, 2> arg12(mock);

	arg12(2,1);
	RB_ASSERT(rbEQUAL(n1, 2));
	RB_ASSERT(rbEQUAL(n2, 1));

	arg12(3,2,1);
	RB_ASSERT(rbEQUAL(n1, 3));
	RB_ASSERT(rbEQUAL(n2, 2));

	arg12(4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 4));
	RB_ASSERT(rbEQUAL(n2, 3));

	arg12(5,4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 5));
	RB_ASSERT(rbEQUAL(n2, 4));

	arg12(6,5,4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 6));
	RB_ASSERT(rbEQUAL(n2, 5));
}

RB_TEST(GetTwoArgumentsReverse_WithMock)
{
	int n1=0, n2=0;
	MockRB2 mock(&n1, &n2);
	RichBool::detail::Get2Args<MockRB2, 2, 1> arg21(mock);

	arg21(2,1);
	RB_ASSERT(rbEQUAL(n1, 1));
	RB_ASSERT(rbEQUAL(n2, 2));

	arg21(3,2,1);
	RB_ASSERT(rbEQUAL(n1, 2));
	RB_ASSERT(rbEQUAL(n2, 3));

	arg21(4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 3));
	RB_ASSERT(rbEQUAL(n2, 4));

	arg21(5,4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 4));
	RB_ASSERT(rbEQUAL(n2, 5));

	arg21(6,5,4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 5));
	RB_ASSERT(rbEQUAL(n2, 6));
}

RB_TEST(GetThreeArguments_WithMock)
{
	int n1=0, n2=0, n3=0;
	MockRB3 mock(&n1, &n2, &n3);
	RichBool::detail::Get3Args<MockRB3, 1, 2, 3> arg(mock);

	arg(3,2,1);
	RB_ASSERT(rbEQUAL(n1, 3));
	RB_ASSERT(rbEQUAL(n2, 2));
	RB_ASSERT(rbEQUAL(n3, 1));

	arg(4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 4));
	RB_ASSERT(rbEQUAL(n2, 3));
	RB_ASSERT(rbEQUAL(n3, 2));

	arg(5,4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 5));
	RB_ASSERT(rbEQUAL(n2, 4));
	RB_ASSERT(rbEQUAL(n3, 3));

	arg(6,5,4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 6));
	RB_ASSERT(rbEQUAL(n2, 5));
	RB_ASSERT(rbEQUAL(n3, 4));
}

RB_TEST(GetThreeArgumentsReverse_WithMock)
{
	int n1=0, n2=0, n3=0;
	MockRB3 mock(&n1, &n2, &n3);
	RichBool::detail::Get3Args<MockRB3, 3, 2, 1> arg(mock);

	arg(3,2,1);
	RB_ASSERT(rbEQUAL(n1, 1));
	RB_ASSERT(rbEQUAL(n2, 2));
	RB_ASSERT(rbEQUAL(n3, 3));

	arg(4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 2));
	RB_ASSERT(rbEQUAL(n2, 3));
	RB_ASSERT(rbEQUAL(n3, 4));

	arg(5,4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 3));
	RB_ASSERT(rbEQUAL(n2, 4));
	RB_ASSERT(rbEQUAL(n3, 5));

	arg(6,5,4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 4));
	RB_ASSERT(rbEQUAL(n2, 5));
	RB_ASSERT(rbEQUAL(n3, 6));
}

RB_TEST(Get4Arguments_WithMock)
{
	int n1=0, n2=0, n3=0, n4=0;
	MockRB4 mock(&n1, &n2, &n3, &n4);
	RichBool::detail::Get4Args<MockRB4, 1, 2, 3, 4> arg(mock);

	arg(4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 4));
	RB_ASSERT(rbEQUAL(n2, 3));
	RB_ASSERT(rbEQUAL(n3, 2));
	RB_ASSERT(rbEQUAL(n4, 1));

	arg(5,4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 5));
	RB_ASSERT(rbEQUAL(n2, 4));
	RB_ASSERT(rbEQUAL(n3, 3));
	RB_ASSERT(rbEQUAL(n4, 2));

	arg(6,5,4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 6));
	RB_ASSERT(rbEQUAL(n2, 5));
	RB_ASSERT(rbEQUAL(n3, 4));
	RB_ASSERT(rbEQUAL(n4, 3));
}

RB_TEST(Get4ArgumentsReverse_WithMock)
{
	int n1=0, n2=0, n3=0, n4=0;
	MockRB4 mock(&n1, &n2, &n3, &n4);
	RichBool::detail::Get4Args<MockRB4, 4, 3, 2, 1> arg(mock);

	arg(4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 1));
	RB_ASSERT(rbEQUAL(n2, 2));
	RB_ASSERT(rbEQUAL(n3, 3));
	RB_ASSERT(rbEQUAL(n4, 4));

	arg(5,4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 2));
	RB_ASSERT(rbEQUAL(n2, 3));
	RB_ASSERT(rbEQUAL(n3, 4));
	RB_ASSERT(rbEQUAL(n4, 5));

	arg(6,5,4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 3));
	RB_ASSERT(rbEQUAL(n2, 4));
	RB_ASSERT(rbEQUAL(n3, 5));
	RB_ASSERT(rbEQUAL(n4, 6));
}

RB_TEST(Get5Arguments_WithMock)
{
	int n1=0, n2=0, n3=0, n4=0, n5=0;
	MockRB5 mock(&n1, &n2, &n3, &n4, &n5);
	RichBool::detail::Get5Args<MockRB5, 1, 2, 3, 4, 5> arg(mock);

	arg(5,4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 5));
	RB_ASSERT(rbEQUAL(n2, 4));
	RB_ASSERT(rbEQUAL(n3, 3));
	RB_ASSERT(rbEQUAL(n4, 2));
	RB_ASSERT(rbEQUAL(n5, 1));

	arg(6,5,4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 6));
	RB_ASSERT(rbEQUAL(n2, 5));
	RB_ASSERT(rbEQUAL(n3, 4));
	RB_ASSERT(rbEQUAL(n4, 3));
	RB_ASSERT(rbEQUAL(n5, 2));
}

RB_TEST(Get5ArgumentsReverse_WithMock)
{
	int n1=0, n2=0, n3=0, n4=0, n5=0;
	MockRB5 mock(&n1, &n2, &n3, &n4, &n5);
	RichBool::detail::Get5Args<MockRB5, 5, 4, 3, 2, 1> arg(mock);

	arg(5,4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 1));
	RB_ASSERT(rbEQUAL(n2, 2));
	RB_ASSERT(rbEQUAL(n3, 3));
	RB_ASSERT(rbEQUAL(n4, 4));
	RB_ASSERT(rbEQUAL(n5, 5));

	arg(6,5,4,3,2,1);
	RB_ASSERT(rbEQUAL(n1, 2));
	RB_ASSERT(rbEQUAL(n2, 3));
	RB_ASSERT(rbEQUAL(n3, 4));
	RB_ASSERT(rbEQUAL(n4, 5));
	RB_ASSERT(rbEQUAL(n5, 6));
}

static
RichBool::SharedAnalysis an1 = (RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false)
	.expr("7", ":")("7", true)(" == ")("5", true);

static
RichBool::SharedAnalysis an2 = (RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false)
	.expr("7", ":")("7", true)(" == ").expr("5", ":")("5", true);

static
RichBool::SharedAnalysis an3 = (RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false)
	.expr("1", ":")("1", true)(" < ").expr("5", ":")("5", true)(" < ").expr("3", ":")("3", true);

static
RichBool::Order3<RichBool::LessRelation, RichBool::LessRelation> order3;

static
RichBool::SharedAnalysis an4 = (RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false)
	.expr("1", ":")("1", true)(" < ").expr("5", ":")("5", true)(" < ")
	.expr("7", ":")("7", true)(" < ").expr("3", ":")("3", true);

static
RichBool::Order4<RichBool::LessRelation, RichBool::LessRelation, RichBool::LessRelation> order4;


#if !defined(_MSC_VER) || (_MSC_VER > 1300)

//////////////////////////////////////////////////////////////////
// Get1Arg

RB_TEST(Get1ArgOf2)
{
	RB_PASS(rb2_RB_(5, 9, RichBool::Get1Arg<1>(RichBool::Equals<int>(5))));
	RB_FAIL(rb2_RB_(7, 9, RichBool::Get1Arg<1>(RichBool::Equals<int>(5))), *an1);
}

RB_TEST(Get1ArgOf3)
{
	RB_PASS(rb3_RB_(5, 9, 1, RichBool::Get1Arg<1>(RichBool::Equals<int>(5))));
	RB_FAIL(rb3_RB_(7, 9, 1, RichBool::Get1Arg<1>(RichBool::Equals<int>(5))), *an1);
}

RB_TEST(Get1ArgOf4)
{
	RB_PASS(rb4_RB_(5, 9, 1, 2, RichBool::Get1Arg<1>(RichBool::Equals<int>(5))));
	RB_FAIL(rb4_RB_(7, 9, 1, 2, RichBool::Get1Arg<1>(RichBool::Equals<int>(5))), *an1);
}

RB_TEST(Get1ArgOf5)
{
	RB_PASS(rb5_RB_(5, 9, 1, 2, 3, RichBool::Get1Arg<1>(RichBool::Equals<int>(5))));
	RB_FAIL(rb5_RB_(7, 9, 1, 2, 3, RichBool::Get1Arg<1>(RichBool::Equals<int>(5))), *an1);
}


//////////////////////////////////////////////////////////////////
// Get2Args

RB_TEST(Get2ArgsOf2)
{
	RB_PASS(rb2_RB_(5, 5, (RichBool::Get2Args<1,2>(RichBool::Equal<>()))));
	RB_FAIL(rb2_RB_(7, 5, (RichBool::Get2Args<1,2>(RichBool::Equal<>()))), *an2);
}

RB_TEST(Get2ArgsOf2_Reverse)
{
	RB_PASS(rb2_RB_(5, 5, (RichBool::Get2Args<2,1>(RichBool::Equal<>()))));
	RB_FAIL(rb2_RB_(5, 7, (RichBool::Get2Args<2,1>(RichBool::Equal<>()))), *an2);
}

RB_TEST(Get2ArgsOf3)
{
	RB_PASS(rb3_RB_(5, 5, 1, (RichBool::Get2Args<1,2>(RichBool::Equal<>()))));
	RB_FAIL(rb3_RB_(7, 5, 1, (RichBool::Get2Args<1,2>(RichBool::Equal<>()))), *an2);
}

RB_TEST(Get2ArgsOf4)
{
	RB_PASS(rb4_RB_(5, 5, 1, 2, (RichBool::Get2Args<1,2>(RichBool::Equal<>()))));
	RB_FAIL(rb4_RB_(7, 5, 1, 2, (RichBool::Get2Args<1,2>(RichBool::Equal<>()))), *an2);
}

RB_TEST(Get2ArgsOf5)
{
	RB_PASS(rb5_RB_(5, 5, 1, 2, 3, (RichBool::Get2Args<1,2>(RichBool::Equal<>()))));
	RB_FAIL(rb5_RB_(7, 5, 1, 2, 3, (RichBool::Get2Args<1,2>(RichBool::Equal<>()))), *an2);
}


//////////////////////////////////////////////////////////////////
// Get3Args

RB_TEST(Get3ArgsOf3)
{
	RB_PASS(rb3_RB_(1, 5, 7, (RichBool::Get3Args<1,2,3>(order3))));
	RB_FAIL(rb3_RB_(1, 5, 3, (RichBool::Get3Args<1,2,3>(order3))), *an3);
}

RB_TEST(Get3ArgsOf3_Reverse)
{
	RB_PASS(rb3_RB_(7, 5, 1, (RichBool::Get3Args<3,2,1>(order3))));
	RB_FAIL(rb3_RB_(3, 5, 1, (RichBool::Get3Args<3,2,1>(order3))), *an3);
}

RB_TEST(Get3ArgsOf4)
{
	RB_PASS(rb4_RB_(1, 5, 7, 2, (RichBool::Get3Args<1,2,3>(order3))));
	RB_FAIL(rb4_RB_(1, 5, 3, 2, (RichBool::Get3Args<1,2,3>(order3))), *an3);
}

RB_TEST(Get3ArgsOf4_Reverse)
{
	RB_PASS(rb4_RB_(7, 5, 1, 2, (RichBool::Get3Args<3,2,1>(order3))));
	RB_FAIL(rb4_RB_(3, 5, 1, 2, (RichBool::Get3Args<3,2,1>(order3))), *an3);
}

RB_TEST(Get3ArgsOf5)
{
	RB_PASS(rb5_RB_(1, 5, 7, 2, 3, (RichBool::Get3Args<1,2,3>(order3))));
	RB_FAIL(rb5_RB_(1, 5, 3, 2, 3, (RichBool::Get3Args<1,2,3>(order3))), *an3);
}



//////////////////////////////////////////////////////////////////
// Get4Args

RB_TEST(Get4ArgsOf4)
{
	RB_PASS(rb4_RB_(1, 3, 5, 7, (RichBool::Get4Args<1,2,3,4>(order4))));
	RB_FAIL(rb4_RB_(1, 5, 7, 3, (RichBool::Get4Args<1,2,3,4>(order4))), *an4);
}

RB_TEST(Get4ArgsOf4_Reverse)
{
	RB_PASS(rb4_RB_(7, 5, 3, 1, (RichBool::Get4Args<4,3,2,1>(order4))));
	RB_FAIL(rb4_RB_(3, 7, 5, 1, (RichBool::Get4Args<4,3,2,1>(order4))), *an4);
}

RB_TEST(Get4ArgsOf5)
{
	RB_PASS(rb5_RB_(1, 3, 5, 7, 0, (RichBool::Get4Args<1,2,3,4>(order4))));
	RB_FAIL(rb5_RB_(1, 5, 7, 3, 2, (RichBool::Get4Args<1,2,3,4>(order4))), *an4);
}

RB_TEST(Get4ArgsOf5_Reverse)
{
	RB_PASS(rb5_RB_(7, 5, 3, 1, 0, (RichBool::Get4Args<4,3,2,1>(order4))));
	RB_FAIL(rb5_RB_(3, 7, 5, 1, 2, (RichBool::Get4Args<4,3,2,1>(order4))), *an4);
}


#endif

//////////////////////////////////////////////////////////////////
// Get1Arg

RB_TEST(Alternative_Get1ArgOf2)
{
	RB_PASS(rb2_RB_(5, 9, RichBool::Get1Arg_<1>()(RichBool::Equals<int>(5))));
	RB_FAIL(rb2_RB_(7, 9, RichBool::Get1Arg_<1>()(RichBool::Equals<int>(5))), *an1);
}

RB_TEST(Alternative_Get1ArgOf3)
{
	RB_PASS(rb3_RB_(5, 9, 1, RichBool::Get1Arg_<1>()(RichBool::Equals<int>(5))));
	RB_FAIL(rb3_RB_(7, 9, 1, RichBool::Get1Arg_<1>()(RichBool::Equals<int>(5))), *an1);
}

RB_TEST(Alternative_Get1ArgOf4)
{
	RB_PASS(rb4_RB_(5, 9, 1, 2, RichBool::Get1Arg_<1>()(RichBool::Equals<int>(5))));
	RB_FAIL(rb4_RB_(7, 9, 1, 2, RichBool::Get1Arg_<1>()(RichBool::Equals<int>(5))), *an1);
}

RB_TEST(Alternative_Get1ArgOf5)
{
	RB_PASS(rb5_RB_(5, 9, 1, 2, 3, RichBool::Get1Arg_<1>()(RichBool::Equals<int>(5))));
	RB_FAIL(rb5_RB_(7, 9, 1, 2, 3, RichBool::Get1Arg_<1>()(RichBool::Equals<int>(5))), *an1);
}


//////////////////////////////////////////////////////////////////
// Get2Args

class MockFunctor
{
      int *m_array;
public:
       MockFunctor(int *arr): m_array(arr)
       {}
       bool operator()(int a, int b) const
       {
            m_array[0] = a;
            m_array[1] = b;
            return true;
       }
       bool operator()(int a, int b, int c) const
       {
            m_array[0] = a;
            m_array[1] = b;
            m_array[2] = c;
            return true;
       }
       bool operator()(int a, int b, int c, int d) const
       {
            m_array[0] = a;
            m_array[1] = b;
            m_array[2] = c;
            m_array[3] = d;
            return true;
       }
       bool operator()(int a, int b, int c, int d, int e) const
       {
            m_array[0] = a;
            m_array[1] = b;
            m_array[2] = c;
            m_array[3] = d;
            m_array[4] = e;
            return true;
       }
};


RB_TEST(Alternative_Get2ArgsOf2)
{
    int arr[2];
    MockFunctor f(arr);
	RichBool::Get2Args_<1,2>()(f)(2, 3);
	RB_ASSERT(rbEQUAL(arr[0], 2));
	RB_ASSERT(rbEQUAL(arr[1], 3));
}

RB_TEST(Alternative_Get2ArgsOf2_Reverse)
{
    int arr[2];
    MockFunctor f(arr);
	RichBool::Get2Args_<2,1>()(f)(2, 3);
	RB_ASSERT(rbEQUAL(arr[0], 3));
	RB_ASSERT(rbEQUAL(arr[1], 2));
}

RB_TEST(Alternative_Get2ArgsOf3)
{
    int arr[2];
    MockFunctor f(arr);
	RichBool::Get2Args_<1,2>()(f)(2, 3, 4);
	RB_ASSERT(rbEQUAL(arr[0], 2));
	RB_ASSERT(rbEQUAL(arr[1], 3));
}

RB_TEST(Alternative_Get2ArgsOf4)
{
    int arr[2];
    MockFunctor f(arr);
	RichBool::Get2Args_<1,2>()(f)(2, 3, 4, 5);
	RB_ASSERT(rbEQUAL(arr[0], 2));
	RB_ASSERT(rbEQUAL(arr[1], 3));
}

RB_TEST(Alternative_Get2ArgsOf5)
{
    int arr[2];
    MockFunctor f(arr);
	RichBool::Get2Args_<1,2>()(f)(2, 3, 4, 5, 6);
	RB_ASSERT(rbEQUAL(arr[0], 2));
	RB_ASSERT(rbEQUAL(arr[1], 3));
}


//////////////////////////////////////////////////////////////////
// Get3Args

RB_TEST(Alternative_Get3ArgsOf3)
{
    int arr[3];
    MockFunctor f(arr);
	RichBool::Get3Args_<1,2,3>()(f)(2, 3, 4);
	RB_ASSERT(rbEQUAL(arr[0], 2));
	RB_ASSERT(rbEQUAL(arr[1], 3));
	RB_ASSERT(rbEQUAL(arr[2], 4));
}

RB_TEST(Alternative_Get3ArgsOf3_Reverse)
{
    int arr[3];
    MockFunctor f(arr);
	RichBool::Get3Args_<3,2,1>()(f)(2, 3, 4);
	RB_ASSERT(rbEQUAL(arr[0], 4));
	RB_ASSERT(rbEQUAL(arr[1], 3));
	RB_ASSERT(rbEQUAL(arr[2], 2));
}

RB_TEST(Alternative_Get3ArgsOf4)
{
    int arr[3];
    MockFunctor f(arr);
	RichBool::Get3Args_<1,2,3>()(f)(2, 3, 4, 5);
	RB_ASSERT(rbEQUAL(arr[0], 2));
	RB_ASSERT(rbEQUAL(arr[1], 3));
	RB_ASSERT(rbEQUAL(arr[2], 4));
}

RB_TEST(Alternative_Get3ArgsOf4_Reverse)
{
    int arr[3];
    MockFunctor f(arr);
	RichBool::Get3Args_<3,2,1>()(f)(2, 3, 4, 5);
	RB_ASSERT(rbEQUAL(arr[0], 4));
	RB_ASSERT(rbEQUAL(arr[1], 3));
	RB_ASSERT(rbEQUAL(arr[2], 2));
}

RB_TEST(Alternative_Get3ArgsOf5)
{
    int arr[3];
    MockFunctor f(arr);
	RichBool::Get3Args_<1,2,3>()(f)(2, 3, 4, 5, 6);
	RB_ASSERT(rbEQUAL(arr[0], 2));
	RB_ASSERT(rbEQUAL(arr[1], 3));
	RB_ASSERT(rbEQUAL(arr[2], 4));
}



//////////////////////////////////////////////////////////////////
// Get4Args

RB_TEST(Alternative_Get4ArgsOf4)
{
    int arr[4];
    MockFunctor f(arr);
	RichBool::Get4Args_<1,2,3,4>()(f)(2, 3, 4, 5);
	RB_ASSERT(rbEQUAL(arr[0], 2));
	RB_ASSERT(rbEQUAL(arr[1], 3));
	RB_ASSERT(rbEQUAL(arr[2], 4));
	RB_ASSERT(rbEQUAL(arr[3], 5));
}

RB_TEST(Alternative_Get4ArgsOf4_Reverse)
{
    int arr[4];
    MockFunctor f(arr);
	RichBool::Get4Args_<4,3,2,1>()(f)(2, 3, 4, 5);
	RB_ASSERT(rbEQUAL(arr[0], 5));
	RB_ASSERT(rbEQUAL(arr[1], 4));
	RB_ASSERT(rbEQUAL(arr[2], 3));
	RB_ASSERT(rbEQUAL(arr[3], 2));
}

RB_TEST(Alternative_Get4ArgsOf5)
{
    int arr[4];
    MockFunctor f(arr);
	RichBool::Get4Args_<1,2,3,4>()(f)(2, 3, 4, 5, 6);
	RB_ASSERT(rbEQUAL(arr[0], 2));
	RB_ASSERT(rbEQUAL(arr[1], 3));
	RB_ASSERT(rbEQUAL(arr[2], 4));
	RB_ASSERT(rbEQUAL(arr[3], 5));
}

RB_TEST(Alternative_Get4ArgsOf5_Reverse)
{
    int arr[4];
    MockFunctor f(arr);
	RichBool::Get4Args_<4,3,2,1>()(f)(2, 3, 4, 5, 6);
	RB_ASSERT(rbEQUAL(arr[0], 5));
	RB_ASSERT(rbEQUAL(arr[1], 4));
	RB_ASSERT(rbEQUAL(arr[2], 3));
	RB_ASSERT(rbEQUAL(arr[3], 2));
}

