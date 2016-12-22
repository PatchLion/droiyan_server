#if !defined(AFX_SERVICECONFIGDLG_H__3731D1A8_2242_11D2_A549_00A0248552AD__INCLUDED_)
#define AFX_SERVICECONFIGDLG_H__3731D1A8_2242_11D2_A549_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ServiceConfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CServiceConfigDlg dialog

class CServiceConfigDlg : public CDialog
{
// Construction
public:
	CObList* m_pListServer;
	CServiceConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CServiceConfigDlg)
	enum { IDD = IDD_SERVICE };
	CComboBox	m_comboServer;
	CComboBox	m_comboAddr;
	CString	m_strAddr;
	CString	m_strServer;
	int		m_nCapacity;
	int		m_nID;
	CString	m_strModule;
	int		m_nPort;
	CString	m_strName;
	DWORD	m_dwTimeOuts;
	DWORD	m_dwTimer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServiceConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CServiceConfigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboGsServer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVICECONFIGDLG_H__3731D1A8_2242_11D2_A549_00A0248552AD__INCLUDED_)
