#if !defined(AFX_EBODYUPGRADETABLESET_H__16C4F3A1_78AF_4C94_B869_938F38C3958E__INCLUDED_)
#define AFX_EBODYUPGRADETABLESET_H__16C4F3A1_78AF_4C94_B869_938F38C3958E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EBodyUpgradeTableSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEBodyUpgradeTableSet recordset

class CEBodyUpgradeTableSet : public CRecordset
{
public:
	CEBodyUpgradeTableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEBodyUpgradeTableSet)

// Field/Param Data
	//{{AFX_FIELD(CEBodyUpgradeTableSet, CRecordset)
	BYTE	m_tRandom1;
	BYTE	m_tRandom2;
	BYTE	m_tRandom3;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEBodyUpgradeTableSet)
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

#endif // !defined(AFX_EBODYUPGRADETABLESET_H__16C4F3A1_78AF_4C94_B869_938F38C3958E__INCLUDED_)
