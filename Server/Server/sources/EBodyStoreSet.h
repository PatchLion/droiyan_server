#if !defined(AFX_EBODYSTORESET_H__CFF7C43F_2196_4BC8_9D46_D72EC4988885__INCLUDED_)
#define AFX_EBODYSTORESET_H__CFF7C43F_2196_4BC8_9D46_D72EC4988885__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EBodyStoreSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEBodyStoreSet recordset

class CEBodyStoreSet : public CRecordset
{
public:
	CEBodyStoreSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEBodyStoreSet)

// Field/Param Data
	//{{AFX_FIELD(CEBodyStoreSet, CRecordset)
	int		m_sStoreID;
	int		m_sEbodyID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEBodyStoreSet)
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

#endif // !defined(AFX_EBODYSTORESET_H__CFF7C43F_2196_4BC8_9D46_D72EC4988885__INCLUDED_)
