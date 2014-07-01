//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_MFC_EXCEPTIONS_H__QM
#define RICH_BOOL_MFC_EXCEPTIONS_H__QM

#include <afx.h>
#include <afxwin.h>
#include <afxole.h>
#include <afxdb.h>
#include <afxdao.h>
#include <afxinet.h>

#include "richbool/exceptions.hpp"

RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(CException)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(CMemoryException)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(CNotSupportedException)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(CArchiveException)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(CFileException)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(CResourceException)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(COleException)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(CDBException)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(COleDispatchException)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(CUserException)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(CDaoException)
RICHBOOL_MAKE_EXCEPTION_TYPE_NAME(CInternetException)

namespace RichBool
{
	inline detail::String GetExceptionInfo(CException &exc)
	{
		char str[255];
		exc.GetErrorMessage(str, sizeof(str)-1);
		return str;
	}
}

#endif // #ifndef RICH_BOOL_MFC_EXCEPTIONS_H__QM
