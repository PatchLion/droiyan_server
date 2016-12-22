#if !defined(AFX_CLIENTPAYSET_H__0599A493_122E_11D3_AACF_00A0248552AD__INCLUDED_)
#define AFX_CLIENTPAYSET_H__0599A493_122E_11D3_AACF_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientPaySet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClientPaySet recordset

class CClientPaySet : public CRecordset
{
public:
	CClientPaySet(CDatabase* pDatabase = NULL, long Month_Filter = 0, int Client_Filter = 0);
	DECLARE_DYNAMIC(CClientPaySet)

// Field/Param Data
	//{{AFX_FIELD(CClientPaySet, CRecordset)
	int		m_wClientID;
	long	m_nMonth;
	long	m_nUseTime;
	int		m_BANK_SERIAL_wSerial;
	long	m_nBankID;
	CString	m_strSerialCode;
	int		m_CLIENT_PAY_wSerial;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientPaySet)
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
	int m_nClient_Filter;
	int m_nMonth_Filter;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTPAYSET_H__0599A493_122E_11D3_AACF_00A0248552AD__INCLUDED_)
