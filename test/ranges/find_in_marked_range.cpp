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

typedef RichBool::detail::FindInMarkedRange<int*, RichBool::detail::EndCondition<size_t>, RichBool::Equal<> >
	MarkedRange;

typedef RichBool::detail::FindInMarkedRange<int**, RichBool::detail::EndCondition<size_t>, RichBool::Equal<RichBool::Pointer<>, RichBool::Pointer<> > >
	MarkedPtrRange;

typedef RichBool::detail::FindInMarkedSortedRange<int*, RichBool::detail::EndCondition<size_t>, RichBool::Less<> >
	SortedMarkedRange;

typedef RichBool::detail::FindInMarkedSortedRange<int**, RichBool::detail::EndCondition<size_t>, RichBool::Less<RichBool::Pointer<>, RichBool::Pointer<> > >
	SortedMarkedPtrRange;

typedef RichBool::detail::FindInMarkedSortedRange<int*, RichBool::detail::EndCondition<size_t>, RichBool::More<> >
	ReverseSortedMarkedRange;

#define END(ARR) RichBool::detail::EndCondition<size_t>(RICHBOOL_ARRAY_COUNT(ARR))

#if !RICHBOOL_IS_MSVC6_RELEASE

	#define FIND_AND_MARK(t, loc) \
		switch (RichBoolTest::GetLevel()) { \
		case 1: \
			s_it=r.Find(t); \
			RB_ASSERT(s_it.it ==a+loc); \
			RB_ASSERT(rbEQUAL(s_it.idx,loc)); \
			if (loc!=RICHBOOL_ARRAY_COUNT(a)) \
			{ \
				RB_ASSERT((bool)r.found[loc]); \
			} \
			break; \
		case 2: \
			s_it=r.SafeFind(t,s_st); \
			RB_ASSERT(s_it.it ==a+loc); \
			RB_ASSERT(rbEQUAL(s_it.idx,loc)); \
			if (loc!=RICHBOOL_ARRAY_COUNT(a)) \
				RB_ASSERT((bool)r.found[loc]); \
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

#else

	#define FIND_AND_MARK(t, loc) \
		if (RichBoolTest::GetLevel()==1) { \
			s_it=r.Find(t); \
		} else if (RichBoolTest::GetLevel()==2) { \
			s_it=r.SafeFind(t,s_st); \
		} else return; \
		RB_ASSERT(s_it.it ==a+loc); \
		RB_ASSERT(s_it.idx==loc);

	#define FIND_SOMEWHERE(t) \
		if (RichBoolTest::GetLevel()==1) { \
			s_it=r.Find(t); \
			RB_ASSERT(s_it.it !=a+RICHBOOL_ARRAY_COUNT(a)); \
			RB_ASSERT((s_it.idx!=RICHBOOL_ARRAY_COUNT(a))); \
		} else if (RichBoolTest::GetLevel()==2) { \
			s_it=r.SafeFind(t,st); \
			RB_ASSERT(s_it.it !=a+RICHBOOL_ARRAY_COUNT(a)); \
			RB_ASSERT((s_it.idx!=RICHBOOL_ARRAY_COUNT(a))); \
			RB_ASSERT((s_st==RichBool::Analysis::Ok)); \
		} else return;

#endif

static RichBool::detail::EnhIt<int*, size_t> s_it(0,0);
static RichBool::Analysis::State s_st=RichBool::Analysis::Ok;


// tests for equal_pred_safe

RB_TEST(equal_pred_safe_Less)
{
	s_st=RichBool::detail::equal_pred_safe(1, 2, RichBool::Less<>());
	RB_ASSERT(s_st==RichBool::Analysis::NotOk);
}

RB_TEST(equal_pred_safe_Equal)
{
	s_st=RichBool::detail::equal_pred_safe(1, 1, RichBool::Less<>());
	RB_ASSERT(s_st==RichBool::Analysis::Ok);
}

RB_TEST(equal_pred_safe_More)
{
	s_st=RichBool::detail::equal_pred_safe(2, 1, RichBool::Less<>());
	RB_ASSERT(s_st==RichBool::Analysis::NotOk);
}

RB_TEST(equal_pred_safe_FirstIsBad)
{
	int *p=0;
	s_st=RichBool::detail::equal_pred_safe(*p, 1, RichBool::Less<>());
	RB_ASSERT(s_st==RichBool::Analysis::BadValue);
}

RB_TEST(equal_pred_safe_SecondIsBad)
{
	int *p=0;
	s_st=RichBool::detail::equal_pred_safe(1, *p, RichBool::Less<>());
	RB_ASSERT(s_st==RichBool::Analysis::BadValue);
}



// tests for MarkedRange::Find(T)

RB_TEST(OneElement_Equal)
{
	int a[] = { 1 };
	MarkedRange r(a, END(a));

	FIND_AND_MARK(1,0u);
}

RB_TEST(OneElement_Less)
{
	int a[] = { 1 };
	MarkedRange r(a, END(a));
	FIND_AND_MARK(0,1u);
}

RB_TEST(TwoElements_EqualTo1)
{
	int a[] = { 1, 3 };
	MarkedRange r(a, END(a));
	FIND_AND_MARK(1, 0u);
	RB_ASSERT(!r.found[1]);
}

RB_TEST(TwoElements_EqualTo2)
{
	int a[] = { 1, 3 };
	MarkedRange r(a, END(a));
	FIND_AND_MARK(3, 1u);
	RB_ASSERT((bool)r.found[1]);
}

RB_TEST(TwoElements_Less)
{
	int a[] = { 1, 3 };
	MarkedRange r(a, END(a));
	FIND_AND_MARK(0, 2u);
	RB_ASSERT(!r.found[1]);
}

RB_TEST(ThreeElements_Less)
{
	int a[] = { 1, 3, 5 };
	MarkedRange r(a, END(a));
	FIND_AND_MARK(0, 3u);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(ThreeElements_EqualTo1)
{
	int a[] = { 1, 3, 5 };
	MarkedRange r(a, END(a));
	FIND_AND_MARK(1, 0u);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(ThreeElements_Between1And2)
{
	int a[] = { 1, 3, 5 };
	MarkedRange r(a, END(a));
	FIND_AND_MARK(2, 3u);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(ThreeElements_EqualTo2)
{
	int a[] = { 1, 3, 5 };
	MarkedRange r(a, END(a));
	FIND_AND_MARK(3, 1u);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(ThreeElements_Between2And3)
{
	int a[] = { 1, 3, 5 };
	MarkedRange r(a, END(a));
	FIND_AND_MARK(4, 3u);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(ThreeElements_EqualTo3)
{
	int a[] = { 1, 3, 5 };
	MarkedRange r(a, END(a));
	FIND_AND_MARK(5, 2u);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
}

RB_TEST(ThreeElements_More)
{
	int a[] = { 1, 3, 5 };
	MarkedRange r(a, END(a));
	FIND_AND_MARK(6, 3u);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(ThreeElements_MultipleSearch)
{
	int a[] = { 1, 3, 5 };
	MarkedRange r(a, END(a));

	FIND_AND_MARK(1, 0u);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_AND_MARK(1, 3u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_AND_MARK(3, 1u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(TwoElements_OneAndTwoSame_MultipleSearch)
{
	int a[] = { 1, 1 };
	MarkedRange r(a, END(a));

	FIND_AND_MARK(1, 0u);
	RB_ASSERT(!r.found[1]);

	FIND_AND_MARK(1, 1u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);

	FIND_AND_MARK(1, 2u);
}

RB_TEST(ThreeElements_OneAndTwoSame_MultipleSearch)
{
	int a[] = { 1, 1, 5 };
	MarkedRange r(a, END(a));

	FIND_AND_MARK(1, 0u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_AND_MARK(1, 1u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_AND_MARK(1, 3u);

	FIND_AND_MARK(5, 2u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);
}

RB_TEST(ThreeElements_TwoAndThreeSame_MultipleSearch)
{
	int a[] = { 0, 1, 1 };
	MarkedRange r(a, END(a));

	FIND_AND_MARK(1, 1u);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_AND_MARK(1, 2u);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);

	FIND_AND_MARK(1, 3u);

	FIND_AND_MARK(0, 0u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);
}

RB_TEST(ThreeElements_AllSame_MultipleSearch)
{
	int a[] = { 1, 1, 1 };
	MarkedRange r(a, END(a));

	FIND_AND_MARK(1, 0u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_AND_MARK(1, 1u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_AND_MARK(1, 2u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);

	FIND_AND_MARK(1, 3u);
}

RB_TEST(TwoElements_Reset)
{
	int a[] = { 1, 3 };
	MarkedRange r(a, END(a));

	FIND_AND_MARK(1, 0u);
	FIND_AND_MARK(3, 1u);

	FIND_AND_MARK(1, 2u);
	FIND_AND_MARK(3, 2u);

	r.Reset();
	FIND_AND_MARK(1, 0u);
	FIND_AND_MARK(3, 1u);
}

RB_TEST(FindInMarked_TwoElements_Reset)
{
	int a[] = { 1, 3 };
	MarkedRange r(a, END(a));

	FIND_AND_MARK(1, 0u);
	FIND_AND_MARK(3, 1u);

	FIND_AND_MARK(1, 2u);
	FIND_AND_MARK(3, 2u);

	r.Reset();
	FIND_AND_MARK(1, 0u);
	FIND_AND_MARK(3, 1u);
}

RB_TEST(FindInMarkedRangePtr_OneElement_NullPtr)
{
	int *b[] = { 0 };
	MarkedPtrRange r(b, END(b));

	int c = 2;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b);
	RB_ASSERT(s_st==RichBool::Analysis::BadValue);
}


// tests for SortedMarkedRange::Find(T)

RB_TEST(FindInSortedMarked_OneElement_Equal)
{
	int a[] = { 1 };
	SortedMarkedRange r(a, END(a));

	FIND_AND_MARK(1,0u);
}

RB_TEST(FindInSortedMarked_OneElement_Less)
{
	int a[] = { 1 };
	SortedMarkedRange r(a, END(a));
	FIND_AND_MARK(0,1u);
}

RB_TEST(FindInSortedMarked_OneElement_More)
{
	int a[] = { 1 };
	SortedMarkedRange r(a, END(a));
	FIND_AND_MARK(2, 1u);
}

RB_TEST(FindInSortedMarked_TwoElements_EqualTo1)
{
	int a[] = { 1, 3 };
	SortedMarkedRange r(a, END(a));
	FIND_AND_MARK(1, 0u);
	RB_ASSERT(!r.found[1]);
}

RB_TEST(FindInSortedMarked_TwoElements_EqualTo2)
{
	int a[] = { 1, 3 };
	SortedMarkedRange r(a, END(a));
	FIND_AND_MARK(3, 1u);
	RB_ASSERT((bool)r.found[1]);
}

RB_TEST(FindInSortedMarked_TwoElements_Less)
{
	int a[] = { 1, 3 };
	SortedMarkedRange r(a, END(a));
	FIND_AND_MARK(0, 2u);
	RB_ASSERT(!r.found[1]);
}

RB_TEST(FindInSortedMarked_TwoElements_InBetween)
{
	int a[] = { 1, 3 };
	SortedMarkedRange r(a, END(a));
	FIND_AND_MARK(2, 2u);
	RB_ASSERT(!r.found[1]);
}

RB_TEST(FindInSortedMarked_TwoElements_More)
{
	int a[] = { 1, 3 };
	SortedMarkedRange r(a, END(a));
	FIND_AND_MARK(4, 2u);
	RB_ASSERT(!r.found[1]);
}

RB_TEST(FindInSortedMarked_ThreeElements_Less)
{
	int a[] = { 1, 3, 5 };
	SortedMarkedRange r(a, END(a));
	FIND_AND_MARK(0, 3u);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInSortedMarked_ThreeElements_EqualTo1)
{
	int a[] = { 1, 3, 5 };
	SortedMarkedRange r(a, END(a));
	FIND_AND_MARK(1, 0u);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInSortedMarked_ThreeElements_Between1And2)
{
	int a[] = { 1, 3, 5 };
	SortedMarkedRange r(a, END(a));
	FIND_AND_MARK(2, 3u);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInSortedMarked_ThreeElements_EqualTo2)
{
	int a[] = { 1, 3, 5 };
	SortedMarkedRange r(a, END(a));
	FIND_AND_MARK(3, 1u);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInSortedMarked_ThreeElements_Between2And3)
{
	int a[] = { 1, 3, 5 };
	SortedMarkedRange r(a, END(a));
	FIND_AND_MARK(4, 3u);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInSortedMarked_ThreeElements_EqualTo3)
{
	int a[] = { 1, 3, 5 };
	SortedMarkedRange r(a, END(a));
	FIND_AND_MARK(5, 2u);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
}

RB_TEST(FindInSortedMarked_ThreeElements_More)
{
	int a[] = { 1, 3, 5 };
	SortedMarkedRange r(a, END(a));
	FIND_AND_MARK(6, 3u);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInSortedMarked_ThreeElements_MultipleSearch)
{
	int a[] = { 1, 3, 5 };
	SortedMarkedRange r(a, END(a));

	FIND_AND_MARK(1, 0u);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_AND_MARK(1, 3u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_AND_MARK(3, 1u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInSortedMarked_TwoElements_OneAndTwoSame_MultipleSearch)
{
	int a[] = { 1, 1 };
	SortedMarkedRange r(a, END(a));

	FIND_AND_MARK(1, 0u);
	RB_ASSERT(!r.found[1]);

	FIND_AND_MARK(1, 1u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);

	FIND_AND_MARK(1, 2u);
}

RB_TEST(FindInSortedMarked_ThreeElements_OneAndTwoSame_MultipleSearch)
{
	int a[] = { 1, 1, 5 };
	SortedMarkedRange r(a, END(a));

	FIND_AND_MARK(1, 0u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_AND_MARK(1, 1u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_AND_MARK(1, 3u);

	FIND_AND_MARK(5, 2u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);
}

RB_TEST(FindInSortedMarked_ThreeElements_TwoAndThreeSame_MultipleSearch)
{
	int a[] = { 0, 1, 1 };
	SortedMarkedRange r(a, END(a));

	FIND_AND_MARK(1, 1u);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_AND_MARK(1, 2u);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);

	FIND_AND_MARK(1, 3u);

	FIND_AND_MARK(0, 0u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);
}

RB_TEST(FindInSortedMarked_ThreeElements_AllSame_MultipleSearch)
{
	int a[] = { 1, 1, 1 };
	SortedMarkedRange r(a, END(a));

	FIND_AND_MARK(1, 0u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_AND_MARK(1, 1u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_AND_MARK(1, 2u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);

	FIND_AND_MARK(1, 3u);
}

RB_TEST(FindInSortedMarked_ThreeElements_More_MultipleSearch)
{
	int a[] = { 3, 2, 1 };
	ReverseSortedMarkedRange r(a, END(a));

	FIND_AND_MARK(1, 2u);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT((bool)r.found[2]);

	FIND_AND_MARK(2, 1u);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);

	FIND_AND_MARK(3, 0u);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);

	FIND_AND_MARK(1, 3u);
}


RB_TEST(FindInSortedMarked_TwoElements_Reset)
{
	int a[] = { 1, 3 };
	SortedMarkedRange r(a, END(a));

	FIND_AND_MARK(1, 0u);
	FIND_AND_MARK(3, 1u);

	FIND_AND_MARK(1, 2u);
	FIND_AND_MARK(3, 2u);

	r.Reset();
	FIND_AND_MARK(1, 0u);
	FIND_AND_MARK(3, 1u);
}

RB_TEST(FindInSortedMarkedPtr_OneElement_NullPtr)
{
	int *b[] = { 0 };
	SortedMarkedPtrRange r(b, END(b));

	int c = 2;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b);
	RB_ASSERT(s_st==RichBool::Analysis::BadValue);
}
