//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICHBOOL_USE_WX
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include "rbtest.hpp"
#include "richbool/richbool.hpp"
#include "richbool/std.hpp"
#include "richbool/stdstring.hpp"
#include "testable_analysis_for_ranges.hpp"
#include "testable_analysis_with_strings.hpp"
#include "string_cmp.hpp"

#if defined(RICHBOOL_WIN)
    #include <windows.h>
#endif // #if defined(RICHBOOL_WIN)

#ifdef RICHBOOL_USE_WX
#include "richbool/wxstring.hpp"
#define STRINGCMP RichBool::WxStringCmp()
#else
#include "richbool/stdstring.hpp"
#define STRINGCMP RichBool::StringCompare()
#endif

using namespace RichBool;
using RichBool::detail::String;

class MyClass
{
public:
	MyClass(): a(0) {}
	MyClass(int n, const String &s): a(n), str(s) {}
	MyClass(const MyClass &obj): a(obj.a), str(obj.str) {}
	bool operator==(const MyClass &obj) const
	{
		return (a==obj.a) && (str==obj.str);
	}

	int a;
	String str;
};

RB_CONVERSION_HEADER(MyClass)
{
	str << val.a << ", " << val.str;
	return str;
}


static String strEndl;

struct InitEndl
{
	InitEndl()
	{
#ifdef RICHBOOL_USE_WX
		wxMemoryOutputStream memStream;
		wxTextOutputStream stream(memStream);
		endl(stream);
		int len = memStream.TellO();
		memStream.CopyTo(strEndl.GetWriteBuf(len), len);
		strEndl.UngetWriteBuf();
#else
		std::ostringstream strstr;
		detail::Endl(strstr);
		strEndl = strstr.str();
#endif
	}
} initEndl;

detail::String StreamOutShort(const Analysis &an)
{
#ifdef RICHBOOL_USE_WX
		wxMemoryOutputStream memStream;
		wxTextOutputStream stream(memStream);
		an.StreamOutShort(stream);
		int len = memStream.TellO();
		detail::String s;
		memStream.CopyTo(s.GetWriteBuf(len), len);
		s.UngetWriteBuf();
		return s;
#else
		std::ostringstream stream;
		an.StreamOutShort(stream);
		return stream.str();
#endif
}

// helper class to access Analysis::StreamOut
class StreamAnalysis: public Analysis
{
    StreamAnalysis(): Analysis(true) {}
public:
	static String ToString(const Analysis *analysis, int indent)
	{
#if defined(RICHBOOL_USE_WX)
		wxMemoryOutputStream memStream;
		wxTextOutputStream stream(memStream);
		analysis->StreamOut(stream, indent);
		wxString str;
		int len = memStream.TellO();
		memStream.CopyTo(str.GetWriteBuf(len), len);
		str.UngetWriteBuf();
		return str;
#else
		std::ostringstream strstr;
		analysis->StreamOut(strstr, indent);
		return strstr.str();
#endif
	}
};

class StubAnalysis: public Analysis
{
public:
    StubAnalysis(const char *text)
		: Analysis(true)
		, m_streamText(text)
	{}
	
	virtual void StreamOut(detail::OutStream &stream, int indent=0) const
	{
		stream << m_streamText;
	}

	virtual const detail::String& GetType() const
	{
		static detail::String str = "StubAnalysis";
		return str;
	}

protected:
	RichBool::detail::String m_streamText;
	virtual bool Equals(const Analysis* ) const
	{
		return true;
	}
};

RB_TEST(GetText)
{
	StubAnalysis analysis("123 ABC");
	RichBool::detail::String str = analysis.GetText();
	RB_ASSERT(rbSTRING_CS(str, ==, "123 ABC"));
}

RB_TEST(DefineStream)
{
	MyClass obj1(1, "abc"), obj2(3, "xyz");

	SharedAnalysis analysisEqual =
		(Analysis*)MakeGeneralAnalysis(false).expr("obj1", ":")("1, abc", true)
			(" == ").expr("obj2", ":")("3, xyz", true);

	RB_FAIL(rbEQUAL(obj1, obj2), *analysisEqual);
}


///////////////////////////////////////////////////////////
// tests for class GeneralAnalysis

RB_TEST(Stream_GeneralAnalysis_Ok)
{
	SharedAnalysis analysis =
		(Analysis*)MakeGeneralAnalysis(true)("1", true)
			(" == ")("1", true);

	String str = ToString(*analysis);
	RB_ASSERT(rbEQUAL(str, "<1> == <1> - ok"));
}

RB_TEST(Stream_GeneralAnalysis_With_Expressions_Ok)
{
	SharedAnalysis analysis =
		(Analysis*)MakeGeneralAnalysis(true).expr("a", ":")("1", true)
			(" == ").expr("b", ":")("1", true);

	String str = ToString(*analysis);
	RB_ASSERT(rbEQUAL(str, "`a':<1> == `b':<1> - ok"));
}

RB_TEST(Stream_GeneralAnalysis_With_Indices_Ok)
{
	SharedAnalysis analysis =
		(Analysis*)MakeGeneralAnalysis(true).idx(0, ":")("1", true)
			(" == ").idx(0, ":")("1", true);

	String str = ToString(*analysis);
	RB_ASSERT(rbEQUAL(str, "[0]:<1> == [0]:<1> - ok"));
}

RB_TEST(Stream_GeneralAnalysis_Ok_Indented)
{
	SharedAnalysis analysis =
		(Analysis*)MakeGeneralAnalysis(true)("1", true)
			(" == ")("1", true);

	String str = StreamAnalysis::ToString(&*analysis, 2);
	RB_ASSERT(rbEQUAL(str, "<1> == <1> - ok"));
}

RB_TEST(Stream_GeneralAnalysis_NotOk)
{
	SharedAnalysis analysis =
		(Analysis*)MakeGeneralAnalysis(false)("1", true)
			(" == ")("2", true);

	String str = ToString(*analysis);
	RB_ASSERT(rbEQUAL(str, "<1> == <2> - nok"));
}

RB_TEST(Stream_GeneralAnalysis_BadAddress)
{
	SharedAnalysis analysis =
		(Analysis*)MakeGeneralAnalysis(false)("1", true)
			(" == ")(GetNullPtrString(), false);

	String str = ToString(*analysis);
	RB_ASSERT(rbEQUAL(str, "<1> == @"+GetNullPtrString()+" - nok"));
}

RB_TEST(Stream_GeneralAnalysis_WithMyClass)
{
    MyClass obj1(1, "abc"), obj2(5, "xyz");

	SharedAnalysis analysis =
		(Analysis*)MakeGeneralAnalysis(false)(obj1, Value(), MakeString())
			(" == ")(obj2, Value(), MakeString());

	String str = ToString(*analysis);
	RB_ASSERT(rbEQUAL(str, "<1, abc> == <5, xyz> - nok"));
}

RB_TEST(Stream_GeneralAnalysis_WithEpilogue)
{
	SharedAnalysis analysis =
		(Analysis*)MakeGeneralAnalysis(true)("1", true).ep("epilogue");

	String str = ToString(*analysis);
	RB_ASSERT(rbEQUAL(str, "<1> - ok"+strEndl+"epilogue"));
}

RB_TEST(Stream_GeneralAnalysis_WithAnalysis)
{
	SharedAnalysis analysis1 =
		(Analysis*)MakeGeneralAnalysis(true)("1", true);

	SharedAnalysis analysis2 =
		(Analysis*)MakeGeneralAnalysis(true)("2", true)(" ")
			(analysis1);

	String str = ToString(*analysis2);
	RB_ASSERT(rbSTRING_(str, ==, "<2> <1> - ok - ok"));
}

RB_TEST(Stream_GeneralAnalysis_WithCoreAnalysis)
{
	SharedAnalysis analysis1 =
		(Analysis*)MakeGeneralAnalysis(false)("1", true);

	GeneralAnalysis *analysis2 = MakeGeneralAnalysis(true)("2", true)(" ");
	analysis2->SetCoreAnalysis(analysis1);

	String str = ToString(*analysis2);
	RB_ASSERT(rbSTRING_(str, ==, "<2> <1> - nok"));

	RB_ASSERT(analysis2->GetState()==Analysis::NotOk);

	delete analysis2;
}

RB_TEST(Stream_GeneralAnalysis_Ok_Negated)
{
	Analysis *analysis =
		MakeGeneralAnalysis(true)("1", true);
	analysis->Negate();

	String str = ToString(*analysis);
	RB_ASSERT(rbEQUAL(str, "!(<1>) - nok"));

	delete analysis;
}

RB_TEST(Stream_GeneralAnalysis_NotOk_Negated)
{
	Analysis *analysis =
		MakeGeneralAnalysis(false)("1", true);
	analysis->Negate();

	String str = ToString(*analysis);
	RB_ASSERT(rbEQUAL(str, "!(<1>) - ok"));

	delete analysis;
}

RB_TEST(Stream_GeneralAnalysis_Ok_NegatedTwice)
{
	Analysis *analysis =
		MakeGeneralAnalysis(true)("1", true);
	analysis->Negate();
	analysis->Negate();

	String str = ToString(*analysis);
	RB_ASSERT(rbEQUAL(str, "<1> - ok"));

	delete analysis;
}

RB_TEST(Stream_GeneralAnalysis_NotOk_NegatedTwice)
{
	Analysis *analysis =
		MakeGeneralAnalysis(false)("1", true);
	analysis->Negate();
	analysis->Negate();

	String str = ToString(*analysis);
	RB_ASSERT(rbEQUAL(str, "<1> - nok"));

	delete analysis;
}

RB_TEST(Stream_GeneralAnalysis_MaxValueLengthIs40)
{
	SharedAnalysis analysis =
		(Analysis*)MakeGeneralAnalysis(true)("12345678901234567890123456789012345678901234567890", true);

	String str = ToString(*analysis);
	RB_ASSERT(rbEQUAL(str, "<1234567890123456789012345678901234567890...> - ok"));
}

RB_TEST(Stream_GeneralAnalysis_SetMaxValueLengthTo20)
{
	GeneralAnalysis::SetMaximumValueLength(20);

	SharedAnalysis analysis =
		(Analysis*)MakeGeneralAnalysis(true)("12345678901234567890123456789012345678901234567890", true);

	String str = ToString(*analysis);
	RB_ASSERT(rbEQUAL(str, "<12345678901234567890...> - ok"));

	GeneralAnalysis::SetMaximumValueLength(40); // reset to default value
}


///////////////////////////////////////////////////////////
// tests for class AnalysisNotEvaluated

RB_TEST(Stream_AnalysisNotEvaluated)
{
    AnalysisNotEvaluated ne;

	String str = ToString(ne);
	RB_ASSERT(rbEQUAL(str, "not evaluated"));
}

RB_TEST(Stream_AnalysisNotEvaluated_Indented)
{
    AnalysisNotEvaluated ne;

	String str = StreamAnalysis::ToString(&ne, 2);
	RB_ASSERT(rbEQUAL(str, "not evaluated"));
}


///////////////////////////////////////////////////////////
// tests for class CombinedAnalysis

RB_TEST(Stream_CombinedAnalysis_False_False)
{
	Bool b1 = false, b2 = false;

	CombinedAnalysis ci(b1, b2, "&&", false);

	String str = ToString(ci);
	RB_ASSERT(rbEQUAL(str, "condition 1: nok"+strEndl+"&&"+strEndl+"condition 2: nok"));
}

RB_TEST(Stream_CombinedAnalysis_True_True)
{
	Bool b1 = true, b2 = true;

	CombinedAnalysis ci(b1, b2, "&&", false);

	String str = ToString(ci);
	RB_ASSERT(rbEQUAL(str, "condition 1: ok"+strEndl+"&&"+strEndl+"condition 2: ok"));
}

RB_TEST(Stream_CombinedAnalysis_True_True_Indented)
{
	Bool b1 = true, b2 = true;

	CombinedAnalysis ci(b1, b2, "&&", false);

	String str = StreamAnalysis::ToString(&ci, 2);
	RB_ASSERT(rbEQUAL(str, "condition 1: ok"+strEndl+"&&"+strEndl+"  condition 2: ok"));
}

RB_TEST(Stream_CombinedAnalysis_True_Analysis)
{
	Bool b1 = false, b2 = (Analysis*)MakeGeneralAnalysis(false)("abc");

	CombinedAnalysis ci(b1, b2, "&&", false);

	String str = ToString(ci);
	RB_ASSERT(rbSTRING_(str, ==, "condition 1: nok"+strEndl+"&&"+strEndl+"condition 2:"+strEndl+"  abc - nok"));
}

RB_TEST(Stream_CombinedAnalysis_True_Analysis_Indented)
{
	Bool b1 = false, b2 = (Analysis*)MakeGeneralAnalysis(false)("abc");

	CombinedAnalysis ci(b1, b2, "&&", false);

	String str = StreamAnalysis::ToString(&ci, 2);
	RB_ASSERT(rbSTRING_(str, ==, "condition 1: nok"+strEndl+"&&"+strEndl+"  condition 2:"+strEndl+"    abc - nok"));
}

RB_TEST(Stream_CombinedAnalysis_Analysis_Analysis_Indented)
{
	Bool b1 = (Analysis*)MakeGeneralAnalysis(false)("abc"),
		b2 = (Analysis*)MakeGeneralAnalysis(false)("xyz");

	CombinedAnalysis ci(b1, b2, "&&", false);

	String str = StreamAnalysis::ToString(&ci, 2);
	RB_ASSERT(rbSTRING_(str, ==, "condition 1:"+strEndl+"    abc - nok"+strEndl+"&&"+strEndl+
		"  condition 2:"+strEndl+"    xyz - nok"));
}

RB_TEST(Stream_CombinedAnalysis_False_False_Negated)
{
	Bool b1 = false, b2 = false;

	CombinedAnalysis ci(b1, b2, "&&", false);
	ci.Negate();

	String str = ToString(ci);
	RB_ASSERT(rbSTRING_(str, ==, "!("+strEndl+"condition 1: nok"+strEndl+"&&"+strEndl+"condition 2: nok"+strEndl+")"));
}


///////////////////////////////////////////////////////////
// tests for class CombinedAnalysis with short analyis

RB_TEST(Stream_CombinedAnalysis_Short_False_False)
{
	Bool b1 = false, b2 = false;

	CombinedAnalysis ci(b1, b2, "&&", false);

	String str = StreamOutShort(ci);
	RB_ASSERT(rbEQUAL(str, "(nok && nok) - nok"));
}

RB_TEST(Stream_CombinedAnalysis_Short_True_True)
{
	Bool b1 = true, b2 = true;

	CombinedAnalysis ci(b1, b2, "&&", true);

	String str = StreamOutShort(ci);
	RB_ASSERT(rbEQUAL(str, "(ok && ok) - ok"));
}

RB_TEST(Stream_CombinedAnalysis_Short_True_Analysis)
{
	Bool b1 = false, b2 = (Analysis*)MakeGeneralAnalysis(false)("abc");

	CombinedAnalysis ci(b1, b2, "&&", false);

	String str = StreamOutShort(ci);
	RB_ASSERT(rbEQUAL(str, "(nok && abc - nok) - nok"));
}

RB_TEST(Stream_CombinedAnalysis_Short_False_False_Negated)
{
	Bool b1 = false, b2 = false;

	CombinedAnalysis ci(b1, b2, "&&", false);
	ci.Negate();

	String str = StreamOutShort(ci);
	RB_ASSERT(rbSTRING_(str, ==, "!(nok && nok) - ok"));
}


///////////////////////////////////////////////////////////
// tests for class Single

RB_TEST(Stream_Single_Valid)
{
	Single analysis(1, 2, "text", new TextExpression("expr"), true);

	String str = ToString(analysis);
	RB_ASSERT(rbEQUAL(str, " X `expr':<text> - nok"));
}

RB_TEST(Stream_Single_Valid_Indented)
{
	Single analysis(1, 2, "text", new TextExpression("expr"), true);

	String str = StreamAnalysis::ToString(&analysis, 2);
	RB_ASSERT(rbEQUAL(str, " X `expr':<text> - nok"));
}

RB_TEST(Stream_Single_NotValid)
{
	Single analysis(1, 2, GetNullPtrString(), new TextExpression("expr"), false);

	String str = ToString(analysis);
	RB_ASSERT(rbEQUAL(str, " X `expr':@"+GetNullPtrString()+" - nok"));
}


///////////////////////////////////////////////////////////
// tests for class AnalysisOfRange

RB_TEST(Stream_AnalysisOfRange_Empty)
{
	TestableAnalysisOfContainers analysis("ranges equal ",
		"vec1", "vec2");

	String str = ToString(analysis);
	RB_ASSERT(rbEQUAL(str, "ranges equal `vec1' and `vec2' - nok"));
}

RB_TEST(Stream_AnalysisOfRange_Empty_Indented)
{
	TestableAnalysisOfContainers analysis("ranges equal ",
		"vec1", "vec2");

	String str = StreamAnalysis::ToString(&analysis, 2);
	RB_ASSERT(rbEQUAL(str, "ranges equal `vec1' and `vec2' - nok"));
}

RB_TEST(Stream_AnalysisOfRange_OneAnalysis)
{
	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(false)("1", true)(" == ")("2", true)
	};

	TestableAnalysisOfContainers analysis("ranges have different content ",
		"vec1", "vec2");
	analysis.AddAnalyses(arrAnalysis, 1);

	String str = ToString(analysis);
	RB_ASSERT(rbEQUAL(str, "ranges have different content `vec1' and `vec2' - nok"+strEndl+
	                            "X: <1> == <2> - nok"));
}

RB_TEST(Stream_AnalysisOfRange_OneAnalysis_Indented)
{
	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(false)("1", true)(" == ")("2", true)
	};

	TestableAnalysisOfContainers analysis("ranges have different content ",
		"vec1", "vec2");
	analysis.AddAnalyses(arrAnalysis, 1);

	String str = StreamAnalysis::ToString(&analysis, 2);
	RB_ASSERT(rbEQUAL(str, "ranges have different content `vec1' and `vec2' - nok"+strEndl+
	                            "  X: <1> == <2> - nok"));
}

RB_TEST(Stream_AnalysisOfRange_TwoAnalyses)
{
	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(true)("1", true)(" == ")("1", true),
		MakeGeneralAnalysis(false)("1", true)(" == ")("2", true),
	};

	TestableAnalysisOfContainers analysis("ranges have different content ",
		"vec1", "vec2");
	analysis.AddAnalyses(arrAnalysis, 2);

	String str = ToString(analysis);
	RB_ASSERT(rbEQUAL(str, "ranges have different content `vec1' and `vec2' - nok"+strEndl+
	                            "M: <1> == <1> - ok"+strEndl+
								"X: <1> == <2> - nok"));
}

RB_TEST(Stream_AnalysisOfRange_OneNullAnalysis)
{
	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(false)("1", true)(" == ")("2", true),
		0
	};

	TestableAnalysisOfContainers analysis("ranges have different content ",
		"vec1", "vec2");
	analysis.AddAnalyses(arrAnalysis, 2);

	String str = ToString(analysis);
	RB_ASSERT(rbSTRING(str, ==, "ranges have different content `vec1' and `vec2' - nok"+strEndl+
	                            "X: <1> == <2> - nok"+strEndl+
								"M: ok", STRINGCMP));
}

RB_TEST(Stream_AnalysisOfRange_OneNullAnalysis_Indent)
{
	Analysis *arrAnalysis[] = {
		MakeGeneralAnalysis(false)("1", true)(" == ")("2", true),
		0
	};

	TestableAnalysisOfContainers analysis("ranges have different content ",
		"vec1", "vec2");
	analysis.AddAnalyses(arrAnalysis, 2);

	String str = StreamAnalysis::ToString(&analysis, 2);
	RB_ASSERT(rbSTRING(str, ==, "ranges have different content `vec1' and `vec2' - nok"+strEndl+
	                            "  X: <1> == <2> - nok"+strEndl+
								"  M: ok", STRINGCMP));
}

RB_TEST(Stream_AnalysisOfRange_TwoSingles)
{
	Analysis *arrAnalysis[] = {
		new Single(0, 2, "5", new IndexExpression(0), true),
		new Single(1, 2, "6", new IndexExpression(0), true)
	};

	TestableAnalysisOfContainers analysis("ranges have different content ",
		"vec1", "vec2");
	analysis.AddAnalyses(arrAnalysis, 2);

	String str = StreamAnalysis::ToString(&analysis, 2);
	RB_ASSERT(rbSTRING(str, ==, "ranges have different content `vec1' and `vec2' - nok"+strEndl+
		"  1: [0]:<5> X  - nok"+strEndl+
		"  2:  X [0]:<6> - nok", STRINGCMP));
}

RB_TEST(Stream_AnalysisOfRange_Empty_NoText)
{
	TestableAnalysisOfContainers analysis("ranges equal",
		NULL, NULL);

	String str = ToString(analysis);
	RB_ASSERT(rbEQUAL(str, "ranges equal - nok"));
}


///////////////////////////////////////////////////////////
// tests for class AnalysisOfStrings

RB_TEST(StringsNoEscape)
{
	TestableAnalysisOfStrings analysis("abc", "abd", "str1", "str2", "MMX",
		" == ", "locale C");

	String str = ToString(analysis);
	String expected =
		"`str1':<abc> == `str2':<abd> (locale C) - nok"+strEndl+
		"str1: abc"+strEndl+
		"diff: ..x"+strEndl+
		"str2: abd";
	RB_ASSERT(rbEQUAL(str, expected));
}

RB_TEST(StringsWithEscape)
{
	TestableAnalysisOfStrings analysis("ab\nc", "abc\xa0", "str1", "str2", "MMXX",
		" == ", "locale C");

	String str = ToString(analysis);
	String expected =
		"`str1':<ab\\nc> == `str2':<abc\\xa0> (locale C) - nok"+strEndl+
		"str1: ab\\n   c"+strEndl+
		"diff: .. x   x"+strEndl+
		"str2: ab c\\xa0";
	RB_ASSERT(rbEQUAL(str, expected));
}

RB_TEST(StringsMore)
{
	TestableAnalysisOfStrings analysis("abcde", "abdef", "str1", "str2", "MMX  ",
		" > ", "locale C");

	String str = ToString(analysis);
	String expected =
		"`str1':<abcde> > `str2':<abdef> (locale C) - nok"+strEndl+
		"str1: abcde"+strEndl+
		"diff: ..x.."+strEndl+
		"str2: abdef";
	RB_ASSERT(rbEQUAL(str, expected));
}

RB_TEST(StringsNoEscape_SideBySide)
{
	TestableAnalysisOfStringsSideBySide analysis("abc", "abd", "str1", "str2", "MMX",
		" == ", "locale C");

	String str = ToString(analysis);
	String expected =
		"abc   abd"+strEndl+
		"  ^<->  ^";
	RB_ASSERT(rbEQUAL(str, expected));
}

RB_TEST(StringsWithEscape_SideBySide)
{
	TestableAnalysisOfStringsSideBySide analysis("ab\nc", "abc\xa0", "str1", "str2", "MMXX",
		" == ", "locale C");

	String str = ToString(analysis);
	String expected =
		"ab\\nc   abc\\xa0"+strEndl+
		"  ^^^<->  ^^^^^";
	RB_ASSERT(rbSTRING_CS(str, ==, expected));
}

RB_TEST(StringsMore_SideBySide)
{
	TestableAnalysisOfStringsSideBySide analysis("abcde", "abdef", "str1", "str2", "MMX  ",
		" > ", "locale C");

	String str = ToString(analysis);
	String expected =
		"abcde   abdef"+strEndl+
		"  ^  <->  ^  ";
	RB_ASSERT(rbEQUAL(str, expected));
}

RB_TEST(StringsUnmatched_SideBySide)
{
	TestableAnalysisOfStringsSideBySide analysis("abxc", "abcy", "str1", "str2", "MM1M2",
		" > ", "locale C");

	String str = ToString(analysis);
	String expected =
		"abxc   abcy"+strEndl+
		"  ^ <->   ^";
	RB_ASSERT(rbEQUAL(str, expected));
}

RB_TEST(StringsEqual_ToUpper)
{
	TestableAnalysisOfStrings analysis("abc", "ABD", "str1", "str2", "MMX",
		" == ", "toupper");

	String str = ToString(analysis);
	String expected =
		"`str1':<abc> == `str2':<ABD> (toupper) - nok"+strEndl+
		"str1: abc"+strEndl+
		"diff: ..x"+strEndl+
		"str2: ABD";
	RB_ASSERT(rbEQUAL(str, expected));
}

RB_TEST(StringsEqual_Above0x80)
{
	TestableAnalysisOfStrings analysis("y\xa0", "\xa0y", "str1", "str2", "XX",
		" == ", "locale C");

	String str = ToString(analysis);
	String expected =
		"`str1':<y\\xa0> == `str2':<\\xa0y> (locale C) - nok"+strEndl+
		"str1:    y\\xa0"+strEndl+
		"diff:    x   x"+strEndl+
		"str2: \\xa0   y";
	RB_ASSERT(rbEQUAL(str, expected));
}

#ifdef RICHBOOL_HAS_WSTRING
RB_TEST(WStringsWithEscape)
{
	TestableAnalysisOfWStrings analysis(L"ab\nc", L"abc\xaaaa", "str1", "str2", "MMXX",
		" == ", "locale C");

	String str = ToString(analysis);
	String expected =
		"`str1':<ab\\nc> == `str2':<abc\\xaaaa> (locale C) - nok"+strEndl+
		"str1: ab\\n     c"+strEndl+
		"diff: .. x     x"+strEndl+
		"str2: ab c\\xaaaa";
	RB_ASSERT(rbEQUAL(str, expected));
}

RB_TEST(WStringsWithEscape_SideBySide)
{
	TestableAnalysisOfWStringsSideBySide analysis(L"ab\nc", L"abc\xaaaa", "str1", "str2", "MMXX",
		" == ", "locale C");

	String str = ToString(analysis);
	String expected =
		"ab\\nc   abc\\xaaaa"+strEndl+
		"  ^^^<->  ^^^^^^^";
	RB_ASSERT(rbSTRING_CS(str, ==, expected));
}
#endif

RB_TEST(LongStringsEqual_EachPartDifferent)
{
	TestableAnalysisOfStrings analysis(
		"123456789012345678901234567890123456789012345678901234567890",
		"123456789x1234567890123456789012345678901234567890123456789x",
		"str1", "str2",
		"MMMMMMMMMXMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMX",
		" == ", "locale C");

	String str = ToString(analysis);
	String expected =
		"`str1':<1234567890123456789012345678901234567890...> "
		"== `str2':<123456789x123456789012345678901234567890...> (locale C) - nok"+strEndl+
		"str1: 1234567890123456789012345678901234567890"+strEndl+
		"diff: .........x.............................."+strEndl+
		"str2: 123456789x123456789012345678901234567890"+strEndl+
		strEndl+
		"str1: 12345678901234567890"+strEndl+
		"diff: ...................x"+strEndl+
		"str2: 1234567890123456789x";
	RB_ASSERT(rbSTRING(str, ==, expected, STRINGCMP));
}

RB_TEST(LongStringsEqual_FirstPartDifferent)
{
	TestableAnalysisOfStrings analysis(
		"123456789012345678901234567890123456789012345678901234567890",
		"123456789x12345678901234567890123456789012345678901234567890",
		"str1", "str2",
		"MMMMMMMMMXMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
		" == ", "locale C");

	String str = ToString(analysis);
	String expected =
		"`str1':<1234567890123456789012345678901234567890...> "
		"== `str2':<123456789x123456789012345678901234567890...> (locale C) - nok"+strEndl+
		"str1: 1234567890123456789012345678901234567890"+strEndl+
		"diff: .........x.............................."+strEndl+
		"str2: 123456789x123456789012345678901234567890"+strEndl+
		strEndl+
		"str1: 12345678901234567890"+strEndl+
		"same: ...................."+strEndl+
		"str2: 12345678901234567890";
	RB_ASSERT(rbSTRING(str, ==, expected, STRINGCMP));
}

///////////////////////////////////////////////////////////
// tests for class BriefAnalysisOfTwoSequences

RB_TEST(BriefAnalysisOfTwoSequences)
{
	BriefAnalysisOfTwoSequences analysis(false, new TextExpression("a"), new TextExpression("b"),
		"value ", " has bits ", " on");
	analysis.SetString1   ("00111100");
	analysis.SetString2   ("00001111");
	analysis.SetStringDiff("      XX");

	String str = ToString(analysis);

	String expected = "value `a' has bits `b' on - nok"+strEndl+
		"1: 00111100"+strEndl+
		"C:       XX"+strEndl+
		"2: 00001111";

	RB_ASSERT(rbEQUAL(str, expected));
}

RB_TEST(BriefAnalysisOfTwoSequences_WithBlockSize)
{
	BriefAnalysisOfTwoSequences analysis(false, new TextExpression("a"), new TextExpression("b"),
		"value ", " has bits ", " on");
	analysis.SetString1   ("00111100");
	analysis.SetString2   ("00001111");
	analysis.SetStringDiff("      XX");
	analysis.SetBlockSize(2);

	String str = ToString(analysis);

	String expected = "value `a' has bits `b' on - nok"+strEndl+
		"1: 00 11 11 00"+strEndl+
		"C:          XX"+strEndl+
		"2: 00 00 11 11";

	RB_ASSERT(rbEQUAL(str, expected));
}

RB_TEST(BriefAnalysisOfTwoSequences_WithBlockSizeAndBlocksPerLine)
{
	BriefAnalysisOfTwoSequences analysis(false, new TextExpression("a"), new TextExpression("b"),
		"value ", " has bits ", " on");
	analysis.SetString1   ("00111100");
	analysis.SetString2   ("00001111");
	analysis.SetStringDiff("      XX");
	analysis.SetBlockSize(2);
	analysis.SetBlocksPerLine(2);

	String str = ToString(analysis);

	String expected = "value `a' has bits `b' on - nok"+strEndl+
		"1: 00 11"+strEndl+
		"C:      "+strEndl+
		"2: 00 00"+strEndl+
		""+strEndl+
		"1: 11 00"+strEndl+
		"C:    XX"+strEndl+
		"2: 11 11"+strEndl;

	RB_ASSERT(rbEQUAL(str, expected));
}

RB_TEST(BriefAnalysisOfTwoSequences_WithBlockSizeAndBlocksPerLine_IncompleteLastLine)
{
	BriefAnalysisOfTwoSequences analysis(false, new TextExpression("a"), new TextExpression("b"),
		"value ", " has bits ", " on");
	analysis.SetString1   ("001100");
	analysis.SetString2   ("000011");
	analysis.SetStringDiff("    XX");
	analysis.SetBlockSize(2);
	analysis.SetBlocksPerLine(2);

	String str = ToString(analysis);

	String expected = "value `a' has bits `b' on - nok"+strEndl+
		"1: 00 11"+strEndl+
		"C:      "+strEndl+
		"2: 00 00"+strEndl+
		""+strEndl+
		"1: 00"+strEndl+
		"C: XX"+strEndl+
		"2: 11"+strEndl;

	RB_ASSERT(rbEQUAL(str, expected));
}

RB_TEST(BriefAnalysisOfTwoSequences_WithBlockSizeAndBlocksPerLine_IncompleteLastBlock)
{
	BriefAnalysisOfTwoSequences analysis(false, new TextExpression("a"), new TextExpression("b"),
		"value ", " has bits ", " on");
	analysis.SetString1   ("00110");
	analysis.SetString2   ("00001");
	analysis.SetStringDiff("    X");
	analysis.SetBlockSize(2);
	analysis.SetBlocksPerLine(2);

	String str = ToString(analysis);

	String expected = "value `a' has bits `b' on - nok"+strEndl+
		"1: 00 11"+strEndl+
		"C:      "+strEndl+
		"2: 00 00"+strEndl+
		""+strEndl+
		"1: 0"+strEndl+
		"C: X"+strEndl+
		"2: 1"+strEndl;

	RB_ASSERT(rbEQUAL(str, expected));
}

RB_TEST(BriefAnalysisOfTwoSequences_OtherTitles)
{
	BriefAnalysisOfTwoSequences analysis(false, new TextExpression("a"), new TextExpression("b"),
		"value ", " has bits ", " on");
	analysis.SetString1   ("00111100");
	analysis.SetString2   ("00001111");
	analysis.SetStringDiff("      XX");

	analysis.SetTitle1("bits");
	analysis.SetTitle2("mask");
	analysis.SetTitleDiff("err ");

	String str = ToString(analysis);

	String expected = "value `a' has bits `b' on - nok"+strEndl
		+"bits: 00111100"+strEndl
		+"err :       XX"+strEndl
		+"mask: 00001111";

	RB_ASSERT(rbEQUAL(str, expected));
}


// other tests

RB_TEST(Ptr)
{
	int *p = 0;
	String str = PtrToString(p);
	RB_ASSERT(rbEQUAL(str, GetNullPtrString()));
}

RB_TEST(EscapeChar_Regular)
{
	String str = detail::EscapeChar('a');
	RB_ASSERT(rbEQUAL(str, "a"));
}

RB_TEST(EscapeChar_0)
{
	String str = detail::EscapeChar('\0');
	RB_ASSERT(rbEQUAL(str, "\\x00"));
}

RB_TEST(EscapeChar_0x12)
{
	String str = detail::EscapeChar('\x12');
	RB_ASSERT(rbEQUAL(str, "\\x12"));
}

RB_TEST(EscapeChar_0xa0)
{
	String str = detail::EscapeChar('\xa0');
	RB_ASSERT(rbEQUAL(str, "\\xa0"));
}

RB_TEST(EscapeChar_Slash)
{
	String str = detail::EscapeChar('\\');
	RB_ASSERT(rbEQUAL(str, "\\\\"));
}

RB_TEST(EscapeChar_Tab)
{
	String str = detail::EscapeChar('\t');
	RB_ASSERT(rbEQUAL(str, "\\t"));
}

RB_TEST(EscapeChar_Newline)
{
	String str = detail::EscapeChar('\n');
	RB_ASSERT(rbEQUAL(str, "\\n"));
}

RB_TEST(EscapeChar_Return)
{
	String str = detail::EscapeChar('\r');
	RB_ASSERT(rbEQUAL(str, "\\r"));
}

RB_TEST(CharToString_Regular)
{
	String str = RichBool::ToString('a');
	RB_ASSERT(rbEQUAL(str, "a"));
}

RB_TEST(CharToString_0)
{
	String str = RichBool::ToString('\0');
	RB_ASSERT(rbEQUAL(str, "\\x00"));
}

RB_TEST(CharToString_0x12)
{
	String str = RichBool::ToString('\x12');
	RB_ASSERT(rbEQUAL(str, "\\x12"));
}

RB_TEST(CharToString_0xa0)
{
	String str = RichBool::ToString('\xa0');
	RB_ASSERT(rbEQUAL(str, "\\xa0"));
}


///////////////////////////////////////////////////////////
// const char* to string

RB_TEST(ConstCharPtrToString)
{
	String str = RichBool::ToString("\\\t\xa0");
	RB_ASSERT(rbEQUAL(str, "\\\\\\t\\xa0"));
}

RB_TEST(ConstCharNullPtrToString)
{
	const char *sz=NULL;
	String str = RichBool::ToString(sz);
	RB_ASSERT(rbEQUAL(str, "\\NULL"));
}

RB_TEST(ConstUCharPtrToString)
{
	String str = RichBool::ToString((const unsigned char*)"\\\t\xa0");
	RB_ASSERT(rbEQUAL(str, "\\\\\\t\\xa0"));
}

RB_TEST(CharPtrToString)
{
	char *sz = new char[4];
	strcpy(sz, "\\\t\xa0");
	String str = RichBool::ToString(sz);
	RB_ASSERT(rbEQUAL(str, "\\\\\\t\\xa0"));
	delete sz;
}

RB_TEST(UCharPtrToString)
{
	unsigned char *sz = new unsigned char[4];
	strcpy((char*)sz, "\\\t\xa0");
	String str = RichBool::ToString(sz);
	RB_ASSERT(rbEQUAL(str, "\\\\\\t\\xa0"));
	delete sz;
}


///////////////////////////////////////////////////////////
// String to String

RB_TEST(StringToString)
{
	String test = "\\0\t\xa0";
	test[1] = '\0';
	String str = RichBool::ToString(test);
	RB_ASSERT(rbEQUAL(str, "\\\\\\x00\\t\\xa0"));
}

RB_TEST(UCharToString_Regular)
{
	unsigned char ch = 'a';
	String str = RichBool::ToString(ch);
	RB_ASSERT(rbEQUAL(str, "a"));
}

RB_TEST(UCharToString_0)
{
	unsigned char ch = '\0';
	String str = RichBool::ToString(ch);
	RB_ASSERT(rbEQUAL(str, "\\x00"));
}

RB_TEST(UCharToString_0x12)
{
	unsigned char ch = '\x12';
	String str = RichBool::ToString(ch);
	RB_ASSERT(rbEQUAL(str, "\\x12"));
}

RB_TEST(UCharToString_0xa0)
{
	unsigned char ch = (unsigned char)'\xa0';
	String str = RichBool::ToString(ch);
	RB_ASSERT(rbEQUAL(str, "\\xa0"));
}

RB_TEST(EscapeWChar_Regular)
{
	String str = detail::EscapeChar(L'a');
	RB_ASSERT(rbEQUAL(str, "a"));
}

RB_TEST(EscapeWChar_0)
{
	String str = detail::EscapeChar(L'\0');
	RB_ASSERT(rbEQUAL(str, "\\x0000"));
}

RB_TEST(EscapeWChar_0x12)
{
	String str = detail::EscapeChar(L'\x12');
	RB_ASSERT(rbEQUAL(str, "\\x0012"));
}

RB_TEST(EscapeWChar_0xabcd)
{
	String str = detail::EscapeChar(L'\xabcd');
	RB_ASSERT(rbEQUAL(str, "\\xabcd"));
}

#if !RICHBOOL_WCHAR_T_IS_USHORT

RB_TEST(WCharToString_Regular)
{
	String str = RichBool::ToString(L'a');
	RB_ASSERT(rbEQUAL(str, "a"));
}

RB_TEST(WCharToString_0)
{
	String str = RichBool::ToString(L'\0');
	RB_ASSERT(rbEQUAL(str, "\\x0000"));
}

RB_TEST(WCharToString_0x12)
{
	String str = RichBool::ToString(L'\x12');
	RB_ASSERT(rbEQUAL(str, "\\x0012"));
}

RB_TEST(WCharToString_0xabcd)
{
	wchar_t ch = L'\xabcd';
	String str = RichBool::ToString(ch);
	RB_ASSERT(rbEQUAL(str, "\\xabcd"));
}

RB_TEST(ConstWCharPtrToString_a)
{
	const wchar_t *sz=L"a";
	String str = RichBool::ToString(sz);
	RB_ASSERT(rbEQUAL(str, "a"));
}

RB_TEST(ConstWCharPtrToString_a0xabcd)
{
	const wchar_t *sz=L"a\xabcd";
	String str = RichBool::ToString(sz);
	RB_ASSERT(rbEQUAL(str, "a\\xabcd"));
}

RB_TEST(ConstWCharNullPtrToString)
{
	const wchar_t *sz=NULL;
	String str = RichBool::ToString(sz);
	RB_ASSERT(rbEQUAL(str, "\\NULL"));
}

#endif

RB_TEST(Short_0)
{
	short s=0;

	String str = ToString(s);
	RB_ASSERT(rbEQUAL(str, "0"));
}

RB_TEST(Short_1)
{
	short s=1;

	String str = ToString(s);
	RB_ASSERT(rbEQUAL(str, "1"));
}

RB_TEST(Short_Max)
{
	short s=32767;

	String str = ToString(s);
	RB_ASSERT(rbEQUAL(str, "32767"));
}

RB_TEST(Short_Min)
{
	short s=-32768;

	String str = ToString(s);
	RB_ASSERT(rbEQUAL(str, "-32768"));
}

RB_TEST(UShort_0)
{
	unsigned short s=0;

	String str = ToString(s);
	RB_ASSERT(rbEQUAL(str, "0"));
}

RB_TEST(UShort_1)
{
	unsigned short s=1;

	String str = ToString(s);
	RB_ASSERT(rbEQUAL(str, "1"));
}

RB_TEST(UShort_Max)
{
	unsigned short s=65535;

	String str = ToString(s);
	RB_ASSERT(rbEQUAL(str, "65535"));
}

RB_TEST(VoidPtrNULL)
{
	void *p=NULL;

	String str = ToString(p);
	RB_ASSERT(rbOR(rbOR_BE(rbEQUAL(str, "0x00000000"), rbEQUAL(str, "0x0000000000000000")),
		 rbEQUAL(str, "(nil)")));
}

RB_TEST(ConstVoidPtrNULL)
{
	const void *p=NULL;

	String str = ToString(p);
	RB_ASSERT(rbOR(rbOR_BE(rbEQUAL(str, "0x00000000"), rbEQUAL(str, "0x0000000000000000")),
		 rbEQUAL(str, "(nil)")));
}

RB_TEST(IntPtrNULL)
{
	int *p=NULL;

	String str = ToString(p);
	RB_ASSERT(rbOR(rbOR_BE(rbEQUAL(str, "0x00000000"), rbEQUAL(str, "0x0000000000000000")),
		 rbEQUAL(str, "(nil)")));
}

#if defined(RICHBOOL_WIN)

RB_TEST(LargeInteger_0)
{
	LARGE_INTEGER li;
	li.QuadPart = 0;

	String str = ToString(li);
	RB_ASSERT(rbEQUAL(str, "0"));
}

RB_TEST(LargeInteger_Minus1)
{
	LARGE_INTEGER li;
	li.QuadPart = -1;

	String str = ToString(li);
	RB_ASSERT(rbEQUAL(str, "-1"));
}

RB_TEST(LargeInteger_Big)
{
	LARGE_INTEGER li;
	li.HighPart = 100;
	li.LowPart = 100;

	String str = ToString(li);
	RB_ASSERT(rbEQUAL(str, "429496729700"));
}

RB_TEST(ULargeInteger_0)
{
	ULARGE_INTEGER uli;
	uli.QuadPart = 0;

	String str = ToString(uli);
	RB_ASSERT(rbEQUAL(str, "0"));
}

RB_TEST(ULargeInteger_Maximum)
{
	ULARGE_INTEGER uli;
	uli.LowPart = (DWORD)-1;
	uli.HighPart = (DWORD)-1;

	String str = ToString(uli);
	RB_ASSERT(rbEQUAL(str, "18446744073709551615"));
}

RB_TEST(ULargeInteger_Big)
{
	ULARGE_INTEGER uli;
	uli.HighPart = 100;
	uli.LowPart = 100;

	String str = ToString(uli);
    RB_ASSERT(rbEQUAL(str, "429496729700"));
}

#if !defined(RICHBOOL_USE_WX) && (!defined(_MSC_VER)||(_MSC_VER > 1300))

// with VC 6.0 ostream doesn't seem to accept __int64

RB_TEST(__int64)
{
#ifdef _MSVC
	__int64 n = 2123456798*100;
#else
	long long n = 2123456798;
	n *= 100;
#endif

	String str = ToString(n);
	RB_ASSERT(rbEQUAL(str, "212345679800"));
}

RB_TEST(u__int64)
{
#ifdef _MSVC
	unsigned __int64 n = 212345679800;
#else
	unsigned long long n = 2123456798;
	n *= 100;
#endif

	String str = ToString(n);
	RB_ASSERT(rbEQUAL(str, "212345679800"));
}
#endif // #if !defined(RICHBOOL_USE_WX)

#endif // #if defined(RICHBOOL_WIN)


#if defined(RICHBOOL_USE_WX) && defined(RICHBOOL_WIN)

#if wxCHECK_VERSION(2, 6, 3)

RB_TEST(wxLongLong)
{
	wxLongLong n = 429496729700;

	String str = ToString(n);
	RB_ASSERT(rbEQUAL(str, "429496729700"));
}

RB_TEST(wxULongLong)
{
	wxULongLong n = 429496729700;

	String str = ToString(n);
	RB_ASSERT(rbEQUAL(str, "429496729700"));
}

#if defined wxLongLong_t && !defined wxLongLongIsLong
RB_TEST(wxLongLong_t)
{
	// This fails with some versions of WxWidgets:
	wxLongLong_t n = 429496729700;

	String str = ToString(n);
	RB_ASSERT(rbEQUAL(str, "429496729700"));
}
#endif

#if defined wxULongLong_t && !defined wxLongLongIsLong
RB_TEST(wxULongLong_t)
{
	// This fails with some versions of WxWidgets:
	wxULongLong_t n = 429496729700;

	String str = ToString(n);
	RB_ASSERT(rbEQUAL(str, "429496729700"));
}
#endif

#endif // #if wxCHECK_VERSION(2, 6, 3)

#endif // #if defined(RICHBOOL_USE_WX)

////////////////////////////////////////////////
// custom ToString in RichBool namespace

struct StubToStringInRB
{
	StubToStringInRB(int a_): a(a_) {}
	int a;
};

namespace RichBool
{
	template <>
	inline detail::String ToString<StubToStringInRB>(const StubToStringInRB &a)
	{
		return ToString(a.a);
	}
}

RB_TEST(CustomToStringInRB)
{
	SharedAnalysis analysis =
		(Analysis*)MakeGeneralAnalysis(true)(StubToStringInRB(7), Value(), MakeString());

	String str = ToString(*analysis);
	RB_ASSERT(rbEQUAL(str, "<7> - ok"));
}


// MSVC++ 6.0 has difficulty with the overload of the template function
#if !defined(_MSC_VER) || (_MSC_VER > 1300)

////////////////////////////////////////////////
// custom ToString in default namespace

struct StubToString
{
	explicit StubToString(int a_): a(a_) {}
	int a;
};

inline detail::String ToString(const StubToString &a)
{
	return RichBool::ToString(a.a);
}

RB_TEST(CustomToString)
{
	SharedAnalysis analysis =
		(Analysis*)MakeGeneralAnalysis(true)(StubToString(7), Value(), MakeString());

	String str = ToString(*analysis);
	RB_ASSERT(rbEQUAL(str, "<7> - ok"));
}



////////////////////////////////////////////////
// custom ToString in other namespace

namespace Other
{
	struct StubToStringOther
	{
		explicit StubToStringOther(int n_): n(n_) {}
		int n;
	};

	inline detail::String ToString(const StubToStringOther &a)
	{
		return RichBool::ToString(a.n);
	}
}

RB_TEST(CustomToStringOther)
{
	SharedAnalysis analysis =
		(Analysis*)MakeGeneralAnalysis(true)(Other::StubToStringOther(7), Value(), MakeString());

	String str = ToString(*analysis);
	RB_ASSERT(rbEQUAL(str, "<7> - ok"));
}

#endif
