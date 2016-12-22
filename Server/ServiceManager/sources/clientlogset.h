#if !defined(AFX_CLIENTLOGSET_H__0599A494_122E_11D3_AACF_00A0248552AD__INCLUDED_)
#define AFX_CLIENTLOGSET_H__0599A494_122E_11D3_AACF_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientLogSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClientLogSet recordset

class CClientLogSet : public CRecordset
{
public:
	CClientLogSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CClientLogSet)

// Field/Param Data
	//{{AFX_FIELD(CClientLogSet, CRecordset)
	long	m_nLogID;
	CString	m_strUserID;
	int		m_wSerial;
	CTime	m_timeLogin;
	long	m_nUseTime;
	CString	m_strIPAddr;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientLogSet)
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

#endif // !defined(AFX_CLIENTLOGSET_H__0599A494_122E_11D3_AACF_00A0248552AD__INCLUDED_)
