#if !defined(AFX_DNTABLESET_H__7D63A61F_D908_44F1_AB43_A11A1F78AA99__INCLUDED_)
#define AFX_DNTABLESET_H__7D63A61F_D908_44F1_AB43_A11A1F78AA99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DNTableSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDNTableSet recordset

class CDNTableSet : public CRecordset
{
public:
	CDNTableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDNTableSet)

// Field/Param Data
	//{{AFX_FIELD(CDNTableSet, CRecordset)
	int		m_sIndex;
	int		m_sMinDn;
	int		m_sMaxDn;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDNTableSet)
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

#endif // !defined(AFX_DNTABLESET_H__7D63A61F_D908_44F1_AB43_A11A1F78AA99__INCLUDED_)
