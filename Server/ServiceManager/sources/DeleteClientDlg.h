#if !defined(AFX_DELETECLIENTDLG_H__1872D4B7_290C_11D3_9D84_00A0248552B0__INCLUDED_)
#define AFX_DELETECLIENTDLG_H__1872D4B7_290C_11D3_9D84_00A0248552B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DeleteClientDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDeleteClientDlg dialog

class CDeleteClientDlg : public CDialog
{
// Construction
public:
	CDeleteClientDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDeleteClientDlg)
	enum { IDD = IDD_DELETE_CLIENT };
	CString	m_strReasion;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeleteClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDeleteClientDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELETECLIENTDLG_H__1872D4B7_290C_11D3_9D84_00A0248552B0__INCLUDED_)
