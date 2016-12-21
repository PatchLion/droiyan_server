#if !defined(AFX_EBODYIDENTIFYTABLESET_H__8307210F_BB29_43DB_9B6B_CDDFA93D3B7B__INCLUDED_)
#define AFX_EBODYIDENTIFYTABLESET_H__8307210F_BB29_43DB_9B6B_CDDFA93D3B7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EBodyIdentifyTableSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEBodyIdentifyTableSet recordset

class CEBodyIdentifyTableSet : public CRecordset
{
public:
	CEBodyIdentifyTableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEBodyIdentifyTableSet)

// Field/Param Data
	//{{AFX_FIELD(CEBodyIdentifyTableSet, CRecordset)
	int		m_sSid;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEBodyIdentifyTableSet)
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

#endif // !defined(AFX_EBODYIDENTIFYTABLESET_H__8307210F_BB29_43DB_9B6B_CDDFA93D3B7B__INCLUDED_)
