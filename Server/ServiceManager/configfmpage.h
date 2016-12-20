#if !defined(AFX_CONFIGFMPAGE_H__3731D1AD_2242_11D2_A549_00A0248552AD__INCLUDED_)
#define AFX_CONFIGFMPAGE_H__3731D1AD_2242_11D2_A549_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ConfigFMPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigFMPage dialog

class CConfigFMPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CConfigFMPage)

// Construction
public:
	CServiceManagerDoc* m_pDoc;
	CConfigFMPage(CServiceManagerDoc* pDoc = NULL);
	~CConfigFMPage();

// Dialog Data
	//{{AFX_DATA(CConfigFMPage)
	enum { IDD = IDD_CONFIGFM };
	CComboBox	m_comboServer;
	CComboBox	m_comboAddr;
	CString	m_strAddr;
	CString	m_strServer;
	CString	m_strModule;
	int		m_nPort;
	CString	m_strSrcPath;
	int		m_nCapacity;
	DWORD	m_dwBuffer;
	DWORD	m_dwHold;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CConfigFMPage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CConfigFMPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboFmServer();
	afx_msg void OnSelchangeComboFmAddr();
	afx_msg void OnChangeEditFmCapacity();
	afx_msg void OnChangeEditFmPath();
	afx_msg void OnChangeEditFmPort();
	afx_msg void OnChangeEditFmModule();
	afx_msg void OnChangeEditFmBuffer();
	afx_msg void OnChangeEditFmHold();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGFMPAGE_H__3731D1AD_2242_11D2_A549_00A0248552AD__INCLUDED_)
