#if !defined(AFX_ZONEINFOSET_H__822C9236_BEFA_4622_A8C1_E75C46CC4881__INCLUDED_)
#define AFX_ZONEINFOSET_H__822C9236_BEFA_4622_A8C1_E75C46CC4881__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZoneInfoSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZoneInfoSet recordset

class CZoneInfoSet : public CRecordset
{
public:
	CZoneInfoSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CZoneInfoSet)

// Field/Param Data
	//{{AFX_FIELD(CZoneInfoSet, CRecordset)
	int		m_sSid;
	int		m_sZone;
	BYTE	m_tPkMode;
	BYTE	m_tWeather;
	int		m_sPotalZone;
	int		m_sPotalX;
	int		m_sPotalY;
	int		m_sPotalX1;
	int		m_sPotalY1;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoneInfoSet)
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

#endif // !defined(AFX_ZONEINFOSET_H__822C9236_BEFA_4622_A8C1_E75C46CC4881__INCLUDED_)
