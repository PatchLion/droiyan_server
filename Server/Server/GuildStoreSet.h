#if !defined(AFX_GUILDSTORESET_H__6A62B5B7_5302_4450_B79E_28D8C20E892F__INCLUDED_)
#define AFX_GUILDSTORESET_H__6A62B5B7_5302_4450_B79E_28D8C20E892F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuildStoreSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuildStoreSet recordset

class CGuildStoreSet : public CRecordset
{
public:
	CGuildStoreSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CGuildStoreSet)

// Field/Param Data
	//{{AFX_FIELD(CGuildStoreSet, CRecordset)
	int		m_sStoreID;
	long	m_iGuildSid;
	CString	m_strGuildName;
	CString	m_strMasterName;
	int		m_sTaxRate;
	long	m_iGuildDN;
	CTime	m_GetTime;
	CTime	m_WarTime;
	CTime	m_WarPlan;
	BYTE	m_tWarType;	
	CByteArray	m_strAttackList;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuildStoreSet)
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

#endif // !defined(AFX_GUILDSTORESET_H__6A62B5B7_5302_4450_B79E_28D8C20E892F__INCLUDED_)
