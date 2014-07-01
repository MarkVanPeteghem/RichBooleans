//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/richbool.hpp"
#include "richbool/functors.hpp"


//////////////////////////////////////////////////////////////////////////
// Tests for wrappers with a core that is not in the RichBool namespace:


// 1 argument

class Is3Core: public RichBool::FunctorCore
{
public:
	bool operator()(int n) const
	{
		return 3==n;
	}
	const char* GetTextAfter1() const { return " == 3"; }
};

RICHBOOL_WRAPPER1ARG(Is3, Is3Core)

RB_TEST(Wrapper1Arg_Pass)
{
	RB_PASS(rb1_RB(3, Is3<>()));
}

RB_TEST(Wrapper1Arg_Fail)
{
	RichBool::SharedAnalysis an=(RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)
			.expr("2", ":")("2", true)(" == 3");
	RB_FAIL(rb1_RB(2, Is3<>()), *an);
}


// 2 arguments

class SumOf2Is77Core: public RichBool::FunctorCore
{
public:
	bool operator()(int a, int b) const
	{
		return 77==a+b;
	}
	const char* GetTextAfter1() const { return " + "; }
	const char* GetTextAfter2() const { return " == 77"; }
};

RICHBOOL_WRAPPER2ARG(SumOf2Is77, SumOf2Is77Core)

RB_TEST(Wrapper2Arg_Pass)
{
	RB_PASS(rb2_RB(55, 22, SumOf2Is77<>()));
}

RB_TEST(Wrapper2Arg_Fail)
{
	RichBool::SharedAnalysis an=(RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)
			.expr("56", ":")("56", true)(" + ").expr("22", ":")("22", true)(" == 77");
	RB_FAIL(rb2_RB(56, 22, SumOf2Is77<>()), *an);
}


// 3 arguments

class SumOf3Is77Core: public RichBool::FunctorCore
{
public:
	bool operator()(int a, int b, int c) const
	{
		return 77==a+b+c;
	}
	const char* GetTextAfter1() const { return " + "; }
	const char* GetTextAfter2() const { return " + "; }
	const char* GetTextAfter3() const { return " == 77"; }
};

RICHBOOL_WRAPPER3ARG(SumOf3Is77, SumOf3Is77Core)

RB_TEST(Wrapper3Arg_Pass)
{
	RB_PASS(rb3_RB(33, 22, 22, SumOf3Is77<>()));
}

RB_TEST(Wrapper3Arg_Fail)
{
	RichBool::SharedAnalysis an=(RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)
			.expr("56", ":")("56", true)(" + ")
			.expr("11", ":")("11", true)(" + ")
			.expr("22", ":")("22", true)(" == 77");
	RB_FAIL(rb3_RB(56, 11, 22, SumOf3Is77<>()), *an);
}


// 4 arguments

class SumOf4Is77Core: public RichBool::FunctorCore
{
public:
	bool operator()(int a, int b, int c, int d) const
	{
		return 77==a+b+c+d;
	}
	const char* GetTextAfter1() const { return " + "; }
	const char* GetTextAfter2() const { return " + "; }
	const char* GetTextAfter3() const { return " + "; }
	const char* GetTextAfter4() const { return " == 77"; }
};

RICHBOOL_WRAPPER4ARG(SumOf4Is77, SumOf4Is77Core)

RB_TEST(Wrapper4Arg_Pass)
{
	RB_PASS(rb4_RB(33, 22, 11, 11, SumOf4Is77<>()));
}

RB_TEST(Wrapper4Arg_Fail)
{
	RichBool::SharedAnalysis an=(RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)
			.expr("56", ":")("56", true)(" + ")
			.expr("11", ":")("11", true)(" + ")
			.expr("11", ":")("11", true)(" + ")
			.expr("22", ":")("22", true)(" == 77");
	RB_FAIL(rb4_RB(56, 11, 11, 22, SumOf4Is77<>()), *an);
}


// 5 arguments

class SumOf5Is77Core: public RichBool::FunctorCore
{
public:
	bool operator()(int a, int b, int c, int d, int e) const
	{
		return 77==a+b+c+d+e;
	}
	const char* GetTextAfter1() const { return " + "; }
	const char* GetTextAfter2() const { return " + "; }
	const char* GetTextAfter3() const { return " + "; }
	const char* GetTextAfter4() const { return " + "; }
	const char* GetTextAfter5() const { return " == 77"; }
};

RICHBOOL_WRAPPER5ARG(SumOf5Is77, SumOf5Is77Core)

RB_TEST(Wrapper5Arg_Pass)
{
	RB_PASS(rb5_RB(18, 15, 22, 11, 11, SumOf5Is77<>()));
}

RB_TEST(Wrapper5Arg_Fail)
{
	RichBool::SharedAnalysis an=(RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)
			.expr("56", ":")("56", true)(" + ")
			.expr("11", ":")("11", true)(" + ")
			.expr("11", ":")("11", true)(" + ")
			.expr("11", ":")("11", true)(" + ")
			.expr("22", ":")("22", true)(" == 77");
	RB_FAIL(rb5_RB(56, 11, 11, 11, 22, SumOf5Is77<>()), *an);
}


//////////////////////////////////////////////////////////////////////////
// Tests for wrappers with constructor with one argument:


// 1 argument

class IsCore: public RichBool::FunctorCore
{
	int val;
public:
	IsCore(int n): val(n) {}
	bool operator()(int n) const
	{
		return val==n;
	}
	const char* GetTextAfter1() const { return " == "; }
	const RichBool::detail::String GetExtraValue1() const { return RichBool::ToString(val); }
};

RICHBOOL_WRAPPER1ARG_1CARG(Is, IsCore, int n, n)

RB_TEST(Wrapper1Arg1CArg_Pass)
{
	RB_PASS(rb1_RB(1, Is<>(1)));
}

RB_TEST(Wrapper1Arg1CArg_Fail)
{
	RichBool::SharedAnalysis an=(RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)
			.expr("2", ":")("2", true)(" == ")("1", true);
	RB_FAIL(rb1_RB(2, Is<>(1)), *an);
}


// 2 arguments

class SumOf2IsCore: public RichBool::FunctorCore
{
	int val;
public:
	SumOf2IsCore(int n): val(n) {}
	bool operator()(int a, int b) const
	{
		return (a+b)==val;
	}
	const char* GetTextAfter1() const { return "+"; }
	const char* GetTextAfter2() const { return " == "; }
	const RichBool::detail::String GetExtraValue2() const { return RichBool::ToString(val); }
};

RICHBOOL_WRAPPER2ARG_1CARG(SumOf2Is, SumOf2IsCore, int n, n)

RB_TEST(Wrapper2Arg1CArg_Pass)
{
	RB_PASS(rb2_RB(2,3, SumOf2Is<>(5)));
}

RB_TEST(Wrapper2Arg1CArg_Fail)
{
	RichBool::SharedAnalysis an=(RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)
			.expr("2", ":")("2", true)("+").expr("3", ":")("3", true)(" == ")("6", true);
	RB_FAIL(rb2_RB(2, 3, SumOf2Is<>(6)), *an);
}


// 3 arguments

class SumOf3IsCore: public RichBool::FunctorCore
{
	int val;
public:
	SumOf3IsCore(int n): val(n) {}
	bool operator()(int a, int b, int c) const
	{
		return (a+b+c)==val;
	}
	const char* GetTextAfter1() const { return "+"; }
	const char* GetTextAfter2() const { return "+"; }
	const char* GetTextAfter3() const { return " == "; }
	const RichBool::detail::String GetExtraValue3() const { return RichBool::ToString(val); }
};

RICHBOOL_WRAPPER3ARG_1CARG(SumOf3Is, SumOf3IsCore, int n, n)

RB_TEST(Wrapper3Arg1CArg_Pass)
{
	RB_PASS(rb3_RB(2,3,4, SumOf3Is<>(9)));
}

RB_TEST(Wrapper3Arg1CArg_Fail)
{
	RichBool::SharedAnalysis an=(RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)
			.expr("2", ":")("2", true)("+").expr("3", ":")("3", true)
			("+").expr("1", ":")("1", true)(" == ")("7", true);
	RB_FAIL(rb3_RB(2, 3, 1, SumOf3Is<>(7)), *an);
}


// 4 arguments

class SumOf4IsCore: public RichBool::FunctorCore
{
	int val;
public:
	SumOf4IsCore(int n): val(n) {}
	bool operator()(int a, int b, int c, int d) const
	{
		return (a+b+c+d)==val;
	}
	const char* GetTextAfter1() const { return "+"; }
	const char* GetTextAfter2() const { return "+"; }
	const char* GetTextAfter3() const { return "+"; }
	const char* GetTextAfter4() const { return " == "; }
	const RichBool::detail::String GetExtraValue4() const { return RichBool::ToString(val); }
};

RICHBOOL_WRAPPER4ARG_1CARG(SumOf4Is, SumOf4IsCore, int n, n)

RB_TEST(Wrapper4Arg1CArg_Pass)
{
	RB_PASS(rb4_RB(1,2,3,4, SumOf4Is<>(10)));
}

RB_TEST(Wrapper4Arg1CArg_Fail)
{
	RichBool::SharedAnalysis an=(RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)
			.expr("4", ":")("4", true)("+").expr("2", ":")("2", true)("+")
			.expr("3", ":")("3", true)("+").expr("1", ":")("1", true)
			(" == ")("7", true);
	RB_FAIL(rb4_RB(4, 2, 3, 1, SumOf4Is<>(7)), *an);
}


// 5 arguments

class SumOf5IsCore: public RichBool::FunctorCore
{
	int val;
public:
	SumOf5IsCore(int n): val(n) {}
	bool operator()(int a, int b, int c, int d, int e) const
	{
		return (a+b+c+d+e)==val;
	}
	const char* GetTextAfter1() const { return "+"; }
	const char* GetTextAfter2() const { return "+"; }
	const char* GetTextAfter3() const { return "+"; }
	const char* GetTextAfter4() const { return "+"; }
	const char* GetTextAfter5() const { return " == "; }
	const RichBool::detail::String GetExtraValue5() const { return RichBool::ToString(val); }
};

RICHBOOL_WRAPPER5ARG_1CARG(SumOf5Is, SumOf5IsCore, int n, n)

RB_TEST(Wrapper5Arg1CArg_Pass)
{
	RB_PASS(rb5_RB(1,2,3,4,5, SumOf5Is<>(15)));
}

RB_TEST(Wrapper5Arg1CArg_Fail)
{
	RichBool::SharedAnalysis an=(RichBool::Analysis*)
		RichBool::MakeGeneralAnalysis(false)
			.expr("4", ":")("4", true)("+").expr("2", ":")("2", true)("+")
			.expr("3", ":")("3", true)("+").expr("5", ":")("5", true)("+")
			.expr("1", ":")("1", true)
			(" == ")("7", true);
	RB_FAIL(rb5_RB(4, 2, 3, 5, 1, SumOf5Is<>(7)), *an);
}
