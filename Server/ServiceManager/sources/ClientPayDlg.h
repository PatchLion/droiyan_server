#if !defined(AFX_CLIENTPAYDLG_H__00E980E4_24C0_11D3_B440_00A0248552B0__INCLUDED_)
#define AFX_CLIENTPAYDLG_H__00E980E4_24C0_11D3_B440_00A0248552B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientPayDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClientPayDlg dialog

#include "ClientSet.h"


class CClientPayDlg : public CDialog
{
// Construction
public:
	CStringList m_listClient;
	long m_nFrom;
	long m_nTo;

	CClientPayDlg( CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CClientPayDlg)
	enum { IDD = IDD_CLIENT_PAY };
	CListCtrl	m_listctrl;
	CComboBox	m_toMonth;
	CComboBox	m_fromMonth;
	CString	m_strFromYear;
	CString	m_strToYear;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientPayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClientPayDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void AddClient( CClientSet* pSet);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTPAYDLG_H__00E980E4_24C0_11D3_B440_00A0248552B0__INCLUDED_)
