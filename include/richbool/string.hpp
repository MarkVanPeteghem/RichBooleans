//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICHBOOL_STRING_H__QM
#define RICHBOOL_STRING_H__QM

#include "richbool/functors.hpp"

// This headerfile contains functionality for comparing strings.
// It is implemented here for const char pointers, but
// it can be extended to use any type of string.
// In other files this is done for std::string, the wxString class
// from wxWidgets and the CString from MFC.

namespace RichBool
{
	namespace detail
	{
		/////////////////////////////////////////////////////////////////
		// helper function for string comparisons

		template <class T>
		inline bool IsValidString(const T &)
		{
			return true;
		}

		inline bool IsValidString(const char* sz)
		{
			return !BadPtr(sz);
		}

		inline bool IsValidString(const wchar* sz)
		{
			return !BadPtr(sz);
		}
	}

	struct GetStringValue: public Value
	{
		template<typename T>
		bool BadPtrChain(const T &t) const
		{
			return BadPtr(&t) || !detail::IsValidString(t);
		}
	};


	template<typename StringType>
	class StringRange
	{
	public:
		typedef typename StringType::const_iterator iterator;
		typedef size_t IndexType;

		StringRange(const StringType &str): m_end(str.end()) {}

		iterator begin(const StringType &str) const
		{
			return str.begin();
		}

		bool operator()(iterator it) const
		{
			return it!=m_end;
		}

		bool operator()(iterator it, size_t) const
		{
			return it!=m_end;
		}
	private:
		iterator m_end;
	};

	template<>
	class StringRange<char *>
	{
	public:
		typedef char* iterator;
		typedef size_t IndexType;

		StringRange(char *) {}

		iterator begin(char *sz) const { return sz; }
		bool operator()(char *ch) const { return *ch!=0; }
		bool operator()(char *ch, size_t) const { return *ch!=0; }
	};

	template<>
	class StringRange<const char *>
	{
	public:
		typedef const char* iterator;
		typedef size_t IndexType;

		StringRange(const char *) {}

		iterator begin(const char *sz) const { return sz; }
		bool operator()(const char *ch) const { return *ch!=0; }
		bool operator()(const char *ch, size_t) const { return *ch!=0; }
	};

	template<>
	class StringRange<detail::wchar *>
	{
	public:
		typedef detail::wchar* iterator;
		typedef size_t IndexType;

		StringRange(detail::wchar *) {}

		iterator begin(detail::wchar *sz) const { return sz; }
		bool operator()(detail::wchar *ch) const { return *ch!=0; }
		bool operator()(detail::wchar *ch, size_t) const { return *ch!=0; }
	};

	template<>
	class StringRange<const detail::wchar *>
	{
	public:
		typedef const detail::wchar* iterator;
		typedef size_t IndexType;

		StringRange(const detail::wchar *) {}

		iterator begin(const detail::wchar *sz) const { return sz; }
		bool operator()(const detail::wchar *ch) const { return *ch!=0; }
		bool operator()(const detail::wchar *ch, size_t) const { return *ch!=0; }
	};

	inline StringRange<char*> MakeStringRange(char *sz)
	{
		return StringRange<char*>(sz);
	}

	inline StringRange<const char*> MakeStringRange(const char *sz)
	{
		return StringRange<const char*>(sz);
	}

	inline StringRange<detail::wchar*> MakeStringRange(detail::wchar *sz)
	{
		return StringRange<detail::wchar*>(sz);
	}

	inline StringRange<const detail::wchar*> MakeStringRange(const detail::wchar *sz)
	{
		return StringRange<const detail::wchar*>(sz);
	}

	template<typename T>
	inline StringRange<T> MakeStringRange(const T &t)
	{
		return StringRange<T>(t);
	}

	namespace detail
	{
		template <class Relation, class CharCompareType>
		struct Adapter
		{
	#if defined(_MSC_VER) && (_MSC_VER <= 1300)
			Adapter(Relation op_, const CharCompareType &comp_): comp(comp_), op(op_) {}
			const CharCompareType &comp;
	#else
			Adapter(Relation op_, CharCompareType comp_): comp(comp_), op(op_) {}
			CharCompareType comp;
	#endif
			Relation op;

			template<typename E>
			bool operator()(E ch1, E ch2) const
			{
				return op(comp(ch1, ch2));
			}
			template<typename E>
			Analysis::State SafeCheck(E ch1, E ch2) const
			{
				return op(comp(ch1, ch2)) ? Analysis::Ok : Analysis::NotOk;
			}
			template<typename E>
			bool IsValid1(E ) const { return true; }
			template<typename E>
			bool IsValid2(E ) const { return true; }
		};

		template <class Relation, class CharCompareType>
		struct AdapterNotEqual
		{
	#if defined(_MSC_VER) && (_MSC_VER <= 1300)
			AdapterNotEqual(Relation op_, const CharCompareType &comp_): op(op_), comp(comp_) {}
			const CharCompareType &comp;
	#else
			AdapterNotEqual(Relation op_, CharCompareType comp_): op(op_), comp(comp_) {}
			CharCompareType comp;
	#endif
			Relation op;

			template<typename E>
			bool operator()(E ch1, E ch2) const
			{
				int cmp = comp(ch1, ch2);
				return (cmp==0) || op(cmp);
			}
			template<typename E>
			Analysis::State SafeCheck(E ch1, E ch2) const
			{
				return operator()(ch1, ch2) ? Analysis::Ok : Analysis::NotOk;
			}
			template<typename E>
			bool IsValid1(E ) const { return true; }
			template<typename E>
			bool IsValid2(E ) const { return true; }
		};

		struct Equality
		{
			template <class StringType1, class StringType2,
				class StringRange1, class StringRange2,
				class Relation, class CharCompareType>
			static void GetDiff(const StringType1 &str1, const StringType2 &str2,
				StringRange1 range1, StringRange2 range2,
				Relation relation, CharCompareType comp,
				detail::String &strDiff)
			{
				detail::FindDifferences<bool>::FindDifference(
					range1.begin(str1), range1,
					range2.begin(str2), range2,
					strDiff, Adapter<Relation, CharCompareType>(relation, comp));
			}
		};

		template <bool equality, bool continueAfterConflict>
		struct A {};

		template <> struct A<true, true>: public Equality
		{};

		template <> struct A<true, false>: public Equality
		{};

		template <>
		struct A<false, true>
		{
			template <class StringType1, class StringType2,
				class StringRange1, class StringRange2,
				class Relation, class CharCompareType>
			static void GetDiff(const StringType1 &str1, const StringType2 &str2,
				StringRange1 range1, StringRange2 range2,
				Relation relation, CharCompareType comp,
				detail::String &strDiff)
			{
				detail::FindDifferences<bool>::FindDifference(
					range1.begin(str1), range1,
					range2.begin(str2), range2,
					strDiff, AdapterNotEqual<Relation, CharCompareType>(relation, comp));
			}
		};
		template <>
		struct A<false, false>
		{
			template <class StringType1, class StringType2,
				class StringRange1, class StringRange2,
				class Relation, class CharCompareType>
			static void GetDiff(const StringType1 &str1, const StringType2 &str2,
				StringRange1 range1, StringRange2 range2,
				Relation relation, CharCompareType comp,
				detail::String &strDiff)
			{
				typename StringRange1::iterator it1=range1.begin(str1);
				typename StringRange2::iterator it2=range2.begin(str2);

				bool mismatch = false;
				for (; range1(it1) && range2(it2); ++it1, ++it2)
				{
					if (mismatch)
						strDiff += ' ';
					else
					{
						int rv = comp(*it1, *it2);
						if (rv==0)
							strDiff += 'M';
						else
						{
							strDiff += relation(rv) ? '+' : 'X';
							mismatch = true;
						}
					}
				}
				for (; range1(it1); ++it1)
					strDiff += '1';
				for (; range2(it2); ++it2)
					strDiff += '2';
			}
		};
	}

	namespace detail
	{
		template <class Relation>
		struct DeterminePoints
		{
			typedef bool Points;
		};

		template <>
		struct DeterminePoints<EqualRelation>
		{
			typedef unsigned short Points;
		};
	}

	template <class CharCompareType, class Relation=EqualRelation>
	class CompareCompletely
	{
		CharCompareType comp;
		Relation relation;

	public:
		typedef typename CharCompareType::CharType CharType;
		typedef typename detail::CharTypeToStringType<CharType>::StringType StringType;
		typedef typename detail::DeterminePoints<EqualRelation>::Points Points;

		CompareCompletely(CharCompareType comp_=CharCompareType(), Relation op_=Relation()):
			comp(comp_), relation(op_)
		{}

		template <typename StringType1, typename StringType2>
		bool operator()(const StringType1 &str1, const StringType2 &str2) const
		{
			return relation(comp(str1, str2));
		}

		const char* name1() const { return relation.name(); }
		const detail::String& name2() const { return comp.name(); }

		template <class StringType1, class StringType2>
		detail::String GetDiff(const StringType1 &str1, const StringType2 &str2) const
		{
			return GetDiff_(str1, str2,
				MakeStringRange(str1), MakeStringRange(str2));
		}

		template<typename Str_>
		static StringType ToDefaultString(const Str_ &str)
		{
			return CharCompareType::ToDefaultString(str);
		}

	private:
		template <class StringType1, class StringType2,
			class StringRange1, class StringRange2>
		detail::String GetDiff_(const StringType1 &str1, const StringType2 &str2,
			StringRange1 range1, StringRange2 range2) const
		{
			detail::String strDiff;
			detail::A<Relation::equality, CharCompareType::ContinueAfterConflict>::
				GetDiff(str1, str2, range1, range2, relation, comp, strDiff);
			return strDiff;
		}
	};


	/////////////////////////////////////////////////////////////////
	// class for checking if a string begins with a certain string

	template <class CharCompareType>
	class StringBeginsWith
	{
		CharCompareType comp;
	public:
		typedef typename CharCompareType::CharType CharType;
		typedef typename detail::CharTypeToStringType<CharType>::StringType StringType;
		typedef typename detail::DeterminePoints<EqualRelation>::Points Points;

		StringBeginsWith(CharCompareType comp_=CharCompareType()):
			comp(comp_)
		{}

		template <typename StringType1, typename StringType2>
		bool operator()(const StringType1 &str1, const StringType2 &str2) const
		{
			return check(str1, str2, MakeStringRange(str1), MakeStringRange(str2));
		}

		template<typename Str_>
		static StringType ToDefaultString(const Str_ &str)
		{
			return CharCompareType::ToDefaultString(str);
		}

		const char* name1() const { return " begins with "; }
		const detail::String& name2() const { return comp.name(); }

		template <class StringType1, class StringType2>
		detail::String GetDiff(const StringType1 &str1, const StringType2 &str2) const
		{
			return GetDiff_(str1, str2, MakeStringRange(str1), MakeStringRange(str2));
		}

	private:
		template <typename StringType1, typename StringType2,
			class StringRange1, class StringRange2>
		bool check(const StringType1 &str1, const StringType2 &str2,
			const StringRange1 &range1, const StringRange2 &range2) const
		{
			typename StringRange1::iterator it1=range1.begin(str1);
			typename StringRange2::iterator it2=range2.begin(str2);
			for (; range1(it1) && range2(it2); ++it1, ++it2)
				if (comp(*it1, *it2)!=0)
					return false;
			return !range2(it2);
		}

		template <typename StringType1, typename StringType2,
			class StringRange1, class StringRange2>
		detail::String GetDiff_(const StringType1 &str1, const StringType2 &str2,
			const StringRange1 &range1, const StringRange2 &range2) const
		{
			detail::String strDiff;
			typename StringRange1::iterator it1=range1.begin(str1);
			typename StringRange2::iterator it2=range2.begin(str2);
			for (; range1(it1) && range2(it2); ++it1, ++it2)
				strDiff += comp(*it1, *it2)==0 ? 'M' : 'X';
			for (; range2(it2); ++it2)
				strDiff += '2';
			for (; range1(it1); ++it1)
				strDiff += 'A';

			return strDiff;
		}
	};


	template <class CharCompareType>
	class StringEndsWith
	{
		CharCompareType comp;
	public:
		typedef typename CharCompareType::CharType CharType;
		typedef typename detail::CharTypeToStringType<CharType>::StringType StringType;
		typedef typename detail::DeterminePoints<EqualRelation>::Points Points;

		StringEndsWith(CharCompareType comp_=CharCompareType()):
			comp(comp_)
		{}

		template <typename StringType1, typename StringType2>
		bool operator()(const StringType1 &str1, const StringType2 &str2) const
		{
			return check(str1, str2, MakeStringRange(str1), MakeStringRange(str2));
		}

		template<typename Str_>
		static StringType ToDefaultString(const Str_ &str)
		{
			return CharCompareType::ToDefaultString(str);
		}

		const char* name1() const { return " ends with "; }
		const detail::String& name2() const { return comp.name(); }

		template <class StringType1, class StringType2>
		detail::String GetDiff(const StringType1 &str1, const StringType2 &str2) const
		{
			return GetDiff_(str1, str2, MakeStringRange(str1), MakeStringRange(str2));
		}

	private:
		template <typename StringType1, typename StringType2,
			class StringRange1, class StringRange2>
		bool check(const StringType1 &str1, const StringType2 &str2,
			const StringRange1 &range1, const StringRange2 &range2) const
		{
			size_t len1=detail::str_size(str1), len2=detail::str_size(str2);
			if (len1<len2)
				return false;
			typename StringRange1::iterator it1=range1.begin(str1)+len1-len2;
			typename StringRange2::iterator it2=range2.begin(str2);
			for (; range1(it1); ++it1, ++it2)
				if (comp(*it1, *it2)!=0)
					return false;
			return true;
		}

		template <typename StringType1, typename StringType2,
			class StringRange1, class StringRange2>
		detail::String GetDiff_(const StringType1 &str1, const StringType2 &str2,
			const StringRange1 &range1, const StringRange2 &range2) const
		{
			detail::String strDiff;
			typename StringRange1::iterator it1=range1.begin(str1);
			typename StringRange2::iterator it2=range2.begin(str2);
			size_t len1=detail::str_size(str1), len2=detail::str_size(str2);
			if (len1<len2)
			{
				size_t i=0;
				for (; i<(len2-len1); ++i)
					strDiff += '2';
				it2 += len2-len1;
				for (; i<len2; ++i, ++it1, ++it2)
					strDiff += comp(*it1, *it2)==0 ? 'M' : 'X';
			}
			else
			{
				size_t i=0;
				for (; i<(len1-len2); ++i)
					strDiff += 'A';
				it1 += len1-len2;
				for (; range1(it1); ++it1, ++it2)
					strDiff += comp(*it1, *it2)==0 ? 'M' : 'X';
			}
			return strDiff;
		}
	};


	/////////////////////////////////////////////////////////////////
	// class for checking if a string begins with a certain string

	template <class CharCompareType>
	class StringContains
	{
		CharCompareType comp;
	public:
		typedef typename CharCompareType::CharType CharType;
		typedef typename detail::CharTypeToStringType<CharType>::StringType StringType;
		typedef typename detail::DeterminePoints<EqualRelation>::Points Points;

		StringContains(CharCompareType comp_=CharCompareType()):
			comp(comp_)
		{}

		template <typename StringType1, typename StringType2>
		bool operator()(const StringType1 &str1, const StringType2 &str2) const
		{
			return check(str1, str2, MakeStringRange(str1), MakeStringRange(str2));
		}

		template<typename Str_>
		static StringType ToDefaultString(const Str_ &str)
		{
			return CharCompareType::ToDefaultString(str);
		}

		const char* name1() const { return " contains "; }
		const detail::String& name2() const { return comp.name(); }

		template <class StringType1, class StringType2>
		detail::String GetDiff(const StringType1 &str1, const StringType2 &str2) const
		{
			return GetDiff_(str1, str2, MakeStringRange(str1), MakeStringRange(str2));
		}

	private:
		template <typename It1, typename It2,
			class StringRange1, class StringRange2>
		bool matches(It1 it1, It2 it2,
			const StringRange1 &range1, const StringRange2 &range2) const
		{
			for (; range1(it1) && range2(it2); ++it1, ++it2)
				if (comp(*it1, *it2)!=0)
					return false;
			return true;
		}

		template <typename StringType1, typename StringType2,
			class StringRange1, class StringRange2>
		bool check(const StringType1 &str1, const StringType2 &str2,
			const StringRange1 &range1, const StringRange2 &range2) const
		{
			typename StringRange1::iterator it1=range1.begin(str1);
			typename StringRange2::iterator it2=range2.begin(str2);
			for (; range1(it1); ++it1)
				if (matches(it1, it2, range1, range2))
					return true;
			return false;
		}

		template <typename It1, typename It2,
			class StringRange1, class StringRange2>
		size_t count_matches(It1 it1, It2 it2,
			const StringRange1 &range1, const StringRange2 &range2) const
		{
			size_t count=0;
			for (; range1(it1) && range2(it2); ++it1, ++it2)
				if (comp(*it1, *it2)==0)
					++count;
			return count;
		}

		template <typename StringType1, typename StringType2,
			class StringRange1, class StringRange2>
		detail::String GetDiff_(const StringType1 &str1, const StringType2 &str2,
			const StringRange1 &range1, const StringRange2 &range2) const
		{
			detail::String strDiff;
			typename StringRange1::iterator it1=range1.begin(str1);
			typename StringRange2::iterator it2=range2.begin(str2);
			size_t best_count=0;
			typename StringRange1::iterator best_pos=it1;

			for (; range1(it1); ++it1)
			{
				size_t count = count_matches(it1, it2, range1, range2);
				if (count>best_count)
				{
					best_pos = it1;
					best_count = count;
				}
			}

			size_t lenBefore = best_pos-range1.begin(str1);
			for (size_t i=0; i<lenBefore; ++i)
				strDiff += 'A';
			for (; range1(best_pos) && range2(it2); ++best_pos, ++it2)
				strDiff += comp(*best_pos, *it2)==0 ? 'M' : 'X';
			for (; range1(best_pos); ++best_pos)
				strDiff += 'A';
			for (; range2(it2); ++it2)
				strDiff += '2';

			return strDiff;
		}
	};


	/////////////////////////////////////////////////////////////////
	// class for doing string comparisons with a relational operator

	template <class CompareType>
	struct CompareStringsCore: public CustomFunctorCore<false>
	{
		CompareType comp;

		typedef typename CompareType::Points Points;
		enum { maxPoints = 100 };

		CompareStringsCore(CompareType comp_=CompareType()):
			comp(comp_)
		{}

		template <typename StringType1, typename StringType2>
		bool operator()(const StringType1 &str1, const StringType2 &str2) const
		{
			return comp(str1, str2);
		}

		template <typename StringType1, typename StringType2>
		Points GetPoints(const StringType1 &str1, const StringType2 &str2) const
		{
			detail::String strDiff = comp.GetDiff(str1, str2);
			return (Points)detail::GetPointsFromDiff(strDiff, maxPoints);
		}

		Points GetGood() const
		{
			return maxPoints;
		}

		template <typename StringType1, typename StringType2>
		Analysis* Analyse(const StringType1 &str1, const detail::String &, SharedExpression expr1,
			const StringType2 &str2, const detail::String &, SharedExpression expr2, bool ok) const
		{
			return MakeAnalysisOfStrings(ok, str1, str2,
				(typename CompareType::CharType*)0,
				expr1, expr2);
		}

		const char* GetTextBefore2() const
		{
			return comp.name1();
		}
		const detail::String GetTextAfter2() const
		{
			return " ("+comp.name2()+")";
		}

	protected:
		template <class StringType1, class StringType2>
		AnalysisOfStrings* MakeAnalysisOfStrings(bool ok,
			const StringType1 &str1,
			const StringType2 &str2,
			const char *,
			SharedExpression expr1, SharedExpression expr2) const
		{
			detail::String strDiff = comp.GetDiff(str1, str2);
			return new AnalysisOfStrings
				(ok, CompareType::ToDefaultString(str1), CompareType::ToDefaultString(str2),
				strDiff, comp.name1(), comp.name2(), expr1, expr2);
		}

#if defined(RICHBOOL_HAS_WSTRING)
		template <class StringType1, class StringType2>
		AnalysisOfWStrings* MakeAnalysisOfStrings(bool ok,
			const StringType1 &str1,
			const StringType2 &str2,
			const detail::wchar *,
			SharedExpression expr1, SharedExpression expr2) const
		{
			detail::String strDiff = comp.GetDiff(str1, str2);
			return new AnalysisOfWStrings
				(ok, CompareType::ToDefaultString(str1), CompareType::ToDefaultString(str2),
				strDiff, comp.name1(), comp.name2(), expr1, expr2);
		}
#endif
	};

	template <class CompareType, class GetValue1_=GetStringValue, class GetValue2_=GetStringValue>
	struct CompareStrings:
		public Wrapper2Arg<CompareStringsCore<CompareType>, GetValue1_, GetValue2_>
	{
		CompareStrings(CompareType comp_=CompareType(), GetValue1_ gv1=GetValue1_(), GetValue2_ gv2=GetValue2_()):
			Wrapper2Arg<CompareStringsCore<CompareType>, GetValue1_, GetValue2_>
				(CompareStringsCore<CompareType>(comp_), gv1, gv2)
		{}
	};

	template<class CompareType, class Relation>
	CompareStrings<CompareCompletely<CompareType, Relation>, GetStringValue, GetStringValue>
	MakeCompareStrings(CompareType comp, Relation op)
	{
		return CompareStrings<CompareCompletely<CompareType, Relation>, GetStringValue, GetStringValue>
			(CompareCompletely<CompareType, Relation>(comp, op));
	}

	template<class CompareType>
	CompareStrings<StringBeginsWith<CompareType>, GetStringValue, GetStringValue>
	MakeStringBeginsWith(CompareType comp)
	{
		return CompareStrings<StringBeginsWith<CompareType>, GetStringValue, GetStringValue>
			(comp);
	}

	template<class CompareType>
	CompareStrings<StringEndsWith<CompareType>, GetStringValue, GetStringValue>
	MakeStringEndsWith(CompareType comp)
	{
		return CompareStrings<StringEndsWith<CompareType>, GetStringValue, GetStringValue>
			(comp);
	}

	template<class CompareType>
	CompareStrings<StringContains<CompareType>, GetStringValue, GetStringValue>
	MakeStringContains(CompareType comp)
	{
		return CompareStrings<StringContains<CompareType>, GetStringValue, GetStringValue>
			(comp);
	}


	/////////////////////////////////////////////////////////////
	// classes for comparing null terminated char strings

	template <typename E>
	struct BasicStrcmp
	{};

	template <>
	struct BasicStrcmp<char>
	{
		typedef char CharType;

		static inline char* StringTypeToCharType(const char*)
		{
			return (char*)0;
		}

		static inline detail::String ToDefaultString(const char *sz)
		{
			return sz;
		}

		int operator()(char ch1, char ch2) const
		{
			return ch1==ch2 ? 0 : (ch1<ch2 ? -1 : 1);
		}

		int operator()(const char *sz1, const char *sz2) const
		{
			return strcmp(sz1, sz2);
		}

		const detail::String& name() const;

		enum { ContinueAfterConflict = false };
	};

	typedef BasicStrcmp<char>  Strcmp;

#if defined(RICHBOOL_HAS_WSTRING)
	template <>
	struct BasicStrcmp<detail::wchar>
	{
		typedef detail::wchar CharType;

		static inline detail::wchar* StringTypeToCharType(const detail::wchar*)
		{
			return (detail::wchar*)0;
		}

		static inline const detail::WString ToDefaultString(const detail::wchar *sz)
		{
			return sz;
		}

		int operator()(detail::wchar ch1, detail::wchar ch2) const
		{
			return ch1==ch2 ? 0 : (ch1<ch2 ? -1 : 1);
		}

		int operator()(const detail::wchar *sz1, const detail::wchar *sz2) const
		{
			return wcscmp(sz1, sz2);
		}

		const detail::String& name() const;

		enum { ContinueAfterConflict = false };
	};

	typedef BasicStrcmp<detail::wchar> Wcscmp;
#endif
}

#endif // #ifndef RICHBOOL_STRING_H__QM
