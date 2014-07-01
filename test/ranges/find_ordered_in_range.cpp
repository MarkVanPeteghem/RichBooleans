//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#if defined(_MSC_VER)
	#pragma warning(disable: 4786)
#endif

#include "richbool/richbool.hpp"
#include "rbtest.hpp"

#include "stub_container.hpp"

using namespace RichBool;

#if !RICHBOOL_IS_MSVC6_RELEASE

	#define FIND(t, loc) \
		if (RichBoolTest::GetLevel()==1) { \
			s_it=r.Find(t); \
		} else if (RichBoolTest::GetLevel()==2) { \
			s_it=r.SafeFind(t,s_st); \
			if (loc!=RICHBOOL_ARRAY_COUNT(a)) \
				RB_ASSERT(s_st==RichBool::Analysis::Ok); \
			else \
				RB_ASSERT(s_st==RichBool::Analysis::NotOk); \
		} else return; \
		RB_ASSERT(s_it.it ==a+loc); \
		RB_ASSERT(rbEQUAL(s_it.idx,loc));

	#define FIND_SC(t, loc) \
		if (RichBoolTest::GetLevel()==1) { \
			it_sc=r.Find(t); \
		} else if (RichBoolTest::GetLevel()==2) { \
			it_sc=r.SafeFind(t,s_st); \
			if (loc!=a.size()) \
				RB_ASSERT(s_st==RichBool::Analysis::Ok); \
			else \
				RB_ASSERT(s_st==RichBool::Analysis::NotOk); \
		} else return; \
		RB_ASSERT(rbEQUAL(it_sc.it.idx(),loc)); \
		RB_ASSERT(rbEQUAL(it_sc.idx,loc));

#else

	#define FIND(t, loc) \
		if (RichBoolTest::GetLevel()==1) { \
			s_it=r.Find(t); \
		} else if (RichBoolTest::GetLevel()==2) { \
			s_it=r.SafeFind(t,s_st); \
			if (loc!=RICHBOOL_ARRAY_COUNT(a)) \
				RB_ASSERT(s_st==RichBool::Analysis::Ok); \
			else \
				RB_ASSERT(s_st==RichBool::Analysis::NotOk); \
		} else return; \
		RB_ASSERT(s_it.it ==a+loc); \
		RB_ASSERT((s_it.idx==loc));

	#define FIND_SC(t, loc) \
		if (RichBoolTest::GetLevel()==1) { \
			it_sc=r.Find(t); \
		} else if (RichBoolTest::GetLevel()==2) { \
			it_sc=r.SafeFind(t,s_st); \
			if (loc!=a.size()) \
				RB_ASSERT(s_st==RichBool::Analysis::Ok); \
			else \
				RB_ASSERT(s_st==RichBool::Analysis::NotOk); \
		} else return; \
		RB_ASSERT((it_sc.it.idx()==loc)); \
		RB_ASSERT((it_sc.idx==loc));

#endif

#define END(ARR) detail::EndCondition<size_t>(RICHBOOL_ARRAY_COUNT(ARR))

static RichBool::detail::EnhIt<int*, size_t> s_it(0,0);
static RichBool::Analysis::State s_st=RichBool::Analysis::Ok;


///////////////////////////////////////////////////////////
// tests for OrderedFindInRange

typedef detail::OrderedFindInRange<int*, detail::EndCondition<size_t>, Equal<> >
	OrderedInRange;

typedef detail::OrderedFindInRange<int**, detail::EndCondition<size_t>, Equal<Pointer<>, Pointer<> > >
	PtrOrderedInRange;

RB_TEST(OrderedFindInRange_OneElement_Equal)
{
	int a[] = { 1 };
	OrderedInRange r(a, END(a));

	FIND(1,0u);
}

RB_TEST(OrderedFindInRange_OneElement_Less)
{
	int a[] = { 1 };
	OrderedInRange r(a, END(a));

	FIND(0,1u);
}

RB_TEST(OrderedFindInRange_TwoElements_EqualTo1)
{
	int a[] = { 1, 3 };
	OrderedInRange r(a, END(a));

	FIND(1,0u);
}

RB_TEST(OrderedFindInRange_TwoElements_EqualTo2)
{
	int a[] = { 1, 3 };
	OrderedInRange r(a, END(a));

	FIND(3,1u);
}

RB_TEST(OrderedFindInRange_TwoElements_Less)
{
	int a[] = { 1, 3 };
	OrderedInRange r(a, END(a));

	FIND(0,2u);
}

RB_TEST(OrderedFindInRange_ThreeElements_Less)
{
	int a[] = { 1, 3, 5 };
	OrderedInRange r(a, END(a));

	FIND(0,3u);
}

RB_TEST(OrderedFindInRange_ThreeElements_EqualTo1)
{
	int a[] = { 1, 3, 5 };
	OrderedInRange r(a, END(a));

	FIND(1,0u);
}

RB_TEST(OrderedFindInRange_ThreeElements_EqualTo2)
{
	int a[] = { 1, 3, 5 };
	OrderedInRange r(a, END(a));

	FIND(3,1u);
}

RB_TEST(OrderedFindInRange_ThreeElements_EqualTo3)
{
	int a[] = { 1, 3, 5 };
	OrderedInRange r(a, END(a));

	FIND(5,2u);
}

RB_TEST(OrderedFindInRange_ThreeElements_MultipleSearch)
{
	int a[] = { 1, 3, 5 };
	OrderedInRange r(a, END(a));

	FIND(1,0u);

	FIND(3,1u);
}

RB_TEST(OrderedFindInRange_ThreeElements_MultipleSearch_PrevNotFound)
{
	int a[] = { 1, 3, 5 };
	OrderedInRange r(a, END(a));

	FIND(3,1u);

	FIND(1,3u);
}

RB_TEST(OrderedFindInRange_ThreeElements_MultipleSearch_PrevNotFound2)
{
	int a[] = { 1, 3, 5 };
	OrderedInRange r(a, END(a));

	FIND(5,2u);

	FIND(1,3u);
	FIND(3,3u);
}

RB_TEST(OrderedFindInRange_TwoElements_OneAndTwoSame_MultipleSearch)
{
	int a[] = { 1, 1 };
	OrderedInRange r(a, END(a));

	FIND(1,0u);
	FIND(1,1u);
	FIND(1,2u);
}

RB_TEST(OrderedFindInRange_ThreeElements_OneAndTwoSame)
{
	int a[] = { 1, 1, 5 };
	OrderedInRange r(a, END(a));

	FIND(1,0u);

	FIND(5,2u);

	FIND(1,3u);
}

RB_TEST(OrderedFindInRange_ThreeElements_MultipleSearch_Reset)
{
	int a[] = { 1, 3, 5 };
	OrderedInRange r(a, END(a));

	FIND(3,1u);

	r.Reset();

	FIND(1,0u);
}

RB_TEST(OrderedFindInRange_ThreeElements_FindAfterUnfound)
{
	int a[] = { 1, 3, 5 };
	OrderedInRange r(a, END(a));

	FIND(1,0u);
	FIND(2,3u);
	FIND(3,1u);
	FIND(2,3u);
	FIND(5,2u);
}


// tests for OrderedFindInRange::Find(T) with dereferencing

RB_TEST(OrderedFindInRangePtr_OneElement_Equal)
{
	int a[] = { 1 };
	int *b[] = { &a[0] };
	PtrOrderedInRange r(b, END(b));

	int c = 1;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b);
	RB_ASSERT(s_st==RichBool::Analysis::Ok);
}

RB_TEST(OrderedFindInRangePtr_OneElement_Less)
{
	int a[] = { 1 };
	int *b[] = { &a[0] };
	PtrOrderedInRange r(b, END(b));

	int c = 0;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b+1);
	RB_ASSERT(s_st==RichBool::Analysis::NotOk);
}

RB_TEST(OrderedFindInRangePtr_OneElement_NullPtr)
{
	int *b[] = { 0 };
	PtrOrderedInRange r(b, END(b));

	int c = 2;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b);
	RB_ASSERT(s_st==RichBool::Analysis::BadValue);
}


///////////////////////////////////////////////////////////
// tests for OrderedFindInRangeSP

typedef detail::OrderedFindInRangeSP<StubContainer::GenIterator<int>, detail::EndCondition<StubContainer::GenIterator<int> >, Equal<> >
	OrderedInRangeSP;

typedef detail::OrderedFindInRangeSP<int**, detail::EndCondition<size_t>, Equal<Pointer<>, Pointer<> > >
	PtrOrderedInRangeSP;

RB_TEST(OrderedFindInRangeSP_OneElement_Equal)
{
	StubContainer a(1);
	RichBool::detail::EnhIt<StubContainer::GenIterator<int>, size_t> it_sc(a.begin(),0);
	OrderedInRangeSP r(a.begin(), a.end());

	FIND_SC(1,0u);
}

RB_TEST(OrderedFindInRangeSP_OneElement_Less)
{
	StubContainer a(1);
	RichBool::detail::EnhIt<StubContainer::GenIterator<int>, size_t> it_sc(a.begin(),0);
	OrderedInRangeSP r(a.begin(), a.end());

	FIND_SC(0,1u);
}

RB_TEST(OrderedFindInRangeSP_TwoElements_EqualTo1)
{
	StubContainer a(1, 3);
	RichBool::detail::EnhIt<StubContainer::GenIterator<int>, size_t> it_sc(a.begin(),0);
	OrderedInRangeSP r(a.begin(), a.end());

	FIND_SC(1,0u);
}

RB_TEST(OrderedFindInRangeSP_TwoElements_EqualTo2)
{
	StubContainer a(1, 3);
	RichBool::detail::EnhIt<StubContainer::GenIterator<int>, size_t> it_sc(a.begin(),0);
	OrderedInRangeSP r(a.begin(), a.end());

	FIND_SC(3,1u);
}

RB_TEST(OrderedFindInRangeSP_TwoElements_Less)
{
	StubContainer a(1, 3);
	RichBool::detail::EnhIt<StubContainer::GenIterator<int>, size_t> it_sc(a.begin(),0);
	OrderedInRangeSP r(a.begin(), a.end());

	FIND_SC(0,2u);
}

RB_TEST(OrderedFindInRangeSP_ThreeElements_Less)
{
	StubContainer a(1, 3, 5);
	RichBool::detail::EnhIt<StubContainer::GenIterator<int>, size_t> it_sc(a.begin(),0);
	OrderedInRangeSP r(a.begin(), a.end());

	FIND_SC(0,3u);
}

RB_TEST(OrderedFindInRangeSP_ThreeElements_EqualTo1)
{
	StubContainer a(1, 3, 5);
	RichBool::detail::EnhIt<StubContainer::GenIterator<int>, size_t> it_sc(a.begin(),0);
	OrderedInRangeSP r(a.begin(), a.end());

	FIND_SC(1,0u);
}

RB_TEST(OrderedFindInRangeSP_ThreeElements_EqualTo2)
{
	StubContainer a(1, 3, 5);
	RichBool::detail::EnhIt<StubContainer::GenIterator<int>, size_t> it_sc(a.begin(),0);
	OrderedInRangeSP r(a.begin(), a.end());

	FIND_SC(3,1u);
}

RB_TEST(OrderedFindInRangeSP_ThreeElements_EqualTo3)
{
	StubContainer a(1, 3, 5);
	RichBool::detail::EnhIt<StubContainer::GenIterator<int>, size_t> it_sc(a.begin(),0);
	OrderedInRangeSP r(a.begin(), a.end());

	FIND_SC(5,2u);
}

RB_TEST(OrderedFindInRangeSP_ThreeElements_MultipleSearch)
{
	StubContainer a(1, 3, 5);
	RichBool::detail::EnhIt<StubContainer::GenIterator<int>, size_t> it_sc(a.begin(),0);
	OrderedInRangeSP r(a.begin(), a.end());

	FIND_SC(1,0u);

	FIND_SC(3,1u);
}

RB_TEST(OrderedFindInRangeSP_ThreeElements_MultipleSearch_PrevNotFound)
{
	StubContainer a(1, 3, 5);
	RichBool::detail::EnhIt<StubContainer::GenIterator<int>, size_t> it_sc(a.begin(),0);
	OrderedInRangeSP r(a.begin(), a.end());

	FIND_SC(3,1u);

	FIND_SC(1,3u);
}

RB_TEST(OrderedFindInRangeSP_ThreeElements_MultipleSearch_PrevNotFound2)
{
	StubContainer a(1, 3, 5);
	RichBool::detail::EnhIt<StubContainer::GenIterator<int>, size_t> it_sc(a.begin(),0);
	OrderedInRangeSP r(a.begin(), a.end());

	FIND_SC(5,2u);

	FIND_SC(1,3u);
	FIND_SC(3,3u);
}

RB_TEST(OrderedFindInRangeSP_TwoElements_OneAndTwoSame_MultipleSearch)
{
	StubContainer a(1, 1);
	RichBool::detail::EnhIt<StubContainer::GenIterator<int>, size_t> it_sc(a.begin(),0);
	OrderedInRangeSP r(a.begin(), a.end());

	FIND_SC(1,0u);
	FIND_SC(1,1u);
	FIND_SC(1,2u);
}

RB_TEST(OrderedFindInRangeSP_ThreeElements_OneAndTwoSame)
{
	StubContainer a(1, 1, 5);
	RichBool::detail::EnhIt<StubContainer::GenIterator<int>, size_t> it_sc(a.begin(),0);
	OrderedInRangeSP r(a.begin(), a.end());

	FIND_SC(1,0u);

	FIND_SC(5,2u);

	FIND_SC(1,3u);
}

RB_TEST(OrderedFindInRangeSP_ThreeElements_FindNotAfterUnfound)
{
	StubContainer a(1, 3, 5);
	RichBool::detail::EnhIt<StubContainer::GenIterator<int>, size_t> it_sc(a.begin(),0);
	OrderedInRangeSP r(a.begin(), a.end());

	FIND_SC(1,0u);
	FIND_SC(2,3u);
	FIND_SC(3,3u);
	FIND_SC(2,3u);
	FIND_SC(5,3u);
}


// tests for OrderedFindInRangeSP::Find(T) with dereferencing

RB_TEST(OrderedFindInRangeSPPtr_OneElement_Equal)
{
	int a[] = { 1 };
	int *b[] = { &a[0] };
	PtrOrderedInRangeSP r(b, END(b));

	int c = 1;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b);
	RB_ASSERT(s_st==RichBool::Analysis::Ok);
}

RB_TEST(OrderedFindInRangeSPPtr_OneElement_Less)
{
	int a[] = { 1 };
	int *b[] = { &a[0] };
	PtrOrderedInRangeSP r(b, END(b));

	int c = 0;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b+1);
	RB_ASSERT(s_st==RichBool::Analysis::NotOk);
}

RB_TEST(OrderedFindInRangeSPPtr_OneElement_NullPtr)
{
	int *b[] = { 0 };
	PtrOrderedInRangeSP r(b, END(b));

	int c = 2;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b);
	RB_ASSERT(s_st==RichBool::Analysis::BadValue);
}


///////////////////////////////////////////////////////////
// tests for OrderedFindInSortedRange

typedef detail::OrderedFindInSortedRange<int*, detail::EndCondition<size_t>, Less<> >
	OrderedInSortedRange;

typedef detail::OrderedFindInSortedRange<int**, detail::EndCondition<size_t>, Less<Pointer<>, Pointer<> > >
	PtrOrderedInSortedRange;

RB_TEST(OrderedFindInSortedRange_OneElement_Equal)
{
	int a[] = { 1 };
	OrderedInSortedRange r(a, END(a));

	FIND(1,0u);
}

RB_TEST(OrderedFindInSortedRange_OneElement_Less)
{
	int a[] = { 1 };
	OrderedInSortedRange r(a, END(a));

	FIND(0,1u);
}

RB_TEST(OrderedFindInSortedRange_TwoElements_EqualTo1)
{
	int a[] = { 1, 3 };
	OrderedInSortedRange r(a, END(a));

	FIND(1,0u);
}

RB_TEST(OrderedFindInSortedRange_TwoElements_EqualTo2)
{
	int a[] = { 1, 3 };
	OrderedInSortedRange r(a, END(a));

	FIND(3,1u);
}

RB_TEST(OrderedFindInSortedRange_TwoElements_Less)
{
	int a[] = { 1, 3 };
	OrderedInSortedRange r(a, END(a));

	FIND(0,2u);
}

RB_TEST(OrderedFindInSortedRange_ThreeElements_Less)
{
	int a[] = { 1, 3, 5 };
	OrderedInSortedRange r(a, END(a));

	FIND(0,3u);
}

RB_TEST(OrderedFindInSortedRange_ThreeElements_EqualTo1)
{
	int a[] = { 1, 3, 5 };
	OrderedInSortedRange r(a, END(a));

	FIND(1,0u);
}

RB_TEST(OrderedFindInSortedRange_ThreeElements_EqualTo2)
{
	int a[] = { 1, 3, 5 };
	OrderedInSortedRange r(a, END(a));

	FIND(3,1u);
}

RB_TEST(OrderedFindInSortedRange_ThreeElements_EqualTo3)
{
	int a[] = { 1, 3, 5 };
	OrderedInSortedRange r(a, END(a));

	FIND(5,2u);
}

RB_TEST(OrderedFindInSortedRange_ThreeElements_MultipleSearch)
{
	int a[] = { 1, 3, 5 };
	OrderedInSortedRange r(a, END(a));

	FIND(1,0u);

	FIND(3,1u);
}

RB_TEST(OrderedFindInSortedRange_ThreeElements_MultipleSearch_PrevNotFound)
{
	int a[] = { 1, 3, 5 };
	OrderedInSortedRange r(a, END(a));

	FIND(3,1u);

	FIND(1,3u);
}

RB_TEST(OrderedFindInSortedRange_ThreeElements_MultipleSearch_PrevNotFound2)
{
	int a[] = { 1, 3, 5 };
	OrderedInSortedRange r(a, END(a));

	FIND(5,2u);

	FIND(1,3u);
	FIND(3,3u);
}

RB_TEST(OrderedFindInSortedRange_TwoElements_OneAndTwoSame_MultipleSearch)
{
	int a[] = { 1, 1 };
	OrderedInSortedRange r(a, END(a));

	FIND(1,0u);
	FIND(1,1u);
	FIND(1,2u);
}

RB_TEST(OrderedFindInSortedRange_ThreeElements_OneAndTwoSame)
{
	int a[] = { 1, 1, 5 };
	OrderedInSortedRange r(a, END(a));

	FIND(1,0u);

	FIND(5,2u);

	FIND(1,3u);
}

RB_TEST(OrderedFindInSortedRange_ThreeElements_MultipleSearch_Reset)
{
	int a[] = { 1, 3, 5 };
	OrderedInSortedRange r(a, END(a));

	FIND(3,1u);

	r.Reset();

	FIND(1,0u);
}

RB_TEST(OrderedFindInSortedRange_ThreeElements_FindAfterUnfound)
{
	int a[] = { 1, 3, 5 };
	OrderedInSortedRange r(a, END(a));

	FIND(1,0u);
	FIND(2,3u);
	FIND(3,1u);
	FIND(2,3u);
	FIND(5,2u);
}


// tests for OrderedFindInRange::Find(T) with dereferencing

RB_TEST(OrderedFindInSortedRangePtr_OneElement_Equal)
{
	int a[] = { 1 };
	int *b[] = { &a[0] };
	PtrOrderedInSortedRange r(b, END(b));

	int c = 1;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b);
	RB_ASSERT(s_st==RichBool::Analysis::Ok);
}

RB_TEST(OrderedFindInSortedRangePtr_OneElement_Less)
{
	int a[] = { 1 };
	int *b[] = { &a[0] };
	PtrOrderedInSortedRange r(b, END(b));

	int c = 0;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b+1);
	RB_ASSERT(s_st==RichBool::Analysis::NotOk);
}

RB_TEST(OrderedFindInSortedRangePtr_OneElement_NullPtr)
{
	int *b[] = { 0 };
	PtrOrderedInSortedRange r(b, END(b));

	int c = 2;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b);
	RB_ASSERT(s_st==RichBool::Analysis::BadValue);
}
