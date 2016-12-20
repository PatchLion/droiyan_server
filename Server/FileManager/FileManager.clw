; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPatchVer
LastTemplate=CRecordset
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FileManager.h"

ClassCount=5
Class1=CFileManagerApp
Class2=CFileManagerDlg

ResourceCount=1
Resource1=IDR_MAINFRAME
Class3=CSessThread
Class4=CVerSet
Class5=CPatchVer

[CLS:CFileManagerApp]
Type=0
HeaderFile=FileManager.h
ImplementationFile=FileManager.cpp
Filter=N

[CLS:CFileManagerDlg]
Type=0
HeaderFile=FileManagerDlg.h
ImplementationFile=FileManagerDlg.cpp
Filter=D



[CLS:CSessThread]
Type=0
HeaderFile=SessThread.h
ImplementationFile=SessThread.cpp
BaseClass=CWinThread
Filter=N
VirtualFilter=TC
LastObject=CSessThread

[CLS:CVerSet]
Type=0
HeaderFile=VerSet.h
ImplementationFile=VerSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CVerSet]
DB=1
DBType=ODBC
ColumnCount=3
Column1=[strFileName], 12, 255
Column2=[strCompName], 12, 255
Column3=[wVersion], 5, 2

[CLS:CPatchVer]
Type=0
HeaderFile=PatchVer.h
ImplementationFile=PatchVer.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CPatchVer]
DB=1
DBType=ODBC
ColumnCount=2
Column1=[sVersion], 5, 2
Column2=[strFileName], 12, 255

