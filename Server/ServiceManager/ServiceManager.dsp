# Microsoft Developer Studio Project File - Name="ServiceManager" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ServiceManager - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ServiceManager.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ServiceManager.mak" CFG="ServiceManager - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ServiceManager - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ServiceManager - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ServiceManager - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /nodefaultlib:"LIBC" /out:"../Output/ServiceManager.exe"
# SUBTRACT LINK32 /incremental:yes /debug

!ELSEIF  "$(CFG)" == "ServiceManager - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /incremental:no

!ENDIF 

# Begin Target

# Name "ServiceManager - Win32 Release"
# Name "ServiceManager - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AddFileDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BadIDDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BadIDSet.cpp
# End Source File
# Begin Source File

SOURCE=.\BadSerialSet.cpp
# End Source File
# Begin Source File

SOURCE=.\BankSerialDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BankSerialSet.cpp
# End Source File
# Begin Source File

SOURCE=.\BankSet.cpp
# End Source File
# Begin Source File

SOURCE=.\BillDate.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientLogSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientPayDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientPaySet.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientSelectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientSerialSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientSock.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigFMPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigGSPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigSMPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigUMPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ConvSerialDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Count.cpp
# End Source File
# Begin Source File

SOURCE=.\CountView.cpp
# End Source File
# Begin Source File

SOURCE=.\CurrentUserSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteClientDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DelFileDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FileManager.cpp
# End Source File
# Begin Source File

SOURCE=.\FindBankDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FindUserDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LogDataSet.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LogSet.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Msg.cpp
# End Source File
# Begin Source File

SOURCE=.\NewBankDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NewSerialDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NoticeSetDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\NumSerialDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PatchVer.cpp
# End Source File
# Begin Source File

SOURCE=.\PayDetailDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintAddressDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintBillDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RegDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchClientDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchLogDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SelServerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SelServiceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SerialSet.cpp
# End Source File
# Begin Source File

SOURCE=.\Server.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerConfigDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Service.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceConfigDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceManager.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceManager.rc
# End Source File
# Begin Source File

SOURCE=.\ServiceManagerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceManagerView.cpp
# End Source File
# Begin Source File

SOURCE=.\Session.cpp
# End Source File
# Begin Source File

SOURCE=.\SessionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UserCountSet.cpp
# End Source File
# Begin Source File

SOURCE=.\UserDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UserManager.cpp
# End Source File
# Begin Source File

SOURCE=.\UserSet.cpp
# End Source File
# Begin Source File

SOURCE=.\VerSet.cpp
# End Source File
# Begin Source File

SOURCE=.\VersionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ZipCompress.cpp
# End Source File
# Begin Source File

SOURCE=.\ZipFileViewDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AddFileDlg.h
# End Source File
# Begin Source File

SOURCE=.\BadIDDlg.h
# End Source File
# Begin Source File

SOURCE=.\BadIDSet.h
# End Source File
# Begin Source File

SOURCE=.\BadSerialSet.h
# End Source File
# Begin Source File

SOURCE=.\BankSerialDlg.h
# End Source File
# Begin Source File

SOURCE=.\BankSerialSet.h
# End Source File
# Begin Source File

SOURCE=.\BankSet.h
# End Source File
# Begin Source File

SOURCE=.\BillDate.h
# End Source File
# Begin Source File

SOURCE=.\ClientDlg.h
# End Source File
# Begin Source File

SOURCE=.\ClientListDlg.h
# End Source File
# Begin Source File

SOURCE=.\ClientLogSet.h
# End Source File
# Begin Source File

SOURCE=.\ClientPayDlg.h
# End Source File
# Begin Source File

SOURCE=.\ClientPaySet.h
# End Source File
# Begin Source File

SOURCE=.\ClientSelectDlg.h
# End Source File
# Begin Source File

SOURCE=.\ClientSerialSet.h
# End Source File
# Begin Source File

SOURCE=.\ClientSet.h
# End Source File
# Begin Source File

SOURCE=.\ClientSock.h
# End Source File
# Begin Source File

SOURCE=.\ColumnTitle.h
# End Source File
# Begin Source File

SOURCE=.\ConfigFMPage.h
# End Source File
# Begin Source File

SOURCE=.\ConfigGSPage.h
# End Source File
# Begin Source File

SOURCE=.\ConfigSheet.h
# End Source File
# Begin Source File

SOURCE=.\ConfigSMPage.h
# End Source File
# Begin Source File

SOURCE=.\ConfigUMPage.h
# End Source File
# Begin Source File

SOURCE=.\ConvSerialDlg.h
# End Source File
# Begin Source File

SOURCE=.\Count.h
# End Source File
# Begin Source File

SOURCE=.\CountView.h
# End Source File
# Begin Source File

SOURCE=.\CurrentUserSet.h
# End Source File
# Begin Source File

SOURCE=.\DeleteClientDlg.h
# End Source File
# Begin Source File

SOURCE=.\DelFileDlg.h
# End Source File
# Begin Source File

SOURCE=.\FileManager.h
# End Source File
# Begin Source File

SOURCE=.\FindBankDlg.h
# End Source File
# Begin Source File

SOURCE=.\FindUserDlg.h
# End Source File
# Begin Source File

SOURCE=.\LogDataSet.h
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.h
# End Source File
# Begin Source File

SOURCE=.\LogSet.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Msg.h
# End Source File
# Begin Source File

SOURCE=.\NewBankDlg.h
# End Source File
# Begin Source File

SOURCE=.\NewSerialDlg.h
# End Source File
# Begin Source File

SOURCE=.\NoticeSetDialog.h
# End Source File
# Begin Source File

SOURCE=.\NumSerialDlg.h
# End Source File
# Begin Source File

SOURCE=.\PatchVer.h
# End Source File
# Begin Source File

SOURCE=.\PayDetailDlg.h
# End Source File
# Begin Source File

SOURCE=.\PrintAddressDlg.h
# End Source File
# Begin Source File

SOURCE=.\PrintBillDlg.h
# End Source File
# Begin Source File

SOURCE=.\RegDlg.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SearchClientDlg.h
# End Source File
# Begin Source File

SOURCE=.\SearchLogDlg.h
# End Source File
# Begin Source File

SOURCE=.\SelServerDlg.h
# End Source File
# Begin Source File

SOURCE=.\SelServiceDlg.h
# End Source File
# Begin Source File

SOURCE=.\SerialSet.h
# End Source File
# Begin Source File

SOURCE=.\Server.h
# End Source File
# Begin Source File

SOURCE=.\ServerConfigDlg.h
# End Source File
# Begin Source File

SOURCE=.\Service.h
# End Source File
# Begin Source File

SOURCE=.\ServiceConfigDlg.h
# End Source File
# Begin Source File

SOURCE=.\ServiceManager.h
# End Source File
# Begin Source File

SOURCE=.\ServiceManagerDoc.h
# End Source File
# Begin Source File

SOURCE=.\ServiceManagerView.h
# End Source File
# Begin Source File

SOURCE=.\Session.h
# End Source File
# Begin Source File

SOURCE=.\SessionDlg.h
# End Source File
# Begin Source File

SOURCE=.\StatusConst.h
# End Source File
# Begin Source File

SOURCE=.\StatusView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\UserCountSet.h
# End Source File
# Begin Source File

SOURCE=.\UserDlg.h
# End Source File
# Begin Source File

SOURCE=.\UserManager.h
# End Source File
# Begin Source File

SOURCE=.\UserSet.h
# End Source File
# Begin Source File

SOURCE=.\VerSet.h
# End Source File
# Begin Source File

SOURCE=.\VersionDlg.h
# End Source File
# Begin Source File

SOURCE=.\ZipCompress.h
# End Source File
# Begin Source File

SOURCE=.\ZipFileViewDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ServiceManager.ico
# End Source File
# Begin Source File

SOURCE=.\res\ServiceManager.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ServiceManagerDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\ServiceManager.reg
# End Source File
# End Target
# End Project
