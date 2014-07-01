//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICHBOOL_BAD_BLOCK_H__QM
#define RICHBOOL_BAD_BLOCK_H__QM

#include "stddef.h"
#include "richbool/export.hpp"

namespace RichBool
{
	RICHBOOL_DLL_API bool BadBlock(const void *p, size_t size);

	template<typename T>
	bool BadPtr(const T *pblock)
	{
		return BadBlock(pblock, sizeof(T));
	}
}

#endif // #ifndef RICHBOOL_BAD_BLOCK_H__QM
