#if !defined(AFX_BANKSERIALSET_H__33BFD2F5_A71F_11D2_BB91_00A0248552AD__INCLUDED_)
#define AFX_BANKSERIALSET_H__33BFD2F5_A71F_11D2_BB91_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BankSerialSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBankSerialSet recordset

class CBankSerialSet : public CRecordset
{
public:
	CBankSerialSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CBankSerialSet)

// Field/Param Data
	//{{AFX_FIELD(CBankSerialSet, CRecordset)
	int		m_nBankID;
	CString	m_strSerialCode;
	int		m_wSerial;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBankSerialSet)
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

#endif // !defined(AFX_BANKSERIALSET_H__33BFD2F5_A71F_11D2_BB91_00A0248552AD__INCLUDED_)
