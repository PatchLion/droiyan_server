#if !defined(AFX_NEWBANKDLG_H__33BFD2F6_A71F_11D2_BB91_00A0248552AD__INCLUDED_)
#define AFX_NEWBANKDLG_H__33BFD2F6_A71F_11D2_BB91_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewBankDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewBankDlg dialog


#include "DeleteClientDlg.h"


class CNewBankDlg : public CDialog
{
// Construction
public:
	CString m_strUserID;
	int m_nBankID;
	int m_nClientID;
	BOOL m_fGetSerial;
	CNewBankDlg( BOOL print_tax = FALSE, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewBankDlg)
	enum { IDD = IDD_BANK };
	CString	m_strBank;
	CString	m_strComment;
	int		m_nMoney;
	CString	m_strName;
	int		m_nNumSerial;
	CString	m_strOper;
	CString	m_strSoc1;
	CString	m_strSoc2;
	int		m_nProc;
	int		m_nType;
	CTime	m_timeBank;
	CString	m_strTelNo;
	CString	m_strClient;
	BOOL	m_checkTax;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewBankDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewBankDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSerial();
	afx_msg void OnChangeEditSoc1();
	afx_msg void OnChangeEditSoc2();
	afx_msg void OnButtonFindclient();
	afx_msg void OnButtonClient();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL IsDeleted;
	void DeleteClient( CDeleteClientDlg*);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWBANKDLG_H__33BFD2F6_A71F_11D2_BB91_00A0248552AD__INCLUDED_)
