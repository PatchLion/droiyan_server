#if !defined(AFX_USERCOUNTSET_H__25239C34_18CC_11D3_AAD3_00A0248552AD__INCLUDED_)
#define AFX_USERCOUNTSET_H__25239C34_18CC_11D3_AAD3_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserCountSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserCountSet recordset

class CUserCountSet : public CRecordset
{
public:
	CUserCountSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CUserCountSet)

// Field/Param Data
	//{{AFX_FIELD(CUserCountSet, CRecordset)
	long	m_nServiceID;
	long	m_nNumUser;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserCountSet)
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

#endif // !defined(AFX_USERCOUNTSET_H__25239C34_18CC_11D3_AAD3_00A0248552AD__INCLUDED_)
