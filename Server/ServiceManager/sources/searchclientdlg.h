#if !defined(AFX_SEARCHCLIENTDLG_H__A7FF51F8_0344_11D3_AABF_00A0248552AD__INCLUDED_)
#define AFX_SEARCHCLIENTDLG_H__A7FF51F8_0344_11D3_AABF_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchClientDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchClientDlg dialog

class CSearchClientDlg : public CDialog
{
// Construction
public:
	CSearchClientDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSearchClientDlg)
	enum { IDD = IDD_FINDCLIENT };
	int		m_nLoc;
	CString	m_strName;
	CString	m_strHost;
	CString	m_strTelNo;
	CTime	m_time;
	CString	m_strSearchRegNo1;
	CString	m_strSearchRegNo2;
	CString	m_strSearchRegNo3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchClientDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHCLIENTDLG_H__A7FF51F8_0344_11D3_AABF_00A0248552AD__INCLUDED_)
