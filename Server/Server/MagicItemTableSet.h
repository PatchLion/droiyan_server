#if !defined(AFX_MAGICITEMTABLESET_H__7CD2B542_C72A_4881_846C_5CA3C5850439__INCLUDED_)
#define AFX_MAGICITEMTABLESET_H__7CD2B542_C72A_4881_846C_5CA3C5850439__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MagicItemTableSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMagicItemTableSet recordset

class CMagicItemTableSet : public CRecordset
{
public:
	CMagicItemTableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CMagicItemTableSet)

// Field/Param Data
	//{{AFX_FIELD(CMagicItemTableSet, CRecordset)
	int		m_sChangeValue;
	int		m_sSid;
	int		m_sSubType;
	CString	m_strText;
	BYTE	m_tLevel;
	BYTE	m_tNeedClass;
	BYTE	m_tUpgrade;
	BYTE	m_tUse;
	BYTE	m_tWearInfo;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMagicItemTableSet)
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

#endif // !defined(AFX_MAGICITEMTABLESET_H__7CD2B542_C72A_4881_846C_5CA3C5850439__INCLUDED_)
