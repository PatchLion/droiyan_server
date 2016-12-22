#if !defined(AFX_PRINTADDRESSDLG_H__1872D4B9_290C_11D3_9D84_00A0248552B0__INCLUDED_)
#define AFX_PRINTADDRESSDLG_H__1872D4B9_290C_11D3_9D84_00A0248552B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrintAddressDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrintAddressDlg dialog

class CPrintAddressDlg : public CDialog
{
// Construction
public:
	CPrintAddressDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrintAddressDlg)
	enum { IDD = IDD_PRINT_ADDR };
	int		m_nMonth;
	CString	m_strYear;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintAddressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrintAddressDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTADDRESSDLG_H__1872D4B9_290C_11D3_9D84_00A0248552B0__INCLUDED_)
