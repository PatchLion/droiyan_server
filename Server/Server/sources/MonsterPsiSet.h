#if !defined(AFX_MONSTERPSISET_H__23D3195E_3837_4D75_9EF5_5EBC965B2315__INCLUDED_)
#define AFX_MONSTERPSISET_H__23D3195E_3837_4D75_9EF5_5EBC965B2315__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MonsterPsiSet.h : header file
//

class CMonsterPsi
{
public:
	int		m_sSid;
	int		m_sPid;
	int		m_sCasting;
	int		m_sMinDmg;
	int		m_sMaxDmg;
	int		m_byRange;
};

/////////////////////////////////////////////////////////////////////////////
// CMonsterPsiSet recordset

class CMonsterPsiSet : public CRecordset
{
public:
	CMonsterPsiSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CMonsterPsiSet)

// Field/Param Data
	//{{AFX_FIELD(CMonsterPsiSet, CRecordset)
	BYTE	m_byRange;
	int		m_sCasting;
	int		m_sMaxDmg;
	int		m_sMinDmg;
	int		m_sPid;
	int		m_sSid;
	CString	m_strName;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonsterPsiSet)
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

#endif // !defined(AFX_MONSTERPSISET_H__23D3195E_3837_4D75_9EF5_5EBC965B2315__INCLUDED_)
