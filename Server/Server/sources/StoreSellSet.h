#if !defined(AFX_STORESELLSET_H__4FF71DBE_AB09_4EB3_8129_7640CAD0FD3E__INCLUDED_)
#define AFX_STORESELLSET_H__4FF71DBE_AB09_4EB3_8129_7640CAD0FD3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StoreSellSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStoreSellSet recordset

class CStoreSellSet : public CRecordset
{
public:
	CStoreSellSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CStoreSellSet)

// Field/Param Data
	//{{AFX_FIELD(CStoreSellSet, CRecordset)
	int		m_sStoreID;
	int		m_sItemID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStoreSellSet)
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

#endif // !defined(AFX_STORESELLSET_H__4FF71DBE_AB09_4EB3_8129_7640CAD0FD3E__INCLUDED_)
