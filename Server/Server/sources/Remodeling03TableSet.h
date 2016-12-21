#if !defined(AFX_REMODELING03TABLESET_H__BEFDFDD9_BA08_49F6_BD37_822792D80B45__INCLUDED_)
#define AFX_REMODELING03TABLESET_H__BEFDFDD9_BA08_49F6_BD37_822792D80B45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Remodeling03TableSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRemodeling03TableSet recordset

class CRemodeling03TableSet : public CRecordset
{
public:
	CRemodeling03TableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRemodeling03TableSet)

// Field/Param Data
	//{{AFX_FIELD(CRemodeling03TableSet, CRecordset)
	int		m_sPlan;
	int		m_sRid;
	int		m_sSid;
	CString	m_strText;
	BYTE	m_tNeedClass;
	BYTE	m_tRandom1;
	BYTE	m_tRandom2;
	BYTE	m_tReplace;
	BYTE	m_tWearInfo;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRemodeling03TableSet)
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

#endif // !defined(AFX_REMODELING03TABLESET_H__BEFDFDD9_BA08_49F6_BD37_822792D80B45__INCLUDED_)
