#if !defined(AFX_PRINTBILLDLG_H__C4A31D09_2611_11D3_B440_00A0248552B0__INCLUDED_)
#define AFX_PRINTBILLDLG_H__C4A31D09_2611_11D3_B440_00A0248552B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrintBillDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrintBillDlg dialog

class CPrintBillDlg : public CDialog
{
// Construction
public:
	CPrintBillDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrintBillDlg)
	enum { IDD = IDD_PRINTBILL_DLG };
	CTime	m_timeDead;
	CTime	m_timeFrom;
	CTime	m_timeTo;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintBillDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrintBillDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTBILLDLG_H__C4A31D09_2611_11D3_B440_00A0248552B0__INCLUDED_)
