# Microsoft Developer Studio Project File - Name="richbooltestmacros" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=richbooltestmacros - Win32 ReleaseMTD
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "richbooltestmacros.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "richbooltestmacros.mak" CFG="richbooltestmacros - Win32 ReleaseMTD"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "richbooltestmacros - Win32 ReleaseMTD" (based on "Win32 (x86) Console Application")
!MESSAGE "richbooltestmacros - Win32 DebugMTD" (based on "Win32 (x86) Console Application")
!MESSAGE "richbooltestmacros - Win32 ReleaseWxMTD" (based on "Win32 (x86) Console Application")
!MESSAGE "richbooltestmacros - Win32 DebugWxMTD" (based on "Win32 (x86) Console Application")
!MESSAGE "richbooltestmacros - Win32 DebugMT" (based on "Win32 (x86) Console Application")
!MESSAGE "richbooltestmacros - Win32 ReleaseMT" (based on "Win32 (x86) Console Application")
!MESSAGE "richbooltestmacros - Win32 DebugST" (based on "Win32 (x86) Console Application")
!MESSAGE "richbooltestmacros - Win32 ReleaseST" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "richbooltestmacros - Win32 ReleaseMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMTD"
# PROP BASE Intermediate_Dir "ReleaseMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMTD-6.0"
# PROP Intermediate_Dir "ReleaseMTD-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../../include" /I "../common" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /FD /Zm250 /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386 /nodefaultlib:"nafxcw.lib" /libpath:"../lib"
# Begin Special Build Tool
TargetPath=.\ReleaseMTD-6.0\richbooltestmacros.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Testing...
PostBuild_Cmds=$(TARGETPATH)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "richbooltestmacros - Win32 DebugMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugMTD"
# PROP BASE Intermediate_Dir "DebugMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugMTD-6.0"
# PROP Intermediate_Dir "DebugMTD-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../../include" /I "../common" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /FD /GZ /Zm250 /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"nafxcwd.lib" /pdbtype:sept /libpath:"../lib"
# Begin Special Build Tool
TargetPath=.\DebugMTD-6.0\richbooltestmacros.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Testing...
PostBuild_Cmds=$(TARGETPATH)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "richbooltestmacros - Win32 ReleaseWxMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseWxMTD"
# PROP BASE Intermediate_Dir "ReleaseWxMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseWxMTD-6.0"
# PROP Intermediate_Dir "ReleaseWxMTD-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /O2 /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "$(WXWIN)/include" /I "$(WXWIN)/lib/vc_lib/msw" /I "../../include" /I "../common" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "RICHBOOL_USE_WX" /FD /Zm250 /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib richbool.lib /nologo /subsystem:console /machine:I386 /libpath:"$(RICHBOOL)\ReleaseMTD"
# ADD LINK32 wxbase28.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib rpcrt4.lib wsock32.lib /nologo /subsystem:console /machine:I386 /libpath:"$(WXWIN)/lib/vc_lib" /libpath:"../lib"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=.\ReleaseWxMTD-6.0\richbooltestmacros.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Testing...
PostBuild_Cmds=$(TARGETPATH)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "richbooltestmacros - Win32 DebugWxMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugWxMTD"
# PROP BASE Intermediate_Dir "DebugWxMTD"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugWxMTD-6.0"
# PROP Intermediate_Dir "DebugWxMTD-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FD /GZ /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(WXWIN)/include" /I "../../include" /I "../common" /I "$(WXWIN)/include/msvc" /D "WIN32" /D "__WXDEBUG__" /D WXDEBUG=1 /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "RICHBOOL_USE_WX" /D "_AFXDLL" /FR /FD /Zm250 /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib richbool.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"$(RICHBOOL)\DebugMTD"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib rpcrt4.lib wsock32.lib wxbase28d.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"$(WXWIN)/lib/vc_lib" /libpath:"$(WXWIN)/contrib/lib" /libpath:"../lib"
# Begin Special Build Tool
TargetPath=.\DebugWxMTD-6.0\richbooltestmacros.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Testing...
PostBuild_Cmds=$(TARGETPATH)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "richbooltestmacros - Win32 DebugMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugMT"
# PROP BASE Intermediate_Dir "DebugMT"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugMT-6.0"
# PROP Intermediate_Dir "DebugMT-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FD /GZ /Zm250 /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /I "../../include" /I "../common" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FD /GZ /Zm250 /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib richbool.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"..\DebugMTD"
# ADD LINK32 nafxcwd.lib libcmtd.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"nafxcwd.lib libcmtd.lib" /pdbtype:sept /libpath:"../lib"
# Begin Special Build Tool
TargetPath=.\DebugMT-6.0\richbooltestmacros.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Testing...
PostBuild_Cmds=$(TARGETPATH)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "richbooltestmacros - Win32 ReleaseMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMT"
# PROP BASE Intermediate_Dir "ReleaseMT"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMT-6.0"
# PROP Intermediate_Dir "ReleaseMT-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /I "../include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I "../../include" /I "../common" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /Zm250 /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib richbool.lib /nologo /subsystem:console /machine:I386 /libpath:"..\ReleaseMTD"
# ADD LINK32 nafxcw.lib libcmt.lib /nologo /subsystem:console /machine:I386 /nodefaultlib:"nafxcw.lib libcmt.lib" /libpath:"../lib"
# Begin Special Build Tool
TargetPath=.\ReleaseMT-6.0\richbooltestmacros.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Testing...
PostBuild_Cmds=$(TARGETPATH)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "richbooltestmacros - Win32 DebugST"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugST"
# PROP BASE Intermediate_Dir "DebugST"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugST-6.0"
# PROP Intermediate_Dir "DebugST-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FD /GZ /Zm250 /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /I "../../include" /I "../common" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FD /GZ /Zm250 /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib richbool.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"..\DebugMTD"
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"../lib"
# Begin Special Build Tool
TargetPath=.\DebugST-6.0\richbooltestmacros.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Testing...
PostBuild_Cmds=$(TARGETPATH)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "richbooltestmacros - Win32 ReleaseST"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseST"
# PROP BASE Intermediate_Dir "ReleaseST"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseST-6.0"
# PROP Intermediate_Dir "ReleaseST-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /I "../include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /Zm250 /c
# ADD CPP /nologo /W3 /GR /GX /O2 /I "../../include" /I "../common" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /Zm250 /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib richbool.lib /nologo /subsystem:console /machine:I386 /libpath:"..\ReleaseMTD"
# ADD LINK32 /nologo /subsystem:console /machine:I386 /libpath:"../lib"
# Begin Special Build Tool
TargetPath=.\ReleaseST-6.0\richbooltestmacros.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Testing...
PostBuild_Cmds=$(TARGETPATH)
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "richbooltestmacros - Win32 ReleaseMTD"
# Name "richbooltestmacros - Win32 DebugMTD"
# Name "richbooltestmacros - Win32 ReleaseWxMTD"
# Name "richbooltestmacros - Win32 DebugWxMTD"
# Name "richbooltestmacros - Win32 DebugMT"
# Name "richbooltestmacros - Win32 ReleaseMT"
# Name "richbooltestmacros - Win32 DebugST"
# Name "richbooltestmacros - Win32 ReleaseST"
# Begin Group "Tests"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\and_test.cpp
# End Source File
# Begin Source File

SOURCE=.\argument_hiding.cpp
# End Source File
# Begin Source File

SOURCE=.\basictest.cpp
# End Source File
# Begin Source File

SOURCE=.\bindtest.cpp
# End Source File
# Begin Source File

SOURCE=.\bits_test.cpp
# End Source File
# Begin Source File

SOURCE=.\equal_using_less.cpp
# End Source File
# Begin Source File

SOURCE=.\evaluate_test.cpp
# End Source File
# Begin Source File

SOURCE=.\files_test.cpp
# End Source File
# Begin Source File

SOURCE=.\getarg_test.cpp
# End Source File
# Begin Source File

SOURCE=.\getmember_test.cpp
# End Source File
# Begin Source File

SOURCE=.\logic_test.cpp
# End Source File
# Begin Source File

SOURCE=.\macro_safety.cpp
# End Source File
# Begin Source File

SOURCE=.\mfc_test.cpp
# End Source File
# Begin Source File

SOURCE=.\notext_test.cpp
# End Source File
# Begin Source File

SOURCE=.\or_test.cpp
# End Source File
# Begin Source File

SOURCE=.\person_test.cpp
# End Source File
# Begin Source File

SOURCE=.\pointertest.cpp
# End Source File
# Begin Source File

SOURCE=.\single_arg_test.cpp
# End Source File
# Begin Source File

SOURCE=.\std_exceptions_test.cpp
# End Source File
# Begin Source File

SOURCE=.\string_locale_test.cpp
# End Source File
# Begin Source File

SOURCE=.\string_test.cpp
# End Source File
# Begin Source File

SOURCE=.\typeinfo_test.cpp
# End Source File
# Begin Source File

SOURCE=.\wrapper_test.cpp
# End Source File
# Begin Source File

SOURCE=.\wstring_test.cpp
# End Source File
# Begin Source File

SOURCE=.\wx_classinfo_test.cpp
# End Source File
# Begin Source File

SOURCE=.\xor_test.cpp
# End Source File
# End Group
# Begin Group "Test framework"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\common\rbtest.cpp
# End Source File
# Begin Source File

SOURCE=..\common\rbtest.hpp
# End Source File
# Begin Source File

SOURCE=..\common\richbooltest.cpp
# End Source File
# End Group
# Begin Group "Helper code"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\common\composite_expressions.hpp
# End Source File
# Begin Source File

SOURCE=..\common\int_less.hpp
# End Source File
# Begin Source File

SOURCE=..\common\predicates.hpp
# End Source File
# Begin Source File

SOURCE=..\common\string_cmp.hpp
# End Source File
# Begin Source File

SOURCE=..\common\testable_analysis_for_ranges.hpp
# End Source File
# Begin Source File

SOURCE=..\common\testable_analysis_with_strings.hpp
# End Source File
# End Group
# End Target
# End Project
