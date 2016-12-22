#if !defined(AFX_SEARCHLOGDLG_H__E6554036_2834_11D2_A54E_00A0248552AD__INCLUDED_)
#define AFX_SEARCHLOGDLG_H__E6554036_2834_11D2_A54E_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SearchLogDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchLogDlg dialog

class CSession;

class CSearchLogDlg : public CDialog
{
// Construction
public:
	CSearchLogDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSearchLogDlg)
	enum { IDD = IDD_LOG };
	CString	m_strUserID;
	CString	m_strSerial1;
	CString	m_strSerial2;
	CTime	m_timeStart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchLogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchLogDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHLOGDLG_H__E6554036_2834_11D2_A54E_00A0248552AD__INCLUDED_)
