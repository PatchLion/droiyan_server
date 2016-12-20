#if !defined(AFX_TOWNPOTALTABLESET_H__E84C8D2B_70B7_46DF_BD19_08EF287292CF__INCLUDED_)
#define AFX_TOWNPOTALTABLESET_H__E84C8D2B_70B7_46DF_BD19_08EF287292CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TownPotalTableSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTownPotalTableSet recordset

class CTownPotalTableSet : public CRecordset
{
public:
	CTownPotalTableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTownPotalTableSet)

// Field/Param Data
	//{{AFX_FIELD(CTownPotalTableSet, CRecordset)
	int		m_sPotalZone;
	int		m_sPotalX1;
	int		m_sPotalY1;
	int		m_sPotalX2;
	int		m_sPotalY2;
	int		m_sPotalX3;
	int		m_sPotalY3;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTownPotalTableSet)
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

#endif // !defined(AFX_TOWNPOTALTABLESET_H__E84C8D2B_70B7_46DF_BD19_08EF287292CF__INCLUDED_)
