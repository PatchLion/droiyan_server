#if !defined(AFX_MECHANICSTORESET_H__F2FE7C19_A220_4FB5_86EE_056B7CF033CC__INCLUDED_)
#define AFX_MECHANICSTORESET_H__F2FE7C19_A220_4FB5_86EE_056B7CF033CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MechanicStoreSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMechanicStoreSet recordset

class CMechanicStoreSet : public CRecordset
{
public:
	CMechanicStoreSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CMechanicStoreSet)

// Field/Param Data
	//{{AFX_FIELD(CMechanicStoreSet, CRecordset)
	int		m_sStoreID;
	int		m_sSid;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMechanicStoreSet)
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

#endif // !defined(AFX_MECHANICSTORESET_H__F2FE7C19_A220_4FB5_86EE_056B7CF033CC__INCLUDED_)
