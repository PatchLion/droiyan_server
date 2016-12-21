#if !defined(AFX_DBITEMINFO_H__2CB0FA90_27CB_4DFE_AD3E_AABF75E92D0E__INCLUDED_)
#define AFX_DBITEMINFO_H__2CB0FA90_27CB_4DFE_AD3E_AABF75E92D0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBItemInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBItemInfo recordset

class CDBItemInfo : public CRecordset
{
public:
	CDBItemInfo(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDBItemInfo)

// Field/Param Data
	//{{AFX_FIELD(CDBItemInfo, CRecordset)
	int		m_sNum;
	CString	m_strName;
	long	m_iCost;
	BYTE	m_tArm;
	BYTE	m_tUseLevel;
	BYTE	m_tUseType;
	int		m_sPicNum;
	int		m_sWg;
	int		m_sDur;
	int		m_sMaxAt;
	int		m_sAtDelay;
	BYTE	m_tDmgX;
	BYTE	m_tDmgY;
	BYTE	m_tDmgZ;
	BYTE	m_tDf;
	BYTE	m_tAt;
	BYTE	m_tCrit;
	BYTE	m_tRange;
	BYTE	m_tOut;
	BYTE	m_tBullNum;
	BYTE	m_tBullType;
	BYTE	m_tStErr;
	BYTE	m_tStDf;
	BYTE	m_tStCure;
	BYTE	m_tHP;
	BYTE	m_tPP;
	int		m_sSP;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBItemInfo)
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

#endif // !defined(AFX_DBITEMINFO_H__2CB0FA90_27CB_4DFE_AD3E_AABF75E92D0E__INCLUDED_)
