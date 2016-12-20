#if !defined(AFX_PSITABLESET_H__E896DE57_FDB1_487D_84F8_759EEEA07F27__INCLUDED_)
#define AFX_PSITABLESET_H__E896DE57_FDB1_487D_84F8_759EEEA07F27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PsiTableSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPsiTableSet recordset

class CPsiTableSet : public CRecordset
{
public:
	CPsiTableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPsiTableSet)

// Field/Param Data
	//{{AFX_FIELD(CPsiTableSet, CRecordset)
	long	m_iNeedDN;
	long	m_iNeedXP;
	int		m_sBasic;
	int		m_sDelayTime;
	int		m_sHoldTime;
	int		m_sLevelUp;
	int		m_sPid;
	int		m_sSid;
	CString	m_strName;
	CString	m_strText;
	BYTE	m_tClass;
	BYTE	m_tNeedLevel;
	BYTE	m_tNeedPP;
	BYTE	m_tRange;
	BYTE	m_tRegi;
	BYTE	m_tTarget;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPsiTableSet)
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

#endif // !defined(AFX_PSITABLESET_H__E896DE57_FDB1_487D_84F8_759EEEA07F27__INCLUDED_)
