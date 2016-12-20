#if !defined(AFX_GUILDHOUSERANKSET_H__B812F272_D365_41F9_BFE9_EC17FDA2B051__INCLUDED_)
#define AFX_GUILDHOUSERANKSET_H__B812F272_D365_41F9_BFE9_EC17FDA2B051__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuildHouseRankSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuildHouseRankSet recordset

class CGuildHouseRankSet : public CRecordset
{
public:
	CGuildHouseRankSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CGuildHouseRankSet)

// Field/Param Data
	//{{AFX_FIELD(CGuildHouseRankSet, CRecordset)
	BYTE	m_tSid;
	long	m_iGuild;
	BYTE	m_tNum;
	int		m_sValue;
	int		m_sGuildLevel;
	long	m_iLastTime;
	int		m_sZone;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuildHouseRankSet)
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

#endif // !defined(AFX_GUILDHOUSERANKSET_H__B812F272_D365_41F9_BFE9_EC17FDA2B051__INCLUDED_)
