//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_RANGES_H__QM
#define RICH_BOOL_RANGES_H__QM

#include "richbool/der_analysis.hpp"
#include "richbool/findinrange.hpp"
#include "richbool/finddiff.hpp"
#include "richbool/functors.hpp"
#include "richbool/expression.hpp"
#include "richbool/logic.hpp"
#include "richbool/swap.hpp"

#define RICHBOOL_MAKE_FACTORY(CLASS, SUFFIX, CORE, KEYWORD) \
	template<> \
	struct CLASS SUFFIX \
	{ \
		explicit CLASS(bool aeos_=false): aeos(aeos_) {} \
		bool aeos; \
		template <class RB> \
		detail::CORE<RB> KEYWORD(RB rb) \
		{ \
			return detail::CORE<RB>(rb, aeos); \
		} \
		template <class RB> \
		detail::CORE<RB> Tie(RB rb) \
		{ \
			return detail::CORE<RB>(rb, aeos); \
		} \
	};

#define RICHBOOL_SUFFIX_T <true>
#define RICHBOOL_SUFFIX_F <false>
#define RICHBOOL_SUFFIX_TT <true, true>
#define RICHBOOL_SUFFIX_FT <false, true>
#define RICHBOOL_SUFFIX_TF <true, false>
#define RICHBOOL_SUFFIX_FF <false, false>

namespace RichBool
{
	// helper functionality

	namespace detail
	{
		template <typename T, typename U>
		class ConstRange
		{
			T b;
			U e;
		public:
			ConstRange(T begin, U end): b(begin), e(end) {}
			T begin() const { return b; }
			U end() const { return e; }
		};
		template <typename T, typename U>
		ConstRange<T, U> MakeConstRange(const T &begin, const U &end)
		{
			return ConstRange<T, U>(begin, end);
		}
#if !defined (_MSC_VER) || (_MSC_VER>1300)
		template <typename T, typename U>
		ConstRange<const T*, const T*> MakeConstRange(T begin[], const U end)
		{
			return ConstRange<const T*, const T*>(static_cast<const T*>(begin), static_cast<const T*>(end));
		}
		template <typename T>
		ConstRange<const T*, size_t> MakeConstRange(T begin[], size_t end)
		{
			return ConstRange<const T*, size_t>(static_cast<const T*>(begin), end);
		}
		template <typename T>
		ConstRange<const T*, int> MakeConstRange(T begin[], int end)
		{
			return ConstRange<const T*, int>(static_cast<const T*>(begin), end);
		}
#endif

		template <typename T>
		class ConstArray
		{
			const T *b;
			size_t m_size;
		public:
			ConstArray(const T *begin_, size_t size_): b(begin_), m_size(size_) {}
			const T* begin() const { return b; }
			const T* end() const { return b+m_size; }
			size_t size() const { return m_size; }
		};
		template <typename T>
		ConstArray<T> MakeConstArray(const T *begin, size_t size)
		{
			return ConstArray<T>(begin, size);
		}

		template <class PR>
		struct SortToEqualCore: public FunctorCore
		{
			SortToEqualCore() {}
			SortToEqualCore(PR pr_): pr(pr_) {}

			PR pr;

			template<typename T1, typename T2>
			bool operator()(const T1 &t1, const T2 &t2) const
			{
				return !pr(t1,t2)&&!pr(t2,t1);
			}
			const char* GetTextAfter1() const
			{
				return " == ";
			}
		};

		template <class PR, class GV1=Value, class GV2=Value, class Str1=MakeString, class Str2=MakeString>
		struct SortToEqual: public Wrapper2Arg<SortToEqualCore<PR>, GV1, GV2, Str1, Str2>
		{
			SortToEqual(GV1 gv1=GV1(), GV2 gv2=GV2()):
				Wrapper2Arg<SortToEqualCore<PR>, GV1, GV2, Str1, Str2>(SortToEqualCore<PR>(), gv1, gv2)
			{}
			SortToEqual(PR pr, GV1 gv1=GV1(), GV2 gv2=GV2()):
				Wrapper2Arg<SortToEqualCore<PR>, GV1, GV2, Str1, Str2>(SortToEqualCore<PR>(pr), gv1, gv2)
			{}
		};
	}

	// structs for one range

	namespace detail
	{
		class AllMessages
		{
		protected:
			static const char * const s_msg;
		};

		template <class RB>
		class AllCoreBase: public CustomFunctorCore<true>, public AllMessages
		{
		protected:
			RB rb;

			template<typename It, class EC_>
			bool check(It begin, EC_ ec) const
			{
				for (typename EC_::IndexType idx=0; ec(begin, idx); ++begin, ++idx)
					if (!rb(*begin)) return false;
				return true;
			}
			template<typename It, class EC_>
			Analysis::State SafeCheck_(It begin, EC_ ec) const
			{
				for (typename EC_::IndexType idx=0; ec(begin, idx); ++begin, ++idx)
					switch (rb.SafeCheck(*begin))
					{
					case Analysis::NotOk: return Analysis::NotOk;
					case Analysis::BadValue: return Analysis::BadValue;
					}
				return Analysis::Ok;
			}

		public:
			explicit AllCoreBase(RB rb_=RB()): rb(rb_) {}

			template<typename It, typename T>
			bool operator()(It begin, T t) const
			{
				return check(begin, MakeEndCondition(t));
			}
			template<typename It, typename T>
			Analysis::State SafeCheck(It begin, T t) const
			{
				return SafeCheck_(begin, MakeEndCondition(t));
			}
			const char* GetTextBefore1() const
			{ return s_msg; }
			const char* GetTextBefore2() const
			{ return "-"; }
		};

		template <class RB>
		class AllCoreMP: public AllCoreBase<RB>
		{
		public:
			explicit AllCoreMP(bool aeos_=false):
				aeos(aeos_) {}
			explicit AllCoreMP(RB rb_, bool aeos_=false):
				AllCoreBase<RB>(rb_), aeos(aeos_) {}

            using AllCoreBase<RB>::rb;

			bool aeos;

			template <typename It, typename Expr1, class Str1,
				typename T, typename Expr2, class Str2>
			Analysis* Analyse(It begin, Expr1 expr1, Str1 ,
				T t, Expr2 expr2, Str2 ,
				bool ais, bool negate=false,
				const char *msg=0) const
			{
				return Analyse_(begin, expr1, MakeEndCondition(t), expr2,
					ais, negate, msg);
			}

		private:
			template <typename It, typename Expr1, class EC_, typename Expr2>
			Analysis* Analyse_(It begin, Expr1 expr1,
				EC_ ec, Expr2 expr2,
				bool ais, bool negate,
				const char *msg) const
			{
				if (!msg) msg = AllMessages::s_msg;

				Analysis::State gst = SafeCheck_(begin, ec);
				bool ok=gst==Analysis::Ok;
				if ((ok!=negate) && !ais && (gst!=Analysis::BadValue))
					return 0;

				AnalysisOfRange *an =
					new AnalysisOfRange(gst, msg,
						MakeExpression(expr1), MakeExpression(expr2)
					);

				AutoAnalysis autoAn = an;

				if (aeos)
					for (typename EC_::IndexType idx=0; ec(begin, idx); ++begin, ++idx)
					{
						Analysis *a=AllCoreBase<RB>::rb.Analyse(*begin, idx, true);
						an->Add(a);
						if (a->GetState()==Analysis::BadValue) an->SetState(Analysis::BadValue);
					}
				else
					for (typename EC_::IndexType idx=0; ec(begin, idx); ++begin, ++idx)
					{
						Analysis::State st=rb.SafeCheck(*begin);
						if (st!=Analysis::Ok)
						{
							an->Add(AllCoreBase<RB>::rb.Analyse(*begin, idx, false));
							if (st==Analysis::BadValue)
								an->SetState(Analysis::BadValue);
						}
					}
				return autoAn.Release();
			}
		};

		template <class RB,
			class GV1=Value, class GV2=Value>
		struct AllMP: public Wrapper2Arg<AllCoreMP<RB>, GV1, GV2, NoString, NoString>
		{
			AllMP(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2()):
				Wrapper2Arg<AllCoreMP<RB>, GV1, GV2, NoString, NoString>(AllCoreMP<RB>(aeos_), gv1, gv2)
			{}
			AllMP(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2()):
				Wrapper2Arg<AllCoreMP<RB>, GV1, GV2, NoString, NoString>(AllCoreMP<RB>(rb, aeos_), gv1, gv2)
			{}

			typedef Wrapper2Arg<AllCoreMP<RB>, GV1, GV2, NoString, NoString> Parent;
			const char* GetTextBefore1() const
			{ return Parent::condition.GetTextBefore1(); }
			const char* GetTextAfter1() const
			{ return Parent::condition.GetTextAfter1(); }
		};

		template <class RB>
		struct AllCoreSP: public AllCoreBase<RB>
		{
			explicit AllCoreSP(bool aeos_=false):
				aeos(aeos_) {}
			explicit AllCoreSP(RB rb_, bool aeos_=false):
				AllCoreBase<RB>(rb_), aeos(aeos_) {}

			bool aeos;

			template <typename It, typename Expr1, class Str1,
				typename T, typename Expr2, class Str2>
			Analysis* Analyse(It begin, Expr1 expr1, Str1 ,
				T t, Expr2 expr2, Str2 ,
				bool ais, bool negate=false,
				const char *msg=0) const
			{
				return Analyse_(begin, expr1, MakeEndCondition(t), expr2,
					ais, negate, msg);
			}

		private:
			template<typename It, typename Expr1, class EC_, typename Expr2>
			Analysis* Analyse_(It begin, Expr1 expr1,
				EC_ ec, Expr2 expr2,
				bool ais, bool negate,
				const char *msg) const
			{
				if (!msg) msg = AllMessages::s_msg;

				bool ok = true, bv=false;
				AnalysisOfRange *an =
					new AnalysisOfRange(false, msg, MakeExpression(expr1), MakeExpression(expr2));
				AutoAnalysis autoAn = an;

				for (typename EC_::IndexType idx=0; ec(begin, idx); ++begin, ++idx)
				{
					Analysis::State st = AllCoreBase<RB>::rb.SafeCheck(*begin);
					if (st!=Analysis::Ok)
						ok = false;
					if (st==Analysis::BadValue)
						bv=true;
					if ((st!=Analysis::Ok)||aeos)
						an->Add(AllCoreBase<RB>::rb.Analyse(*begin, idx, true));
				}

				if (bv)
					an->SetState(Analysis::BadValue);
				else if ((ok!=negate)&&!ais)
					return 0;
				else if (ok)
					an->SetState(Analysis::Ok);
				return autoAn.Release();
			}
		};

		template <class RB,
			class GV1=Value, class GV2=Value>
		struct AllSP: public Wrapper2Arg<AllCoreSP<RB>, GV1, GV2, NoString, NoString>
		{
			AllSP(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2()):
				Wrapper2Arg<AllCoreSP<RB>, GV1, GV2, NoString, NoString>(AllCoreSP<RB>(aeos_), gv1, gv2)
			{}
			AllSP(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2()):
				Wrapper2Arg<AllCoreSP<RB>, GV1, GV2, NoString, NoString>(AllCoreSP<RB>(rb, aeos_), gv1, gv2)
			{}

			typedef Wrapper2Arg<AllCoreSP<RB>, GV1, GV2, NoString, NoString> Parent;
			const char* GetTextBefore1() const
			{ return Parent::condition.GetTextBefore1(); }
			const char* GetTextAfter1() const
			{ return Parent::condition.GetTextAfter1(); }
		};
	}

	template<bool mp=true>
	struct All {};

	RICHBOOL_MAKE_FACTORY(All, RICHBOOL_SUFFIX_T, AllMP, Are)
	RICHBOOL_MAKE_FACTORY(All, RICHBOOL_SUFFIX_F, AllSP, Are)


	// structs that check whether a range has an element that
	// satisfies a certain condition

	namespace detail
	{
		class HasMessages
		{
		protected:
			static const char * const s_msg;
		};

		template <class RB>
		class HasCoreBase: public CustomFunctorCore<true>, public HasMessages
		{
		protected:
			RB rb;
		public:
			explicit HasCoreBase(RB rb_=RB()): rb(rb_) {}

			template<typename It, typename Ec>
			bool operator()(It begin, Ec end) const
			{
				return check(begin, MakeEndCondition(end));
			}
			template<typename It, typename Ec>
			Analysis::State SafeCheck(It begin, Ec end) const
			{
				return SafeCheck_(begin, MakeEndCondition(end));
			}
			const char* GetTextBefore1() const
			{ return s_msg; }
			const char* GetTextBefore2() const
			{ return "-"; }

		protected:
			template<typename It, class EC_>
			bool check(It begin, EC_ ec) const
			{
				for (typename EC_::IndexType i=0; ec(begin, i); ++i, ++begin)
					if (rb(*begin))
						return true;
				return false;
			}
			template<typename It, class EC_>
			Analysis::State SafeCheck_(It begin, EC_ ec) const
			{
				for (typename EC_::IndexType i=0; ec(begin, i); ++i, ++begin)
				{
					switch (rb.SafeCheck(*begin))
					{
					case Analysis::Ok: return Analysis::Ok;
					case Analysis::BadValue: return Analysis::BadValue;
					}
				}
				return Analysis::NotOk;
			}
		};

		template<class RB>
		struct HasCoreMP: public HasCoreBase<RB>
		{
			explicit HasCoreMP(bool aeos_=false):
				aeos(aeos_) {}
			explicit HasCoreMP(RB rb_, bool aeos_=false):
				HasCoreBase<RB>(rb_), aeos(aeos_) {}

			bool aeos;

			template <typename It, typename Expr1, class Str1,
				typename End, typename Expr2, class Str2>
			Analysis* Analyse(It begin, Expr1 expr1, Str1 ,
				End end, Expr2 expr2, Str2 ,
				bool ais, bool negate=false,
				const char *msg=0) const
			{
				return Analyse_(begin, MakeEndCondition(end), expr1, expr2,
					ais, negate, msg);
			}

		protected:
			template <typename It, typename Expr1, class EC_, typename Expr2>
			Analysis* Analyse_(It begin, EC_ ec,
				Expr1 expr1, Expr2 expr2,
				bool ais, bool negate,
				const char *msg) const
			{
				if (!msg) msg = HasMessages::s_msg;

				Analysis::State st=SafeCheck_(begin, ec);
				bool ok=st==Analysis::Ok;
				if ((ok!=negate) && !ais && (st!=Analysis::BadValue))
					return 0;

				AnalysisOfRange *an =
					new AnalysisOfRange(st, msg,
						MakeExpression(expr1), MakeExpression(expr2)
					);

				AutoAnalysis autoAn = an;

				if (aeos)
					for (typename EC_::IndexType idx=0; ec(begin, idx); ++begin, ++idx)
						an->Add(HasCoreBase<RB>::rb.Analyse(*begin, idx, aeos));
				else if (st==Analysis::BadValue)
					for (typename EC_::IndexType idx=0; ec(begin, idx); ++begin, ++idx)
					{
						Analysis *a=HasCoreBase<RB>::rb.Analyse(*begin, idx, aeos);
						if (a&&(a->GetState()==Analysis::BadValue)) an->Add(a);
						else delete a;
					}

				return autoAn.Release();
			}
		};

		template<class RB>
		struct HasCoreSP: public HasCoreBase<RB>
		{
			explicit HasCoreSP(bool aeos_=false):
				aeos(aeos_) {}
			explicit HasCoreSP(RB rb_, bool aeos_=false):
				HasCoreBase<RB>(rb_), aeos(aeos_) {}

            using HasCoreBase<RB>::rb;

			bool aeos;

			template<typename It, typename Expr1, class Str1,
				typename End, typename Expr2, class Str2>
			Analysis* Analyse(It begin, Expr1 expr1, Str1 ,
				End end, Expr2 expr2, Str2 ,
				bool ais, bool negate=false,
				const char *msg=0) const
			{
				return Analyse_(begin, MakeEndCondition(end), expr1, expr2,
					ais, negate, msg);
			}

		protected:
			template<typename It, typename Expr1, class EC_, typename Expr2>
			Analysis* Analyse_(It begin, EC_ ec,
				Expr1 expr1, Expr2 expr2,
				bool ais, bool negate,
				const char *msg) const
			{
				if (!msg) msg = HasMessages::s_msg;

				bool ok = false;
				AnalysisOfRange *an =
					new AnalysisOfRange(false, msg, MakeExpression(expr1), MakeExpression(expr2));
				AutoAnalysis autoAn = an;

				bool bv=false;
				for (typename EC_::IndexType idx=0; ec(begin, idx); ++begin, ++idx)
				{
					Analysis::State st=rb.SafeCheck(*begin);
					if (st==Analysis::Ok)
					{
						ok = true;
						if (!ais&&!negate&&!bv)
							break; // no need to continue
					}
					else if (st==Analysis::BadValue)
						bv = true;
					if (aeos||(st==Analysis::BadValue))
						an->Add(HasCoreBase<RB>::rb.Analyse(*begin, idx, aeos));
				}

				if (bv)
					an->SetState(Analysis::BadValue);
				else if ((ok!=negate)&&!ais)
					return 0;
				else if (ok)
					an->SetState(Analysis::Ok);
				return autoAn.Release();
			}
		};

		template <class RB,
			class GV1=Value, class GV2=Value>
		struct HasMP: public Wrapper2Arg<HasCoreMP<RB>, GV1, GV2, NoString, NoString>
		{
			HasMP(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2()):
				Wrapper2Arg<HasCoreMP<RB>, GV1, GV2, NoString, NoString>(HasCoreMP<RB>(aeos_), gv1, gv2)
			{}
			HasMP(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2()):
				Wrapper2Arg<HasCoreMP<RB>, GV1, GV2, NoString, NoString>(HasCoreMP<RB>(rb, aeos_), gv1, gv2)
			{}

			typedef Wrapper2Arg<HasCoreMP<RB>, GV1, GV2, NoString, NoString> Parent;
			const char* GetTextBefore1() const
			{ return Parent::condition.GetTextBefore1(); }
			const char* GetTextAfter1() const
			{ return Parent::condition.GetTextAfter1(); }
		};

		template <class RB,
			class GV1=Value, class GV2=Value>
		struct HasSP: public Wrapper2Arg<HasCoreSP<RB>, GV1, GV2, NoString, NoString>
		{
			HasSP(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2()):
				Wrapper2Arg<HasCoreSP<RB>, GV1, GV2, NoString, NoString>(HasCoreSP<RB>(aeos_), gv1, gv2)
			{}
			HasSP(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2()):
				Wrapper2Arg<HasCoreSP<RB>, GV1, GV2, NoString, NoString>(HasCoreSP<RB>(rb, aeos_), gv1, gv2)
			{}

			typedef Wrapper2Arg<HasCoreSP<RB>, GV1, GV2, NoString, NoString> Parent;
			const char* GetTextBefore1() const
			{ return Parent::condition.GetTextBefore1(); }
			const char* GetTextAfter1() const
			{ return Parent::condition.GetTextAfter1(); }
		};
	}

	template<bool mp=true>
	struct Has {};

	RICHBOOL_MAKE_FACTORY(Has, RICHBOOL_SUFFIX_T, HasMP, That)
	RICHBOOL_MAKE_FACTORY(Has, RICHBOOL_SUFFIX_F, HasSP, That)


	// structs that check whether a range has a unique element that
	// satisfies a certain condition

	namespace detail
	{
		class UniqueMessages
		{
		protected:
			static const char * const s_msg;
		};

		template <class RB>
		class UniqueCoreBase: public CustomFunctorCore<true>, protected UniqueMessages
		{
		protected:
			RB rb;
		public:
			explicit UniqueCoreBase(RB rb_=RB()): rb(rb_) {}

			template<typename It, typename End>
			bool operator()(It begin, End end) const
			{
				return check(begin, MakeEndCondition(end));
			}
			template<typename It, typename End>
			Analysis::State SafeCheck(It begin, End end) const
			{
				return SafeCheck_(begin, MakeEndCondition(end));
			}
			const char* GetTextBefore1() const
			{ return s_msg; }
			const char* GetTextBefore2() const
			{ return "-"; }

		protected:
			template<typename It, class EC_>
			bool check(It begin, EC_ ec) const
			{
				bool found = false;
				for (typename EC_::IndexType idx=0; ec(begin, idx); ++begin, ++idx)
					if (rb(*begin))
					{
						if (found)
							return false;
						else
							found = true;
					}
				return found;
			}
			template<typename It, class EC_>
			Analysis::State SafeCheck_(It begin, EC_ ec) const
			{
				bool found = false;
				for (typename EC_::IndexType idx=0; ec(begin, idx); ++begin, ++idx)
					switch (rb.SafeCheck(*begin))
					{
					case Analysis::Ok:
						if (found)
							return Analysis::NotOk;
						else
							found = true;
						break;
					case Analysis::BadValue:
						return Analysis::BadValue;
					}
				return found ? Analysis::Ok : Analysis::NotOk;
			}
		};

		template <class RB>
		struct UniqueCoreMP: public UniqueCoreBase<RB>
		{
			explicit UniqueCoreMP(bool aeos_=false):
				aeos(aeos_) {}
			explicit UniqueCoreMP(RB rb_, bool aeos_=false):
				UniqueCoreBase<RB>(rb_), aeos(aeos_) {}

			bool aeos;

			template <typename It, typename Expr1, class Str1,
				typename End, typename Expr2, class Str2>
			Analysis* Analyse(It begin, Expr1 expr1, Str1 ,
				End end, Expr2 expr2, Str2 ,
				bool ais, bool negate=false,
				const char *msg=0) const
			{
				return Analyse_(begin, MakeEndCondition(end), expr1, expr2,
					ais, negate, msg);
			}

		protected:
			template <typename It, typename Expr1, class EC_, typename Expr2>
			Analysis* Analyse_(It begin, EC_ ec,
				Expr1 expr1, Expr2 expr2,
				bool ais, bool negate,
				const char *msg) const
			{
				if (!msg) msg = UniqueMessages::s_msg;

				Analysis::State gst=SafeCheck_(begin, ec);
				bool ok=gst==Analysis::Ok;
				if ((ok!=negate) && !ais && (gst!=Analysis::BadValue))
					return 0;

				AnalysisOfRange *an =
					new AnalysisOfRange(gst, msg,
						MakeExpression(expr1), MakeExpression(expr2));
				AutoAnalysis autoAn = an;

				if (aeos)
					for (typename EC_::IndexType idx=0; ec(begin, idx); ++begin, ++idx)
					{
						Analysis::State st=UniqueCoreBase<RB>::rb.SafeCheck(*begin);
						if (st==Analysis::BadValue)
							an->SetState(Analysis::BadValue);
						an->Add(UniqueCoreBase<RB>::rb.Analyse(*begin, idx, true));
					}
				else
					// only show the ones that *fulfill* the condition,
					// i.e. the opposite of usual, but also show the ones with a bad value
					for (typename EC_::IndexType idx=0; ec(begin, idx); ++begin, ++idx)
					{
						Analysis::State st=UniqueCoreBase<RB>::rb.SafeCheck(*begin);
						if ((st==Analysis::Ok)||(st==Analysis::BadValue))
						{
							an->Add(UniqueCoreBase<RB>::rb.Analyse(*begin, idx, true));
							if (st==Analysis::BadValue)
								an->SetState(Analysis::BadValue);
						}
					}
				return autoAn.Release();
			}
		};

		template <class RB>
		struct UniqueCoreSP: public UniqueCoreBase<RB>
		{
			explicit UniqueCoreSP(bool aeos_=false):
				aeos(aeos_) {}
			explicit UniqueCoreSP(RB rb_, bool aeos_=false):
				UniqueCoreBase<RB>(rb_), aeos(aeos_) {}

			bool aeos;

			template<typename It, typename Expr1, class Str1,
				typename End, typename Expr2, class Str2>
			Analysis* Analyse(It begin, Expr1 expr1, Str1 ,
				End end, Expr2 expr2, Str2 ,
				bool ais, bool negate=false,
				const char *msg=0) const
			{
				return Analyse_(begin, MakeEndCondition(end), expr1, expr2,
					ais, negate, msg);
			}

		protected:
			template<typename It, typename Expr1, class EC_, typename Expr2>
			Analysis* Analyse_(It begin, EC_ ec,
				Expr1 expr1, Expr2 expr2,
				bool ais, bool negate=false,
				const char *msg=0) const
			{
				if (!msg) msg = UniqueMessages::s_msg;

				int count=0;
				AnalysisOfRange *an =
					new AnalysisOfRange(false, msg, MakeExpression(expr1), MakeExpression(expr2));
				AutoAnalysis autoAn = an;

				bool bv=false;
				for (typename EC_::IndexType idx=0; ec(begin, idx); ++begin, ++idx)
				{
					Analysis::State st=UniqueCoreBase<RB>::rb.SafeCheck(*begin);
					bool ok = st==Analysis::Ok;
					if (ok)
						++count;
					else if (st==Analysis::BadValue)
						bv=true;
					if (ok || aeos || (st==Analysis::BadValue))
						an->Add(UniqueCoreBase<RB>::rb.Analyse(*begin, idx, true));
				}

				if (bv)
					an->SetState(Analysis::BadValue);
				else if (((count==1)!=negate)&&!ais)
					return 0;
				else if (count==1)
					an->SetState(Analysis::Ok);
				return autoAn.Release();
			}
		};

		template <class RB,
			class GV1=Value, class GV2=Value>
		struct UniqueMP: public Wrapper2Arg<UniqueCoreMP<RB>, GV1, GV2, NoString, NoString>
		{
			UniqueMP(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2()):
				Wrapper2Arg<UniqueCoreMP<RB>, GV1, GV2, NoString, NoString>(UniqueCoreMP<RB>(aeos_), gv1, gv2)
			{}
			UniqueMP(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2()):
				Wrapper2Arg<UniqueCoreMP<RB>, GV1, GV2, NoString, NoString>(UniqueCoreMP<RB>(rb, aeos_), gv1, gv2)
			{}

			typedef Wrapper2Arg<UniqueCoreMP<RB>, GV1, GV2, NoString, NoString> Parent;
			const char* GetTextBefore1() const
			{ return Parent::condition.GetTextBefore1(); }
			const char* GetTextAfter1() const
			{ return Parent::condition.GetTextAfter1(); }
		};

		template <class RB,
			class GV1=Value, class GV2=Value>
		struct UniqueSP: public Wrapper2Arg<UniqueCoreSP<RB>, GV1, GV2, NoString, NoString>
		{
			UniqueSP(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2()):
				Wrapper2Arg<UniqueCoreSP<RB>, GV1, GV2, NoString, NoString>(UniqueCoreSP<RB>(aeos_), gv1, gv2)
			{}
			UniqueSP(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2()):
				Wrapper2Arg<UniqueCoreSP<RB>, GV1, GV2, NoString, NoString>(UniqueCoreSP<RB>(rb, aeos_), gv1, gv2)
			{}

			typedef Wrapper2Arg<UniqueCoreSP<RB>, GV1, GV2, NoString, NoString> Parent;
			const char* GetTextBefore1() const
			{ return Parent::condition.GetTextBefore1(); }
			const char* GetTextAfter1() const
			{ return Parent::condition.GetTextAfter1(); }
		};
	}

	template<bool mp=true>
	struct Unique {};

	RICHBOOL_MAKE_FACTORY(Unique, RICHBOOL_SUFFIX_T, UniqueMP, That)
	RICHBOOL_MAKE_FACTORY(Unique, RICHBOOL_SUFFIX_F, UniqueSP, That)

	// adjacent checks on a range

	namespace detail
	{
		class AdjacentMessages
		{
		protected:
			static const char *s_msg;
		};

		template <class RB>
		struct AdjacentCoreMP: public CustomFunctorCore<true>, public AdjacentMessages
		{
		protected:
			RB rb;
			bool aeos;
		public:
			explicit AdjacentCoreMP(bool aeos_=false):
				aeos(aeos_) {}
			explicit AdjacentCoreMP(RB rb_, bool aeos_=false):
				rb(rb_), aeos(aeos_) {}

			template<typename It, typename End>
			bool operator()(It begin, End end) const
			{
				return check(begin, MakeEndCondition(end));
			}
			template<typename It, typename End>
			Analysis::State SafeCheck(It begin, End end) const
			{
				return SafeCheck_(begin, MakeEndCondition(end));
			}

			template<typename It, typename Expr1, class Str1,
				typename End, typename Expr2, class Str2>
			Analysis* Analyse(It begin, Expr1 expr1, Str1,
				End end, Expr2 expr2, Str2,
				bool ais, bool negate=false,
				const char *msg=0) const
			{
				return Analyse_(begin, MakeEndCondition(end), expr1, expr2,
					ais, negate, msg);
			}

			const char* GetTextBefore1() const
			{ return s_msg; }
			const char* GetTextBefore2() const
			{ return "-"; }

		protected:
			template<typename It, class EC_>
			bool check(It begin, EC_ ec) const
			{
				if (!ec(begin, 0))
					return true; // empty range

				It next = begin;
				++next;

				for (typename EC_::IndexType idx=1; ec(next, idx); ++begin, ++next, ++idx)
					if (!rb(*begin, *next))
						return false;
				return true;
			}
			template<typename It, class EC_>
			Analysis::State SafeCheck_(It begin, EC_ ec) const
			{
				if (!ec(begin, 0))
					return Analysis::Ok; // empty range

				if (!rb.IsValid1(*begin))
					return Analysis::BadValue;

				It next = begin;
				++next;

				for (typename EC_::IndexType idx=1; ec(next, idx); ++begin, ++next, ++idx)
				{
					if (!rb.IsValid1(*next))
						return Analysis::BadValue;
					if (!rb(*begin, *next))
						return Analysis::NotOk;
				}
				return Analysis::Ok;
			}

			template<typename It, typename Expr1, class EC_, typename Expr2>
			Analysis* Analyse_(It begin, EC_ ec,
				Expr1 expr1, Expr2 expr2,
				bool ais, bool negate,
				const char *msg) const
			{
				if (!msg) msg = AdjacentMessages::s_msg;

				Analysis::State st=SafeCheck_(begin, ec);
				bool ok=st==Analysis::Ok;
				if ((ok!=negate) && !ais && (st!=Analysis::BadValue))
					return 0;

				AnalysisOfRange *an =
					new AnalysisOfRange(st, msg,
						MakeExpression(expr1), MakeExpression(expr2)
					);

				AutoAnalysis autoAn = an;

				if (ec(begin, 0))
				{
					It next = begin;
					++next;
					for (typename EC_::IndexType idx=1; ec(next, idx); ++begin, ++next, ++idx)
						if (aeos || (rb.SafeCheck(*begin, *next)!=Analysis::Ok) )
							an->Add(rb.Analyse(*begin, *next, idx-1, idx,
								aeos));
				}
				return autoAn.Release();
			}
		};

		template <class RB>
		struct AdjacentCoreSP: public CustomFunctorCore<true>, public AdjacentMessages
		{
		protected:
			RB rb;
			bool aeos;
		public:
			explicit AdjacentCoreSP(bool aeos_=false):
				aeos(aeos_) {}
			explicit AdjacentCoreSP(RB rb_, bool aeos_=false):
				rb(rb_), aeos(aeos_) {}

			template<typename It, typename End>
			bool operator()(It begin, End end) const
			{
				return check(begin, MakeEndCondition(end));
			}
			template<typename It, typename End>
			Analysis::State SafeCheck(It begin, End end) const
			{
				return SafeCheck_(begin, MakeEndCondition(end));
			}

			template<typename It, typename Expr1, class Str1,
				typename End, typename Expr2, class Str2>
			Analysis* Analyse(It begin, Expr1 expr1, Str1 ,
				End end, Expr2 expr2, Str2 ,
				bool ais, bool negate=false,
				const char *msg=0) const
			{
				return Analyse1(begin, MakeEndCondition(end), expr1, expr2,
					ais, negate, msg);
			}

			template<typename It, typename Expr1, class EC_, typename Expr2>
			Analysis* Analyse1(It begin, EC_ ec,
				Expr1 expr1, Expr2 expr2,
				bool ais, bool negate=false,
				const char *msg=0) const
			{
				if (!msg) msg = AdjacentMessages::s_msg;

				if (!ec(begin, 0))
				{
					if (!ais && !negate)
						return 0;
                    Analysis *an=new AnalysisOfRange(true, msg, MakeExpression(expr1), MakeExpression(expr2));
					return an;
				}
				else
					return Analyse2(begin, ec, *begin, expr1, expr2,
						ais, negate, msg);
			}

			const char* GetTextBefore1() const
			{ return s_msg; }
			const char* GetTextBefore2() const
			{ return "-"; }

		private:
			template<typename It, class EC_>
			bool check(It begin, EC_ ec) const
			{
				if (!ec(begin, 0))
					return true; // empty range
				else
					return check2(begin, ec, *begin);
			}
			template<typename It, class EC_>
			Analysis::State SafeCheck_(It begin, EC_ ec) const
			{
				if (!ec(begin, 0))
					return Analysis::Ok; // empty range
				else
					return SafeCheck2(begin, ec, *begin);
			}

			template<typename It, class EC_, typename T>
			bool check2(It begin, EC_ ec, T) const
			{
				T prev = *begin;
				++begin;

				for (typename EC_::IndexType idx=1; ec(begin, idx); ++begin, ++idx)
					if (rb(prev, *begin))
						prev = *begin;
					else
						return false;
				return true;
			}
			template<typename It, class EC_, typename T>
			Analysis::State SafeCheck2(It begin, EC_ ec, T) const
			{
				if (!rb.IsValid1(*begin))
					return Analysis::BadValue;
				T prev = *begin;
				++begin;

				for (typename EC_::IndexType idx=1; ec(begin, idx); ++begin, ++idx)
				{
					if (!rb.IsValid1(*begin))
						return Analysis::BadValue;
					if (!rb(prev, *begin))
						return Analysis::NotOk;
					prev = *begin;
				}
				return Analysis::Ok;
			}

			template<typename It, typename Expr1, class EC_, typename T, typename Expr2>
			Analysis* Analyse2(It begin, EC_ ec, T,
				Expr1 expr1, Expr2 expr2,
				bool ais, bool negate,
				const char *msg) const
			{
				bool ok = true;

				T prev;

				AnalysisOfRange *an = new AnalysisOfRange(false, msg, MakeExpression(expr1), MakeExpression(expr2));
				AutoAnalysis autoAn = an;

				bool prevValid=rb.IsValid1(*begin);
				if (prevValid)
					prev=*begin;
				else
					an->Add(new Single(0, 2, rb.GetString1(*begin),
						new IndexExpression(0), false));
				++begin;

				bool bv=!prevValid;
				for (typename EC_::IndexType idx=1; ec(begin, idx); ++begin, ++idx)
				{
					if (prevValid)
					{
						prevValid=rb.IsValid1(*begin);
						if (prevValid)
						{
							const bool thisOk = rb(prev, *begin);
							if (!thisOk)
								ok = false;
							if (!thisOk || aeos)
								an->Add(rb.Analyse(prev, *begin,
									idx-1, idx,
									aeos));
						}
						else
						{
							an->Add(rb.Analyse(prev, *begin,
									idx-1, idx,
									aeos));
							bv=true;
						}
					}
					else
						prevValid=rb.IsValid1(*begin);
					if (prevValid)
						prev = *begin;
				}

				if (bv)
					an->SetState(Analysis::BadValue);
				else if ((ok!=negate)&&!ais)
					return 0;
				else if (ok)
					an->SetState(Analysis::Ok);
				return autoAn.Release();
			}
		};

		template <class RB, class GV1=Value, class GV2=Value>
		struct AdjacentMP: public Wrapper2Arg<AdjacentCoreMP<RB>, GV1, GV2, NoString, NoString>
		{
			AdjacentMP(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2()):
				Wrapper2Arg<AdjacentCoreMP<RB>, GV1, GV2, NoString, NoString>(AdjacentCoreMP<RB>(aeos_), gv1, gv2)
			{}
			AdjacentMP(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2()):
				Wrapper2Arg<AdjacentCoreMP<RB>, GV1, GV2, NoString, NoString>(AdjacentCoreMP<RB>(rb, aeos_), gv1, gv2)
			{}

			typedef Wrapper2Arg<AdjacentCoreMP<RB>, GV1, GV2, NoString, NoString> Parent;
			const char* GetTextBefore1() const
			{ return Parent::condition.GetTextBefore1(); }
			const char* GetTextAfter1() const
			{ return Parent::condition.GetTextAfter1(); }
		};

		template <class RB, class GV1=Value, class GV2=Value>
		struct AdjacentSP: public Wrapper2Arg<AdjacentCoreSP<RB>, GV1, GV2, NoString, NoString>
		{
			AdjacentSP(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2()):
				Wrapper2Arg<AdjacentCoreSP<RB>, GV1, GV2, NoString, NoString>(AdjacentCoreSP<RB>(aeos_), gv1, gv2)
			{}
			AdjacentSP(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2()):
				Wrapper2Arg<AdjacentCoreSP<RB>, GV1, GV2, NoString, NoString>(AdjacentCoreSP<RB>(rb, aeos_), gv1, gv2)
			{}

			typedef Wrapper2Arg<AdjacentCoreSP<RB>, GV1, GV2, NoString, NoString> Parent;
			const char* GetTextBefore1() const
			{ return Parent::condition.GetTextBefore1(); }
			const char* GetTextAfter1() const
			{ return Parent::condition.GetTextAfter1(); }
		};

		template<bool mp=true>
		struct SortedCore {};

		template<>
		struct SortedCore<true>: public detail::AdjacentCoreMP< LessOrEqual<> >
		{
			typedef detail::AdjacentCoreMP< LessOrEqual<> > Parent;
			explicit SortedCore(bool aeos_=false):
				detail::AdjacentCoreMP< LessOrEqual<> >(aeos_) {}

			template<typename It, typename End, typename Expr1, typename Expr2, class Str1, class Str2>
			Analysis* Analyse(It begin, Expr1 expr1, Str1 str1,
				End end, Expr2 expr2, Str2 str2,
				bool ais, bool negate=false) const
			{
				return Parent::Analyse(begin, expr1, str1, end, expr2, str2,
					ais, negate,
					"range is sorted: ");
			}
		};

		template<>
		struct SortedCore<false>: public detail::AdjacentCoreSP< LessOrEqual<> >
		{
			typedef detail::AdjacentCoreSP< LessOrEqual<> > Parent;
			explicit SortedCore(bool aeos_=false):
				detail::AdjacentCoreSP< LessOrEqual<> >(aeos_) {}

			template<typename It, typename End, typename Expr1, typename Expr2, class Str1, class Str2>
			Analysis* Analyse(It begin, Expr1 expr1, Str1 str1,
				End end, Expr2 expr2, Str2 str2,
				bool ais, bool negate=false) const
			{
				return Parent::Analyse(begin, expr1, str1, end, expr2, str2,
					ais, negate,
					"range is sorted: ");
			}
		};

		template<bool mp=true>
		struct SortedStrictlyCore {};

		template<>
		struct SortedStrictlyCore<true>: public detail::AdjacentCoreMP< Less<> >
		{
			typedef detail::AdjacentCoreMP< Less<> > Parent;
			explicit SortedStrictlyCore(bool aeos_=false):
				detail::AdjacentCoreMP< Less<> >(aeos_) {}

			template<typename It, typename End, typename Expr1, typename Expr2,
				class Str1, class Str2>
			Analysis* Analyse(It begin, Expr1 expr1, Str1 str1,
				End end, Expr2 expr2, Str2 str2,
				bool ais, bool negate=false) const
			{
				return Parent::Analyse(begin, expr1, str1, end, expr2, str2,
					ais, negate,
					"range is sorted strictly: ");
			}
		};

		template<>
		struct SortedStrictlyCore<false>: public detail::AdjacentCoreSP< Less<> >
		{
			typedef detail::AdjacentCoreSP< Less<> > Parent;
			explicit SortedStrictlyCore(bool aeos_=false):
				detail::AdjacentCoreSP< Less<> >(aeos_) {}

			template<typename It, typename End, typename Expr1, typename Expr2,
				class Str1, class Str2>
			Analysis* Analyse(It begin, Expr1 expr1, Str1 str1,
				End end, Expr2 expr2, Str2 str2,
				bool ais, bool negate=false) const
			{
				return Parent::Analyse(begin, expr1, str1, end, expr2, str2,
					ais, negate,
					"range is sorted strictly: ");
			}
		};
	}

	template<bool mp=true>
	struct Adjacent {};

	RICHBOOL_MAKE_FACTORY(Adjacent, RICHBOOL_SUFFIX_T, AdjacentMP, Are)
	RICHBOOL_MAKE_FACTORY(Adjacent, RICHBOOL_SUFFIX_F, AdjacentSP, Are)

	template <bool mp=true, class GV1=Value, class GV2=Value>
	struct Sorted: public Wrapper2Arg<detail::SortedCore<mp>, GV1, GV2, NoString, NoString>
	{
		Sorted(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2()):
			Wrapper2Arg<detail::SortedCore<mp>, GV1, GV2, NoString, NoString>(detail::SortedCore<mp>(aeos_), gv1, gv2)
		{}

		typedef Wrapper2Arg<detail::SortedCore<mp>, GV1, GV2, NoString, NoString> Parent;
		const char* GetTextBefore1() const
		{ return Parent::condition.GetTextBefore1(); }
		const char* GetTextAfter1() const
		{ return Parent::condition.GetTextAfter1(); }
	};

	template <bool mp=true, class GV1=Value, class GV2=Value>
	struct SortedStrictly: public Wrapper2Arg<detail::SortedStrictlyCore<mp>, GV1, GV2, NoString, NoString>
	{
		SortedStrictly(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2()):
			Wrapper2Arg<detail::SortedStrictlyCore<mp>, GV1, GV2, NoString, NoString>(detail::SortedStrictlyCore<mp>(aeos_), gv1, gv2)
		{}

		typedef Wrapper2Arg<detail::SortedStrictlyCore<mp>, GV1, GV2, NoString, NoString> Parent;
		const char* GetTextBefore1() const
		{ return Parent::condition.GetTextBefore1(); }
		const char* GetTextAfter1() const
		{ return Parent::condition.GetTextAfter1(); }
	};

	namespace detail
	{
		class AllPairsMessages
		{
		protected:
			static const char *s_msg;
		};

		template <class RB>
		struct AllPairsCore: public CustomFunctorCore<true>, public AllPairsMessages
		{
		protected:
			RB rb;
			bool analyseElementsOnSuccess;
		public:
			explicit AllPairsCore(bool analyseElementsOnSuccess_=false):
				analyseElementsOnSuccess(analyseElementsOnSuccess_) {}
			explicit AllPairsCore(RB rb_, bool analyseElementsOnSuccess_=false):
				rb(rb_), analyseElementsOnSuccess(analyseElementsOnSuccess_) {}

			template<typename It, typename End>
			bool operator()(It begin, End end) const
			{
				return check(begin, MakeEndCondition(end));
			}

			template<typename It, typename Expr1, class Str1,
				typename End, typename Expr2, class Str2>
			Analysis* Analyse(It begin, Expr1 expr1, Str1,
				End end, Expr2 expr2, Str2,
				bool analyseOnSuccess, bool negate=false,
				const char *msg=0) const
			{
				return Analyse_(begin, MakeEndCondition(end), expr1, expr2,
					analyseOnSuccess, negate, msg);
			}

			const char* GetTextBefore1() const
			{ return s_msg; }
			const char* GetTextBefore2() const
			{ return "-"; }

		protected:
			template<typename It, class EndCondition_>
			bool check(It it1, EndCondition_ ec) const
			{
				for (typename EndCondition_::IndexType idx1=0; ec(it1, idx1); ++it1, ++idx1)
				{
					It it2 = it1;
					++it2;
					for (typename EndCondition_::IndexType idx2=idx1+1; ec(it2, idx2); ++it2, ++idx2)
						if (!rb(*it1, *it2))
							return false;
				}
				return true;
			}

			template<typename It, class EndCondition_>
			Analysis::State SafeCheck(It it1, EndCondition_ ec) const
			{
				for (typename EndCondition_::IndexType idx1=0; ec(it1, idx1); ++it1, ++idx1)
				{
					It it2 = it1;
					++it2;
					for (typename EndCondition_::IndexType idx2=idx1+1; ec(it2, idx2); ++it2, ++idx2)
					{
						Analysis::State st=rb.SafeCheck(*it1, *it2);
						if (st!=Analysis::Ok)
							return st;
					}
				}
				return Analysis::Ok;
			}

			template<typename It, typename Expr1, class EndCondition_, typename Expr2>
			Analysis* Analyse_(It it1, EndCondition_ ec,
				Expr1 expr1, Expr2 expr2,
				bool analyseOnSuccess, bool negate,
				const char *msg) const
			{
				if (!msg) msg = AllPairsMessages::s_msg;

				Analysis::State st=SafeCheck(it1, ec);
				bool ok= st==Analysis::Ok;

				if ((ok!=negate)&&!analyseOnSuccess&&(st!=Analysis::BadValue))
					return 0;

				AnalysisOfRange *analysis =
					new AnalysisOfRange(ok, msg,
						MakeExpression(expr1), MakeExpression(expr2)
					);

				AutoAnalysis autoAnalysis = analysis;

				for (typename EndCondition_::IndexType idx1=0; ec(it1, idx1); ++it1, ++idx1)
				{
					if (!rb.IsValid1(*it1))
					{
						analysis->Add(new Single(0, 1, rb.GetString1(*it1),
							new IndexExpression(0), false));
						continue;
					}
					It it2 = it1;
					++it2;
					for (typename EndCondition_::IndexType idx2=idx1+1; ec(it2, idx2); ++it2, ++idx2)
						if (analyseElementsOnSuccess || (rb.SafeCheck(*it1, *it2)==Analysis::NotOk))
							analysis->Add(rb.Analyse(*it1, *it2, idx1, idx2,
								analyseElementsOnSuccess));
				}
				return autoAnalysis.Release();
			}
		};

		template <class RB, class GetValue1=Value, class GetValue2=Value>
		struct AllPairs: public Wrapper2Arg<AllPairsCore<RB>, GetValue1, GetValue2, NoString, NoString>
		{
			AllPairs(bool analyseElementsOnSuccess_=false, GetValue1 gv1=GetValue1(), GetValue2 gv2=GetValue2()):
				Wrapper2Arg<AllPairsCore<RB>, GetValue1, GetValue2, NoString, NoString>(AllPairsCore<RB>(analyseElementsOnSuccess_), gv1, gv2)
			{}
			AllPairs(RB rb, bool analyseElementsOnSuccess_=false, GetValue1 gv1=GetValue1(), GetValue2 gv2=GetValue2()):
				Wrapper2Arg<AllPairsCore<RB>, GetValue1, GetValue2, NoString, NoString>(AllPairsCore<RB>(rb, analyseElementsOnSuccess_), gv1, gv2)
			{}

			typedef Wrapper2Arg<AllPairsCore<RB>, GetValue1, GetValue2, NoString, NoString> Parent;
			const char* GetTextBefore1() const
			{ return Parent::condition.GetTextBefore1(); }
			const char* GetTextAfter1() const
			{ return Parent::condition.GetTextAfter1(); }
		};

		struct AllUniqueCore: public detail::AllPairsCore< Diff<> >
		{
			typedef detail::AllPairsCore< Diff<> > Parent;
			explicit AllUniqueCore(bool analyseElementsOnSuccess_=false):
				detail::AllPairsCore< Diff<> >(analyseElementsOnSuccess_) {}

			template<typename It, typename End, typename Expr1, typename Expr2, class Str1, class Str2>
			Analysis* Analyse(It begin, Expr1 expr1, Str1 str1,
				End end, Expr2 expr2, Str2 str2,
				bool analyseOnSuccess, bool negate=false) const
			{
				return Parent::Analyse(begin, expr1, str1, end, expr2, str2,
					analyseOnSuccess, negate,
					"all elements are unique in range ");
			}
		};
	}

	struct AllPairs
	{
		explicit AllPairs(bool analyseElementsOnSuccess_=false):
			analyseElementsOnSuccess(analyseElementsOnSuccess_)
		{}

		bool analyseElementsOnSuccess;

		template <class RB>
		detail::AllPairs<RB> Are(RB rb)
		{
			return detail::AllPairs<RB>(rb, analyseElementsOnSuccess);
		}

		template <class RB>
		detail::AllPairs<RB> Tie(RB rb)
		{
			return detail::AllPairs<RB>(rb, analyseElementsOnSuccess);
		}
	};

	template <class GetValue1=Value, class GetValue2=Value>
	struct AllUnique: public Wrapper2Arg<detail::AllUniqueCore, GetValue1, GetValue2, NoString, NoString>
	{
		AllUnique(bool analyseElementsOnSuccess_=false, GetValue1 gv1=GetValue1(), GetValue2 gv2=GetValue2()):
			Wrapper2Arg<detail::AllUniqueCore, GetValue1, GetValue2, NoString, NoString>(detail::AllUniqueCore(analyseElementsOnSuccess_), gv1, gv2)
		{}

		typedef Wrapper2Arg<detail::AllUniqueCore, GetValue1, GetValue2, NoString, NoString> Parent;
		const char* GetTextBefore1() const
		{ return Parent::condition.GetTextBefore1(); }
		const char* GetTextAfter1() const
		{ return Parent::condition.GetTextAfter1(); }
	};



	// function objects for two ranges

	namespace detail
	{
		class CompareMessages
		{
		protected:
			static const char * const s_msg;
		};

		template <class RB>
		class CompareCoreBase: public CustomFunctorCore<true>, public CompareMessages
		{
		protected:
			RB rb;
		public:
			explicit CompareCoreBase(RB rb_=RB()): rb(rb_) {}

			template<typename It1, typename End1, typename It2, typename End2>
			bool operator()(It1 begin1, End1 end1,
							It2 begin2, End2 end2) const
			{
				return check(begin1, MakeEndCondition(end1), begin2, MakeEndCondition(end2));
			}
			template<typename It1, typename End1, typename It2, typename End2>
			Analysis::State SafeCheck(It1 begin1, End1 end1,
							It2 begin2, End2 end2) const
			{
				return SafeCheck_(begin1, MakeEndCondition(end1), begin2, MakeEndCondition(end2));
			}

			const char* GetTextBefore1() const
			{ return s_msg; }
			const char* GetTextBefore2() const
			{ return "-"; }
			const char* GetTextBefore3() const
			{ return " and "; }
			const char* GetTextBefore4() const
			{ return "-"; }

		protected:
			template<typename It1, class EC1, typename It2, class EC2>
			bool check(It1 begin1, EC1 ec1,
					   It2 begin2, EC2 ec2) const
			{
				typename EC1::IndexType idx1=0;
				typename EC2::IndexType idx2=0;
				for (; ec1(begin1, idx1) && ec2(begin2, idx2); ++begin1, ++begin2, ++idx1, ++idx2)
					if (!rb(*begin1, *begin2))
						return false;
				return !ec1(begin1, idx1) && !ec2(begin2, idx2);
			}
			template<typename It1, class EC1, typename It2, class EC2>
			Analysis::State SafeCheck_(It1 begin1, EC1 ec1,
					   It2 begin2, EC2 ec2) const
			{
				typename EC1::IndexType idx1=0;
				typename EC2::IndexType idx2=0;
				for (; ec1(begin1, idx1) && ec2(begin2, idx2); ++begin1, ++begin2, ++idx1, ++idx2)
				{
					Analysis::State st=rb.SafeCheck(*begin1, *begin2);
					if ((st==Analysis::NotOk)||(st==Analysis::BadValue))
						return st;
				}
				return (!ec1(begin1, idx1) && !ec2(begin2, idx2)) ?
                    Analysis::Ok : Analysis::NotOk;
			}
		};

		template <class RB>
		struct CompareCoreMultiMulti: public CompareCoreBase<RB>
		{
			typedef size_t Points;

			explicit CompareCoreMultiMulti(bool aeos_=false):
				aeos(aeos_) {}
			explicit CompareCoreMultiMulti(RB rb_, bool aeos_=false):
				CompareCoreBase<RB>(rb_), aeos(aeos_) {}

			bool aeos;

			enum { maxPoints = 100 };

			Points GetGood() const
			{
				return maxPoints;
			}

			template<typename It1, typename End1, typename It2, typename End2>
			Points GetPoints(It1 begin1, End1 end1,
						  It2 begin2, End2 end2) const
			{
				typedef typename RB::Points PointsIntern;
				String strDiff;
				FindDifferences<PointsIntern>::FindDifference(
						begin1, MakeEndCondition(end1),
						begin2, MakeEndCondition(end2),
						strDiff,
						CompareCoreBase<RB>::rb);

				return detail::GetPointsFromDiff(strDiff, maxPoints);
			}

			template <typename It1, typename Expr1, class Str1,
				typename End1, typename Expr2, class Str2,
				typename It2, typename Expr3, class Str3,
				typename End2, typename Expr4, class Str4>
			Analysis* Analyse(It1 begin1, Expr1 expr1, Str1,
				End1 end1, Expr2 expr2, Str2,
				It2 begin2, Expr3 expr3, Str3,
				End2 end2, Expr4 expr4, Str4,
				bool ais, bool negate=false,
				const char *msg=0) const
			{
				if (!msg) msg = this->s_msg;

				typedef typename RB::Points PointsIntern;
				String strDiff;
				Analysis::State st = FindDifferences<PointsIntern>::FindDifference(
						begin1, MakeEndCondition(end1),
						begin2, MakeEndCondition(end2),
						strDiff,
						CompareCoreBase<RB>::rb);

				bool ok = st==Analysis::Ok;
				if ((ok!=negate)&&!ais&&(st!=Analysis::BadValue))
					return NULL;

				AnalysisOfRange *an =
					new AnalysisOfRange(st, msg,
						MakeExpression(expr1), MakeExpression(expr2), MakeExpression(expr3), MakeExpression(expr4)
					);

				AutoAnalysis autoAn = an;

				size_t idx1=0, idx2=0;
				for (size_t i=0; i<detail::str_size(strDiff); ++i)
				{
					switch (strDiff[i])
					{
					case 'M':
						if (aeos)
							an->Add(
								CompareCoreBase<RB>::rb.Analyse(*begin1, *begin2,
									idx1, idx2, true));
						++begin1; ++idx1;
						++begin2; ++idx2;
						break;
					case 'X':
						an->Add(
							CompareCoreBase<RB>::rb.Analyse(*begin1, *begin2,
								idx1, idx2, true));
						++begin1; ++idx1;
						++begin2; ++idx2;
						break;
					case '1':
						an->Add(new Single(0, 2, this->rb.GetString1(*begin1), new IndexExpression(idx1), this->rb.IsValid1(*begin1)));
						++begin1; ++idx1;
						break;
					case '2':
						an->Add(new Single(1, 2, this->rb.GetString2(*begin2), new IndexExpression(idx2), this->rb.IsValid2(*begin2)));
						++begin2; ++idx2;
						break;
					}
				}
				return autoAn.Release();
			}
		};

		template<class RB>
		struct CompareCoreSingleMulti: public CompareCoreBase<RB>
		{
			typedef bool Points;

			explicit CompareCoreSingleMulti(bool aeos_=false):
				aeos(aeos_) {}
			explicit CompareCoreSingleMulti(RB rb_, bool aeos_=false):
				CompareCoreBase<RB>(rb_), aeos(aeos_) {}

            using CompareCoreBase<RB>::rb;

			bool aeos;

			template<typename It1, typename Expr1, class Str1,
				typename End1, typename Expr2, class Str2,
				typename It2, typename Expr3, class Str3,
				typename End2, typename Expr4, class Str4>
			Analysis* Analyse(It1 begin1, Expr1 expr1, Str1,
							  End1 end1, Expr2 expr2, Str2,
							  It2 begin2, Expr3 expr3, Str3,
							  End2 end2, Expr4 expr4, Str4,
							  bool ais, bool negate=false,
							  const char *msg=0) const
			{
				return Analyse_(begin1, MakeEndCondition(end1),
								begin2, MakeEndCondition(end2),
								expr1, expr2, expr3, expr4,
								ais, negate, msg);
			}

			template<typename It1, typename Expr1,
				typename EC1, typename Expr2,
				typename It2, typename Expr3,
				typename EC2, typename Expr4>
			Analysis* Analyse_(It1 begin1, EC1 ec1,
							  It2 begin2, EC2 ec2,
							  Expr1 expr1, Expr2 expr2,
							  Expr3 expr3, Expr4 expr4,
							  bool ais, bool negate,
							  const char *msg) const
			{
				if (!msg) msg = this->s_msg;

				bool ok = true, bv=false;

				AnalysisOfRange *an =
					new AnalysisOfRange(false, msg, MakeExpression(expr1), MakeExpression(expr2), MakeExpression(expr3), MakeExpression(expr4));
				AutoAnalysis autoAn = an;

				typename EC1::IndexType idx1=0;
				typename EC2::IndexType idx2=0;
				for (; ec1(begin1, idx1) && ec2(begin2, idx2); ++begin1, ++idx1, ++begin2, ++idx2)
				{
					Analysis::State st=CompareCoreBase<RB>::rb.SafeCheck(*begin1, *begin2);
					if (st==Analysis::Ok)
					{
						if (aeos)
							an->Add(CompareCoreBase<RB>::rb.Analyse(*begin1, *begin2,
								idx1, idx2, true));
					}
					else
					{
						ok = false;
						if (st==Analysis::BadValue) bv=true;
						It2 cur2 = begin2;
						++cur2;
						bool match = false;
						for (int i=0; (i<maxNrMatches) && ec2(cur2, idx2+i); ++cur2, ++i)
							if (rb.SafeCheck(*begin1, *cur2)==Analysis::Ok)
							{
								match = true;
								for ( ; begin2!=cur2; ++begin2, ++idx2)
									an->Add(new Single(1, 2, this->rb.GetString2(*begin2), new IndexExpression(idx2), this->rb.IsValid2(*begin2)));
								if (aeos)
									an->Add(
										CompareCoreBase<RB>::rb.Analyse(*begin1, *begin2,
											idx1, idx2, true));
								break;
							}
						if (!match)
						{
							an->Add(
								CompareCoreBase<RB>::rb.Analyse(*begin1, *begin2,
									idx1, idx2, aeos));
						}
					}
				}
				while (ec1(begin1, idx1))
				{
					an->Add(new Single(0, 2, this->rb.GetString1(*begin1), new IndexExpression(idx1), this->rb.IsValid1(*begin1)));
					++begin1; ++idx1;
					ok = false;
				}
				while (ec2(begin2, idx2))
				{
					an->Add(new Single(1, 2, this->rb.GetString2(*begin2), new IndexExpression(idx2), this->rb.IsValid2(*begin2)));
					++begin2; ++idx2;
					ok = false;
				}
				if (bv)
					an->SetState(Analysis::BadValue);
				else if ((ok!=negate)&&!ais)
					return 0;
				else if (ok)
					an->SetState(Analysis::Ok);
				return autoAn.Release();
			}
		};

		template<class RB>
		struct CompareCoreSingleSingle: public CompareCoreBase<RB>
		{
			typedef bool Points;

			explicit CompareCoreSingleSingle(bool aeos_=false):
				aeos(aeos_) {}
			explicit CompareCoreSingleSingle(RB rb_, bool aeos_=false):
				CompareCoreBase<RB>(rb_), aeos(aeos_) {}

            using CompareCoreBase<RB>::rb;

			bool aeos;

			template<typename It1, typename Expr1, class Str1,
				typename End1, typename Expr2, class Str2,
				typename It2, typename Expr3, class Str3,
				typename End2, typename Expr4, class Str4>
			Analysis* Analyse(It1 begin1, Expr1 expr1, Str1,
							  End1 end1, Expr2 expr2, Str2,
							  It2 begin2, Expr3 expr3, Str3,
							  End2 end2, Expr4 expr4, Str4,
							  bool ais, bool negate=false,
							  const char *msg=0) const
			{
				return Analyse_(begin1, MakeEndCondition(end1),
							  begin2, MakeEndCondition(end2),
							  expr1, expr2, expr3, expr4,
							  ais, negate, msg);
			}

		protected:
			template<typename It1, typename Expr1, typename EC1, typename Expr2,
				typename It2, typename Expr3, typename EC2, typename Expr4>
			Analysis* Analyse_(It1 begin1, EC1 ec1,
							  It2 begin2, EC2 ec2,
							  Expr1 expr1, Expr2 expr2,
							  Expr3 expr3, Expr4 expr4,
							  bool ais, bool negate,
							  const char *msg)

							  const
			{
				if (!msg) msg = this->s_msg;

				bool ok = true, bv=false;

				AnalysisOfRange *an =
					new AnalysisOfRange(Analysis::NotOk, msg, MakeExpression(expr1), MakeExpression(expr2), MakeExpression(expr3), MakeExpression(expr4));
				AutoAnalysis autoAn = an;

				typename EC1::IndexType idx1=0;
				typename EC2::IndexType idx2=0;
				while ( ec1(begin1, idx1) && ec2(begin2, idx2) )
				{
					Analysis::State st=rb.SafeCheck(*begin1, *begin2);
					if (st==Analysis::Ok)
					{
						if (aeos)
							an->Add(CompareCoreBase<RB>::rb.Analyse(*begin1, *begin2,
								idx1, idx2, true));
						++begin1; ++idx1;
						++begin2; ++idx2;
					}
					else
					{
						ok = false;
						if (st==Analysis::BadValue)
							bv=true;

						Analysis *newAnalysis = CompareCoreBase<RB>::rb.Analyse(*begin1, *begin2,
							idx1, idx2, true);
						AutoAnalysis autoNewAnalysis = newAnalysis;

						Analysis *single = new Single(0, 2, this->rb.GetString1(*begin1), new IndexExpression(idx1), this->rb.IsValid1(*begin1));
						AutoAnalysis autoSingle = single;

						++begin1; ++idx1;
						if (ec1(begin1, idx1) &&
							(CompareCoreBase<RB>::rb.SafeCheck(*begin1, *begin2)==Analysis::Ok))
						{
							autoNewAnalysis.Delete();
							an->Add(autoSingle.Release());
							if (aeos)
								an->Add(CompareCoreBase<RB>::rb.Analyse(*begin1, *begin2,
									idx1, idx2, true));
							++begin1; ++idx1;
						}
						else
						{
							autoSingle.Delete();
							an->Add(autoNewAnalysis.Release());
						}
						++begin2; ++idx2;
					}
				}
				while (ec1(begin1, idx1))
				{
					an->Add(new Single(0, 2, this->rb.GetString1(*begin1), new IndexExpression(idx1), this->rb.IsValid1(*begin1)));
					++begin1; ++idx1;
					ok = false;
				}
				while (ec2(begin2, idx2))
				{
					an->Add(new Single(1, 2, this->rb.GetString2(*begin2), new IndexExpression(idx2), this->rb.IsValid2(*begin2)));
					++begin2; ++idx2;
					ok = false;
				}
				if (bv)
					an->SetState(Analysis::BadValue);
				else if ((ok!=negate)&&!ais)
					return 0;
				else if (ok)
					an->SetState(Analysis::Ok);
				return autoAn.Release();
			}
		};

		template <class RB, class GV1=Value,
			class GV2=Value, class GV3=Value, class GV4=Value>
		struct CompareMultiMulti: public Wrapper4Arg<CompareCoreMultiMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
		{
			CompareMultiMulti(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<CompareCoreMultiMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(CompareCoreMultiMulti<RB>(aeos_), gv1, gv2, gv3, gv4)
			{}
			CompareMultiMulti(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<CompareCoreMultiMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(CompareCoreMultiMulti<RB>(rb, aeos_), gv1, gv2, gv3, gv4)
			{}
		};

		template <class RB, class GV1=Value,
			class GV2=Value, class GV3=Value, class GV4=Value>
		struct CompareSingleMulti: public Wrapper4Arg<CompareCoreSingleMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
		{
			CompareSingleMulti(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<CompareCoreSingleMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(CompareCoreSingleMulti<RB>(aeos_), gv1, gv2, gv3, gv4)
			{}
			CompareSingleMulti(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<CompareCoreSingleMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(CompareCoreSingleMulti<RB>(rb, aeos_), gv1, gv2, gv3, gv4)
			{}
		};

		template <class RB, class GV1=Value,
			class GV2=Value, class GV3=Value, class GV4=Value>
		struct CompareSingleSingle: public Wrapper4Arg<CompareCoreSingleSingle<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
		{
			CompareSingleSingle(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<CompareCoreSingleSingle<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(CompareCoreSingleSingle<RB>(aeos_), gv1, gv2, gv3, gv4)
			{}
			CompareSingleSingle(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<CompareCoreSingleSingle<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(CompareCoreSingleSingle<RB>(rb, aeos_), gv1, gv2, gv3, gv4)
			{}
		};

		template<bool mp1=true, bool mp2=true>
		struct AllEqualCore {};

		template<>
		struct AllEqualCore<true, true>: public detail::CompareCoreMultiMulti< Equal<> >
		{
			typedef detail::CompareCoreMultiMulti< Equal<> > Parent;
			explicit AllEqualCore(bool aeos_=false):
				detail::CompareCoreMultiMulti< Equal<> >(aeos_) {}

			template<typename It1, typename End1, typename It2, typename End2,
				typename Expr1, typename Expr2, typename Expr3, typename Expr4,
				class Str1, class Str2, class Str3, class Str4>
			Analysis* Analyse(It1 begin1, Expr1 expr1, Str1 str1,
				End1 end1, Expr2 expr2, Str2 str2,
				It2 begin2, Expr3 expr3, Str3 str3,
				End2 end2, Expr4 expr4, Str4 str4,
				bool ais, bool negate=false) const
			{
				return Parent::Analyse(begin1, expr1, str1, end1, expr2, str2,
					begin2, expr3, str3, end2, expr4, str4,
					ais, negate,
					"ranges are equal: ");
			}
		};

		template<>
		struct AllEqualCore<false, true>: public detail::CompareCoreSingleMulti< Equal<> >
		{
			typedef detail::CompareCoreSingleMulti< Equal<> > Parent;
			explicit AllEqualCore(bool aeos_=false):
				detail::CompareCoreSingleMulti< Equal<> >(aeos_) {}

			template<typename It1, typename End1, typename It2, typename End2,
				typename Expr1, typename Expr2, typename Expr3, typename Expr4,
				class Str1, class Str2, class Str3, class Str4>
			Analysis* Analyse(It1 begin1, Expr1 expr1, Str1 str1,
				End1 end1, Expr2 expr2, Str2 str2,
				It2 begin2, Expr3 expr3, Str3 str3,
				End2 end2, Expr4 expr4, Str4 str4,
				bool ais, bool negate=false) const
			{
				return Parent::Analyse(begin1, expr1, str1, end1, expr2, str2,
					begin2, expr3, str3, end2, expr4, str4,
					ais, negate,
					"ranges are equal: ");
			}
		};

		template<>
		struct AllEqualCore<false, false>: public detail::CompareCoreSingleSingle< Equal<> >
		{
			typedef detail::CompareCoreSingleSingle< Equal<> > Parent;
			explicit AllEqualCore(bool aeos_=false):
				detail::CompareCoreSingleSingle< Equal<> >(aeos_) {}

			template<typename It1, typename End1, typename It2, typename End2,
				typename Expr1, typename Expr2, typename Expr3, typename Expr4,
				class Str1, class Str2, class Str3, class Str4>
			Analysis* Analyse(It1 begin1, Expr1 expr1, Str1 str1,
				End1 end1, Expr2 expr2, Str2 str2,
				It2 begin2, Expr3 expr3, Str3 str3,
				End2 end2, Expr4 expr4, Str4 str4,
				bool ais, bool negate=false) const
			{
				return Parent::Analyse(begin1, expr1, str1, end1, expr2, str2,
					begin2, expr3, str3, end2, expr4, str4,
					ais, negate,
					"ranges are equal: ");
			}
		};
	}

	template<bool mp1=true, bool mp2=true>
	struct Compare {};

	RICHBOOL_MAKE_FACTORY(Compare, RICHBOOL_SUFFIX_TT, CompareMultiMulti, That)
	RICHBOOL_MAKE_FACTORY(Compare, RICHBOOL_SUFFIX_FT, CompareSingleMulti, That)
	RICHBOOL_MAKE_FACTORY(Compare, RICHBOOL_SUFFIX_FF, CompareSingleSingle, That)

	template<bool mp1=true, bool mp2=true,
		class GV1=Value, class GV2=Value, class GV3=Value, class GV4=Value>
	struct AllEqual: Wrapper4Arg<detail::AllEqualCore<mp1, mp2>,
		GV1, GV2,GV3, GV4, NoString, NoString, NoString, NoString>
	{
		AllEqual(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(),
			GV3 gv3=GV3(), GV4 gv4=GV4()):
			Wrapper4Arg<detail::AllEqualCore<mp1, mp2>,
				GV1, GV2,GV3, GV4, NoString, NoString, NoString, NoString>
			(detail::AllEqualCore<mp1, mp2>(aeos_), gv1, gv2, gv3, gv4)
		{}
	};

	// unordered comparisons:

	namespace detail
	{
		class CompareUnorderedMessages
		{
		protected:
			static const char *s_msg;
		};

		template <class RB>
		class CompareUnorderedCoreBase: public CustomFunctorCore<true>, public CompareUnorderedMessages
		{
		protected:
			RB rb;
		public:
			explicit CompareUnorderedCoreBase(RB rb_=RB()): rb(rb_) {}

			template<typename It1, typename End1, typename It2, typename End2>
			bool operator()(It1 begin1, End1 end1,
							It2 begin2, End2 end2) const
			{
				return check(begin1, MakeEndCondition(end1), begin2, MakeEndCondition(end2));
			}

			template<typename It1, typename EC1, typename It2, typename EC2>
			bool check(It1 begin1, EC1 ec1,
					   It2 begin2, EC2 ec2) const
			{
				if (!ec1(begin1, 0))
					return !ec2(begin2, 0);
				if (!ec2(begin2, 0))
					return false;

				detail::BoolVector found(ec2.length(begin2), false);

				typename EC1::IndexType idx1=0;
				for (; ec1(begin1, idx1); ++begin1, ++idx1)
				{
					typename EC2::IndexType idx2=0;
					bool matched = false;
					for (It2 it2=begin2; ec2(it2, idx2); ++it2, ++idx2)
					{
						if (!found[idx2] && rb(*begin1, *it2))
						{
							found[idx2] = true;
							matched = true;
							break;
						}
					}
					if (!matched)
						return false;
				}

				for (size_t idx=0; idx<found.size(); ++idx)
					if (!found[idx])
						return false;

				return true;
			}

			template<typename It1, typename EC1, typename It2, typename EC2>
			Analysis::State SafeCheck(It1 begin1, EC1 ec1,
					   It2 begin2, EC2 ec2) const
			{
				if (!ec1(begin1, 0))
					return !ec2(begin2, 0) ? Analysis::Ok : Analysis::NotOk;
				if (!ec2(begin2, 0))
					return Analysis::NotOk;

				detail::BoolVector found(ec2.length(begin2), false);

				typename EC1::IndexType idx1=0;
				for (; ec1(begin1, idx1); ++begin1, ++idx1)
				{
					typename EC2::IndexType idx2=0;
					bool matched = false;
					for (It2 it2=begin2; ec2(it2, idx2); ++it2, ++idx2)
					{
						if (!found[idx2])
						{
							Analysis::State st=rb.SafeCheck(*begin1, *it2);
							if (st==Analysis::Ok)
							{
								found[idx2] = true;
								matched = true;
								break;
							}
							if (st==Analysis::BadValue)
								return Analysis::BadValue;
						}
					}
					if (!matched)
						return Analysis::NotOk;
				}

				for (size_t idx=0; idx<found.size(); ++idx)
					if (!found[idx])
						return Analysis::NotOk;

				return Analysis::Ok;
			}

			const char* GetTextBefore1() const
			{ return s_msg; }
			const char* GetTextBefore2() const
			{ return "-"; }
			const char* GetTextBefore3() const
			{ return " and "; }
			const char* GetTextBefore4() const
			{ return "-"; }
		};

		template <class RB>
		struct CompareUnorderedCoreMulti: public CompareUnorderedCoreBase<RB>
		{
			typedef size_t Points;

			explicit CompareUnorderedCoreMulti(bool aeos_=false):
				aeos(aeos_) {}
			explicit CompareUnorderedCoreMulti(RB rb_, bool aeos_=false):
				CompareUnorderedCoreBase<RB>(rb_), aeos(aeos_) {}

            using CompareUnorderedCoreBase<RB>::rb;

			bool aeos;

			enum { maxPoints = 10 };

			Points GetGood() const
			{
				return maxPoints;
			}

			template<typename It1, typename End1, typename It2, typename End2>
			Points GetPoints(It1 begin1, End1 end1,
						  It2 begin2, End2 end2) const
			{
				return GetPoints_(begin1, MakeEndCondition(end1), begin2, MakeEndCondition(end2));
			}

			template<typename It1, typename EC1, typename It2, typename EC2>
			Points GetPoints_(It1 begin1, EC1 ec1,
						  It2 begin2, EC2 ec2) const
			{
				size_t count=0, good=0;
				if (ec1(begin1, 0))
				{
					detail::BoolVector found(ec2.length(begin2), false);

					typename EC1::IndexType idx1 = 0;
					for (; ec1(begin1, idx1); ++begin1, ++idx1)
					{
						typename EC2::IndexType idx2=0;
						bool matched = false;
						for (It2 it2=begin2; ec2(it2, idx2); ++it2, ++idx2)
							if (!found[idx2] && CompareUnorderedCoreBase<RB>::rb(*begin1, *it2))
							{
								found[idx2] = true;
								matched = true;
								break;
							}
						++count;
						if (matched)
							++good;
					}

					typename EC2::IndexType idx2=0;
					for (It2 it2=begin2; ec2(it2, idx2); ++it2, ++idx2)
						if (!found[idx2])
							++count;

					return (maxPoints*good)/count;
				}
				else
				{
					return ec2(begin2, 0) ? 0 : 10u;
				}
			}

			template <typename It1, typename Expr1, class Str1,
				typename End1, typename Expr2, class Str2,
				typename It2, typename Expr3, class Str3,
				typename End2, typename Expr4, class Str4>
			Analysis* Analyse(It1 begin1, Expr1 expr1, Str1,
							  End1 end1, Expr2 expr2, Str2,
							  It2 begin2, Expr3 expr3, Str3,
							  End2 end2, Expr4 expr4, Str4,
							  bool ais, bool negate=false,
							  const char *msg=0) const
			{
				return Analyse_(begin1, MakeEndCondition(end1), begin2, MakeEndCondition(end2),
					expr1, expr2, expr3, expr4, ais, negate, msg);
			}

		protected:
			template <typename It1, typename Expr1,
				typename EC1, typename Expr2,
				typename It2, typename Expr3,
				typename EC2, typename Expr4>
			Analysis* Analyse_(It1 begin1, EC1 ec1, It2 begin2, EC2 ec2,
				Expr1 expr1, Expr2 expr2,
				Expr3 expr3, Expr4 expr4,
				bool ais, bool negate,
				const char *msg) const
			{
				if (!msg) msg = this->s_msg;

				Analysis::State gst=SafeCheck(begin1, ec1, begin2, ec2);
				bool ok=gst==Analysis::Ok;
				if ((ok!=negate)&&!ais&&(gst!=Analysis::BadValue))
					return 0;

				AnalysisOfRange *an = new AnalysisOfRange(gst, msg,
					MakeExpression(expr1), MakeExpression(expr2), MakeExpression(expr3), MakeExpression(expr4));

				AutoAnalysis autoAn = an;

				if (ec1(begin1, 0))
				{
					detail::BoolVector found(ec2.length(begin2), false);
					typename EC1::IndexType idx1 = 0;

					for (; ec1(begin1, idx1); ++begin1, ++idx1)
					{
						typename EC2::IndexType idx2=0;
						bool matched = false;
						for (It2 it2=begin2; ec2(it2, idx2); ++it2, ++idx2)
						{
							if (!found[idx2])
							{
								Analysis::State st=CompareUnorderedCoreBase<RB>::rb.SafeCheck(*begin1, *it2);
								if (st==Analysis::Ok)
								{
									found[idx2] = true;
									matched = true;
									if (aeos)
										an->Add(CompareUnorderedCoreBase<RB>::rb.Analyse(*begin1, *it2,
											idx1, idx2, true));
									break;
								}
							}
						}
						if (!matched)
							an->Add(
								new Single(0, 2, this->rb.GetString1(*begin1), new IndexExpression(idx1), this->rb.IsValid1(*begin1)));
					}

					typename EC2::IndexType idx2=0;
					for (It2 it2=begin2; ec2(it2, idx2); ++it2, ++idx2)
						if (!found[idx2])
							an->Add(
								new Single(1, 2, this->rb.GetString2(*it2), new IndexExpression(idx2), this->rb.IsValid2(*it2)));
				}
				else
				{
					typename EC2::IndexType idx2=0;
					for (It2 it2=begin2; ec2(it2, idx2); ++it2, ++idx2)
						an->Add(
							new Single(1, 2, this->rb.GetString2(*it2), new IndexExpression(idx2), this->rb.IsValid2(*it2)));
				}
				return autoAn.Release();
			}
		};

		template<class RB>
		struct CompareUnorderedCoreSingle: public CompareUnorderedCoreBase<RB>
		{
			typedef bool Points;
			using CompareUnorderedCoreBase<RB>::rb;

			explicit CompareUnorderedCoreSingle(bool aeos_=false):
				aeos(aeos_) {}
			explicit CompareUnorderedCoreSingle(RB rb_, bool aeos_=false):
				CompareUnorderedCoreBase<RB>(rb_), aeos(aeos_) {}

			bool aeos;

			template<typename It1, typename Expr1, class Str1,
				typename End1, typename Expr2, class Str2,
				typename It2, typename Expr3, class Str3,
				typename End2, typename Expr4, class Str4>
			Analysis* Analyse(It1 begin1, Expr1 expr1, Str1,
							  End1 end1, Expr2 expr2, Str2,
							  It2 begin2, Expr3 expr3, Str3,
							  End2 end2, Expr4 expr4, Str4,
							  bool ais, bool negate=false,
							  const char *msg=0) const
			{
				return Analyse_(begin1, expr1, MakeEndCondition(end1), expr2,
							  begin2, expr3, MakeEndCondition(end2), expr4,
							  ais, negate, msg);
			}

			template<typename It1, typename Expr1,
				typename EC1, typename Expr2,
				typename It2, typename Expr3,
				typename EC2, typename Expr4>
			Analysis* Analyse_(It1 begin1, Expr1 expr1,
							  EC1 ec1, Expr2 expr2,
							  It2 begin2, Expr3 expr3,
							  EC2 ec2, Expr4 expr4,
							  bool ais, bool negate=false,
							  const char *msg=0) const
			{
				if (!msg) msg = this->s_msg;

				bool ok = true;

				AnalysisOfRange *an = new AnalysisOfRange(
					Analysis::NotOk, msg,
					MakeExpression(expr1), MakeExpression(expr2), MakeExpression(expr3), MakeExpression(expr4));

				AutoAnalysis autoAn = an;

				bool bv=false;

				if (ec1(begin1, 0))
				{
					detail::BoolVector found(ec2.length(begin2), false);
					typename EC1::IndexType idx1 = 0;
					for (; ec1(begin1, idx1); ++begin1, ++idx1)
					{
						typename EC2::IndexType idx2=0;
						bool matched = false;
						for (It2 it2=begin2; ec2(it2, idx2); ++it2, ++idx2)
						{
							if (!found[idx2])
							{
								Analysis::State st=rb.SafeCheck(*begin1, *it2);
								if (st==Analysis::Ok)
								{
									found[idx2] = true;
									matched = true;
									if (aeos)
										an->Add(CompareUnorderedCoreBase<RB>::rb.Analyse(*begin1, *it2,
											idx1, idx2, true));
									break;
								}
								if (st==Analysis::Ok)
									bv=true;
							}
						}
						if (!matched)
						{
							an->Add(
								new Single(0, 2, this->rb.GetString1(*begin1), new IndexExpression(idx1), this->rb.IsValid1(*begin1)));
							ok = false;
						}
					}

					typename EC2::IndexType idx2=0;
					for (It2 it2=begin2; ec2(it2, idx2); ++it2, ++idx2)
					{
						if (!found[idx2])
						{
							an->Add(
								new Single(1, 2, this->rb.GetString2(*it2), new IndexExpression(idx2), this->rb.IsValid2(*it2)));
							ok = false;
						}
					}
				}
				else
				{
					typename EC2::IndexType idx2=0;
					for (It2 it2=begin2; ec2(it2, idx2); ++it2, ++idx2)
					{
						an->Add(
							new Single(1, 2, this->rb.GetString2(*it2), new IndexExpression(idx2), this->rb.IsValid2(*it2)));
					}
					ok = idx2==0;
				}

				if (bv)
					an->SetState(Analysis::BadValue);
				else if ((ok!=negate)&&!ais)
					return 0;
				else if (ok)
					an->SetState(Analysis::Ok);
				return autoAn.Release();
			}
		};

		template <class RB, class GV1=Value,
			class GV2=Value, class GV3=Value, class GV4=Value>
		struct CompareUnorderedMulti: public Wrapper4Arg<CompareUnorderedCoreMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
		{
			CompareUnorderedMulti(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<CompareUnorderedCoreMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(CompareUnorderedCoreMulti<RB>(aeos_), gv1, gv2, gv3, gv4)
			{}
			CompareUnorderedMulti(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<CompareUnorderedCoreMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(CompareUnorderedCoreMulti<RB>(rb, aeos_), gv1, gv2, gv3, gv4)
			{}
		};

		template <class RB, class GV1=Value,
			class GV2=Value, class GV3=Value, class GV4=Value>
		struct CompareUnorderedSingle: public Wrapper4Arg<CompareUnorderedCoreSingle<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
		{
			CompareUnorderedSingle(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<CompareUnorderedCoreSingle<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(CompareUnorderedCoreSingle<RB>(aeos_), gv1, gv2, gv3, gv4)
			{}
			CompareUnorderedSingle(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<CompareUnorderedCoreSingle<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(CompareUnorderedCoreSingle<RB>(rb, aeos_), gv1, gv2, gv3, gv4)
			{}
		};

		template<bool mp1=true>
		struct AllEqualUnorderedCore {};

		template<>
		struct AllEqualUnorderedCore<true>: public detail::CompareUnorderedCoreMulti< Equal<> >
		{
			typedef detail::CompareUnorderedCoreMulti< Equal<> > Parent;
			explicit AllEqualUnorderedCore(bool aeos_=false):
				detail::CompareUnorderedCoreMulti< Equal<> >(aeos_) {}

			template<typename It1, typename End1, typename It2, typename End2,
				typename Expr1, typename Expr2, typename Expr3, typename Expr4,
				class Str1, class Str2, class Str3, class Str4>
			Analysis* Analyse(It1 begin1, Expr1 expr1, Str1 str1,
				End1 end1, Expr2 expr2, Str2 str2,
				It2 begin2, Expr3 expr3, Str3 str3,
				End2 end2, Expr4 expr4, Str4 str4,
				bool ais, bool negate=false) const
			{
				return Parent::Analyse(begin1, expr1, str1, end1, expr2, str2,
					begin2, expr3, str3, end2, expr4, str4,
					ais, negate,
					"unordered ranges are equal: ");
			}
		};

		template<>
		struct AllEqualUnorderedCore<false>: public detail::CompareUnorderedCoreSingle< Equal<> >
		{
			typedef detail::CompareUnorderedCoreSingle< Equal<> > Parent;
			explicit AllEqualUnorderedCore(bool aeos_=false):
				detail::CompareUnorderedCoreSingle< Equal<> >(aeos_) {}

			template<typename It1, typename End1, typename It2, typename End2,
				typename Expr1, typename Expr2, typename Expr3, typename Expr4,
				class Str1, class Str2, class Str3, class Str4>
			Analysis* Analyse(It1 begin1, Expr1 expr1, Str1,
				End1 end1, Expr2 expr2, Str2,
				It2 begin2, Expr3 expr3, Str3,
				End2 end2, Expr4 expr4, Str4,
				bool ais, bool negate=false) const
			{
				return Parent::Analyse(begin1, end1, begin2, end2,
					expr1, expr2, expr3, expr4,
					ais, negate,
					"unordered ranges are equal: ");
			}
		};
	}

	template<bool mp=true>
	struct CompareUnordered {};

	RICHBOOL_MAKE_FACTORY(CompareUnordered, RICHBOOL_SUFFIX_T, CompareUnorderedMulti, That)
	RICHBOOL_MAKE_FACTORY(CompareUnordered, RICHBOOL_SUFFIX_F, CompareUnorderedSingle, That)

	template<bool mp1=true,
		class GV1=Value, class GV2=Value, class GV3=Value, class GV4=Value>
	struct AllEqualUnordered: Wrapper4Arg<detail::AllEqualUnorderedCore<mp1>,
		GV1, GV2,GV3, GV4, NoString, NoString, NoString, NoString>
	{
		AllEqualUnordered(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(),
			GV3 gv3=GV3(), GV4 gv4=GV4()):
			Wrapper4Arg<detail::AllEqualUnorderedCore<mp1>,
				GV1, GV2,GV3, GV4, NoString, NoString, NoString, NoString>
			(detail::AllEqualUnorderedCore<mp1>(aeos_), gv1, gv2, gv3, gv4)
		{}
	};

	namespace detail
	{
		class MatchesSubsetOfMessages: public CustomFunctorCore<true>
		{
		public:
			const char* GetTextBefore2() const
			{ return "-"; }
			const char* GetTextBefore3() const
			{ return s_msg; }
			const char* GetTextBefore4() const
			{ return "-"; }
		protected:
			static const char *s_msg;
		};

		template <class RB>
		struct GeneralMatchesSubsetOfCoreMultiMulti: public MatchesSubsetOfMessages
		{
			RB rb;
			typedef size_t Points;

			explicit GeneralMatchesSubsetOfCoreMultiMulti(bool aeos_=false):
				aeos(aeos_) {}
			explicit GeneralMatchesSubsetOfCoreMultiMulti(RB rb_, bool aeos_=false):
				rb(rb_), aeos(aeos_) {}

			bool aeos;

			enum { maxPoints = 10 };

			Points GetGood() const
			{
				return maxPoints;
			}

		protected:
			template<typename It1, class EC1, class FIR>
			bool check(It1 begin1, EC1 ec1,
					   FIR &range) const
			{
				if (!ec1(begin1, 0))
					return true;
				if (range.empty())
					return false;

				typename EC1::IndexType idx1=0;
				for (; ec1(begin1, idx1); ++begin1, ++idx1)
				{
					typename FIR::EIt it2 = range.Find(*begin1);
					if (range.is_end(it2))
						return false;
				}

				return true;
			}

			template<typename It1, class EC1, class Range_>
			Points GetPoints_(It1 begin1, EC1 ec1,
							Range_ &range) const
			{
				size_t good=0;

				typename EC1::IndexType idx1=0;
				for (; ec1(begin1, idx1); ++begin1, ++idx1)
				{
					typename Range_::EIt it2 = range.Find(*begin1);
					if (!range.is_end(it2))
						++good;
				}

				return idx1==0 ? maxPoints : (good*maxPoints)/idx1;
			}

			template<typename It1, typename EC1, class Range_>
			Analysis::State SafeCheck(It1 begin1, EC1 ec1,
					   Range_ &range) const
			{
				if (!ec1(begin1, 0))
					return Analysis::Ok;
				if (range.empty())
					return Analysis::NotOk;

				typename EC1::IndexType idx1=0;
				Analysis::State st=Analysis::Ok;
				for (; ec1(begin1, idx1); ++begin1, ++idx1)
				{
					range.SafeFind(*begin1,st);
					if (st!=Analysis::Ok)
						return st;
				}

				return Analysis::Ok;
			}

			template <typename It1, typename Expr1,
				typename EC1, typename Expr2,
				class Range_, typename Expr3, typename Expr4>
			Analysis* Analyse_(It1 begin1, EC1 ec1, Range_ &range,
				Expr1 expr1, Expr2 expr2, Expr3 expr3, Expr4 expr4,
				bool ais, bool negate,
				const char *msg) const
			{
				Analysis::State gst = SafeCheck(begin1, ec1, range);
				bool ok = gst==Analysis::Ok;
				if ((ok!=negate) && !ais && (gst!=Analysis::BadValue))
					return 0;

				if (!msg) msg = this->s_msg;

				AnalysisOfRange *an = new AnalysisOfRange(
					gst, "",
					MakeExpression(expr1), MakeExpression(expr2),
					msg,
					MakeExpression(expr3), MakeExpression(expr4),
					"");
				range.Reset();

				AutoAnalysis autoAn = an;

				typename EC1::IndexType idx1=0;
				for (; ec1(begin1, idx1); ++begin1, ++idx1)
				{
					if (!rb.IsValid1(*begin1))
					{
						an->Add(new Single(0, 2, rb.GetString1(*begin1),
							MakeExpression(idx1), false));
						continue;
					}
					Analysis::State st=Analysis::Ok;
					typename Range_::EIt it2 = range.SafeFind(*begin1, st);
					if (st==Analysis::Ok)
					{
						if (aeos)
							an->Add(rb.Analyse(*begin1, *it2.it, idx1, it2.idx, true));
					}
					else if (st==Analysis::NotOk)
						an->Add(new Single(0, 2,
							this->rb.GetString1(*begin1),
							new IndexExpression(idx1),
							this->rb.IsValid1(*begin1)));
					else
					{
						an->Add(new Single(1, 2,
							this->rb.GetString2(*it2.it),
							new IndexExpression(it2.idx),
							false));
						break;
					}
				}

				return autoAn.Release();
			}
		};

		template <class RB>
		struct GeneralMatchesSubsetOfCoreSingleMulti: public GeneralMatchesSubsetOfCoreMultiMulti<RB>
		{
			explicit GeneralMatchesSubsetOfCoreSingleMulti(bool aeos_=false):
				GeneralMatchesSubsetOfCoreMultiMulti<RB>(aeos_) {}
			explicit GeneralMatchesSubsetOfCoreSingleMulti(RB rb_, bool aeos_=false):
				GeneralMatchesSubsetOfCoreMultiMulti<RB>(rb_, aeos_) {}

            using GeneralMatchesSubsetOfCoreMultiMulti<RB>::rb;
            using GeneralMatchesSubsetOfCoreMultiMulti<RB>::aeos;

			template<typename It1, typename Expr1,
				typename EC1, typename Expr2,
				class Range_, typename Expr3, typename Expr4>
			Analysis* Analyse_(It1 begin1, EC1 ec1, Range_ &range,
							  Expr1 expr1, Expr2 expr2, Expr3 expr3, Expr4 expr4,
							  bool ais, bool negate=false,
							  const char *msg=0) const
			{
				if (!msg) msg = this->s_msg;

				bool ok=true, bv=false;

				AnalysisOfRange *an = new AnalysisOfRange(
					false, "",
					MakeExpression(expr1), MakeExpression(expr2),
					msg,
					MakeExpression(expr3), MakeExpression(expr4),
					"");

				AutoAnalysis autoAn = an;

				typename EC1::IndexType idx1=0;
				if (range.empty())
				{
					if ((ec1(begin1, idx1)==negate)&&!ais)
						return 0;
					for (; ec1(begin1, idx1); ++begin1, ++idx1)
					{
						bool gv=rb.IsValid1(*begin1);
						if (!gv) bv=true;
						an->Add(new Single(0, 2, rb.GetString1(*begin1),
							MakeExpression(idx1), gv));
					}
					ok = false;
				}
				else
					for (; ec1(begin1, idx1); ++begin1, ++idx1)
					{
						if (!rb.IsValid1(*begin1))
						{
							an->Add(new Single(0, 2, rb.GetString1(*begin1),
								MakeExpression(idx1), false));
							bv=true;
							continue;
						}
						Analysis::State st;
						typename Range_::EIt it2 = range.SafeFind(*begin1, st);
						if (st==Analysis::Ok)
						{
							if (aeos)
								an->Add(rb.Analyse(*begin1, *it2.it, idx1, it2.idx, true));
						}
						else if (st==Analysis::NotOk)
						{
							an->Add(new Single(0, 2,
								this->rb.GetString1(*begin1),
								new IndexExpression(idx1),
								this->rb.IsValid1(*begin1)));
							ok = false;
						}
						else
						{
							an->Add(new Single(1, 2,
								this->rb.GetString2(*it2.it),
								new IndexExpression(it2.idx),
								false));
							bv=true;
							break;
						}
					}

				if (bv)
					an->SetState(Analysis::BadValue);
				else if ((ok!=negate)&&!ais)
					return 0;
				else if (ok)
					an->SetState(Analysis::Ok);
				return autoAn.Release();
			}
		};

		template <class RB>
		struct GeneralMatchesSubsetOfCoreMultiSingle: public MatchesSubsetOfMessages
		{
			typedef bool Points;
			Swap<RB> srb;

			explicit GeneralMatchesSubsetOfCoreMultiSingle(bool aeos_=false):
				aeos(aeos_) {}
			explicit GeneralMatchesSubsetOfCoreMultiSingle(RB rb_, bool aeos_=false):
				srb(rb_), aeos(aeos_) {}

			bool aeos;

		protected:
			template<class Range_, typename It2, typename EC2>
			bool check(Range_ &range,
					   It2 begin2, EC2 ec2) const
			{
				if (!ec2(begin2, 0))
					return false;

				typename EC2::IndexType idx2=0;
				for (; ec2(begin2, idx2); ++begin2, ++idx2)
					range.Find(*begin2);

				return !range.HasUnfound();
			}

			template <class Range_, typename Expr1, typename Expr2,
				typename It2, typename Expr3,
				typename EC2, typename Expr4>
			Analysis* Analyse_(Range_ &range, It2 it2, EC2 ec2,
				Expr1 expr1, Expr2 expr2,
				Expr3 expr3, Expr4 expr4,
				bool ais, bool negate,
				const char *msg) const
			{
				if (!msg) msg = this->s_msg;

				AnalysisOfRange *an = new AnalysisOfRange(
					false, "",
					MakeExpression(expr1), MakeExpression(expr2),
					msg,
					MakeExpression(expr3), MakeExpression(expr4),
					"");

				AutoAnalysis autoAn = an;

				typename EC2::IndexType idx2=0;
				bool bv=false;
				for (; ec2(it2, idx2); ++it2, ++idx2)
				{
					if (!srb.rb.IsValid2(*it2))
					{
						an->Add(new Single(1, 2, srb.rb.GetString2(*it2),
							MakeExpression(idx2), false));
						bv=true;
						continue;
					}
					Analysis::State st;
					typename Range_::EIt it1 = range.SafeFind(*it2, st);
					if (st==Analysis::Ok)
					{
						if (aeos)
							an->Add(this->srb.rb.Analyse(*it1.it, *it2, it1.idx, idx2, true));
					}
					else if (st==Analysis::BadValue)
					{
						an->Add(new Single(0, 2,
							this->srb.rb.GetString1(*it1.it),
							new IndexExpression(it1.idx),
							false));
						bv=true;
						break;
					}
				}

				if (!bv)
				{
					bool ok = true;
					for (typename Range_::EIt it1=range.ebegin(); !range.is_end(it1); ++it1)
						if (!range.found[it1.idx])
						{
							ok = false;
							an->Add(new Single(0, 2,
								this->srb.rb.GetString1(*it1.it),
								new IndexExpression(it1.idx),
								this->srb.rb.IsValid1(*it1.it)));
						}

					if ((ok!=negate)&&!ais)
						return 0;
					else if (ok)
						an->SetState(Analysis::Ok);
				}
				else
					an->SetState(Analysis::BadValue);

				return autoAn.Release();
			}
		};

#define RICHBOOL_MAKE_MATCHER(CLASS, PARENT, PARENT_RB, RANGE, RANGE_RB) \
		template <class RB> \
		struct CLASS: public PARENT<PARENT_RB > \
		{ \
			explicit CLASS(RB rb_, bool aeos_=false): \
				PARENT<PARENT_RB >(rb_, aeos_) {} \
		typedef typename PARENT<PARENT_RB >::Points Points; \
		using PARENT<PARENT_RB >::aeos; \
		using PARENT<PARENT_RB >::rb; \
 \
			template<typename It1, typename End1, typename It2, typename End2> \
			bool operator()(It1 begin1, End1 end1, \
							It2 begin2, End2 end2) const \
			{ \
				RANGE<It2, EndCondition<End2>, RB > range(begin2, EndCondition<End2>(end2), RANGE_RB); \
				return this->check(begin1, MakeEndCondition(end1), range); \
			} \
 \
			template<typename It1, typename End1, typename It2, typename End2> \
			Points GetPoints(It1 begin1, End1 end1, \
						  It2 begin2, End2 end2) const \
			{ \
				RANGE<It2, EndCondition<End2>, RB > range(begin2, EndCondition<End2>(end2), RANGE_RB); \
				return this->GetPoints_(begin1, MakeEndCondition(end1), range); \
			} \
 \
			template <typename It1, typename Expr1, class Str1, \
				typename End1, typename Expr2, class Str2, \
				typename It2, typename Expr3, class Str3, \
				typename End2, typename Expr4, class Str4> \
			Analysis* Analyse(It1 begin1, Expr1 expr1, Str1, \
							  End1 end1, Expr2 expr2, Str2, \
							  It2 begin2, Expr3 expr3, Str3, \
							  End2 end2, Expr4 expr4, Str4, \
							  bool ais, bool negate=false, \
							  const char *msg=0) const \
			{ \
				RANGE<It2,EndCondition<End2>, RB > range(begin2, MakeEndCondition(end2), RANGE_RB); \
				return this->Analyse_(begin1, MakeEndCondition(end1), range, \
					expr1, expr2, expr3, expr4, ais, negate, msg); \
			} \
		};

		RICHBOOL_MAKE_MATCHER(MatchesSubsetOfCoreMultiMulti, GeneralMatchesSubsetOfCoreMultiMulti, RB, FindInMarkedRange, rb)
		RICHBOOL_MAKE_MATCHER(MatchesSubsetOfSortedCoreMultiMulti, GeneralMatchesSubsetOfCoreMultiMulti, detail::SortToEqual<RB>, FindInMarkedSortedRange, rb.GetCore().pr)
		RICHBOOL_MAKE_MATCHER(MatchesSubsetOfCoreSingleMulti, GeneralMatchesSubsetOfCoreSingleMulti, RB, FindInMarkedRange, rb)
		RICHBOOL_MAKE_MATCHER(MatchesSubsetOfSortedCoreSingleMulti, GeneralMatchesSubsetOfCoreSingleMulti, detail::SortToEqual<RB>, FindInMarkedSortedRange, rb.GetCore().pr)

		RICHBOOL_MAKE_MATCHER(MatchesMultiSubsetOfCoreMultiMulti, GeneralMatchesSubsetOfCoreMultiMulti, RB, FindInRange, rb)
		RICHBOOL_MAKE_MATCHER(MatchesMultiSubsetOfSortedCoreMultiMulti, GeneralMatchesSubsetOfCoreMultiMulti, detail::SortToEqual<RB>, FindInSortedRange, rb.GetCore().pr)
		RICHBOOL_MAKE_MATCHER(MatchesMultiSubsetOfCoreSingleMulti, GeneralMatchesSubsetOfCoreSingleMulti, RB, FindInRange, rb)
		RICHBOOL_MAKE_MATCHER(MatchesMultiSubsetOfSortedCoreSingleMulti, GeneralMatchesSubsetOfCoreSingleMulti, detail::SortToEqual<RB>, FindInSortedRange, rb.GetCore().pr)

		RICHBOOL_MAKE_MATCHER(MatchesOrderedSubsetOfCoreMultiMulti, GeneralMatchesSubsetOfCoreMultiMulti, RB, OrderedFindInRange, rb)
		RICHBOOL_MAKE_MATCHER(MatchesOrderedSubsetOfSortedCoreMultiMulti, GeneralMatchesSubsetOfCoreMultiMulti, detail::SortToEqual<RB>, OrderedFindInSortedRange, rb.GetCore().pr)
		RICHBOOL_MAKE_MATCHER(MatchesOrderedSubsetOfCoreSingleMulti, GeneralMatchesSubsetOfCoreSingleMulti, RB, OrderedFindInRange, rb)
		RICHBOOL_MAKE_MATCHER(MatchesOrderedSubsetOfSortedCoreSingleMulti, GeneralMatchesSubsetOfCoreSingleMulti, detail::SortToEqual<RB>, OrderedFindInSortedRange, rb.GetCore().pr)

#define RICHBOOL_MAKE_REVERSE_MATCHER(CLASS, PARENT, RANGE, AEOS_CARG, AEOS_ARG) \
 		template <class RB> \
		struct CLASS: public PARENT \
		{ \
			explicit CLASS(RB rb_, AEOS_CARG): \
				PARENT(rb_, AEOS_ARG) {} \
            using PARENT::srb; \
 \
			template<typename It1, typename End1, typename It2, typename End2> \
			bool operator()(It1 begin1, End1 end1, \
							It2 begin2, End2 end2) const \
			{ \
				RANGE<It1,EndCondition<End1>,Swap<RB> > range(begin1, MakeEndCondition(end1), srb); \
				return this->check(range, begin2, MakeEndCondition(end2)); \
			} \
 \
			template <typename It1, typename Expr1, class Str1, \
				typename End1, typename Expr2, class Str2, \
				typename It2, typename Expr3, class Str3, \
				typename End2, typename Expr4, class Str4> \
			Analysis* Analyse(It1 begin1, Expr1 expr1, Str1, \
							  End1 end1, Expr2 expr2, Str2, \
							  It2 begin2, Expr3 expr3, Str3, \
							  End2 end2, Expr4 expr4, Str4, \
							  bool ais, bool negate=false, \
							  const char *msg=0) const \
			{ \
				RANGE<It1, EndCondition<End1>, Swap<RB> > range(begin1, MakeEndCondition(end1), srb); \
				return Analyse_(range, begin2, MakeEndCondition(end2), \
					expr1, expr2, expr3, expr4, ais, negate, msg); \
			} \
		};

		RICHBOOL_MAKE_REVERSE_MATCHER(MatchesSubsetOfCoreMultiSingle, GeneralMatchesSubsetOfCoreMultiSingle<RB>, FindInMarkedRange, bool aeos_=false, aeos_)
		RICHBOOL_MAKE_REVERSE_MATCHER(MatchesMultiSubsetOfCoreMultiSingle, GeneralMatchesSubsetOfCoreMultiSingle<RB>, FindInMultiMarkedRange, bool =false, false)

		template <class RB, class GV1=Value,
			class GV2=Value, class GV3=Value, class GV4=Value>
		struct MatchesSubsetOfMultiMulti: public Wrapper4Arg<MatchesSubsetOfCoreMultiMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
		{
			MatchesSubsetOfMultiMulti(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<MatchesSubsetOfCoreMultiMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(MatchesSubsetOfCoreMultiMulti<RB>(rb, aeos_), gv1, gv2, gv3, gv4)
			{}
		};

		template <class RB, class GV1=Value,
			class GV2=Value, class GV3=Value, class GV4=Value>
		struct MatchesSubsetOfSortedMultiMulti: public Wrapper4Arg<MatchesSubsetOfSortedCoreMultiMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
		{
			MatchesSubsetOfSortedMultiMulti(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<MatchesSubsetOfSortedCoreMultiMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(MatchesSubsetOfSortedCoreMultiMulti<RB>(rb, aeos_), gv1, gv2, gv3, gv4)
			{}
		};

		template <class RB, class GV1=Value,
			class GV2=Value, class GV3=Value, class GV4=Value>
		struct MatchesSubsetOfSingleMulti: public Wrapper4Arg<MatchesSubsetOfCoreSingleMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
		{
			MatchesSubsetOfSingleMulti(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<MatchesSubsetOfCoreSingleMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(MatchesSubsetOfCoreSingleMulti<RB>(rb, aeos_), gv1, gv2, gv3, gv4)
			{}
		};

		template <class RB, class GV1=Value,
			class GV2=Value, class GV3=Value, class GV4=Value>
		struct MatchesSubsetOfSortedSingleMulti: public Wrapper4Arg<MatchesSubsetOfSortedCoreSingleMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
		{
			MatchesSubsetOfSortedSingleMulti(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<MatchesSubsetOfSortedCoreSingleMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(MatchesSubsetOfSortedCoreSingleMulti<RB>(rb, aeos_), gv1, gv2, gv3, gv4)
			{}
		};

		template <class RB, class GV1=Value,
			class GV2=Value, class GV3=Value, class GV4=Value>
		struct MatchesSubsetOfMultiSingle: public Wrapper4Arg<MatchesSubsetOfCoreMultiSingle<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
		{
			MatchesSubsetOfMultiSingle(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<MatchesSubsetOfCoreMultiSingle<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(MatchesSubsetOfCoreMultiSingle<RB>(rb, aeos_), gv1, gv2, gv3, gv4)
			{}
		};

		template <class RB, class GV1=Value,
			class GV2=Value, class GV3=Value, class GV4=Value>
		struct MatchesMultiSubsetOfMultiMulti: public Wrapper4Arg<MatchesMultiSubsetOfCoreMultiMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
		{
			MatchesMultiSubsetOfMultiMulti(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<MatchesMultiSubsetOfCoreMultiMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(MatchesMultiSubsetOfCoreMultiMulti<RB>(rb, aeos_), gv1, gv2, gv3, gv4)
			{}
		};

		template <class RB, class GV1=Value,
			class GV2=Value, class GV3=Value, class GV4=Value>
		struct MatchesMultiSubsetOfSortedMultiMulti: public Wrapper4Arg<MatchesMultiSubsetOfSortedCoreMultiMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
		{
			MatchesMultiSubsetOfSortedMultiMulti(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<MatchesMultiSubsetOfSortedCoreMultiMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(MatchesMultiSubsetOfSortedCoreMultiMulti<RB>(rb, aeos_), gv1, gv2, gv3, gv4)
			{}
		};

		template <class RB, class GV1=Value,
			class GV2=Value, class GV3=Value, class GV4=Value>
		struct MatchesMultiSubsetOfSingleMulti: public Wrapper4Arg<MatchesMultiSubsetOfCoreSingleMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
		{
			MatchesMultiSubsetOfSingleMulti(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<MatchesMultiSubsetOfCoreSingleMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(MatchesMultiSubsetOfCoreSingleMulti<RB>(rb, aeos_), gv1, gv2, gv3, gv4)
			{}
		};

		template <class RB, class GV1=Value,
			class GV2=Value, class GV3=Value, class GV4=Value>
		struct MatchesMultiSubsetOfSortedSingleMulti: public Wrapper4Arg<MatchesMultiSubsetOfSortedCoreSingleMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
		{
			MatchesMultiSubsetOfSortedSingleMulti(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<MatchesMultiSubsetOfSortedCoreSingleMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(MatchesMultiSubsetOfSortedCoreSingleMulti<RB>(rb, aeos_), gv1, gv2, gv3, gv4)
			{}
		};

		template <class RB, class GV1=Value,
			class GV2=Value, class GV3=Value, class GV4=Value>
		struct MatchesMultiSubsetOfMultiSingle: public Wrapper4Arg<MatchesMultiSubsetOfCoreMultiSingle<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
		{
			MatchesMultiSubsetOfMultiSingle(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<MatchesMultiSubsetOfCoreMultiSingle<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(MatchesMultiSubsetOfCoreMultiSingle<RB>(rb, aeos_), gv1, gv2, gv3, gv4)
			{}
		};

		template <class RB, class GV1=Value,
			class GV2=Value, class GV3=Value, class GV4=Value>
		struct MatchesOrderedSubsetOfMultiMulti: public Wrapper4Arg<MatchesOrderedSubsetOfCoreMultiMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
		{
			MatchesOrderedSubsetOfMultiMulti(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<MatchesOrderedSubsetOfCoreMultiMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(MatchesOrderedSubsetOfCoreMultiMulti<RB>(rb, aeos_), gv1, gv2, gv3, gv4)
			{}
		};

		template <class RB, class GV1=Value,
			class GV2=Value, class GV3=Value, class GV4=Value>
		struct MatchesOrderedSubsetOfSortedMultiMulti: public Wrapper4Arg<MatchesOrderedSubsetOfSortedCoreMultiMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
		{
			MatchesOrderedSubsetOfSortedMultiMulti(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<MatchesOrderedSubsetOfSortedCoreMultiMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(MatchesOrderedSubsetOfSortedCoreMultiMulti<RB>(rb, aeos_), gv1, gv2, gv3, gv4)
			{}
		};

		template <class RB, class GV1=Value,
			class GV2=Value, class GV3=Value, class GV4=Value>
		struct MatchesOrderedSubsetOfSingleMulti: public Wrapper4Arg<MatchesOrderedSubsetOfCoreSingleMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
		{
			MatchesOrderedSubsetOfSingleMulti(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<MatchesOrderedSubsetOfCoreSingleMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(MatchesOrderedSubsetOfCoreSingleMulti<RB>(rb, aeos_), gv1, gv2, gv3, gv4)
			{}
		};

		template <class RB, class GV1=Value,
			class GV2=Value, class GV3=Value, class GV4=Value>
		struct MatchesOrderedSubsetOfSortedSingleMulti: public Wrapper4Arg<MatchesOrderedSubsetOfSortedCoreSingleMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
		{
			MatchesOrderedSubsetOfSortedSingleMulti(RB rb, bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(), GV3 gv3=GV3(), GV4 gv4=GV4()):
				Wrapper4Arg<MatchesOrderedSubsetOfSortedCoreSingleMulti<RB>, GV1, GV2, GV3, GV4, NoString, NoString, NoString, NoString>
					(MatchesOrderedSubsetOfSortedCoreSingleMulti<RB>(rb, aeos_), gv1, gv2, gv3, gv4)
			{}
		};

#define RICHBOOL_MAKE_ISSUBSETOF(CLASS, SUFFIX, PARENT, PARENT_RB, TEXT) \
		template<> \
		struct CLASS SUFFIX: public detail::PARENT<PARENT_RB > \
		{ \
			typedef detail::PARENT<PARENT_RB > Parent; \
			explicit CLASS(bool aeos_=false): \
				detail::PARENT<PARENT_RB >(PARENT_RB(), aeos_) {} \
 \
			template<typename It1, typename End1, typename It2, typename End2, \
				typename Expr1, typename Expr2, typename Expr3, typename Expr4, \
				class Str1, class Str2, class Str3, class Str4> \
			Analysis* Analyse(It1 begin1, Expr1 expr1, Str1 str1, \
				End1 end1, Expr2 expr2, Str2 str2, \
				It2 begin2, Expr3 expr3, Str3 str3, \
				End2 end2, Expr4 expr4, Str4 str4, \
				bool ais, bool negate=false) const \
			{ \
				return Parent::Analyse(begin1, expr1, str1, end1, expr2, str2, \
					begin2, expr3, str3, end2, expr4, str4, \
					ais, negate, \
					TEXT); \
			} \
		};

		template<bool mp1=true, bool mp2=true>
		struct IsSubsetOfCore {};

		RICHBOOL_MAKE_ISSUBSETOF(IsSubsetOfCore, RICHBOOL_SUFFIX_TT, MatchesSubsetOfCoreMultiMulti, Equal<>, " is subset of ")
		RICHBOOL_MAKE_ISSUBSETOF(IsSubsetOfCore, RICHBOOL_SUFFIX_FT, MatchesSubsetOfCoreSingleMulti, Equal<>, " is subset of ")
		RICHBOOL_MAKE_ISSUBSETOF(IsSubsetOfCore, RICHBOOL_SUFFIX_TF, MatchesSubsetOfCoreMultiSingle, Equal<>, " is subset of ")

		template<bool mp1=true>
		struct IsSubsetOfSortedCore {};

		RICHBOOL_MAKE_ISSUBSETOF(IsSubsetOfSortedCore, RICHBOOL_SUFFIX_T, MatchesSubsetOfSortedCoreMultiMulti, Less<>, " is subset of sorted ")
		RICHBOOL_MAKE_ISSUBSETOF(IsSubsetOfSortedCore, RICHBOOL_SUFFIX_F, MatchesSubsetOfSortedCoreSingleMulti, Less<>, " is subset of sorted ")

		template<bool mp1=true, bool mp2=true>
		struct IsMultiSubsetOfCore {};

		RICHBOOL_MAKE_ISSUBSETOF(IsMultiSubsetOfCore, RICHBOOL_SUFFIX_TT, MatchesMultiSubsetOfCoreMultiMulti, Equal<>, " is multisubset of ")
		RICHBOOL_MAKE_ISSUBSETOF(IsMultiSubsetOfCore, RICHBOOL_SUFFIX_FT, MatchesMultiSubsetOfCoreSingleMulti, Equal<>, " is multisubset of ")
		RICHBOOL_MAKE_ISSUBSETOF(IsMultiSubsetOfCore, RICHBOOL_SUFFIX_TF, MatchesMultiSubsetOfCoreMultiSingle, Equal<>, " is multisubset of ")

		template<bool mp1=true>
		struct IsMultiSubsetOfSortedCore {};

		RICHBOOL_MAKE_ISSUBSETOF(IsMultiSubsetOfSortedCore, RICHBOOL_SUFFIX_T, MatchesMultiSubsetOfSortedCoreMultiMulti, Less<>, " is multisubset of sorted ")
		RICHBOOL_MAKE_ISSUBSETOF(IsMultiSubsetOfSortedCore, RICHBOOL_SUFFIX_F, MatchesMultiSubsetOfSortedCoreSingleMulti, Less<>, " is multisubset of sorted ")

		template<bool mp1=true, bool mp2=true>
		struct IsOrderedSubsetOfCore {};

		RICHBOOL_MAKE_ISSUBSETOF(IsOrderedSubsetOfCore, RICHBOOL_SUFFIX_TT, MatchesOrderedSubsetOfCoreMultiMulti, Equal<>, " is ordered subset of ")
		RICHBOOL_MAKE_ISSUBSETOF(IsOrderedSubsetOfCore, RICHBOOL_SUFFIX_FT, MatchesOrderedSubsetOfCoreSingleMulti, Equal<>, " is ordered subset of ")

		template<bool mp1=true>
		struct IsOrderedSubsetOfSortedCore {};

		RICHBOOL_MAKE_ISSUBSETOF(IsOrderedSubsetOfSortedCore, RICHBOOL_SUFFIX_T, MatchesOrderedSubsetOfSortedCoreMultiMulti, Less<>, " is ordered subset of sorted ")
		RICHBOOL_MAKE_ISSUBSETOF(IsOrderedSubsetOfSortedCore, RICHBOOL_SUFFIX_F, MatchesOrderedSubsetOfSortedCoreSingleMulti, Less<>, " is ordered subset of sorted ")
	}

	template<bool mp1=true, bool mp2=true>
	struct MatchesSubsetOf {};

	RICHBOOL_MAKE_FACTORY(MatchesSubsetOf, RICHBOOL_SUFFIX_TT, MatchesSubsetOfMultiMulti, That)
	RICHBOOL_MAKE_FACTORY(MatchesSubsetOf, RICHBOOL_SUFFIX_FT, MatchesSubsetOfSingleMulti, That)
	RICHBOOL_MAKE_FACTORY(MatchesSubsetOf, RICHBOOL_SUFFIX_TF, MatchesSubsetOfMultiSingle, That)

	template<bool mp1=true>
	struct IsSubsetOfCustomSorted {};

	RICHBOOL_MAKE_FACTORY(IsSubsetOfCustomSorted, RICHBOOL_SUFFIX_T, MatchesSubsetOfSortedMultiMulti, By)
	RICHBOOL_MAKE_FACTORY(IsSubsetOfCustomSorted, RICHBOOL_SUFFIX_F, MatchesSubsetOfSortedSingleMulti, By)

	template<bool mp1=true, bool mp2=true,
		class GV1=Value, class GV2=Value, class GV3=Value, class GV4=Value>
	struct IsSubsetOf: Wrapper4Arg<detail::IsSubsetOfCore<mp1, mp2>,
		GV1, GV2,GV3, GV4, NoString, NoString, NoString, NoString>
	{
		IsSubsetOf(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(),
			GV3 gv3=GV3(), GV4 gv4=GV4()):
			Wrapper4Arg<detail::IsSubsetOfCore<mp1, mp2>,
				GV1, GV2,GV3, GV4, NoString, NoString, NoString, NoString>
			(detail::IsSubsetOfCore<mp1, mp2>(aeos_), gv1, gv2, gv3, gv4)
		{}
	};

	template<bool mp1=true,
		class GV1=Value, class GV2=Value, class GV3=Value, class GV4=Value>
	struct IsSubsetOfSorted: Wrapper4Arg<detail::IsSubsetOfSortedCore<mp1>,
		GV1, GV2,GV3, GV4, NoString, NoString, NoString, NoString>
	{
		IsSubsetOfSorted(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(),
			GV3 gv3=GV3(), GV4 gv4=GV4()):
			Wrapper4Arg<detail::IsSubsetOfSortedCore<mp1>,
				GV1, GV2,GV3, GV4, NoString, NoString, NoString, NoString>
			(detail::IsSubsetOfSortedCore<mp1>(aeos_), gv1, gv2, gv3, gv4)
		{}
	};

	template<bool mp1=true, bool mp2=true>
	struct MatchesMultiSubsetOf {};

	RICHBOOL_MAKE_FACTORY(MatchesMultiSubsetOf, RICHBOOL_SUFFIX_TT, MatchesMultiSubsetOfMultiMulti, That)
	RICHBOOL_MAKE_FACTORY(MatchesMultiSubsetOf, RICHBOOL_SUFFIX_FT, MatchesMultiSubsetOfSingleMulti, That)
	RICHBOOL_MAKE_FACTORY(MatchesMultiSubsetOf, RICHBOOL_SUFFIX_TF, MatchesMultiSubsetOfMultiSingle, That)

	template<bool mp1=true>
	struct IsMultiSubsetOfCustomSorted {};

	RICHBOOL_MAKE_FACTORY(IsMultiSubsetOfCustomSorted, RICHBOOL_SUFFIX_T, MatchesMultiSubsetOfSortedMultiMulti, By)
	RICHBOOL_MAKE_FACTORY(IsMultiSubsetOfCustomSorted, RICHBOOL_SUFFIX_F, MatchesMultiSubsetOfSortedSingleMulti, By)

	template<bool mp1=true, bool mp2=true,
		class GV1=Value, class GV2=Value, class GV3=Value, class GV4=Value>
	struct IsMultiSubsetOf: Wrapper4Arg<detail::IsMultiSubsetOfCore<mp1, mp2>,
		GV1, GV2,GV3, GV4, NoString, NoString, NoString, NoString>
	{
		IsMultiSubsetOf(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(),
			GV3 gv3=GV3(), GV4 gv4=GV4()):
			Wrapper4Arg<detail::IsMultiSubsetOfCore<mp1, mp2>,
				GV1, GV2,GV3, GV4, NoString, NoString, NoString, NoString>
			(detail::IsMultiSubsetOfCore<mp1, mp2>(aeos_), gv1, gv2, gv3, gv4)
		{}
	};

	template<bool mp1=true,
		class GV1=Value, class GV2=Value, class GV3=Value, class GV4=Value>
	struct IsMultiSubsetOfSorted: Wrapper4Arg<detail::IsMultiSubsetOfSortedCore<mp1>,
		GV1, GV2,GV3, GV4, NoString, NoString, NoString, NoString>
	{
		IsMultiSubsetOfSorted(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(),
			GV3 gv3=GV3(), GV4 gv4=GV4()):
			Wrapper4Arg<detail::IsMultiSubsetOfSortedCore<mp1>,
				GV1, GV2,GV3, GV4, NoString, NoString, NoString, NoString>
			(detail::IsMultiSubsetOfSortedCore<mp1>(aeos_), gv1, gv2, gv3, gv4)
		{}
	};

	template<bool mp1=true, bool mp2=true>
	struct MatchesOrderedSubsetOf {};

	RICHBOOL_MAKE_FACTORY(MatchesOrderedSubsetOf, RICHBOOL_SUFFIX_TT, MatchesOrderedSubsetOfMultiMulti, That)
	RICHBOOL_MAKE_FACTORY(MatchesOrderedSubsetOf, RICHBOOL_SUFFIX_FT, MatchesOrderedSubsetOfSingleMulti, That)

	template<bool mp1=true>
	struct IsOrderedSubsetOfCustomSorted {};

	RICHBOOL_MAKE_FACTORY(IsOrderedSubsetOfCustomSorted, RICHBOOL_SUFFIX_T, MatchesOrderedSubsetOfSortedMultiMulti, By)
	RICHBOOL_MAKE_FACTORY(IsOrderedSubsetOfCustomSorted, RICHBOOL_SUFFIX_F, MatchesOrderedSubsetOfSortedSingleMulti, By)

	template<bool mp1=true, bool mp2=true,
		class GV1=Value, class GV2=Value, class GV3=Value, class GV4=Value>
	struct IsOrderedSubsetOf: Wrapper4Arg<detail::IsOrderedSubsetOfCore<mp1, mp2>,
		GV1, GV2,GV3, GV4, NoString, NoString, NoString, NoString>
	{
		IsOrderedSubsetOf(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(),
			GV3 gv3=GV3(), GV4 gv4=GV4()):
			Wrapper4Arg<detail::IsOrderedSubsetOfCore<mp1, mp2>,
				GV1, GV2,GV3, GV4, NoString, NoString, NoString, NoString>
			(detail::IsOrderedSubsetOfCore<mp1, mp2>(aeos_), gv1, gv2, gv3, gv4)
		{}
	};

	template<bool mp1=true,
		class GV1=Value, class GV2=Value, class GV3=Value, class GV4=Value>
	struct IsOrderedSubsetOfSorted: Wrapper4Arg<detail::IsOrderedSubsetOfSortedCore<mp1>,
		GV1, GV2,GV3, GV4, NoString, NoString, NoString, NoString>
	{
		IsOrderedSubsetOfSorted(bool aeos_=false, GV1 gv1=GV1(), GV2 gv2=GV2(),
			GV3 gv3=GV3(), GV4 gv4=GV4()):
			Wrapper4Arg<detail::IsOrderedSubsetOfSortedCore<mp1>,
				GV1, GV2,GV3, GV4, NoString, NoString, NoString, NoString>
			(detail::IsOrderedSubsetOfSortedCore<mp1>(aeos_), gv1, gv2, gv3, gv4)
		{}
	};
}

#endif // #ifndef RICH_BOOL_RANGES_H__QM
