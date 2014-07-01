//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_STD_EXCEPTIONS_H__QM
#define RICH_BOOL_STD_EXCEPTIONS_H__QM

#include "richbool/exceptions.hpp"
#include <stdexcept>

RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(std::exception)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(std::bad_cast)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(std::bad_alloc)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(std::bad_exception)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(std::bad_typeid)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(std::ios_base::failure)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(std::domain_error)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(std::invalid_argument)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(std::length_error)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(std::out_of_range)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(std::logic_error)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(std::overflow_error)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(std::range_error)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(std::underflow_error)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(std::runtime_error)

namespace RichBool
{
	inline detail::String GetExceptionInfo(const std::exception &exc)
	{
		return exc.what();
	}
}

#endif // #ifndef RICH_BOOL_STD_EXCEPTIONS_H__QM












