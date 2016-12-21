#if !defined(AFX_NPCPOSSET_H__E81DE0AC_1CBC_4C97_858F_8D16B460DA15__INCLUDED_)
#define AFX_NPCPOSSET_H__E81DE0AC_1CBC_4C97_858F_8D16B460DA15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NpcPosSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNpcPosSet recordset

class CNpcPosSet : public CRecordset
{
public:
	CNpcPosSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CNpcPosSet)

// Field/Param Data
	//{{AFX_FIELD(CNpcPosSet, CRecordset)
	int		m_sSid;
	CString m_strName;
	BYTE	m_byType;	
	int		m_sZone;
	int		m_sX;
	int		m_sY;
	int		m_sMinX;
	int		m_sMinY;
	int		m_sMaxX;
	int		m_sMaxY;
	int		m_sCount;
	long	m_sRegenTime;
	int		m_sEvent;
	int		m_sEZone;
	int		m_sGuild;
	int		m_sDimension;
	int		m_sHaveItem;
	int		m_sSay;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNpcPosSet)
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

#endif // !defined(AFX_NPCPOSSET_H__E81DE0AC_1CBC_4C97_858F_8D16B460DA15__INCLUDED_)
