//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#if defined(_MSC_VER)
	#pragma warning(disable: 4786)
#endif

#include "richbool/richbool.hpp"
#include "richbool/containers.hpp"

#include "rbtest.hpp"
#include "int_less.hpp"

static const IntHolder_WithLess one(1), two(2);

struct CustomLessCore: public RichBool::FunctorCore
{
	template <typename T1, typename T2>
	bool operator()(const T1 &t1, const T2 &t2) const
	{
		return t1<t2;
	}
	const char* GetTextAfter1() const
	{
		return " < ";
	}
};

RICHBOOL_WRAPPER2ARG(CustomLess, CustomLessCore)

static RichBool::detail::SortToEqual<CustomLess<> > equalc;

RB_TEST(SortToEqual_Pass)
{
	RB_PASS(rb2_RB(one,one, equalc));
}

RB_TEST(SortToEqual_Pass_Negate)
{
	RB_PASS(rb2_RB(one,two, !equalc));
	RB_PASS(rb2_RB(two,one, !equalc));
}

RB_TEST(SortToEqual_SafeCheck)
{
	RB_ASSERT(rbEQUAL(equalc.SafeCheck(one,one), RichBool::Analysis::Ok));
	RB_ASSERT(rbEQUAL(equalc.SafeCheck(one,two), RichBool::Analysis::NotOk));
	RB_ASSERT(rbEQUAL(equalc.SafeCheck(two,one), RichBool::Analysis::NotOk));
}

RB_TEST(SortToEqual_SafeCheck_NullPtr)
{
	IntHolder_WithLess *p=0;
	RB_ASSERT(rbEQUAL(equalc.SafeCheck(*p,one), RichBool::Analysis::BadValue));
	RB_ASSERT(rbEQUAL(equalc.SafeCheck(one,*p), RichBool::Analysis::BadValue));
	RB_ASSERT(rbEQUAL(equalc.SafeCheck(*p,*p), RichBool::Analysis::BadValue));
}

RB_TEST(SortToEqual_Fail1)
{
	RichBool::Analysis *an = RichBool::MakeGeneralAnalysis(false)
		.expr("one", ":")("1",true)(" == ").expr("two", ":")("2",true);
	RB_FAIL(rb2_RB(one,two, equalc), *an);
}

RB_TEST(SortToEqual_Fail2)
{
	RichBool::Analysis *an = RichBool::MakeGeneralAnalysis(false)
		.expr("two", ":")("2",true)(" == ").expr("one", ":")("1",true);
	RB_FAIL(rb2_RB(two,one, equalc), *an);
}

RB_TEST(SortToEqual_Fail_Negate)
{
	RichBool::Analysis *an = RichBool::MakeGeneralAnalysis(true)
		.expr("one", ":")("1",true)(" == ").expr("one", ":")("1",true).neg();
	RB_FAIL(rb2_RB(one,one, !equalc), *an);
}

RB_TEST(SortToEqual_Fail_FirstBad)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	IntHolder_WithLess *p=0;

	RichBool::Analysis *an = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.expr("*p", ":")(GetNullPtrString(),false)(" == ").expr("one", ":")("1",true);

	RB_FAIL(rb2_RB(*p,one, equalc), *an);
}

RB_TEST(SortToEqual_Fail_SecondBad)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	IntHolder_WithLess *p=0;

	RichBool::Analysis *an = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.expr("one", ":")("1",true)(" == ").expr("*p", ":")(GetNullPtrString(),false);

	RB_FAIL(rb2_RB(one,*p, equalc), *an);
}



// the specialization with Less:

static RichBool::detail::SortToEqual<RichBool::Less<> > equal;

RB_TEST(SortToEqual_Less_Pass)
{
	RB_PASS(rb2_RB(one,one, equal));
}

RB_TEST(SortToEqual_Less_Pass_Negate)
{
	RB_PASS(rb2_RB(one,two, !equal));
	RB_PASS(rb2_RB(two,one, !equal));
}

RB_TEST(SortToEqual_Less_SafeCheck)
{
	RB_ASSERT(rbEQUAL(equal.SafeCheck(one,one), RichBool::Analysis::Ok));
	RB_ASSERT(rbEQUAL(equal.SafeCheck(one,two), RichBool::Analysis::NotOk));
	RB_ASSERT(rbEQUAL(equal.SafeCheck(two,one), RichBool::Analysis::NotOk));
}

RB_TEST(SortToEqual_Less_SafeCheck_NullPtr)
{
	IntHolder_WithLess *p=0;
	RB_ASSERT(rbEQUAL(equal.SafeCheck(*p,one), RichBool::Analysis::BadValue));
	RB_ASSERT(rbEQUAL(equal.SafeCheck(one,*p), RichBool::Analysis::BadValue));
	RB_ASSERT(rbEQUAL(equal.SafeCheck(*p,*p), RichBool::Analysis::BadValue));
}

RB_TEST(SortToEqual_Less_Fail1)
{
	RichBool::Analysis *an = RichBool::MakeGeneralAnalysis(false)
		.expr("one", ":")("1",true)(" == ").expr("two", ":")("2",true);
	RB_FAIL(rb2_RB(one,two, equal), *an);
}

RB_TEST(SortToEqual_Less_Fail2)
{
	RichBool::Analysis *an = RichBool::MakeGeneralAnalysis(false)
		.expr("two", ":")("2",true)(" == ").expr("one", ":")("1",true);
	RB_FAIL(rb2_RB(two,one, equal), *an);
}

RB_TEST(SortToEqual_Less_Fail_Negate)
{
	RichBool::Analysis *an = RichBool::MakeGeneralAnalysis(true)
		.expr("one", ":")("1",true)(" == ").expr("one", ":")("1",true).neg();
	RB_FAIL(rb2_RB(one,one, !equal), *an);
}

RB_TEST(SortToEqual_Less_Fail_FirstBad)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	IntHolder_WithLess *p=0;

	RichBool::Analysis *an = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.expr("*p", ":")(GetNullPtrString(),false)(" == ").expr("one", ":")("1",true);

	RB_FAIL(rb2_RB(*p,one, equal), *an);
}

RB_TEST(SortToEqual_Less_Fail_SecondBad)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	IntHolder_WithLess *p=0;

	RichBool::Analysis *an = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.expr("one", ":")("1",true)(" == ").expr("*p", ":")(GetNullPtrString(),false);

	RB_FAIL(rb2_RB(one,*p, equal), *an);
}



// the specialization with More:

static RichBool::detail::SortToEqual<RichBool::More<> > equalm;
static const IntHolder_WithMore onem(1), twom(2);

RB_TEST(SortToEqual_More_Pass)
{
	RB_PASS(rb2_RB(onem,onem, equalm));
}

RB_TEST(SortToEqual_More_Pass_Negate)
{
	RB_PASS(rb2_RB(onem,twom, !equalm));
	RB_PASS(rb2_RB(twom,onem, !equalm));
}

RB_TEST(SortToEqual_More_SafeCheck)
{
	RB_ASSERT(rbEQUAL(equalm.SafeCheck(onem,onem), RichBool::Analysis::Ok));
	RB_ASSERT(rbEQUAL(equalm.SafeCheck(onem,twom), RichBool::Analysis::NotOk));
	RB_ASSERT(rbEQUAL(equalm.SafeCheck(twom,onem), RichBool::Analysis::NotOk));
}

RB_TEST(SortToEqual_More_SafeCheck_NullPtr)
{
	IntHolder_WithMore *p=0;
	RB_ASSERT(rbEQUAL(equalm.SafeCheck(*p,onem), RichBool::Analysis::BadValue));
	RB_ASSERT(rbEQUAL(equalm.SafeCheck(onem,*p), RichBool::Analysis::BadValue));
	RB_ASSERT(rbEQUAL(equalm.SafeCheck(*p,*p), RichBool::Analysis::BadValue));
}

RB_TEST(SortToEqual_More_Fail1)
{
	RichBool::Analysis *an = RichBool::MakeGeneralAnalysis(false)
		.expr("onem", ":")("1",true)(" == ").expr("twom", ":")("2",true);
	RB_FAIL(rb2_RB(onem,twom, equalm), *an);
}

RB_TEST(SortToEqual_More_Fail2)
{
	RichBool::Analysis *an = RichBool::MakeGeneralAnalysis(false)
		.expr("twom", ":")("2",true)(" == ").expr("onem", ":")("1",true);
	RB_FAIL(rb2_RB(twom,onem, equalm), *an);
}

RB_TEST(SortToEqual_More_Fail_Negate)
{
	RichBool::Analysis *an = RichBool::MakeGeneralAnalysis(true)
		.expr("onem", ":")("1",true)(" == ").expr("onem", ":")("1",true).neg();
	RB_FAIL(rb2_RB(onem,onem, !equalm), *an);
}

RB_TEST(SortToEqual_More_Fail_FirstBad)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	IntHolder_WithMore *p=0;

	RichBool::Analysis *an = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.expr("*p", ":")(GetNullPtrString(),false)(" == ").expr("onem", ":")("1",true);

	RB_FAIL(rb2_RB(*p,onem, equalm), *an);
}

RB_TEST(SortToEqual_More_Fail_SecondBad)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	IntHolder_WithMore *p=0;

	RichBool::Analysis *an = RichBool::MakeGeneralAnalysis(RichBool::Analysis::BadValue)
		.expr("onem", ":")("1",true)(" == ").expr("*p", ":")(GetNullPtrString(),false);

	RB_FAIL(rb2_RB(onem,*p, equalm), *an);
}
