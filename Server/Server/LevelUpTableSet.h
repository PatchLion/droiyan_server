#if !defined(AFX_LEVELUPTABLESET_H__74BC7F9F_9F08_4EBE_95CE_2348159A1249__INCLUDED_)
#define AFX_LEVELUPTABLESET_H__74BC7F9F_9F08_4EBE_95CE_2348159A1249__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LevelUpTableSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLevelUpTableSet recordset

class CLevelUpTableSet : public CRecordset
{
public:
	CLevelUpTableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CLevelUpTableSet)

// Field/Param Data
	//{{AFX_FIELD(CLevelUpTableSet, CRecordset)
	long long	m_iExp;
	int		m_sLevel;
	BYTE	m_tBasicUp;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLevelUpTableSet)
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

#endif // !defined(AFX_LEVELUPTABLESET_H__74BC7F9F_9F08_4EBE_95CE_2348159A1249__INCLUDED_)
