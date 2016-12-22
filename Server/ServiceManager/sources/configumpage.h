#if !defined(AFX_CONFIGUMPAGE_H__3731D1B0_2242_11D2_A549_00A0248552AD__INCLUDED_)
#define AFX_CONFIGUMPAGE_H__3731D1B0_2242_11D2_A549_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ConfigUMPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigUMPage dialog

class CConfigUMPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CConfigUMPage)

// Construction
public:
	CServiceManagerDoc* m_pDoc;
	CConfigUMPage(CServiceManagerDoc* pDoc = NULL);
	~CConfigUMPage();

// Dialog Data
	//{{AFX_DATA(CConfigUMPage)
	enum { IDD = IDD_CONFIGUM };
	CComboBox	m_comboServer;
	CComboBox	m_comboAddr;
	CString	m_strAddr;
	CString	m_strServer;
	int		m_nCapacity;
	CString	m_strModule;
	int		m_nPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CConfigUMPage)
	public:
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CConfigUMPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboUmServer();
	afx_msg void OnSelchangeComboUmAddr();
	afx_msg void OnChangeEditUmCapacity();
	afx_msg void OnChangeEditUmModule();
	afx_msg void OnChangeEditUmPort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGUMPAGE_H__3731D1B0_2242_11D2_A549_00A0248552AD__INCLUDED_)
