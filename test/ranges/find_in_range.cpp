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

using namespace RichBool;

typedef detail::FindInRange<int*, detail::EndCondition<size_t>, Equal<> >
	Range;

typedef detail::FindInRange<int**, detail::EndCondition<size_t>, Equal<Pointer<>, Pointer<> > >
	PtrRange;

typedef detail::FindInSortedRange<int*, detail::EndCondition<size_t>, Less<> >
	SortedRange;

typedef detail::FindInSortedRange<int**, detail::EndCondition<size_t>, Less<Pointer<>, Pointer<> > >
	SortedPtrRange;

typedef detail::FindInSortedRange<int*, detail::EndCondition<size_t>, More<> >
	ReverseSortedRange;

#define END(ARR) detail::EndCondition<size_t>(RICHBOOL_ARRAY_COUNT(ARR))

#define FIND(t, loc) \
	switch (RichBoolTest::GetLevel()) { \
	case 1: \
		s_it=r.Find(t); \
		RB_ASSERT(s_it.it ==a+loc); \
		RB_ASSERT(rbEQUAL(s_it.idx,loc)); \
		break; \
	case 2: \
		s_it=r.SafeFind(t,s_st); \
		RB_ASSERT(s_it.it ==a+loc); \
		RB_ASSERT(rbEQUAL(s_it.idx,loc)); \
		if (loc!=RICHBOOL_ARRAY_COUNT(a)) \
			RB_ASSERT(s_st==RichBool::Analysis::Ok); \
		else \
			RB_ASSERT(s_st==RichBool::Analysis::NotOk); \
		break; \
	default: \
		return; \
	}

#define FIND_SOMEWHERE(t) \
	switch (RichBoolTest::GetLevel()) { \
	case 1: \
		s_it=r.Find(t); \
		RB_ASSERT(s_it.it !=a+RICHBOOL_ARRAY_COUNT(a)); \
		RB_ASSERT(rbDIFF(s_it.idx,RICHBOOL_ARRAY_COUNT(a))); \
		break; \
	case 2: \
		s_it=r.SafeFind(t,s_st); \
		RB_ASSERT(s_it.it !=a+RICHBOOL_ARRAY_COUNT(a)); \
		RB_ASSERT(rbDIFF(s_it.idx,RICHBOOL_ARRAY_COUNT(a))); \
		RB_ASSERT(rbEQUAL(s_st,RichBool::Analysis::Ok)); \
		break; \
	default: \
		return; \
	}

static RichBool::detail::EnhIt<int*, size_t> s_it(0,0);
static RichBool::Analysis::State s_st=RichBool::Analysis::Ok;


// tests for Range::Find(T)

RB_TEST(FindInRange_OneElement_Equal)
{
	int a[] = { 1 };
	Range r(a, END(a));

	FIND(1,0u);
}

RB_TEST(FindInRange_OneElement_Less)
{
	int a[] = { 1 };
	Range r(a, END(a));

	FIND(0,1u);
}

RB_TEST(FindInRange_TwoElements_EqualTo1)
{
	int a[] = { 1, 3 };
	Range r(a, END(a));

	FIND(1,0u);
}

RB_TEST(FindInRange_TwoElements_EqualTo2)
{
	int a[] = { 1, 3 };
	Range r(a, END(a));

	FIND(3,1u);
}

RB_TEST(FindInRange_TwoElements_Less)
{
	int a[] = { 1, 3 };
	Range r(a, END(a));

	FIND(0,2u);
}

RB_TEST(FindInRange_ThreeElements_Less)
{
	int a[] = { 1, 3, 5 };
	Range r(a, END(a));

	FIND(0,3u);
}

RB_TEST(FindInRange_ThreeElements_EqualTo1)
{
	int a[] = { 1, 3, 5 };
	Range r(a, END(a));

	FIND(1,0u);
}

RB_TEST(FindInRange_ThreeElements_Between1And2)
{
	int a[] = { 1, 3, 5 };
	Range r(a, END(a));

	FIND(2,3u);
}

RB_TEST(FindInRange_ThreeElements_EqualTo2)
{
	int a[] = { 1, 3, 5 };
	Range r(a, END(a));

	FIND(3,1u);
}

RB_TEST(FindInRange_ThreeElements_Between2And3)
{
	int a[] = { 1, 3, 5 };
	Range r(a, END(a));

	FIND(4,3u);
}

RB_TEST(FindInRange_ThreeElements_EqualTo3)
{
	int a[] = { 1, 3, 5 };
	Range r(a, END(a));

	FIND(5,2u);
}

RB_TEST(FindInRange_ThreeElements_More)
{
	int a[] = { 1, 3, 5 };
	Range r(a, END(a));

	FIND(6,3u);
}

RB_TEST(FindInRange_ThreeElements_MultipleSearch)
{
	int a[] = { 1, 3, 5 };
	Range r(a, END(a));

	FIND(1,0u);

	FIND(3,1u);
}

RB_TEST(FindInRange_TwoElements_OneAndTwoSame_MultipleSearch)
{
	int a[] = { 1, 1 };
	Range r(a, END(a));

	FIND_SOMEWHERE(1);
}

RB_TEST(FindInRange_ThreeElements_OneAndTwoSame)
{
	int a[] = { 1, 1, 5 };
	Range r(a, END(a));

	FIND_SOMEWHERE(1);

	FIND(5,2u);
}

RB_TEST(FindInRange_ThreeElements_TwoAndThreeSame_MultipleSearch)
{
	int a[] = { 0, 1, 1 };
	Range r(a, END(a));

	FIND_SOMEWHERE(1);

	FIND(0,0u);
}


// tests for Range::Find(T) with dereferencing

RB_TEST(FindInRangePtr_OneElement_Equal)
{
	int a[] = { 1 };
	int *b[] = { &a[0] };
	PtrRange r(b, END(b));

	int c = 1;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b);
	RB_ASSERT(s_st==RichBool::Analysis::Ok);
}

RB_TEST(FindInRangePtr_OneElement_Less)
{
	int a[] = { 1 };
	int *b[] = { &a[0] };
	PtrRange r(b, END(b));

	int c = 0;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b+1);
	RB_ASSERT(s_st==RichBool::Analysis::NotOk);
}

RB_TEST(FindInRangePtr_OneElement_NullPtr)
{
	int *b[] = { 0 };
	PtrRange r(b, END(b));

	int c = 2;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b);
	RB_ASSERT(s_st==RichBool::Analysis::BadValue);
}


// tests for SortedRange::Find(T)


RB_TEST(FindInSorted_OneElement_Equal)
{
	int a[] = { 1 };
	SortedRange r(a, END(a));

	FIND(1,0u);
}

RB_TEST(FindInSorted_OneElement_Less)
{
	int a[] = { 1 };
	SortedRange r(a, END(a));

	FIND(0,1u);
}

RB_TEST(FindInSorted_OneElement_More)
{
	int a[] = { 1 };
	SortedRange r(a, END(a));

	FIND(2,1u);
}

RB_TEST(FindInSorted_TwoElements_EqualTo1)
{
	int a[] = { 1, 3 };
	SortedRange r(a, END(a));

	FIND(1,0u);
}

RB_TEST(FindInSorted_TwoElements_EqualTo2)
{
	int a[] = { 1, 3 };
	SortedRange r(a, END(a));

	FIND(3,1u);
}

RB_TEST(FindInSorted_TwoElements_Less)
{
	int a[] = { 1, 3 };
	SortedRange r(a, END(a));

	FIND(0,2u);
}

RB_TEST(FindInSorted_TwoElements_InBetween)
{
	int a[] = { 1, 3 };
	SortedRange r(a, END(a));

	FIND(2,2u);
}

RB_TEST(FindInSorted_TwoElements_More)
{
	int a[] = { 1, 3 };
	SortedRange r(a, END(a));

	FIND(4,2u);
}

RB_TEST(FindInSorted_ThreeElements_Less)
{
	int a[] = { 1, 3, 5 };
	SortedRange r(a, END(a));

	FIND(0,3u);
}

RB_TEST(FindInSorted_ThreeElements_EqualTo1)
{
	int a[] = { 1, 3, 5 };
	SortedRange r(a, END(a));

	FIND(1,0u);
}

RB_TEST(FindInSorted_ThreeElements_Between1And2)
{
	int a[] = { 1, 3, 5 };
	SortedRange r(a, END(a));

	FIND(2,3u);
}

RB_TEST(FindInSorted_ThreeElements_EqualTo2)
{
	int a[] = { 1, 3, 5 };
	SortedRange r(a, END(a));

	FIND(3,1u);
}

RB_TEST(FindInSorted_ThreeElements_Between2And3)
{
	int a[] = { 1, 3, 5 };
	SortedRange r(a, END(a));

	FIND(4,3u);
}

RB_TEST(FindInSorted_ThreeElements_EqualTo3)
{
	int a[] = { 1, 3, 5 };
	SortedRange r(a, END(a));

	FIND(5,2u);
}

RB_TEST(FindInSorted_ThreeElements_More)
{
	int a[] = { 1, 3, 5 };
	SortedRange r(a, END(a));

	FIND(6,3u);
}

RB_TEST(FindInSorted_ThreeElements_MultipleSearch)
{
	int a[] = { 1, 3, 5 };
	SortedRange r(a, END(a));

	FIND(1,0u);

	FIND(3,1u);
}

RB_TEST(FindInSorted_TwoElements_OneAndTwoSame_MultipleSearch)
{
	int a[] = { 1, 1 };
	SortedRange r(a, END(a));

	FIND_SOMEWHERE(1);
}

RB_TEST(FindInSorted_ThreeElements_OneAndTwoSame)
{
	int a[] = { 1, 1, 5 };
	SortedRange r(a, END(a));

	FIND_SOMEWHERE(1);

	FIND(5,2u);
}

RB_TEST(FindInSorted_ThreeElements_TwoAndThreeSame_MultipleSearch)
{
	int a[] = { 0, 1, 1 };
	SortedRange r(a, END(a));

	FIND_SOMEWHERE(1);

	FIND(0,0u);
}

RB_TEST(FindInSorted_ThreeElements_AllSame_MultipleSearch)
{
	int a[] = { 1, 1, 1 };
	SortedRange r(a, END(a));

	FIND_SOMEWHERE(1);
}

RB_TEST(FindInSorted_ThreeElements_More_MultipleSearch)
{
	int a[] = { 3, 2, 1 };
	ReverseSortedRange r(a, END(a));

	FIND(1,2u);

	FIND(2,1u);

	FIND(3,0u);
}

// tests for SortedRange::Find(T) with dereferencing

RB_TEST(FindInSortedPtr_OneElement_Equal)
{
	int a[] = { 1 };
	int *b[] = { &a[0] };
	SortedPtrRange r(b, END(b));

	int c = 1;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b);
	RB_ASSERT(s_st==RichBool::Analysis::Ok);
}

RB_TEST(FindInSortedPtr_OneElement_Less)
{
	int a[] = { 1 };
	int *b[] = { &a[0] };
	SortedPtrRange r(b, END(b));

	int c = 0;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b+1);
	RB_ASSERT(s_st==RichBool::Analysis::NotOk);
}

RB_TEST(FindInSortedPtr_OneElement_More)
{
	int a[] = { 1 };
	int *b[] = { &a[0] };
	SortedPtrRange r(b, END(b));

	int c = 2;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b+1);
	RB_ASSERT(s_st==RichBool::Analysis::NotOk);
}

RB_TEST(FindInSortedPtr_OneElement_NullPtr)
{
	int *b[] = { 0 };
	SortedPtrRange r(b, END(b));

	int c = 2;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b);
	RB_ASSERT(s_st==RichBool::Analysis::BadValue);
}
