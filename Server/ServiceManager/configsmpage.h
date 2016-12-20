#if !defined(AFX_CONFIGSMPAGE_H__3731D1AF_2242_11D2_A549_00A0248552AD__INCLUDED_)
#define AFX_CONFIGSMPAGE_H__3731D1AF_2242_11D2_A549_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ConfigSMPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigSMPage dialog

class CConfigSMPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CConfigSMPage)

// Construction
public:
	CServiceManagerDoc* m_pDoc;
	CConfigSMPage(CServiceManagerDoc* pDoc = NULL);
	~CConfigSMPage();

// Dialog Data
	//{{AFX_DATA(CConfigSMPage)
	enum { IDD = IDD_CONFIGSM };
	CListBox	m_listSM;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CConfigSMPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CConfigSMPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSmAdd();
	afx_msg void OnButtonSmDel();
	afx_msg void OnButtonSmUpdate();
	afx_msg void OnButtonSmRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGSMPAGE_H__3731D1AF_2242_11D2_A549_00A0248552AD__INCLUDED_)
