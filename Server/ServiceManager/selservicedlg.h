#if !defined(AFX_SELSERVICEDLG_H__3731D1A9_2242_11D2_A549_00A0248552AD__INCLUDED_)
#define AFX_SELSERVICEDLG_H__3731D1A9_2242_11D2_A549_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SelServiceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelServiceDlg dialog

class CSelServiceDlg : public CDialog
{
// Construction
public:
	CObList* m_pListServer;
	CString m_strService;
	CSelServiceDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelServiceDlg)
	enum { IDD = IDD_SELSERVICE };
	CListBox	m_listService;
	CComboBox	m_comboServer;
	CString	m_strServer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelServiceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelServiceDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeComboServer();
	afx_msg void OnDblclkListService();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELSERVICEDLG_H__3731D1A9_2242_11D2_A549_00A0248552AD__INCLUDED_)
