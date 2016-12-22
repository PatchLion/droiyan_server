#if !defined(AFX_REGDLG_H__8DF5B1B6_4237_11D2_A55C_00A0248552AD__INCLUDED_)
#define AFX_REGDLG_H__8DF5B1B6_4237_11D2_A55C_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RegDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRegDlg dialog

class CRegDlg : public CDialog
{
// Construction
public:
	virtual  ~CRegDlg();
	CRegDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRegDlg)
	enum { IDD = IDD_REGVALUE };
	CString	m_strName;
	int		m_nType;
	//}}AFX_DATA
	CString m_strValue;
	int		m_nValue;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRegDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGDLG_H__8DF5B1B6_4237_11D2_A55C_00A0248552AD__INCLUDED_)
