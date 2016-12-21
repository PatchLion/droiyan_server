#if !defined(AFX_REMODELINGTABLESET_H__E0294D83_40DC_4A38_94A1_E9417F9ADF5C__INCLUDED_)
#define AFX_REMODELINGTABLESET_H__E0294D83_40DC_4A38_94A1_E9417F9ADF5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RemodelingTableSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRemodelingTableSet recordset

class CRemodelingTableSet : public CRecordset
{
public:
	CRemodelingTableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRemodelingTableSet)

// Field/Param Data
	//{{AFX_FIELD(CRemodelingTableSet, CRecordset)
	int		m_sRid;
	int		m_sSid;
	BYTE	m_tWearInfo;
	BYTE	m_tNeedClass;
	int		m_sPlan;
	BYTE	m_tRandom1;
	BYTE	m_tRandom2;
	BYTE	m_tReplace;
	CString	m_strText;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRemodelingTableSet)
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

#endif // !defined(AFX_REMODELINGTABLESET_H__E0294D83_40DC_4A38_94A1_E9417F9ADF5C__INCLUDED_)
