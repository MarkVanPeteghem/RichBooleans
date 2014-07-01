# Microsoft Developer Studio Project File - Name="RichBool" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RichBool - Win32 ReleaseMTD
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RichBool.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RichBool.mak" CFG="RichBool - Win32 ReleaseMTD"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RichBool - Win32 ReleaseMTD" (based on "Win32 (x86) Static Library")
!MESSAGE "RichBool - Win32 DebugMTD" (based on "Win32 (x86) Static Library")
!MESSAGE "RichBool - Win32 ReleaseWxMTD" (based on "Win32 (x86) Static Library")
!MESSAGE "RichBool - Win32 DebugWxMTD" (based on "Win32 (x86) Static Library")
!MESSAGE "RichBool - Win32 DebugMT" (based on "Win32 (x86) Static Library")
!MESSAGE "RichBool - Win32 ReleaseMT" (based on "Win32 (x86) Static Library")
!MESSAGE "RichBool - Win32 DebugST" (based on "Win32 (x86) Static Library")
!MESSAGE "RichBool - Win32 ReleaseST" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RichBool - Win32 ReleaseMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMTD"
# PROP BASE Intermediate_Dir "ReleaseMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "ReleaseMTD-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "./include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/librichbool-vc6-mt-2_2_2.lib"

!ELSEIF  "$(CFG)" == "RichBool - Win32 DebugMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugMTD"
# PROP BASE Intermediate_Dir "DebugMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "DebugMTD-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/librichbool-vc6-mt-gd-2_2_2.lib"

!ELSEIF  "$(CFG)" == "RichBool - Win32 ReleaseWxMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseWxMTD"
# PROP BASE Intermediate_Dir "ReleaseWxMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "ReleaseWxMTD-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "./include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /GX /O2 /I "./include" /I "$(WXWIN)/include" /I "$(WXWIN)/include/msvc" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "RICHBOOL_USE_WX" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/librichbool-vc6-mt-wx-2_2_2.lib"

!ELSEIF  "$(CFG)" == "RichBool - Win32 DebugWxMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugWxMTD"
# PROP BASE Intermediate_Dir "DebugWxMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "DebugWxMTD-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "./include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "./include" /I "$(WXWIN)/include" /I "$(WXWIN)/include/msvc" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "RICHBOOL_USE_WX" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/librichbool-vc6-mt-gd-wx-2_2_2.lib"

!ELSEIF  "$(CFG)" == "RichBool - Win32 DebugMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugMT"
# PROP BASE Intermediate_Dir "DebugMT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "DebugMT-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I ".\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/librichbool-vc6-mt-sgd-2_2_2.lib"

!ELSEIF  "$(CFG)" == "RichBool - Win32 ReleaseMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMT"
# PROP BASE Intermediate_Dir "ReleaseMT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "ReleaseMT-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "./include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MT /W3 /GX /O2 /I "./include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/librichbool-vc6-mt-s-2_2_2.lib"

!ELSEIF  "$(CFG)" == "RichBool - Win32 DebugST"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugST"
# PROP BASE Intermediate_Dir "DebugST"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "DebugST-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/librichbool-vc6-sgd-2_2_2.lib"

!ELSEIF  "$(CFG)" == "RichBool - Win32 ReleaseST"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseST"
# PROP BASE Intermediate_Dir "ReleaseST"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "ReleaseST-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "./include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /W3 /GX /O2 /I "./include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/librichbool-vc6-s-2_2_2.lib"

!ENDIF 

# Begin Target

# Name "RichBool - Win32 ReleaseMTD"
# Name "RichBool - Win32 DebugMTD"
# Name "RichBool - Win32 ReleaseWxMTD"
# Name "RichBool - Win32 DebugWxMTD"
# Name "RichBool - Win32 DebugMT"
# Name "RichBool - Win32 ReleaseMT"
# Name "RichBool - Win32 DebugST"
# Name "RichBool - Win32 ReleaseST"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\analysis.cpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\analysis.hpp
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

SOURCE=.\src\expression.cpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\expression.hpp
# End Source File
# Begin Source File

SOURCE=.\src\fileutils.cpp
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

SOURCE=.\include\richbool\getpoints.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\getvalue.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\logic.hpp
# End Source File
# Begin Source File

SOURCE=.\src\mfcexceptions.cpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\mfcexceptions.hpp
# End Source File
# Begin Source File

SOURCE=.\src\mfcstream.cpp
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

SOURCE=.\src\tmpbool.cpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\tmpbool.hpp
# End Source File
# Begin Source File

SOURCE=.\include\richbool\tostring.hpp
# End Source File
# Begin Source File

SOURCE=.\src\values.cpp
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
