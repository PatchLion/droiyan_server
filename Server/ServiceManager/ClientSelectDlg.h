#if !defined(AFX_CLIENTSELECTDLG_H__EF2B29B1_3991_11D3_BB9F_00C02615866B__INCLUDED_)
#define AFX_CLIENTSELECTDLG_H__EF2B29B1_3991_11D3_BB9F_00C02615866B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSelectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClientSelectDlg dialog

class CClientSelectDlg : public CDialog
{
// Construction
public:
	CClientSelectDlg(CWnd* pParent = NULL);   // standard constructor

	void InitListCtrl();

	int m_vClientID;
	CString m_vClientName;
// Dialog Data
	//{{AFX_DATA(CClientSelectDlg)
	enum { IDD = IDD_CLIENT_SELECT };
	CEdit	m_wndClientName;
	CListCtrl	m_wndListClient;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClientSelectDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonClientsearch();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSELECTDLG_H__EF2B29B1_3991_11D3_BB9F_00C02615866B__INCLUDED_)
