#if !defined(AFX_STOREREPAIRSET_H__57B9C0FA_5B9D_47C7_B550_64A95F4FDC5B__INCLUDED_)
#define AFX_STOREREPAIRSET_H__57B9C0FA_5B9D_47C7_B550_64A95F4FDC5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StoreRepairSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStoreRepairSet recordset

class CStoreRepairSet : public CRecordset
{
public:
	CStoreRepairSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CStoreRepairSet)

// Field/Param Data
	//{{AFX_FIELD(CStoreRepairSet, CRecordset)
	int		m_sStoreID;
	int		m_sItemID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStoreRepairSet)
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

#endif // !defined(AFX_STOREREPAIRSET_H__57B9C0FA_5B9D_47C7_B550_64A95F4FDC5B__INCLUDED_)
