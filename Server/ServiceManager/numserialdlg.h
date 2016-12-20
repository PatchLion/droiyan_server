#if !defined(AFX_NUMSERIALDLG_H__B181B55E_5A6F_11D2_A57B_00A0248552AD__INCLUDED_)
#define AFX_NUMSERIALDLG_H__B181B55E_5A6F_11D2_A57B_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NumSerialDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNumSerialDlg dialog

class CNumSerialDlg : public CDialog
{
// Construction
public:
	CNumSerialDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNumSerialDlg)
	enum { IDD = IDD_NEWSERIAL };
	int		m_nNumSerial;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumSerialDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNumSerialDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NUMSERIALDLG_H__B181B55E_5A6F_11D2_A57B_00A0248552AD__INCLUDED_)
