// ShootSunDroiyanDlg.h : header file
//

#if !defined(AFX_SHOOTSUNDROIYANDLG_H__F87AC73F_DDE0_4D5C_8E1A_212380CA8B03__INCLUDED_)
#define AFX_SHOOTSUNDROIYANDLG_H__F87AC73F_DDE0_4D5C_8E1A_212380CA8B03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CShootSunDroiyanDlg dialog
#include "HyperLink.h"

class CShootSunDroiyanDlg : public CDialog
{
// Construction
public:
	CShootSunDroiyanDlg(CWnd* pParent = NULL);	// standard constructor
	//CString GetExeDir();
	int GetWebPage(HINTERNET hSession,const CString& Url,CString& Contents);
	BOOL GetDroPathFromReg( CString szKey,CString &szGamePath );
	int File_in();
	CString m_szGamePath;
	HINTERNET	m_hSession;
// Dialog Data
	//{{AFX_DATA(CShootSunDroiyanDlg)
	enum { IDD = IDD_SHOOTSUNDROIYAN_DIALOG };
	CHyperLink	m_webShootSun;
	CComboBox	m_comboSelectSection;
	CEdit	 list;
	CEdit    user;
	CEdit    password;
	CEdit    m_ctrlCheck1;
	CButton  login;
	CButton  game;
	CButton  online;
	CButton  select;
	CString	str_user;
	CString str_password;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShootSunDroiyanDlg)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	LRESULT OnReadClose(WPARAM wParam,LPARAM lParam);
	void Recvinfo(char *buf, int len);
// Implementation
public:

	SOCKET ServerSocket;                 //SOCKET 
	SOCKADDR_IN sockStruct;          //SOCKET ½á¹¹

	BOOL IsTrue;

	CString IP;
	BYTE Code[8];
	
	Msg msg;


protected:
	HICON m_hIcon;
	DWORD m_pID;
	CString m_szHookDll;
	// Generated message map functions
	//{{AFX_MSG(CShootSunDroiyanDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnButtonLogin();
	afx_msg void OnlineShop();
	afx_msg void BaoCunZhangHao();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOOTSUNDROIYANDLG_H__F87AC73F_DDE0_4D5C_8E1A_212380CA8B03__INCLUDED_)
