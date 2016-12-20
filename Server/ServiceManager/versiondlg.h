#if !defined(AFX_VERSIONDLG_H__FDCC3433_25E5_11D2_A54C_00A0248552AD__INCLUDED_)
#define AFX_VERSIONDLG_H__FDCC3433_25E5_11D2_A54C_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VersionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVersionDlg dialog

class CVersionDlg : public CDialog
{
// Construction
public:
	CVersionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVersionDlg)
	enum { IDD = IDD_SETVERSION };
	short	m_wGameVer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVersionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVersionDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VERSIONDLG_H__FDCC3433_25E5_11D2_A54C_00A0248552AD__INCLUDED_)
