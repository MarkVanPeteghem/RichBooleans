# Microsoft Developer Studio Project File - Name="RichBoolDLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=RichBoolDLL - Win32 ReleaseMTD
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RichBoolDLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RichBoolDLL.mak" CFG="RichBoolDLL - Win32 ReleaseMTD"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RichBoolDLL - Win32 ReleaseMTD" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RichBoolDLL - Win32 DebugMTD" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RichBoolDLL - Win32 ReleaseWxMTD" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RichBoolDLL - Win32 DebugWxMTD" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RichBoolDLL - Win32 DebugMT" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RichBoolDLL - Win32 ReleaseMT" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RichBoolDLL - Win32 DebugST" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RichBoolDLL - Win32 ReleaseST" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RichBoolDLL - Win32 ReleaseMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMTD"
# PROP BASE Intermediate_Dir "ReleaseMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "ReleaseMTDDLL-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RICHBOOLDLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "./include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RICHBOOLDLL_EXPORTS" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /dll /machine:I386 /out:"lib/richbool-vc6-mt-2_2_2.dll"

!ELSEIF  "$(CFG)" == "RichBoolDLL - Win32 DebugMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugMTD"
# PROP BASE Intermediate_Dir "DebugMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "DebugMTDDLL-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RICHBOOLDLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RICHBOOLDLL_EXPORTS" /FD /GZ /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /dll /machine:I386
# ADD LINK32 /nologo /dll /machine:I386 /nodefaultlib:"nafxcwd.lib" /out:"lib/richbool-vc6-mt-gd-2_2_2.dll"

!ELSEIF  "$(CFG)" == "RichBoolDLL - Win32 ReleaseWxMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseWxMTD"
# PROP BASE Intermediate_Dir "ReleaseWxMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "ReleaseWxMTDDLL-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "./include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RICHBOOLDLL_EXPORTS" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "./include" /I "$(WXWIN)/include" /I "$(WXWIN)/include/msvc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RICHBOOLDLL_EXPORTS" /D "RICHBOOL_USE_WX" /FR /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /dll /machine:I386 /out:"lib/richbool-vc6-mt-wx-2_2_2.dll"

!ELSEIF  "$(CFG)" == "RichBoolDLL - Win32 DebugWxMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugWxMTD"
# PROP BASE Intermediate_Dir "DebugWxMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "DebugWxMTDDLL-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "./include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RICHBOOLDLL_EXPORTS" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "./include" /I "$(WXWIN)/include" /I "$(WXWIN)/include/msvc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RICHBOOLDLL_EXPORTS" /D "RICHBOOL_USE_WX" /FR /FD /GZ /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /dll /machine:I386 /out:"lib/richbool-vc6-mt-gd-wx-2_2_2.dll"

!ELSEIF  "$(CFG)" == "RichBoolDLL - Win32 DebugMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugMT"
# PROP BASE Intermediate_Dir "DebugMT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "DebugMTDLL-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RICHBOOLDLL_EXPORTS" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I ".\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RICHBOOLDLL_EXPORTS" /FD /GZ /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /dll /machine:I386 /out:"lib/richbool-vc6-mt-sgd-2_2_2.dll"

!ELSEIF  "$(CFG)" == "RichBoolDLL - Win32 ReleaseMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMT"
# PROP BASE Intermediate_Dir "ReleaseMT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "ReleaseMTDLL-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "./include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RICHBOOLDLL_EXPORTS" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "./include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RICHBOOLDLL_EXPORTS" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /dll /machine:I386 /out:"lib/richbool-vc6-mt-s-2_2_2.dll"

!ELSEIF  "$(CFG)" == "RichBoolDLL - Win32 DebugST"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugST"
# PROP BASE Intermediate_Dir "DebugST"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "DebugSTDLL-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RICHBOOLDLL_EXPORTS" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RICHBOOLDLL_EXPORTS" /FD /GZ /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /dll /machine:I386 /out:"lib/richbool-vc6-sgd-2_2_2.dll"

!ELSEIF  "$(CFG)" == "RichBoolDLL - Win32 ReleaseST"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseST"
# PROP BASE Intermediate_Dir "ReleaseST"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "ReleaseSTDLL-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "./include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RICHBOOLDLL_EXPORTS" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "./include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RICHBOOLDLL_EXPORTS" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib shell32.lib /nologo /dll /machine:I386 /out:"lib/richbool-vc6-s-2_2_2.dll"

!ENDIF 

# Begin Target

# Name "RichBoolDLL - Win32 ReleaseMTD"
# Name "RichBoolDLL - Win32 DebugMTD"
# Name "RichBoolDLL - Win32 ReleaseWxMTD"
# Name "RichBoolDLL - Win32 DebugWxMTD"
# Name "RichBoolDLL - Win32 DebugMT"
# Name "RichBoolDLL - Win32 ReleaseMT"
# Name "RichBoolDLL - Win32 DebugST"
# Name "RichBoolDLL - Win32 ReleaseST"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\analysis.cpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\analysis.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\auto_link.hpp
# End Source File
# Begin Source File

SOURCE=.\src\badblock.cpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\badblock.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\base.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\basic_rb.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\bind.hpp
# End Source File
# Begin Source File

SOURCE=.\src\bit_iterator.cpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\bit_iterator.hpp
# End Source File
# Begin Source File

SOURCE=.\src\bool.cpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\bool.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\config.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\containers.hpp
# End Source File
# Begin Source File

SOURCE=.\src\der_analysis.cpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\der_analysis.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\exceptions.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\export.hpp
# End Source File
# Begin Source File

SOURCE=.\src\expression.cpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\expression.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\fileutils.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\finddiff.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\findinrange.hpp
# End Source File
# Begin Source File

SOURCE=.\src\functors.cpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\functors.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\getarg.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\getpoints.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\getvalue.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\logic.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\mfcexceptions.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\mfcstream.hpp
# End Source File
# Begin Source File

SOURCE=.\src\mfcstring.cpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\mfcstring.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\mfcstring1.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\pair.hpp
# End Source File
# Begin Source File

SOURCE=.\src\portability.cpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\portability.hpp
# End Source File
# Begin Source File

SOURCE=.\src\ranges.cpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\ranges.hpp
# End Source File
# Begin Source File

SOURCE=.\src\regexp.cpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\regexp.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\relation.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\richbool.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\shared_ptr.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\std.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\stdexceptions.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\stdstring.hpp
# End Source File
# Begin Source File

SOURCE=.\src\string.cpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\string.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\swap.hpp
# End Source File
# Begin Source File

SOURCE=.\src\tmpbool.cpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\tmpbool.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\tostring.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\values.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\version.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\wx.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\wx_iter.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\wxstring.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\xcontainers.hpp
# End Source File
# End Group
# End Target
# End Project
