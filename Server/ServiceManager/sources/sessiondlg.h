#if !defined(AFX_SESSIONDLG_H__3731D1B1_2242_11D2_A549_00A0248552AD__INCLUDED_)
#define AFX_SESSIONDLG_H__3731D1B1_2242_11D2_A549_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SessionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSessionDlg dialog

class CSessionDlg : public CDialog
{
// Construction
public:
	CObList* m_pListServer;
	CSessionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSessionDlg)
	enum { IDD = IDD_SESSION };
	CComboBox	m_comboServer;
	CComboBox	m_comboAddr;
	CString	m_strAddr;
	CString	m_strServer;
	int		m_nCapacity;
	int		m_nID;
	CString	m_strModule;
	CString	m_strName;
	int		m_nPort;
	DWORD	m_dwTimeOuts;
	int		m_nPay;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSessionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSessionDlg)
	afx_msg void OnSelchangeComboSmServer();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SESSIONDLG_H__3731D1B1_2242_11D2_A549_00A0248552AD__INCLUDED_)
