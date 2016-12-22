#if !defined(AFX_CLIENTSET_H__A7FF51F4_0344_11D3_AABF_00A0248552AD__INCLUDED_)
#define AFX_CLIENTSET_H__A7FF51F4_0344_11D3_AABF_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClientSet recordset

class CClientSet : public CRecordset
{
public:
	CClientSet( CDatabase* pDatabase = NULL, int Client_Filter = 0 );
	DECLARE_DYNAMIC(CClientSet)

// Field/Param Data
	//{{AFX_FIELD(CClientSet, CRecordset)
	long	m_nNumPC;
	CString	m_strAddress;
	CString	m_strEMail;
	CString	m_strHost;
	CString	m_strKind;
	CString	m_strName;
	CString	m_strRegNo;
	CString	m_strTelNo;
	CString	m_strType;
	CString	m_strUseLine;
	CString	m_strZipCode;
	CTime	m_timeReg;
	int		m_wID;
	BYTE	m_wLoc;
	CString m_strIPAddress;
	CString m_strEtc;	
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSet)
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
	int m_wClientFilter;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSET_H__A7FF51F4_0344_11D3_AABF_00A0248552AD__INCLUDED_)
