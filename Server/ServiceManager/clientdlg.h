#if !defined(AFX_CLIENTDLG_H__A7FF51F3_0344_11D3_AABF_00A0248552AD__INCLUDED_)
#define AFX_CLIENTDLG_H__A7FF51F3_0344_11D3_AABF_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

class CClientDlg : public CDialog
{
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CClientDlg)
	enum { IDD = IDD_CLIENT };
	CString	m_strLine;
	int		m_nLoc;
	CTime	m_timeReg;
	CString	m_strAddress;
	CString	m_strEMail;
	CString	m_strHost;
	CString	m_strKind;
	CString	m_strName;
	int		m_nNumPC;
	CString	m_strRegNo1;
	CString	m_strRegNo2;
	CString	m_strRegNo3;
	CString	m_strTelNo;
	CString	m_strType;
	CString	m_strZip1;
	CString	m_strZip2;
	int		m_nID;
	CString	m_strEtc;
	CString	m_strIPAddress;	
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClientDlg)
	afx_msg void OnChangeEditClientRegno1();
	afx_msg void OnChangeEditClientRegno2();
	afx_msg void OnChangeEditClientRegno3();
	afx_msg void OnChangeEditClientZip1();
	afx_msg void OnChangeEditClientZip2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDLG_H__A7FF51F3_0344_11D3_AABF_00A0248552AD__INCLUDED_)
