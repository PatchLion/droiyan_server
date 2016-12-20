#if !defined(AFX_RECOVERRATESET_H__15CB7AEE_34F3_4D2C_88C8_FE46B4655AF0__INCLUDED_)
#define AFX_RECOVERRATESET_H__15CB7AEE_34F3_4D2C_88C8_FE46B4655AF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecoverRateSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecoverRateSet recordset

class CRecoverRateSet : public CRecordset
{
public:
	CRecoverRateSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRecoverRateSet)

// Field/Param Data
	//{{AFX_FIELD(CRecoverRateSet, CRecordset)
	int		m_sSid;
	int		m_sHpSpeedupTime;
	BYTE	m_byHpSpeedupLevel;
	int		m_sSpSpeedupTime;
	BYTE	m_bySpSpeedupLevel;
	int		m_sPpSpeedupTime;
	BYTE	m_byPpSpeedupLevel;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecoverRateSet)
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

#endif // !defined(AFX_RECOVERRATESET_H__15CB7AEE_34F3_4D2C_88C8_FE46B4655AF0__INCLUDED_)
