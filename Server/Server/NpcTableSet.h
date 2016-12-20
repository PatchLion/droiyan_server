#if !defined(AFX_NPCTABLESET_H__3A9EE3C9_2CF7_410A_B39C_6D8A20114937__INCLUDED_)
#define AFX_NPCTABLESET_H__3A9EE3C9_2CF7_410A_B39C_6D8A20114937__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NpcTableSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNpcTableSet recordset

class CNpcTableSet : public CRecordset
{
public:
	CNpcTableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CNpcTableSet)

// Field/Param Data
	//{{AFX_FIELD(CNpcTableSet, CRecordset)
	int		m_sSid;
	int		m_sPid;
	CString	m_strName;
	int		m_sSTR;
	int		m_sDEX;
	int		m_sVOL;
	int		m_sWIS;
	int		m_sMaxHP;
	int		m_sMaxPP;
	BYTE	m_byClass;
	BYTE	m_byClassLevel;
	long	m_sExp;
	int 	m_byAX;
	int 	m_byAY;
	int 	m_byAZ;
	BYTE	m_byRange;
	int		m_sAI;
	int		m_sAttackDelay;
	BYTE	m_byVitalC;
	BYTE	m_byWildShot;
	BYTE	m_byExcitedRate;
	BYTE	m_byIronSkin;
	BYTE	m_byReAttack;
	BYTE	m_bySubAttack;
	BYTE	m_byState;
	BYTE	m_byPsi;
	BYTE	m_byPsiLevel;
	BYTE	m_bySearchRange;
	int		m_sSpeed;
	int		m_sInclination;
	BYTE	m_byColor;
	int		m_sStandTime;
	BYTE	m_tNpcType;
	int		m_sFamilyType;
	BYTE	m_tItemPer;
	BYTE	m_tDnPer;
	int		m_byDefense;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNpcTableSet)
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

#endif // !defined(AFX_NPCTABLESET_H__3A9EE3C9_2CF7_410A_B39C_6D8A20114937__INCLUDED_)
