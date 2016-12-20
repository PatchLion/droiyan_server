#if !defined(AFX_CURRENTUSERSET_H__25239C33_18CC_11D3_AAD3_00A0248552AD__INCLUDED_)
#define AFX_CURRENTUSERSET_H__25239C33_18CC_11D3_AAD3_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CurrentUserSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCurrentUserSet recordset

class CCurrentUserSet : public CRecordset
{
public:
	CCurrentUserSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCurrentUserSet)

// Field/Param Data
	//{{AFX_FIELD(CCurrentUserSet, CRecordset)
	BYTE	m_bUseSecond;
	long	m_nAccountID;
	BYTE	m_nAcctType;
	long	m_nCPAccountID;
	BYTE	m_nCPAcctType;
	long	m_nCPID;
	BYTE	m_nDisplay;
	int		m_nServiceID;
	CTime	m_nValidDay;
	long	m_nValidTime;
	CString	m_strBizNo;
	CString	m_strClientID;
	CString	m_strIPAddr;
	CString	m_strServerIPAddr;
	CTime	m_timeCPLogin;
	CTime	m_timeLogin;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurrentUserSet)
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

#endif // !defined(AFX_CURRENTUSERSET_H__25239C33_18CC_11D3_AAD3_00A0248552AD__INCLUDED_)
