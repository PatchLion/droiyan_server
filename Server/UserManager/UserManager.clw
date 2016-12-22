; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUserManagerApp
LastTemplate=CRecordset
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "usermanager.h"
LastPage=0

ClassCount=1
Class1=CUserManagerApp

ResourceCount=0

[CLS:CUserManagerApp]
Type=0
BaseClass=CWinApp
HeaderFile=UserManager.h
ImplementationFile=UserManager.cpp
LastObject=CUserManagerApp

[DB:CSerialSet]
DB=1
DBType=ODBC
ColumnCount=7
Column1=[wSerial], 5, 2
Column2=[nValidDay], 4, 4
Column3=[strPasswd], 12, 11
Column4=[timeStart], 11, 16
Column5=[timeEnd], 11, 16
Column6=[nMaxReg], 4, 4
Column7=[nCurReg], 4, 4

[DB:CUserSet]
DB=1
DBType=ODBC
ColumnCount=10
Column1=[strUserID], 12, 13
Column2=[strPasswd], 12, 11
Column3=[wSerial], 5, 2
Column4=[strName], 12, 11
Column5=[strSocNo], 12, 15
Column6=[strAddr], 12, 61
Column7=[strTel], 12, 21
Column8=[strEMail], 12, 31
Column9=[timeReg], 11, 16
Column10=[timeLog], 11, 16

[DB:CGameSet]
DB=1
DBType=ODBC
ColumnCount=14
Column1=[Code], 12, 11
Column2=[Name], 12, 21
Column3=[Company], 12, 21
Column4=[TelNo], 12, 31
Column5=[Price], 4, 4
Column6=[PriceIP], 4, 4
Column7=[MaxRegUser], 4, 4
Column8=[Version], 4, 4
Column9=[GSAddr], 12, 16
Column10=[GSPort], 4, 4
Column11=[FMAddr], 12, 16
Column12=[FMPort], 4, 4
Column13=[UMAddr], 12, 16
Column14=[UMPort], 4, 4

[DB:CLogSet]
DB=1
DBType=ODBC
ColumnCount=8
Column1=[nLogID], 4, 4
Column2=[nServiceID], 4, 4
Column3=[strUserID], 12, 13
Column4=[wSerial], 5, 2
Column5=[timeLogin], 11, 16
Column6=[nUseTime], 4, 4
Column7=[bReason], -6, 1
Column8=[strIPAddr], 12, 16

[DB:CUserRegSet]
DB=1
DBType=ODBC
ColumnCount=4
Column1=[UserID], 12, 13
Column2=[SerialID], 4, 4
Column3=[RegDate], 11, 16
Column4=[Game], 12, 11

[DB:CServiceSet]
DB=1
DBType=ODBC
ColumnCount=7
Column1=[ServiceID], 4, 4
Column2=[ServiceName], 12, 11
Column3=[Game], 12, 11
Column4=[Pay], -6, 1
Column5=[Addr], 12, 16
Column6=[Port], 4, 4
Column7=[Filter], 12, 16

