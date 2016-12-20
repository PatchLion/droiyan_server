#if !defined(AFX_SERVERCONFIGDLG_H__3731D1A7_2242_11D2_A549_00A0248552AD__INCLUDED_)
#define AFX_SERVERCONFIGDLG_H__3731D1A7_2242_11D2_A549_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ServerConfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CServerConfigDlg dialog

class CServerConfigDlg : public CDialog
{
// Construction
public:
	CStringList* m_pListAddr;
	CServerConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CServerConfigDlg)
	enum { IDD = IDD_SERVER };
	CListBox	m_listAddr;
	CString	m_strAddr;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CServerConfigDlg)
	afx_msg void OnButtonSetdefault();
	afx_msg void OnButtonAddipaddr();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERCONFIGDLG_H__3731D1A7_2242_11D2_A549_00A0248552AD__INCLUDED_)
