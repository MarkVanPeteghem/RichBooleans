//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_FUNCTORS_H__QM
#define RICH_BOOL_FUNCTORS_H__QM

#include "richbool/der_analysis.hpp"
#include "richbool/tostring.hpp"
#include "richbool/getvalue.hpp"
#include "richbool/relation.hpp"
#include "richbool/getpoints.hpp"
#include "richbool/base.hpp"

#include <sys/stat.h>
#include <stdio.h>
#include <math.h>

namespace RichBool
{
	namespace detail
	{
		struct None {};

		inline void AddExtraValue(MakeGeneralAnalysis &,
				const char *, const char *, SharedExpression , None )
		{}

		inline void AddExtraValue(MakeGeneralAnalysis &ga,
			const char *text1, const char *text2,
			SharedExpression expr, const String &str)
		{
			ga(text1).expr(expr, ":")(str, true)(text2);
		}

		inline void AddResult(MakeGeneralAnalysis &,
				const char *, const char *, None )
		{}

		inline void AddResult(MakeGeneralAnalysis &ga,
			const char *text1, const char *text2, const String &str)
		{
			ga(text1).result(str)(text2);
		}

		inline void AddEpilogue(MakeGeneralAnalysis &, None )
		{}

		inline void AddEpilogue(MakeGeneralAnalysis &ga, const String &str)
		{
			ga.ep(str);
		}
	}

	struct FunctorCoreBase
	{
		typedef bool Points;

		const char* GetTextBefore1() const { return 0; }
		const char* GetTextAfter1() const { return 0; }
		const char* GetTextBefore2() const { return 0; }
		const char* GetTextAfter2() const { return 0; }
		const char* GetTextBefore3() const { return 0; }
		const char* GetTextAfter3() const { return 0; }
		const char* GetTextBefore4() const { return 0; }
		const char* GetTextAfter4() const { return 0; }
		const char* GetTextBefore5() const { return 0; }
		const char* GetTextAfter5() const { return 0; }
		const char* GetTextBefore6() const { return 0; }
		const char* GetTextAfter6() const { return 0; }

		const char* GetTextBeforeExtra1() const { return 0; }
		const char* GetTextAfterExtra1() const { return 0; }
		const char* GetTextBeforeExtra2() const { return 0; }
		const char* GetTextAfterExtra2() const { return 0; }
		const char* GetTextBeforeExtra3() const { return 0; }
		const char* GetTextAfterExtra3() const { return 0; }
		const char* GetTextBeforeExtra4() const { return 0; }
		const char* GetTextAfterExtra4() const { return 0; }
		const char* GetTextBeforeExtra5() const { return 0; }
		const char* GetTextAfterExtra5() const { return 0; }
		const char* GetTextBeforeExtra6() const { return 0; }
		const char* GetTextAfterExtra6() const { return 0; }

		SharedExpression GetExtraExpression1() const
		{ return SharedExpression(0); }
		SharedExpression GetExtraExpression2() const
		{ return SharedExpression(0); }
		SharedExpression GetExtraExpression3() const
		{ return SharedExpression(0); }
		SharedExpression GetExtraExpression4() const
		{ return SharedExpression(0); }
		SharedExpression GetExtraExpression5() const
		{ return SharedExpression(0); }
		SharedExpression GetExtraExpression6() const
		{ return SharedExpression(0); }

		detail::None GetExtraValue1() const { return detail::None(); }
		detail::None GetExtraValue2() const { return detail::None(); }
		detail::None GetExtraValue3() const { return detail::None(); }
		detail::None GetExtraValue4() const { return detail::None(); }
		detail::None GetExtraValue5() const { return detail::None(); }
		detail::None GetExtraValue6() const { return detail::None(); }


		const char* GetTextBeforeResult1() const { return 0; }
		const char* GetTextAfterResult1() const { return 0; }
		const char* GetTextBeforeResult2() const { return 0; }
		const char* GetTextAfterResult2() const { return 0; }
		const char* GetTextBeforeResult3() const { return 0; }
		const char* GetTextAfterResult3() const { return 0; }
		const char* GetTextBeforeResult4() const { return 0; }
		const char* GetTextAfterResult4() const { return 0; }
		const char* GetTextBeforeResult5() const { return 0; }
		const char* GetTextAfterResult5() const { return 0; }
		const char* GetTextBeforeResult6() const { return 0; }
		const char* GetTextAfterResult6() const { return 0; }

		template <typename T1>
		detail::None GetResult1(const T1 &) const { return detail::None(); }
		template <typename T1, typename T2>
		detail::None GetResult1(const T1&, const T2&) const { return detail::None(); }
		template <typename T1, typename T2, typename T3>
		detail::None GetResult1(const T1&, const T2&, const T3&) const { return detail::None(); }
		template <typename T1, typename T2, typename T3, typename T4>
		detail::None GetResult1(const T1&, const T2&, const T3&, const T4&) const { return detail::None(); }
		template <typename T1, typename T2, typename T3, typename T4, typename T5>
		detail::None GetResult1(const T1&, const T2&, const T3&, const T4&, const T5&) const { return detail::None(); }
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		detail::None GetResult1(const T1&, const T2&, const T3&, const T4&, const T5&, const T6&) const { return detail::None(); }

		template <typename T1, typename T2>
		detail::None GetResult2(const T1&, const T2&) const { return detail::None(); }
		template <typename T1, typename T2, typename T3>
		detail::None GetResult2(const T1&, const T2&, const T3&) const { return detail::None(); }
		template <typename T1, typename T2, typename T3, typename T4>
		detail::None GetResult2(const T1&, const T2&, const T3&, const T4&) const { return detail::None(); }
		template <typename T1, typename T2, typename T3, typename T4, typename T5>
		detail::None GetResult2(const T1&, const T2&, const T3&, const T4&, const T5&) const { return detail::None(); }
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		detail::None GetResult2(const T1&, const T2&, const T3&, const T4&, const T5&, const T6&) const { return detail::None(); }

		template <typename T1, typename T2, typename T3>
		detail::None GetResult3(const T1&, const T2&, const T3&) const { return detail::None(); }
		template <typename T1, typename T2, typename T3, typename T4>
		detail::None GetResult3(const T1&, const T2&, const T3&, const T4&) const { return detail::None(); }
		template <typename T1, typename T2, typename T3, typename T4, typename T5>
		detail::None GetResult3(const T1&, const T2&, const T3&, const T4&, const T5&) const { return detail::None(); }
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		detail::None GetResult3(const T1&, const T2&, const T3&, const T4&, const T5&, const T6&) const { return detail::None(); }

		template <typename T1, typename T2, typename T3, typename T4>
		detail::None GetResult4(const T1&, const T2&, const T3&, const T4&) const { return detail::None(); }
		template <typename T1, typename T2, typename T3, typename T4, typename T5>
		detail::None GetResult4(const T1&, const T2&, const T3&, const T4&, const T5&) const { return detail::None(); }
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		detail::None GetResult4(const T1&, const T2&, const T3&, const T4&, const T5&, const T6&) const { return detail::None(); }

		template <typename T1, typename T2, typename T3, typename T4, typename T5>
		detail::None GetResult5(const T1&, const T2&, const T3&, const T4&, const T5&) const { return detail::None(); }
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		detail::None GetResult5(const T1&, const T2&, const T3&, const T4&, const T5&, const T6&) const { return detail::None(); }

		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		detail::None GetResult6(const T1&, const T2&, const T3&, const T4&, const T5&, const T6&) const { return detail::None(); }
	};


#define RICHBOOL_ADD_WITH_RESULT(N, ARGS) \
	ga(cond.GetTextBefore##N()) \
			.expr(gv##N.Convert(MakeExpression(expr##N)), ":") \
			(t##N, gv##N, str##N) \
			(cond.GetTextAfter##N()); \
	detail::AddResult(ga, cond.GetTextBeforeResult##N(), cond.GetTextAfterResult##N(), cond.GetResult##N ARGS ); \
	detail::AddExtraValue(ga, \
		cond.GetTextBeforeExtra##N(), \
		cond.GetTextAfterExtra##N(), \
		cond.GetExtraExpression##N(), \
		cond.GetExtraValue##N());

#define RICHBOOL_ADD_WITHOUT_RESULT(N) \
	ga(cond.GetTextBefore##N()) \
	.expr(gv##N.Convert(MakeExpression(expr##N)), ":") \
	(t##N, gv##N, Str##N()) \
	(cond.GetTextAfter##N()); \
	detail::AddExtraValue(ga, \
		cond.GetTextBeforeExtra##N(), \
		cond.GetTextAfterExtra##N(), \
		cond.GetExtraExpression##N(), \
		cond.GetExtraValue##N());

	////////////////////////////////////////////////
	// class FunctorCore

	struct FunctorCore: public FunctorCoreBase
	{
		template <class Core, typename T1, typename Expr1, class GV1, class Str1>
		static Analysis* GetAnalysis1(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			bool analyseIfSuccess, bool negate=false)
		{
			if (!gv1.BadPtrChain(t1))
			{
#define RICHBOOL_ARGS (gv1(t1))
				bool ok = cond RICHBOOL_ARGS;
				if (analyseIfSuccess||(ok==negate))
				{
					MakeGeneralAnalysis ga(ok);
					RICHBOOL_ADD_WITH_RESULT(1, RICHBOOL_ARGS);
					detail::AddEpilogue(ga, cond.GetEpilogue RICHBOOL_ARGS );
					return ga;
#undef RICHBOOL_ARGS
				}
				else
					return 0;
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				return ga;
			}
		}
		template <class Core,
			typename T1, typename Expr1, class GV1, class Str1,
			typename T2, typename Expr2, class GV2, class Str2>
		static Analysis* GetAnalysis2(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			const T2 &t2, Expr2 expr2, GV2 gv2, Str2 str2,
			bool analyseIfSuccess, bool negate=false)
		{
			if (!gv1.BadPtrChain(t1) && !gv2.BadPtrChain(t2))
			{
#define RICHBOOL_ARGS (gv1(t1), gv2(t2))
				bool ok = cond RICHBOOL_ARGS;
				if (analyseIfSuccess||(ok==negate))
				{
					MakeGeneralAnalysis ga(ok);
					RICHBOOL_ADD_WITH_RESULT(1, RICHBOOL_ARGS);
					RICHBOOL_ADD_WITH_RESULT(2, RICHBOOL_ARGS);
					detail::AddEpilogue(ga, cond.GetEpilogue RICHBOOL_ARGS );
					return ga;
#undef RICHBOOL_ARGS
				}
				else
					return 0;
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				RICHBOOL_ADD_WITHOUT_RESULT(2);
				return ga;
			}
		}
		template <class Core,
			typename T1, typename Expr1, class GV1, class Str1,
			typename T2, typename Expr2, class GV2, class Str2>
		static Analysis* GetDummyAnalysis2(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			const T2 &t2, Expr2 expr2, GV2 gv2, Str2 str2)
		{
			if (!gv1.BadPtrChain(t1) && !gv2.BadPtrChain(t2))
			{
#define RICHBOOL_ARGS (gv1(t1), gv2(t2))
				MakeGeneralAnalysis ga(Analysis::NotEvaluated);
				RICHBOOL_ADD_WITH_RESULT(1, RICHBOOL_ARGS);
				RICHBOOL_ADD_WITH_RESULT(2, RICHBOOL_ARGS);
				detail::AddEpilogue(ga, cond.GetEpilogue RICHBOOL_ARGS );
				return ga;
#undef RICHBOOL_ARGS
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				RICHBOOL_ADD_WITHOUT_RESULT(2);
				return ga;
			}
		}
		template <class Core,
			typename T1, typename Expr1, class GV1, class Str1,
			typename T2, typename Expr2, class GV2, class Str2,
			typename T3, typename Expr3, class GV3, class Str3>
		static Analysis* GetAnalysis3(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			const T2 &t2, Expr2 expr2, GV2 gv2, Str2 str2,
			const T3 &t3, Expr3 expr3, GV3 gv3, Str3 str3,
			bool analyseIfSuccess, bool negate=false)
		{
			if (!gv1.BadPtrChain(t1) && !gv2.BadPtrChain(t2) && !gv3.BadPtrChain(t3))
			{
#define RICHBOOL_ARGS (gv1(t1), gv2(t2), gv3(t3))
				bool ok = cond RICHBOOL_ARGS;
				if (analyseIfSuccess||(ok==negate))
				{
					MakeGeneralAnalysis ga(ok);
					RICHBOOL_ADD_WITH_RESULT(1, RICHBOOL_ARGS);
					RICHBOOL_ADD_WITH_RESULT(2, RICHBOOL_ARGS);
					RICHBOOL_ADD_WITH_RESULT(3, RICHBOOL_ARGS);
					detail::AddEpilogue(ga, cond.GetEpilogue RICHBOOL_ARGS );
					return ga;
#undef RICHBOOL_ARGS
				}
				else
					return 0;
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				RICHBOOL_ADD_WITHOUT_RESULT(2);
				RICHBOOL_ADD_WITHOUT_RESULT(3);
				return ga;
			}
		}
		template <class Core,
			typename T1, typename Expr1, class GV1, class Str1,
			typename T2, typename Expr2, class GV2, class Str2,
			typename T3, typename Expr3, class GV3, class Str3,
			typename T4, typename Expr4, class GV4, class Str4>
		static Analysis* GetAnalysis4(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			const T2 &t2, Expr2 expr2, GV2 gv2, Str2 str2,
			const T3 &t3, Expr3 expr3, GV3 gv3, Str3 str3,
			const T4 &t4, Expr4 expr4, GV4 gv4, Str4 str4,
			bool analyseIfSuccess, bool negate=false)
		{
			if (!gv1.BadPtrChain(t1) && !gv2.BadPtrChain(t2)
				&& !gv3.BadPtrChain(t3) && !gv4.BadPtrChain(t4))
			{
#define RICHBOOL_ARGS (gv1(t1), gv2(t2), gv3(t3), gv4(t4))
				bool ok = cond RICHBOOL_ARGS;
				if (analyseIfSuccess||(ok==negate))
				{
					MakeGeneralAnalysis ga(ok);
					RICHBOOL_ADD_WITH_RESULT(1, RICHBOOL_ARGS);
					RICHBOOL_ADD_WITH_RESULT(2, RICHBOOL_ARGS);
					RICHBOOL_ADD_WITH_RESULT(3, RICHBOOL_ARGS);
					RICHBOOL_ADD_WITH_RESULT(4, RICHBOOL_ARGS);
					detail::AddEpilogue(ga, cond.GetEpilogue RICHBOOL_ARGS );
					return ga;
#undef RICHBOOL_ARGS
				}
				else
					return 0;
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				RICHBOOL_ADD_WITHOUT_RESULT(2);
				RICHBOOL_ADD_WITHOUT_RESULT(3);
				RICHBOOL_ADD_WITHOUT_RESULT(4);
				return ga;
			}
		}
		template <class Core,
			typename T1, typename Expr1, class GV1, class Str1,
			typename T2, typename Expr2, class GV2, class Str2,
			typename T3, typename Expr3, class GV3, class Str3,
			typename T4, typename Expr4, class GV4, class Str4,
			typename T5, typename Expr5, class GV5, class Str5>
		static Analysis* GetAnalysis5(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			const T2 &t2, Expr2 expr2, GV2 gv2, Str2 str2,
			const T3 &t3, Expr3 expr3, GV3 gv3, Str3 str3,
			const T4 &t4, Expr4 expr4, GV4 gv4, Str4 str4,
			const T5 &t5, Expr5 expr5, GV5 gv5, Str5 str5,
			bool analyseIfSuccess, bool negate=false)
		{
			if (!gv1.BadPtrChain(t1) && !gv2.BadPtrChain(t2)
				&& !gv3.BadPtrChain(t3) && !gv4.BadPtrChain(t4) && !gv5.BadPtrChain(t5))
			{
#define RICHBOOL_ARGS (gv1(t1), gv2(t2), gv3(t3), gv4(t4), gv5(t5))
				bool ok = cond RICHBOOL_ARGS;
				if (analyseIfSuccess||(ok==negate))
				{
					MakeGeneralAnalysis ga(ok);
					RICHBOOL_ADD_WITH_RESULT(1, RICHBOOL_ARGS);
					RICHBOOL_ADD_WITH_RESULT(2, RICHBOOL_ARGS);
					RICHBOOL_ADD_WITH_RESULT(3, RICHBOOL_ARGS);
					RICHBOOL_ADD_WITH_RESULT(4, RICHBOOL_ARGS);
					RICHBOOL_ADD_WITH_RESULT(5, RICHBOOL_ARGS);
					detail::AddEpilogue(ga, cond.GetEpilogue RICHBOOL_ARGS );
					return ga;
#undef RICHBOOL_ARGS
				}
				else
					return 0;
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				RICHBOOL_ADD_WITHOUT_RESULT(2);
				RICHBOOL_ADD_WITHOUT_RESULT(3);
				RICHBOOL_ADD_WITHOUT_RESULT(4);
				RICHBOOL_ADD_WITHOUT_RESULT(5);
				return ga;
			}
		}
		template <class Core,
			typename T1, typename Expr1, class GV1, class Str1,
			typename T2, typename Expr2, class GV2, class Str2,
			typename T3, typename Expr3, class GV3, class Str3,
			typename T4, typename Expr4, class GV4, class Str4,
			typename T5, typename Expr5, class GV5, class Str5,
			typename T6, typename Expr6, class GV6, class Str6>
		static Analysis* GetAnalysis6(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			const T2 &t2, Expr2 expr2, GV2 gv2, Str2 str2,
			const T3 &t3, Expr3 expr3, GV3 gv3, Str3 str3,
			const T4 &t4, Expr4 expr4, GV4 gv4, Str4 str4,
			const T5 &t5, Expr5 expr5, GV5 gv5, Str5 str5,
			const T6 &t6, Expr6 expr6, GV6 gv6, Str6 str6,
			bool analyseIfSuccess, bool negate=false)
		{
			if (!gv1.BadPtrChain(t1) && !gv2.BadPtrChain(t2) && !gv3.BadPtrChain(t3)
				&& !gv4.BadPtrChain(t4) && !gv5.BadPtrChain(t5) && !gv6.BadPtrChain(t6))
			{
#define RICHBOOL_ARGS (gv1(t1), gv2(t2), gv3(t3), gv4(t4), gv5(t5), gv6(t6))
				bool ok = cond RICHBOOL_ARGS;
				if (analyseIfSuccess||(ok==negate))
				{
					MakeGeneralAnalysis ga(ok);
					RICHBOOL_ADD_WITH_RESULT(1, RICHBOOL_ARGS);
					RICHBOOL_ADD_WITH_RESULT(2, RICHBOOL_ARGS);
					RICHBOOL_ADD_WITH_RESULT(3, RICHBOOL_ARGS);
					RICHBOOL_ADD_WITH_RESULT(4, RICHBOOL_ARGS);
					RICHBOOL_ADD_WITH_RESULT(5, RICHBOOL_ARGS);
					RICHBOOL_ADD_WITH_RESULT(6, RICHBOOL_ARGS);
					detail::AddEpilogue(ga, cond.GetEpilogue RICHBOOL_ARGS );
					return ga;
#undef RICHBOOL_ARGS
				}
				else
					return 0;
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				RICHBOOL_ADD_WITHOUT_RESULT(2);
				RICHBOOL_ADD_WITHOUT_RESULT(3);
				RICHBOOL_ADD_WITHOUT_RESULT(4);
				RICHBOOL_ADD_WITHOUT_RESULT(5);
				RICHBOOL_ADD_WITHOUT_RESULT(6);
				return ga;
			}
		}
		template <typename T1>
		detail::None GetEpilogue(const T1 &) const { return detail::None(); }
		template <typename T1, typename T2>
		detail::None GetEpilogue(const T1&, const T2&) const { return detail::None(); }
		template <typename T1, typename T2, typename T3>
		detail::None GetEpilogue(const T1&, const T2&, const T3&) const { return detail::None(); }
		template <typename T1, typename T2, typename T3, typename T4>
		detail::None GetEpilogue(const T1&, const T2&, const T3&, const T4&) const { return detail::None(); }
		template <typename T1, typename T2, typename T3, typename T4, typename T5>
		detail::None GetEpilogue(const T1&, const T2&, const T3&, const T4&, const T5&) const { return detail::None(); }
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		detail::None GetEpilogue(const T1&, const T2&, const T3&, const T4&, const T5&, const T6&) const { return detail::None(); }
	};

	template <bool analysisChecks>
	struct CustomFunctorCore
	{};

	template <>
	struct CustomFunctorCore<false>: public FunctorCoreBase
	{
#define RICHBOOL_ARGS(N) \
	gv##N(t##N), gv##N.ToString(t##N, str##N), gv##N.Convert(MakeExpression(expr##N))

		template <class Core,
			typename T1, typename Expr1, class GV1, class Str1>
		static Analysis* GetAnalysis1(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			bool analyseIfSuccess, bool negate=false)
		{
			if (!gv1.BadPtrChain(t1))
			{
				bool ok = cond(gv1(t1));
				if ( (ok!=negate) && !analyseIfSuccess)
					return 0;
				return cond.Analyse(RICHBOOL_ARGS(1), ok);
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				return ga;
			}
		}
		template <class Core,
			typename T1, typename Expr1, class GV1, class Str1,
			typename T2, typename Expr2, class GV2, class Str2>
		static Analysis* GetAnalysis2(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			const T2 &t2, Expr2 expr2, GV2 gv2, Str2 str2,
			bool analyseIfSuccess, bool negate=false)
		{
			if (!gv1.BadPtrChain(t1) && !gv2.BadPtrChain(t2))
			{
				bool ok = cond(gv1(t1), gv2(t2));
				if ( (ok!=negate) && !analyseIfSuccess)
					return 0;
				return cond.Analyse(RICHBOOL_ARGS(1), RICHBOOL_ARGS(2), ok);
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				RICHBOOL_ADD_WITHOUT_RESULT(2);
				return ga;
			}
		}
		template <class Core,
			typename T1, typename Expr1, class GV1, class Str1,
			typename T2, typename Expr2, class GV2, class Str2>
		static Analysis* GetDummyAnalysis2(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			const T2 &t2, Expr2 expr2, GV2 gv2, Str2 str2)
		{
			if (!gv1.BadPtrChain(t1) && !gv2.BadPtrChain(t2))
			{
				return cond.GetDummyAnalysis(RICHBOOL_ARGS(1), RICHBOOL_ARGS(2));
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				RICHBOOL_ADD_WITHOUT_RESULT(2);
				return ga;
			}
		}
		template <class Core,
			typename T1, typename Expr1, class GV1, class Str1,
			typename T2, typename Expr2, class GV2, class Str2,
			typename T3, typename Expr3, class GV3, class Str3>
		static Analysis* GetAnalysis3(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			const T2 &t2, Expr2 expr2, GV2 gv2, Str2 str2,
			const T3 &t3, Expr3 expr3, GV3 gv3, Str3 str3,
			bool analyseIfSuccess, bool negate=false)
		{
			if (!gv1.BadPtrChain(t1) && !gv2.BadPtrChain(t2) && !gv3.BadPtrChain(t3))
			{
				bool ok = cond(gv1(t1), gv2(t2), gv3(t3));
				if ( (ok!=negate) && !analyseIfSuccess)
					return 0;
				return cond.Analyse(RICHBOOL_ARGS(1), RICHBOOL_ARGS(2), RICHBOOL_ARGS(3), ok);
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				RICHBOOL_ADD_WITHOUT_RESULT(2);
				RICHBOOL_ADD_WITHOUT_RESULT(3);
				return ga;
			}
		}
		template <class Core,
			typename T1, typename Expr1, class GV1, class Str1,
			typename T2, typename Expr2, class GV2, class Str2,
			typename T3, typename Expr3, class GV3, class Str3,
			typename T4, typename Expr4, class GV4, class Str4>
		static Analysis* GetAnalysis4(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			const T2 &t2, Expr2 expr2, GV2 gv2, Str2 str2,
			const T3 &t3, Expr3 expr3, GV3 gv3, Str3 str3,
			const T4 &t4, Expr4 expr4, GV4 gv4, Str4 str4,
			bool analyseIfSuccess, bool negate=false)
		{
			if (!gv1.BadPtrChain(t1) && !gv2.BadPtrChain(t2) && !gv3.BadPtrChain(t3)
				&& !gv4.BadPtrChain(t4))
			{
				bool ok = cond(gv1(t1), gv2(t2), gv3(t3), gv4(t4));
				if ( (ok!=negate) && !analyseIfSuccess)
					return 0;
				return cond.Analyse(RICHBOOL_ARGS(1), RICHBOOL_ARGS(2), RICHBOOL_ARGS(3), RICHBOOL_ARGS(4), ok);
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				RICHBOOL_ADD_WITHOUT_RESULT(2);
				RICHBOOL_ADD_WITHOUT_RESULT(3);
				RICHBOOL_ADD_WITHOUT_RESULT(4);
				return ga;
			}
		}
		template <class Core,
			typename T1, typename Expr1, class GV1, class Str1,
			typename T2, typename Expr2, class GV2, class Str2,
			typename T3, typename Expr3, class GV3, class Str3,
			typename T4, typename Expr4, class GV4, class Str4,
			typename T5, typename Expr5, class GV5, class Str5>
		static Analysis* GetAnalysis5(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			const T2 &t2, Expr2 expr2, GV2 gv2, Str2 str2,
			const T3 &t3, Expr3 expr3, GV3 gv3, Str3 str3,
			const T4 &t4, Expr4 expr4, GV4 gv4, Str4 str4,
			const T5 &t5, Expr5 expr5, GV5 gv5, Str5 str5,
			bool analyseIfSuccess, bool negate=false)
		{
			if (!gv1.BadPtrChain(t1) && !gv2.BadPtrChain(t2) && !gv3.BadPtrChain(t3)
				&& !gv4.BadPtrChain(t4) && !gv5.BadPtrChain(t5))
			{
				bool ok = cond(gv1(t1), gv2(t2), gv3(t3), gv4(t4), gv5(t5));
				if ( (ok!=negate) && !analyseIfSuccess)
					return 0;
				return cond.Analyse(RICHBOOL_ARGS(1), RICHBOOL_ARGS(2), RICHBOOL_ARGS(3), RICHBOOL_ARGS(4), RICHBOOL_ARGS(5), ok);
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				RICHBOOL_ADD_WITHOUT_RESULT(2);
				RICHBOOL_ADD_WITHOUT_RESULT(3);
				RICHBOOL_ADD_WITHOUT_RESULT(4);
				RICHBOOL_ADD_WITHOUT_RESULT(5);
				return ga;
			}
		}
		template <class Core,
			typename T1, typename Expr1, class GV1, class Str1,
			typename T2, typename Expr2, class GV2, class Str2,
			typename T3, typename Expr3, class GV3, class Str3,
			typename T4, typename Expr4, class GV4, class Str4,
			typename T5, typename Expr5, class GV5, class Str5,
			typename T6, typename Expr6, class GV6, class Str6>
		static Analysis* GetAnalysis6(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			const T2 &t2, Expr2 expr2, GV2 gv2, Str2 str2,
			const T3 &t3, Expr3 expr3, GV3 gv3, Str3 str3,
			const T4 &t4, Expr4 expr4, GV4 gv4, Str4 str4,
			const T5 &t5, Expr5 expr5, GV5 gv5, Str5 str5,
			const T6 &t6, Expr6 expr6, GV6 gv6, Str6 str6,
			bool analyseIfSuccess, bool negate=false)
		{
			if (!gv1.BadPtrChain(t1) && !gv2.BadPtrChain(t2) && !gv3.BadPtrChain(t3)
				&& !gv4.BadPtrChain(t4) && !gv5.BadPtrChain(t5) && !gv6.BadPtrChain(t6))
			{
				bool ok = cond(gv1(t1), gv2(t2), gv3(t3), gv4(t4), gv5(t5), gv6(t6));
				if ( (ok!=negate) && !analyseIfSuccess)
					return 0;
				return cond.Analyse(RICHBOOL_ARGS(1), RICHBOOL_ARGS(2), RICHBOOL_ARGS(3), RICHBOOL_ARGS(4), RICHBOOL_ARGS(5), RICHBOOL_ARGS(6), ok);
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				RICHBOOL_ADD_WITHOUT_RESULT(2);
				RICHBOOL_ADD_WITHOUT_RESULT(3);
				RICHBOOL_ADD_WITHOUT_RESULT(4);
				RICHBOOL_ADD_WITHOUT_RESULT(5);
				RICHBOOL_ADD_WITHOUT_RESULT(6);
				return ga;
			}
		}
#undef RICHBOOL_ARGS
	};

	template <>
	struct CustomFunctorCore<true>: public FunctorCoreBase
	{
#define RICHBOOL_ARGS(N) gv##N(t##N), expr##N, str##N
		template <class Core,
			typename T1, typename Expr1, class GV1, class Str1>
		static Analysis* GetAnalysis1(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			bool analyseIfSuccess, bool negate=false)
		{
			if (!gv1.BadPtrChain(t1))
			{
				return cond.Analyse(RICHBOOL_ARGS(1),
 					analyseIfSuccess, negate);
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				return ga;
			}
		}
		template <class Core,
			typename T1, typename Expr1, class GV1, class Str1,
			typename T2, typename Expr2, class GV2, class Str2>
		static Analysis* GetAnalysis2(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			const T2 &t2, Expr2 expr2, GV2 gv2, Str2 str2,
			bool analyseIfSuccess, bool negate=false)
		{
			if (!gv1.BadPtrChain(t1) && !gv2.BadPtrChain(t2))
			{
				return cond.Analyse(RICHBOOL_ARGS(1), RICHBOOL_ARGS(2),
 					analyseIfSuccess, negate);
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				RICHBOOL_ADD_WITHOUT_RESULT(2);
				return ga;
			}
		}
		template <class Core,
			typename T1, typename Expr1, class GV1, class Str1,
			typename T2, typename Expr2, class GV2, class Str2,
			typename T3, typename Expr3, class GV3, class Str3>
		static Analysis* GetAnalysis3(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			const T2 &t2, Expr2 expr2, GV2 gv2, Str2 str2,
			const T3 &t3, Expr3 expr3, GV3 gv3, Str3 str3,
			bool analyseIfSuccess, bool negate=false)
		{
			if (!gv1.BadPtrChain(t1) && !gv2.BadPtrChain(t2) && !gv3.BadPtrChain(t3))
			{
				return cond.Analyse(RICHBOOL_ARGS(1), RICHBOOL_ARGS(2),
					RICHBOOL_ARGS(3),
 					analyseIfSuccess, negate);
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				RICHBOOL_ADD_WITHOUT_RESULT(2);
				RICHBOOL_ADD_WITHOUT_RESULT(3);
				return ga;
			}
		}
		template <class Core,
			typename T1, typename Expr1, class GV1, class Str1,
			typename T2, typename Expr2, class GV2, class Str2,
			typename T3, typename Expr3, class GV3, class Str3,
			typename T4, typename Expr4, class GV4, class Str4>
		static Analysis* GetAnalysis4(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			const T2 &t2, Expr2 expr2, GV2 gv2, Str2 str2,
			const T3 &t3, Expr3 expr3, GV3 gv3, Str3 str3,
			const T4 &t4, Expr4 expr4, GV4 gv4, Str4 str4,
			bool analyseIfSuccess, bool negate=false)
		{
			if (!gv1.BadPtrChain(t1) && !gv2.BadPtrChain(t2)
				 && !gv3.BadPtrChain(t3) && !gv4.BadPtrChain(t4))
			{
				return cond.Analyse(RICHBOOL_ARGS(1), RICHBOOL_ARGS(2),
					RICHBOOL_ARGS(3), RICHBOOL_ARGS(4),
 					analyseIfSuccess, negate);
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				RICHBOOL_ADD_WITHOUT_RESULT(2);
				RICHBOOL_ADD_WITHOUT_RESULT(3);
				RICHBOOL_ADD_WITHOUT_RESULT(4);
				return ga;
			}
		}
		template <class Core,
			typename T1, typename Expr1, class GV1, class Str1,
			typename T2, typename Expr2, class GV2, class Str2,
			typename T3, typename Expr3, class GV3, class Str3,
			typename T4, typename Expr4, class GV4, class Str4,
			typename T5, typename Expr5, class GV5, class Str5>
		static Analysis* GetAnalysis5(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			const T2 &t2, Expr2 expr2, GV2 gv2, Str2 str2,
			const T3 &t3, Expr3 expr3, GV3 gv3, Str3 str3,
			const T4 &t4, Expr4 expr4, GV4 gv4, Str4 str4,
			const T5 &t5, Expr5 expr5, GV5 gv5, Str5 str5,
			bool analyseIfSuccess, bool negate=false)
		{
			if (!gv1.BadPtrChain(t1) && !gv2.BadPtrChain(t2) && !gv3.BadPtrChain(t3)
				&& !gv4.BadPtrChain(t4) && !gv5.BadPtrChain(t5))
			{
				return cond.Analyse(RICHBOOL_ARGS(1), RICHBOOL_ARGS(2),
					RICHBOOL_ARGS(3), RICHBOOL_ARGS(4), RICHBOOL_ARGS(5),
 					analyseIfSuccess, negate);
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				RICHBOOL_ADD_WITHOUT_RESULT(2);
				RICHBOOL_ADD_WITHOUT_RESULT(3);
				RICHBOOL_ADD_WITHOUT_RESULT(4);
				RICHBOOL_ADD_WITHOUT_RESULT(5);
				return ga;
			}
		}
		template <class Core,
			typename T1, typename Expr1, class GV1, class Str1,
			typename T2, typename Expr2, class GV2, class Str2,
			typename T3, typename Expr3, class GV3, class Str3,
			typename T4, typename Expr4, class GV4, class Str4,
			typename T5, typename Expr5, class GV5, class Str5,
			typename T6, typename Expr6, class GV6, class Str6>
		static Analysis* GetAnalysis6(Core cond,
			const T1 &t1, Expr1 expr1, GV1 gv1, Str1 str1,
			const T2 &t2, Expr2 expr2, GV2 gv2, Str2 str2,
			const T3 &t3, Expr3 expr3, GV3 gv3, Str3 str3,
			const T4 &t4, Expr4 expr4, GV4 gv4, Str4 str4,
			const T5 &t5, Expr5 expr5, GV5 gv5, Str5 str5,
			const T6 &t6, Expr6 expr6, GV6 gv6, Str6 str6,
			bool analyseIfSuccess, bool negate=false)
		{
			if (!gv1.BadPtrChain(t1) && !gv2.BadPtrChain(t2) && !gv3.BadPtrChain(t3)
				&& !gv4.BadPtrChain(t4) && !gv5.BadPtrChain(t5) && !gv6.BadPtrChain(t6))
			{
				return cond.Analyse(RICHBOOL_ARGS(1), RICHBOOL_ARGS(2),
					RICHBOOL_ARGS(3), RICHBOOL_ARGS(4), RICHBOOL_ARGS(5), RICHBOOL_ARGS(6),
 					analyseIfSuccess, negate);
			}
			else
			{
				MakeGeneralAnalysis ga(Analysis::BadValue);
				RICHBOOL_ADD_WITHOUT_RESULT(1);
				RICHBOOL_ADD_WITHOUT_RESULT(2);
				RICHBOOL_ADD_WITHOUT_RESULT(3);
				RICHBOOL_ADD_WITHOUT_RESULT(4);
				RICHBOOL_ADD_WITHOUT_RESULT(5);
				RICHBOOL_ADD_WITHOUT_RESULT(6);
				return ga;
			}
		}
	};
#undef RICHBOOL_ADD_WITH_RESULT
#undef RICHBOOL_ADD_WITHOUT_RESULT


	////////////////////////////////////////////////
	// with one argument

	template <class Core,
		class GV1_=Value,
		class Str_=MakeString>
	class Wrapper1Arg: public Functors::Base
	{
		Core core;
	public:
		typedef GV1_ GV1;
		GV1 getValue1;
		typedef Str_ Str1;

		Wrapper1Arg(GV1 gv1=GV1()): getValue1(gv1)
		{}
		Wrapper1Arg(Core cond, GV1 gv1=GV1()):
			core(cond), getValue1(gv1)
		{}

		template<typename T1>
		bool operator()(const T1 &t1) const
		{
			return core(getValue1(t1));
		}
		template<typename T1>
		Analysis::State SafeCheck(const T1 &t1) const
		{
			if (getValue1.BadPtrChain(t1))
				return Analysis::BadValue;
			return core(getValue1(t1)) ? Analysis::Ok : Analysis::NotOk;
		}
		template<typename T1, typename Expr>
		Analysis* Analyse(const T1 &t1, Expr expr1,
			bool analyseIfSuccess=false, bool negate=false) const
		{
			return Core::GetAnalysis1(core, t1, expr1, getValue1, Str1(), analyseIfSuccess, negate);
		}
		template<typename T1>
		detail::String GetString1(const T1 &t1) const
		{
			return getValue1.ToString(t1, Str1());
		}
		template<typename T1>
		bool IsValid1(const T1 &t1) const
		{
			return !getValue1.BadPtrChain(t1);
		}

		Core GetCore() const
		{
			return core;
		}
		typedef int* Points;
	};

#define RICHBOOL_WRAPPER1ARG(FUNCTOR, CORE) \
	template <class GV1=RichBool::Value, class Str_=RichBool::MakeString> \
	struct FUNCTOR: public RichBool::Wrapper1Arg<CORE, GV1, Str_> { \
		FUNCTOR(GV1 gv1=GV1()): \
		RichBool::Wrapper1Arg<CORE, GV1, Str_>(gv1) \
		{} \
	};

#define RICHBOOL_WRAPPER1ARG_1CARG(FUNCTOR, CORE, ARG1, VAL1) \
	template <class GV1=RichBool::Value, class Str_=RichBool::MakeString> \
	struct FUNCTOR: public RichBool::Wrapper1Arg<CORE, GV1, Str_> { \
		FUNCTOR(ARG1, GV1 gv1=GV1()): \
		RichBool::Wrapper1Arg<CORE, GV1, Str_>(CORE(VAL1), gv1) \
		{} \
	};

	template <typename Pred>
	class Pred1Core: public FunctorCore
	{
		Pred pred;
	public:
		Pred1Core() {}
		Pred1Core(const Pred &pred_): pred(pred_) {}
		Pred1Core(const Pred1Core &pred_): pred(pred_.pred) {}

		template<typename T1>
		bool operator()(const T1 &t1) const
		{
			return pred(t1);
		}

		const char* GetTextBefore1() const
		{
			return "predicate(";
		}
		const char* GetTextAfter1() const
		{
			return ")";
		}
	};

	template <class Pred,
		class GV1=Value, class Str_=MakeString>
	struct Pred1: public Wrapper1Arg<Pred1Core<Pred>, GV1, Str_>
	{
		Pred1(GV1 gv1=GV1()):
			Wrapper1Arg<Pred1Core<Pred>, GV1, Str_>(gv1)
		{}
		Pred1(const Pred &pred, GV1 gv1=GV1()):
			Wrapper1Arg<Pred1Core<Pred>, GV1, Str_>(pred, gv1)
		{}
	};

	template<class Pred>
	Pred1<Pred, Value, MakeString>
	PredToRichBool_1Arg(const Pred &pred)
	{
		return Pred1<Pred, Value, MakeString>(pred);
	}

	template<class Pred, class GV1_,
		class Stringize_>
	Pred1<Pred, GV1_, Stringize_>
	PredToRichBool_1Arg(const Pred &pred,
		GV1_ ,
		Stringize_ )
	{
		return Pred1<Pred, GV1_, Stringize_>(pred);
	}

	template<typename T, class Relation>
	class Order1Core: public FunctorCore
	{
		Relation relation;
		T value;
	public:
		Order1Core(const T &t): value(t) {}
		template<typename T1>
		bool operator()(const T1 &t1) const
		{
			return relation(t1, value);
		}

		const char* GetTextAfter1() const { return Relation::name(); }
		const detail::String GetExtraValue1() const
		{
			return ToString(value);
		}
	};

#define RICHBOOL_MAKE_ORDER1_1ARG(RELATION, STRUCT) \
	template <typename T, class GV1=Value, class Stringize_=MakeString> \
	struct STRUCT: public Wrapper1Arg<Order1Core<T, RELATION>, GV1, Stringize_> \
	{ \
		STRUCT(const T &t, GV1 gv1=GV1()): \
			Wrapper1Arg<Order1Core<T, RELATION>, GV1, Stringize_>(Order1Core<T, RELATION>(t), gv1) \
		{} \
	};

	RICHBOOL_MAKE_ORDER1_1ARG(EqualRelation, Equals)
	RICHBOOL_MAKE_ORDER1_1ARG(LessRelation, IsLessThan)
	RICHBOOL_MAKE_ORDER1_1ARG(LessOrEqualRelation, IsLessOrEqualTo)
	RICHBOOL_MAKE_ORDER1_1ARG(MoreRelation, IsMoreThan)
	RICHBOOL_MAKE_ORDER1_1ARG(MoreOrEqualRelation, IsMoreOrEqualTo)
	RICHBOOL_MAKE_ORDER1_1ARG(DifferentRelation, IsDifferentFrom)

#define RICHBOOL_MAKE_ORDER1_1ARG_FUNC(FUNC, STRUCT) \
	template<typename T> \
	STRUCT<T> FUNC(const T &t) { \
		return STRUCT<T>(t); \
	}
	RICHBOOL_MAKE_ORDER1_1ARG_FUNC(EqualTo, Equals)
	RICHBOOL_MAKE_ORDER1_1ARG_FUNC(LessThan, IsLessThan)
	RICHBOOL_MAKE_ORDER1_1ARG_FUNC(LessOrEqualTo, IsLessOrEqualTo)
	RICHBOOL_MAKE_ORDER1_1ARG_FUNC(MoreThan, IsMoreThan)
	RICHBOOL_MAKE_ORDER1_1ARG_FUNC(MoreOrEqualTo, IsMoreOrEqualTo)
	RICHBOOL_MAKE_ORDER1_1ARG_FUNC(DifferentFrom, IsDifferentFrom)

	// short wrapper function to prevent warnings:
	// with some compilers type_info::operator== returns bool,
	// with others int
	inline bool equal_type_info(const std::type_info &t1, const std::type_info &t2)
	{
#if defined(_MSC_VER)
		return (t1==t2)!=0;
#else
		return t1==t2;
#endif
	}

	template <typename Type>
	class HasTypeCore: public FunctorCore
	{
		const char *szType;
	public:
		HasTypeCore(const char *szType_):
			szType(szType_) {}

		template<typename T1>
		bool operator()(const T1 &t1) const
		{
			return equal_type_info(typeid(t1), typeid(Type));
		}
		const char* GetTextBefore1() const
		{ return "typeid("; }
		const char* GetTextAfter1() const
		{ return ")"; }

		const char* GetTextBeforeResult1() const
		{ return ":"; }
		template<typename T1>
		const detail::String GetResult1(const T1 &t1)
		{ return typeid(t1).name(); }

		const char* GetTextBeforeExtra1() const
		{ return " == "; }
		SharedExpression GetExtraExpression1() const
		{ return new TextExpression(szType); }
		const detail::String GetExtraValue1() const
		{ return typeid(Type).name(); }
	};

	template <typename T, class GV1=Value, class Stringize_=MakeString>
	struct HasType: public Wrapper1Arg<HasTypeCore<T>, GV1, Stringize_>
	{
		HasType(const char *szType, GV1 gv1=GV1()):
			Wrapper1Arg<HasTypeCore<T>, GV1, Stringize_>(HasTypeCore<T>(szType), gv1)
		{}
	};

	template <typename Expected>
	HasType<Expected, Pointer<> >
	MakeHasTypePtr(const Expected*, const char *szType)
	{
		return HasType<Expected, Pointer<> >(szType);
	}


	template <typename Type>
	class DynamicCastableRefCore: public FunctorCore
	{
		const char *szType;
	public:
		DynamicCastableRefCore(const char *szType_):
			szType(szType_) {}

		template<typename T1>
		bool operator()(const T1 &t1) const
		{
			try
			{
				dynamic_cast<Type>(const_cast<T1&>(t1));
				return true;
			}
			catch (...)
			{
				return false;
			}
		}
		const char* GetTextBefore1() const
		{ return "typeid("; }
		const char* GetTextAfter1() const
		{ return ")"; }

		template<typename T1>
		const detail::String GetResult1(const T1 &t1)
		{ return typeid(t1).name(); }
		const char* GetTextBeforeResult1() const
		{ return ":"; }

		const char* GetTextBeforeExtra1() const
		{ return " -> "; }
		SharedExpression GetExtraExpression1() const
		{ return new TextExpression(szType); }
		const detail::String GetExtraValue1() const
		{ return typeid(Type).name(); }
	};

	template <typename Type>
	class DynamicCastablePtrCore: public DynamicCastableRefCore<Type>
	{
	public:
		DynamicCastablePtrCore(const char *szType_):
			DynamicCastableRefCore<Type>(szType_) {}

		template<typename T1>
		bool operator()(const T1 &t1) const
		{
			return dynamic_cast<const Type>(t1)!=0;
		}

		template<typename T1>
		const detail::String GetResult1(const T1 &t1)
		{ return typeid(*t1).name(); }
	};

	template <typename T, class GV1=Value, class Stringize_=MakeString>
	struct DynamicCastableReference: public Wrapper1Arg<DynamicCastableRefCore<T>, GV1, Stringize_>
	{
		DynamicCastableReference(const char *szType, GV1 gv1=GV1()):
			Wrapper1Arg<DynamicCastableRefCore<T>, GV1, Stringize_>
				(DynamicCastableRefCore<T>(szType), gv1)
		{}
	};

	template <typename T, class GV1=Value, class Stringize_=MakeStringOfPointer<true,false> >
	struct DynamicCastablePointer: public Wrapper1Arg<DynamicCastablePtrCore<T>, GV1, Stringize_>
	{
		DynamicCastablePointer(const char *szType, GV1 gv1=GV1()):
			Wrapper1Arg<DynamicCastablePtrCore<T>, GV1, Stringize_>
				(DynamicCastablePtrCore<T>(szType), gv1)
		{}
	};


#ifndef RICHBOOL_NO_PARTIAL_TEMPLATE_SPECIALIZATION
	template <typename Type>
	struct DynamicCastableCore: public DynamicCastableRefCore<Type>
	{
		DynamicCastableCore(const char *szType_): DynamicCastableRefCore<Type>(szType_)
		{}
	};

	template <typename Type>
	struct DynamicCastableCore<Type*>: public DynamicCastablePtrCore<Type*>
	{
		DynamicCastableCore(const char *szType_): DynamicCastablePtrCore<Type*>(szType_)
		{}
	};

	template <typename T, class GV1=Value, class Stringize_=MakeString>
	struct DynamicCastable: public Wrapper1Arg<DynamicCastableCore<T>, GV1, Stringize_>
	{
		DynamicCastable(const char *szType, GV1 gv1=GV1()):
			Wrapper1Arg<DynamicCastableCore<T>, GV1, Stringize_>
				(DynamicCastableCore<T>(szType), gv1)
		{}
	};
#endif

	////////////////////////////////////////////////
	// with two arguments

	template <class Core,
		class GV1_=Value,
		class GV2_=Value,
		class Stringize1_=MakeString,
		class Stringize2_=MakeString>
	class Wrapper2Arg: public Functors::Base
	{
	protected:
		Core core;
	public:
		typedef GV1_ GV1;
		typedef GV2_ GV2;
		GV1 getValue1;
		GV2 getValue2;
		typedef Stringize1_ Stringize1;
		typedef Stringize2_ Stringize2;

		Wrapper2Arg(GV1 gv1=GV1(), GV2 gv2=GV2()): getValue1(gv1), getValue2(gv2)
		{}
		Wrapper2Arg(Core cond, GV1 gv1=GV1(), GV2 gv2=GV2()):
			core(cond), getValue1(gv1), getValue2(gv2)
		{}

		template<typename T1, typename T2>
		bool operator()(const T1 &t1, const T2 &t2) const
		{
			return core(getValue1(t1), getValue2(t2));
		}
		template<typename T1, typename T2>
		Analysis::State SafeCheck(const T1 &t1, const T2 &t2) const
		{
			if (getValue1.BadPtrChain(t1)||getValue2.BadPtrChain(t2))
				return Analysis::BadValue;
			return core(getValue1(t1), getValue2(t2)) ? Analysis::Ok : Analysis::NotOk;
		}

		template<typename T1, typename T2, typename Expr1, typename Expr2>
		Analysis* Analyse(const T1 &t1, const T2 &t2,
			Expr1 expr1, Expr2 expr2,
			bool analyseIfSuccess=false, bool negate=false) const
		{
			return Core::GetAnalysis2(core,
				t1, expr1, getValue1, Stringize1(),
				t2, expr2, getValue2, Stringize2(),
				analyseIfSuccess, negate);
		}

		template<typename T1, typename T2, typename Expr1, typename Expr2>
		Analysis* GetDummyAnalysis(const T1 &t1, const T2 &t2, Expr1 expr1, Expr2 expr2) const
		{
			return Core::GetDummyAnalysis2(core, t1, expr1, getValue1, Stringize1(), t2, expr2, getValue2, Stringize2());
		}

		typedef typename Core::Points Points;
		Points GetGood() const
		{
			return core.GetGood();
		}
		template<typename T1, typename T2>
		Points GetPoints(const T1 &t1, const T2 &t2) const
		{
			if (getValue1.BadPtrChain(t1))
				return 0;
			if (getValue2.BadPtrChain(t2))
				return 0;
			return core.GetPoints(getValue1(t1), getValue2(t2));
		}
		template<typename T1>
		detail::String GetString1(const T1 &t1) const
		{
			return getValue1.ToString(t1, Stringize1());
		}
		template<typename T2>
		detail::String GetString2(const T2 &t2) const
		{
			return getValue2.ToString(t2, Stringize2());
		}
		template<typename T1>
		bool IsValid1(const T1 &t1) const
		{
			return !getValue1.BadPtrChain(t1);
		}
		template<typename T2>
		bool IsValid2(const T2 &t2) const
		{
			return !getValue2.BadPtrChain(t2);
		}

		Core GetCore() const
		{
			return core;
		}
	};

#define RICHBOOL_WRAPPER2ARG(FUNCTOR, CORE) \
	template <class GV1=RichBool::Value, class GV2=RichBool::Value, \
		class Str1_=RichBool::MakeString, class Str2_=RichBool::MakeString> \
	struct FUNCTOR: public RichBool::Wrapper2Arg<CORE, GV1, GV2, Str1_, Str2_> { \
		FUNCTOR(GV1 gv1=GV1(), GV2 gv2=GV2()): \
			RichBool::Wrapper2Arg<CORE, GV1, GV2, Str1_, Str2_>(gv1, gv2) \
		{} \
	};

#define RICHBOOL_WRAPPER2ARG_1CARG(FUNCTOR, CORE, ARG1, VAL1) \
	template <class GV1=RichBool::Value, class GV2=RichBool::Value, \
		class Str1_=RichBool::MakeString, class Str2_=RichBool::MakeString> \
	struct FUNCTOR: public RichBool::Wrapper2Arg<CORE, GV1, GV2, Str1_, Str2_> { \
		FUNCTOR(ARG1, GV1 gv1=GV1(), GV2 gv2=GV2()): \
			RichBool::Wrapper2Arg<CORE, GV1, GV2, Str1_, Str2_>(CORE(VAL1), gv1, gv2) \
		{} \
	};

	template <typename Pred>
	class Pred2Core: public FunctorCore
	{
		Pred pred;
	public:
		Pred2Core() {}
		Pred2Core(const Pred &pred_): pred(pred_) {}
		Pred2Core(const Pred2Core &pred_): pred(pred_.pred) {}

		template<typename T1, typename T2>
		bool operator()(const T1 &t1, const T2 &t2) const
		{
			return pred(t1, t2);
		}

		const char* GetTextBefore1() const
		{
			return "predicate(";
		}
		const char* GetTextBefore2() const
		{
			return ", ";
		}
		const char* GetTextAfter2() const
		{
			return ")";
		}
	};

	template <class Pred,
		class GV1=Value, class GV2=Value,
		class Stringize1=MakeString, class Stringize2=MakeString>
	struct Pred2: public Wrapper2Arg<Pred2Core<Pred>, GV1, GV2,
		Stringize1, Stringize2>
	{
		Pred2(GV1 gv1=GV1(), GV2 gv2=GV2()):
			Wrapper2Arg<Pred2Core<Pred>,
				GV1, GV2, Stringize1, Stringize2>(gv1, gv2)
		{}
		Pred2(const Pred &pred, GV1 gv1=GV1(), GV2 gv2=GV2()):
			Wrapper2Arg<Pred2Core<Pred>,
				GV1, GV2, Stringize1, Stringize2>(pred, gv1, gv2)
		{}
	};

	template<class Pred>
	Pred2<Pred, Value, Value, MakeString, MakeString>
	PredToRichBool_2Arg(const Pred &pred)
	{
		return Pred2<Pred, Value, Value, MakeString, MakeString>(pred);
	}

	template<class Pred, class GV1_, class GV2_,
		class Stringize1, class Stringize2>
	Pred2<Pred, GV1_, GV2_, Stringize1, Stringize2>
	PredToRichBool_2Arg(const Pred &pred,
		GV1_ , GV2_ ,
		Stringize1 , Stringize2 )
	{
		return Pred2<Pred, GV1_, GV2_, Stringize1, Stringize2>(pred);
	}

	template <class Relation>
	struct Order2Core: public FunctorCore
	{
		Relation relation;
		template<typename T1, typename T2>
		bool operator()(const T1 &t1, const T2 &t2) const
		{
			return relation(t1, t2);
		}
		const char* GetTextBefore2() const
		{ return Relation::name(); }
	};
	template <class Relation, class GV1=Value, class GV2=Value,
		class Stringize_=MakeString>
	struct Order2: public Wrapper2Arg<Order2Core<Relation>, GV1, GV2, Stringize_>
	{
		Order2(GV1 gv1=GV1(), GV2 gv2=GV2()):
			Wrapper2Arg<Order2Core<Relation>, GV1, GV2, Stringize_>(gv1, gv2)
		{}
	};

	template <class Relation>
	Order2<Relation> MakeOrder2(Relation)
	{
		return Order2<Relation>();
	}

	typedef Order2Core<EqualRelation> EqualCore;
	RICHBOOL_WRAPPER2ARG(Equal, EqualCore)

	typedef Order2Core<LessRelation> LessCore;
	RICHBOOL_WRAPPER2ARG(Less, LessCore)

	typedef Order2Core<LessOrEqualRelation> LessOrEqualCore;
	RICHBOOL_WRAPPER2ARG(LessOrEqual, LessOrEqualCore)

	typedef Order2Core<MoreRelation> MoreCore;
	RICHBOOL_WRAPPER2ARG(More, MoreCore)

	typedef Order2Core<MoreOrEqualRelation> MoreOrEqualCore;
	RICHBOOL_WRAPPER2ARG(MoreOrEqual, MoreOrEqualCore)

	typedef Order2Core<DifferentRelation> DiffCore;
	RICHBOOL_WRAPPER2ARG(Diff, DiffCore)

	struct EqualUsingLessCore: public FunctorCore
	{
		template <typename T1, typename T2>
		bool operator()(const T1 &t1, const T2 &t2) const
		{
			return (!(t1<t2))&&(!(t2<t1));
		}
		const char* GetTextAfter1() const
		{
			return " == ";
		}
	};
	RICHBOOL_WRAPPER2ARG(EqualUsingLess, EqualUsingLessCore)

	struct EqualUsingMoreCore: public FunctorCore
	{
		template <typename T1, typename T2>
		bool operator()(const T1 &t1, const T2 &t2) const
		{
			return (!(t1>t2))&&(!(t2>t1));
		}
		const char* GetTextAfter1() const
		{
			return " == ";
		}
	};
	RICHBOOL_WRAPPER2ARG(EqualUsingMore, EqualUsingMoreCore)

	template <class GV1=Value, class GV2=Value>
	struct EqualPtr: public Wrapper2Arg<EqualCore, GV1, GV2,
		MakeStringOfPointer<true, true>, MakeStringOfPointer<true, true> >
	{
		EqualPtr(GV1 gv1=GV1(), GV2 gv2=GV2()):
			Wrapper2Arg<EqualCore, GV1, GV2, MakeStringOfPointer<true, true>, MakeStringOfPointer<true, true> >(gv1, gv2)
		{}
	};

	struct EqualBitwiseCore: public CustomFunctorCore<false>
	{
		template<typename T>
		bool operator()(const T &bits, const T &mask) const
		{
			return bits==mask;
		}
		template<typename T>
		Analysis* Analyse(const T &bits1, const detail::String &str1, SharedExpression expr1,
			const T &bits2, const detail::String &str2, SharedExpression expr2,
			bool ok) const
		{
			const unsigned char *p1 = (const unsigned char*)&bits1,
				*p2 = (const unsigned char*)&bits2;
			return Analyse(p1, p2, sizeof(T), str1, str2, expr1, expr2, ok);
		}
		RICHBOOL_DLL_API Analysis* Analyse(const unsigned char *bits1,
			const unsigned char *bits2,
			size_t len,
			const detail::String &str1, const detail::String &str2,
			SharedExpression expr1, SharedExpression expr2, bool ok) const;
		const char* GetTextAfter1() const
		{ return " .==. "; }
	};
	RICHBOOL_WRAPPER2ARG(EqualBitwise, EqualBitwiseCore)

	struct BitsOffCore: public CustomFunctorCore<false>
	{
		template<typename T>
		bool operator()(const T &bits, const T &mask) const
		{
			return (bits&mask)==0;
		}
		template<typename T>
		Analysis* Analyse(const T &bits, const detail::String &str1, SharedExpression expr1,
			const T &mask, const detail::String &str2, SharedExpression expr2, bool ok) const
		{
			const unsigned char *p1 = (const unsigned char*)&bits,
				*p2 = (const unsigned char*)&mask;
			return Analyse_(p1, str1, expr1, p2, str2, expr2, sizeof(T), ok);
		}
		RICHBOOL_DLL_API Analysis* Analyse_(const unsigned char *bits, const detail::String &str1, SharedExpression expr1,
			const unsigned char *mask, const detail::String &str2, SharedExpression expr2,
			size_t len, bool ok) const;
		const char* GetTextAfter1() const
		{ return " has bits "; }
		const char* GetTextAfter2() const
		{ return " off "; }
	};
	RICHBOOL_WRAPPER2ARG(BitsOff, BitsOffCore)

	struct BitsOnCore: public CustomFunctorCore<false>
	{
		template<typename T>
		bool operator()(const T &bits, const T &mask) const
		{
			return (bits&mask)==mask;
		}
		template<typename T>
		Analysis* Analyse(const T &bits, const detail::String &, SharedExpression expr1,
			const T &mask, const detail::String &, SharedExpression expr2, bool ok) const
		{
			const unsigned char *p1 = (const unsigned char*)&bits,
				*p2 = (const unsigned char*)&mask;
			return Analyse(p1, expr1, p2, expr2, sizeof(T), ok);
		}
		RICHBOOL_DLL_API Analysis* Analyse(const unsigned char *bits, SharedExpression expr1,
			const unsigned char *mask, SharedExpression expr2,
			size_t len, bool ok) const;
		const char* GetTextAfter1() const
		{ return " has bits "; }
		const char* GetTextAfter2() const
		{ return " on "; }
	};
	RICHBOOL_WRAPPER2ARG(BitsOn, BitsOnCore)

	struct BitsAreCore: public CustomFunctorCore<false>
	{
	    enum BitCompareResult { Ok, Mismatch, MaskTooShort, MaskTooLong, IllegalCharacter };
		template<typename T>
		bool operator()(const T &bits, const detail::String &mask) const
		{
			const unsigned char *p1 = (const unsigned char*)&bits;
			return Match(p1, sizeof(bits), mask)==Ok;
		}
		BitCompareResult Match(const void *bits, int nrBytes, const detail::String &mask) const;
		template<typename T>
		Analysis* Analyse(const T &bits, const detail::String &, SharedExpression expr1,
			const detail::String &mask, const detail::String &, SharedExpression expr2, bool ok) const
		{
			const unsigned char *p1 = (const unsigned char*)&bits;
			return Analyse(p1, expr1, mask, expr2, sizeof(T), ok);
		}
		RICHBOOL_DLL_API Analysis* Analyse(const unsigned char *bits, SharedExpression expr1,
			const detail::String &mask, SharedExpression expr2,
			size_t nrBytes, bool ok) const;
		const char* GetTextAfter1() const
		{ return " has bits "; }
	};
	RICHBOOL_WRAPPER2ARG(BitsAre, BitsAreCore)

	struct EqualTypesCore: public FunctorCore
	{
		template<typename T1, typename T2>
		bool operator()(const T1 &t1, const T2 &t2) const
		{
			return equal_type_info(typeid(t1), typeid(t2));
		}

		const char* GetTextBefore1() const { return "typeid("; }
		const char* GetTextAfter1() const { return ")"; }
		const char* GetTextBeforeResult1() const { return ":"; }
		template<typename T1, typename T2>
		detail::String GetResult1(const T1 &t1, const T2 &) const
		{
			return typeid(t1).name();
		}

		const char* GetTextBefore2() const { return " == typeid("; }
		const char* GetTextAfter2() const { return ")"; }
		const char* GetTextBeforeResult2() const { return ":"; }
		template<typename T1, typename T2>
		detail::String GetResult2(const T1 &, const T2 &t2) const
		{
			return typeid(t2).name();
		}
	};
	RICHBOOL_WRAPPER2ARG(EqualTypes, EqualTypesCore)

	// for usage in macros:
	typedef EqualTypes<Pointer<>, Pointer<> > EqualTypesPointers;


	// Rich Boolean functors working on files

    namespace detail
    {
        int GetFileNo(FILE *file);
    }

#if defined(RICHBOOL_WIN) && !defined(__CYGWIN__)
    #define RICHBOOL_STAT _stat
    #define RICHBOOL_FSTAT _fstat
    #define RICHBOOL_ISDIR(mode) (((mode)&_S_IFMT)==_S_IFDIR)
#else
    #define RICHBOOL_STAT stat
    #define RICHBOOL_FSTAT fstat
    #define RICHBOOL_ISDIR(mode) S_ISDIR(mode)
#endif

#if !defined(RICHBOOL_WIN)
	detail::String LinkStatus(const char *name);
	detail::String LinkStatus(int desc);
	detail::String LinkStatus(FILE *file);
    #define RICHBOOL_LINK_STATUS(name) LinkStatus(name)+
#else
    #define RICHBOOL_LINK_STATUS(name)
#endif

	namespace detail
	{
		RICHBOOL_DLL_API String PathCheck(const String &path_org);
#if defined(RICHBOOL_WIN)
#ifdef RICHBOOL_HAS_WSTRING
		RICHBOOL_DLL_API String PathCheck(const std::wstring &path_org);
#endif
		RICHBOOL_DLL_API String PathCheck(const wchar_t *path_org);
#endif
		// next two overloads should not be called:
		inline String PathCheck(int) { return ""; }
		inline String PathCheck(FILE*) { return ""; }

		inline String FileDescToString(const char *name) { return EscapeString(name); }
#if defined(RICHBOOL_WIN)
		inline String FileDescToString(const wchar_t *name) { return EscapeString(name); }
#endif
		inline String FileDescToString(int fd) { return ToString(fd); }
		inline String FileDescToString(FILE *file) { return PtrToString(file); }
	}

	struct FileExistsCore: public CustomFunctorCore<true>
	{
		bool operator()(const char *filename) const
		{
			struct RICHBOOL_STAT st;
			int result = RICHBOOL_STAT(filename, &st);
			return (result==0) && (!RICHBOOL_ISDIR(st.st_mode));
		}
		bool operator()(const detail::String &filename) const
		{
			return operator()(detail::c_str(filename));
		}
#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
		bool operator()(const wchar_t *filename) const
		{
			struct RICHBOOL_STAT st;
			int result = _wstat(filename, &st);
			return (result==0) && (!RICHBOOL_ISDIR(st.st_mode));
		}
		bool operator()(const std::wstring &filename) const
		{
			return operator()(filename.c_str());
		}
#endif
		bool operator()(int fd) const
		{
			struct RICHBOOL_STAT st;
			int result = RICHBOOL_FSTAT(fd, &st);
			return result==0;
		}
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const char *filename, Expr1 expr1, Stringize1 ,
			bool analysisIfSuccess, bool negate=false) const
		{
			struct RICHBOOL_STAT st;
			int result = RICHBOOL_STAT(filename, &st);
			return Analyse_("file ", filename, result, st, expr1, analysisIfSuccess, negate);
		}
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const detail::String &filename, Expr1 expr1, Stringize1 str1,
			bool analysisIfSuccess, bool negate=false) const
		{
			return Analyse(detail::c_str(filename), expr1, str1, analysisIfSuccess, negate);
		}
#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const wchar_t *wfilename, Expr1 expr1, Stringize1 ,
			bool analysisIfSuccess, bool negate=false) const
		{
			struct RICHBOOL_STAT st;
			int result = _wstat(wfilename, &st);
			return Analyse_("file ", wfilename, result, st, expr1, analysisIfSuccess, negate);
		}
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const std::wstring &filename, Expr1 expr1, Stringize1 str1,
			bool analysisIfSuccess, bool negate=false) const
		{
			return Analyse(filename.c_str(), expr1, str1, analysisIfSuccess, negate);
		}
#endif
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(int fd, Expr1 expr1, Stringize1 ,
			bool analysisIfSuccess, bool negate=false) const
		{
			struct RICHBOOL_STAT st;
			int result = RICHBOOL_FSTAT(fd, &st);
			return Analyse_("file with descriptor ", fd, result, st, expr1, analysisIfSuccess, negate);
		}
		const char* GetTextBefore1() const
		{ return "file "; }
		const char* GetTextAfter1() const
		{ return " should exist"; }
	private:
		template <typename Expr1, typename Desc>
		Analysis* Analyse_(const char *type, Desc desc, int result, const struct RICHBOOL_STAT &st,
			Expr1 expr1, bool analysisIfSuccess, bool negate) const
		{
			bool exists = result==0;
			bool isDir = RICHBOOL_ISDIR(st.st_mode);
			if ((exists!=negate)&&!isDir&&!analysisIfSuccess)
				return 0;
			MakeGeneralAnalysis ga((exists!=negate)&&!isDir);
			ga(type).expr(expr1, ":")(detail::FileDescToString(desc), true)(" should exist");
			if (exists&&isDir)
				ga.ep(" is a directory");
			else if (!exists)
				ga.ep(detail::PathCheck(desc));
			return ga;
		}
	};
	template <class GetValue1=Value>
	struct FileExists: public Wrapper1Arg<FileExistsCore, GetValue1, MakeString> {
		FileExists(GetValue1 gv1=GetValue1()):
			Wrapper1Arg<FileExistsCore, GetValue1, MakeString>(gv1)
		{}
	};

	struct DirectoryExistsCore: public CustomFunctorCore<true>
	{
		bool operator()(const char *name) const
		{
			struct RICHBOOL_STAT st;
			int result = RICHBOOL_STAT(name, &st);
			return (result==0) && (RICHBOOL_ISDIR(st.st_mode));
		}
		bool operator()(const detail::String &filename) const
		{
			return operator()(detail::c_str(filename));
		}
#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
		bool operator()(const wchar_t *name) const
		{
			struct RICHBOOL_STAT st;
			int result = _wstat(name, &st);
			return (result==0) && (RICHBOOL_ISDIR(st.st_mode));
		}
		bool operator()(const std::wstring &filename) const
		{
			return operator()(filename.c_str());
		}
#endif
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const char *name, Expr1 expr1, Stringize1 ,
			bool analysisIfSuccess, bool negate=false) const
		{
			struct RICHBOOL_STAT st;
			int result = RICHBOOL_STAT(name, &st);
			return FinishAnalysis(name, expr1, Stringize1(), analysisIfSuccess, negate, result, st);
		}
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const detail::String &filename, Expr1 expr1, Stringize1 str1,
			bool analysisIfSuccess, bool negate=false) const
		{
			return Analyse(detail::c_str(filename), expr1, str1, analysisIfSuccess, negate);
		}
#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const wchar_t *name, Expr1 expr1, Stringize1 ,
			bool analysisIfSuccess, bool negate=false) const
		{
			struct RICHBOOL_STAT st;
			int result = _wstat(name, &st);
			return FinishAnalysis(name, expr1, Stringize1(), analysisIfSuccess, negate, result, st);
		}
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const std::wstring &filename, Expr1 expr1, Stringize1 str1,
			bool analysisIfSuccess, bool negate=false) const
		{
			return Analyse(filename.c_str(), expr1, str1, analysisIfSuccess, negate);
		}
#endif
		template <typename Expr1, class Stringize1, typename E>
		Analysis* FinishAnalysis(const E *name, Expr1 expr1, Stringize1 ,
			bool analysisIfSuccess, bool negate, int result, const struct RICHBOOL_STAT &st) const
		{
			bool exists=result==0, isDir=RICHBOOL_ISDIR(st.st_mode);
			bool ok = (exists!=negate)&&isDir;
			if (ok && !analysisIfSuccess)
				return 0;
			MakeGeneralAnalysis ga(ok);
			ga("directory ").expr(expr1, ":")(detail::EscapeString(name), true)(" should exist");
			if (exists&&!isDir)
				ga.ep(" is a file");
			else if (!exists)
				ga.ep(detail::PathCheck(name));
			return ga;
		}
		const char* GetTextBefore1() const
		{
			return "directory ";
		}
		const char* GetTextAfter1() const
		{
			return " should exist";
		}
	};
	template <class GetValue1=Value>
	struct DirectoryExists: public Wrapper1Arg<DirectoryExistsCore, GetValue1> {
		DirectoryExists(GetValue1 gv1=GetValue1()):
			Wrapper1Arg<DirectoryExistsCore, GetValue1>(gv1)
		{}
	};

#if defined(RICHBOOL_WIN)
#ifdef RICHBOOL_HAS_WSTRING
	#define RICHBOOL_FILE_CHECK_WSTRING \
		bool operator()(const wchar_t *name, const struct RICHBOOL_STAT &fs) const; \
		bool operator()(const std::wstring &filename, const struct RICHBOOL_STAT &fs) const \
		{ \
			return operator()(filename.c_str(), fs); \
		}
#else
	#define RICHBOOL_FILE_CHECK_WSTRING \
		bool operator()(const wchar_t *name, const struct RICHBOOL_STAT &fs) const;
#endif
#else
	#define RICHBOOL_FILE_CHECK_WSTRING
#endif

#define RICHBOOL_FILE_CHECK(name, text) \
	struct name##Core: public FunctorCore \
	{ \
		bool operator()(const char *name, const struct RICHBOOL_STAT &fs) const; \
		bool operator()(const detail::String &filename, const struct RICHBOOL_STAT &fs) const \
		{ \
			return operator()(detail::c_str(filename), fs); \
		} \
		RICHBOOL_FILE_CHECK_WSTRING \
		const char* GetTextAfter1() const \
		{ \
			return text; \
		} \
	}; \
	struct name: public Wrapper2Arg<name##Core, Value, Value, \
			HideString, HideString> \
	{};

	RICHBOOL_FILE_CHECK(IsReadable, "readable")
	RICHBOOL_FILE_CHECK(IsWritable, "writable")
	RICHBOOL_FILE_CHECK(IsExecutable, "executable")
	RICHBOOL_FILE_CHECK(IsRegular, "regular")
	RICHBOOL_FILE_CHECK(IsDevice, "device")
	RICHBOOL_FILE_CHECK(IsPipe, "pipe")

#if !defined(RICHBOOL_WIN)
	RICHBOOL_FILE_CHECK(IsCharacterSpecial, "character special")
	RICHBOOL_FILE_CHECK(IsBlockSpecial, "block special")
	RICHBOOL_FILE_CHECK(IsLink, "link")
	RICHBOOL_FILE_CHECK(IsSocket, "socket")
	detail::String GetUserAndGroup();
#endif

	detail::String ToString(const struct RICHBOOL_STAT &st);
	inline detail::String ToString(FILE *file) { return PtrToString(file); }

	template <class Func>
	struct FileCore: public CustomFunctorCore<true>
	{
		FileCore(Func f): func(f) {}
		Func func;

		bool operator()(const char *name) const
		{
			struct RICHBOOL_STAT st;
			int result = RICHBOOL_STAT(name, &st);
			return (result==0) && (!RICHBOOL_ISDIR(st.st_mode)) && func(name, st);
		}
		bool operator()(const detail::String &filename) const
		{
			return operator()(detail::c_str(filename));
		}
#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
		bool operator()(const wchar_t *name) const
		{
			struct RICHBOOL_STAT st;
			int result = _wstat(name, &st);
			return (result==0) && (!RICHBOOL_ISDIR(st.st_mode)) && func(name, st);
		}
		bool operator()(const std::wstring &filename) const
		{
			return operator()(filename.c_str());
		}
#endif
		bool operator()(int fd) const
		{
			if (fd==-1)
				return false;
			struct RICHBOOL_STAT st;
			int result = RICHBOOL_FSTAT(fd, &st);
			return (result==0) && (!RICHBOOL_ISDIR(st.st_mode)) && func((const char*)0, st);
		}
		bool operator()(FILE *file) const
		{
			return file ? operator()(detail::GetFileNo(file)) : false;
		}
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const char *name, Expr1 expr1, Stringize1 ,
			bool analysisIfSuccess, bool negate=false) const
		{
			struct RICHBOOL_STAT st;
			int result = RICHBOOL_STAT(name, &st);
			return Analyse_("file ", name, result, st, expr1, analysisIfSuccess, negate);
		}
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const detail::String &filename, Expr1 expr1, Stringize1 str1,
			bool analysisIfSuccess, bool negate=false) const
		{
			return Analyse(detail::c_str(filename), expr1, str1, analysisIfSuccess, negate);
		}
#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const wchar_t *name, Expr1 expr1, Stringize1 ,
			bool analysisIfSuccess, bool negate=false) const
		{
			struct RICHBOOL_STAT st;
			int result = _wstat(name, &st);
			return Analyse_("file ", name, result, st, expr1, analysisIfSuccess, negate);
		}
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const std::wstring &filename, Expr1 expr1, Stringize1 str1,
			bool analysisIfSuccess, bool negate=false) const
		{
			return Analyse(filename.c_str(), expr1, str1, analysisIfSuccess, negate);
		}
#endif
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(int fd, Expr1 expr1, Stringize1 ,
			bool analysisIfSuccess, bool negate=false) const
		{
			if (fd<0)
			{
				MakeGeneralAnalysis ga(false);
				ga("file ").expr(expr1, ":")(detail::FileDescToString(fd), true)(" is negative, no valid file");
				return ga;
			}
			struct RICHBOOL_STAT st;
			int result = RICHBOOL_FSTAT(fd, &st);
			return Analyse_("file with descriptor ", fd, result, st, expr1, analysisIfSuccess, negate);
		}
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(FILE *file, Expr1 expr1, Stringize1 ,
			bool analysisIfSuccess, bool negate=false) const
		{
			if (!file)
			{
				MakeGeneralAnalysis ga(false);
				ga("file ").expr(expr1, ":")(detail::FileDescToString(file), true)(" is NULL");
				return ga;
			}
			struct RICHBOOL_STAT st;
			int result = RICHBOOL_FSTAT(detail::GetFileNo(file), &st);
			return Analyse_("file ", file, result, st, expr1, analysisIfSuccess, negate);
		}
		const char* GetTextBefore1() const
		{ return "file "; }
	private:
		static const char* GetName(const char *str)
		{
			return str;
		}
		static const wchar_t* GetName(const wchar_t *str)
		{
			return str;
		}
		static const char* GetName(int )
		{
			return 0;
		}
		static const char* GetName(FILE* )
		{
			return 0;
		}
		template <typename Expr1, typename Desc>
		Analysis* Analyse_(const char *type, Desc desc, int result, const struct RICHBOOL_STAT &st,
			Expr1 expr1, bool analysisIfSuccess, bool negate) const
		{
			if ((result==0)&&!(RICHBOOL_ISDIR(st.st_mode))&&!analysisIfSuccess&&(func(GetName(desc), st)!=negate))
				return 0;

			// create analysis here, so it is not created when we return 0:
			MakeGeneralAnalysis ga(false);
			ga(type).expr(expr1, ":")(detail::FileDescToString(desc), true)(" should be ");
			Analysis *an = 0;
			if ((result==0)&&!RICHBOOL_ISDIR(st.st_mode))
			{
				an = func.Analyse(GetName(desc), st, (const char*)0, (const char*)0, true, false);
				ga.core(an, true);
			}
			else
			{
				an = func.GetDummyAnalysis(GetName(desc), st, (const char*)0, (const char*)0);
				ga(an, true);
			}

			if (result!=0)
			{
				return ga.ep(detail::PathCheck(desc));
			}
			else if (RICHBOOL_ISDIR(st.st_mode))
			{
				return ga.ep(" is a directory");
			}
			else
			{
				ga.SetState(an->GetState());
				ga.ep(RICHBOOL_LINK_STATUS(desc)ToString(st)
#if !defined(RICHBOOL_WIN)
					+"; process user and group: "+GetUserAndGroup()
#endif
					);
				return ga;
			}
		}
	};
	template <class Func, class GetValue1=Value>
	struct File: public Wrapper1Arg<FileCore<Func>, GetValue1, MakeString> {
		File(GetValue1 gv1=GetValue1()):
			Wrapper1Arg<FileCore<Func>, GetValue1, MakeString>(gv1)
		{}
		File(Func func, GetValue1 gv1=GetValue1()):
			Wrapper1Arg<FileCore<Func>, GetValue1, MakeString>(func, gv1)
		{}
	};

	template <class Func>
	File<Func> MakeFile(Func func)
	{
		return File<Func>(func);
	}

	template <class Func>
	struct DirectoryCore: public CustomFunctorCore<true>
	{
		DirectoryCore(Func f): func(f) {}
		Func func;

		bool operator()(const char *name) const
		{
			struct RICHBOOL_STAT st;
			int result = RICHBOOL_STAT(name, &st);
			return (result==0) && (RICHBOOL_ISDIR(st.st_mode)) && func(name, st);
		}
		bool operator()(const detail::String &filename) const
		{
			return operator()(detail::c_str(filename));
		}
#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
		bool operator()(const wchar_t *name) const
		{
			struct RICHBOOL_STAT st;
			int result = _wstat(name, &st);
			return (result==0) && (RICHBOOL_ISDIR(st.st_mode)) && func(name, st);
		}
		bool operator()(const std::wstring &filename) const
		{
			return operator()(filename.c_str());
		}
#endif
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const char *name, Expr1 expr1, Stringize1 ,
			bool analysisIfSuccess, bool negate=false) const
		{
			struct RICHBOOL_STAT st;
			int result = RICHBOOL_STAT(name, &st);
			return FinishAnalysis(name, expr1, Stringize1(), analysisIfSuccess, negate, result, st);
		}
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const detail::String &filename, Expr1 expr1, Stringize1 str1,
			bool analysisIfSuccess, bool negate=false) const
		{
			return Analyse(detail::c_str(filename), expr1, str1, analysisIfSuccess, negate);
		}
#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const wchar_t *name, Expr1 expr1, Stringize1 ,
			bool analysisIfSuccess, bool negate=false) const
		{
			struct RICHBOOL_STAT st;
			int result = _wstat(name, &st);
			return FinishAnalysis(name, expr1, Stringize1(), analysisIfSuccess, negate, result, st);
		}
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const std::wstring &filename, Expr1 expr1, Stringize1 str1,
			bool analysisIfSuccess, bool negate=false) const
		{
			return Analyse(detail::c_str(filename), expr1, str1, analysisIfSuccess, negate);
		}
#endif
		template <typename Expr1, class Stringize1, typename E>
		Analysis* FinishAnalysis(const E *name, Expr1 expr1, Stringize1 ,
			bool analysisIfSuccess, bool negate, int result, const struct RICHBOOL_STAT &st) const
		{
			Analysis *an = 0;
			if ( (result!=0) || !RICHBOOL_ISDIR(st.st_mode) )
				an = func.GetDummyAnalysis(name, st, (const char*)0, (const char*)0);
			else
			{
				an = func.Analyse(name, st, (const char*)0, (const char*)0, analysisIfSuccess, negate);
				if (!an)
					return 0;
			}

			// create analysis here, so it is not created when we return 0:
			MakeGeneralAnalysis ga(false);
			ga("directory ").expr(expr1, ":")(detail::EscapeString(name), true)(" should be ");
			if ( (result!=0) || !RICHBOOL_ISDIR(st.st_mode) )
				ga(an, true);
			else
				ga.core(an, true);
			if (result!=0)
			{
				return ga.ep(detail::PathCheck(name));
			}
			else if (!RICHBOOL_ISDIR(st.st_mode))
			{
				return ga.ep(" is a file");
			}
			else
			{
				ga.ep(RICHBOOL_LINK_STATUS(name)ToString(st)
#if !defined(RICHBOOL_WIN)
					+"; process user and group: "+GetUserAndGroup()
#endif
					);
				return ga;
			}
		}
		const char* GetTextBefore1() const
		{ return "directory "; }
		const char* GetTextBefore2() const
		{ return " has properties "; }
	};
	template <class Func, class GetValue1=Value>
	struct Directory: public Wrapper1Arg<DirectoryCore<Func>, GetValue1, MakeString> {
		Directory(GetValue1 gv1=GetValue1()):
			Wrapper1Arg<DirectoryCore<Func>, GetValue1, MakeString>(gv1)
		{}
		Directory(Func func, GetValue1 gv1=GetValue1()):
			Wrapper1Arg<DirectoryCore<Func>, GetValue1, MakeString>(func, gv1)
		{}
	};

	template <class Func>
	Directory<Func> MakeDirectory(Func func)
	{
		return Directory<Func>(func);
	}

	struct DoesNotExistCore: public CustomFunctorCore<true>
	{
		bool operator()(const char *name) const
		{
			struct RICHBOOL_STAT st;
			int result = RICHBOOL_STAT(name, &st);
			return (result!=0);
		}
		bool operator()(const detail::String &name) const
		{
			return operator()(detail::c_str(name));
		}
#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
		bool operator()(const wchar_t *name) const
		{
			struct RICHBOOL_STAT st;
			int result = _wstat(name, &st);
			return (result!=0);
		}
		bool operator()(const std::wstring &name) const
		{
			return operator()(name.c_str());
		}
#endif
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const char *name, Expr1 expr1, Stringize1 ,
			bool analysisIfSuccess, bool negate=false) const
		{
			struct RICHBOOL_STAT st;
			bool ok = RICHBOOL_STAT(name, &st)!=0;
			return FinishAnalysis(name, expr1, Stringize1(), analysisIfSuccess, negate, ok, st);
		}
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const detail::String &name, Expr1 expr1, Stringize1 ,
			bool analysisIfSuccess, bool negate=false) const
		{
			return Analyse(name.c_str(), expr1, Stringize1(), analysisIfSuccess, negate);
		}
#if defined(RICHBOOL_WIDE_CHAR_FILENAMES)
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const wchar_t *name, Expr1 expr1, Stringize1 ,
			bool analysisIfSuccess, bool negate=false) const
		{
			struct RICHBOOL_STAT st;
			bool ok = _wstat(name, &st)!=0;
			return FinishAnalysis(name, expr1, Stringize1(), analysisIfSuccess, negate, ok, st);
		}
		template <typename Expr1, class Stringize1>
		Analysis* Analyse(const std::wstring &name, Expr1 expr1, Stringize1 ,
			bool analysisIfSuccess, bool negate=false) const
		{
			return Analyse(name.c_str(), expr1, Stringize1(), analysisIfSuccess, negate);
		}
#endif
		template <typename Expr1, class Stringize1, typename E>
		Analysis* FinishAnalysis(const E *name, Expr1 expr1, Stringize1 ,
			bool analysisIfSuccess, bool negate, bool ok, const struct RICHBOOL_STAT &st) const
		{
			if ((ok==negate)||analysisIfSuccess)
			{
				MakeGeneralAnalysis ga(ok!=negate);
				ga.expr(expr1, ":")(detail::EscapeString(name), true)(" should not exist");
				if (!ok)
					ga.ep( (!RICHBOOL_ISDIR(st.st_mode)) ? " is a file" : " is a directory");
				return ga;
			}
			else
				return 0;
		}
		const char* GetTextAfter1() const
		{ return " should not exist"; }
	};
	template <class GetValue1=Value>
	struct DoesNotExist: public Wrapper1Arg<DoesNotExistCore, GetValue1, MakeString> {
		DoesNotExist(GetValue1 gv1=GetValue1()):
			Wrapper1Arg<DoesNotExistCore, GetValue1, MakeString>(gv1)
		{}
	};

#if !defined(RICHBOOL_WIN)
	void SetFsUid(uid_t fsuid);
	void SetFsGid(uid_t fsgid);
#endif


	////////////////////////////////////////////////
	// with three arguments

	template <class Core,
		class GV1_=Value,
		class GV2_=Value,
		class GV3_=Value,
		class Stringize1_=MakeString,
		class Stringize2_=MakeString,
		class Stringize3_=MakeString>
	class Wrapper3Arg: public Functors::Base
	{
		Core core;
	public:
		typedef GV1_ GV1;
		typedef GV2_ GV2;
		typedef GV3_ GV3;
		GV1 getValue1;
		GV2 getValue2;
		GV3 getValue3;
		typedef Stringize1_ Stringize1;
		typedef Stringize2_ Stringize2;
		typedef Stringize3_ Stringize3;
		typedef typename Core::Points Points;

		Wrapper3Arg(GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3()):
			getValue1(gv1), getValue2(gv2), getValue3(gv3)
		{}
		Wrapper3Arg(Core cond, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3()):
			core(cond), getValue1(gv1), getValue2(gv2), getValue3(gv3)
		{}

		template<typename T1, typename T2, typename T3>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
		{
			return core(getValue1(t1), getValue2(t2), getValue3(t3));
		}
		template<typename T1, typename T2, typename T3>
		Analysis::State SafeCheck(const T1 &t1, const T2 &t2, const T3 &t3) const
		{
			if (getValue1.BadPtrChain(t1)||getValue2.BadPtrChain(t2)
				||getValue3.BadPtrChain(t3))
				return Analysis::BadValue;
			return core(getValue1(t1), getValue2(t2), getValue3(t3)) ?
				 Analysis::Ok : Analysis::NotOk;
		}
		template<typename T1, typename T2, typename T3,
			typename Expr1, typename Expr2, typename Expr3>
		Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3,
			Expr1 expr1, Expr2 expr2, Expr3 expr3,
			bool analyseIfSuccess=false, bool negate=false) const
		{
			return Core::GetAnalysis3(core,
				t1, expr1, getValue1, Stringize1(),
				t2, expr2, getValue2, Stringize2(),
				t3, expr3, getValue3, Stringize3(),
				analyseIfSuccess, negate);
		}
		template<typename T1>
		detail::String GetString1(const T1 &t1) const
		{
			return getValue1.ToString(t1, Stringize1());
		}
		template<typename T2>
		detail::String GetString2(const T2 &t2) const
		{
			return getValue2.ToString(t2, Stringize2());
		}
		template<typename T3>
		detail::String GetString3(const T3 &t3) const
		{
			return getValue3.ToString(t3, Stringize3());
		}
		template<typename T1>
		bool IsValid1(const T1 &t1) const
		{
			return !getValue1.BadPtrChain(t1);
		}
		template<typename T2>
		bool IsValid2(const T2 &t2) const
		{
			return !getValue2.BadPtrChain(t2);
		}
		template<typename T3>
		bool IsValid3(const T3 &t3) const
		{
			return !getValue3.BadPtrChain(t3);
		}

		Core GetCore() const
		{
			return core;
		}
	};

#define RICHBOOL_WRAPPER3ARG(FUNCTOR, CORE) \
	template <class GV1=RichBool::Value, class GV2=RichBool::Value, class GV3=RichBool::Value, \
		class Str1_=RichBool::MakeString, class Str2_=RichBool::MakeString, class Str3_=RichBool::MakeString> \
	struct FUNCTOR: public RichBool::Wrapper3Arg<CORE, GV1, GV2, GV3, \
			Str1_, Str2_, Str3_> { \
		FUNCTOR(GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3()): \
			RichBool::Wrapper3Arg<CORE, GV1, GV2, GV3, Str1_, Str2_, Str3_>(gv1, gv2, gv3) \
		{} \
	};

#define RICHBOOL_WRAPPER3ARG_1CARG(FUNCTOR, CORE, ARG1, VAL1) \
	template <class GV1=RichBool::Value, class GV2=RichBool::Value, class GV3=RichBool::Value, \
		class Str1_=RichBool::MakeString, class Str2_=RichBool::MakeString, class Str3_=RichBool::MakeString> \
	struct FUNCTOR: public RichBool::Wrapper3Arg<CORE, GV1, GV2, GV3, Str1_, Str2_, Str3_> { \
		FUNCTOR(ARG1, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3()): \
			RichBool::Wrapper3Arg<CORE, GV1, GV2, GV3, Str1_, Str2_, Str3_>(CORE(VAL1), gv1, gv2, gv3) \
		{} \
	};

	template <typename Pred>
	class Pred3Core: public FunctorCore
	{
		Pred pred;
	public:
		Pred3Core() {}
		Pred3Core(const Pred &pred_): pred(pred_) {}
		Pred3Core(const Pred3Core &pred_): pred(pred_.pred) {}

		template<typename T1, typename T2, typename T3>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
		{
			return pred(t1, t2, t3);
		}

		const char* GetTextBefore1() const
		{
			return "predicate(";
		}
		const char* GetTextBefore2() const
		{
			return ", ";
		}
		const char* GetTextBefore3() const
		{
			return ", ";
		}
		const char* GetTextAfter3() const
		{
			return ")";
		}
	};

	template <class Pred,
		class GV1=Value, class GV2=Value, class GV3=Value,
		class Stringize1=MakeString, class Stringize2=MakeString, class Stringize3=MakeString>
	struct Pred3: public Wrapper3Arg<Pred3Core<Pred>,
		GV1, GV2, GV3, Stringize1, Stringize2, Stringize3>
	{
		Pred3(GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3()):
			Wrapper3Arg<Pred3Core<Pred>,
				GV1, GV2, GV3, Stringize1, Stringize2, Stringize3>(gv1, gv2, gv3)
		{}
		Pred3(const Pred &pred, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3()):
			Wrapper3Arg<Pred3Core<Pred>,
				GV1, GV2, GV3, Stringize1, Stringize2, Stringize3>
				(pred, gv1, gv2, gv3)
		{}
	};

	template<class Pred, class GV1_, class GV2_, class GV3_,
		class Stringize1, class Stringize2, class Stringize3>
	Pred3<Pred, GV1_, GV2_, GV3_,
		Stringize1, Stringize2, Stringize3>
	PredToRichBool_3Arg(const Pred &pred,
		GV1_ ,
		GV2_ ,
		GV3_ ,
		Stringize1 ,
		Stringize2 ,
		Stringize3 )
	{
		return Pred3<Pred, GV1_, GV2_, GV3_,
			Stringize1, Stringize2, Stringize3>(pred);
	}

	template <class Relation>
	struct Order2NearCore: public FunctorCore
	{
		Relation relation;
		template<typename T1, typename T2, typename T3>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
		{
			return relation(t1, t2, t3);
		}
		const char* GetTextBefore2() const
		{ return Relation::name(); }
		const char* GetTextAfter2() const
		{ return " (difference "; }

		const char* GetTextBeforeResult2() const
		{ return "is "; }
		template<typename T1, typename T2, typename T3>
		detail::String GetResult2(const T1 &t1, const T2 &t2, const T3 &) const
		{ return ToString(fabs(t1-t2)); }
		const char* GetTextAfterResult2() const
		{ return ", "; }

		const char* GetTextAfter3() const
		{ return " allowed)"; }
	};
	template <class Relation, class GV1=Value, class GV2=Value,
		class GV3=Value, class Stringize_=MakeString>
	struct Order2Near: public Wrapper3Arg<Order2NearCore<Relation>, GV1, GV2, GV3, Stringize_>
	{
		Order2Near(GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3()):
			Wrapper3Arg<Order2NearCore<Relation>, GV1, GV2, GV3, Stringize_>(gv1, gv2, gv3)
		{}
	};

	template <class Relation>
	Order2Near<Relation>
	MakeOrder2Near(Relation)
	{
		return Order2Near<Relation>();
	}

	typedef Order2NearCore<EqualNearRelation> NearCore;
	RICHBOOL_WRAPPER3ARG(Near, NearCore)

	typedef Order2NearCore<LessNearRelation> LessNearCore;
	RICHBOOL_WRAPPER3ARG(LessNear, LessNearCore)

	typedef Order2NearCore<MoreNearRelation> MoreNearCore;
	RICHBOOL_WRAPPER3ARG(MoreNear, MoreNearCore)

	struct DiffNearCore: public Order2NearCore<DifferentNearRelation>
	{
		const char* GetTextAfterResult2() const
		{ return ", should be at least "; }

		const char* GetTextAfter3() const
		{ return ")"; }
	};
	RICHBOOL_WRAPPER3ARG(DiffNear, DiffNearCore)

	struct InIntervalCore: public FunctorCore
	{
		template<typename T1, typename T2, typename T3>
		bool operator()(const T1 &val, const T2 &low, const T3 &high) const
		{
			return !(val<low) && !(high<val);
		}
		const char* GetTextBefore2() const
		{ return " in ["; }
		const char* GetTextBefore3() const
		{ return ", "; }
		const char* GetTextAfter3() const
		{ return "]"; }
	};
	RICHBOOL_WRAPPER3ARG(InInterval, InIntervalCore)

	struct InOpenIntervalCore: public FunctorCore
	{
		template<typename T1, typename T2, typename T3>
		bool operator()(const T1 &val, const T2 &low, const T3 &high) const
		{
			return (low<val) && (val<high);
		}
		const char* GetTextBefore2() const
		{ return " in ("; }
		const char* GetTextBefore3() const
		{ return ", "; }
		const char* GetTextAfter3() const
		{ return ")"; }
	};
	RICHBOOL_WRAPPER3ARG(InOpenInterval, InOpenIntervalCore)

	template <class Relation>
	struct Order2RelativeNearCore: public FunctorCore
	{
		Relation relation;
		template<typename T1, typename T2, typename T3>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
		{
			return relation(t1, t2, t3);
		}
		const char* GetTextBefore2() const
		{ return Relation::name(); }
		const char* GetTextAfter2() const
		{ return " (relative difference "; }

		const char* GetTextBeforeResult2() const
		{ return "is "; }
		template<typename T1, typename T2, typename T3>
		detail::String GetResult2(const T1 &t1, const T2 &t2, const T3 &) const
		{
			T3 mabs = detail::max_(fabs(t1), fabs(t2));
			return mabs==0.0 ? "0.0" : ToString(fabs(t1-t2)/mabs);
		}
		const char* GetTextAfterResult2() const
		{ return ", "; }

		const char* GetTextAfter3() const
		{ return " allowed)"; }
	};
	template <class Relation, class GV1=Value, class GV2=Value,
		class GV3=Value, class Stringize_=MakeString>
	struct Order2RelativeNear: public Wrapper3Arg<Order2RelativeNearCore<Relation>, GV1, GV2, GV3, Stringize_>
	{
		Order2RelativeNear(GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3()):
			Wrapper3Arg<Order2RelativeNearCore<Relation>, GV1, GV2, GV3, Stringize_>(gv1, gv2, gv3)
		{}
	};

	template <class Relation>
	Order2RelativeNear<Relation>
	MakeOrder2RelativeNear(Relation)
	{
		return Order2RelativeNear<Relation>();
	}

	typedef Order2RelativeNearCore<EqualRelativeNearRelation> RelativeNearCore;
	RICHBOOL_WRAPPER3ARG(RelativeNear, RelativeNearCore)

	typedef Order2RelativeNearCore<LessRelativeNearRelation> LessRelativeNearCore;
	RICHBOOL_WRAPPER3ARG(LessRelativeNear, LessRelativeNearCore)

	typedef Order2RelativeNearCore<MoreRelativeNearRelation> MoreRelativeNearCore;
	RICHBOOL_WRAPPER3ARG(MoreRelativeNear, MoreRelativeNearCore)

	struct DiffRelativeNearCore: public Order2RelativeNearCore<DifferentRelativeNearRelation>
	{
		const char* GetTextAfterResult2() const
		{ return ", should be at least "; }

		const char* GetTextAfter3() const
		{ return ")"; }
	};
	RICHBOOL_WRAPPER3ARG(DiffRelativeNear, DiffRelativeNearCore)

	class RelNearCore: public FunctorCore
	{
	public:
		template<typename T1, typename T2, typename T3>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
		{
			T3 max_diff = detail::max_(fabs(t1), fabs(t2))*t3;
			return fabs(t1-t2)<=max_diff;
		}
		const char* GetTextBefore1() const
		{ return "relative difference of "; }
		const char* GetTextBefore2() const
		{ return " and "; }
		const char* GetTextBefore3() const
		{ return " <= "; }

		const char* GetTextBeforeResult2() const
		{ return " = "; }
		template<typename T1, typename T2, typename T3>
		detail::String GetResult2(const T1 &t1, const T2 &t2, const T3 &) const
		{
			T3 maxAbsolute = detail::max_(fabs(t1), fabs(t2));
			return (maxAbsolute==0) ? "?": ToString(fabs(t1-t2) / maxAbsolute);
		}
	};
	RICHBOOL_WRAPPER3ARG(RelNear, RelNearCore)

	struct EqualDataCore: public CustomFunctorCore<false>
	{
		template <typename T1, typename T2>
		bool operator()(const T1 *buf1, const T2 *buf2, const size_t nrBytes) const
		{
			return memcmp(buf1, buf2, nrBytes)==0;
		}

		template <typename T1, typename T2>
		BriefAnalysisOfTwoSequences* Analyse(const T1 *buf1, const detail::String &str1, SharedExpression expr1,
			const T2 *buf2, const detail::String &str2, SharedExpression expr2,
			const size_t nrBytes, const detail::String &str3, SharedExpression expr3,
			bool ok) const
		{
			return AnalyseBytes(
				(const unsigned char*)buf1, str1, expr1,
				(const unsigned char*)buf2, str2, expr2,
				nrBytes, str3, expr3, ok);
		}

		BriefAnalysisOfTwoSequences* AnalyseBytes(const unsigned char *buf1, const detail::String &str1, SharedExpression expr1,
			const unsigned char *buf2, const detail::String &str2, SharedExpression expr2,
			const size_t nrBytes, const detail::String &str3, SharedExpression expr3,
			bool ok) const;

		const char* GetTextBefore2() const
		{ return " == "; }
		const char* GetTextBefore3() const
		{ return " ("; }
		const char* GetTextAfter3() const
		{ return " bytes)"; }
	};
	RICHBOOL_WRAPPER3ARG(EqualData, EqualDataCore)

	struct EqualDataBitwiseCore: public CustomFunctorCore<false>
	{
		template <typename T1, typename T2>
		bool operator()(const T1 *buf1, const T2 *buf2, const size_t nrBytes) const
		{
			return memcmp(buf1, buf2, nrBytes)==0;
		}

		template <typename T1, typename T2>
		Analysis* Analyse(const T1 *buf1, const detail::String &, SharedExpression expr1,
			const T2 *buf2, const detail::String &, SharedExpression expr2,
			const size_t nrBytes, const detail::String &str3, SharedExpression expr3,
			bool ok) const
		{
			return AnalyseBytes(
				(const unsigned char*)buf1, expr1,
				(const unsigned char*)buf2, expr2,
				nrBytes, str3, expr3,
				ok);
		}

		Analysis* AnalyseBytes(const unsigned char *buf1, SharedExpression expr1,
			const unsigned char *buf2, SharedExpression expr2,
			const size_t nrBytes, const detail::String &str3, SharedExpression expr3,
			bool ok) const;

		const char* GetTextBefore2() const
		{ return " == "; }
		const char* GetTextBefore3() const
		{ return " ("; }
		const char* GetTextAfter3() const
		{ return " bytes)"; }
	};
	RICHBOOL_WRAPPER3ARG(EqualDataBitwise, EqualDataBitwiseCore)

	template <class Relation1, class Relation2>
	struct Order3Core: public FunctorCore
	{
		template<typename T1, typename T2, typename T3>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
		{
			Relation1 relation1;
			Relation2 relation2;
			return relation1(t1, t2) && relation2(t2, t3);
		}
		const char* GetTextBefore2() const
		{ return Relation1::name(); }
		const char* GetTextBefore3() const
		{ return Relation2::name(); }
	};
	template <class Relation1, class Relation2,
		class GV1=Value, class GV2=Value, class GV3=Value,
		class Stringize_=MakeString>
	struct Order3: public Wrapper3Arg<Order3Core<Relation1, Relation2>,
	                                      GV1, GV2, GV3, Stringize_>
	{
		Order3(GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3()):
			Wrapper3Arg<Order3Core<Relation1, Relation2>, GV1, GV2, GV3, Stringize_>(gv1, gv2, gv3)
		{}
	};

	template <class Relation1, class Relation2>
	Order3<Relation1, Relation2>
	MakeOrder3(Relation1, Relation2)
	{
		return Order3<Relation1, Relation2>();
	}


	////////////////////////////////////////////////
	// with four arguments

	template <class Core,
		class GV1_=Value,
		class GV2_=Value,
		class GV3_=Value,
		class GV4_=Value,
		class Stringize1_=MakeString,
		class Stringize2_=MakeString,
		class Stringize3_=MakeString,
		class Stringize4_=MakeString>
	class Wrapper4Arg: public Functors::Base
	{
		Core core;
	public:
		typedef GV1_ GV1;
		typedef GV2_ GV2;
		typedef GV3_ GV3;
		typedef GV4_ GV4;
		GV1 getValue1;
		GV2 getValue2;
		GV3 getValue3;
		GV4 getValue4;
		typedef Stringize1_ Stringize1;
		typedef Stringize2_ Stringize2;
		typedef Stringize3_ Stringize3;
		typedef Stringize4_ Stringize4;
		typedef typename Core::Points Points;

		Wrapper4Arg(GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
			getValue1(gv1), getValue2(gv2), getValue3(gv3), getValue4(gv4)
		{}
		Wrapper4Arg(Core cond, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
			core(cond), getValue1(gv1), getValue2(gv2), getValue3(gv3), getValue4(gv4)
		{}

		template<typename T1, typename T2, typename T3, typename T4>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4) const
		{
			return core(getValue1(t1), getValue2(t2), getValue3(t3), getValue4(t4));
		}
		template<typename T1, typename T2, typename T3, typename T4>
		Analysis::State SafeCheck(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4) const
		{
			if (getValue1.BadPtrChain(t1)||getValue2.BadPtrChain(t2)
				||getValue3.BadPtrChain(t3)||getValue4.BadPtrChain(t4))
				return Analysis::BadValue;
			return core(getValue1(t1), getValue2(t2), getValue3(t3), getValue4(t4))
				 ? Analysis::Ok : Analysis::NotOk;
		}
		template<typename T1, typename T2, typename T3, typename T4>
		Points GetPoints(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4) const
		{
			return core.GetPoints(getValue1(t1), getValue2(t2), getValue3(t3), getValue4(t4));
		}
		Points GetGood() const
		{
			return core.GetGood();
		}
		template<typename T1, typename T2, typename T3, typename T4,
			typename Expr1, typename Expr2, typename Expr3, typename Expr4>
		Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4,
			Expr1 expr1, Expr2 expr2,
			Expr3 expr3, Expr4 expr4,
			bool analyseIfSuccess=false, bool negate=false) const
		{
			return Core::GetAnalysis4(core,
				t1, expr1, getValue1, Stringize1(),
				t2, expr2, getValue2, Stringize2(),
				t3, expr3, getValue3, Stringize3(),
				t4, expr4, getValue4, Stringize4(),
				analyseIfSuccess, negate);
		}
		template<typename T1>
		detail::String GetString1(const T1 &t1) const
		{
			return getValue1.ToString(t1, Stringize1());
		}
		template<typename T2>
		detail::String GetString2(const T2 &t2) const
		{
			return getValue2.ToString(t2, Stringize2());
		}
		template<typename T3>
		detail::String GetString3(const T3 &t3) const
		{
			return getValue3.ToString(t3, Stringize3());
		}
		template<typename T4>
		detail::String GetString4(const T4 &t4) const
		{
			return getValue4.ToString(t4, Stringize4());
		}
		template<typename T1>
		bool IsValid1(const T1 &t1) const
		{
			return !getValue1.BadPtrChain(t1);
		}
		template<typename T2>
		bool IsValid2(const T2 &t2) const
		{
			return !getValue2.BadPtrChain(t2);
		}
		template<typename T3>
		bool IsValid3(const T3 &t3) const
		{
			return !getValue3.BadPtrChain(t3);
		}
		template<typename T4>
		bool IsValid4(const T4 &t4) const
		{
			return !getValue4.BadPtrChain(t4);
		}

		Core GetCore() const
		{
			return core;
		}
	};

#define RICHBOOL_WRAPPER4ARG(FUNCTOR, CORE) \
	template <class GV1=RichBool::Value, class GV2=RichBool::Value, class GV3=RichBool::Value, class GV4=RichBool::Value, \
		class Str1_=RichBool::MakeString, class Str2_=RichBool::MakeString, class Str3_=RichBool::MakeString, class Str4_=RichBool::MakeString> \
	struct FUNCTOR: public RichBool::Wrapper4Arg<CORE, GV1, GV2, GV3, GV4, \
			Str1_, Str2_, Str3_, Str4_> { \
		FUNCTOR(GV1 gv1=GV1(), GV2 gv2=GV2(), \
				GV3 gv3=GV3(), GV4 gv4=GV4()): \
			RichBool::Wrapper4Arg<CORE, GV1, GV2, GV3, GV4, Str1_, Str2_, Str3_, Str4_> \
				(gv1, gv2, gv3, gv4) \
		{} \
	};

#define RICHBOOL_WRAPPER4ARG_1CARG(FUNCTOR, CORE, ARG1, VAL1) \
	template <class GV1=RichBool::Value, class GV2=RichBool::Value, class GV3=RichBool::Value, class GV4=RichBool::Value, \
		class Str1_=RichBool::MakeString, class Str2_=RichBool::MakeString, class Str3_=RichBool::MakeString, class Str4_=RichBool::MakeString> \
	struct FUNCTOR: public RichBool::Wrapper4Arg<CORE, GV1, GV2, GV3, GV4, Str1_, Str2_, Str3_, Str4_> { \
		FUNCTOR(ARG1, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()): \
			RichBool::Wrapper4Arg<CORE, GV1, GV2, GV3, GV4, Str1_, Str2_, Str3_, Str4_>(CORE(VAL1), gv1, gv2, gv3, gv4) \
		{} \
	};

	template <typename Pred>
	class Pred4Core: public FunctorCore
	{
		Pred pred;
	public:
		Pred4Core() {}
		Pred4Core(const Pred &pred_): pred(pred_) {}
		Pred4Core(const Pred4Core &pred_): pred(pred_.pred) {}

		template<typename T1, typename T2, typename T3, typename T4>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4) const
		{
			return pred(t1, t2, t3, t4);
		}

		const char* GetTextBefore1() const
		{
			return "predicate(";
		}
		const char* GetTextBefore2() const
		{
			return ", ";
		}
		const char* GetTextBefore3() const
		{
			return ", ";
		}
		const char* GetTextBefore4() const
		{
			return ", ";
		}
		const char* GetTextAfter4() const
		{
			return ")";
		}
	};

	template <class Pred,
		class GV1=Value, class GV2=Value, class GV3=Value, class GV4=Value,
		class Stringize1=MakeString, class Stringize2=MakeString,
		class Stringize3=MakeString, class Stringize4=MakeString>
	struct Pred4: public Wrapper4Arg<Pred4Core<Pred>,
		GV1, GV2, GV3, GV4,
		Stringize1, Stringize2, Stringize3, Stringize4>
	{
		Pred4(GV1 gv1=GV1(), GV2 gv2=GV2(),
			GV3 gv3=GV3(), GV4 gv4=GV4()):
			Wrapper4Arg<Pred4Core<Pred>,
				GV1, GV2, GV3, GV4,
				Stringize1, Stringize2, Stringize3, Stringize4>
				(gv1, gv2, gv3, gv4)
		{}
		Pred4(const Pred &pred, GV1 gv1=GV1(), GV2 gv2=GV2(),
			GV3 gv3=GV3(), GV4 gv4=GV4()):
			Wrapper4Arg<Pred4Core<Pred>,
				GV1, GV2, GV3, GV4,
				Stringize1, Stringize2, Stringize3, Stringize4>
				(pred, gv1, gv2, gv3, gv4)
		{}
	};

	template<class Pred, class GV1_, class GV2_, class GV3_, class GV4_,
		class Stringize1, class Stringize2, class Stringize3, class Stringize4>
	Pred4<Pred, GV1_, GV2_, GV3_, GV4_,
		Stringize1, Stringize2, Stringize3, Stringize4>
	PredToRichBool_4Arg(const Pred &pred,
		GV1_, GV2_,
		GV3_, GV4_,
		Stringize1, Stringize2,
		Stringize3, Stringize4)
	{
		return Pred4<Pred, GV1_, GV2_, GV3_, GV4_,
			Stringize1, Stringize2, Stringize3, Stringize4>(pred);
	}


	template <class Relation1, class Relation2, class Relation3>
	struct Order4Core: public FunctorCore
	{
		template<typename T1, typename T2, typename T3, typename T4>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4) const
		{
			Relation1 relation1;
			Relation2 relation2;
			Relation3 relation3;
			return relation1(t1, t2) && relation2(t2, t3) && relation3(t3, t4);
		}
		const char* GetTextBefore2() const
		{ return Relation1::name(); }
		const char* GetTextBefore3() const
		{ return Relation2::name(); }
		const char* GetTextBefore4() const
		{ return Relation3::name(); }
	};
	template <class Relation1, class Relation2, class Relation3,
		class GV1=Value, class GV2=Value, class GV3=Value, class GV4=Value,
		class Stringize_=MakeString>
	struct Order4: public Wrapper4Arg<Order4Core<Relation1, Relation2, Relation3>,
	                                      GV1, GV2, GV3, GV4,
										  Stringize_>
	{
		Order4(GV1 gv1=GV1(), GV2 gv2=GV2(),
			GV3 gv3=GV3(), GV4 gv4=GV4()):
			Wrapper4Arg<Order4Core<Relation1, Relation2, Relation3>,
				GV1, GV2, GV3, GV4,
				Stringize_, Stringize_, Stringize_, Stringize_>
				(gv1, gv2, gv3, gv4)
		{}
	};

	template <class Relation1, class Relation2, class Relation3>
	Order4<Relation1, Relation2, Relation3>
	MakeOrder4(Relation1, Relation2, Relation3)
	{
		return Order4<Relation1, Relation2, Relation3>();
	}

	template <class Relation1, class Relation2>
	struct Order3NearCore: public FunctorCore
	{
		Relation1 relation1;
		Relation2 relation2;
		template<typename T1, typename T2, typename T3, typename T4>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &err) const
		{
			return relation1(t1, t2, err) && relation2(t2, t3, err);
		}
		const char* GetTextBefore2() const
		{ return Relation1::name(); }
		const char* GetTextBefore3() const
		{ return Relation2::name(); }
		const char* GetTextBefore4() const
		{ return " (difference up to "; }
		const char* GetTextAfter4() const
		{ return " allowed)"; }
	};
	template <class Relation1, class Relation2, class GV1=Value, class GV2=Value,
		class GV3=Value, class GV4=Value, class Stringize_=MakeString>
	struct Order3Near: public Wrapper4Arg<Order3NearCore<Relation1, Relation2>,
		GV1, GV2, GV3, GV4, Stringize_>
	{
		Order3Near(GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
			Wrapper4Arg<Order3NearCore<Relation1, Relation2>, GV1, GV2, GV3, GV4, Stringize_>(gv1, gv2, gv3, gv4)
		{}
	};

	template <class Relation1, class Relation2>
	Order3Near<Relation1, Relation2>
	MakeOrder3Near(Relation1, Relation2)
	{
		return Order3Near<Relation1, Relation2>();
	}

	struct InIntervalNearCore: public FunctorCore
	{
		template<typename T1, typename T2, typename T3, typename T4>
		bool operator()(const T1 &val, const T2 &low, const T3 &high, const T4 &err) const
		{
			return !((val+err)<low) && !((high+err)<val);
		}
		const char* GetTextBefore2() const
		{ return " in ["; }
		const char* GetTextBefore3() const
		{ return ", "; }
		const char* GetTextAfter3() const
		{ return "]"; }
		const char* GetTextBefore4() const
		{ return " (difference up to "; }
		const char* GetTextAfter4() const
		{ return " allowed)"; }
	};
	RICHBOOL_WRAPPER4ARG(InIntervalNear, InIntervalNearCore)

	template <class Relation1, class Relation2>
	struct Order3RelativeNearCore: public FunctorCore
	{
		Relation1 relation1;
		Relation2 relation2;
		template<typename T1, typename T2, typename T3, typename T4>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &err) const
		{
			return relation1(t1, t2, err) && relation2(t2, t3, err);
		}
		const char* GetTextBefore2() const
		{ return Relation1::name(); }
		const char* GetTextBefore3() const
		{ return Relation2::name(); }
		const char* GetTextBefore4() const
		{ return " (relative difference up to "; }
		const char* GetTextAfter4() const
		{ return " allowed)"; }
	};
	template <class Relation1, class Relation2, class GV1=Value, class GV2=Value,
		class GV3=Value, class GV4=Value, class Stringize_=MakeString>
	struct Order3RelativeNear: public Wrapper4Arg<Order3RelativeNearCore<Relation1, Relation2>,
		GV1, GV2, GV3, GV4, Stringize_>
	{
		Order3RelativeNear(GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
			Wrapper4Arg<Order3RelativeNearCore<Relation1, Relation2>, GV1, GV2, GV3, GV4, Stringize_>(gv1, gv2, gv3, gv4)
		{}
	};

	template <class Relation1, class Relation2>
	Order3RelativeNear<Relation1, Relation2>
	MakeOrder3RelativeNear(Relation1, Relation2)
	{
		return Order3RelativeNear<Relation1, Relation2>();
	}

	struct InIntervalRelativeNearCore: public FunctorCore
	{
		template<typename T1, typename T2, typename T3, typename T4>
		bool operator()(const T1 &val, const T2 &low, const T3 &high, const T4 &err) const
		{
			LessRelativeNear<> lrn;
			return lrn(low,val,err) && lrn(val,high,err);
		}
		const char* GetTextBefore2() const
		{ return " in ["; }
		const char* GetTextBefore3() const
		{ return ", "; }
		const char* GetTextAfter3() const
		{ return "]"; }
		const char* GetTextBefore4() const
		{ return " (relative difference up to "; }
		const char* GetTextAfter4() const
		{ return " allowed)"; }
	};
	RICHBOOL_WRAPPER4ARG(InIntervalRelativeNear, InIntervalRelativeNearCore)


	////////////////////////////////////////////////
	// with five arguments

	template <class Core,
		class GV1_=Value, class GV2_=Value,
		class GV3_=Value, class GV4_=Value,
		class GV5_=Value,
		class Stringize1_=MakeString, class Stringize2_=MakeString,
		class Stringize3_=MakeString, class Stringize4_=MakeString,
		class Stringize5_=MakeString>
	class Wrapper5Arg: public Functors::Base
	{
		Core core;
	public:
		typedef GV1_ GV1;
		typedef GV2_ GV2;
		typedef GV3_ GV3;
		typedef GV4_ GV4;
		typedef GV5_ GV5;
		GV1 getValue1;
		GV2 getValue2;
		GV3 getValue3;
		GV4 getValue4;
		GV5 getValue5;
		typedef Stringize1_ Stringize1;
		typedef Stringize2_ Stringize2;
		typedef Stringize3_ Stringize3;
		typedef Stringize4_ Stringize4;
		typedef Stringize5_ Stringize5;
		typedef typename Core::Points Points;

		Wrapper5Arg(GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4(), GV5 gv5=GV5()):
			getValue1(gv1), getValue2(gv2), getValue3(gv3), getValue4(gv4), getValue5(gv5)
		{}
		Wrapper5Arg(Core cond, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4(), GV5 gv5=GV5()):
			core(cond), getValue1(gv1), getValue2(gv2), getValue3(gv3), getValue4(gv4), getValue5(gv5)
		{}

		template<typename T1, typename T2, typename T3, typename T4, typename T5>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5) const
		{
			return core(getValue1(t1), getValue2(t2), getValue3(t3), getValue4(t4), getValue5(t5));
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5>
		Analysis::State SafeCheck(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5) const
		{
			if (getValue1.BadPtrChain(t1)||getValue2.BadPtrChain(t2)
				||getValue3.BadPtrChain(t3)||getValue4.BadPtrChain(t4)||getValue5.BadPtrChain(t5))
				return Analysis::BadValue;
			return core(getValue1(t1), getValue2(t2), getValue3(t3), getValue4(t4), getValue5(t5))
				 ? Analysis::Ok : Analysis::NotOk;
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5>
		Points GetPoints(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5) const
		{
			return core.GetPoints(getValue1(t1), getValue2(t2), getValue3(t3), getValue4(t4), getValue5(t5));
		}
		Points GetGood() const
		{
			return core.GetGood();
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5,
			typename Expr1, typename Expr2, typename Expr3, typename Expr4, typename Expr5>
		Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5,
			Expr1 expr1, Expr2 expr2,
			Expr3 expr3, Expr4 expr4, Expr5 expr5,
			bool analyseIfSuccess=false, bool negate=false) const
		{
			return Core::GetAnalysis5(core,
				t1, expr1, getValue1, Stringize1(),
				t2, expr2, getValue2, Stringize2(),
				t3, expr3, getValue3, Stringize3(),
				t4, expr4, getValue4, Stringize4(),
				t5, expr5, getValue5, Stringize5(),
				analyseIfSuccess, negate);
		}
		template<typename T1>
		detail::String GetString1(const T1 &t1) const
		{
			return getValue1.ToString(t1, Stringize1());
		}
		template<typename T2>
		detail::String GetString2(const T2 &t2) const
		{
			return getValue2.ToString(t2, Stringize2());
		}
		template<typename T3>
		detail::String GetString3(const T3 &t3) const
		{
			return getValue3.ToString(t3, Stringize3());
		}
		template<typename T4>
		detail::String GetString4(const T4 &t4) const
		{
			return getValue4.ToString(t4, Stringize4());
		}
		template<typename T5>
		detail::String GetString5(const T5 &t5) const
		{
			return getValue4.ToString(t5, Stringize5());
		}
		template<typename T1>
		bool IsValid1(const T1 &t1) const
		{
			return !getValue1.BadPtrChain(t1);
		}
		template<typename T2>
		bool IsValid2(const T2 &t2) const
		{
			return !getValue2.BadPtrChain(t2);
		}
		template<typename T3>
		bool IsValid3(const T3 &t3) const
		{
			return !getValue3.BadPtrChain(t3);
		}
		template<typename T4>
		bool IsValid4(const T4 &t4) const
		{
			return !getValue4.BadPtrChain(t4);
		}
		template<typename T5>
		bool IsValid5(const T5 &t5) const
		{
			return !getValue5.BadPtrChain(t5);
		}

		Core GetCore() const
		{
			return core;
		}
	};

#define RICHBOOL_WRAPPER5ARG(FUNCTOR, CORE) \
	template <class GV1=RichBool::Value, class GV2=RichBool::Value, class GV3=RichBool::Value, class GV4=RichBool::Value, class GV5=RichBool::Value, \
		class Str1_=RichBool::MakeString, class Str2_=RichBool::MakeString, class Str3_=RichBool::MakeString, class Str4_=RichBool::MakeString, class Str5_=RichBool::MakeString> \
	struct FUNCTOR: public RichBool::Wrapper5Arg<CORE, GV1, GV2, GV3, GV4, GV5, \
			Str1_, Str2_, Str3_, Str4_, Str5_> { \
		FUNCTOR(GV1 gv1=GV1(), GV2 gv2=GV2(), \
				GV3 gv3=GV3(), GV4 gv4=GV4(), GV5 gv5=GV5()): \
			RichBool::Wrapper5Arg<CORE, GV1, GV2, GV3, GV4, GV5, \
				Str1_, Str2_, Str3_, Str4_, Str5_> \
				(gv1, gv2, gv3, gv4, gv5) \
		{} \
	};

#define RICHBOOL_WRAPPER5ARG_1CARG(FUNCTOR, CORE, ARG1, VAL1) \
	template <class GV1=RichBool::Value, class GV2=RichBool::Value, class GV3=RichBool::Value, \
		class GV4=RichBool::Value, class GV5=RichBool::Value, \
		class Str1_=RichBool::MakeString, class Str2_=RichBool::MakeString, class Str3_=RichBool::MakeString, \
		class Str4_=RichBool::MakeString, class Str5_=RichBool::MakeString> \
	struct FUNCTOR: public RichBool::Wrapper5Arg<CORE, GV1, GV2, GV3, GV4, GV5, Str1_, Str2_, Str3_, Str4_, Str5_> { \
		FUNCTOR(ARG1, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4(), GV5 gv5=GV5()): \
			RichBool::Wrapper5Arg<CORE, GV1, GV2, GV3, GV4, GV5, Str1_, Str2_, Str3_, Str4_, Str5_>(CORE(VAL1), gv1, gv2, gv3, gv4, gv5) \
		{} \
	};

	template <typename Pred>
	class Pred5Core: public FunctorCore
	{
		Pred pred;
	public:
		Pred5Core() {}
		Pred5Core(const Pred &pred_): pred(pred_) {}
		Pred5Core(const Pred5Core &pred_): pred(pred_.pred) {}

		template<typename T1, typename T2, typename T3, typename T4, typename T5>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5) const
		{
			return pred(t1, t2, t3, t4, t5);
		}

		const char* GetTextBefore1() const
		{
			return "predicate(";
		}
		const char* GetTextBefore2() const
		{
			return ", ";
		}
		const char* GetTextBefore3() const
		{
			return ", ";
		}
		const char* GetTextBefore4() const
		{
			return ", ";
		}
		const char* GetTextBefore5() const
		{
			return ", ";
		}
		const char* GetTextAfter5() const
		{
			return ")";
		}
	};

	template <class Pred,
		class GV1=Value, class GV2=Value, class GV3=Value,
		class GV4=Value, class GV5=Value,
		class Stringize1=MakeString, class Stringize2=MakeString, class Stringize3=MakeString,
		class Stringize4=MakeString, class Stringize5=MakeString>
	struct Pred5: public Wrapper5Arg<Pred5Core<Pred>,
		GV1, GV2, GV3, GV4, GV5,
		Stringize1, Stringize2, Stringize3, Stringize4, Stringize5>
	{
		Pred5(GV1 gv1=GV1(), GV2 gv2=GV2(),
			GV3 gv3=GV3(), GV4 gv4=GV4(), GV5 gv5=GV5()):
			Wrapper5Arg<Pred5Core<Pred>,
				GV1, GV2, GV3, GV4, GV5,
				Stringize1, Stringize2, Stringize3, Stringize4, Stringize5>
				(gv1, gv2, gv3, gv4, gv5)
		{}
		Pred5(const Pred &pred, GV1 gv1=GV1(), GV2 gv2=GV2(),
			GV3 gv3=GV3(), GV4 gv4=GV4(), GV5 gv5=GV5()):
			Wrapper5Arg<Pred5Core<Pred>,
				GV1, GV2, GV3, GV4, GV5,
				Stringize1, Stringize2, Stringize3, Stringize4, Stringize5>
				(pred, gv1, gv2, gv3, gv4, gv5)
		{}
	};

	template<class Pred, class GV1_, class GV2_, class GV3_,
		class GV4_, class GV5_,
		class Stringize1, class Stringize2, class Stringize3, class Stringize4, class Stringize5>
	Pred5<Pred, GV1_, GV2_, GV3_, GV4_, GV5_,
		Stringize1, Stringize2, Stringize3, Stringize4, Stringize5>
	PredToRichBool_5Arg(const Pred &pred,
		GV1_, GV2_, GV3_, GV4_, GV5_,
		Stringize1, Stringize2, Stringize3, Stringize4, Stringize5)
	{
		return Pred5<Pred, GV1_, GV2_, GV3_, GV4_, GV5_,
			Stringize1, Stringize2, Stringize3, Stringize4, Stringize5>(pred);
	}


	template <class Relation1, class Relation2, class Relation3>
	struct Order4NearCore: public FunctorCore
	{
		Relation1 relation1;
		Relation2 relation2;
		Relation3 relation3;
		template<typename T1, typename T2, typename T3, typename T4, typename T5>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &err) const
		{
			return relation1(t1, t2, err) && relation2(t2, t3, err) &&
				relation3(t3, t4, err);
		}
		const char* GetTextBefore2() const
		{ return Relation1::name(); }
		const char* GetTextBefore3() const
		{ return Relation2::name(); }
		const char* GetTextBefore4() const
		{ return Relation3::name(); }
		const char* GetTextBefore5() const
		{ return " (difference up to "; }
		const char* GetTextAfter5() const
		{ return " allowed)"; }
	};
	template <class Relation1, class Relation2, class Relation3,
		class GV1=Value, class GV2=Value, class GV3=Value,
		class GV4=Value, class GV5=Value, class Stringize_=MakeString>
	struct Order4Near: public Wrapper5Arg<Order4NearCore<Relation1, Relation2, Relation3>,
		GV1, GV2, GV3, GV4, GV5, Stringize_>
	{
		Order4Near(GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4(), GV5 gv5=GV5()):
			Wrapper5Arg<Order4NearCore<Relation1, Relation2, Relation3>, GV1, GV2, GV3, GV4, GV5, Stringize_>(gv1, gv2, gv3, gv4, gv5)
		{}
	};

	template <class Relation1, class Relation2, class Relation3>
	Order4Near<Relation1, Relation2, Relation3>
	MakeOrder4Near(Relation1, Relation2, Relation3)
	{
		return Order4Near<Relation1, Relation2, Relation3>();
	}

	template <class Relation1, class Relation2, class Relation3>
	struct Order4RelativeNearCore: public FunctorCore
	{
		Relation1 relation1;
		Relation2 relation2;
		Relation3 relation3;
		template<typename T1, typename T2, typename T3, typename T4, typename T5>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &err) const
		{
			return relation1(t1, t2, err) && relation2(t2, t3, err) &&
				relation3(t3, t4, err);
		}
		const char* GetTextBefore2() const
		{ return Relation1::name(); }
		const char* GetTextBefore3() const
		{ return Relation2::name(); }
		const char* GetTextBefore4() const
		{ return Relation3::name(); }
		const char* GetTextBefore5() const
		{ return " (relative difference up to "; }
		const char* GetTextAfter5() const
		{ return " allowed)"; }
	};
	template <class Relation1, class Relation2, class Relation3,
		class GV1=Value, class GV2=Value, class GV3=Value,
		class GV4=Value, class GV5=Value, class Stringize_=MakeString>
	struct Order4RelativeNear: public Wrapper5Arg<Order4RelativeNearCore<Relation1, Relation2, Relation3>,
		GV1, GV2, GV3, GV4, GV5, Stringize_>
	{
		Order4RelativeNear(GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4(), GV5 gv5=GV5()):
			Wrapper5Arg<Order4RelativeNearCore<Relation1, Relation2, Relation3>, GV1, GV2, GV3, GV4, GV5, Stringize_>(gv1, gv2, gv3, gv4, gv5)
		{}
	};

	template <class Relation1, class Relation2, class Relation3>
	Order4RelativeNear<Relation1, Relation2, Relation3>
	MakeOrder4RelativeNear(Relation1, Relation2, Relation3)
	{
		return Order4RelativeNear<Relation1, Relation2, Relation3>();
	}


	////////////////////////////////////////////////
	// with six arguments

	template <class Core,
		class GV1_=Value, class GV2_=Value,
		class GV3_=Value, class GV4_=Value,
		class GV5_=Value, class GV6_=Value,
		class Stringize1_=MakeString, class Stringize2_=MakeString,
		class Stringize3_=MakeString, class Stringize4_=MakeString,
		class Stringize5_=MakeString, class Stringize6_=MakeString>
	class Wrapper6Arg: public Functors::Base
	{
		Core core;
	public:
		typedef GV1_ GV1;
		typedef GV2_ GV2;
		typedef GV3_ GV3;
		typedef GV4_ GV4;
		typedef GV5_ GV5;
		typedef GV6_ GV6;
		GV1 getValue1;
		GV2 getValue2;
		GV3 getValue3;
		GV4 getValue4;
		GV5 getValue5;
		GV6 getValue6;
		typedef Stringize1_ Stringize1;
		typedef Stringize2_ Stringize2;
		typedef Stringize3_ Stringize3;
		typedef Stringize4_ Stringize4;
		typedef Stringize5_ Stringize5;
		typedef Stringize6_ Stringize6;
		typedef typename Core::Points Points;

		Wrapper6Arg(GV1 gv1, GV2 gv2, GV3 gv3, GV4 gv4, GV5 gv5, GV6 gv6):
			getValue1(gv1), getValue2(gv2), getValue3(gv3), getValue4(gv4), getValue5(gv5), getValue6(gv6)
		{}
		Wrapper6Arg(Core cond, GV1 gv1, GV2 gv2, GV3 gv3, GV4 gv4, GV5 gv5, GV6 gv6):
			core(cond), getValue1(gv1), getValue2(gv2), getValue3(gv3), getValue4(gv4), getValue5(gv5), getValue6(gv6)
		{}

		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5, const T6 &t6) const
		{
			return core(getValue1(t1), getValue2(t2), getValue3(t3), getValue4(t4), getValue5(t5), getValue6(t6));
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		Analysis::State SafeCheck(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5, const T6 &t6) const
		{
			if (getValue1.BadPtrChain(t1)||getValue2.BadPtrChain(t2)||getValue3.BadPtrChain(t3)
				||getValue4.BadPtrChain(t4)||getValue5.BadPtrChain(t5)||getValue6.BadPtrChain(t6))
				return Analysis::BadValue;
			return core(getValue1(t1), getValue2(t2), getValue3(t3), getValue4(t4), getValue5(t5), getValue6(t6))
				 ? Analysis::Ok : Analysis::NotOk;
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		Points GetPoints(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5, const T6 &t6) const
		{
			return core.GetPoints(getValue1(t1), getValue2(t2), getValue3(t3), getValue4(t4), getValue5(t5), getValue6(t6));
		}
		Points GetGood() const
		{
			return core.GetGood();
		}
		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
			typename Expr1, typename Expr2, typename Expr3, typename Expr4, typename Expr5, typename Expr6>
		Analysis* Analyse(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5, const T6 &t6,
			Expr1 expr1, Expr2 expr2, Expr3 expr3,
			Expr4 expr4, Expr5 expr5, Expr6 expr6,
			bool analyseIfSuccess=false, bool negate=false) const
		{
			return Core::GetAnalysis6(core,
				t1, expr1, getValue1, Stringize1(),
				t2, expr2, getValue2, Stringize2(),
				t3, expr3, getValue3, Stringize3(),
				t4, expr4, getValue4, Stringize4(),
				t5, expr5, getValue5, Stringize5(),
				t6, expr6, getValue6, Stringize6(),
				analyseIfSuccess, negate);
		}
		template<typename T1>
		detail::String GetString1(const T1 &t1) const
		{
			return getValue1.ToString(t1, Stringize1());
		}
		template<typename T2>
		detail::String GetString2(const T2 &t2) const
		{
			return getValue2.ToString(t2, Stringize2());
		}
		template<typename T3>
		detail::String GetString3(const T3 &t3) const
		{
			return getValue3.ToString(t3, Stringize3());
		}
		template<typename T4>
		detail::String GetString4(const T4 &t4) const
		{
			return getValue4.ToString(t4, Stringize4());
		}
		template<typename T5>
		detail::String GetString5(const T5 &t5) const
		{
			return getValue5.ToString(t5, Stringize5());
		}
		template<typename T6>
		detail::String GetString6(const T6 &t6) const
		{
			return getValue6.ToString(t6, Stringize6());
		}
		template<typename T1>
		bool IsValid1(const T1 &t1) const
		{
			return !getValue1.BadPtrChain(t1);
		}
		template<typename T2>
		bool IsValid2(const T2 &t2) const
		{
			return !getValue2.BadPtrChain(t2);
		}
		template<typename T3>
		bool IsValid3(const T3 &t3) const
		{
			return !getValue3.BadPtrChain(t3);
		}
		template<typename T4>
		bool IsValid4(const T4 &t4) const
		{
			return !getValue4.BadPtrChain(t4);
		}
		template<typename T5>
		bool IsValid5(const T5 &t5) const
		{
			return !getValue5.BadPtrChain(t5);
		}
		template<typename T6>
		bool IsValid6(const T6 &t6) const
		{
			return !getValue6.BadPtrChain(t6);
		}

		Core GetCore() const
		{
			return core;
		}
	};

	template <typename Pred>
	class Pred6Core: public FunctorCore
	{
		Pred pred;
	public:
		Pred6Core() {}
		Pred6Core(const Pred &pred_): pred(pred_) {}
		Pred6Core(const Pred6Core &pred_): pred(pred_.pred) {}

		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5, const T6 &t6) const
		{
			return pred(t1, t2, t3, t4, t5, t6);
		}

		const char* GetTextBefore1() const
		{
			return "predicate(";
		}
		const char* GetTextBefore2() const
		{
			return ", ";
		}
		const char* GetTextBefore3() const
		{
			return ", ";
		}
		const char* GetTextBefore4() const
		{
			return ", ";
		}
		const char* GetTextBefore5() const
		{
			return ", ";
		}
		const char* GetTextBefore6() const
		{
			return ", ";
		}
		const char* GetTextAfter6() const
		{
			return ")";
		}
	};

	template <class Pred,
		class GV1=Value, class GV2=Value, class GV3=Value,
		class GV4=Value, class GV5=Value, class GV6=Value,
		class Stringize1=MakeString, class Stringize2=MakeString, class Stringize3=MakeString,
		class Stringize4=MakeString, class Stringize5=MakeString, class Stringize6=MakeString>
	struct Pred6: public Wrapper6Arg<Pred6Core<Pred>,
		GV1, GV2, GV3, GV4, GV5, GV6,
		Stringize1, Stringize2, Stringize3, Stringize4, Stringize5, Stringize6>
	{
		Pred6(GV1 gv1=GV1(), GV2 gv2=GV2(),
			GV3 gv3=GV3(), GV4 gv4=GV4(), GV5 gv5=GV5(), GV6 gv6=GV6()):
			Wrapper6Arg<Pred6Core<Pred>,
				GV1, GV2, GV3, GV4, GV5, GV6,
				Stringize1, Stringize2, Stringize3, Stringize4, Stringize5, Stringize6>
				(gv1, gv2, gv3, gv4, gv5, gv6)
		{}
		Pred6(const Pred &pred, GV1 gv1=GV1(), GV2 gv2=GV2(),
			GV3 gv3=GV3(), GV4 gv4=GV4(), GV5 gv5=GV5(), GV6 gv6=GV6()):
			Wrapper6Arg<Pred6Core<Pred>,
				GV1, GV2, GV3, GV4, GV5, GV6,
				Stringize1, Stringize2, Stringize3, Stringize4, Stringize5, Stringize6>
				(pred, gv1, gv2, gv3, gv4, gv5, gv6)
		{}
	};

	template<class Pred, class GV1_, class GV2_, class GV3_,
		class GV4_, class GV5_, class GV6_,
		class Stringize1, class Stringize2, class Stringize3, class Stringize4, class Stringize5, class Stringize6>
	Pred6<Pred, GV1_, GV2_, GV3_, GV4_, GV5_, GV6_,
		Stringize1, Stringize2, Stringize3, Stringize4, Stringize5, Stringize6>
	PredToRichBool_6Arg(const Pred &pred,
		GV1_, GV2_, GV3_, GV4_, GV5_, GV6_,
		Stringize1, Stringize2, Stringize3, Stringize4, Stringize5, Stringize6)
	{
		return Pred6<Pred, GV1_, GV2_, GV3_, GV4_, GV5_, GV6_,
			Stringize1, Stringize2, Stringize3, Stringize4, Stringize5, Stringize6>(pred);
	}


	///////////////////////////////////////////////////////
	// other functionality

	inline bool XorBool(bool b1, bool b2)
	{
		return b1 ? !b2 : b2;
	}

	RICHBOOL_DLL_API TmpBool OrBothEvaluated(const TmpBool &bool1, const TmpBool &bool2, int level);
	RICHBOOL_DLL_API TmpBool AndBothEvaluated(const TmpBool &bool1, const TmpBool &bool2, int level);
	RICHBOOL_DLL_API TmpBool XorBothEvaluated(const TmpBool &bool1, const TmpBool &bool2, bool analyseIfSuccess);
}

#endif // #ifndef RICH_BOOL_FUNCTORS_H__QM
