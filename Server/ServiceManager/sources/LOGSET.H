#if !defined(AFX_LOGSET_H__B181B57E_5A6F_11D2_A57B_00A0248552AD__INCLUDED_)
#define AFX_LOGSET_H__B181B57E_5A6F_11D2_A57B_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogSet recordset

class CLogSet : public CRecordset
{
public:
	CLogSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CLogSet)

// Field/Param Data
	//{{AFX_FIELD(CLogSet, CRecordset)
	long	m_nLogID;
	long	m_nServiceID;
	CString	m_strUserID;
	int		m_wSerial;
	CTime	m_timeLogin;
	long	m_nUseTime;
	BYTE	m_bReason;
	CString	m_strIPAddr;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogSet)
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

#endif // !defined(AFX_LOGSET_H__B181B57E_5A6F_11D2_A57B_00A0248552AD__INCLUDED_)
