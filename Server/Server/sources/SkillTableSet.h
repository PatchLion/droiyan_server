#if !defined(AFX_SKILLTABLESET_H__E326EFAD_3982_4F28_B3F7_8B655D646A8F__INCLUDED_)
#define AFX_SKILLTABLESET_H__E326EFAD_3982_4F28_B3F7_8B655D646A8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkillTableSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSkillTableSet recordset

class CSkillTableSet : public CRecordset
{
public:
	CSkillTableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSkillTableSet)

// Field/Param Data
	//{{AFX_FIELD(CSkillTableSet, CRecordset)
	int		m_sPid;
	int		m_sSid;
	BYTE	m_tClass;
	BYTE	m_tInc;
	BYTE	m_tLevel;
	BYTE	m_tRepair;
	BYTE	m_tSuccess;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkillTableSet)
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

#endif // !defined(AFX_SKILLTABLESET_H__E326EFAD_3982_4F28_B3F7_8B655D646A8F__INCLUDED_)
