#if !defined(AFX_EXCEPTIONZONESET_H__778D8E13_507A_478E_B555_F92626C29AAF__INCLUDED_)
#define AFX_EXCEPTIONZONESET_H__778D8E13_507A_478E_B555_F92626C29AAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExceptionZoneSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExceptionZoneSet recordset

class CExceptionZoneSet : public CRecordset
{
public:
	CExceptionZoneSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CExceptionZoneSet)

// Field/Param Data
	//{{AFX_FIELD(CExceptionZoneSet, CRecordset)
	int		m_sZone;
	BYTE	m_tFighterType;
	BYTE	m_tEventMopType;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExceptionZoneSet)
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

#endif // !defined(AFX_EXCEPTIONZONESET_H__778D8E13_507A_478E_B555_F92626C29AAF__INCLUDED_)
