//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_TEST_H__QM
#define RICH_BOOL_TEST_H__QM

#include "richbool/analysis.hpp"
#include "richbool/richbool.hpp"

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif

class RichBoolTest
{
public:
	RichBoolTest(const char *name, const char *file, int line);
	virtual void run() = 0;

	const char* GetName() const { return m_name; }
	const char* GetFile() const { return m_file; }
	int GetLine() const { return m_line; }

	static void RunTests();
	static int GetNrTests() { return s_nrTests; }
	static int GetLevel() { return s_level; }
	static void SetLevel(int l) { s_level=l; }

private:
	RichBoolTest *m_next;
	const char *m_name;
	const char *m_file;
	int m_line;
	static RichBoolTest *s_tests;
	static int s_nrTests;
	static int s_level;
};

#define RB_TEST(NAME) \
	class RichBoolTest##NAME: public RichBoolTest \
	{ \
	public: \
		RichBoolTest##NAME(): RichBoolTest(#NAME, __FILE__, __LINE__) {} \
		virtual void run(); \
	} richBoolTest##NAME; \
	void RichBoolTest##NAME::run()

namespace RichBool { class Bool; }

void rbPass(const RichBool::Bool &b,
			const char *szFile,
			int line);

void rbPassBool(bool b,
			bool isRich,
			const char *szFile,
			int line);

int GetNrPassOK();
int GetNrPassNOK();
int GetNrAssertionsFailed();

void rbFail(const RichBool::Bool &b,
			const RichBool::Analysis &analysis,
			const char *szFile,
			int line);

void rbAssertFailed(const RichBool::Bool &b,
					const char *szFile,
					int line);

int GetNrEqualOK();
int GetNrEqualNOK();
int GetNrUncaughtExceptions();

template <class RB, typename T>
void rbPassIV(RB rb,
			const char *sz,
			const T &t,
			const char *szFile,
			int line)
{
	switch (RichBoolTest::GetLevel())
	{
	case 0:
		rbPass(true, szFile, line);
		break;
	case 1:
		rbPass(rb(t), szFile, line);
		break;
	case 2:
		rbPass(rb.Analyse(t, sz), szFile, line);
		break;
	case 3:
		rbPass(rb.Analyse(t, sz, true), szFile, line);
		break;
	}
}

template <class RB, typename T, typename U>
void rbPassV(RB rb,
			const char *sz,
			const T &t,
			const U &expected,
			const char *szFile,
			int line)
{
	rbPassIV(rb, sz, t, szFile, line);
	const int richbool_level = 2;
	RichBool::Bool richbool = rbEQUAL(t, expected);
	if (!richbool())
		rbAssertFailed(richbool, szFile, line);
}

template <class RB, typename T, typename U>
void rbPassVB(RB rb,
			const char *sz,
			const T &t,
			const U &expected,
			const char *szFile,
			int line)
{
	rbPassIV(rb, sz, t, szFile, line);
	if (!(t==expected))
		rbAssertFailed(false, szFile, line);
}

template <class RB, typename T>
void rbFailIV(RB rb,
			const char *sz,
			const T &t,
			const char *szFile,
			int line,
			const RichBool::Analysis &analysis)
{
	switch (RichBoolTest::GetLevel())
	{
	case 0:
		rbFail(true, analysis, szFile, line);
		break;
	case 1:
		rbFail(rb(t), analysis, szFile, line);
		break;
	case 2:
		rbFail(rb.Analyse(t, sz), analysis, szFile, line);
		break;
	case 3:
		rbFail(rb.Analyse(t, sz, true), analysis, szFile, line);
		break;
	}
}

template <class RB, typename T, typename U>
void rbFailV(RB rb,
			const char *sz,
			const T &t,
			const U &expected,
			const char *szFile,
			int line,
			const RichBool::Analysis &analysis)
{
	rbFailIV(rb, sz, t, szFile, line, analysis);
	const int richbool_level = 2;
	RichBool::Bool richbool = rbEQUAL(t, expected);
	if (!richbool())
		rbAssertFailed(richbool, szFile, line);
}

template <class RB, typename T, typename U>
void rbFailVB(RB rb,
			const char *sz,
			const T &t,
			const U &expected,
			const char *szFile,
			int line,
			const RichBool::Analysis &analysis)
{
	rbFailIV(rb, sz, t, szFile, line, analysis);
	if (!(t==expected))
		rbAssertFailed(false, szFile, line);
}

#define RB_PASS(richbool) \
	do { \
		RichBool::TmpBool richbool_tmp1, richbool_tmp2; \
		int richbool_level = RichBoolTest::GetLevel(); \
		rbPass(richbool, __FILE__, __LINE__); \
	} while (false)

#define RB_PASS_V(richbool, value) \
    rbPassV(richbool, value, __FILE__, __LINE__);

#define RB_PASS_VB(richbool, value) \
    rbPassVB(richbool, value, __FILE__, __LINE__);

#define RB_PASS_IV(richbool) \
    rbPassIV(richbool, __FILE__, __LINE__);

#define RB_PASS_B(cond) \
	do { \
		rbPassBool(cond, false, __FILE__, __LINE__); \
	} while (false)

#define RB_FAIL(richbool, analysis) \
	do { \
		RichBool::TmpBool richbool_tmp1, richbool_tmp2; \
		int richbool_level = RichBoolTest::GetLevel(); \
		rbFail(richbool, analysis, __FILE__, __LINE__); \
	} while (false)

#define RB_FAIL_V(richbool, analysis, value) \
	rbFailV(richbool, value, __FILE__, __LINE__, analysis);

#define RB_FAIL_VB(richbool, analysis, value) \
	rbFailVB(richbool, value, __FILE__, __LINE__, analysis);

#define RB_FAIL_IV(richbool, analysis) \
	rbFailIV(richbool, __FILE__, __LINE__, analysis);

class IgnoreAnalysis: public RichBool::Analysis
{
public:
	IgnoreAnalysis(): RichBool::Analysis(RichBool::Analysis::Ok) {}
	void StreamOut(RichBool::detail::OutStream &, int =0) const {}
	virtual bool Equals(const RichBool::Analysis* ) const
	{
		return false;
	}
	virtual const RichBool::detail::String& GetType() const
	{
		static const RichBool::detail::String type = "ignore";
		return type;
	}
};

#define RB_FAIL_I(richbool) \
	do { \
		RichBool::TmpBool richbool_tmp1, richbool_tmp2; \
		int richbool_level = RichBoolTest::GetLevel(); \
		rbFail(richbool, IgnoreAnalysis(), __FILE__, __LINE__); \
	} while (false)

#define RB_ASSERT(cond) \
	do { \
		int richbool_level = 2; \
		RichBool::TmpBool richbool_tmp1(richbool_level==0), richbool_tmp2; \
		RichBool::Bool richbool = cond; \
		if (!richbool()) \
			rbAssertFailed(richbool, __FILE__, __LINE__); \
	} while (false)

#define RB_INTERNAL_ASSERT(cond) \
	do { \
		const int richbool_level = 2; \
		RichBool::TmpBool richbool_tmp1(richbool_level==0), richbool_tmp2; \
		RichBool::Bool richbool = cond; \
		if (!richbool()) { \
			PrintTestLocation(); \
			rbAssertFailed(richbool, __FILE__, __LINE__); \
		} \
	} while (false)

void print_warning(const char *szWarning,
			const char *szFile,
			int line);

RichBool::detail::String GetNullPtrString();

void PrintTestLocation();

#if defined(_MSC_VER) && (_MSC_VER <= 1300)
	#define RICHBOOL_IS_MSVC6 1
#else
	#define RICHBOOL_IS_MSVC6 0
#endif

#if defined(_MSC_VER) && (_MSC_VER <= 1300) && defined(NDEBUG)
	#define RICHBOOL_IS_MSVC6_RELEASE 1
#else
	#define RICHBOOL_IS_MSVC6_RELEASE 0
#endif


#endif // #ifndef RICH_BOOL_TEST_H__QM
