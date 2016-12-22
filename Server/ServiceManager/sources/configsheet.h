#if !defined(AFX_CONFIGSHEET_H__3731D1B2_2242_11D2_A549_00A0248552AD__INCLUDED_)
#define AFX_CONFIGSHEET_H__3731D1B2_2242_11D2_A549_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ConfigSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigSheet

class CConfigSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CConfigSheet)

// Construction
public:
	CConfigSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CConfigSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConfigSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CConfigSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGSHEET_H__3731D1B2_2242_11D2_A549_00A0248552AD__INCLUDED_)
