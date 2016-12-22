#if !defined(AFX_FINDBANKDLG_H__10A24993_04E4_11D3_AAC1_00A0248552AD__INCLUDED_)
#define AFX_FINDBANKDLG_H__10A24993_04E4_11D3_AAC1_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindBankDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindBankDlg dialog

class CFindBankDlg : public CDialog
{
// Construction
public:
	int m_nClientID;
	CFindBankDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFindBankDlg)
	enum { IDD = IDD_FINDBANK };
	CString	m_strBank;
	int		m_nProc;
	int		m_nType;
	CTime	m_timeEnd;
	CTime	m_timeStart;
	CString	m_strClient;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindBankDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindBankDlg)
	afx_msg void OnButtonFindclient();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDBANKDLG_H__10A24993_04E4_11D3_AAC1_00A0248552AD__INCLUDED_)
