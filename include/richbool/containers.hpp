//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_CONTAINERS_H__QM
#define RICH_BOOL_CONTAINERS_H__QM

#include "richbool/pair.hpp"
#include "richbool/functors.hpp"

#ifdef RICHBOOL_INITIALIZER_LISTS
#include <initializer_list>
#endif

namespace RichBool
{
	// Rich Boolean classes working on one container
	template<class Algorithm>
	struct InContainerCore: public CustomFunctorCore<true>
	{
		Algorithm algorithm;

		explicit InContainerCore(Algorithm algorithm_):
			algorithm(algorithm_)
		{}

		template <class Container>
		bool operator()(const Container &cont) const
		{
			return algorithm(cont.begin(), cont.size());
		}

		template <class Container, typename Expr, class Str>
		Analysis* Analyse(const Container &cont,
			Expr expr, Str ,
			bool analyseOnSucceed, bool negate=false) const
		{
			return algorithm.Analyse(
				cont.begin(), cont.size(),
				MakeExpression(expr), (const char*)0,
				analyseOnSucceed, negate);
		}
	};

	template<class Algorithm, class GetValue1_=Value, class Stringize_=NoString>
	struct InContainer: public Wrapper1Arg<InContainerCore<Algorithm>, GetValue1_, Stringize_>
	{
		explicit InContainer(Algorithm a=Algorithm(), GetValue1_ gv1=GetValue1_()):
			Wrapper1Arg<InContainerCore<Algorithm>, GetValue1_, Stringize_>
				(InContainerCore<Algorithm>(a), gv1)
		{}
	};

	template<class Algorithm>
	InContainer<Algorithm> MakeInContainer(Algorithm algorithm)
	{
		return InContainer<Algorithm>(algorithm);
	}

	//////////////////////////////////////////////////////
	// Rich Boolean classes working on two containers

	template<class Algorithm>
	class InContainersCore: public CustomFunctorCore<true>
	{
	protected:
		Algorithm algorithm;
	public:
		typedef typename Algorithm::Points Points;

		explicit InContainersCore(Algorithm algorithm_=Algorithm()):
			algorithm(algorithm_)
		{}

		template <class Container1, class Container2>
		bool operator()(const Container1 &cont1, const Container2 &cont2) const
		{
			return algorithm(
				cont1.begin(), cont1.end(),
				cont2.begin(), cont2.end()
			);
		}

		template <class Container1, class Container2>
		Points GetPoints(const Container1 &cont1, const Container2 &cont2) const
		{
			return algorithm.GetPoints(
				cont1.begin(), cont1.size(),
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
				cont1.begin(), cont1.end(),
				cont2.begin(), cont2.end(),
				MakeExpression(expr1), (const char*)0,
				MakeExpression(expr2), (const char*)0,
				analyseOnSucceed, negate);
		}
		const char* GetTextBefore2() const
		{ return ", "; }
	};

	template<class Algorithm, class GetValue1_=Value, class GetValue2_=Value, class Stringize1_=NoString, class Stringize2_=NoString>
	struct InContainers: public Wrapper2Arg<InContainersCore<Algorithm>, GetValue1_, GetValue2_, Stringize1_, Stringize2_>
	{
		explicit InContainers(Algorithm a=Algorithm(), GetValue1_ gv1=GetValue1_(), GetValue2_ gv2=GetValue2_()):
			Wrapper2Arg<InContainersCore<Algorithm>, GetValue1_, GetValue2_, Stringize1_, Stringize2_>
				(InContainersCore<Algorithm>(a), gv1, gv2)
		{}
	};

	template<class Algorithm>
	InContainers<Algorithm>
	MakeInContainers(Algorithm alg)
	{
		return InContainers<Algorithm>(alg);
	}

	template <bool multiPass1=true, bool multiPass2=true,
		class GetValue1_=Value, class GetValue2_=Value>
	struct ContainersEqual:
		public InContainers<AllEqual<multiPass1, multiPass2>, GetValue1_, GetValue2_>
	{
		explicit ContainersEqual(bool analyseElementsOnSuccess=false):
			InContainers<AllEqual<multiPass1, multiPass2>, GetValue1_, GetValue2_>
				(AllEqual<multiPass1, multiPass2>(analyseElementsOnSuccess))
		{}
	};

	struct MapsEqual:
		public InContainers<detail::CompareMultiMulti<EqualPair>, Value, Value>
	{
		MapsEqual(bool analyseElementsOnSuccess_=false):
			InContainers<detail::CompareMultiMulti<EqualPair>, Value, Value>(
				detail::CompareMultiMulti<EqualPair>(analyseElementsOnSuccess_))
		{}
	};

	namespace detail
	{
#ifdef RICHBOOL_INITIALIZER_LISTS
        template<typename T>
        std::initializer_list<T> MakeInitializerList(const std::initializer_list<T>& il)
        {
            return il;
        }
#endif

        template <typename It>
        class Range
        {
            It m_begin;
            It m_end;
        public:
            Range(It b, It e)
                : m_begin(b)
                , m_end(e)
            {}
            It begin() const
            {
                return m_begin;
            }
            It end() const
            {
                return m_end;
            }
        };

        template <typename It>
        Range<It> MakeRange(It begin, It end)
        {
            return Range<It>(begin, end);
        }

	}
}


// Rich Boolean macros working on one container
#define rbIN_CONTAINER(cont, algorithm) \
	rb1_RB(cont, RichBool::MakeInContainer(algorithm))
#define rbvIN_CONTAINER(cont, algorithm) \
	rbv1_1_RB(cont, RichBool::MakeInContainer(algorithm))


// Rich Boolean macros working on two containers
#define rbIN_CONTAINERS(cont1, cont2, algorithm) \
	rb2_RB(cont1, cont2, RichBool::MakeInContainers(algorithm))
#define rbvIN_CONTAINERS(cont1, cont2, algorithm) \
	rbv2_1_RB(cont1, cont2, RichBool::MakeInContainers(algorithm))


// Rich Boolean macros working on a container and a range
#define rbIN_CONTAINER_RANGE(cont, b, e, algorithm) \
	rb2_RB_IMPL(cont, #cont, RichBool::detail::MakeConstRange(b, e), "[" #b "," #e ")", RichBool::MakeInContainers(algorithm))

// Rich Boolean macros working on a range and a container
#define rbIN_RANGE_CONTAINER(b, e, cont, algorithm) \
	rb2_RB_IMPL(RichBool::detail::MakeConstRange(b, e), "[" #b "," #e ")", cont, #cont, RichBool::MakeInContainers(algorithm))
#define rbvIN_RANGE_CONTAINER(b, e, cont, algorithm) \
	rbv2_1_RB_IMPL(RichBool::detail::MakeConstRange(b, e), "[" #b "," #e ")", cont, #cont, RichBool::MakeInContainers(algorithm))

// Rich Boolean macros working on a container and an array
#define rbIN_CONTAINER_ARRAY(cont, arr, algorithm) \
	rb2_RB_IMPL(cont, #cont, RichBool::detail::MakeConstArray(arr, RICHBOOL_ARRAY_COUNT(arr)), #arr, \
		RichBool::MakeInContainers(algorithm))
#define rbvIN_CONTAINER_ARRAY(cont, arr, algorithm) \
	rbv2_1_RB_IMPL(cont, #cont, RichBool::detail::MakeConstArray(arr, RICHBOOL_ARRAY_COUNT(arr)), #arr, \
		RichBool::MakeInContainers(algorithm))

// Rich Boolean macros working on an array and a container
#define rbIN_ARRAY_CONTAINER(arr, cont, algorithm) \
	rb2_RB_IMPL(RichBool::detail::MakeConstArray(arr, RICHBOOL_ARRAY_COUNT(arr)), #arr, cont, #cont, \
		RichBool::MakeInContainers(algorithm))
#define rbvIN_ARRAY_CONTAINER(arr, cont, algorithm) \
	rbv4_1_RB_IMPL(arr, #arr, RICHBOOL_ARRAY_COUNT(arr), 0, cont.begin(), #cont, \
		cont.end(), 0, algorithm)


#ifdef RICHBOOL_INITIALIZER_LISTS
    #define rbIN_VALUES(il, algorithm) \
        rb1_RB_IMPL(detail::MakeInitializerList il, #il, RichBool::MakeInContainer(algorithm))
    #define rbvIN_VALUES(il, algorithm) \
        rbv1_1_RB_IMPL(detail::MakeInitializerList il, #il, RichBool::MakeInContainer(algorithm))

    #define rbIN_VALUES_VALUES(il1, il2, algorithm) \
        rb2_RB_IMPL(detail::MakeInitializerList il1, #il1, detail::MakeInitializerList il2, #il2, RichBool::MakeInContainers(algorithm))
    #define rbvIN_VALUES_VALUES(il1, il2, algorithm) \
        rbv2_1_RB_IMPL(detail::MakeInitializerList il1, #il1, detail::MakeInitializerList il2, #il2, RichBool::MakeInContainers(algorithm))

    #define rbIN_VALUES_RANGE(il, b, e, algorithm) \
        rb2_RB_IMPL(detail::MakeInitializerList il, #il, RichBool::detail::MakeRange(b, e), #b "-" #e, RichBool::MakeInContainers(algorithm))
    #define rbvIN_VALUES_RANGE(il, b, e, algorithm) \
        rbv2_1_RB_IMPL(detail::MakeInitializerList il, #il, RichBool::detail::MakeRange(b, e), #b "-" #e, RichBool::MakeInContainers(algorithm))

    #define rbIN_RANGE_VALUES(b, e, il, algorithm) \
        rb2_RB_IMPL(RichBool::detail::MakeRange(b, e), #b "-" #e, detail::MakeInitializerList il, #il, RichBool::MakeInContainers(algorithm))
    #define rbvIN_RANGE_VALUES(b, e, il, algorithm) \
        rbv2_1_RB_IMPL(RichBool::detail::MakeRange(b, e), #b "-" #e, detail::MakeInitializerList il, #il, RichBool::MakeInContainers(algorithm))

    #define rbIN_VALUES_ARRAY(il, arr, algorithm) \
        rb2_RB_IMPL(detail::MakeInitializerList il, #il, RichBool::detail::MakeConstArray(arr, RICHBOOL_ARRAY_COUNT(arr)), #arr, RichBool::MakeInContainers(algorithm))
    #define rbvIN_VALUES_ARRAY(il, arr, algorithm) \
        rbv2_1_RB_IMPL(detail::MakeInitializerList il, #il, RichBool::detail::MakeConstArray(arr, RICHBOOL_ARRAY_COUNT(arr)), #arr, RichBool::MakeInContainers(algorithm))

    #define rbIN_ARRAY_VALUES(arr, il, algorithm) \
        rb2_RB_IMPL(RichBool::detail::MakeConstArray(arr, RICHBOOL_ARRAY_COUNT(arr)), #arr, detail::MakeInitializerList il, #il, RichBool::MakeInContainers(algorithm))
    #define rbvIN_ARRAY_VALUES(arr, il, algorithm) \
        rbv2_1_RB_IMPL(RichBool::detail::MakeConstArray(arr, RICHBOOL_ARRAY_COUNT(arr)), #arr, detail::MakeInitializerList il, #il, RichBool::MakeInContainers(algorithm))

    #define rbIN_VALUES_CONTAINER(il, cont, algorithm) \
        rb2_RB_IMPL(detail::MakeInitializerList il, #il, cont, #cont, \
            RichBool::MakeInContainers(algorithm))
    #define rbvIN_VALUES_CONTAINER(il, cont, algorithm) \
        rbv2_1_RB_IMPL(detail::MakeInitializerList il, #il, cont, #cont, RichBool::MakeInContainers(algorithm))
    #define rbIN_CONTAINER_VALUES(cont, il, algorithm) \
        rb2_RB_IMPL(cont, #cont, detail::MakeInitializerList il, #il, \
            RichBool::MakeInContainers(algorithm))
    #define rbvIN_CONTAINER_VALUES(cont, il, algorithm) \
        rbv2_1_RB_IMPL(cont, #cont, detail::MakeInitializerList il, #il, RichBool::MakeInContainers(algorithm))
#endif




// deprecated rich booleans:
#define rbIN_CONTAINER_ARG(cont, algorithm, argument) \
	rb1_RB(cont, RichBool::MakeInContainer((algorithm).Tie(argument)))
#define rbIN_CONTAINERS_ARG(cont1, cont2, algorithm, argument) \
	rb2_RB(cont1, cont2, RichBool::MakeInContainers((algorithm).Tie(argument)))
#define rbIN_CONTAINER_ARRAY_ARG(cont, arr, algorithm, argument) \
	rb2_RB_IMPL(cont, #cont, RichBool::detail::MakeConstArray(arr, RICHBOOL_ARRAY_COUNT(arr)), #arr, \
		RichBool::MakeInContainers((algorithm).Tie(argument)) )

#endif // #ifndef RICH_BOOL_CONTAINERS_H__QM
