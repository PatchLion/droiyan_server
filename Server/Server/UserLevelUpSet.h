#if !defined(AFX_USERLEVELUPSET_H__41141955_6B7D_4298_85AB_770FD0EC3D6C__INCLUDED_)
#define AFX_USERLEVELUPSET_H__41141955_6B7D_4298_85AB_770FD0EC3D6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserLevelUpSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserLevelUpSet recordset

class CUserLevelUpSet : public CRecordset
{
public:
	CUserLevelUpSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CUserLevelUpSet)

// Field/Param Data
	//{{AFX_FIELD(CUserLevelUpSet, CRecordset)
	int		m_sLevel;
	int		m_sHP;
	int		m_sPP;
	int		m_sDamage;
	int		m_sDefense;
	int		m_sWeight;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserLevelUpSet)
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

#endif // !defined(AFX_USERLEVELUPSET_H__41141955_6B7D_4298_85AB_770FD0EC3D6C__INCLUDED_)
