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

typedef detail::FindInMultiMarkedRange<int*, detail::EndCondition<size_t>, Equal<> >
	MultiMarkedRange;

typedef detail::FindInMultiMarkedRange<int**, detail::EndCondition<size_t>, Equal<Pointer<>, Pointer<> > >
	MultiMarkedPtrRange;

typedef detail::FindInMultiMarkedSortedRange<int*, detail::EndCondition<size_t>, Less<> >
	SortedMultiMarkedRange;

typedef detail::FindInMultiMarkedSortedRange<int**, detail::EndCondition<size_t>, Less<Pointer<>, Pointer<> > >
	SortedMultiMarkedPtrRange;

typedef detail::FindInMultiMarkedSortedRange<int*, detail::EndCondition<size_t>, More<> >
	ReverseSortedMultiMarkedRange;

#define END(ARR) detail::EndCondition<size_t>(RICHBOOL_ARRAY_COUNT(ARR))


#if !RICHBOOL_IS_MSVC6_RELEASE

	#define FIND_AND_MARK(t) \
		if (RichBoolTest::GetLevel()==1) { \
			s_it=r.Find(t); \
			RB_ASSERT(rbEQUAL_PTR(s_it.it,a+RICHBOOL_ARRAY_COUNT(a))); \
			RB_ASSERT(rbEQUAL(s_it.idx,RICHBOOL_ARRAY_COUNT(a))); \
		} else if (RichBoolTest::GetLevel()==2) { \
			s_it=r.SafeFind(t,s_st); \
			RB_ASSERT(rbEQUAL_PTR(s_it.it,a+RICHBOOL_ARRAY_COUNT(a))); \
			RB_ASSERT(rbEQUAL(s_it.idx,RICHBOOL_ARRAY_COUNT(a))); \
			RB_ASSERT(s_st==RichBool::Analysis::Ok); \
		} else return;

	#define FIND_NOT(t) \
		if (RichBoolTest::GetLevel()==1) { \
			s_it=r.Find(t); \
			RB_ASSERT(rbEQUAL_PTR(s_it.it,a+RICHBOOL_ARRAY_COUNT(a))); \
			RB_ASSERT(rbEQUAL(s_it.idx,RICHBOOL_ARRAY_COUNT(a))); \
		} else if (RichBoolTest::GetLevel()==2) { \
			s_it=r.SafeFind(t,s_st); \
			RB_ASSERT(rbEQUAL_PTR(s_it.it,a+RICHBOOL_ARRAY_COUNT(a))); \
			RB_ASSERT(rbEQUAL(s_it.idx,RICHBOOL_ARRAY_COUNT(a))); \
			RB_ASSERT(s_st==RichBool::Analysis::NotOk); \
		} else return;

#else

	#define FIND_AND_MARK(t) \
		if (RichBoolTest::GetLevel()==1) { \
			s_it=r.Find(t); \
		} else if (RichBoolTest::GetLevel()==2) { \
			s_it=r.SafeFind(t,s_st); \
			RB_ASSERT(s_st==RichBool::Analysis::Ok); \
		} else return; \
		RB_ASSERT((s_it.it==a+RICHBOOL_ARRAY_COUNT(a))); \
		RB_ASSERT((s_it.idx==RICHBOOL_ARRAY_COUNT(a)));

	#define FIND_NOT(t) \
		if (RichBoolTest::GetLevel()==1) { \
			s_it=r.Find(t); \
			RB_ASSERT((s_it.it==a+RICHBOOL_ARRAY_COUNT(a))); \
			RB_ASSERT((s_it.idx==RICHBOOL_ARRAY_COUNT(a))); \
		} else if (RichBoolTest::GetLevel()==2) { \
			s_it=r.SafeFind(t,s_st); \
			RB_ASSERT((s_it.it==a+RICHBOOL_ARRAY_COUNT(a))); \
			RB_ASSERT((s_it.idx==RICHBOOL_ARRAY_COUNT(a))); \
			RB_ASSERT(s_st==RichBool::Analysis::NotOk); \
		} else return;

#endif

static RichBool::detail::EnhIt<int*, size_t> s_it(0,0);
static RichBool::Analysis::State s_st=RichBool::Analysis::Ok;



// tests for MultiMarkedRange::Find(T)

RB_TEST(FindInMultiMarkedRange_OneElement_Equal)
{
	int a[] = { 1 };
	MultiMarkedRange r(a, END(a));

	FIND_AND_MARK(1);
	RB_ASSERT((bool)r.found[0]);
}

RB_TEST(FindInMultiMarkedRange_OneElement_Less)
{
	int a[] = { 1 };
	MultiMarkedRange r(a, END(a));
	FIND_NOT(0);
	RB_ASSERT(!r.found[0]);
}

RB_TEST(FindInMultiMarkedRange_TwoElements_EqualTo1)
{
	int a[] = { 1, 3 };
	MultiMarkedRange r(a, END(a));
	FIND_AND_MARK(1);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT(!r.found[1]);
}

RB_TEST(FindInMultiMarkedRange_TwoElements_EqualTo2)
{
	int a[] = { 1, 3 };
	MultiMarkedRange r(a, END(a));
	FIND_AND_MARK(3);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT((bool)r.found[1]);
}

RB_TEST(FindInMultiMarkedRange_TwoElements_Less)
{
	int a[] = { 1, 3 };
	MultiMarkedRange r(a, END(a));
	FIND_NOT(0);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
}

RB_TEST(FindInMultiMarkedRange_ThreeElements_Less)
{
	int a[] = { 1, 3, 5 };
	MultiMarkedRange r(a, END(a));
	FIND_NOT(0);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInMultiMarkedRange_ThreeElements_EqualTo1)
{
	int a[] = { 1, 3, 5 };
	MultiMarkedRange r(a, END(a));
	FIND_AND_MARK(1);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInMultiMarkedRange_ThreeElements_Between1And2)
{
	int a[] = { 1, 3, 5 };
	MultiMarkedRange r(a, END(a));
	FIND_NOT(2);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInMultiMarkedRange_ThreeElements_EqualTo2)
{
	int a[] = { 1, 3, 5 };
	MultiMarkedRange r(a, END(a));
	FIND_AND_MARK(3);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInMultiMarkedRange_ThreeElements_Between2And3)
{
	int a[] = { 1, 3, 5 };
	MultiMarkedRange r(a, END(a));
	FIND_NOT(4);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInMultiMarkedRange_ThreeElements_EqualTo3)
{
	int a[] = { 1, 3, 5 };
	MultiMarkedRange r(a, END(a));
	FIND_AND_MARK(5);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT((bool)r.found[2]);
}

RB_TEST(FindInMultiMarkedRange_ThreeElements_More)
{
	int a[] = { 1, 3, 5 };
	MultiMarkedRange r(a, END(a));
	FIND_NOT(6);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInMultiMarkedRange_ThreeElements_MultipleSearch)
{
	int a[] = { 1, 3, 5 };
	MultiMarkedRange r(a, END(a));

	FIND_AND_MARK(1);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_NOT(1);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_AND_MARK(3);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInMultiMarkedRange_TwoElements_OneAndTwoSame_MultipleSearch)
{
	int a[] = { 1, 1 };
	MultiMarkedRange r(a, END(a));

	FIND_AND_MARK(1);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);

	FIND_NOT(1);

	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
}

RB_TEST(FindInMultiMarkedRange_ThreeElements_OneAndTwoSame_MultipleSearch)
{
	int a[] = { 1, 1, 5 };
	MultiMarkedRange r(a, END(a));

	FIND_AND_MARK(1);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_NOT(1);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_AND_MARK(5);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);
}

RB_TEST(FindInMultiMarkedRange_ThreeElements_TwoAndThreeSame_MultipleSearch)
{
	int a[] = { 0, 1, 1 };
	MultiMarkedRange r(a, END(a));

	FIND_AND_MARK(1);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);

	FIND_NOT(1);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);

	FIND_AND_MARK(0);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);
}

RB_TEST(FindInMultiMarkedRange_ThreeElements_AllSame_MultipleSearch)
{
	int a[] = { 1, 1, 1 };
	MultiMarkedRange r(a, END(a));

	FIND_AND_MARK(1);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);

	FIND_NOT(1);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);
}

RB_TEST(FindInMultiMarked_TwoElements_Reset)
{
	int a[] = { 1, 3 };
	MultiMarkedRange r(a, END(a));

	FIND_AND_MARK(1);
	FIND_AND_MARK(3);

	r.Reset();
	FIND_AND_MARK(1);
	FIND_AND_MARK(3);
}

RB_TEST(FindInMultiMarkedRangePtr_OneElement_NullPtr)
{
	int *b[] = { 0 };
	MultiMarkedPtrRange r(b, END(b));

	int c = 2;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b);
	RB_ASSERT(s_st==RichBool::Analysis::BadValue);
}


// tests for SortedMultiMarkedRange::Find(T)

RB_TEST(FindInSortedMultiMarked_OneElement_Equal)
{
	int a[] = { 1 };
	SortedMultiMarkedRange r(a, END(a));

	FIND_AND_MARK(1);
	RB_ASSERT((bool)r.found[0]);
}

RB_TEST(FindInSortedMultiMarked_OneElement_Less)
{
	int a[] = { 1 };
	SortedMultiMarkedRange r(a, END(a));
	FIND_NOT(0);
	RB_ASSERT(!r.found[0]);
}

RB_TEST(FindInSortedMultiMarked_OneElement_More)
{
	int a[] = { 1 };
	SortedMultiMarkedRange r(a, END(a));
	FIND_NOT(2);
	RB_ASSERT(!r.found[0]);
}

RB_TEST(FindInSortedMultiMarked_TwoElements_EqualTo1)
{
	int a[] = { 1, 3 };
	SortedMultiMarkedRange r(a, END(a));
	FIND_AND_MARK(1);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT(!r.found[1]);
}

RB_TEST(FindInSortedMultiMarked_TwoElements_EqualTo2)
{
	int a[] = { 1, 3 };
	SortedMultiMarkedRange r(a, END(a));
	FIND_AND_MARK(3);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT((bool)r.found[1]);
}

RB_TEST(FindInSortedMultiMarked_TwoElements_Less)
{
	int a[] = { 1, 3 };
	SortedMultiMarkedRange r(a, END(a));
	FIND_NOT(0);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
}

RB_TEST(FindInSortedMultiMarked_TwoElements_InBetween)
{
	int a[] = { 1, 3 };
	SortedMultiMarkedRange r(a, END(a));
	FIND_NOT(2);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
}

RB_TEST(FindInSortedMultiMarked_TwoElements_More)
{
	int a[] = { 1, 3 };
	SortedMultiMarkedRange r(a, END(a));
	FIND_NOT(4);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
}

RB_TEST(FindInSortedMultiMarked_ThreeElements_Less)
{
	int a[] = { 1, 3, 5 };
	SortedMultiMarkedRange r(a, END(a));
	FIND_NOT(0);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInSortedMultiMarked_ThreeElements_EqualTo1)
{
	int a[] = { 1, 3, 5 };
	SortedMultiMarkedRange r(a, END(a));
	FIND_AND_MARK(1);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInSortedMultiMarked_ThreeElements_Between1And2)
{
	int a[] = { 1, 3, 5 };
	SortedMultiMarkedRange r(a, END(a));
	FIND_NOT(2);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInSortedMultiMarked_ThreeElements_EqualTo2)
{
	int a[] = { 1, 3, 5 };
	SortedMultiMarkedRange r(a, END(a));
	FIND_AND_MARK(3);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInSortedMultiMarked_ThreeElements_Between2And3)
{
	int a[] = { 1, 3, 5 };
	SortedMultiMarkedRange r(a, END(a));
	FIND_NOT(4);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInSortedMultiMarked_ThreeElements_EqualTo3)
{
	int a[] = { 1, 3, 5 };
	SortedMultiMarkedRange r(a, END(a));
	FIND_AND_MARK(5);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT((bool)r.found[2]);
}

RB_TEST(FindInSortedMultiMarked_ThreeElements_More)
{
	int a[] = { 1, 3, 5 };
	SortedMultiMarkedRange r(a, END(a));
	FIND_NOT(6);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInSortedMultiMarked_ThreeElements_MultipleSearch)
{
	int a[] = { 1, 3, 5 };
	SortedMultiMarkedRange r(a, END(a));

	FIND_AND_MARK(1);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_NOT(1);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_AND_MARK(3);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT(!r.found[2]);
}

RB_TEST(FindInSortedMultiMarked_TwoElements_OneAndTwoSame_MultipleSearch)
{
	int a[] = { 1, 1 };
	SortedMultiMarkedRange r(a, END(a));

	FIND_AND_MARK(1);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);

	FIND_NOT(1);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
}

RB_TEST(FindInSortedMultiMarked_ThreeElements_OneAndTwoSame_MultipleSearch)
{
	int a[] = { 1, 1, 5 };
	SortedMultiMarkedRange r(a, END(a));

	FIND_AND_MARK(1);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_NOT(1);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT(!r.found[2]);

	FIND_AND_MARK(5);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);
}

RB_TEST(FindInSortedMultiMarked_ThreeElements_TwoAndThreeSame_MultipleSearch)
{
	int a[] = { 0, 1, 1 };
	SortedMultiMarkedRange r(a, END(a));

	FIND_AND_MARK(1);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);

	FIND_NOT(1);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);

	FIND_AND_MARK(0);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);
}

RB_TEST(FindInSortedMultiMarked_ThreeElements_AllSame_MultipleSearch)
{
	int a[] = { 1, 1, 1 };
	SortedMultiMarkedRange r(a, END(a));

	FIND_AND_MARK(1);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);

	FIND_NOT(1);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);
}

RB_TEST(FindInSortedMultiMarked_ThreeElements_More_MultipleSearch)
{
	int a[] = { 3, 2, 1 };
	ReverseSortedMultiMarkedRange r(a, END(a));

	FIND_AND_MARK(1);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT(!r.found[1]);
	RB_ASSERT((bool)r.found[2]);

	FIND_AND_MARK(2);
	RB_ASSERT(!r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);

	FIND_AND_MARK(3);
	RB_ASSERT((bool)r.found[0]);
	RB_ASSERT((bool)r.found[1]);
	RB_ASSERT((bool)r.found[2]);

	FIND_NOT(1);
}


RB_TEST(FindInSortedMultiMarked_TwoElements_Reset)
{
	int a[] = { 1, 3 };
	SortedMultiMarkedRange r(a, END(a));

	FIND_AND_MARK(1);
	FIND_AND_MARK(3);

	FIND_NOT(1);
	FIND_NOT(3);

	r.Reset();
	FIND_AND_MARK(1);
	FIND_AND_MARK(3);
}

RB_TEST(FindInSortedMultiMarkedPtr_OneElement_NullPtr)
{
	int *b[] = { 0 };
	SortedMultiMarkedPtrRange r(b, END(b));

	int c = 2;
	int **f = r.SafeFind(&c, s_st).it;
	RB_ASSERT(f==b);
	RB_ASSERT(s_st==RichBool::Analysis::BadValue);
}

RB_TEST(FindInSortedMultiMarkedPtr_FourElements_SecondNullPtr)
{
	int a=0, b=1;
	int *c[] = { &a, 0, &b, &b };
	SortedMultiMarkedPtrRange r(c, END(c));

	int **f = r.SafeFind(&b, s_st).it;
	RB_ASSERT(f==c+1);
	RB_ASSERT(s_st==RichBool::Analysis::BadValue);
}

RB_TEST(FindInSortedMultiMarkedPtr_FourElements_ThirdNullPtr)
{
	int a=0, b=1;
	int *c[] = { &a, &b, 0, &b };
	SortedMultiMarkedPtrRange r(c, END(c));

	int **f = r.SafeFind(&b, s_st).it;
	RB_ASSERT(f==c+2);
	RB_ASSERT(s_st==RichBool::Analysis::BadValue);
}

RB_TEST(FindInSortedMultiMarkedPtr_FourElements_FourthNullPtr)
{
	int a=0, b=1;
	int *c[] = { &a, &b, &b, 0 };
	SortedMultiMarkedPtrRange r(c, END(c));

	int **f = r.SafeFind(&b, s_st).it;
	RB_ASSERT(f==c+3);
	RB_ASSERT(s_st==RichBool::Analysis::BadValue);
}
