#if !defined(AFX_BANKSET_H__33BFD2F4_A71F_11D2_BB91_00A0248552AD__INCLUDED_)
#define AFX_BANKSET_H__33BFD2F4_A71F_11D2_BB91_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BankSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBankSet recordset

class CBankSet : public CRecordset
{
public:
	CBankSet( CDatabase* pDatabase = NULL, int wClientID = 0 );
	DECLARE_DYNAMIC(CBankSet)

// Field/Param Data
	//{{AFX_FIELD(CBankSet, CRecordset)
	long	m_nID;
	CTime	m_timeReg;
	CString	m_strName;
	CString	m_strBank;
	long	m_nMoney;
	CString	m_strOper;
	CString	m_strComment;
	BYTE	m_bProcess;
	BYTE	m_bType;
	CString	m_strSocNo;
	CString	m_strTelNo;
	int		m_wClientID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBankSet)
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
private:
	int m_wClientIDFilter;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BANKSET_H__33BFD2F4_A71F_11D2_BB91_00A0248552AD__INCLUDED_)
