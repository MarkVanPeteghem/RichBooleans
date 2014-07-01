//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/richbool.hpp"
#include "richbool/functors.hpp"
#include "testable_analysis_for_ranges.hpp"
#include "count_calls.hpp"
#include "stdlib.h"


template <int n>
struct ModuloCore: public RichBool::FunctorCore
{
	bool operator()(int a, int b) const
	{
		return a%n==b%n;
	}

	const char* GetTextAfter1() const
	{ return " == "; }
	const char* GetTextAfter2() const
	{ return " mod n"; }
};

template <int n>
struct Modulo: public RichBool::Wrapper2Arg<ModuloCore<n> >
{
	Modulo(): RichBool::Wrapper2Arg<ModuloCore<n> >(RichBool::Value(), RichBool::Value())
	{}
};

RICHBOOL_WRAPPER2ARG_1CARG(Modulo2CountCalls, CountCallsCore<ModuloCore<2> >, int n, n)
RICHBOOL_WRAPPER2ARG_1CARG(Modulo3CountCalls, CountCallsCore<ModuloCore<3> >, int n, n)

struct EqualPCore: public RichBool::FunctorCore
{
	typedef unsigned int Points;

	bool operator()(int a, int b) const
	{
		return a==b;
	}

	const char* GetTextAfter1() const
	{
		return " == ";
	}

	Points GetPoints(int a, int b) const
	{
		int diff = abs(a-b);
		return diff > 10 ? 0 : 10-diff;
	}
	Points GetGood() const
	{
		return 10;
	}
};

struct EqualP: public RichBool::Wrapper2Arg<EqualPCore>
{
	EqualP(): RichBool::Wrapper2Arg<EqualPCore>(RichBool::Value(), RichBool::Value())
	{}
};

struct StubBoolCore: public RichBool::FunctorCore
{
	StubBoolCore(): b(false) {}

	bool b;

	bool operator()(int , int ) const
	{
		return b;
	}

	const char* GetText1() const
	{ return " stub "; }
};

struct StubBoolFunctor: public RichBool::Wrapper2Arg<StubBoolCore>
{
	StubBoolFunctor(): RichBool::Wrapper2Arg<StubBoolCore>(RichBool::Value(), RichBool::Value())
	{}

	void SetRV(bool b)
	{
		core.b = b;
	}
};

struct StubIntCore: public RichBool::FunctorCore
{
	StubIntCore(int good_): good(good_) {}

	int good, n;

	bool operator()(int , int ) const
	{
		return good==n;
	}

	const char* GetText1() const
	{ return " stub "; }
};

struct StubIntFunctor: public RichBool::Wrapper2Arg<StubIntCore>
{
	StubIntFunctor(int g): RichBool::Wrapper2Arg<StubIntCore>(StubIntCore(g), RichBool::Value(), RichBool::Value())
	{}

	typedef unsigned int Points;

	void SetRV(int n)
	{
		core.n = n;
	}

	Points GetPoints(int , int ) const
	{
		return core.n;
	}
	Points GetGood() const
	{
		return core.good;
	}
};


////////////////////////////////////////////////////////////
// Tests for And<...>

RB_TEST(And_Pass)
{
	RB_PASS(
		rb2_RB(1, 1, (EqualCountCalls<>(1) && EqualCountCalls<>(1)))
	);
}

RB_TEST(And_Fail_First)
{
	int a=1, b=2;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(false).expr("a", ":")("1", true)
		(" == ").expr("b", ":")("2", true);

	RichBool::SharedAnalysis cb =
		new RichBool::AndAnalysis(an1, new RichBool::AnalysisNotEvaluated);

	RB_FAIL(
		rb2_RB(a, b, (EqualCountCalls<>(1) && DiffCountCalls<>(0))),
		*cb);
}

RB_TEST(And_Fail_Second)
{
	int a=1, b=2;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(true).expr("a", ":")("1", true)
		(" != ").expr("b", ":")("2", true),
			*an2 = RichBool::MakeGeneralAnalysis(false).expr("a", ":")("1", true)
		(" == ").expr("b", ":")("2", true);

	RichBool::SharedAnalysis cb;
	if (RichBoolTest::GetLevel()==3)
		cb = new RichBool::AndAnalysis(an1, an2);
	else
		cb = new RichBool::AndAnalysis((RichBool::Analysis*)0, an2);

	RB_FAIL(
		rb2_RB(a, b, (DiffCountCalls<>(1) && EqualCountCalls<>(1))),
		*cb);
}

RB_TEST(And_Fail_Both)
{
	int a=1, b=2;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(false).expr("a", ":")("1", true)
		(" == ").expr("b", ":")("2", true);

	RichBool::SharedAnalysis cb =
		new RichBool::AndAnalysis(an1, new RichBool::AnalysisNotEvaluated);

	RB_FAIL(
		rb2_RB(a, b, (EqualCountCalls<>(1) && EqualCountCalls<>(0))),
		*cb);
}

RB_TEST(And_GetPoints_Bool_Bool)
{
	RichBool::And<StubBoolFunctor, StubBoolFunctor> functor;
	RB_ASSERT(rbEQUAL(functor.GetGood(),4u));

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),4)); // both match

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0)); // only first matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0)); // only second matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0)); // no matches
}

RB_TEST(And_GetPoints_Bool_Int)
{
	RichBool::And<StubBoolFunctor, StubIntFunctor>
		functor(StubBoolFunctor(), StubIntFunctor(10));
	RB_ASSERT(rbEQUAL(functor.GetGood(),20u));

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),20u)); // both match

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // only first matches

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(5);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only first matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // only second matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(5);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches
}

RB_TEST(And_GetPoints_Int_Bool)
{
	RichBool::And<StubIntFunctor, StubBoolFunctor>
		functor(StubIntFunctor(10), StubBoolFunctor());
	RB_ASSERT(rbEQUAL(functor.GetGood(),20u));

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),20u)); // both match

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // only first matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // only second matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // only second matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches
}

RB_TEST(And_GetPoints_Int_Int)
{
	RichBool::And<StubIntFunctor, StubIntFunctor>
		functor(StubIntFunctor(10), StubIntFunctor(20));
	RB_ASSERT(rbEQUAL(functor.GetGood(),200u));

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(20);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),200u)); // both match

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // only first matches

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),100u)); // only first matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(20);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // only second matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(20);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // only second matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches
}

RB_TEST(And_InArrays_Pass)
{
	int a[] = { 1, 2, 3 }, b[] = { 7, 8, 9 };

	RB_PASS(
		rbIN_ARRAYS(a, b,
			RichBool::Compare<>().That(Modulo2CountCalls<>(3) && Modulo3CountCalls<>(3))
		)
	);
}

RB_TEST(And_InArrays_Fail_First)
{
	int a[] = { 1, 2, 1 }, b[] = { 6 };

	RichBool::Analysis *arrAnalysis[] = {
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(0), true),
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(1), true),
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(2), true),
		new RichBool::Single(1, 2, "6", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"a", "b");
	analysis.AddAnalyses(arrAnalysis, 4);

	RB_FAIL(
		rbIN_ARRAYS(a, b,
			RichBool::Compare<>().That(Modulo<3>() && Modulo<2>())
		),
		analysis
	);
}

RB_TEST(And_InArrays_Fail_Second)
{
	int a[] = { 1, 2, 1 }, b[] = { 6 };

	RichBool::Analysis *arrAnalysis[] = {
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(0), true),
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(1), true),
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(2), true),
		new RichBool::Single(1, 2, "6", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"a", "b");
	analysis.AddAnalyses(arrAnalysis, 4);

	RB_FAIL(
		rbIN_ARRAYS(a, b,
			RichBool::Compare<>().That(Modulo<2>() && Modulo<3>())
		),
		analysis
	);
}

RB_TEST(And_Weight)
{
	RB_ASSERT(rbEQUAL((StubIntFunctor(10) && StubIntFunctor(10)).GetGood(), 100u));
	RB_ASSERT(rbEQUAL((StubIntFunctor(10) && StubIntFunctor(20)).GetGood(), 200u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(10) && StubIntFunctor(10) && StubIntFunctor(10)).GetGood(), 1000u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(10) && StubIntFunctor(10) && StubIntFunctor(20)).GetGood(), 2000u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(10) && StubIntFunctor(20) && StubIntFunctor(10)).GetGood(), 2000u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(20) && StubIntFunctor(10) && StubIntFunctor(10)).GetGood(), 2000u));
}

typedef EqualCountCalls<RichBool::Pointer<>, RichBool::Pointer<> > EqualDerefCount;

// with bad values

RB_TEST(And_Fail_FirstBad)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true);

	RichBool::SharedAnalysis cb =
		new RichBool::AndAnalysis(an1, new RichBool::AnalysisNotEvaluated);

	RB_FAIL(
		rb2_RB(p, pa, (EqualDerefCount(0) && EqualCountCalls<>(0))),
		*cb);
}

RB_TEST(And_Fail_SecondBad_FirstOk)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(true)
		.expr("p", ":")(RichBool::PtrToString(p), true)
		(" == ")
		.expr("p", ":")(RichBool::PtrToString(p), true),

		*an2 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ")
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false);

	RichBool::SharedAnalysis cb;
	if (RichBoolTest::GetLevel()==3)
		cb = new RichBool::AndAnalysis(an1, an2);
	else
		cb = new RichBool::AndAnalysis((RichBool::Analysis*)0, an2);

	RB_FAIL(
		rb2_RB(p, p, (EqualCountCalls<>(1) && EqualDerefCount(0))),
		*cb);
}

RB_TEST(And_Fail_SecondBad_FirstNok)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotOk)
		.expr("p", ":")(GetNullPtrString(), true)
		(" == ").expr("pa", ":")(RichBool::PtrToString(pa), true);

	RichBool::SharedAnalysis cb =
		new RichBool::AndAnalysis(an1, new RichBool::AnalysisNotEvaluated);

	RB_FAIL(
		rb2_RB(p, pa, (EqualCountCalls<>(1) && EqualDerefCount(0))),
		*cb);
}


////////////////////////////////////////////////////////////
// Tests for AndBoth<...>

RB_TEST(AndBoth_Pass)
{
	int a=1, b=1;
	RB_PASS(
		rb2_RB(a, b, (EqualCountCalls<>(1) && EqualCountCalls<>(1)))
	);
}

RB_TEST(AndBoth_Fail_First)
{
	int a=1, b=2;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(false).expr("a", ":")("1", true)
		(" == ").expr("b", ":")("2", true),
		*an2 = RichBool::MakeGeneralAnalysis(true).expr("a", ":")("1", true)
		(" != ").expr("b", ":")("2", true);

	RichBool::SharedAnalysis cb;
	if (RichBoolTest::GetLevel()==3)
		cb = new RichBool::AndAnalysis(an1, an2);
	else
		cb = new RichBool::AndAnalysis(an1, (RichBool::Analysis*)0);

	int nrCalls2 = RichBoolTest::GetLevel()==1 ? 0 : 1;
	RB_FAIL(
		rb2_RB(a, b, (EqualCountCalls<>(1) & DiffCountCalls<>(nrCalls2))),
		*cb);
}

RB_TEST(AndBoth_Fail_Second)
{
	int a=1, b=2;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(true).expr("a", ":")("1", true)
		(" != ").expr("b", ":")("2", true),
		*an2 = RichBool::MakeGeneralAnalysis(false).expr("a", ":")("1", true)
		(" == ").expr("b", ":")("2", true);

	RichBool::SharedAnalysis cb;
	if (RichBoolTest::GetLevel()==3)
		cb = new RichBool::AndAnalysis(an1, an2);
	else
		cb = new RichBool::AndAnalysis((RichBool::Analysis*)0, an2);

	RB_FAIL(
		rb2_RB(a, b, (DiffCountCalls<>(1) & EqualCountCalls<>(1))),
		*cb);
}

RB_TEST(AndBoth_Fail_Both)
{
	int a=1, b=2;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(false).expr("a", ":")("1", true)
		(" == ").expr("b", ":")("2", true);
	RichBool::Analysis *an2 = RichBool::MakeGeneralAnalysis(false).expr("a", ":")("1", true)
		(" == ").expr("b", ":")("2", true);

	RichBool::SharedAnalysis cb =
		new RichBool::AndAnalysis(an1, an2);

	int nrCalls2 = RichBoolTest::GetLevel()==1 ? 0 : 1;
	RB_FAIL(
		rb2_RB(a, b, (EqualCountCalls<>(1) & EqualCountCalls<>(nrCalls2))),
		*cb);
}

RB_TEST(AndBoth_GetPoints_Bool_Bool)
{
	RichBool::AndBoth<StubBoolFunctor, StubBoolFunctor> functor;
	RB_ASSERT(rbEQUAL(functor.GetGood(),4u));

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),4u)); // both match

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // only first matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // only second matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches
}

RB_TEST(AndBoth_GetPoints_Bool_Int)
{
	RichBool::AndBoth<StubBoolFunctor, StubIntFunctor>
		functor(StubBoolFunctor(), StubIntFunctor(10));
	RB_ASSERT(rbEQUAL(functor.GetGood(),20u));

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),20u)); // both match

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // only first matches

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(5);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only first matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // only second matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(5);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches
}

RB_TEST(AndBoth_GetPoints_Int_Bool)
{
	RichBool::AndBoth<StubIntFunctor, StubBoolFunctor>
		functor(StubIntFunctor(10), StubBoolFunctor());
	RB_ASSERT(rbEQUAL(functor.GetGood(),20u));

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),20u)); // both match

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // only first matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // only second matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only second matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches
}

RB_TEST(AndBoth_GetPoints_Int_Int)
{
	RichBool::AndBoth<StubIntFunctor, StubIntFunctor>
		functor(StubIntFunctor(10), StubIntFunctor(20));
	RB_ASSERT(rbEQUAL(functor.GetGood(),200u));

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(20);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),200u)); // both match

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // only first matches

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),100u)); // only first matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(20);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // only second matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(20);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),100u)); // only second matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),50u)); // no matches
}

RB_TEST(AndBoth_InArrays_Pass)
{
	int a[] = { 1, 2, 3 }, b[] = { 7, 8, 9 };

	RB_PASS(
		rbIN_ARRAYS(a, b,
			RichBool::Compare<>().That(Modulo<2>() & Modulo<3>())
		)
	);

}

RB_TEST(AndBoth_InArrays_Fail_First)
{
	int a[] = { 1, 2, 1 }, b[] = { 6 };

	RichBool::Analysis *arrAnalysis[] = {
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(0), true),
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(1), true),
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(2), true),
		new RichBool::Single(1, 2, "6", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"a", "b");
	analysis.AddAnalyses(arrAnalysis, 4);

	RB_FAIL(
		rbIN_ARRAYS(a, b,
			RichBool::Compare<>().That(Modulo<3>() & Modulo<2>())
		),
		analysis
	);
}

RB_TEST(AndBoth_InArrays_Fail_Second)
{
	int a[] = { 1, 2, 1 }, b[] = { 6 };

	RichBool::Analysis *arrAnalysis[] = {
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(0), true),
		new RichBool::Single(0, 2, "2", new RichBool::IndexExpression(1), true),
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(2), true),
		new RichBool::Single(1, 2, "6", new RichBool::IndexExpression(0), true)
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"a", "b");
	analysis.AddAnalyses(arrAnalysis, 4);

	RB_FAIL(
		rbIN_ARRAYS(a, b,
			RichBool::Compare<>().That(Modulo<2>() & Modulo<3>())
		),
		analysis
	);
}

RB_TEST(AndBoth_Weight)
{
	RB_ASSERT(rbEQUAL((StubIntFunctor(10) & StubIntFunctor(10)).GetGood(), 100u));
	RB_ASSERT(rbEQUAL((StubIntFunctor(10) & StubIntFunctor(20)).GetGood(), 200u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(10) & StubIntFunctor(10) & StubIntFunctor(10)).GetGood(), 1000u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(10) & StubIntFunctor(10) & StubIntFunctor(20)).GetGood(), 2000u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(10) & StubIntFunctor(20) & StubIntFunctor(10)).GetGood(), 2000u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(20) & StubIntFunctor(10) & StubIntFunctor(10)).GetGood(), 2000u));
}

// with bad values

RB_TEST(AndBoth_Fail_FirstBad)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true),
		*an2 = RichBool::MakeGeneralAnalysis(false)
		.expr("p", ":")(RichBool::PtrToString(p), true)
		(" == ").expr("pa", ":")(RichBool::PtrToString(pa), true);

	RichBool::SharedAnalysis cb =
		new RichBool::AndAnalysis(an1, an2);

	RB_FAIL(
		rb2_RB(p, pa, (EqualDerefCount(0) & EqualCountCalls<>(1))),
		*cb);
}

RB_TEST(AndBoth_Fail_SecondBad_FirstOk)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(true)
		.expr("p", ":")(RichBool::PtrToString(p), true)
		(" == ")
		.expr("p", ":")(RichBool::PtrToString(p), true),

		*an2 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ")
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false);

	RichBool::SharedAnalysis cb;
	if (RichBoolTest::GetLevel()==3)
		cb = new RichBool::AndAnalysis(an1, an2);
	else
		cb = new RichBool::AndAnalysis((RichBool::Analysis*)0, an2);

	RB_FAIL(
		rb2_RB(p, p, (EqualCountCalls<>(1) & EqualDerefCount(0))),
		*cb);
}

RB_TEST(AndBoth_Fail_SecondBad_FirstNok)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotOk)
		.expr("p", ":")(GetNullPtrString(), true)
		(" == ").expr("pa", ":")(RichBool::PtrToString(pa), true),
		*an2 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true);

	RichBool::SharedAnalysis cb =
		new RichBool::AndAnalysis(an1, an2);

	RB_FAIL(
		rb2_RB(p, pa, (EqualCountCalls<>(1) & EqualDerefCount(0))),
		*cb);
}



////////////////////////////////////////////////////////////
// Tests for Or<...>

RB_TEST(Or_Pass_Both)
{
	int a=1, b=2;
	RB_PASS(
		rb2_RB(a, b, (DiffCountCalls<>(1) || DiffCountCalls<>(0)))
	);
}

RB_TEST(Or_Pass_First)
{
	int a=1, b=2;
	RB_PASS(
		rb2_RB(a, b, (DiffCountCalls<>(1) || EqualCountCalls<>(0)))
	);
}

RB_TEST(Or_Pass_Second)
{
	int a=1, b=2;
	RB_PASS(
		rb2_RB(a, b, (EqualCountCalls<>(1) || DiffCountCalls<>(1)))
	);
}

RB_TEST(Or_Fail)
{
	int a=1, b=2;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(false).expr("a", ":")("1", true)
		(" >= ").expr("b", ":")("2", true);
	RichBool::Analysis *an2 = RichBool::MakeGeneralAnalysis(false).expr("a", ":")("1", true)
		(" > ").expr("b", ":")("2", true);

	RichBool::SharedAnalysis cb =
		new RichBool::OrAnalysis(an1, an2);

	RB_FAIL(
		rb2_RB(a, b, (RichBool::MoreOrEqual<>() || RichBool::More<>())),
		*cb);
}

RB_TEST(Or_GetPoints_Bool_Bool)
{
	RichBool::Or<StubBoolFunctor, StubBoolFunctor> functor;
	RB_ASSERT(rbEQUAL(functor.GetGood(),true));

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),true)); // both match

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),true)); // only first matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),true)); // only second matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),false)); // no matches
}

RB_TEST(Or_GetPoints_Bool_Int)
{
	RichBool::Or<StubBoolFunctor, StubIntFunctor>
		functor(StubBoolFunctor(), StubIntFunctor(10));
	RB_ASSERT(rbEQUAL(functor.GetGood(),10u));

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // both match

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only first matches

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(5);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only first matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only second matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(5);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),5u)); // no matches
}

RB_TEST(Or_GetPoints_Int_Bool)
{
	RichBool::Or<StubIntFunctor, StubBoolFunctor>
		functor(StubIntFunctor(10), StubBoolFunctor());
	RB_ASSERT(rbEQUAL(functor.GetGood(),10u));

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // both match

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only first matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only second matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only second matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),5u)); // no matches
}

RB_TEST(Or_GetPoints_Int_Int)
{
	RichBool::Or<StubIntFunctor, StubIntFunctor>
		functor(StubIntFunctor(10), StubIntFunctor(20));
	RB_ASSERT(rbEQUAL(functor.GetGood(),20u));

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(20);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),20u)); // both match

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),20u)); // only first matches

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),20u)); // only first matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(20);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),20u)); // only second matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(20);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),20u)); // only second matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // no matches
}

RB_TEST(Or_InArrays_Pass)
{
	int a[] = { 1, 2, 3 }, b[] = { 7, 4, 6 };

	RB_PASS(
		rbIN_ARRAYS(a, b,
			RichBool::Compare<>().That(Modulo<2>() || Modulo<3>())
		)
	);

}

RB_TEST(Or_InArrays_Fail_1)
{
	int a[] = { 1, 2, 1 }, b[] = { 6 };

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(false)
		.expr(new RichBool::IndexExpression(1), ":")("2", true)(" == ")
		.expr(new RichBool::IndexExpression(0), ":")("6", true)(" mod n");

	RichBool::Analysis *an2 = RichBool::MakeGeneralAnalysis(false)
		.expr(new RichBool::IndexExpression(1), ":")("2", true)(" == ")
		.expr(new RichBool::IndexExpression(0), ":")("6", true);

	RichBool::Analysis *arrAnalysis[] = {
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(0), true),
		new RichBool::AndAnalysis(an1, an2),
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(2), true)
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"a", "b");
	analysis.AddAnalyses(arrAnalysis, 3);

	RB_FAIL(
		rbIN_ARRAYS(a, b,
			RichBool::Compare<>().That(Modulo<3>() || EqualP())
		),
		analysis
	);
}

RB_TEST(Or_InArrays_Fail_2)
{
	int a[] = { 1, 2, 1 }, b[] = { 6 };

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(false)
		.expr(new RichBool::IndexExpression(1), ":")("2", true)(" == ")
		.expr(new RichBool::IndexExpression(0), ":")("6", true)(" mod n");

	RichBool::Analysis *an2 = RichBool::MakeGeneralAnalysis(false)
		.expr(new RichBool::IndexExpression(1), ":")("2", true)(" == ")
		.expr(new RichBool::IndexExpression(0), ":")("6", true);

	RichBool::Analysis *arrAnalysis[] = {
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(0), true),
		new RichBool::AndAnalysis(an2, an1),
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(2), true)
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"a", "b");
	analysis.AddAnalyses(arrAnalysis, 3);

	RB_FAIL(
		rbIN_ARRAYS(a, b,
			RichBool::Compare<>().That(EqualP() || Modulo<3>())
		),
		analysis
	);
}

RB_TEST(Or_Weight)
{
	RB_ASSERT(rbEQUAL((StubIntFunctor(10) || StubIntFunctor(10)).GetGood(), 10u));
	RB_ASSERT(rbEQUAL((StubIntFunctor(10) || StubIntFunctor(20)).GetGood(), 20u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(10) || StubIntFunctor(10) || StubIntFunctor(10)).GetGood(), 10u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(10) || StubIntFunctor(10) || StubIntFunctor(20)).GetGood(), 20u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(10) || StubIntFunctor(20) || StubIntFunctor(10)).GetGood(), 20u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(20) || StubIntFunctor(10) || StubIntFunctor(10)).GetGood(), 20u));
}


// with bad values

RB_TEST(Or_Fail_FirstBad)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true);

	RichBool::SharedAnalysis cb =
		new RichBool::OrAnalysis(an1, new RichBool::AnalysisNotEvaluated);

	RB_FAIL(
		rb2_RB(p, pa, (EqualDerefCount(0) || EqualCountCalls<>(0))),
		*cb);
}

RB_TEST(Or_Fail_SecondBad_FirstOk)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int *p=0;

	RB_PASS(rb2_RB(p, p, (EqualCountCalls<>(1) || EqualDerefCount(0))));
}

RB_TEST(Or_Fail_SecondBad_FirstNok)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotOk)
		.expr("p", ":")(GetNullPtrString(), true)
		(" == ").expr("pa", ":")(RichBool::PtrToString(pa), true),
		*an2 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true);

	RichBool::SharedAnalysis cb =
		new RichBool::OrAnalysis(an1, an2);

	RB_FAIL(
		rb2_RB(p, pa, (RichBool::Equal<>() || EqualDerefCount(0))),
		*cb);
}


////////////////////////////////////////////////////////////
// Tests for OrBoth<...>

RB_TEST(OrBoth_Pass_Both)
{
	int a=1, b=2;
	int nrCalls2 = RichBoolTest::GetLevel()==3 ? 1 : 0;
	RB_PASS(
		rb2_RB(a, b, (DiffCountCalls<>(1) | DiffCountCalls<>(nrCalls2)))
	);
}

RB_TEST(OrBoth_Pass_First)
{
	int a=1, b=2;
	int nrCalls2 = RichBoolTest::GetLevel()==3 ? 1 : 0;
	RB_PASS(
		rb2_RB(a, b, (DiffCountCalls<>(1) | EqualCountCalls<>(nrCalls2)))
	);
}

RB_TEST(OrBoth_Pass_Second)
{
	int a=1, b=2;
	RB_PASS(
		rb2_RB(a, b, (EqualCountCalls<>(1) | DiffCountCalls<>(1)))
	);
}

RB_TEST(OrBoth_Fail)
{
	int a=1, b=2;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(false).expr("a", ":")("1", true)
		(" >= ").expr("b", ":")("2", true);
	RichBool::Analysis *an2 = RichBool::MakeGeneralAnalysis(false).expr("a", ":")("1", true)
		(" > ").expr("b", ":")("2", true);

	RichBool::SharedAnalysis cb =
		new RichBool::OrAnalysis(an1, an2);

	RB_FAIL(
		rb2_RB(a, b, (RichBool::MoreOrEqual<>() | RichBool::More<>())),
		*cb);
}

RB_TEST(OrBoth_GetPoints_Bool_Bool)
{
	RichBool::OrBoth<StubBoolFunctor, StubBoolFunctor> functor;
	RB_ASSERT(rbEQUAL(functor.GetGood(),true));

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),true)); // both match

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),true)); // only first matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),true)); // only second matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),false)); // no matches
}

RB_TEST(OrBoth_GetPoints_Bool_Int)
{
	RichBool::OrBoth<StubBoolFunctor, StubIntFunctor>
		functor(StubBoolFunctor(), StubIntFunctor(10));
	RB_ASSERT(rbEQUAL(functor.GetGood(),10u));

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // both match

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only first matches

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(5);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only first matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only second matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(5);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),5u)); // no matches
}

RB_TEST(OrBoth_GetPoints_Int_Bool)
{
	RichBool::OrBoth<StubIntFunctor, StubBoolFunctor>
		functor(StubIntFunctor(10), StubBoolFunctor());
	RB_ASSERT(rbEQUAL(functor.GetGood(),10u));

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // both match

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only first matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only second matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only second matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),5u)); // no matches
}

RB_TEST(OrBoth_GetPoints_Int_Int)
{
	RichBool::OrBoth<StubIntFunctor, StubIntFunctor>
		functor(StubIntFunctor(10), StubIntFunctor(20));
	RB_ASSERT(rbEQUAL(functor.GetGood(),20u));

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(20);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),20u)); // both match

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),20u)); // only first matches

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),20u)); // only first matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(20);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),20u)); // only second matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(20);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),20u)); // only second matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // no matches
}

RB_TEST(OrBoth_InArrays_Pass)
{
	int a[] = { 1, 2, 3 }, b[] = { 7, 4, 6 };

	RB_PASS(
		rbIN_ARRAYS(a, b,
			RichBool::Compare<>().That(Modulo<2>() | Modulo<3>())
		)
	);
}

RB_TEST(OrBoth_InArrays_Fail_1)
{
	int a[] = { 1, 2, 1 }, b[] = { 6 };

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(false)
		.expr(new RichBool::IndexExpression(1), ":")("2", true)(" == ")
		.expr(new RichBool::IndexExpression(0), ":")("6", true)(" mod n");

	RichBool::Analysis *an2 = RichBool::MakeGeneralAnalysis(false)
		.expr(new RichBool::IndexExpression(1), ":")("2", true)(" == ")
		.expr(new RichBool::IndexExpression(0), ":")("6", true);

	RichBool::Analysis *arrAnalysis[] = {
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(0), true),
		new RichBool::AndAnalysis(an1, an2),
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(2), true)
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"a", "b");
	analysis.AddAnalyses(arrAnalysis, 3);

	RB_FAIL(
		rbIN_ARRAYS(a, b,
			RichBool::Compare<>().That(Modulo<3>() | EqualP())
		),
		analysis
	);
}

RB_TEST(OrBoth_InArrays_Fail_2)
{
	int a[] = { 1, 2, 1 }, b[] = { 6 };

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(false)
		.expr(new RichBool::IndexExpression(1), ":")("2", true)(" == ")
		.expr(new RichBool::IndexExpression(0), ":")("6", true)(" mod n");

	RichBool::Analysis *an2 = RichBool::MakeGeneralAnalysis(false)
		.expr(new RichBool::IndexExpression(1), ":")("2", true)(" == ")
		.expr(new RichBool::IndexExpression(0), ":")("6", true);

	RichBool::Analysis *arrAnalysis[] = {
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(0), true),
		new RichBool::AndAnalysis(an2, an1),
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(2), true)
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"a", "b");
	analysis.AddAnalyses(arrAnalysis, 3);

	RB_FAIL(
		rbIN_ARRAYS(a, b,
			RichBool::Compare<>().That(EqualP() | Modulo<3>())
		),
		analysis
	);
}

RB_TEST(OrBoth_Weight)
{
	RB_ASSERT(rbEQUAL((StubIntFunctor(10) | StubIntFunctor(10)).GetGood(), 10u));
	RB_ASSERT(rbEQUAL((StubIntFunctor(10) | StubIntFunctor(20)).GetGood(), 20u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(10) | StubIntFunctor(10) | StubIntFunctor(10)).GetGood(), 10u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(10) | StubIntFunctor(10) | StubIntFunctor(20)).GetGood(), 20u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(10) | StubIntFunctor(20) | StubIntFunctor(10)).GetGood(), 20u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(20) | StubIntFunctor(10) | StubIntFunctor(10)).GetGood(), 20u));
}

// with bad values

RB_TEST(OrBoth_Fail_FirstBad)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true),
		*an2 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotOk)
		.expr("p", ":")(GetNullPtrString(), true)
		(" == ").expr("pa", ":")(RichBool::PtrToString(pa), true);

	RichBool::SharedAnalysis cb =
		new RichBool::OrAnalysis(an1, an2);

	RB_FAIL(
		rb2_RB(p, pa, (EqualDerefCount(0) | EqualCountCalls<>(1))),
		*cb);
}

RB_TEST(OrBoth_Fail_SecondBad_FirstOk)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::Ok)
		.expr("p", ":")(GetNullPtrString(), true)
		(" == ").expr("p", ":")(GetNullPtrString(), true),
		*an2 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ")
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false);

	RichBool::SharedAnalysis cb =
		new RichBool::OrAnalysis(an1, an2);

	if (RichBoolTest::GetLevel()!=3)
		RB_PASS(rb2_RB(p, p, (EqualCountCalls<>(1) | EqualDerefCount(0))));
	else
		RB_FAIL(rb2_RB(p, p, (EqualCountCalls<>(1) | EqualDerefCount(0))), *cb);
}

RB_TEST(OrBoth_Fail_SecondBad_FirstNok)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotOk)
		.expr("p", ":")(GetNullPtrString(), true)
		(" == ").expr("pa", ":")(RichBool::PtrToString(pa), true),
		*an2 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true);

	RichBool::SharedAnalysis cb =
		new RichBool::OrAnalysis(an1, an2);

	RB_FAIL(
		rb2_RB(p, pa, (RichBool::Equal<>() | EqualDerefCount(0))),
		*cb);
}


////////////////////////////////////////////////////////////
// Tests for Xor<...>

RB_TEST(Xor_Pass_First)
{
	int a=1, b=2;
	RB_PASS(
		rb2_RB(a, b, (DiffCountCalls<>(1) ^ EqualCountCalls<>(1)))
	);
}

RB_TEST(Xor_Pass_Second)
{
	int a=1, b=2;
	RB_PASS(
		rb2_RB(a, b, (DiffCountCalls<>(1) ^ EqualCountCalls<>(1)))
	);
}

RB_TEST(Xor_Pass_Both)
{
	int a=1, b=2;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(true).expr("a", ":")("1", true)
		(" < ").expr("b", ":")("2", true);
	RichBool::Analysis *an2 = RichBool::MakeGeneralAnalysis(true).expr("a", ":")("1", true)
		(" <= ").expr("b", ":")("2", true);

	RichBool::SharedAnalysis cb =
		new RichBool::XorAnalysis(an1, an2);

	RB_FAIL(
		rb2_RB(a, b, (RichBool::Less<>() ^ RichBool::LessOrEqual<>())),
		*cb);
}

RB_TEST(Xor_Pass_None)
{
	int a=1, b=2;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(false).expr("a", ":")("1", true)
		(" > ").expr("b", ":")("2", true);
	RichBool::Analysis *an2 = RichBool::MakeGeneralAnalysis(false).expr("a", ":")("1", true)
		(" >= ").expr("b", ":")("2", true);

	RichBool::SharedAnalysis cb =
		new RichBool::XorAnalysis(an1, an2);

	RB_FAIL(
		rb2_RB(a, b, (RichBool::More<>() ^ RichBool::MoreOrEqual<>())),
		*cb);
}

RB_TEST(Xor_GetPoints_Bool_Bool)
{
	RichBool::Xor<StubBoolFunctor, StubBoolFunctor> functor;
	RB_ASSERT(rbEQUAL(functor.GetGood(),true));

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),false)); // both match

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),true)); // only first matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),true)); // only second matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),false)); // no matches
}

RB_TEST(Xor_GetPoints_Bool_Int)
{
	RichBool::Xor<StubBoolFunctor, StubIntFunctor>
		functor(StubBoolFunctor(), StubIntFunctor(10));
	RB_ASSERT(rbEQUAL(functor.GetGood(),10u));

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // both match

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only first matches

	functor.rb1.SetRV(true);
	functor.rb2.SetRV(5);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only first matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only second matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches

	functor.rb1.SetRV(false);
	functor.rb2.SetRV(5);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),5u)); // no matches
}

RB_TEST(Xor_GetPoints_Int_Bool)
{
	RichBool::Xor<StubIntFunctor, StubBoolFunctor>
		functor(StubIntFunctor(10), StubBoolFunctor());
	RB_ASSERT(rbEQUAL(functor.GetGood(),10u));

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // both match

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only first matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only second matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(true);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // only second matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(false);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),5u)); // no matches
}

RB_TEST(Xor_GetPoints_Int_Int)
{
	RichBool::Xor<StubIntFunctor, StubIntFunctor>
		functor(StubIntFunctor(10), StubIntFunctor(20));
	RB_ASSERT(rbEQUAL(functor.GetGood(),20u));

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(20);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // both match

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),20u)); // only first matches

	functor.rb1.SetRV(10);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),20u)); // only first matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(20);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),20u)); // only second matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(20);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),20u)); // only second matches

	functor.rb1.SetRV(0);
	functor.rb2.SetRV(0);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),0u)); // no matches

	functor.rb1.SetRV(5);
	functor.rb2.SetRV(10);
	RB_ASSERT(rbEQUAL(functor.GetPoints(1,1),10u)); // no matches
}

RB_TEST(XorBoth_InArrays_Pass)
{
	int a[] = { 1, 2, 3 }, b[] = { 4, 4, 6 };

	RB_PASS(
		rbIN_ARRAYS(a, b,
			RichBool::Compare<>().That(Modulo<2>() ^ Modulo<3>())
		)
	);
}

RB_TEST(XorBoth_InArrays_Fail)
{
	int a[] = { 1, 2, 1 }, b[] = { 6 };

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(false)
		.expr(new RichBool::IndexExpression(1), ":")("2", true)(" == ")
		.expr(new RichBool::IndexExpression(0), ":")("6", true)(" mod n");

	RichBool::Analysis *an2 = RichBool::MakeGeneralAnalysis(false)
		.expr(new RichBool::IndexExpression(1), ":")("2", true)(" == ")
		.expr(new RichBool::IndexExpression(0), ":")("6", true);

	RichBool::Analysis *arrAnalysis[] = {
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(0), true),
		new RichBool::XorAnalysis(an2, an1),
		new RichBool::Single(0, 2, "1", new RichBool::IndexExpression(2), true)
	};

	TestableAnalysisOfContainers analysis(
		"predicate applies to ranges ",
		"a", "b");
	analysis.AddAnalyses(arrAnalysis, 3);

	RB_FAIL(
		rbIN_ARRAYS(a, b,
			RichBool::Compare<>().That(EqualP() ^ Modulo<3>())
		),
		analysis
	);
}

RB_TEST(Xor_Weight)
{
	RB_ASSERT(rbEQUAL((StubIntFunctor(10) ^ StubIntFunctor(10)).GetGood(), 10u));
	RB_ASSERT(rbEQUAL((StubIntFunctor(10) ^ StubIntFunctor(20)).GetGood(), 20u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(10) ^ StubIntFunctor(10) ^ StubIntFunctor(10)).GetGood(), 10u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(10) ^ StubIntFunctor(10) ^ StubIntFunctor(20)).GetGood(), 20u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(10) ^ StubIntFunctor(20) ^ StubIntFunctor(10)).GetGood(), 20u));
	RB_ASSERT(rbEQUAL(
		(StubIntFunctor(20) ^ StubIntFunctor(10) ^ StubIntFunctor(10)).GetGood(), 20u));
}

// with bad values

RB_TEST(Xor_Fail_FirstBad_SecondOk)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true);

	RichBool::SharedAnalysis cb=new RichBool::XorAnalysis(an1, new RichBool::AnalysisNotEvaluated);

	RB_FAIL(
		rb2_RB(p, pa, (EqualDerefCount(0) ^ DiffCountCalls<>(0))),
		*cb);
}

RB_TEST(Xor_Fail_FirstBad_SecondNotOk)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true);

	RichBool::SharedAnalysis cb=new RichBool::XorAnalysis(an1, new RichBool::AnalysisNotEvaluated);

	RB_FAIL(
		rb2_RB(p, pa, (EqualDerefCount(0) ^ EqualCountCalls<>(0))),
		*cb);
}

RB_TEST(Xor_Fail_SecondBad_FirstOk)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::Ok)
		.expr("p", ":")(GetNullPtrString(), true)
		(" != ").expr("pa", ":")(RichBool::PtrToString(pa), true),
		*an2 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true);

	RichBool::SharedAnalysis cb =
		new RichBool::XorAnalysis(an1, an2);

	RB_FAIL(
		rb2_RB(p, pa, (RichBool::Diff<>() ^ EqualDerefCount(0))),
		*cb);
}

RB_TEST(Xor_Fail_SecondBad_FirstNotOk)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotOk)
		.expr("p", ":")(GetNullPtrString(), true)
		(" == ").expr("pa", ":")(RichBool::PtrToString(pa), true),
		*an2 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true);

	RichBool::SharedAnalysis cb =
		new RichBool::XorAnalysis(an1, an2);

	RB_FAIL(
		rb2_RB(p, pa, (RichBool::Equal<>() ^ EqualDerefCount(0))),
		*cb);
}


///////////////////////////////////////////////////////////
// other tests

RB_TEST(SelectType)
{
	RB_ASSERT(rbEQUAL(sizeof(RichBool::detail::UsePoints<bool, bool>::Type), sizeof(bool)));
	RB_ASSERT(rbEQUAL(sizeof(RichBool::detail::UsePoints<bool, short>::Type), sizeof(short)));
	RB_ASSERT(rbEQUAL(sizeof(RichBool::detail::UsePoints<bool, int>::Type), sizeof(int)));
	RB_ASSERT(rbEQUAL(sizeof(RichBool::detail::UsePoints<short, bool>::Type), sizeof(short)));
	RB_ASSERT(rbEQUAL(sizeof(RichBool::detail::UsePoints<short, short>::Type), sizeof(short)));
	RB_ASSERT(rbEQUAL(sizeof(RichBool::detail::UsePoints<short, int>::Type), sizeof(int)));
	RB_ASSERT(rbEQUAL(sizeof(RichBool::detail::UsePoints<int, bool>::Type), sizeof(int)));
	RB_ASSERT(rbEQUAL(sizeof(RichBool::detail::UsePoints<int, short>::Type), sizeof(int)));
	RB_ASSERT(rbEQUAL(sizeof(RichBool::detail::UsePoints<int, int>::Type), sizeof(int)));
}


// test for negating functors derived from FunctorCore:

RB_TEST(NotLess)
{
	RB_PASS(rb2_RB(2,1, !RichBool::Less<>()));
}

RB_TEST(NotNotLess)
{
	RB_PASS(rb2_RB(1,2, !!RichBool::Less<>()));
}

RB_TEST(NotLess_Fail)
{
	RichBool::SharedAnalysis analysisLess =
		(RichBool::Analysis*)RichBool::MakeGeneralAnalysis(true).expr("1", ":")("1", true)(" < ")
			.expr("2", ":")("2", true).neg();
	RB_FAIL(rb2_RB(1,2, !RichBool::Less<>()), *analysisLess);
}

RB_TEST(NotNotLess_Fail)
{
	RichBool::SharedAnalysis analysisLess =
		(RichBool::Analysis*)RichBool::MakeGeneralAnalysis(false).expr("2", ":")("2", true)(" < ")
			.expr("1", ":")("1", true);
	RB_FAIL(rb2_RB(2,1, !!RichBool::Less<>()), *analysisLess);
}

// test for negating functors derived from CustomFunctorCore<false>:

RB_TEST(NotEqualBitwise)
{
	RB_PASS(rb2_RB(1,2, !RichBool::EqualBitwise<>()));
}

RB_TEST(NotNotEqualBitwise)
{
	RB_PASS(rb2_RB(2,2, !!RichBool::EqualBitwise<>()));
}

RB_TEST(NotEqualBitwise_Fail)
{
	RichBool::BriefAnalysisOfTwoSequences analysis(true, new RichBool::TextExpression("3"), new RichBool::TextExpression("3"),
		"", " .==. ", "");
	analysis.SetString1   ("00000011000000000000000000000000");
	analysis.SetString2   ("00000011000000000000000000000000");
	analysis.SetStringDiff("                                ");
	analysis.SetBlockSize(8);
	analysis.SetBlocksPerLine(8);
	analysis.Negate();

	RB_FAIL(rb2_RB(3,3, !RichBool::EqualBitwise<>()), analysis);
}

RB_TEST(NotNotEqualBitwise_Fail)
{
	RichBool::BriefAnalysisOfTwoSequences analysis(false, new RichBool::TextExpression("1"), new RichBool::TextExpression("3"),
		"", " .==. ", "");
	analysis.SetString1   ("00000001000000000000000000000000");
	analysis.SetString2   ("00000011000000000000000000000000");
	analysis.SetStringDiff("      X                         ");
	analysis.SetBlockSize(8);
	analysis.SetBlocksPerLine(8);

	RB_FAIL(rb2_RB(1,3, !!RichBool::EqualBitwise<>()), analysis);
}

////////////////////////////////////////////////////////////
// Tests for Not<And<...>>

RB_TEST(NotAnd_Pass_FirstFail)
{
	RB_PASS(
		rb2_RB(1, 2, !(RichBool::Equal<>() && RichBool::Less<>()))
	);
}

RB_TEST(NotAnd_Pass_SecondFail)
{
	RB_PASS(
		rb2_RB(1, 1, !(RichBool::Equal<>() && RichBool::Less<>()))
	);
}

RB_TEST(NotAnd_Fail)
{
	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(true).expr("1", ":")("1", true)
		(" < ").expr("2", ":")("2", true),
		*an2 = RichBool::MakeGeneralAnalysis(true).expr("1", ":")("1", true)
		(" <= ").expr("2", ":")("2", true);

	RichBool::AndAnalysis *an = new RichBool::AndAnalysis(an1, an2);
	an->Negate();
	RichBool::SharedAnalysis cb = an;

	RB_FAIL(
		rb2_RB(1, 2, !(RichBool::Less<>() && RichBool::LessOrEqual<>())),
		*cb);
}

// with bad values

RB_TEST(NotAnd_Fail_FirstBad)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true);

	RichBool::Analysis *cb =
		new RichBool::AndAnalysis(an1, new RichBool::AnalysisNotEvaluated);
	cb->Negate();

	RB_FAIL(
		rb2_RB(p, pa, !(EqualDerefCount(0) && EqualCountCalls<>(0))),
		*cb);

	delete cb;
}

RB_TEST(NotAnd_Fail_SecondBad_FirstOk)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(true)
		.expr("p", ":")(RichBool::PtrToString(p), true)
		(" == ")
		.expr("p", ":")(RichBool::PtrToString(p), true),

		*an2 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ")
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false);

	RichBool::Analysis *cb;
	if (RichBoolTest::GetLevel()==3)
		cb = new RichBool::AndAnalysis(an1, an2);
	else
		cb = new RichBool::AndAnalysis((RichBool::Analysis*)0, an2);
	cb->Negate();

	RB_FAIL(
		rb2_RB(p, p, !(RichBool::Equal<>() && EqualDerefCount(0))),
		*cb);

	delete cb;
}

RB_TEST(NotAnd_Pass_SecondBad_FirstNok)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RB_PASS(rb2_RB(p, pa, !(EqualCountCalls<>(1) && EqualDerefCount(0))));
}


////////////////////////////////////////////////////////////
// Tests for Not<AndBoth<...>>

RB_TEST(NotAndBoth_Pass_FirstFail)
{
	RB_PASS(
		rb2_RB(1, 2, !(RichBool::Equal<>() & RichBool::Less<>()))
	);
}

RB_TEST(NotAndBoth_Pass_SecondFail)
{
	RB_PASS(
		rb2_RB(1, 1, !(RichBool::Equal<>() & RichBool::Less<>()))
	);
}

RB_TEST(NotAndBoth_Pass_BothFail)
{
	RB_PASS(
		rb2_RB(2, 1, !(RichBool::Equal<>() & RichBool::Less<>()))
	);
}

RB_TEST(NotAndBoth_Fail)
{
	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(true).expr("1", ":")("1", true)
		(" < ").expr("2", ":")("2", true),
		*an2 = RichBool::MakeGeneralAnalysis(true).expr("1", ":")("1", true)
		(" <= ").expr("2", ":")("2", true);

	RichBool::AndAnalysis *an = new RichBool::AndAnalysis(an1, an2);
	an->Negate();
	RichBool::SharedAnalysis cb = an;

	RB_FAIL(
		rb2_RB(1, 2, !(RichBool::Less<>() & RichBool::LessOrEqual<>())),
		*cb);
}

// with bad values

RB_TEST(NotAndBoth_Fail_FirstBad)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true),
		*an2 = RichBool::MakeGeneralAnalysis(false)
		.expr("p", ":")(RichBool::PtrToString(p), true)
		(" == ").expr("pa", ":")(RichBool::PtrToString(pa), true);

	RichBool::Analysis *cb =
		new RichBool::AndAnalysis(an1, an2);
	cb->Negate();

	RB_FAIL(
		rb2_RB(p, pa, !(EqualDerefCount(0) & RichBool::Equal<>())),
		*cb);

	delete cb;
}

RB_TEST(NotAndBoth_Fail_SecondBad_FirstOk)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(true)
		.expr("p", ":")(RichBool::PtrToString(p), true)
		(" == ")
		.expr("p", ":")(RichBool::PtrToString(p), true),

		*an2 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ")
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false);

	RichBool::Analysis *cb = new RichBool::AndAnalysis(an1, an2);
	cb->Negate();

	RB_FAIL(
		rb2_RB(p, p, !(RichBool::Equal<>() & EqualDerefCount(0))),
		*cb);

	delete cb;
}

RB_TEST(NotAndBoth_Fail_SecondBad_FirstNok)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(false)
		.expr("p", ":")(RichBool::PtrToString(p), true)
		(" == ")
		.expr("pa", ":")(RichBool::PtrToString(pa), true),

		*an2 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ")
		.pexpr("*", "pa", ":")("1", true);

	RichBool::Analysis *cb = new RichBool::AndAnalysis(an1, an2);
	cb->Negate();

	if (RichBoolTest::GetLevel()==3)
		RB_FAIL(rb2_RB(p, pa, !(EqualCountCalls<>(1) & EqualDerefCount(0))), *cb);
	else
		RB_PASS(rb2_RB(p, pa, !(EqualCountCalls<>(1) & EqualDerefCount(0))));

	delete cb;
}


////////////////////////////////////////////////////////////
// Tests for Not<Or<...>>

RB_TEST(NotOr_Pass)
{
	RB_PASS(
		rb2_RB(1, 2, !(EqualCountCalls<>(1) || EqualCountCalls<>(1)))
	);
}

RB_TEST(NotOr_Fail_First)
{
	int a=1, b=2;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(false).expr("a", ":")("1", true)
		(" == ").expr("b", ":")("2", true),
		*an2 = RichBool::MakeGeneralAnalysis(true).expr("a", ":")("1", true)
		(" != ").expr("b", ":")("2", true);

	RichBool::Analysis *cb;
	if (RichBoolTest::GetLevel()==3)
		cb = new RichBool::OrAnalysis(an1, an2);
	else
		cb = new RichBool::OrAnalysis(RichBool::Bool(false), an2);
	cb->Negate();

	RB_FAIL(
		rb2_RB(a, b, !(EqualCountCalls<>(1) || DiffCountCalls<>(1))),
		*cb);
	delete cb;
}

RB_TEST(NotOr_Fail_Second)
{
	int a=1, b=2;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(true).expr("a", ":")("1", true)
		(" != ").expr("b", ":")("2", true);

	RichBool::Analysis *cb = new RichBool::OrAnalysis(an1, new RichBool::AnalysisNotEvaluated);
	cb->Negate();

	RB_FAIL(
		rb2_RB(a, b, !(DiffCountCalls<>(1) || EqualCountCalls<>(0))),
		*cb);

	delete cb;
}

RB_TEST(NotOr_Fail_Both)
{
	int a=1, b=1;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(true).expr("a", ":")("1", true)
		(" == ").expr("b", ":")("1", true);

	RichBool::Analysis *cb =
		new RichBool::OrAnalysis(an1, new RichBool::AnalysisNotEvaluated);
	cb->Negate();

	RB_FAIL(
		rb2_RB(a, b, !(EqualCountCalls<>(1) || EqualCountCalls<>(0))),
		*cb);

	delete cb;
}

// with bad values

RB_TEST(NotOr_Fail_FirstBad)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true);

	RichBool::Analysis *cb = new RichBool::OrAnalysis(an1, new RichBool::AnalysisNotEvaluated);
	cb->Negate();

	RB_FAIL(
		rb2_RB(p, pa, !(EqualDerefCount(0) || EqualCountCalls<>(0))),
		*cb);

	delete cb;
}

RB_TEST(NotOr_Fail_SecondBad_FirstOk)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::Ok)
		.expr("p", ":")(GetNullPtrString(), true)
		(" == ").expr("p", ":")(GetNullPtrString(), true);

	RichBool::Analysis *cb = new RichBool::OrAnalysis(an1, new RichBool::AnalysisNotEvaluated);
	cb->Negate();

	RB_FAIL(rb2_RB(p, p, !(EqualCountCalls<>(1) || EqualDerefCount(0))), *cb);

	delete cb;
}

RB_TEST(NotOr_Fail_SecondBad_FirstNok)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotOk)
		.expr("p", ":")(GetNullPtrString(), true)
		(" == ").expr("pa", ":")(RichBool::PtrToString(pa), true),
		*an2 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true);

	RichBool::Analysis *cb;
	if (RichBoolTest::GetLevel()==3)
		cb = new RichBool::OrAnalysis(an1, an2);
	else
		cb = new RichBool::OrAnalysis(RichBool::Bool(false), an2);
	cb->Negate();

	RB_FAIL(
		rb2_RB(p, pa, !(RichBool::Equal<>() || EqualDerefCount(0))),
		*cb);

	delete cb;
}


////////////////////////////////////////////////////////////
// Tests for Not<OrBoth<...>>

RB_TEST(NotOrBoth_Pass)
{
	int a=1, b=2;
	RB_PASS(
		rb2_RB(a, b, !(EqualCountCalls<>(1) | EqualCountCalls<>(1)))
	);
}

RB_TEST(NotOrBoth_Fail_First)
{
	int a=1, b=2;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(false).expr("a", ":")("1", true)
		(" == ").expr("b", ":")("2", true),
		*an2 = RichBool::MakeGeneralAnalysis(true).expr("a", ":")("1", true)
		(" != ").expr("b", ":")("2", true);

	RichBool::Analysis *cb;
	if (RichBoolTest::GetLevel()==3)
		cb = new RichBool::OrAnalysis(an1, an2);
	else
		cb = new RichBool::OrAnalysis(RichBool::Bool(false), an2);
	cb->Negate();

	RB_FAIL(
		rb2_RB(a, b, !(EqualCountCalls<>(1) | DiffCountCalls<>(1))),
		*cb);
	delete cb;
}

RB_TEST(NotOrBoth_Fail_Second)
{
	int a=1, b=2;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(true).expr("a", ":")("1", true)
		(" != ").expr("b", ":")("2", true),
		*an2 = RichBool::MakeGeneralAnalysis(false).expr("a", ":")("1", true)
		(" == ").expr("b", ":")("2", true);

	RichBool::Analysis *cb;
	if (RichBoolTest::GetLevel()==3)
		cb = new RichBool::OrAnalysis(an1, an2);
	else
		cb = new RichBool::OrAnalysis(an1, RichBool::Bool(false));
	cb->Negate();

	int nrCalls2 = RichBoolTest::GetLevel()==1 ? 0 : 1;
	RB_FAIL(
		rb2_RB(a, b, !(DiffCountCalls<>(1) | EqualCountCalls<>(nrCalls2))),
		*cb);

	delete cb;
}

RB_TEST(NotOrBoth_Fail_Both)
{
	int a=1, b=1;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(true).expr("a", ":")("1", true)
		(" == ").expr("b", ":")("1", true);
	RichBool::Analysis *an2 = RichBool::MakeGeneralAnalysis(true).expr("a", ":")("1", true)
		(" == ").expr("b", ":")("1", true);

	RichBool::Analysis *cb =
		new RichBool::OrAnalysis(an1, an2);
	cb->Negate();

	int nrCalls2 = RichBoolTest::GetLevel()==1 ? 0 : 1;
	RB_FAIL(
		rb2_RB(a, b, !(EqualCountCalls<>(1) | EqualCountCalls<>(nrCalls2))),
		*cb);

	delete cb;
}

// with bad values

RB_TEST(NotOrBoth_Fail_FirstBad)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true),
		*an2 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotOk)
		.expr("p", ":")(GetNullPtrString(), true)
		(" == ").expr("pa", ":")(RichBool::PtrToString(pa), true);

	RichBool::Analysis *cb;
	if (RichBoolTest::GetLevel()==3)
		cb = new RichBool::OrAnalysis(an1, an2);
	else
		cb = new RichBool::OrAnalysis(an1, RichBool::Bool(false));
	cb->Negate();

	RB_FAIL(
		rb2_RB(p, pa, !(EqualDerefCount(0) | EqualCountCalls<>(1))),
		*cb);

	delete cb;
}

RB_TEST(NotOrBoth_Fail_SecondBad_FirstOk)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::Ok)
		.expr("p", ":")(GetNullPtrString(), true)
		(" == ").expr("p", ":")(GetNullPtrString(), true),
		*an2 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ")
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false);

	RichBool::Analysis *cb = new RichBool::OrAnalysis(an1, an2);
	cb->Negate();

	RB_FAIL(rb2_RB(p, p, !(EqualCountCalls<>(1) | EqualDerefCount(0))), *cb);

	delete cb;
}

RB_TEST(NotOrBoth_Fail_SecondBad_FirstNok)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotOk)
		.expr("p", ":")(GetNullPtrString(), true)
		(" == ").expr("pa", ":")(RichBool::PtrToString(pa), true),
		*an2 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true);

	RichBool::Analysis *cb;
	if (RichBoolTest::GetLevel()==3)
		cb = new RichBool::OrAnalysis(an1, an2);
	else
		cb = new RichBool::OrAnalysis(RichBool::Bool(false), an2);
	cb->Negate();

	RB_FAIL(
		rb2_RB(p, pa, !(RichBool::Equal<>() | EqualDerefCount(0))),
		*cb);

	delete cb;
}


////////////////////////////////////////////////////////////
// Tests for Not<Xor<...>>

RB_TEST(NotXor_Pass_Both)
{
	int a=1, b=2;
	RB_PASS(
		rb2_RB(a, b, !(DiffCountCalls<>(1) ^ DiffCountCalls<>(1)))
	);
}

RB_TEST(NotXor_Pass_None)
{
	int a=1, b=2;
	RB_PASS(
		rb2_RB(a, b, !(EqualCountCalls<>(1) ^ EqualCountCalls<>(1)))
	);
}

RB_TEST(NotXor_Pass_First)
{
	int a=1, b=2;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(true).expr("a", ":")("1", true)
		(" < ").expr("b", ":")("2", true);
	RichBool::Analysis *an2 = RichBool::MakeGeneralAnalysis(false).expr("a", ":")("1", true)
		(" == ").expr("b", ":")("2", true);

	RichBool::Analysis *cb =
		new RichBool::XorAnalysis(an1, an2);
	cb->Negate();

	RB_FAIL(
		rb2_RB(a, b, !(RichBool::Less<>() ^ RichBool::Equal<>())),
		*cb);

	delete cb;
}

RB_TEST(NotXor_Pass_Second)
{
	int a=1, b=2;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(false).expr("a", ":")("1", true)
		(" > ").expr("b", ":")("2", true);
	RichBool::Analysis *an2 = RichBool::MakeGeneralAnalysis(true).expr("a", ":")("1", true)
		(" < ").expr("b", ":")("2", true);

	RichBool::Analysis *cb = new RichBool::XorAnalysis(an1, an2);
	cb->Negate();

	RB_FAIL(
		rb2_RB(a, b, !(RichBool::More<>() ^ RichBool::Less<>())),
		*cb);

	delete cb;
}

// with bad values

RB_TEST(NotXor_Fail_FirstBad_SecondOk)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true);

	RichBool::Analysis *cb = new RichBool::XorAnalysis(an1, new RichBool::AnalysisNotEvaluated);
	cb->Negate();

	RB_FAIL(
		rb2_RB(p, pa, !(EqualDerefCount(0) ^ DiffCountCalls<>(0))),
		*cb);

	delete cb;
}

RB_TEST(NotXor_Fail_FirstBad_SecondNotOk)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true);

	RichBool::Analysis *cb = new RichBool::XorAnalysis(an1, new RichBool::AnalysisNotEvaluated);
	cb->Negate();

	RB_FAIL(
		rb2_RB(p, pa, !(EqualDerefCount(0) ^ EqualCountCalls<>(0))),
		*cb);

	delete cb;
}

RB_TEST(NotXor_Fail_SecondBad_FirstOk)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::Ok)
		.expr("p", ":")(GetNullPtrString(), true)
		(" != ").expr("pa", ":")(RichBool::PtrToString(pa), true),
		*an2 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true);

	RichBool::Analysis *cb = new RichBool::XorAnalysis(an1, an2);
	cb->Negate();

	RB_FAIL(
		rb2_RB(p, pa, !(RichBool::Diff<>() ^ EqualDerefCount(0))),
		*cb);

	delete cb;
}

RB_TEST(NotXor_Fail_SecondBad_FirstNotOk)
{
	// if no analysis is done, there is also no check for bad pointers,
	// so the tests here would make the testprogram crash
	if (RichBoolTest::GetLevel()==1)
		return;

	int a=1, *pa=&a, *p=0;

	RichBool::Analysis *an1 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::NotOk)
		.expr("p", ":")(GetNullPtrString(), true)
		(" == ").expr("pa", ":")(RichBool::PtrToString(pa), true),
		*an2 = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.pexpr("*", "p", ":")(RichBool::PtrToString(&p)+" -> "+GetNullPtrString(), false)
		(" == ").pexpr("*", "pa", ":")("1", true);

	RichBool::Analysis *cb = new RichBool::XorAnalysis(an1, an2);
	cb->Negate();

	RB_FAIL(
		rb2_RB(p, pa, !(RichBool::Equal<>() ^ EqualDerefCount(0))),
		*cb);

	delete cb;
}
