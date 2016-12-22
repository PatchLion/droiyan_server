#if !defined(AFX_CONFIGGSPAGE_H__3731D1AE_2242_11D2_A549_00A0248552AD__INCLUDED_)
#define AFX_CONFIGGSPAGE_H__3731D1AE_2242_11D2_A549_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ConfigGSPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigGSPage dialog

class CConfigGSPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CConfigGSPage)

// Construction
public:
	int m_nDefaultIndex;
	CServiceManagerDoc* m_pDoc;
	CConfigGSPage(CServiceManagerDoc* pDoc = NULL);
	~CConfigGSPage();

// Dialog Data
	//{{AFX_DATA(CConfigGSPage)
	enum { IDD = IDD_CONFIGGS };
	CListBox	m_listGS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CConfigGSPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CConfigGSPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonGsAdd();
	afx_msg void OnButtonGsDel();
	afx_msg void OnButtonGsUpdate();
	afx_msg void OnButtonGsRefresh();
	afx_msg void OnButtonGsDefault();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGGSPAGE_H__3731D1AE_2242_11D2_A549_00A0248552AD__INCLUDED_)
