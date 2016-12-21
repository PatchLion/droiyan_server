#if !defined(AFX_EBODYTABLESET_H__51F9AD8E_C5C4_4F93_8DFC_BB43DF13CEBD__INCLUDED_)
#define AFX_EBODYTABLESET_H__51F9AD8E_C5C4_4F93_8DFC_BB43DF13CEBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EBodyTableSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEBodyTableSet recordset

class CEBodyTableSet : public CRecordset
{
public:
	CEBodyTableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEBodyTableSet)

// Field/Param Data
	//{{AFX_FIELD(CEBodyTableSet, CRecordset)
	int		m_sChangeValue;
	int		m_sRandom;
	int		m_sSubType;
	CString	m_strText;
	BYTE	m_tLevel;
	BYTE	m_tNeedClass;
	BYTE	m_tSid;
	BYTE	m_tUpgrade;
	BYTE	m_tWearInfo;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEBodyTableSet)
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

#endif // !defined(AFX_EBODYTABLESET_H__51F9AD8E_C5C4_4F93_8DFC_BB43DF13CEBD__INCLUDED_)
