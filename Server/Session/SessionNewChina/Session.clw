; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCP_IP_MASKTableSet
LastTemplate=CRecordset
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Session.h"

ClassCount=4
Class1=CSessionApp
Class2=CSessionDlg

ResourceCount=1
Resource1=IDR_MAINFRAME
Class3=CSessThread
Class4=CCP_IP_MASKTableSet

[CLS:CSessionApp]
Type=0
HeaderFile=Session.h
ImplementationFile=Session.cpp
Filter=N

[CLS:CSessionDlg]
Type=0
HeaderFile=SessionDlg.h
ImplementationFile=SessionDlg.cpp
Filter=D



[CLS:CSessThread]
Type=0
HeaderFile=SessThread.h
ImplementationFile=SessThread.cpp
BaseClass=CWinThread
Filter=N
VirtualFilter=TC
LastObject=CSessThread

[CLS:CCP_IP_MASKTableSet]
Type=0
HeaderFile=CP_IP_MASKTableSet.h
ImplementationFile=CP_IP_MASKTableSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CCP_IP_MASKTableSet]
DB=1
DBType=ODBC
ColumnCount=7
Column1=[num], 4, 4
Column2=[strclientid], 12, 30
Column3=[startip], 12, 16
Column4=[startnum], -5, 8
Column5=[endip], 12, 16
Column6=[endnum], -5, 8
Column7=[CPtype], 4, 4

