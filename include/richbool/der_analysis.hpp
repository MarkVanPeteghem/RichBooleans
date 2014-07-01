//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_DERIVED_ANALYSIS_H__QM
#define RICH_BOOL_DERIVED_ANALYSIS_H__QM

#include "richbool/analysis.hpp"
#include "richbool/bool.hpp"
#include "richbool/expression.hpp"
#include "richbool/finddiff.hpp"
#include <typeinfo>

#if defined(RICHBOOL_USE_WX)
	#include "wx/dynarray.h"
#else
	#include <vector>
#endif

namespace RichBool
{
	// this class helps with exception safety
	class RICHBOOL_DLL_API AutoAnalysis
	{
	public:
		AutoAnalysis(Analysis *analysis): m_analysis(analysis) {}
		~AutoAnalysis() { delete m_analysis; }
		Analysis* Release()
		{
			Analysis *rv = m_analysis;
			m_analysis = 0;
			return rv;
		}
		void Delete()
		{
			delete m_analysis;
			m_analysis = 0;
		}
		operator bool () const { return m_analysis!=0; }

	private:
		Analysis *m_analysis;
	};

	// CombinedAnalysis is used in rich booleans like rbOR and rbAND,
	// when both arguments were evaluated and the analysis failed,
	// so the analysis of both arguments have to be shown.
	class CombinedAnalysis: public Analysis
	{
	public:
		CombinedAnalysis(const Bool &b1, const Bool &b2, const char *comb, bool ok):
			Analysis(ok), bool1(b1), bool2(b2), m_comb(comb)
		{}

		CombinedAnalysis(const Bool &b1, const Bool &b2, const char *comb, State st):
			Analysis(st), bool1(b1), bool2(b2), m_comb(comb)
		{}

		RICHBOOL_DLL_API virtual void StreamOut(detail::OutStream &stream, int indent=0) const;
		RICHBOOL_DLL_API virtual void StreamOutShort(detail::OutStream &stream) const;

		RICHBOOL_DLL_API virtual const detail::String& GetType() const;

		const Bool& GetBool1() const { return bool1; }
		const Bool& GetBool2() const { return bool2; }

	protected:
		Bool bool1, bool2;
		const char *m_comb;

		RICHBOOL_DLL_API virtual bool Equals(const Analysis* analysis) const;

		RICHBOOL_DLL_API void StreamOutShort(detail::OutStream &stream, const Bool &b) const;
		RICHBOOL_DLL_API void StreamOutLong(detail::OutStream &stream, int indent, const Bool &b, int idx) const;
	};

	class OrAnalysis: public CombinedAnalysis
	{
	public:
		OrAnalysis(const Bool &b1, const Bool &b2):
			CombinedAnalysis(b1, b2, "||", b1() || b2())
		{
			Init();
		}
	private:
		RICHBOOL_DLL_API void Init();
	};

	class AndAnalysis: public CombinedAnalysis
	{
	public:
		AndAnalysis(const Bool &b1, const Bool &b2):
			CombinedAnalysis(b1, b2, "&&", b1() && b2())
		{
			Init();
		}
	private:
		RICHBOOL_DLL_API void Init();
	};

	class XorAnalysis: public CombinedAnalysis
	{
	public:
		XorAnalysis(const Bool &b1, const Bool &b2):
			CombinedAnalysis(b1, b2, "^", b1() ^ b2())
		{
			Init();
		}
	private:
		RICHBOOL_DLL_API void Init();
	};


	// This class is a simple way of mingling text with data,
	// to allow loggers to display the text differently than the data
	class GeneralAnalysis: public Analysis
	{
	public:
		RICHBOOL_DLL_API GeneralAnalysis(bool ok);
		RICHBOOL_DLL_API GeneralAnalysis(State s);
		RICHBOOL_DLL_API virtual ~GeneralAnalysis();

		RICHBOOL_DLL_API virtual void StreamOut(detail::OutStream &stream, int indent=0) const;
		RICHBOOL_DLL_API virtual const detail::String& GetType() const;

		class Part
		{
		public:
			enum Type { PlainTextType, ValueType, InvalidValueType,
				ExpressionType, ResultType, OtherAnalysisType, NewLineType, AnythingType };

			Part(): next(0) {}
			RICHBOOL_DLL_API virtual ~Part();
			RICHBOOL_DLL_API virtual Type GetType() const = 0;
			RICHBOOL_DLL_API virtual void StreamOut(detail::OutStream &stream, int indent) const = 0;

			Part *next;

			RICHBOOL_DLL_API bool operator==(const Part &part) const;
			RICHBOOL_DLL_API bool ListEqual(const Part &part) const;
		protected:
			RICHBOOL_DLL_API virtual bool Equals(const Part &part) const = 0;
		};

		class TextualPart: public Part
		{
		public:
			TextualPart(const detail::String &str_, Type type_): str(str_), type(type_) {}
			virtual Type GetType() const { return type; }
			RICHBOOL_DLL_API virtual void StreamOut(detail::OutStream &stream, int indent) const;

			detail::String str;
			Type type;
		protected:
			RICHBOOL_DLL_API virtual bool Equals(const Part &part) const;
		};

		class ExpressionPart: public Part
		{
		public:
			ExpressionPart(SharedExpression expr): expression(expr) {}
			RICHBOOL_DLL_API virtual ~ExpressionPart();
			virtual Type GetType() const { return ExpressionType; }
			RICHBOOL_DLL_API virtual void StreamOut(detail::OutStream &stream, int indent) const;
			SharedExpression GetExpression() const { return expression; }

		protected:
			SharedExpression expression;
			RICHBOOL_DLL_API virtual bool Equals(const Part &part) const;
		};

		class AnalysisPart: public Part
		{
		public:
			AnalysisPart(SharedAnalysis analysis_, bool b): analysis(analysis_), m_short(b) {}
			virtual Type GetType() const { return OtherAnalysisType; }
			RICHBOOL_DLL_API virtual void StreamOut(detail::OutStream &stream, int indent) const;

			const SharedAnalysis analysis;
		protected:
			RICHBOOL_DLL_API virtual bool Equals(const Part &part) const;
			bool m_short;

			AnalysisPart& operator=(const AnalysisPart&) { return *this; }
		};

		class NewLinePart: public Part
		{
		public:
			NewLinePart() {}
			virtual ~NewLinePart() {}
			virtual Type GetType() const { return NewLineType; }
			RICHBOOL_DLL_API virtual void StreamOut(detail::OutStream &stream, int indent) const;
		protected:
			RICHBOOL_DLL_API virtual bool Equals(const Part &part) const;
		};

		class AnythingPart: public Part
		{
		public:
			AnythingPart() {}
			virtual ~AnythingPart() {}
			virtual Type GetType() const { return AnythingType; }
			RICHBOOL_DLL_API virtual void StreamOut(detail::OutStream &stream, int indent) const;
		protected:
			RICHBOOL_DLL_API virtual bool Equals(const Part &part) const;
		};

		RICHBOOL_DLL_API GeneralAnalysis* AddText(const detail::String &str);
		RICHBOOL_DLL_API GeneralAnalysis* PrependText(const detail::String &str);
		RICHBOOL_DLL_API GeneralAnalysis* AddValue(const detail::String &str,
			bool invalid=false);
		RICHBOOL_DLL_API GeneralAnalysis* AddResult(const detail::String &str);
		RICHBOOL_DLL_API ExpressionPart* AddExpression(SharedExpression expr, const char *sz=0);
		RICHBOOL_DLL_API GeneralAnalysis* AddAnalysis(SharedAnalysis analysis, bool keepShort=false);
		RICHBOOL_DLL_API GeneralAnalysis* SetCoreAnalysis(SharedAnalysis analysis, bool keepShort=false);
		RICHBOOL_DLL_API GeneralAnalysis* AddNewLine();
		RICHBOOL_DLL_API GeneralAnalysis* AddAnything();

		RICHBOOL_DLL_API GeneralAnalysis* PrependAnalysis(GeneralAnalysis *ga);

		RICHBOOL_DLL_API static void SetMaximumValueLength(int maxLen);

		GeneralAnalysis* SetEpilogue(const detail::String &str)
		{ epilogue = str; return this; }
		const detail::String& GetEpilogue() const
		{ return epilogue; }

		RICHBOOL_DLL_API const Part* GetFirstPart() const;
		RICHBOOL_DLL_API const Part* GetNextPart(const Part* part) const;

	protected:
		Part *head, *last;
		detail::String epilogue;
		bool hasCoreAnalysis;
		RICHBOOL_DLL_API void AddPart(Part *part);
		RICHBOOL_DLL_API void PrependPart(Part *part);
		RICHBOOL_DLL_API virtual bool Equals(const Analysis* analysis) const;

		static size_t m_maximumValueLength;
	};

	class MakeGeneralAnalysis
	{
	public:
		MakeGeneralAnalysis(bool ok)
		{
			generalAnalysis = new GeneralAnalysis(ok);
		}
		MakeGeneralAnalysis(Analysis::State st)
		{
			generalAnalysis = new GeneralAnalysis(st);
		}
		~MakeGeneralAnalysis()
		{
			delete generalAnalysis;
		}

		void SetState(Analysis::State st)
		{
			generalAnalysis->SetState(st);
		}

		MakeGeneralAnalysis& operator()(const char *text)
		{
			if (text)
				generalAnalysis->AddText(text);
			return *this;
		}

		MakeGeneralAnalysis& operator()(const detail::String &text)
		{
			if (!RichBool::detail::is_empty(text))
				generalAnalysis->AddText(text);
			return *this;
		}

		MakeGeneralAnalysis& result(const detail::String &text)
		{
			generalAnalysis->AddResult(text);
			return *this;
		}

		MakeGeneralAnalysis& expr(SharedExpression expression, const char *sz)
		{
			generalAnalysis->AddExpression(expression, sz);
			return *this;
		}

		MakeGeneralAnalysis& idx(int n, const char *sz)
		{
			generalAnalysis->AddExpression(new IndexExpression(n), sz);
			return *this;
		}

		MakeGeneralAnalysis& expr(const char *expression, const char *sz)
		{
			generalAnalysis->AddExpression(new TextExpression(expression), sz);
			return *this;
		}

		MakeGeneralAnalysis& pexpr(const char *prefix, const char *expression, const char *sz)
		{
			SharedExpression se = new TextExpression(expression);
			generalAnalysis->AddExpression(new PrefixedExpression(prefix, se), sz);
			return *this;
		}

		MakeGeneralAnalysis& operator()()
		{
			generalAnalysis->AddNewLine();
			return *this;
		}

		MakeGeneralAnalysis& Anything()
		{
			generalAnalysis->AddAnything();
			return *this;
		}

		MakeGeneralAnalysis& operator()(SharedAnalysis otherAnalysis, bool keepShort=false)
		{
			generalAnalysis->AddAnalysis(otherAnalysis, keepShort);
			return *this;
		}

		MakeGeneralAnalysis& core(SharedAnalysis otherAnalysis, bool keepShort=false)
		{
			generalAnalysis->SetCoreAnalysis(otherAnalysis, keepShort);
			return *this;
		}

		MakeGeneralAnalysis& operator()(const detail::String &str, bool validPtr)
		{
			generalAnalysis->AddValue(str, !validPtr);
			return *this;
		}

		template<typename T, class GetValue, class Stringize_>
		MakeGeneralAnalysis& operator()(const T &t, GetValue getValue, Stringize_ str)
		{
			if (RICHBOOL_CONST_BOOL(str.showString))
			{
				if (getValue.BadPtrChain(t))
					generalAnalysis->AddValue(getValue.ToString(t, Stringize_()), true);
				else
					generalAnalysis->AddValue(getValue.ToString(t, str));
			}
			return *this;
		}

		MakeGeneralAnalysis& ep(const detail::String &str)
		{
			generalAnalysis->SetEpilogue(str);
			return *this;
		}

		MakeGeneralAnalysis& neg()
		{
			generalAnalysis->Negate();
			return *this;
		}

		operator GeneralAnalysis*()
		{
			GeneralAnalysis *rv = generalAnalysis;
			generalAnalysis = 0;
			return rv;
		}

	private:
		GeneralAnalysis *generalAnalysis;
	};

	// This class is intented for a brief analysis of
	// two sequences (e.g. a string, or a series of bits).
	// The default output has only three lines.
	// Unlike AnalysisOfRange, it does not create a new
	// Analysis derived object per comparison.
	class BriefAnalysisOfTwoSequences: public GeneralAnalysis
	{
	public:
		RICHBOOL_DLL_API BriefAnalysisOfTwoSequences(bool ok, SharedExpression expr1, SharedExpression expr2,
			const char *sz1, const char *sz2, const char *sz3);
		RICHBOOL_DLL_API BriefAnalysisOfTwoSequences(bool ok, SharedExpression expr1, SharedExpression expr2,
			SharedExpression expr3,
			const char *sz1, const char *sz2, const char *sz3, const char *sz4);

		RICHBOOL_DLL_API virtual void StreamOut(detail::OutStream &stream, int indent=0) const;
		RICHBOOL_DLL_API virtual const detail::String& GetType() const;

		const detail::String& GetString1() const { return m_str1; }
		const detail::String& GetString2() const { return m_str2; }
		const detail::String& GetDifferenceString() const { return m_strDiff; }
		SharedExpression GetExpression1() const { return m_expr1; }
		SharedExpression GetExpression2() const { return m_expr2; }
		SharedExpression GetExpression3() const { return m_expr3; }

		void SetString1(const detail::String &str)
		{
			m_str1 = str;
		}

		void SetString2(const detail::String &str)
		{
			m_str2 = str;
		}

		void SetStringDiff(const detail::String &str)
		{
			m_strDiff = str;
		}


		RICHBOOL_DLL_API void SetTitle1(const char *title);
		RICHBOOL_DLL_API void SetTitle2(const char *title);
		RICHBOOL_DLL_API void SetTitleDiff(const char *title);

		RICHBOOL_DLL_API void SetBlockSize(int blockSize);
		int GetBlockSize() const { return m_blockSize; }

		RICHBOOL_DLL_API void SetBlocksPerLine(int blocksPerLine);
		int GetBlocksPerLine() const { return m_blocksPerLine; }

	protected:
		detail::String m_str1, m_str2, m_strDiff;

		SharedExpression m_expr1, m_expr2, m_expr3;

		const char *m_title1, *m_title2, *m_titleDiff;
		int m_blockSize, m_blocksPerLine;

		RICHBOOL_DLL_API void StreamOutPerBlock(detail::OutStream &stream, const detail::String& str,
			size_t b, size_t e) const;
		RICHBOOL_DLL_API virtual bool Equals(const Analysis* analysis) const;
	};

	// This class is used if two ranges are compared, and there
	// is an omission in one of the two ranges. It simply displays
	// the value of the element, and 'X' where the omitted element is
	// (that can be before or after the value of the element).
	class Single: public GeneralAnalysis
	{
	public:
		RICHBOOL_DLL_API Single(int idx, int total, const detail::String &value,
			SharedExpression expr, bool valid);

		virtual char GetCode() const;
		virtual const detail::String& GetType() const;

		const detail::String& GetValue() const { return value; }
		SharedExpression GetExpression() const { return expression; }
		int GetIndex() const { return idx; }
		int GetTotal() const { return total; }
		bool IsValid() const { return valid; }

	protected:
		detail::String value;
		int idx, total;
		bool valid;

		SharedExpression expression;

		void Init(SharedExpression expr);
		virtual bool Equals(const Analysis* analysis) const;
	};

#if defined(RICHBOOL_USE_WX)
	WX_DEFINE_ARRAY_PTR(Analysis*, AnalysisArray);
#else
	typedef std::vector<Analysis*> AnalysisArray;
#endif

	// This class is intended to repeat an analysis on the elements of one
	// or more ranges. A new Analysis derived object is created
	// for every element.
	// The default output has at least one line per element,
	// so its output can be a lot longer than that of
	// BriefAnalysisOfTwoSequences.
	// Unlike BriefAnalysisOfTwoSequences, it isn't restricted
	// to two ranges.
	class AnalysisOfRange: public GeneralAnalysis
	{
	public:
		struct MakeState
		{
			State state;
			MakeState(bool b): state(b?Ok:NotOk) {}
			MakeState(State s): state(s) {}
		};
		AnalysisOfRange(MakeState s, const detail::String &message,
			SharedExpression expr1, SharedExpression expr2);
		AnalysisOfRange(MakeState s, const detail::String &message1,
			SharedExpression expr1, SharedExpression expr2,
			const detail::String &message2);
		AnalysisOfRange(MakeState s, const detail::String &message,
			SharedExpression expr1, SharedExpression expr2,
			SharedExpression expr3, SharedExpression expr4);
		AnalysisOfRange(MakeState s,
			const detail::String &message1,
			SharedExpression expr1, SharedExpression expr2,
			const detail::String &message2,
			SharedExpression expr3, SharedExpression expr4,
			const detail::String &message3);
		virtual ~AnalysisOfRange();
		virtual void StreamOut(detail::OutStream &stream, int indent=0) const;
		virtual const detail::String& GetType() const;

		void Add(Analysis *analysis);

		Analysis* GetAnalysis(size_t idx) const { return m_analysisArray[idx]; }

		void SetMessage(const detail::String &message);

	protected:
		AnalysisArray m_analysisArray;

		void AddSingle(const detail::String &str, int idx, int total,
			SharedExpression expr, bool valid);
		virtual bool Equals(const Analysis* analysis) const;
	};


	// This class is used when part of a condition was not evaluated
	// because of shortcut logic in rbOR or rbAND.
	class RICHBOOL_DLL_API AnalysisNotEvaluated: public Analysis
	{
	public:
		AnalysisNotEvaluated();
		virtual ~AnalysisNotEvaluated();
		virtual void StreamOut(detail::OutStream &stream, int indent=0) const;
		virtual const detail::String& GetType() const;
	protected:
		virtual bool Equals(const Analysis* analysis) const;
	};

	///////////////////////////////////////////////////////
	// classes used to compare strings

	template<typename CharType>
	struct AnalysisOfStringsName
	{};

#ifdef RICHBOOL_USE_WX
	template<>
	struct AnalysisOfStringsName<wxChar>
	{
		static const detail::String name;
	};
#else

	template<>
	struct AnalysisOfStringsName<char>
	{
		static const detail::String name;
	};
#endif

	template<>
	struct AnalysisOfStringsName<wchar_t>
	{
		static const detail::String name;
	};

	template <typename E>
	class BasicAnalysisOfStrings: public GeneralAnalysis
	{
	public:
		typedef typename detail::CharTypeToStringType<E>::StringType StringType;

		BasicAnalysisOfStrings(bool ok, const StringType &str1, const StringType &str2,
				const detail::String &strDiff,
				const char *relation, const detail::String &compare,
				SharedExpression expr1, SharedExpression expr2):
			GeneralAnalysis(ok),
			m_str1(str1),
			m_str2(str2),
			m_strDiff(strDiff)
		{
			Init(m_str1, m_str2, expr1, expr2, relation, compare);
		}

		virtual ~BasicAnalysisOfStrings() {}

		void StreamOutPart(detail::OutStream &stream, int indent, size_t from, size_t to,
			size_t &pos1, size_t &pos2) const
		{
			detail::String strView1("str1: "), strView2("str2: "), strDiff;

			bool hasErrors = false;

			for (size_t pos=from; pos<to; ++pos)
			{
				detail::String esc1, esc2, diff;
				diff = m_strDiff[pos];

				switch (m_strDiff[pos])
				{
				case 'M': // match
				case 'X': // difference
				case ' ': // ignore
					esc1 = detail::EscapeChar(m_str1[pos1]);
					esc2 = detail::EscapeChar(m_str2[pos2]);
					++pos1;
					++pos2;
					switch (m_strDiff[pos])
					{
					case 'M': diff = '.'; break;
					case 'X': diff = 'x'; break;
					case ' ': diff = '.'; break;
					}
					break;
				case 'A': // ignore
				case '1': // one extra in first string
					esc1 = detail::EscapeChar(m_str1[pos1]);
					++pos1;
					if (m_strDiff[pos]=='A')
						diff = '-';
					break;
				case '2': // one extra in second string
					esc2 = detail::EscapeChar(m_str2[pos2]);
					++pos2;
					break;
				}

				if ( (m_strDiff[pos]!='M') && (m_strDiff[pos]!='A') && (m_strDiff[pos]!=' ') )
					hasErrors = true;

				while (detail::str_size(esc1)<detail::str_size(esc2))
					esc1 = ' '+esc1;
				while (detail::str_size(esc2)<detail::str_size(esc1))
					esc2 = ' '+esc2;
				while (detail::str_size(diff)<detail::str_size(esc1))
					diff = ' '+diff;
				strView1 += esc1;
				strView2 += esc2;
				strDiff += diff;
			}

			detail::String spaces;
			for (int i=0; i<indent; ++i)
				spaces += ' ';

			strDiff = (hasErrors ? "diff: " : "same: ") + strDiff;

			detail::Endl(stream);
			stream << spaces << strView1;
			detail::Endl(stream);
			stream << spaces << strDiff;
			detail::Endl(stream);
			stream << spaces << strView2;
		}

		virtual void StreamOut(detail::OutStream &stream, int indent=0) const
		{
			GeneralAnalysis::StreamOut(stream, indent);

			size_t pos1=0, pos2=0;

			const size_t partLength = 40;
			const size_t length = detail::str_size(m_strDiff);
			const size_t nrParts = (length-1)/partLength+1;
			for (size_t part=0; part<nrParts; ++part)
			{
				size_t from = part*partLength, to = (part+1)*partLength;
				if (to>length)
					to = length;
				StreamOutPart(stream, indent, from, to, pos1, pos2);

				if (part<nrParts-1)
					detail::Endl(stream);
			}
		}

		virtual const detail::String& GetType() const
		{
			return AnalysisOfStringsName<E>::name;
		}

		const StringType& GetString1() const { return m_str1; }
		const StringType& GetString2() const { return m_str2; }
		const detail::String& GetDifferenceString() const { return m_strDiff; }

	protected:
		StringType m_str1, m_str2;
		detail::String m_strDiff;

		void Init(const StringType &str1, const StringType &str2,
			SharedExpression expr1, SharedExpression expr2,
			const char *relationName, const detail::String &compareName)
		{
			AddExpression(expr1, ":");
			AddValue(detail::EscapeString(str1), false);
			AddText(relationName);
			AddExpression(expr2, ":");
			AddValue(detail::EscapeString(str2), false);
			AddText(" (");
			AddText(compareName);
			AddText(")");
		}

		virtual bool Equals(const Analysis* analysis_) const
		{
			// equivalence of type is already checked by operator==
			const BasicAnalysisOfStrings<E> *analysisWS =
				(const BasicAnalysisOfStrings<E>*)analysis_;
			bool b1 = m_str1==analysisWS->m_str1;
			bool b2 = m_str2==analysisWS->m_str2;
			bool bd = m_strDiff==analysisWS->m_strDiff;
			bool bg = GeneralAnalysis::Equals(analysis_);
			return b1 && b2 && bd && bg;
		}

		// only for testability:
		BasicAnalysisOfStrings(): GeneralAnalysis(false)
		{}
	};

	template <typename E>
	class BasicAnalysisOfStringsSideBySide: public BasicAnalysisOfStrings<E>
	{
	public:
		BasicAnalysisOfStringsSideBySide(bool ok, const StringType &str1, const StringType &str2,
				const detail::String &strDiff,
				const char *relation, const detail::String &compare,
				SharedExpression expr1, SharedExpression expr2):
			BasicAnalysisOfStrings(ok, str1, str2, strDiff, relation, compare, expr1, expr2)
		{}

		virtual void StreamOut(detail::OutStream &stream, int indent=0) const
		{
			size_t pos1=0, pos2=0;

			detail::String str1, str2, str1Markers, str2Markers;

			for (size_t i=0; i<m_strDiff.size(); ++i)
			{
				switch (m_strDiff[i])
				{
				case 'M':
				case 'X':
				case ' ':
					if (pos1<m_str1.size())
					{
						str1 += detail::EscapeChar(m_str1[pos1++]);
						AdjustLength(str1Markers, str1, m_strDiff[i]!='X' ? ' ' : '^');
					}
					if (pos2<m_str2.size())
					{
						str2 += detail::EscapeChar(m_str2[pos2++]);
						AdjustLength(str2Markers, str2, m_strDiff[i]!='X' ? ' ' : '^');
					}
					break;
				case '1':
					str1 += detail::EscapeChar(m_str1[pos1++]);
					AdjustLength(str1Markers, str1, '^');
					break;
				case '2':
					str2 += detail::EscapeChar(m_str2[pos2++]);
					AdjustLength(str2Markers, str2, '^');
					break;
				}
			}

			stream << str1 << "   " << str2;
			detail::Endl(stream);
			stream << str1Markers << "<->" << str2Markers;
		}

		// only for testability:
		BasicAnalysisOfStringsSideBySide()
		{}

	private:
		static void AdjustLength(detail::String &str, const detail::String &ref, char ch)
		{
			while (str.size()<ref.size())
				str += ch;
		}
	};

	typedef BasicAnalysisOfStrings<char> AnalysisOfStrings;
#if defined(RICHBOOL_HAS_WSTRING)
	typedef BasicAnalysisOfStrings<detail::wchar> AnalysisOfWStrings;
#endif
}

#endif // #ifndef RICH_BOOL_DERIVED_ANALYSIS_H__QM
