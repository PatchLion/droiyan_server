#if !defined(AFX_GUILDFORTRESSTAXSET_H__EEDD28F4_457F_4B8F_87CF_C3B8CB0E601A__INCLUDED_)
#define AFX_GUILDFORTRESSTAXSET_H__EEDD28F4_457F_4B8F_87CF_C3B8CB0E601A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuildFortressTaxSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuildFortressTaxSet recordset

class CGuildFortressTaxSet : public CRecordset
{
public:
	CGuildFortressTaxSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CGuildFortressTaxSet)

// Field/Param Data
	//{{AFX_FIELD(CGuildFortressTaxSet, CRecordset)
	int		m_sFortressID;
	int		m_sStoreID01;
	int		m_sStoreID02;
	int		m_sStoreID03;
	int		m_sStoreID04;
	int		m_sStoreID05;
	int		m_sStoreID06;
	int		m_sStoreID07;
	int		m_sStoreID08;
	int		m_sStoreID09;
	int		m_sStoreID10;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuildFortressTaxSet)
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

#endif // !defined(AFX_GUILDFORTRESSTAXSET_H__EEDD28F4_457F_4B8F_87CF_C3B8CB0E601A__INCLUDED_)
