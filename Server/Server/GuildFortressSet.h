#if !defined(AFX_GUILDFORTRESSSET_H__36ADCF11_6B24_447C_AD37_9BA6500D4305__INCLUDED_)
#define AFX_GUILDFORTRESSSET_H__36ADCF11_6B24_447C_AD37_9BA6500D4305__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuildFortressSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuildFortressSet recordset

class CGuildFortressSet : public CRecordset
{
public:
	CGuildFortressSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CGuildFortressSet)

// Field/Param Data
	//{{AFX_FIELD(CGuildFortressSet, CRecordset)
	int		m_sFortressID;
	long	m_iGuildSid;
	CString	m_strGuildName;
	int		m_sTaxRate;
	long	m_iGuildDN;
	CTime	m_GetTime;
	CTime	m_WarTime;
	CTime	m_WarPlan;
	BYTE	m_tWarType;
	CByteArray	m_HireGuardList;
	CByteArray	m_strAttackList;
	CByteArray	m_strRepairList;
	int		m_sPotalX;
	int		m_sPotalY;
	int		m_sZone;
	CTime	m_MopPartyTime;
	CTime	m_ReleaseTime;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuildFortressSet)
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

#endif // !defined(AFX_GUILDFORTRESSSET_H__36ADCF11_6B24_447C_AD37_9BA6500D4305__INCLUDED_)
