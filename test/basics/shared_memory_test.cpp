//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/shared_ptr.hpp"

struct CheckDelete
{
	CheckDelete(bool *deleted=0): m_deleted(deleted)
	{
		if (m_deleted)
			*m_deleted = false;
	}
	~CheckDelete()
	{
		if (m_deleted)
			*m_deleted = true;
	}
	bool *m_deleted;
};

RB_TEST(SharedPointer)
{
	RichBool::ConstSharedPointer<int> sp = new int(5);
	RB_ASSERT(rbEQUAL(5, *sp));
}

RB_TEST(SharedPointer_CopyConstructor)
{
	RichBool::ConstSharedPointer<int> sp1 = new int(5);
	RichBool::ConstSharedPointer<int> sp2 = sp1;
	RB_ASSERT(rbEQUAL(5, *sp2));
}

RB_TEST(SharedPointer_AssignSharedPointer)
{
	RichBool::ConstSharedPointer<int> sp1 = new int(5);
	RichBool::ConstSharedPointer<int> sp2;
	sp2 = sp1;
	RB_ASSERT(rbEQUAL(5, *sp2));
}

RB_TEST(SharedPointer_AssignPointer)
{
	RichBool::ConstSharedPointer<int> sp;
	sp = new int(5);
	RB_ASSERT(rbEQUAL(5, *sp));
}

RB_TEST(SharedPointer_UnassignReturnsFalse)
{
	RichBool::ConstSharedPointer<int> sp;
	RB_ASSERT(!sp);
}

RB_TEST(SharedPointer_AssignReturnsTrue)
{
	RichBool::ConstSharedPointer<int> sp = new int(5);
	RB_ASSERT(!!sp);
}

RB_TEST(SharedPointer_MemberOperator)
{
	RichBool::ConstSharedPointer<std::string> sp = new std::string("abc");
	RB_ASSERT(!sp->empty());
}

RB_TEST(SharedPointer_DestroyedAfterReassign)
{
	bool deleted = false;
	RichBool::ConstSharedPointer<CheckDelete> sp = new CheckDelete(&deleted);
	RB_ASSERT(!deleted);
	sp = 0;
	RB_ASSERT(deleted);
}

RB_TEST(SharedPointer_DestroyedWhenDestructorCalled)
{
	bool deleted = false;
	{
		RichBool::ConstSharedPointer<CheckDelete> sp = new CheckDelete(&deleted);
		RB_ASSERT(!deleted);
	}
	RB_ASSERT(deleted);
}



namespace
{
	int* IntArray()
	{
		int *arr = new int[3];
		arr[0] = 2;
		arr[1] = 5;
		arr[2] = 8;
		return arr;
	}
}

RB_TEST(SharedArray)
{
	RichBool::ConstSharedArray<int> sp = IntArray();
	RB_ASSERT(rbEQUAL(2, *sp));
}

RB_TEST(SharedArray_Index)
{
	RichBool::ConstSharedArray<int> sp = IntArray();
	RB_ASSERT(rbEQUAL(2, sp[0]));
	RB_ASSERT(rbEQUAL(5, sp[1]));
	RB_ASSERT(rbEQUAL(8, sp[2]));
}

RB_TEST(SharedArray_CopyConstructor)
{
	RichBool::ConstSharedArray<int> sp1 = IntArray();
	RichBool::ConstSharedArray<int> sp2 = sp1;
	RB_ASSERT(rbEQUAL(2, *sp2));
}

RB_TEST(SharedArray_AssignSharedArray)
{
	RichBool::ConstSharedArray<int> sp1 = IntArray();
	RichBool::ConstSharedArray<int> sp2;
	sp2 = sp1;
	RB_ASSERT(rbEQUAL(2, *sp2));
}

RB_TEST(SharedArray_AssignArray)
{
	RichBool::ConstSharedArray<int> sp;
	sp = IntArray();
	RB_ASSERT(rbEQUAL(2, *sp));
}

RB_TEST(SharedArray_UnassignReturnsFalse)
{
	RichBool::ConstSharedArray<int> sp;
	RB_ASSERT(!sp);
}

RB_TEST(SharedArray_AssignReturnsTrue)
{
	RichBool::ConstSharedArray<int> sp = IntArray();
	RB_ASSERT(!!sp);
}

RB_TEST(SharedArray_MemberOperator)
{
	RichBool::ConstSharedArray<std::string> sp = new std::string[2];
	RB_ASSERT(sp->empty());
}

RB_TEST(SharedArray_DestroyedAfterReassign)
{
	bool deleted1 = false;
	bool deleted2 = false;
	CheckDelete *checkDelete = new CheckDelete[2];
	checkDelete[0].m_deleted = &deleted1;
	checkDelete[1].m_deleted = &deleted2;
	RichBool::ConstSharedArray<CheckDelete> sp = checkDelete;
	RB_ASSERT(!deleted1);
	RB_ASSERT(!deleted2);
	sp = 0;
	RB_ASSERT(deleted1);
	RB_ASSERT(deleted2);
}

RB_TEST(SharedArray_DestroyedWhenDestructorCalled)
{
	bool deleted1 = false;
	bool deleted2 = false;
	CheckDelete *checkDelete = new CheckDelete[2];
	checkDelete[0].m_deleted = &deleted1;
	checkDelete[1].m_deleted = &deleted2;
	{
		RichBool::ConstSharedArray<CheckDelete> sp = checkDelete;
		RB_ASSERT(!deleted1);
		RB_ASSERT(!deleted2);
	}
	RB_ASSERT(deleted1);
	RB_ASSERT(deleted2);
}

