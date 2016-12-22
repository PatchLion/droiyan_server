#if !defined(AFX_DELFILEDLG_H__800F4D63_25C8_11D2_A54B_00A0248552AD__INCLUDED_)
#define AFX_DELFILEDLG_H__800F4D63_25C8_11D2_A54B_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DelFileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDelFileDlg dialog

class CDelFileDlg : public CDialog
{
// Construction
public:
	CDelFileDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDelFileDlg)
	enum { IDD = IDD_DELFILE };
	CListBox	m_listFile;
	CListBox	m_listDel;
	//}}AFX_DATA
	CObList		m_listCurFile;
	CObList		m_listDelFile;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDelFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDelFileDlg)
	afx_msg void OnButtonDelfile();
	afx_msg void OnButtonRestore();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELFILEDLG_H__800F4D63_25C8_11D2_A54B_00A0248552AD__INCLUDED_)
