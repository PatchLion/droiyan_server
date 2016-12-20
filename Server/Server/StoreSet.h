#if !defined(AFX_STORESET_H__113E86B1_D869_4A48_8F4F_CB608DC848C5__INCLUDED_)
#define AFX_STORESET_H__113E86B1_D869_4A48_8F4F_CB608DC848C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StoreSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStoreSet recordset

class CStoreSet : public CRecordset
{
public:
	CStoreSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CStoreSet)

// Field/Param Data
	//{{AFX_FIELD(CStoreSet, CRecordset)
	int		m_sStoreID;
	int		m_sItemID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStoreSet)
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

#endif // !defined(AFX_STORESET_H__113E86B1_D869_4A48_8F4F_CB608DC848C5__INCLUDED_)
