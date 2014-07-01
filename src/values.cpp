//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#if defined(_MSC_VER) && _MSC_VER<=1300
#pragma warning(disable: 4284) // disable warnings about operator-> when primitive type is used with detail::Values
#endif

#include "richbool/values.hpp"
	
namespace RichBool
{
	detail::Values<const char*> Values(const char *t0)
	{
		const char **arr = new const char*[1];
		arr[0] = t0;
		return detail::Values<const char*>(arr, 1);
	}
	
	detail::Values<const char*> Values(const char *t0, const char *t1)
	{
		const char **arr = new const char*[2];
		arr[0] = t0;
		arr[1] = t1;
		return detail::Values<const char*>(arr, 2);
	}
	
	detail::Values<const char*> Values(const char *t0, const char *t1, const char *t2)
	{
		const char **arr = new const char*[3];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		return detail::Values<const char*>(arr, 3);
	}
	
	detail::Values<const char*> Values(const char *t0, const char *t1, const char *t2, const char *t3)
	{
		const char **arr = new const char*[4];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		arr[3] = t3;
		return detail::Values<const char*>(arr, 4);
	}
	
	detail::Values<const char*> Values(const char *t0, const char *t1, const char *t2, const char *t3, const char *t4)
	{
		const char **arr = new const char*[5];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		arr[3] = t3;
		arr[4] = t4;
		return detail::Values<const char*>(arr, 5);
	}
	
	detail::Values<const char*> Values(const char *t0, const char *t1, const char *t2, const char *t3, const char *t4, const char *t5)
	{
		const char **arr = new const char*[6];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		arr[3] = t3;
		arr[4] = t4;
		arr[5] = t5;
		return detail::Values<const char*>(arr, 6);
	}
	
	detail::Values<const char*> Values(const char *t0, const char *t1, const char *t2, const char *t3, const char *t4, const char *t5, const char *t6)
	{
		const char **arr = new const char*[7];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		arr[3] = t3;
		arr[4] = t4;
		arr[5] = t5;
		arr[6] = t6;
		return detail::Values<const char*>(arr, 7);
	}
	
	detail::Values<const char*> Values(const char *t0, const char *t1, const char *t2, const char *t3, const char *t4, const char *t5, const char *t6, const char *t7)
	{
		const char **arr = new const char*[8];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		arr[3] = t3;
		arr[4] = t4;
		arr[5] = t5;
		arr[6] = t6;
		arr[7] = t7;
		return detail::Values<const char*>(arr, 8);
	}
	
	detail::Values<const char*> Values(const char *t0, const char *t1, const char *t2, const char *t3, const char *t4, const char *t5, const char *t6, const char *t7, const char *t8)
	{
		const char **arr = new const char*[9];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		arr[3] = t3;
		arr[4] = t4;
		arr[5] = t5;
		arr[6] = t6;
		arr[7] = t7;
		arr[8] = t8;
		return detail::Values<const char*>(arr, 9);
	}
	
	detail::Values<const char*> Values(const char *t0, const char *t1, const char *t2, const char *t3, const char *t4, const char *t5, const char *t6, const char *t7, const char *t8, const char *t9)
	{
		const char **arr = new const char*[10];
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
		return detail::Values<const char*>(arr, 10);
	}


	detail::Values<const wchar_t*> Values(const wchar_t *t0)
	{
		const wchar_t **arr = new const wchar_t*[1];
		arr[0] = t0;
		return detail::Values<const wchar_t*>(arr, 1);
	}
	
	detail::Values<const wchar_t*> Values(const wchar_t *t0, const wchar_t *t1)
	{
		const wchar_t **arr = new const wchar_t*[2];
		arr[0] = t0;
		arr[1] = t1;
		return detail::Values<const wchar_t*>(arr, 2);
	}
	
	detail::Values<const wchar_t*> Values(const wchar_t *t0, const wchar_t *t1, const wchar_t *t2)
	{
		const wchar_t **arr = new const wchar_t*[3];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		return detail::Values<const wchar_t*>(arr, 3);
	}
	
	detail::Values<const wchar_t*> Values(const wchar_t *t0, const wchar_t *t1, const wchar_t *t2, const wchar_t *t3)
	{
		const wchar_t **arr = new const wchar_t*[4];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		arr[3] = t3;
		return detail::Values<const wchar_t*>(arr, 4);
	}
	
	detail::Values<const wchar_t*> Values(const wchar_t *t0, const wchar_t *t1, const wchar_t *t2, const wchar_t *t3, const wchar_t *t4)
	{
		const wchar_t **arr = new const wchar_t*[5];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		arr[3] = t3;
		arr[4] = t4;
		return detail::Values<const wchar_t*>(arr, 5);
	}
	
	detail::Values<const wchar_t*> Values(const wchar_t *t0, const wchar_t *t1, const wchar_t *t2, const wchar_t *t3, const wchar_t *t4, const wchar_t *t5)
	{
		const wchar_t **arr = new const wchar_t*[6];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		arr[3] = t3;
		arr[4] = t4;
		arr[5] = t5;
		return detail::Values<const wchar_t*>(arr, 6);
	}
	
	detail::Values<const wchar_t*> Values(const wchar_t *t0, const wchar_t *t1, const wchar_t *t2, const wchar_t *t3, const wchar_t *t4, const wchar_t *t5, const wchar_t *t6)
	{
		const wchar_t **arr = new const wchar_t*[7];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		arr[3] = t3;
		arr[4] = t4;
		arr[5] = t5;
		arr[6] = t6;
		return detail::Values<const wchar_t*>(arr, 7);
	}
	
	detail::Values<const wchar_t*> Values(const wchar_t *t0, const wchar_t *t1, const wchar_t *t2, const wchar_t *t3, const wchar_t *t4, const wchar_t *t5, const wchar_t *t6, const wchar_t *t7)
	{
		const wchar_t **arr = new const wchar_t*[8];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		arr[3] = t3;
		arr[4] = t4;
		arr[5] = t5;
		arr[6] = t6;
		arr[7] = t7;
		return detail::Values<const wchar_t*>(arr, 8);
	}
	
	detail::Values<const wchar_t*> Values(const wchar_t *t0, const wchar_t *t1, const wchar_t *t2, const wchar_t *t3, const wchar_t *t4, const wchar_t *t5, const wchar_t *t6, const wchar_t *t7, const wchar_t *t8)
	{
		const wchar_t **arr = new const wchar_t*[9];
		arr[0] = t0;
		arr[1] = t1;
		arr[2] = t2;
		arr[3] = t3;
		arr[4] = t4;
		arr[5] = t5;
		arr[6] = t6;
		arr[7] = t7;
		arr[8] = t8;
		return detail::Values<const wchar_t*>(arr, 9);
	}
	
	detail::Values<const wchar_t*> Values(const wchar_t *t0, const wchar_t *t1, const wchar_t *t2, const wchar_t *t3, const wchar_t *t4, const wchar_t *t5, const wchar_t *t6, const wchar_t *t7, const wchar_t *t8, const wchar_t *t9)
	{
		const wchar_t **arr = new const wchar_t*[10];
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
		return detail::Values<const wchar_t*>(arr, 10);
	}
}
