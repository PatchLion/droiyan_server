#if !defined(AFX_FINDUSERDLG_H__DDFF31F6_2A34_11D2_A550_00A0248552AD__INCLUDED_)
#define AFX_FINDUSERDLG_H__DDFF31F6_2A34_11D2_A550_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FindUserDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindUserDlg dialog

class CFindUserDlg : public CDialog
{
// Construction
public:
	CString m_strCaption;
	CFindUserDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFindUserDlg)
	enum { IDD = IDD_FINDUSER };
	CString	m_strUserID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindUserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindUserDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDUSERDLG_H__DDFF31F6_2A34_11D2_A550_00A0248552AD__INCLUDED_)
