//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/richbool.hpp"

#ifdef RICHBOOL_USE_WX
#include "richbool/wxstring.hpp"
const char* compName = "wxString::Cmp";
#else
#include "richbool/stdstring.hpp"
const char* compName = "locale C";
#endif

#include "testable_analysis_with_strings.hpp"

using namespace RichBool;
using RichBool::detail::String;

class Person
{
public:
	Person(const String &f, const String &s, int by):
	  firstName(f), surName(s), birthYear(by) {}
    String firstName, surName;
    int birthYear;

	bool operator==(const Person &other) const
	{
		return (firstName==other.firstName)
			&& (surName==other.surName)
			&& (birthYear==other.birthYear);
	}
};

class EqualPersons
{
public:
    typedef MakeString Stringize1;
    typedef MakeString Stringize2;
	typedef bool Points;

    bool operator()(const Person &person1, const Person &person2) const
    {
        return person1==person2;
    }
	template<typename Expr1, typename Expr2>
    Analysis* Analyse(const Person &person1, const Person &person2,
				Expr1 , Expr2 ,
                bool giveAnalysisOnSuccess=false) const
    {
        bool ok = person1==person2;
        if (ok && !giveAnalysisOnSuccess)
            return 0;

#ifdef RICHBOOL_USE_WX
		CompareStrings<CompareCompletely<WxStringCmp, EqualRelation> > equalStrings;
#else
		CompareStrings<CompareCompletely<Collate, EqualRelation> > equalStrings;
#endif
		SharedAnalysis
			an1 = equalStrings.Analyse(person1.firstName, person2.firstName,
				(const char*)NULL, (const char*)NULL, true),
			an2 = equalStrings.Analyse(person1.surName, person2.surName,
				(const char*)NULL, (const char*)NULL, true),
			an3 = Equal<>().Analyse(person1.birthYear, person2.birthYear,
				(const char*)NULL, (const char*)NULL, true);

        GeneralAnalysis *analysis = new GeneralAnalysis(ok);
        analysis->AddText("first names: ")
            ->AddAnalysis(an1)
            ->AddNewLine()
			->AddText("surnames: ")
            ->AddAnalysis(an2)
            ->AddNewLine()
			->AddText("birth year: ")
            ->AddAnalysis(an3)
            ->AddNewLine();
        return analysis;
    }
};

#define rbEQUAL_PERSONS(person1, person2) rb2_RB(person1, person2, EqualPersons())
#define rbvEQUAL_PERSONS(person1, person2) rbv2_1_RB(person1, person2, EqualPersons())

RB_TEST(PersonsEqual)
{
	Person p1("Joe", "Average", 1980), p2("Joe", "Average", 1980);

	RB_PASS(rbEQUAL_PERSONS(p1, p2));
	RB_PASS_VB(rbvEQUAL_PERSONS(p1, p2), p1);
}

RB_TEST(PersonsDiffFirstName)
{
	const char *empty = NULL;

	SharedAnalysis
		analysis1 =
			new TestableAnalysisOfStrings(
				"Jo", "Joe",
				empty, empty,
				"MM2", " == ", compName),

		analysis2 =
			(new TestableAnalysisOfStrings(
				"Average", "Average",
				empty, empty,
				"MMMMMMM", " == ", compName))
			->MakeOk(),

		analysis3 = (Analysis*)MakeGeneralAnalysis(true)("1980", true)(" == ")("1980", true);

	SharedAnalysis analysis = (Analysis*)MakeGeneralAnalysis(false)
		("first names: ")(analysis1)()
		("surnames: ")(analysis2)()
		("birth year: ")(analysis3)();

	Person p1("Jo", "Average", 1980), p2("Joe", "Average", 1980);

	RB_FAIL(rbEQUAL_PERSONS(p1, p2), *analysis);
	RB_FAIL_VB(rbvEQUAL_PERSONS(p1, p2), *analysis, p1);
}

RB_TEST(PersonsDiffBirthYear)
{
	const char *empty = NULL;

	SharedAnalysis
		analysis1 =
			(new TestableAnalysisOfStrings(
				"Joe", "Joe",
				empty, empty,
				"MMM", " == ", compName))
			->MakeOk(),
		analysis2 =
			(new TestableAnalysisOfStrings(
				"Average", "Average",
				empty, empty,
				"MMMMMMM", " == ", compName))
			->MakeOk(),
		analysis3 = (Analysis*)MakeGeneralAnalysis(false)("1980", true)(" == ")("1981", true);

	SharedAnalysis analysis = (Analysis*)MakeGeneralAnalysis(false)
		("first names: ")(analysis1)()
		("surnames: ")(analysis2)()
		("birth year: ")(analysis3)();

	Person p1("Joe", "Average", 1980), p2("Joe", "Average", 1981);

	RB_FAIL(rbEQUAL_PERSONS(p1, p2), *analysis);
	RB_FAIL_VB(rbvEQUAL_PERSONS(p1, p2), *analysis, p1);
}
