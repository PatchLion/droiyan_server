#if !defined(AFX_ACCESSORIUPTABLESET_H__3BB4728A_AB75_42EA_AA88_B32E1DCE8215__INCLUDED_)
#define AFX_ACCESSORIUPTABLESET_H__3BB4728A_AB75_42EA_AA88_B32E1DCE8215__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AccessoriUpTableSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAccessoriUpTableSet recordset

class CAccessoriUpTableSet : public CRecordset
{
public:
	CAccessoriUpTableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAccessoriUpTableSet)

// Field/Param Data
	//{{AFX_FIELD(CAccessoriUpTableSet, CRecordset)
	int		m_sAid;
	int		m_sSid;
	CString	m_strText;
	BYTE	m_tType;
	BYTE	m_tGroup;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccessoriUpTableSet)
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

#endif // !defined(AFX_ACCESSORIUPTABLESET_H__3BB4728A_AB75_42EA_AA88_B32E1DCE8215__INCLUDED_)
