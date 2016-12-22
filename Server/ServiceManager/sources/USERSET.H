#if !defined(AFX_USERSET_H__B181B57D_5A6F_11D2_A57B_00A0248552AD__INCLUDED_)
#define AFX_USERSET_H__B181B57D_5A6F_11D2_A57B_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserSet recordset

class CUserSet : public CRecordset
{
public:
	CUserSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CUserSet)

// Field/Param Data
	//{{AFX_FIELD(CUserSet, CRecordset)
	int		m_bEmail;
	int		m_bAdmin;
	CString	m_strAddr1;
	CString	m_strAddr2;
	CString	m_strEMail;
	CString	m_strHandNo;
	CString	m_strName;
	CString	m_strPasswd;
	CString	m_strPhoneNo;
	CString	m_strPostalCode;
	CString	m_strQuery1;
	CString	m_strQuery2;
	CString	m_strReply1;
	CString	m_strReply2;
	CString	m_strSocNo;
	CString	m_strUserID;
	CTime	m_timeLog;
	CTime	m_timeReg;
	long	m_wSerial;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserSet)
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

#endif // !defined(AFX_USERSET_H__B181B57D_5A6F_11D2_A57B_00A0248552AD__INCLUDED_)
