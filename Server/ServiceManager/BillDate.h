#if !defined(AFX_BILLDATE_H__43F1FFD3_2E98_11D3_9DD1_00A0248552B0__INCLUDED_)
#define AFX_BILLDATE_H__43F1FFD3_2E98_11D3_9DD1_00A0248552B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BillDate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBillDate dialog

class CBillDate : public CDialog
{
// Construction
public:
	CBillDate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBillDate)
	enum { IDD = IDD_BILLDLG };
	CTime	m_timeBill;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBillDate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBillDate)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BILLDATE_H__43F1FFD3_2E98_11D3_9DD1_00A0248552B0__INCLUDED_)
