//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif
#include "richbool/der_analysis.hpp"

namespace RichBool
{
	void WriteIndent(detail::OutStream &stream, int indent)
	{
		for (int i=0; i<indent; ++i)
			stream << ' ';
	}

	///////////////////////////////////////////////////////////////
	// class CombinedAnalysis

	void CombinedAnalysis::StreamOutShort(detail::OutStream &stream,
		const Bool &b) const
	{
		if (b.GetAnalysis())
			b.GetAnalysis()->StreamOutShort(stream);
		else
			stream << (b() ? "ok" : "nok");
	}

	void CombinedAnalysis::StreamOutLong(detail::OutStream &stream,
		int indent, const Bool &b, int idx) const
	{
		stream << "condition " << idx << ":";
		if (b.GetAnalysis())
		{
			detail::Endl(stream);
			WriteIndent(stream, indent+2);
			b.GetAnalysis()->StreamOut(stream, indent+2);
		}
		else
			stream << (b() ? " ok" : " nok");
	}

	void CombinedAnalysis::StreamOutShort(detail::OutStream &stream) const
	{
		if (m_negated)
		{
			stream << "!";
		}
		stream << '(';

		StreamOutShort(stream, bool1);

		stream << ' ' << m_comb << ' ';

		StreamOutShort(stream, bool2);

		stream << ") " << (GetState()==Ok ? "- ok" : "- nok");
	}

	void CombinedAnalysis::StreamOut(detail::OutStream &stream, int indent) const
	{
		if (m_negated)
		{
			stream << "!(";
			detail::Endl(stream);
		}

		StreamOutLong(stream, indent, bool1, 1);

		detail::Endl(stream);
		stream << m_comb;
		detail::Endl(stream);
		WriteIndent(stream, indent);

		StreamOutLong(stream, indent, bool2, 2);

		if (m_negated)
		{
			detail::Endl(stream);
			stream << ")";
		}
	}

	bool CombinedAnalysis::Equals(const Analysis* analysis) const
	{
		// equivalence of type is already checked by operator==

		const CombinedAnalysis *ci = (const CombinedAnalysis*)analysis;

		return (bool1==ci->bool1) && (bool2==ci->bool2);
	}

	const detail::String& CombinedAnalysis::GetType() const
	{
		static const detail::String type = "combined";
		return type;
	}

#define OK  RichBool::Analysis::Ok
#define NOK RichBool::Analysis::NotOk
#define NE  RichBool::Analysis::NotEvaluated
#define BV  RichBool::Analysis::BadValue

	static RichBool::Analysis::State OrMatrix[4][4] = {
		{ OK,  OK,  OK,  BV },
		{ OK,  NOK, NOK, BV },
		{ OK,  NOK, NE,  BV },
		{ BV,  BV,  BV,  BV }
	};

	void OrAnalysis::Init()
	{
		const State st1 = bool1.GetAnalysis() ? bool1.GetAnalysis()->GetState() :
				(bool1() ? Ok : NotOk),
			st2 = bool2.GetAnalysis() ? bool2.GetAnalysis()->GetState() :
				(bool2() ? Ok : NotOk);
		SetState(OrMatrix[(int)st1][(int)st2]);
	}

	static RichBool::Analysis::State AndMatrix[4][4] = {
		{ OK,  NOK, OK,  BV },
		{ NOK, NOK, NOK, BV },
		{ OK,  NOK, NE,  BV },
		{ BV,  BV,  BV,  BV }
	};

	void AndAnalysis::Init()
	{
		const State st1 = bool1.GetAnalysis() ? bool1.GetAnalysis()->GetState() :
				(bool1() ? Ok : NotOk),
			st2 = bool2.GetAnalysis() ? bool2.GetAnalysis()->GetState() :
				(bool2() ? Ok : NotOk);
		SetState(AndMatrix[(int)st1][(int)st2]);
	}

	static RichBool::Analysis::State XorMatrix[4][4] = {
		{ NOK, OK,  OK,  BV },
		{ OK,  NOK, NOK, BV },
		{ OK,  NOK, OK,  BV },
		{ BV,  BV,  BV,  BV }
	};

	void XorAnalysis::Init()
	{
		const State st1 = bool1.GetAnalysis() ? bool1.GetAnalysis()->GetState() :
				(bool1() ? Ok : NotOk),
			st2 = bool2.GetAnalysis() ? bool2.GetAnalysis()->GetState() :
				(bool2() ? Ok : NotOk);
		SetState(XorMatrix[(int)st1][(int)st2]);
	}

#undef OK
#undef NOK
#undef NE
#undef BV

	///////////////////////////////////////////////////////////////
	// class GeneralAnalysis

	GeneralAnalysis::GeneralAnalysis(bool ok):
		Analysis(ok), head(0), last(0), hasCoreAnalysis(false)
	{}

	GeneralAnalysis::GeneralAnalysis(State s):
		Analysis(s), head(0), last(0), hasCoreAnalysis(false)
	{}

	GeneralAnalysis::~GeneralAnalysis()
	{
		delete head;
	}

	void GeneralAnalysis::StreamOut(detail::OutStream &stream, int indent) const
	{
		if (m_negated)
			stream << "!(";
		for (const Part *part=GetFirstPart(); part; part=GetNextPart(part))
			part->StreamOut(stream, indent);
		if (m_negated)
			stream << ')';

		// if we have a core analysis, the state is that of the core analysis,
		// which is already shown by the core analysis
		if (!hasCoreAnalysis)
			switch (m_state)
			{
			case Ok:
				stream << " - ok";
				break;
			case NotOk:
				stream << " - nok";
				break;
			case NotEvaluated:
				stream << " - ?";
				break;
			case BadValue:
				stream << " - has bad value";
				break;
			}

		if (!detail::is_empty(epilogue))
		{
			detail::Endl(stream);
			stream << epilogue;
		}
	}

	const detail::String& GeneralAnalysis::GetType() const
	{
		static const detail::String type = "general";
		return type;
	}

	GeneralAnalysis* GeneralAnalysis::AddText(const detail::String &str)
	{
		if (!str.empty())
			AddPart(new TextualPart(str, Part::PlainTextType));
		return this;
	}

	GeneralAnalysis* GeneralAnalysis::PrependText(const detail::String &str)
	{
		if (!str.empty())
			PrependPart(new TextualPart(str, Part::PlainTextType));
		return this;
	}

	GeneralAnalysis* GeneralAnalysis::AddValue(const detail::String &str, bool noAnalysis)
	{
		if (str.size()>m_maximumValueLength)
		{
			detail::String reduced(str, 0, m_maximumValueLength);
			reduced += "...";
			AddPart(new TextualPart(reduced, noAnalysis ? Part::InvalidValueType : Part::ValueType));
		}
		else
			AddPart(new TextualPart(str, noAnalysis ? Part::InvalidValueType : Part::ValueType));
		return this;
	}

	GeneralAnalysis* GeneralAnalysis::AddResult(const detail::String &str)
	{
		AddPart(new TextualPart(str, Part::ResultType));
		return this;
	}

	GeneralAnalysis::ExpressionPart* GeneralAnalysis::AddExpression(
		SharedExpression expr,
		const char *sz)
	{
		ExpressionPart *ep=0;
		if (expr)
		{
			AddPart(ep = new ExpressionPart(expr));
			if (sz)
				AddText(sz);
		}
		return ep;
	}

	GeneralAnalysis* GeneralAnalysis::AddAnalysis(SharedAnalysis analysis, bool keepShort)
	{
		AddPart(new AnalysisPart(analysis, keepShort));
		return this;
	}

	GeneralAnalysis* GeneralAnalysis::SetCoreAnalysis(SharedAnalysis analysis, bool keepShort)
	{
		AddPart(new AnalysisPart(analysis, keepShort));
		hasCoreAnalysis = true;
		m_state = analysis->GetState();
		return this;
	}

	GeneralAnalysis* GeneralAnalysis::AddNewLine()
	{
		AddPart(new NewLinePart());
		return this;
	}

	GeneralAnalysis* GeneralAnalysis::AddAnything()
	{
		AddPart(new AnythingPart);
		return this;
	}

	const GeneralAnalysis::Part* GeneralAnalysis::GetFirstPart() const
	{
		return head;
	}

	const GeneralAnalysis::Part* GeneralAnalysis::GetNextPart(const Part* part) const
	{
		return part->next;
	}

	void GeneralAnalysis::AddPart(Part *part)
	{
		if (last)
		{
			last->next = part;
			last = part;
		}
		else
		{
			head = last = part;
		}
	}

	void GeneralAnalysis::PrependPart(Part *part)
	{
		if (head)
		{
			part->next = head;
			head = part;
		}
		else
		{
			head = last = part;
		}
	}

	GeneralAnalysis* GeneralAnalysis::PrependAnalysis(GeneralAnalysis *ga)
	{
		if (ga->head)
		{
			ga->last->next = head;
			head = ga->head;
		}
		return this;
	}

	bool GeneralAnalysis::Equals(const Analysis* analysis) const
	{
		// equivalence of type is already checked by operator==
		const GeneralAnalysis *generalAnalysis = (const GeneralAnalysis*)analysis;

		if ( (head==NULL) && (generalAnalysis->head==NULL) )
			return true;

		if ( (head==NULL) || (generalAnalysis->head==NULL) )
			return false;

		return (epilogue==generalAnalysis->epilogue) &&
			(head->ListEqual(*generalAnalysis->head));
	}

	void GeneralAnalysis::SetMaximumValueLength(int maxLen)
	{
		m_maximumValueLength = maxLen;
	}

	size_t GeneralAnalysis::m_maximumValueLength = 40;



	///////////////////////////////////////////////////////////////
	// class GeneralAnalysis::Part

	GeneralAnalysis::Part::~Part()
	{
		delete next;
	}

	bool GeneralAnalysis::Part::operator==(const GeneralAnalysis::Part &part) const
	{
		if (GetType()==AnythingType || part.GetType()==AnythingType)
			return true;
		if (GetType()!=part.GetType())
			return false;
		return Equals(part);
	}

	bool GeneralAnalysis::Part::ListEqual(const Part &part) const
	{
		if (!(*this==part))
			return false;
		if (next && part.next)
			return next->ListEqual(*part.next);
		if (!next && !part.next)
			return true;
		return false;
	}

	bool GeneralAnalysis::TextualPart::Equals(const Part &part) const
	{
		// equivalence of type is already checked by operator==

		const TextualPart &textualPart = (const TextualPart&)part;
		return (type==textualPart.type) && (str==textualPart.str);
	}

	void GeneralAnalysis::TextualPart::StreamOut(detail::OutStream &stream, int ) const
	{
		switch (type)
		{
		case Part::PlainTextType:
			stream << str;
			break;
		case Part::ValueType:
			stream << '<' << str << '>';
			break;
		case Part::ResultType:
			stream << str;
			break;
		case Part::InvalidValueType:
			stream << '@' << str;
			break;
		case Part::ExpressionType:
		case Part::OtherAnalysisType:
		case Part::NewLineType:
			// handled in other classes derived from Part
			break;
		}
	}

	GeneralAnalysis::ExpressionPart::~ExpressionPart()
	{}

	bool GeneralAnalysis::ExpressionPart::Equals(const Part &part) const
	{
		// equivalence of type is already checked by operator==

		const ExpressionPart &expressionPart = (const ExpressionPart&)part;
		return *expression==*expressionPart.expression;
	}

	void GeneralAnalysis::ExpressionPart::StreamOut(detail::OutStream &stream, int ) const
	{
		detail::String str = *expression;
		stream << str;
	}

	bool GeneralAnalysis::AnalysisPart::Equals(const Part &part) const
	{
		// equivalence of type is already checked by operator==

		const AnalysisPart &analysisPart = (const AnalysisPart&)part;
		return (*analysis==*analysisPart.analysis) && (m_short==analysisPart.m_short);
	}

	void GeneralAnalysis::AnalysisPart::StreamOut(detail::OutStream &stream, int indent) const
	{
		if (m_short)
			analysis->StreamOutShort(stream);
		else
			analysis->StreamOut(stream, indent+2);
	}

	void GeneralAnalysis::NewLinePart::StreamOut(detail::OutStream &stream, int indent) const
	{
		detail::Endl(stream);
		for (int i=0; i<indent; ++i)
			stream << ' ';
	}

	bool GeneralAnalysis::NewLinePart::Equals(const Part &) const
	{
		// equivalence of type is already checked by operator==
		// and two NewLinePart objects are always equal
		return true;
	}

	void GeneralAnalysis::AnythingPart::StreamOut(detail::OutStream &stream, int indent) const
	{
		stream << "*";
	}

	bool GeneralAnalysis::AnythingPart::Equals(const Part &) const
	{
		return true; // should not come here
	}

	///////////////////////////////////////////////////////////////
	// class Single

	Single::Single(int idx_, int total_, const detail::String &value_,
		SharedExpression expr, bool valid_):

		GeneralAnalysis(false), value(value_), idx(idx_), total(total_), valid(valid_),
		expression(0)
	{
		Init(expr);
	}

	void Single::Init(SharedExpression expr)
	{
		for (int i=0; i<total; ++i)
		{
			if (idx!=i)
				AddText(" X ");
			else
			{
				ExpressionPart *ep = AddExpression(expr, ":");
				expression = ep->GetExpression();
				AddValue(value, !valid);
			}
		}
	}

	char Single::GetCode() const
	{
		return static_cast<char>('1'+idx);
	}

	bool Single::Equals(const Analysis* analysis) const
	{
		// equivalence of type is already checked by operator==

		const Single *analysisSE = (const Single*)analysis;

		return (idx==analysisSE->idx) && (total==analysisSE->total)
			&& (value==analysisSE->value) && (valid==analysisSE->valid)
			&& (*expression==*analysisSE->expression);
	}

	const detail::String& Single::GetType() const
	{
		static const detail::String type = "single";
		return type;
	}


	///////////////////////////////////////////////////////////////
	// class AnalysisOfRange

	AnalysisOfRange::AnalysisOfRange(MakeState s, const detail::String &message,
		SharedExpression expr1, SharedExpression expr2):

	GeneralAnalysis(s.state)
	{
		AddText(message);
		AddExpression(expr1);
		if (expr2)
		{
			AddText("-");
			AddExpression(expr2);
		}
	}

	AnalysisOfRange::AnalysisOfRange(MakeState s, const detail::String &message1,
		SharedExpression expr1, SharedExpression expr2,
		const detail::String &message2):

	GeneralAnalysis(s.state)
	{
		AddText(message1);
		AddExpression(expr1);
		if (expr2)
		{
			AddText("-");
			AddExpression(expr2);
		}
		AddText(message2);
	}

	AnalysisOfRange::AnalysisOfRange(MakeState s, const detail::String &message,
		SharedExpression expr1, SharedExpression expr2,
		SharedExpression expr3, SharedExpression expr4):

	GeneralAnalysis(s.state)
	{
		AddText(message);

		if (expr1 && expr3)
		{
			AddExpression(expr1);
			if (expr2)
			{
				AddText("-");
				AddExpression(expr2);
			}

			AddText(" and ");

			AddExpression(expr3);
			if (expr4)
			{
				AddText("-");
				AddExpression(expr4);
			}
		}
	}

	AnalysisOfRange::AnalysisOfRange(MakeState s, const detail::String &message1,
		SharedExpression expr1, SharedExpression expr2,
		const detail::String &message2,
		SharedExpression expr3, SharedExpression expr4,
		const detail::String &message3):

	GeneralAnalysis(s.state)
	{
		if (expr1 && expr3)
		{
			AddText(message1);

			AddExpression(expr1);
			if (expr2)
			{
				AddText("-");
				AddExpression(expr2);
			}

			AddText(message2);

			AddExpression(expr3);
			if (expr4)
			{
				AddText("-");
				AddExpression(expr4);
			}

			AddText(message3);
		}
	}

	AnalysisOfRange::~AnalysisOfRange()
	{
		for (size_t i=0; i<detail::array_size(m_analysisArray); ++i)
 			delete m_analysisArray[i];
	}

	void AnalysisOfRange::StreamOut(detail::OutStream &stream, int indent) const
	{
		GeneralAnalysis::StreamOut(stream, indent);
		for (size_t i=0; i<detail::array_size(m_analysisArray); ++i)
		{
			detail::Endl(stream);
			for (int spaces=0; spaces<indent; ++spaces)
				stream << ' ';
			const Analysis *analysis = m_analysisArray[i];
			if (analysis)
			{
				stream << analysis->GetCode() << ": ";
				analysis->StreamOut(stream, indent+2);
			}
			else
				stream << "M: ok";
		}
	}

	bool AnalysisOfRange::Equals(const Analysis* analysis) const
	{
		// equivalence of type is already checked by operator==
		const AnalysisOfRange *other = (const AnalysisOfRange*)analysis;

		if (!GeneralAnalysis::Equals(other))
			return false;

		// first check that both arrays have the same size
		if (detail::array_size(m_analysisArray)!=detail::array_size(other->m_analysisArray))
			return false;

		// now we are sure that both arrays have the same size
		for (size_t i=0; i<detail::array_size(m_analysisArray); ++i)
		{
			if ( (m_analysisArray[i]==NULL) && (other->m_analysisArray[i]==NULL) )
				continue;

			if ( (m_analysisArray[i]==NULL) || (other->m_analysisArray[i]==NULL) )
				return false;

			if ( !(*m_analysisArray[i] == *other->m_analysisArray[i]) )
				return false;
		}
		return true;
	}

	const detail::String& AnalysisOfRange::GetType() const
	{
		static const detail::String type = "range";
		return type;
	}

	void AnalysisOfRange::Add(Analysis *analysis)
	{
#if defined(RICHBOOL_USE_WX)
		m_analysisArray.Add(analysis);
#else
		m_analysisArray.push_back(analysis);
#endif
	}

	void AnalysisOfRange::AddSingle(const detail::String &str, int idx, int total,
		SharedExpression expr, bool valid)
	{
		Add(new Single(idx, total, str, expr, valid));
	}

	void AnalysisOfRange::SetMessage(const detail::String &message)
	{
		TextualPart *msgPart = (TextualPart*)head;
		msgPart->str = message;
	}


	///////////////////////////////////////////////////////////////
	// class BriefAnalysisOfTwoSequences

	BriefAnalysisOfTwoSequences::BriefAnalysisOfTwoSequences(
		bool ok,
		SharedExpression expr1, SharedExpression expr2,
		const char *sz1, const char *sz2, const char *sz3):

		GeneralAnalysis(ok),
		m_expr1(0), m_expr2(0), m_expr3(0),
		m_title1("1"), m_title2("2"), m_titleDiff("C"),
		m_blockSize(0), m_blocksPerLine(0)
	{
		AddText(sz1);

		ExpressionPart *ep = AddExpression(expr1);
		m_expr1 = ep->GetExpression();

		AddText(sz2);

		ep = AddExpression(expr2);
		m_expr2 = ep->GetExpression();

		AddText(sz3);
	}

	BriefAnalysisOfTwoSequences::BriefAnalysisOfTwoSequences(bool ok,
		SharedExpression expr1, SharedExpression expr2, SharedExpression expr3,
		const char *sz1, const char *sz2, const char *sz3, const char *sz4):

		GeneralAnalysis(ok),
		m_expr1(0), m_expr2(0), m_expr3(0),
		m_title1("1"), m_title2("2"), m_titleDiff("C"),
		m_blockSize(0), m_blocksPerLine(0)
	{
		AddText(sz1);

		ExpressionPart *ep = AddExpression(expr1);
		m_expr1 = ep->GetExpression();

		AddText(sz2);

		ep = AddExpression(expr2);
		m_expr2 = ep->GetExpression();

		AddText(sz3);

		ep = AddExpression(expr3);
		m_expr3 = ep->GetExpression();

		AddText(sz4);
	}

	void BriefAnalysisOfTwoSequences::StreamOut(detail::OutStream &stream, int indent) const
	{
		GeneralAnalysis::StreamOut(stream, indent);

		detail::Endl(stream);

		const size_t nrChars = m_str1.size();
		if (nrChars==0)
			return; // prevent error in calculation below

		if ( (m_blocksPerLine==0) || (m_blockSize==0) )
		{
			WriteIndent(stream, indent);
			stream << m_title1 << ":";
			StreamOutPerBlock(stream, m_str1, 0, m_str1.size());
			detail::Endl(stream);
			WriteIndent(stream, indent);
			stream << m_titleDiff << ":";
			StreamOutPerBlock(stream, m_strDiff, 0, m_strDiff.size());
			detail::Endl(stream);
			WriteIndent(stream, indent);
			stream << m_title2 << ":";
			StreamOutPerBlock(stream, m_str2, 0, m_str2.size());
		}
		else
		{
			const int nrCharsPerLine = m_blockSize*m_blocksPerLine;
			const size_t nrLines = (nrChars-1)/nrCharsPerLine+1;
			for (size_t line=0; line<nrLines; ++line)
			{
				const size_t b = line*nrCharsPerLine,
					e = (line+1)*nrCharsPerLine;

				stream << m_title1 << ":";
				StreamOutPerBlock(stream, m_str1, b, e);
				detail::Endl(stream);

				stream << m_titleDiff << ":";
				StreamOutPerBlock(stream, m_strDiff, b, e);
				detail::Endl(stream);

				stream << m_title2 << ":";
				StreamOutPerBlock(stream, m_str2, b, e);
				detail::Endl(stream);

				if (line+1<nrLines)
					detail::Endl(stream);
			}
		}
	}

	void BriefAnalysisOfTwoSequences::StreamOutPerBlock(detail::OutStream &stream,
		const detail::String& str,
		size_t b, size_t e) const
	{
		for (size_t i=b; (i<str.size()) && (i<e); ++i)
		{
			if ( (i==0) || (m_blockSize && (i%m_blockSize==0) ) )
				stream << ' ';
			stream << str[i];
		}
	}

	bool BriefAnalysisOfTwoSequences::Equals(const Analysis* analysis) const
	{
		// equivalence of type is already checked by operator==

		const BriefAnalysisOfTwoSequences *ts =
			(const BriefAnalysisOfTwoSequences*)analysis;
		bool str1Equal = m_str1==ts->m_str1;
		bool str2Equal = m_str2==ts->m_str2;
		bool strDiffEqual = m_strDiff==ts->m_strDiff;
		bool title1Equal = strcmp(m_title1, ts->m_title1)==0;
		bool title2Equal = strcmp(m_title2, ts->m_title2)==0;
		bool titleDiffEqual = strcmp(m_titleDiff, ts->m_titleDiff)==0;
		bool expr1Equal = *m_expr1==*ts->m_expr1;
		bool expr2Equal = *m_expr2==*ts->m_expr2;
		bool bsEqual = m_blockSize==ts->m_blockSize;
		bool bplEqual = m_blocksPerLine==ts->m_blocksPerLine;

		return str1Equal && str2Equal && strDiffEqual &&
			title1Equal && title2Equal && titleDiffEqual &&
			expr1Equal && expr2Equal && bsEqual && bplEqual;
	}

	const detail::String& BriefAnalysisOfTwoSequences::GetType() const
	{
		static const detail::String type = "two sequences";
		return type;
	}

	void BriefAnalysisOfTwoSequences::SetTitle1(const char *title)
	{
		m_title1 = title;
	}

	void BriefAnalysisOfTwoSequences::SetTitle2(const char *title)
	{
		m_title2 = title;
	}

	void BriefAnalysisOfTwoSequences::SetTitleDiff(const char *title)
	{
		m_titleDiff = title;
	}

	void BriefAnalysisOfTwoSequences::SetBlockSize(int blockSize)
	{
		m_blockSize = blockSize;
	}

	void BriefAnalysisOfTwoSequences::SetBlocksPerLine(int blocksPerLine)
	{
		m_blocksPerLine = blocksPerLine;
	}


	///////////////////////////////////////////////////////////////
	// class AnalysisNotEvaluated

	AnalysisNotEvaluated::AnalysisNotEvaluated(): Analysis(NotEvaluated)
	{}

	AnalysisNotEvaluated::~AnalysisNotEvaluated()
	{}

	void AnalysisNotEvaluated::StreamOut(detail::OutStream &stream, int ) const
	{
		stream << "not evaluated";
	}

	bool AnalysisNotEvaluated::Equals(const Analysis*) const
	{
		// equivalence of type is already checked by operator==
		// and two AnalysisNotEvaluated objects are always equal
		return true;
	}

	const detail::String& AnalysisNotEvaluated::GetType() const
	{
		static const detail::String type = "not evaluated";
		return type;
	}


#if defined(RICHBOOL_USE_WX)
	const detail::String AnalysisOfStringsName<wxChar>::name =  "wxStrings";
#else
	const detail::String AnalysisOfStringsName<char>::name =  "strings";
#endif
	const detail::String AnalysisOfStringsName<wchar_t>::name =  "wstrings";
}
