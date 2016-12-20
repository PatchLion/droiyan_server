// ServiceManager.h : main header file for the SERVICEMANAGER application
//

#if !defined(AFX_SERVICEMANAGER_H__E17147F8_20EA_11D2_A546_00A0248552AD__INCLUDED_)
#define AFX_SERVICEMANAGER_H__E17147F8_20EA_11D2_A546_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "Msg.h"
#include "..\include\SCProtocol.h"

/////////////////////////////////////////////////////////////////////////////
// CServiceManagerApp:
// See ServiceManager.cpp for the implementation of this class
//

#define SERIAL_PRIVATE_MONTH	0
#define SERIAL_GAMEROOM_MONTH	1
#define SERIAL_PRIVATE_TIME		2
#define SERIAL_GAMEROOM_TIME	3
#define SERIAL_NOTUSE			4

#define BANK_TYPE_PRIVATE		0
#define BANK_TYPE_GAMEROOM		1
#define BANK_TYPE_PAYLATER		2
#define BANK_TYPE_PAY			3
#define BANK_TYPE_ETC			4

#define BANK_PROC_IN			0
#define BANK_PROC_CONF			1
#define BANK_PROC_STOP			2
#define BANK_PROC_ETC			3

#define CLIENT_SERIAL_USE		0
#define CLIENT_SERIAL_STOP		1
#define CLIENT_SERIAL_DEL		2

class CServiceManagerApp : public CWinApp
{
public:
	CServiceManagerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServiceManagerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CServiceManagerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

extern CDatabase g_db;

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVICEMANAGER_H__E17147F8_20EA_11D2_A546_00A0248552AD__INCLUDED_)
