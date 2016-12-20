#if !defined(AFX_BANKSERIALDLG_H__81CDF376_AA04_11D2_BB92_00A0248552AD__INCLUDED_)
#define AFX_BANKSERIALDLG_H__81CDF376_AA04_11D2_BB92_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BankSerialDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBankSerialDlg dialog

class CBankSerialDlg : public CDialog
{
// Construction
public:
	BOOL m_fReg;
	CBankSerialDlg(CWnd* pParent = NULL);   // standard constructor
	CStringArray	m_arrayCode;

// Dialog Data
	//{{AFX_DATA(CBankSerialDlg)
	enum { IDD = IDD_BANKSERIAL };
	CListBox	m_listSerial;
	int		m_nIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBankSerialDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBankSerialDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonReg();
	afx_msg void OnCopySerial();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BANKSERIALDLG_H__81CDF376_AA04_11D2_BB92_00A0248552AD__INCLUDED_)
