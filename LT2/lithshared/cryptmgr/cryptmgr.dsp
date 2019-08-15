# Microsoft Developer Studio Project File - Name="CryptMgr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=CryptMgr - Win32 Debug MFC DLL
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cryptmgr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cryptmgr.mak" CFG="CryptMgr - Win32 Debug MFC DLL"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CryptMgr - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "CryptMgr - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "CryptMgr - Win32 Release MFC DLL" (based on "Win32 (x86) Static Library")
!MESSAGE "CryptMgr - Win32 Debug MFC DLL" (based on "Win32 (x86) Static Library")
!MESSAGE "CryptMgr - Win32 Final" (based on "Win32 (x86) Static Library")
!MESSAGE "CryptMgr - Win32 Final MFC DLL" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "cryptmgr"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CryptMgr - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\built\Release\CryptMgr"
# PROP Intermediate_Dir "..\built\Release\CryptMgr"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "CryptMgr - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\built\Debug\CryptMgr"
# PROP Intermediate_Dir "..\built\Debug\CryptMgr"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "CryptMgr - Win32 Release MFC DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CryptMgr___Win32_Release_MFC_DLL"
# PROP BASE Intermediate_Dir "CryptMgr___Win32_Release_MFC_DLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\built\Release\CryptMgrMfcDll"
# PROP Intermediate_Dir "..\built\Release\CryptMgrMfcDll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D "NO_PRAGMA_LIBS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Libs\Release\CryptMgr.lib"
# ADD LIB32 /nologo /out:"..\built\Release\CryptMgrMfcDll\CryptMgrMfcDll.lib"

!ELSEIF  "$(CFG)" == "CryptMgr - Win32 Debug MFC DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CryptMgr___Win32_Debug_MFC_DLL"
# PROP BASE Intermediate_Dir "CryptMgr___Win32_Debug_MFC_DLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\built\Debug\CryptMgrMfcDll"
# PROP Intermediate_Dir "..\built\Debug\CryptMgrMfcDll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /D "_DEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D "NO_PRAGMA_LIBS" /FR /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Libs\Debug\CryptMgr.lib"
# ADD LIB32 /nologo /out:"..\built\Debug\CryptMgrMfcDll\CryptMgrMfcDll.lib"

!ELSEIF  "$(CFG)" == "CryptMgr - Win32 Final"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Final"
# PROP BASE Intermediate_Dir "Final"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\built\Final\CryptMgr"
# PROP Intermediate_Dir "..\built\Final\CryptMgr"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_FINAL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_FINAL" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "CryptMgr - Win32 Final MFC DLL"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CryptMgr___Win32_Final_MFC_DLL"
# PROP BASE Intermediate_Dir "CryptMgr___Win32_Final_MFC_DLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\built\Final\CryptMgrMfcDll"
# PROP Intermediate_Dir "..\built\Final\CryptMgrMfcDll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D "NO_PRAGMA_LIBS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D "NO_PRAGMA_LIBS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\built\Release\CryptMgrMfcDll\CryptMgrMfcDll.lib"
# ADD LIB32 /nologo /out:"..\built\Final\CryptMgrMfcDll\CryptMgrMfcDll.lib"

!ENDIF 

# Begin Target

# Name "CryptMgr - Win32 Release"
# Name "CryptMgr - Win32 Debug"
# Name "CryptMgr - Win32 Release MFC DLL"
# Name "CryptMgr - Win32 Debug MFC DLL"
# Name "CryptMgr - Win32 Final"
# Name "CryptMgr - Win32 Final MFC DLL"
# Begin Group "Source Files"

# PROP Default_Filter ".cpp; .h"
# Begin Source File

SOURCE=.\blowfish.cpp
# End Source File
# Begin Source File

SOURCE=.\BlowFish.h
# End Source File
# Begin Source File

SOURCE=.\CryptMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\CryptMgr.h
# End Source File
# End Group
# End Target
# End Project
