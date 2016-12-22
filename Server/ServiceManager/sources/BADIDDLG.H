#if !defined(AFX_BADIDDLG_H__90251F75_1173_11D3_AACD_00A0248552AD__INCLUDED_)
#define AFX_BADIDDLG_H__90251F75_1173_11D3_AACD_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BadIDDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBadIDDlg dialog

class CBadIDDlg : public CDialog
{
// Construction
public:
	CBadIDDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBadIDDlg)
	enum { IDD = IDD_BADID };
	CString	m_strComment;
	int		m_nDueDay;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBadIDDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBadIDDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BADIDDLG_H__90251F75_1173_11D3_AACD_00A0248552AD__INCLUDED_)
