//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_XCONTAINERS_H__QM
#define RICH_BOOL_XCONTAINERS_H__QM

#include "getvalue.hpp"
#include "ranges.hpp"

namespace RichBool
{
	// Rich Boolean classes working on one container
	template<class Algorithm>
	struct InXContainerCore: public CustomFunctorCore<true>
	{
		Algorithm algorithm;

		explicit InXContainerCore(Algorithm algorithm_):
			algorithm(algorithm_)
		{}

		template <class Container>
		bool operator()(const Container &cont) const
		{
			return algorithm(begin(cont), size(cont));
		}

		template <class Container, typename Expr, class Str>
		Analysis* Analyse(const Container &cont,
			Expr expr, Str ,
			bool analyseOnSucceed, bool negate=false) const
		{
			return algorithm.Analyse(
				begin(cont), size(cont),
				MakeExpression(expr), (const char*)0,
				analyseOnSucceed, negate);
		}
	};

	template<class Algorithm, class GetValue1_=Value, class Stringize_=NoString>
	struct InXContainer: public Wrapper1Arg<InXContainerCore<Algorithm>, GetValue1_, Stringize_>
	{
		explicit InXContainer(Algorithm a=Algorithm(), GetValue1_ gv1=GetValue1_()):
			Wrapper1Arg<InXContainerCore<Algorithm>, GetValue1_, Stringize_>
				(InXContainerCore<Algorithm>(a), gv1)
		{}
	};

	template<class Algorithm>
	InXContainer<Algorithm> MakeInXContainer(Algorithm algorithm)
	{
		return InXContainer<Algorithm>(algorithm);
	}

	//////////////////////////////////////////////////////
	// Rich Boolean classes working on two containers

	template<class Algorithm>
	class InXContainersCore: public CustomFunctorCore<true>
	{
	protected:
		Algorithm algorithm;
	public:
		typedef typename Algorithm::Points Points;

		explicit InXContainersCore(Algorithm algorithm_=Algorithm()):
			algorithm(algorithm_)
		{}

		template <class Container1, class Container2>
		bool operator()(const Container1 &cont1, const Container2 &cont2) const
		{
			return algorithm(
				begin(cont1), size(cont1),
				begin(cont2), size(cont2)
			);
		}

		template <class Container1, class Container2>
		Points GetPoints(const Container1 &cont1, const Container2 &cont2) const
		{
			return algorithm.GetPoints(
				begin(cont1), size(cont1),
				begin(cont2), size(cont2));
		}

		Points GetGood() const
		{
			return algorithm.GetGood();
		}

		template <class Container1, typename Expr1, class Str1,
			class Container2, typename Expr2, class Str2>
		Analysis* Analyse(const Container1 &cont1, Expr1 expr1, Str1 ,
			const Container2 &cont2, Expr2 expr2, Str2 ,
			bool analyseOnSucceed, bool negate=false) const
		{
			return algorithm.Analyse(
				begin(cont1), size(cont1),
				begin(cont2), size(cont2),
				MakeExpression(expr1), (const char*)0,
				MakeExpression(expr2), (const char*)0,
				analyseOnSucceed, negate);
		}
		const char* GetTextBefore2() const
		{ return ", "; }
	};

	template<class Algorithm, class GetValue1_=Value, class GetValue2_=Value, class Stringize1_=NoString, class Stringize2_=NoString>
	struct InXContainers: public Wrapper2Arg<InXContainersCore<Algorithm>, GetValue1_, GetValue2_, Stringize1_, Stringize2_>
	{
		explicit InXContainers(Algorithm a=Algorithm(), GetValue1_ gv1=GetValue1_(), GetValue2_ gv2=GetValue2_()):
			Wrapper2Arg<InXContainersCore<Algorithm>, GetValue1_, GetValue2_, Stringize1_, Stringize2_>
				(InXContainersCore<Algorithm>(a), gv1, gv2)
		{}
	};

	template<class Algorithm>
	InXContainers<Algorithm>
	MakeInXContainers(Algorithm alg)
	{
		return InXContainers<Algorithm>(alg);
	}






	template<class Algorithm>
	class InXNContainersCore: public CustomFunctorCore<true>
	{
	protected:
		Algorithm algorithm;
	public:
		typedef typename Algorithm::Points Points;

		explicit InXNContainersCore(Algorithm algorithm_=Algorithm()):
			algorithm(algorithm_)
		{}

		template <class Container1, class Container2>
		bool operator()(const Container1 &cont1, const Container2 &cont2) const
		{
			return algorithm(
				begin(cont1), size(cont1),
				cont2.begin(), cont2.size()
			);
		}

		template <class Container1, class Container2>
		Points GetPoints(const Container1 &cont1, const Container2 &cont2) const
		{
			return algorithm.GetPoints(
				begin(cont1), size(cont1),
				cont2.begin(), cont2.size());
		}

		Points GetGood() const
		{
			return algorithm.GetGood();
		}

		template <class Container1, typename Expr1, class Str1,
			class Container2, typename Expr2, class Str2>
		Analysis* Analyse(const Container1 &cont1, Expr1 expr1, Str1 ,
			const Container2 &cont2, Expr2 expr2, Str2 ,
			bool analyseOnSucceed, bool negate=false) const
		{
			return algorithm.Analyse(
				begin(cont1), size(cont1),
				cont2.begin(), cont2.size(),
				MakeExpression(expr1), (const char*)0,
				MakeExpression(expr2), (const char*)0,
				analyseOnSucceed, negate);
		}
		const char* GetTextBefore2() const
		{ return ", "; }
	};

	template<class Algorithm, class GetValue1_=Value, class GetValue2_=Value, class Stringize1_=NoString, class Stringize2_=NoString>
	struct InXNContainers: public Wrapper2Arg<InXNContainersCore<Algorithm>, GetValue1_, GetValue2_, Stringize1_, Stringize2_>
	{
		explicit InXNContainers(Algorithm a=Algorithm(), GetValue1_ gv1=GetValue1_(), GetValue2_ gv2=GetValue2_()):
			Wrapper2Arg<InXNContainersCore<Algorithm>, GetValue1_, GetValue2_, Stringize1_, Stringize2_>
				(InXNContainersCore<Algorithm>(a), gv1, gv2)
		{}
	};

	template<class Algorithm>
	InXNContainers<Algorithm>
	MakeInXNContainers(Algorithm alg)
	{
		return InXNContainers<Algorithm>(alg);
	}

	template<class Algorithm>
	class InNXContainersCore: public CustomFunctorCore<true>
	{
	protected:
		Algorithm algorithm;
	public:
		typedef typename Algorithm::Points Points;

		explicit InNXContainersCore(Algorithm algorithm_=Algorithm()):
			algorithm(algorithm_)
		{}

		template <class Container1, class Container2>
		bool operator()(const Container1 &cont1, const Container2 &cont2) const
		{
			return algorithm(
				cont1.begin(), cont1.size(),
				begin(cont2), size(cont2)
			);
		}

		template <class Container1, class Container2>
		Points GetPoints(const Container1 &cont1, const Container2 &cont2) const
		{
			return algorithm.GetPoints(
				cont1.begin(), cont1.size(),
				begin(cont2), size(cont2));
		}

		Points GetGood() const
		{
			return algorithm.GetGood();
		}

		template <class Container1, typename Expr1, class Str1,
			class Container2, typename Expr2, class Str2>
		Analysis* Analyse(const Container1 &cont1, Expr1 expr1, Str1 ,
			const Container2 &cont2, Expr2 expr2, Str2 ,
			bool analyseOnSucceed, bool negate=false) const
		{
			return algorithm.Analyse(
				cont1.begin(), cont1.size(),
				begin(cont2), size(cont2),
				MakeExpression(expr1), (const char*)0,
				MakeExpression(expr2), (const char*)0,
				analyseOnSucceed, negate);
		}
		const char* GetTextBefore2() const
		{ return ", "; }
	};

	template<class Algorithm, class GetValue1_=Value, class GetValue2_=Value, class Stringize1_=NoString, class Stringize2_=NoString>
	struct InNXContainers: public Wrapper2Arg<InNXContainersCore<Algorithm>, GetValue1_, GetValue2_, Stringize1_, Stringize2_>
	{
		explicit InNXContainers(Algorithm a=Algorithm(), GetValue1_ gv1=GetValue1_(), GetValue2_ gv2=GetValue2_()):
			Wrapper2Arg<InNXContainersCore<Algorithm>, GetValue1_, GetValue2_, Stringize1_, Stringize2_>
				(InNXContainersCore<Algorithm>(a), gv1, gv2)
		{}
	};

	template<class Algorithm>
	InNXContainers<Algorithm>
	MakeInNXContainers(Algorithm alg)
	{
		return InNXContainers<Algorithm>(alg);
	}





	template <bool multiPass1=true, bool multiPass2=true,
		class GetValue1_=Value, class GetValue2_=Value>
	struct XContainersEqual:
		public InXContainers<AllEqual<multiPass1, multiPass2>, GetValue1_, GetValue2_>
	{
		explicit XContainersEqual(bool analyseElementsOnSuccess=false):
			InXContainers<AllEqual<multiPass1, multiPass2>, GetValue1_, GetValue2_>
				(AllEqual<multiPass1, multiPass2>(analyseElementsOnSuccess))
		{}
	};
}


// Rich Boolean macros working on one container
#define rbIN_XCONTAINER(cont, algorithm) \
	rb1_RB(cont, RichBool::MakeInXContainer(algorithm))
#define rbvIN_XCONTAINER(cont, algorithm) \
	rbv1_1_RB(cont, RichBool::MakeInXContainer(algorithm))


// Rich Boolean macros working on two containers
#define rbIN_XCONTAINERS(cont1, cont2, algorithm) \
	rb2_RB(cont1, cont2, RichBool::MakeInXContainers(algorithm))
#define rbvIN_XCONTAINERS(cont1, cont2, algorithm) \
	rbv2_1_RB(cont1, cont2, RichBool::MakeInXContainers(algorithm))


// Rich Boolean macros working on a container and a range
#define rbIN_XCONTAINER_RANGE(cont, b, e, algorithm) \
	rb4_RB_IMPL(begin(cont), #cont, end(cont), (const char*)0, b, #b, e, #e, algorithm)

// Rich Boolean macros working on a range and a container
#define rbIN_RANGE_XCONTAINER(b, e, cont, algorithm) \
	rb4_RB_IMPL(b, #b, e, #e, begin(cont), #cont, end(cont), (const char*)0, algorithm)
#define rbvIN_RANGE_XCONTAINER(b, e, cont, algorithm) \
	rbv4_1_RB_IMPL(b, #b, e, #e, begin(cont), #cont, end(cont), (const char*)0, algorithm)

// Rich Boolean macros working on a container and an array
#define rbIN_XCONTAINER_ARRAY(cont, arr, algorithm) \
	rb2_RB_IMPL(cont, #cont, RichBool::detail::MakeConstArray(arr, RICHBOOL_ARRAY_COUNT(arr)), #arr, \
		RichBool::MakeInXNContainers(algorithm))
#define rbvIN_XCONTAINER_ARRAY(cont, arr, algorithm) \
	rbv2_1_RB_IMPL(cont, #cont, RichBool::detail::MakeConstArray(arr, RICHBOOL_ARRAY_COUNT(arr)), #arr, \
		RichBool::MakeInXNContainers(algorithm))

// Rich Boolean macros working on an array and a container
#define rbIN_ARRAY_XCONTAINER(arr, cont, algorithm) \
	rb2_RB_IMPL(RichBool::detail::MakeConstArray(arr, RICHBOOL_ARRAY_COUNT(arr)), #arr, cont, #cont, \
		RichBool::MakeInNXContainers(algorithm))
#define rbvIN_ARRAY_XCONTAINER(arr, cont, algorithm) \
	rbv4_1_RB_IMPL(arr, #arr, RICHBOOL_ARRAY_COUNT(arr), 0, begin(cont), #cont, \
		size(cont), 0, algorithm)

// deprecated rich booleans:
#define rbIN_XCONTAINER_ARG(cont, algorithm, argument) \
	rb1_RB(cont, RichBool::MakeInXContainer((algorithm).Tie(argument)))
#define rbIN_XCONTAINERS_ARG(cont1, cont2, algorithm, argument) \
	rb2_RB(cont1, cont2, RichBool::MakeInXContainers((algorithm).Tie(argument)))
#define rbIN_XCONTAINER_ARRAY_ARG(cont, arr, algorithm, argument) \
	rb2_RB_IMPL(cont, #cont, RichBool::detail::MakeConstArray(arr, RICHBOOL_ARRAY_COUNT(arr)), #arr, \
		RichBool::MakeInXNContainers((algorithm).Tie(argument)))

#endif // #ifndef RICH_BOOL_XCONTAINERS_H__QM
