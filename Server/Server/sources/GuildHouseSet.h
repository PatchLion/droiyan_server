#if !defined(AFX_GUILDHOUSESET_H__E8DCCB52_DA19_42ED_A7B9_13D50E5DA710__INCLUDED_)
#define AFX_GUILDHOUSESET_H__E8DCCB52_DA19_42ED_A7B9_13D50E5DA710__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuildHouseSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuildHouseSet recordset

class CGuildHouseSet : public CRecordset
{
public:
	CGuildHouseSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CGuildHouseSet)

// Field/Param Data
	//{{AFX_FIELD(CGuildHouseSet, CRecordset)
	BYTE	m_tSid;
	long	m_iGuild;
	int		m_sZone;
	int		m_sPotalX;
	int		m_sPotalY;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuildHouseSet)
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

#endif // !defined(AFX_GUILDHOUSESET_H__E8DCCB52_DA19_42ED_A7B9_13D50E5DA710__INCLUDED_)
