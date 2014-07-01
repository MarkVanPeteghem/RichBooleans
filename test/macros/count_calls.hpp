//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef COUNT_CALLS_H__QM
#define COUNT_CALLS_H__QM

#include "richbool/functors.hpp"

// This class checks if its operator++ is called exactly n times.
// This check is done in its destructor.
// The test is not done if the level is 0, because in that level no checks
// are performed.
class CheckedInt
{
public:
	CheckedInt(int n): expected(n), actual(0) {}
	~CheckedInt()
	{
		if (RichBoolTest::GetLevel()!=0)
			RB_INTERNAL_ASSERT(rbEQUAL(expected, actual));
		else
			RB_INTERNAL_ASSERT(rbEQUAL(0, actual));
	}
	CheckedInt& operator++()
	{
		++actual;
		return *this;
	}
private:
	int expected, actual;
};

// This is a typical shared pointer implementation,
// except maybe that it is not threadsafe,
// because this test application is single threaded.
template <typename T>
class SharedPointer
{
public:
	SharedPointer(): wrapper(0) {}
	SharedPointer(T *t)
	{
		if (t)
			wrapper = new Wrapper(t);
		else
			wrapper = 0;
	}

	SharedPointer(const SharedPointer &sp)
	{
		wrapper = sp.wrapper;
		if (wrapper)
			wrapper->AddRef();
	}

	~SharedPointer()
	{
		if (wrapper)
			wrapper->Release();
	}

	SharedPointer& operator=(T *t)
	{
		if (wrapper)
			wrapper->Release();
		if (t)
			wrapper = new Wrapper(t);
		else
			wrapper = 0;
		return *this;
	}

	SharedPointer& operator=(const SharedPointer &sp)
	{
		if (wrapper)
			wrapper->Release();
	
		wrapper = sp.wrapper;
		
		if (wrapper)
			wrapper->AddRef();
		
		return *this;
	}

	operator bool() const
	{
		return wrapper && wrapper->Get()!=0;
	}

	T& operator*()
	{
		return *wrapper->Get();
	}

	T* operator->()
	{
		return wrapper->Get();
	}

	const T& operator*() const
	{
		return *wrapper->Get();
	}

	const T* operator->() const
	{
		return wrapper->Get();
	}

private:
	class Wrapper
	{
	public:
		Wrapper(T *t_): count(1), t(t_)
		{}
		
		virtual ~Wrapper() { delete t; }

		T* Get() { return t; }
		void AddRef() { ++count; }
		virtual void Release()
		{
			--count;
			if (count==0)
				delete this;
		}

	private:
		int count;
		T *t;
	} *wrapper;
};

// This class is a base class for Rich Boolean Functor Cores
// that need to check how many times the check is performed.
// This is done with a shared pointer that contains a CheckedInt object.
// It has to be in a shared pointer because the Rich Boolean Functor Core
// may be copied, e.g. when two Rich Boolean Functors are combined
// with a logical operator.
// The shared pointer makes sure that we always use the correct CheckedInt
// object, that no extra CheckedInt objects are created behind the scenes,
// and that the destructor of the CheckedInt object is called at the end
// of the test, which checks if it was called exactly n times.

// Note that this counts both calls to operator(...) and Analyse(...) on
// the Rich Boolean Functor, because Analyse(...) calls operator(...) in
// the Rich Boolean Functor Core.

template <class RBFC>
struct CountCallsCore: public RBFC
{
	using RBFC::GetAnalysis2;
	CountCallsCore(int n): callCounter(new CheckedInt(n)) {}
	mutable SharedPointer<CheckedInt> callCounter;

	template <typename T1, typename T2>
	bool operator()(const T1 &t1, const T2 &t2) const
	{
		++*callCounter;
		return RBFC::operator()(t1, t2);
	}
};

template <class RBFC, class GetValue1=RichBool::Value, class GetValue2=RichBool::Value,
	class Str1_=RichBool::MakeString, class Str2_=RichBool::MakeString>
struct CountCalls: public RichBool::Wrapper2Arg<CountCallsCore<RBFC>, GetValue1, GetValue2, Str1_, Str2_> {
	CountCalls(int n, GetValue1 gv1=GetValue1(), GetValue2 gv2=GetValue2()):
		RichBool::Wrapper2Arg<CountCallsCore<RBFC>, GetValue1, GetValue2, Str1_, Str2_>
			(CountCallsCore<RBFC>(n), gv1, gv2)
	{}
};

RICHBOOL_WRAPPER2ARG_1CARG(EqualCountCalls, CountCallsCore<RichBool::EqualCore>, int n, n)
RICHBOOL_WRAPPER2ARG_1CARG(DiffCountCalls,  CountCallsCore<RichBool::DiffCore>,  int n, n)

#endif // #ifndef COUNT_CALLS_H__QM
