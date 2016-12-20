// ShootSunDroiyan.h : main header file for the SHOOTSUNDROIYAN application
//

#if !defined(AFX_SHOOTSUNDROIYAN_H__68111F97_A8D8_4092_8937_046B317C1EED__INCLUDED_)
#define AFX_SHOOTSUNDROIYAN_H__68111F97_A8D8_4092_8937_046B317C1EED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CShootSunDroiyanApp:
// See ShootSunDroiyan.cpp for the implementation of this class
//

class CShootSunDroiyanApp : public CWinApp
{
public:
	CShootSunDroiyanApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShootSunDroiyanApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CShootSunDroiyanApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOOTSUNDROIYAN_H__68111F97_A8D8_4092_8937_046B317C1EED__INCLUDED_)
