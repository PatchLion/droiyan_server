#if !defined(AFX_CLIENTSERIALSET_H__B83504A1_0430_11D3_9E59_444553540000__INCLUDED_)
#define AFX_CLIENTSERIALSET_H__B83504A1_0430_11D3_9E59_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSerialSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClientSerialSet recordset

class CClientSerialSet : public CRecordset
{
public:
	CClientSerialSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CClientSerialSet)

// Field/Param Data
	//{{AFX_FIELD(CClientSerialSet, CRecordset)
	int		m_wSerial;
	int		m_wClientID;
	long	m_nLastLogID;
	BYTE	m_bProcess;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSerialSet)
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

#endif // !defined(AFX_CLIENTSERIALSET_H__B83504A1_0430_11D3_9E59_444553540000__INCLUDED_)
