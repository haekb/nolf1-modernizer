# Microsoft Developer Studio Project File - Name="MFCStub" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=MFCStub - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MFCStub60.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MFCStub60.mak" CFG="MFCStub - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MFCStub - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "MFCStub - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "MFCStub - Win32 Final" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "MFCStub60"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MFCStub - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\built\Release\MFCStub"
# PROP Intermediate_Dir "..\built\Release\MFCStub"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\stdlith" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Built\Release\MFCStub\MFCStub.lib"

!ELSEIF  "$(CFG)" == "MFCStub - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\built\Debug\MFCStub"
# PROP Intermediate_Dir "..\built\Debug\MFCStub"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /I "..\stdlith" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Built\Debug\MFCStub\MFCStub.lib"

!ELSEIF  "$(CFG)" == "MFCStub - Win32 Final"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Final"
# PROP BASE Intermediate_Dir "Final"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\built\Final\MFCStub"
# PROP Intermediate_Dir "..\built\Final\MFCStub"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\stdlith" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_FINAL" /FR /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\stdlith" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_FINAL" /FR /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Built\Final\MFCStub\MFCStub.lib"
# ADD LIB32 /nologo /out:"..\Built\Final\MFCStub\MFCStub.lib"

!ENDIF 

# Begin Target

# Name "MFCStub - Win32 Release"
# Name "MFCStub - Win32 Debug"
# Name "MFCStub - Win32 Final"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\mfcs_point.cpp
# End Source File
# Begin Source File

SOURCE=.\mfcs_rect.cpp
# End Source File
# Begin Source File

SOURCE=.\mfcs_string.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\mfcs_misc.h
# End Source File
# Begin Source File

SOURCE=.\mfcs_point.h
# End Source File
# Begin Source File

SOURCE=.\mfcs_rect.h
# End Source File
# Begin Source File

SOURCE=.\mfcs_string.h
# End Source File
# Begin Source File

SOURCE=.\mfcs_types.h
# End Source File
# Begin Source File

SOURCE=.\mfcstub.h
# End Source File
# Begin Source File

SOURCE=.\Stdafx.h
# End Source File
# End Group
# End Target
# End Project
