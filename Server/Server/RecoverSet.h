#if !defined(AFX_RECOVERSET_H__CAAB4B7E_1AC6_43A8_B4C1_6B308EF036E1__INCLUDED_)
#define AFX_RECOVERSET_H__CAAB4B7E_1AC6_43A8_B4C1_6B308EF036E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecoverSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecoverSet recordset

class CRecoverSet : public CRecordset
{
public:
	CRecoverSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRecoverSet)

// Field/Param Data
	//{{AFX_FIELD(CRecoverSet, CRecordset)
	int		m_sSid;
	BYTE	m_byHPDivide;
	BYTE	m_bySPDivide;
	BYTE	m_byPPDivide;
	BYTE	m_byTown;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecoverSet)
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

#endif // !defined(AFX_RECOVERSET_H__CAAB4B7E_1AC6_43A8_B4C1_6B308EF036E1__INCLUDED_)
