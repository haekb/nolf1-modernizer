# Microsoft Developer Studio Project File - Name="ButeMgr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ButeMgr - Win32 Debug MFC DLL
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ButeMgr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ButeMgr.mak" CFG="ButeMgr - Win32 Debug MFC DLL"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ButeMgr - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ButeMgr - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ButeMgr - Win32 Release MFC DLL" (based on "Win32 (x86) Static Library")
!MESSAGE "ButeMgr - Win32 Debug MFC DLL" (based on "Win32 (x86) Static Library")
!MESSAGE "ButeMgr - Win32 Final" (based on "Win32 (x86) Static Library")
!MESSAGE "ButeMgr - Win32 Final MFC DLL" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "ButeMgr"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ButeMgr - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ButeMgr___Win32_Release_No_MFC"
# PROP BASE Intermediate_Dir "ButeMgr___Win32_Release_No_MFC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\built\release\ButeMgr"
# PROP Intermediate_Dir "..\built\release\ButeMgr"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\STLPORT-4.0\STLPORT" /I "..\stdlith" /I "..\mfcstub" /I "..\cryptmgr" /I "..\lith" /D "NDEBUG" /D "_NOMFC" /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Libs\Release\ButeMgr.lib"
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "ButeMgr - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ButeMgr___Win32_Debug_No_MFC"
# PROP BASE Intermediate_Dir "ButeMgr___Win32_Debug_No_MFC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\built\Debug\ButeMgr"
# PROP Intermediate_Dir "..\built\Debug\ButeMgr"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"StdAfx.h" /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /I "..\STLPORT-4.0\STLPORT" /I "..\stdlith" /I "..\mfcstub" /I "..\cryptmgr" /I "..\lith" /D "_DEBUG" /D "_NOMFC" /D "WIN32" /D "_WINDOWS" /Yu"StdAfx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Libs\Debug\ButeMgr.lib"
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "ButeMgr - Win32 Release MFC DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ButeMgr___Win32_Release_MFC_DLL"
# PROP BASE Intermediate_Dir "ButeMgr___Win32_Release_MFC_DLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\built\Release\ButeMgrMFCDll\"
# PROP Intermediate_Dir "..\built\Release\ButeMgrMFCDll\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\incs" /I "..\\" /D "NDEBUG" /D "_NOMFC" /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\STLPORT-4.0\STLPORT" /I "..\stdlith" /I "..\mfcstub" /I "..\cryptmgr" /I "..\lith" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Libs\Release\ButeMgr.lib"
# ADD LIB32 /nologo /out:"..\built\Release\ButeMgrMFCDll\ButeMgrMfcDll.lib"

!ELSEIF  "$(CFG)" == "ButeMgr - Win32 Debug MFC DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ButeMgr___Win32_Debug_MFC_DLL"
# PROP BASE Intermediate_Dir "ButeMgr___Win32_Debug_MFC_DLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\built\Debug\ButeMgrMFCDll\"
# PROP Intermediate_Dir "..\built\Debug\ButeMgrMFCDll\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /ZI /Od /I "..\incs" /I "..\\" /D "_DEBUG" /D "_NOMFC" /D "WIN32" /D "_WINDOWS" /Yu"StdAfx.h" /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /I "..\STLPORT-4.0\STLPORT" /I "..\stdlith" /I "..\mfcstub" /I "..\cryptmgr" /I "..\lith" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /Yu"StdAfx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Libs\Debug\ButeMgr.lib"
# ADD LIB32 /nologo /out:"..\built\Debug\ButeMgrMFCDll\ButeMgrMfcDll.lib"

!ELSEIF  "$(CFG)" == "ButeMgr - Win32 Final"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Final"
# PROP BASE Intermediate_Dir "Final"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\built\Final\ButeMgr"
# PROP Intermediate_Dir "..\built\Final\ButeMgr"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\STLPORT-4.0\STLPORT" /I "..\stdlith" /I "..\mfcstub" /I "..\cryptmgr" /I "..\lith" /D "NDEBUG" /D "_NOMFC" /D "WIN32" /D "_WINDOWS" /D "_FINAL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\STLPORT-4.0\STLPORT" /I "..\stdlith" /I "..\mfcstub" /I "..\cryptmgr" /I "..\lith" /D "NDEBUG" /D "_NOMFC" /D "WIN32" /D "_WINDOWS" /D "_FINAL" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "ButeMgr - Win32 Final MFC DLL"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ButeMgr___Win32_Final_MFC_DLL"
# PROP BASE Intermediate_Dir "ButeMgr___Win32_Final_MFC_DLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\built\Final\ButeMgrMfcDll"
# PROP Intermediate_Dir "..\built\Final\ButeMgrMfcDll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\STLPORT-4.0\STLPORT" /I "..\stdlith" /I "..\mfcstub" /I "..\cryptmgr" /I "..\lith" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\STLPORT-4.0\STLPORT" /I "..\stdlith" /I "..\mfcstub" /I "..\cryptmgr" /I "..\lith" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\built\Release\ButeMgrMFCDll\ButeMgrMfcDll.lib"
# ADD LIB32 /nologo /out:"..\built\Final\ButeMgrMFCDll\ButeMgrMfcDll.lib"

!ENDIF 

# Begin Target

# Name "ButeMgr - Win32 Release"
# Name "ButeMgr - Win32 Debug"
# Name "ButeMgr - Win32 Release MFC DLL"
# Name "ButeMgr - Win32 Debug MFC DLL"
# Name "ButeMgr - Win32 Final"
# Name "ButeMgr - Win32 Final MFC DLL"
# Begin Group "Source Files"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\ARange.cpp
# End Source File
# Begin Source File

SOURCE=.\AVector.cpp
# End Source File
# Begin Source File

SOURCE=.\ButeMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\Stdafx.cpp

!IF  "$(CFG)" == "ButeMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "ButeMgr - Win32 Debug"

# ADD BASE CPP /Yc"StdAfx.h"
# ADD CPP /Yc"StdAfx.h"

!ELSEIF  "$(CFG)" == "ButeMgr - Win32 Release MFC DLL"

!ELSEIF  "$(CFG)" == "ButeMgr - Win32 Debug MFC DLL"

# ADD BASE CPP /Yc"StdAfx.h"
# ADD CPP /Yc"StdAfx.h"

!ELSEIF  "$(CFG)" == "ButeMgr - Win32 Final"

!ELSEIF  "$(CFG)" == "ButeMgr - Win32 Final MFC DLL"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\ARange.h
# End Source File
# Begin Source File

SOURCE=.\AVector.h
# End Source File
# Begin Source File

SOURCE=.\ButeMgr.h
# End Source File
# Begin Source File

SOURCE=.\Stdafx.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ButeMgr.sca
# End Source File
# End Target
# End Project
