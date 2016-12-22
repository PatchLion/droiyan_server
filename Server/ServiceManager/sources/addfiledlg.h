#if !defined(AFX_ADDFILEDLG_H__EB7D49AB_2522_11D2_A54B_00A0248552AD__INCLUDED_)
#define AFX_ADDFILEDLG_H__EB7D49AB_2522_11D2_A54B_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AddFileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddFileDlg dialog

class CAddFileDlg : public CDialog
{
// Construction
public:
	CStringList m_listFileName;
	CAddFileDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddFileDlg)
	enum { IDD = IDD_ADDFILE };
	CListBox	m_listFile;
	CString	m_strSrcPath;
	short	m_wGameVer;
	BOOL	m_fComp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddFileDlg)
	afx_msg void OnButtonAddfile();
	afx_msg void OnButtonDelfile();
	virtual void OnOK();
	afx_msg void OnButtonAddall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDFILEDLG_H__EB7D49AB_2522_11D2_A54B_00A0248552AD__INCLUDED_)
