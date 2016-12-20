// KeyHooks.h : main header file for the KEYHOOKS DLL
//

#if !defined(AFX_KEYHOOKS_H__CF096D1E_E4DA_4FCA_A6FD_053144B4EDEC__INCLUDED_)
#define AFX_KEYHOOKS_H__CF096D1E_E4DA_4FCA_A6FD_053144B4EDEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

//#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CKeyHooksApp
// See KeyHooks.cpp for the implementation of this class
//

class CKeyHooksApp : public CWinApp
{
public:
	CKeyHooksApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyHooksApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CKeyHooksApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifdef KEYHOOK_EXPORTS
#define KEYHOOK_API __declspec(dllexport)
#else
#define KEYHOOK_API __declspec(dllimport)
#endif

BOOL _declspec(dllexport)__stdcall InstallHotKey( DWORD dwThreadId );
BOOL _declspec(dllexport)__stdcall UninstallHotKey( );
BOOL InstallUI(HWND hParent);

int PoupDialog();
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYHOOKS_H__CF096D1E_E4DA_4FCA_A6FD_053144B4EDEC__INCLUDED_)
