#if !defined(AFX_VERSET_H__B181B580_5A6F_11D2_A57B_00A0248552AD__INCLUDED_)
#define AFX_VERSET_H__B181B580_5A6F_11D2_A57B_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VerSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVerSet recordset

class CVerSet : public CRecordset
{
public:
	CVerSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CVerSet)

// Field/Param Data
	//{{AFX_FIELD(CVerSet, CRecordset)
	CString	m_strFileName;
	CString	m_strCompName;
	int		m_wVersion;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVerSet)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VERSET_H__B181B580_5A6F_11D2_A57B_00A0248552AD__INCLUDED_)
