#if !defined(AFX_ITEMTABLESET_H__BA9C5D6C_79A7_464A_B4AE_4DA76B5F4A54__INCLUDED_)
#define AFX_ITEMTABLESET_H__BA9C5D6C_79A7_464A_B4AE_4DA76B5F4A54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ItemTableSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CItemTableSet recordset

class CItemTableSet : public CRecordset
{
public:
	CItemTableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CItemTableSet)

// Field/Param Data
	//{{AFX_FIELD(CItemTableSet, CRecordset)
	BYTE	m_byAX;
	BYTE	m_byAY;
	BYTE	m_byAZ;
	BYTE	m_byBullType;
	BYTE	m_byClass;
	BYTE	m_byErrorRate;
	BYTE	m_byMPP;
	BYTE	m_byRange;
	BYTE	m_byRdex;
	BYTE	m_byRLevel;
	BYTE	m_byRstr;
	BYTE	m_byRvol;
	BYTE	m_bySpecial;
	BYTE	m_bySubCure;
	BYTE	m_bySubDefense;
	BYTE	m_byWear;
	BYTE	m_byWeight;
	long	m_iDN;
	int		m_sAttackDelay;
	int		m_sBullNum;
	int		m_sCTime;
	int		m_sDefense;
	int		m_sDuration;
	int		m_sEvent;
	int		m_sPid;
	int		m_sRepairHP;
	int		m_sRepairPP;
	int		m_sRepairSP;
	int		m_sSid;
	CString	m_strName;
	CString	m_strText;
	int		m_sZone;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CItemTableSet)
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

#endif // !defined(AFX_ITEMTABLESET_H__BA9C5D6C_79A7_464A_B4AE_4DA76B5F4A54__INCLUDED_)
