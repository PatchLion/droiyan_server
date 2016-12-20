#if !defined(AFX_CLIENTLISTDLG_H__A7FF51F9_0344_11D3_AABF_00A0248552AD__INCLUDED_)
#define AFX_CLIENTLISTDLG_H__A7FF51F9_0344_11D3_AABF_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientListDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClientListDlg dialog

class CClientListDlg : public CDialog
{
// Construction
public:
	int m_nClientID;
	CClientListDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CClientListDlg)
	enum { IDD = IDD_CLIENTLIST };
	CListBox	m_listClient;
	CString	m_strClient;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClientListDlg)
	afx_msg void OnButtonClient();
	afx_msg void OnButtonSearch();
	afx_msg void OnButtonNewclient();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTLISTDLG_H__A7FF51F9_0344_11D3_AABF_00A0248552AD__INCLUDED_)
