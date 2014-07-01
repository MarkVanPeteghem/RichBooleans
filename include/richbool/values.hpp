//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICHBOOL_VALUES_H__QM
#define RICHBOOL_VALUES_H__QM

// This header file contains an overloaded template function
// called Values that creates a container object that can be used in
// Rich Booleans that use a container, such as rbIN_CONTAINERS,
// to make it easier to give values, e.g.
// rbIN_CONTAINERS(RichBool::Values(1,2,3), vec, RichBool::AllEqual<>()).
// It deletes its allocated memory when it is no longer needed.

#include "string.h"
#include "richbool/shared_ptr.hpp"

namespace RichBool
{
	namespace detail
	{
		template<typename T>
		class Values
		{
		public:
			typedef const T* iterator;

			Values(T* arr, size_t size): m_values(arr), m_size(size)
			{}

			iterator begin() const
			{
				return m_values.Get();
			}
			iterator end() const
			{
				return m_values.Get()+m_size;
			}
		private:
			size_t m_size;
			ConstSharedArray<T> m_values;
		};
	}

	template<typename T>
	detail::Values<T> Values()
	{
		return detail::Values<T>(0, 0);
	}
	template<typename T>
	detail::Values<T> Values(const T& t0)
	{
		T *arr = new T[1];
		arr[0] = t0;
		return detail::Values<T>(arr, 1);
	}
	template<typename T>
	detail::Values<T> Values(const T& t0, const T& t1)
	{
		T *arr = new T[2];
		arr[0] = t0;
		arr[1] = t1;
		return detail::Values<T>(arr, 2);
	}
	template<typename T>
	detail::Values<T> Values(const T& t0, const T& t1, const T& t2)
	{
		T *arr = new T[3];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		return detail::Values<T>(arr, 3);
	}
	template<typename T>
	detail::Values<T> Values(const T& t0, const T& t1, const T& t2, const T& t3)
	{
		T *arr = new T[4];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		arr[3] = t3;
		return detail::Values<T>(arr, 4);
	}
	template<typename T>
	detail::Values<T> Values(const T& t0, const T& t1, const T& t2, const T& t3, const T& t4)
	{
		T *arr = new T[5];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		arr[3] = t3;
		arr[4] = t4;
		return detail::Values<T>(arr, 5);
	}
	template<typename T>
	detail::Values<T> Values(const T& t0, const T& t1, const T& t2, const T& t3, const T& t4, const T& t5)
	{
		T *arr = new T[6];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		arr[3] = t3;
		arr[4] = t4;
		arr[5] = t5;
		return detail::Values<T>(arr, 6);
	}
	template<typename T>
	detail::Values<T> Values(const T& t0, const T& t1, const T& t2, const T& t3, const T& t4, const T& t5, const T& t6)
	{
		T *arr = new T[7];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		arr[3] = t3;
		arr[4] = t4;
		arr[5] = t5;
		arr[6] = t6;
		return detail::Values<T>(arr, 7);
	}
	template<typename T>
	detail::Values<T> Values(const T& t0, const T& t1, const T& t2, const T& t3, const T& t4, const T& t5, const T& t6, const T& t7)
	{
		T *arr = new T[8];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		arr[3] = t3;
		arr[4] = t4;
		arr[5] = t5;
		arr[6] = t6;
		arr[7] = t7;
		return detail::Values<T>(arr, 8);
	}
	template<typename T>
	detail::Values<T> Values(const T& t0, const T& t1, const T& t2, const T& t3, const T& t4, const T& t5, const T& t6, const T& t7, const T& t8)
	{
		T *arr = new T[9];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		arr[3] = t3;
		arr[4] = t4;
		arr[5] = t5;
		arr[6] = t6;
		arr[7] = t7;
		arr[8] = t8;
		return detail::Values<T>(arr, 9);
	}
	template<typename T>
	detail::Values<T> Values(const T& t0, const T& t1, const T& t2, const T& t3, const T& t4, const T& t5, const T& t6, const T& t7, const T& t8, const T& t9)
	{
		T *arr = new T[10];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		arr[3] = t3;
		arr[4] = t4;
		arr[5] = t5;
		arr[6] = t6;
		arr[7] = t7;
		arr[8] = t8;
		arr[9] = t9;
		return detail::Values<T>(arr, 10);
	}


	// overloads for const char* and const wchar_t* are necessary to use string literals:
	detail::Values<const char*> Values(const char *t0);
	detail::Values<const char*> Values(const char *t0, const char *t1);
	detail::Values<const char*> Values(const char *t0, const char *t1, const char *t2);
	detail::Values<const char*> Values(const char *t0, const char *t1, const char *t2, const char *t3);
	detail::Values<const char*> Values(const char *t0, const char *t1, const char *t2, const char *t3, const char *t4);
	detail::Values<const char*> Values(const char *t0, const char *t1, const char *t2, const char *t3, const char *t4, const char *t5);
	detail::Values<const char*> Values(const char *t0, const char *t1, const char *t2, const char *t3, const char *t4, const char *t5, const char *t6);
	detail::Values<const char*> Values(const char *t0, const char *t1, const char *t2, const char *t3, const char *t4, const char *t5, const char *t6, const char *t7);
	detail::Values<const char*> Values(const char *t0, const char *t1, const char *t2, const char *t3, const char *t4, const char *t5, const char *t6, const char *t7, const char *t8);
	detail::Values<const char*> Values(const char *t0, const char *t1, const char *t2, const char *t3, const char *t4, const char *t5, const char *t6, const char *t7, const char *t8, const char *t9);
	detail::Values<const wchar_t*> Values(const wchar_t *t0);
	detail::Values<const wchar_t*> Values(const wchar_t *t0, const wchar_t *t1);
	detail::Values<const wchar_t*> Values(const wchar_t *t0, const wchar_t *t1, const wchar_t *t2);
	detail::Values<const wchar_t*> Values(const wchar_t *t0, const wchar_t *t1, const wchar_t *t2, const wchar_t *t3);
	detail::Values<const wchar_t*> Values(const wchar_t *t0, const wchar_t *t1, const wchar_t *t2, const wchar_t *t3, const wchar_t *t4);
	detail::Values<const wchar_t*> Values(const wchar_t *t0, const wchar_t *t1, const wchar_t *t2, const wchar_t *t3, const wchar_t *t4, const wchar_t *t5);
	detail::Values<const wchar_t*> Values(const wchar_t *t0, const wchar_t *t1, const wchar_t *t2, const wchar_t *t3, const wchar_t *t4, const wchar_t *t5, const wchar_t *t6);
	detail::Values<const wchar_t*> Values(const wchar_t *t0, const wchar_t *t1, const wchar_t *t2, const wchar_t *t3, const wchar_t *t4, const wchar_t *t5, const wchar_t *t6, const wchar_t *t7);
	detail::Values<const wchar_t*> Values(const wchar_t *t0, const wchar_t *t1, const wchar_t *t2, const wchar_t *t3, const wchar_t *t4, const wchar_t *t5, const wchar_t *t6, const wchar_t *t7, const wchar_t *t8);
	detail::Values<const wchar_t*> Values(const wchar_t *t0, const wchar_t *t1, const wchar_t *t2, const wchar_t *t3, const wchar_t *t4, const wchar_t *t5, const wchar_t *t6, const wchar_t *t7, const wchar_t *t8, const wchar_t *t9);
}

#endif // #ifndef RICHBOOL_VALUES_H__QM
