#if !defined(AFX_PSISTORESET_H__BDF729D6_6AE7_444D_86DA_A75DC5DF35CC__INCLUDED_)
#define AFX_PSISTORESET_H__BDF729D6_6AE7_444D_86DA_A75DC5DF35CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PsiStoreSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPsiStoreSet recordset

class CPsiStoreSet : public CRecordset
{
public:
	CPsiStoreSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPsiStoreSet)

// Field/Param Data
	//{{AFX_FIELD(CPsiStoreSet, CRecordset)
	int		m_sStoreID;
	int		m_sPsiID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPsiStoreSet)
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

#endif // !defined(AFX_PSISTORESET_H__BDF729D6_6AE7_444D_86DA_A75DC5DF35CC__INCLUDED_)
