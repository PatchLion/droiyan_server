#if !defined(AFX_FINDSERIALDLG_H__DDC94945_430E_11D2_A55C_00A0248552AD__INCLUDED_)
#define AFX_FINDSERIALDLG_H__DDC94945_430E_11D2_A55C_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FindSerialDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindSerialDlg dialog

class CFindSerialDlg : public CDialog
{
// Construction
public:
	CFindSerialDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFindSerialDlg)
	enum { IDD = IDD_FINDSERIAL };
	short	m_wSerial;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindSerialDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindSerialDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDSERIALDLG_H__DDC94945_430E_11D2_A55C_00A0248552AD__INCLUDED_)
