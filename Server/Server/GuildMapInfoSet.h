#if !defined(AFX_GUILDMAPINFOSET_H__530390E1_833C_4095_8F1D_FF65439742E9__INCLUDED_)
#define AFX_GUILDMAPINFOSET_H__530390E1_833C_4095_8F1D_FF65439742E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuildMapInfoSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuildMapInfoSet recordset

class CGuildMapInfoSet : public CRecordset
{
public:
	CGuildMapInfoSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CGuildMapInfoSet)

// Field/Param Data
	//{{AFX_FIELD(CGuildMapInfoSet, CRecordset)
	int		m_sMapIndex;
	BYTE	m_tPkMode;
	int		m_sReleatedStore;
	int		m_sGuildZone;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuildMapInfoSet)
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

#endif // !defined(AFX_GUILDMAPINFOSET_H__530390E1_833C_4095_8F1D_FF65439742E9__INCLUDED_)
