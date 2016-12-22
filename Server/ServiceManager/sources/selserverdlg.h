#if !defined(AFX_SELSERVERDLG_H__3731D1AB_2242_11D2_A549_00A0248552AD__INCLUDED_)
#define AFX_SELSERVERDLG_H__3731D1AB_2242_11D2_A549_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SelServerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelServerDlg dialog

class CSelServerDlg : public CDialog
{
// Construction
public:
	int m_nCheck;
	CObList* m_pListServer;
	CSelServerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelServerDlg)
	enum { IDD = IDD_SELSERVER };
	CListBox	m_listServer;
	CString	m_strServer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListServer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELSERVERDLG_H__3731D1AB_2242_11D2_A549_00A0248552AD__INCLUDED_)
