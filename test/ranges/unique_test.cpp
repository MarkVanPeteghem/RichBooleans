//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#if defined(_MSC_VER)
	#pragma warning(disable: 4786)
#endif

#include "richbool/richbool.hpp"

#include "rbtest.hpp"
#include "testable_analysis_for_ranges.hpp"
#include "predicates.hpp"
#include "stub_container.hpp"
#include "stub_get_value.hpp"

using namespace RichBool;


// tests for Rich Booleans that check whether a range a unique element
// that satisfies a certain condition

RB_TEST(Unique_Succeed_One)
{
	int a[] = { 2 };

	RB_PASS(rbIN_RANGE(a, a+1, Unique<>().That(Pred1<IsEven>())));
	RB_PASS(rbIN_RANGE(a, a+1, Unique<>(true).That(Pred1<IsEven>())));

	RB_PASS(rbIN_RANGE(a, 1, Unique<>().That(Pred1<IsEven>())));
	RB_PASS(rbIN_RANGE(a, 1, Unique<>(true).That(Pred1<IsEven>())));
}

RB_TEST(Unique_Succeed_Two_First)
{
	int a[] = { 2, 3 };

	RB_PASS(rbIN_RANGE(a, a+2, Unique<>().That(Pred1<IsEven>())));
	RB_PASS(rbIN_RANGE(a, a+2, Unique<>(true).That(Pred1<IsEven>())));

	RB_PASS(rbIN_RANGE(a, 2, Unique<>().That(Pred1<IsEven>())));
	RB_PASS(rbIN_RANGE(a, 2, Unique<>(true).That(Pred1<IsEven>())));
}

RB_TEST(Unique_Succeed_Two_Second)
{
	int a[] = { 3, 2 };

	RB_PASS(rbIN_RANGE(a, a+2, Unique<>().That(Pred1<IsEven>())));
	RB_PASS(rbIN_RANGE(a, a+2, Unique<>(true).That(Pred1<IsEven>())));
}

RB_TEST(Unique_Succeed_Two_None_Negate)
{
	int a[] = { 3, 5 };

	RB_PASS(rbIN_RANGE(a, a+2, !Unique<>().That(Pred1<IsEven>())));
	RB_PASS(rbIN_RANGE(a, a+2, !Unique<>(true).That(Pred1<IsEven>())));
}

RB_TEST(Unique_Succeed_Two_Both_Negate)
{
	int a[] = { 0, 2 };

	RB_PASS(rbIN_RANGE(a, a+2, !Unique<>().That(Pred1<IsEven>())));
	RB_PASS(rbIN_RANGE(a, a+2, !Unique<>(true).That(Pred1<IsEven>())));
}

RB_TEST(Unique_Succeed_Empty_Negate)
{
	int a[] = { 0 };

	RB_PASS(rbIN_RANGE(a, a, !Unique<>().That(Pred1<IsEven>())));
	RB_PASS(rbIN_RANGE(a, a, !Unique<>(true).That(Pred1<IsEven>())));
}

RB_TEST(Unique_Fail_Empty)
{
	int a[] = { 1 };

	TestableAnalysisOfRange analysis1(
		"predicate applies to exactly one element in range ", "a", "a");
	TestableAnalysisOfRange analysis2(
		"predicate applies to exactly one element in range ", "a", "0");

	RB_FAIL(rbIN_RANGE(a, a, Unique<>().That(Pred1<IsEven>())), analysis1);
	RB_FAIL(rbIN_RANGE(a, 0, Unique<>(true).That(Pred1<IsEven>())), analysis2);
}

RB_TEST(Unique_Fail_One)
{
	int a[] = { 1 };

	TestableAnalysisOfRange analysis1(
		"predicate applies to exactly one element in range ", "a", "a+1");
	TestableAnalysisOfRange analysis2(
		"predicate applies to exactly one element in range ", "a", "1");

	RB_FAIL(rbIN_RANGE(a, a+1, Unique<>().That(Pred1<IsEven>())), analysis1);
	RB_FAIL(rbIN_RANGE(a, 1, Unique<>().That(Pred1<IsEven>())), analysis2);
}

RB_TEST(Unique_Fail_One_Negate)
{
	int a[] = { 2 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("2", true)(")"),
	};

	TestableAnalysisOfRange analysis1(Analysis::Ok,
		"predicate applies to exactly one element in range ", "a", "a+1");
	analysis1.AddAnalyses(arrAnalyses, 1);
	analysis1.Negate();

	RB_FAIL(rbIN_RANGE(a, a+1, !Unique<>().That(Pred1<IsEven>())), analysis1);
}

RB_TEST(Unique_Fail_One_Full)
{
	int a[] = { 1 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(0, ":")("1", true)(")"),
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "a", "a+1");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGE(a, a+1, Unique<>(true).That(Pred1<IsEven>())), analysis);
}

RB_TEST(Unique_Fail_One_Full_Negate)
{
	int a[] = { 2 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("2", true)(")"),
	};

	TestableAnalysisOfRange analysis(Analysis::Ok,
		"predicate applies to exactly one element in range ", "a", "a+1");
	analysis.AddAnalyses(arrAnalyses, 1);
	analysis.Negate();

	RB_FAIL(rbIN_RANGE(a, a+1, !Unique<>(true).That(Pred1<IsEven>())), analysis);
}

RB_TEST(Unique_Fail_Three)
{
	int a[] = { 1, 3, 5 };

	TestableAnalysisOfRange analysis1(
		"predicate applies to exactly one element in range ", "a", "a+3");
	TestableAnalysisOfRange analysis2(
		"predicate applies to exactly one element in range ", "a", "3");

	RB_FAIL(rbIN_RANGE(a, a+3, Unique<>().That(Pred1<IsEven>())), analysis1);
	RB_FAIL(rbIN_RANGE(a, 3, Unique<>().That(Pred1<IsEven>())), analysis2);
}

RB_TEST(Unique_Fail_Three_Full)
{
	int a[] = { 1, 3, 5 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(0, ":")("1", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("3", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(2, ":")("5", true)(")")
	};

	TestableAnalysisOfRange analysis1(
		"predicate applies to exactly one element in range ", "a", "a+3");
	analysis1.AddAnalyses(arrAnalyses, 3);

	TestableAnalysisOfRange analysis2(
		"predicate applies to exactly one element in range ", "a", "3");
	analysis2.AddAnalyses(arrAnalyses, 3, false);

	RB_FAIL(rbIN_RANGE(a, a+3, Unique<>(true).That(Pred1<IsEven>())), analysis1);
	RB_FAIL(rbIN_RANGE(a, 3, Unique<>(true).That(Pred1<IsEven>())), analysis2);
}

RB_TEST(Unique_Fail_Two_All)
{
	int a[] = { 4, 2 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("4", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(1, ":")("2", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "a", "a+2");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGE(a, a+2, Unique<>().That(Pred1<IsEven>())), analysis);
}

RB_TEST(Unique_Fail_Two_All_Full)
{
	int a[] = { 4, 2 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("4", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(1, ":")("2", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "a", "a+2");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGE(a, a+2, Unique<>(true).That(Pred1<IsEven>())), analysis);
}

RB_TEST(Unique_Fail_Two_Of_Four)
{
	int a[] = { 4, 3, 2, 5 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("4", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(2, ":")("2", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "a", "a+4");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGE(a, a+4, Unique<>().That(Pred1<IsEven>())), analysis);
}

RB_TEST(Unique_Fail_Two_Of_Four_Full)
{
	int a[] = { 4, 3, 2, 5 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("4", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("3", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(2, ":")("2", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(3, ":")("5", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "a", "a+4");
	analysis.AddAnalyses(arrAnalyses, 4);

	RB_FAIL(rbIN_RANGE(a, a+4, Unique<>(true).That(Pred1<IsEven>())), analysis);
}



RB_TEST(Unique_Succeed_One_InputIterator)
{
	StubContainer stub(2);

	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), Unique<false>().That(Pred1<IsEven>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), Unique<false>(true).That(Pred1<IsEven>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 1, Unique<false>().That(Pred1<IsEven>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 1, Unique<false>(true).That(Pred1<IsEven>())));
}

RB_TEST(Unique_Succeed_One_InputIterator_Negate)
{
	StubContainer stub(1);

	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), !Unique<false>().That(Pred1<IsEven>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), !Unique<false>(true).That(Pred1<IsEven>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 1, !Unique<false>().That(Pred1<IsEven>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 1, !Unique<false>(true).That(Pred1<IsEven>())));
}

RB_TEST(Unique_Succeed_Two_First_InputIterator)
{
	StubContainer stub(2, 3);

	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), Unique<false>().That(Pred1<IsEven>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), Unique<false>(true).That(Pred1<IsEven>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 2, Unique<false>().That(Pred1<IsEven>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 2, Unique<false>(true).That(Pred1<IsEven>())));
}

RB_TEST(Unique_Succeed_Two_First_InputIterator_Negate)
{
	StubContainer stub(2, 4);

	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), !Unique<false>().That(Pred1<IsEven>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), !Unique<false>(true).That(Pred1<IsEven>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 2, !Unique<false>().That(Pred1<IsEven>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 2, !Unique<false>(true).That(Pred1<IsEven>())));
}

RB_TEST(Unique_Succeed_Empty_InputIterator_Negate)
{
	StubContainer stub(0);

	RB_PASS(rbIN_RANGE(stub.begin(), 0, !Unique<false>().That(Pred1<IsEven>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), 0, !Unique<false>(true).That(Pred1<IsEven>())));
}

RB_TEST(Unique_Succeed_Two_Second_InputIterator)
{
	StubContainer stub(3, 2);

	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), Unique<false>().That(Pred1<IsEven>())));
	stub.rewind();
	RB_PASS(rbIN_RANGE(stub.begin(), stub.end(), Unique<false>(true).That(Pred1<IsEven>())));
}

RB_TEST(Unique_Fail_Empty_InputIterator)
{
	StubContainer stub;

	TestableAnalysisOfRange analysis1(
		"predicate applies to exactly one element in range ", "stub.begin()", "stub.end()");
	TestableAnalysisOfRange analysis2(
		"predicate applies to exactly one element in range ", "stub.begin()", "0");

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), Unique<false>().That(Pred1<IsEven>())), analysis1);
	stub.rewind();
	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), Unique<false>(true).That(Pred1<IsEven>())), analysis1);
	stub.rewind();
	RB_FAIL(rbIN_RANGE(stub.begin(), 0, Unique<false>().That(Pred1<IsEven>())), analysis2);
	stub.rewind();
	RB_FAIL(rbIN_RANGE(stub.begin(), 0, Unique<false>(true).That(Pred1<IsEven>())), analysis2);
}

RB_TEST(Unique_Fail_One_InputIterator)
{
	StubContainer stub(1);

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "stub.begin()", "stub.end()");

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), Unique<false>().That(Pred1<IsEven>())), analysis);
}

RB_TEST(Unique_Fail_One_Full_InputIterator)
{
	StubContainer stub(1);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(0, ":")("1", true)(")"),
	};

	TestableAnalysisOfRange analysis1(
		"predicate applies to exactly one element in range ", "stub.begin()", "stub.end()");
	analysis1.AddAnalyses(arrAnalyses, 1);

	TestableAnalysisOfRange analysis2(
		"predicate applies to exactly one element in range ", "stub.begin()", "1");
	analysis2.AddAnalyses(arrAnalyses, 1, false);

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), Unique<false>(true).That(Pred1<IsEven>())), analysis1);
	stub.rewind();
	RB_FAIL(rbIN_RANGE(stub.begin(), 1, Unique<false>(true).That(Pred1<IsEven>())), analysis2);
}

RB_TEST(Unique_Fail_Three_InputIterator)
{
	StubContainer stub(1, 3, 5);

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "stub.begin()", "stub.end()");

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), Unique<false>().That(Pred1<IsEven>())), analysis);
}

RB_TEST(Unique_Fail_Three_InputIterator_Negate)
{
	StubContainer stub(1, 2, 5);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(1, ":")("2", true)(")")
	};

	TestableAnalysisOfRange analysis(Analysis::Ok,
		"predicate applies to exactly one element in range ", "stub.begin()", "stub.end()");
	analysis.AddAnalyses(arrAnalyses, 1);
	analysis.Negate();

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), !Unique<false>().That(Pred1<IsEven>())), analysis);
}

RB_TEST(Unique_Fail_Three_Full_InputIterator)
{
	StubContainer stub(1, 3, 5);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(0, ":")("1", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("3", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(2, ":")("5", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "stub.begin()", "stub.end()");
	analysis.AddAnalyses(arrAnalyses, 3);

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), Unique<false>(true).That(Pred1<IsEven>())), analysis);
}

RB_TEST(Unique_Fail_Two_All_InputIterator)
{
	StubContainer stub(4, 2);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("4", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(1, ":")("2", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "stub.begin()", "stub.end()");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), Unique<false>().That(Pred1<IsEven>())), analysis);
}

RB_TEST(Unique_Fail_Two_All_Full_InputIterator)
{
	StubContainer stub(4, 2);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("4", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(1, ":")("2", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "stub.begin()", "stub.end()");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGE(stub.begin(), stub.end(), Unique<false>(true).That(Pred1<IsEven>())), analysis);
}




/////////////////////////////////////////////////////////////////////
// same tests, but in the old, deprecated way:

RB_TEST(Unique_Succeed_One_Old)
{
	int a[] = { 2 };

	RB_PASS(rbIN_RANGE_ARG(a, a+1, Unique<>(), Pred1<IsEven>()));
	RB_PASS(rbIN_RANGE_ARG(a, a+1, Unique<>(true), Pred1<IsEven>()));
}

RB_TEST(Unique_Succeed_Two_First_Old)
{
	int a[] = { 2, 3 };

	RB_PASS(rbIN_RANGE_ARG(a, a+2, Unique<>(), Pred1<IsEven>()));
	RB_PASS(rbIN_RANGE_ARG(a, a+2, Unique<>(true), Pred1<IsEven>()));
}

RB_TEST(Unique_Succeed_Two_Second_Old)
{
	int a[] = { 3, 2 };

	RB_PASS(rbIN_RANGE_ARG(a, a+2, Unique<>(), Pred1<IsEven>()));
	RB_PASS(rbIN_RANGE_ARG(a, a+2, Unique<>(true), Pred1<IsEven>()));
}

RB_TEST(Unique_Fail_Empty_Old)
{
	int a[] = { 1 };

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "a", "a");

	RB_FAIL(rbIN_RANGE_ARG(a, a, Unique<>(), Pred1<IsEven>()), analysis);
	RB_FAIL(rbIN_RANGE_ARG(a, a, Unique<>(true), Pred1<IsEven>()), analysis);
}

RB_TEST(Unique_Fail_One_Old)
{
	int a[] = { 1 };

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "a", "a+1");

	RB_FAIL(rbIN_RANGE_ARG(a, a+1, Unique<>(), Pred1<IsEven>()), analysis);
}

RB_TEST(Unique_Fail_One_Full_Old)
{
	int a[] = { 1 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(0, ":")("1", true)(")"),
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "a", "a+1");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGE_ARG(a, a+1, Unique<>(true), Pred1<IsEven>()), analysis);
}

RB_TEST(Unique_Fail_Three_Old)
{
	int a[] = { 1, 3, 5 };

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "a", "a+3");

	RB_FAIL(rbIN_RANGE_ARG(a, a+3, Unique<>(), Pred1<IsEven>()), analysis);
}

RB_TEST(Unique_Fail_Three_Full_Old)
{
	int a[] = { 1, 3, 5 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(0, ":")("1", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("3", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(2, ":")("5", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "a", "a+3");
	analysis.AddAnalyses(arrAnalyses, 3);

	RB_FAIL(rbIN_RANGE_ARG(a, a+3, Unique<>(true), Pred1<IsEven>()), analysis);
}

RB_TEST(Unique_Fail_Two_All_Old)
{
	int a[] = { 4, 2 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("4", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(1, ":")("2", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "a", "a+2");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGE_ARG(a, a+2, Unique<>(), Pred1<IsEven>()), analysis);
}

RB_TEST(Unique_Fail_Two_All_Full_Old)
{
	int a[] = { 4, 2 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("4", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(1, ":")("2", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "a", "a+2");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGE_ARG(a, a+2, Unique<>(true), Pred1<IsEven>()), analysis);
}

RB_TEST(Unique_Fail_Two_Of_Four_Old)
{
	int a[] = { 4, 3, 2, 5 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("4", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(2, ":")("2", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "a", "a+4");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGE_ARG(a, a+4, Unique<>(), Pred1<IsEven>()), analysis);
}

RB_TEST(Unique_Fail_Two_Of_Four_Full_Old)
{
	int a[] = { 4, 3, 2, 5 };

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("4", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("3", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(2, ":")("2", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(3, ":")("5", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "a", "a+4");
	analysis.AddAnalyses(arrAnalyses, 4);

	RB_FAIL(rbIN_RANGE_ARG(a, a+4, Unique<>(true), Pred1<IsEven>()), analysis);
}



RB_TEST(Unique_Succeed_One_InputIterator_Old)
{
	StubContainer stub(2);

	RB_PASS(rbIN_RANGE_ARG(stub.begin(), stub.end(), Unique<false>(), Pred1<IsEven>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE_ARG(stub.begin(), stub.end(), Unique<false>(true), Pred1<IsEven>()));
}

RB_TEST(Unique_Succeed_Two_First_InputIterator_Old)
{
	StubContainer stub(2, 3);

	RB_PASS(rbIN_RANGE_ARG(stub.begin(), stub.end(), Unique<false>(), Pred1<IsEven>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE_ARG(stub.begin(), stub.end(), Unique<false>(true), Pred1<IsEven>()));
}

RB_TEST(Unique_Succeed_Two_Second_InputIterator_Old)
{
	StubContainer stub(3, 2);

	RB_PASS(rbIN_RANGE_ARG(stub.begin(), stub.end(), Unique<false>(), Pred1<IsEven>()));
	stub.rewind();
	RB_PASS(rbIN_RANGE_ARG(stub.begin(), stub.end(), Unique<false>(true), Pred1<IsEven>()));
}

RB_TEST(Unique_Fail_Empty_InputIterator_Old)
{
	StubContainer stub;

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "stub.begin()", "stub.end()");

	RB_FAIL(rbIN_RANGE_ARG(stub.begin(), stub.end(), Unique<false>(), Pred1<IsEven>()), analysis);
	stub.rewind();
	RB_FAIL(rbIN_RANGE_ARG(stub.begin(), stub.end(), Unique<false>(true), Pred1<IsEven>()), analysis);
}

RB_TEST(Unique_Fail_One_InputIterator_Old)
{
	StubContainer stub(1);

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "stub.begin()", "stub.end()");

	RB_FAIL(rbIN_RANGE_ARG(stub.begin(), stub.end(), Unique<false>(), Pred1<IsEven>()), analysis);
}

RB_TEST(Unique_Fail_One_Full_InputIterator_Old)
{
	StubContainer stub(1);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(0, ":")("1", true)(")"),
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "stub.begin()", "stub.end()");
	analysis.AddAnalyses(arrAnalyses, 1);

	RB_FAIL(rbIN_RANGE_ARG(stub.begin(), stub.end(), Unique<false>(true), Pred1<IsEven>()), analysis);
}

RB_TEST(Unique_Fail_Three_InputIterator_Old)
{
	StubContainer stub(1, 3, 5);

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "stub.begin()", "stub.end()");

	RB_FAIL(rbIN_RANGE_ARG(stub.begin(), stub.end(), Unique<false>(), Pred1<IsEven>()), analysis);
}

RB_TEST(Unique_Fail_Three_Full_InputIterator_Old)
{
	StubContainer stub(1, 3, 5);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(false)("predicate(").idx(0, ":")("1", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(1, ":")("3", true)(")"),
		MakeGeneralAnalysis(false)("predicate(").idx(2, ":")("5", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "stub.begin()", "stub.end()");
	analysis.AddAnalyses(arrAnalyses, 3);

	RB_FAIL(rbIN_RANGE_ARG(stub.begin(), stub.end(), Unique<false>(true), Pred1<IsEven>()), analysis);
}

RB_TEST(Unique_Fail_Two_All_InputIterator_Old)
{
	StubContainer stub(4, 2);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("4", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(1, ":")("2", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "stub.begin()", "stub.end()");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGE_ARG(stub.begin(), stub.end(), Unique<false>(), Pred1<IsEven>()), analysis);
}

RB_TEST(Unique_Fail_Two_All_Full_InputIterator_Old)
{
	StubContainer stub(4, 2);

	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(true)("predicate(").idx(0, ":")("4", true)(")"),
		MakeGeneralAnalysis(true)("predicate(").idx(1, ":")("2", true)(")")
	};

	TestableAnalysisOfRange analysis(
		"predicate applies to exactly one element in range ", "stub.begin()", "stub.end()");
	analysis.AddAnalyses(arrAnalyses, 2);

	RB_FAIL(rbIN_RANGE_ARG(stub.begin(), stub.end(), Unique<false>(true), Pred1<IsEven>()), analysis);
}


// with invalid pointers

RB_TEST(Fail_Unique_BadValue)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 2, 5, 8 };
	int *b[] = { &a[0], 0, &a[2] };

	SharedExpression se0=new PrefixedExpression("*", MakeExpression((size_t)0)),
		se1=new PrefixedExpression("*", MakeExpression(1)),
		se2=new PrefixedExpression("*", MakeExpression(2));
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(Analysis::Ok)("predicate(")
			.expr(se0, ":")
			(b[0], Pointer<>(), MakeString())(")"),
		MakeGeneralAnalysis(Analysis::BadValue)("predicate(")
			.expr(se1, ":")
			(b[1], Pointer<>(), MakeString())(")"),
		MakeGeneralAnalysis(Analysis::Ok)("predicate(")
			.expr(se2, ":")
			(b[2], Pointer<>(), MakeString())(")")
	};

	TestableAnalysisOfRange analysis1(Analysis::BadValue,
		"predicate applies to exactly one element in range ", "b", "b+3");
	analysis1.AddAnalyses(arrAnalyses, 3);

	Pred1<IsEven, Pointer<> > p;
	RB_FAIL(rbIN_RANGE(b, b+3, Unique<>().That(p)), analysis1);
}

RB_TEST(Fail_Unique_BadValue2)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 1, 5, 8 };
	int *b[] = { &a[0], 0, &a[2] };

	SharedExpression se1=new PrefixedExpression("*", MakeExpression(1)),
		se2=new PrefixedExpression("*", MakeExpression(2));
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(Analysis::BadValue)("predicate(")
			.expr(se1, ":")
			(b[1], Pointer<>(), MakeString())(")"),
		MakeGeneralAnalysis(Analysis::Ok)("predicate(")
			.expr(se2, ":")
			(b[2], Pointer<>(), MakeString())(")")
	};

	TestableAnalysisOfRange analysis1(Analysis::BadValue,
		"predicate applies to exactly one element in range ", "b", "b+3");
	analysis1.AddAnalyses(arrAnalyses, 2);

	Pred1<IsEven, Pointer<> > p;
	RB_FAIL(rbIN_RANGE(b, b+3, Unique<>().That(p)), analysis1);
}

RB_TEST(Fail_Unique_BadValue_ShowAll)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 1, 5, 8 };
	int *b[] = { &a[0], 0, &a[2] };

	SharedExpression se0=new PrefixedExpression("*", MakeExpression((size_t)0)),
		se1=new PrefixedExpression("*", MakeExpression(1)),
		se2=new PrefixedExpression("*", MakeExpression(2));
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(Analysis::NotOk)("predicate(")
			.expr(se0, ":")
			(b[0], Pointer<>(), MakeString())(")"),
		MakeGeneralAnalysis(Analysis::BadValue)("predicate(")
			.expr(se1, ":")
			(b[1], Pointer<>(), MakeString())(")"),
		MakeGeneralAnalysis(Analysis::Ok)("predicate(")
			.expr(se2, ":")
			(b[2], Pointer<>(), MakeString())(")")
	};

	TestableAnalysisOfRange analysis1(Analysis::BadValue,
		"predicate applies to exactly one element in range ", "b", "b+3");
	analysis1.AddAnalyses(arrAnalyses, 3);

	Pred1<IsEven, Pointer<> > p;
	RB_FAIL(rbIN_RANGE(b, b+3, Unique<>(true).That(p)), analysis1);
}

RB_TEST(Fail_Unique_BadValue_Single)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 2, 5, 8 };
	int *b[] = { &a[0], 0, &a[2] };

	SharedExpression se0=new PrefixedExpression("*", MakeExpression((size_t)0)),
		se1=new PrefixedExpression("*", MakeExpression(1)),
		se2=new PrefixedExpression("*", MakeExpression(2));
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(Analysis::Ok)("predicate(")
			.expr(se0, ":")
			(b[0], Pointer<>(), MakeString())(")"),
		MakeGeneralAnalysis(Analysis::BadValue)("predicate(")
			.expr(se1, ":")
			(b[1], Pointer<>(), MakeString())(")"),
		MakeGeneralAnalysis(Analysis::Ok)("predicate(")
			.expr(se2, ":")
			(b[2], Pointer<>(), MakeString())(")")
	};

	TestableAnalysisOfRange analysis1(Analysis::BadValue,
		"predicate applies to exactly one element in range ", "b", "b+3");
	analysis1.AddAnalyses(arrAnalyses, 3);

	Pred1<IsEven, Pointer<> > p;
	RB_FAIL(rbIN_RANGE(b, b+3, Unique<false>().That(p)), analysis1);
}

RB_TEST(Fail_Unique_BadValue_Single_ShowAll)
{
	if (RichBoolTest::GetLevel()==1)
		return;

	int a[] = { 1, 5, 8 };
	int *b[] = { &a[0], 0, &a[2] };

	SharedExpression se0=new PrefixedExpression("*", MakeExpression((size_t)0)),
		se1=new PrefixedExpression("*", MakeExpression(1)),
		se2=new PrefixedExpression("*", MakeExpression(2));
	Analysis *arrAnalyses[] = {
		MakeGeneralAnalysis(Analysis::NotOk)("predicate(")
			.expr(se0, ":")
			(b[0], Pointer<>(), MakeString())(")"),
		MakeGeneralAnalysis(Analysis::BadValue)("predicate(")
			.expr(se1, ":")
			(b[1], Pointer<>(), MakeString())(")"),
		MakeGeneralAnalysis(Analysis::Ok)("predicate(")
			.expr(se2, ":")
			(b[2], Pointer<>(), MakeString())(")")
	};

	TestableAnalysisOfRange analysis1(Analysis::BadValue,
		"predicate applies to exactly one element in range ", "b", "b+3");
	analysis1.AddAnalyses(arrAnalyses, 3);

	Pred1<IsEven, Pointer<> > p;
	RB_FAIL(rbIN_RANGE(b, b+3, Unique<false>(true).That(p)), analysis1);
}
