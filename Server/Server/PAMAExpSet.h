#if !defined(AFX_PAMAEXPSET_H__98EF5494_C814_4F09_8149_49860C5214C9__INCLUDED_)
#define AFX_PAMAEXPSET_H__98EF5494_C814_4F09_8149_49860C5214C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PAMAExpSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPAMAExpSet recordset

class CPAMAExpSet : public CRecordset
{
public:
	CPAMAExpSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPAMAExpSet)

// Field/Param Data
	//{{AFX_FIELD(CPAMAExpSet, CRecordset)
	long	m_iPAMAExp;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPAMAExpSet)
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

#endif // !defined(AFX_PAMAEXPSET_H__98EF5494_C814_4F09_8149_49860C5214C9__INCLUDED_)
