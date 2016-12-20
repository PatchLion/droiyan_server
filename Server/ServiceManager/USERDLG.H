#if !defined(AFX_USERDLG_H__DDFF31F5_2A34_11D2_A550_00A0248552AD__INCLUDED_)
#define AFX_USERDLG_H__DDFF31F5_2A34_11D2_A550_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// UserDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog

class CUserDlg : public CDialog
{
// Construction
public:
	CString m_strSocNo;
	CUserDlg(CWnd* pParent = NULL);   // standard constructor

	BOOL	m_fSerialSearch;
// Dialog Data
	//{{AFX_DATA(CUserDlg)
	enum { IDD = IDD_USER };
	CString	m_strUserID;
	CString	m_strPasswd;
	CString	m_strSoc1;
	CString	m_strSoc2;
	CString	m_strName;
	CString	m_strEMail;
	UINT	m_wSerial;
	CString	m_strTel;
	CString	m_strAddr1;
	CString m_strAddr2;
	CTime	m_timeLog;
	CTime	m_timeReg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonSerial();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERDLG_H__DDFF31F5_2A34_11D2_A550_00A0248552AD__INCLUDED_)
