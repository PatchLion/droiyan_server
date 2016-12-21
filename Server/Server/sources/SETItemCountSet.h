#if !defined(AFX_SETITEMCOUNTSET_H__9E950E94_61D6_4829_9BC8_21DAF49C4513__INCLUDED_)
#define AFX_SETITEMCOUNTSET_H__9E950E94_61D6_4829_9BC8_21DAF49C4513__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SETItemCountSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSETItemCountSet recordset

class CSETItemCountSet : public CRecordset
{
public:
	CSETItemCountSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSETItemCountSet)

// Field/Param Data
	//{{AFX_FIELD(CSETItemCountSet, CRecordset)
	int		m_sSid;
	int		m_sItemIndex;
	long	m_iServerMax;
	long	m_iServerNow;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSETItemCountSet)
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

#endif // !defined(AFX_SETITEMCOUNTSET_H__9E950E94_61D6_4829_9BC8_21DAF49C4513__INCLUDED_)
