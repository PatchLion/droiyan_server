#if !defined(AFX_BOXEVENTTABLESET_H__6DFF410D_BA5D_4127_8108_206FA401AA45__INCLUDED_)
#define AFX_BOXEVENTTABLESET_H__6DFF410D_BA5D_4127_8108_206FA401AA45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BoxEventTableSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBoxEventTableSet recordset

class CBoxEventTableSet : public CRecordset
{
public:
	CBoxEventTableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CBoxEventTableSet)

// Field/Param Data
	//{{AFX_FIELD(CBoxEventTableSet, CRecordset)
	int		m_sSid;
	BYTE	m_tType;
	int		m_sIid;
	int		m_sCount;
	CString	m_strText;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoxEventTableSet)
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

#endif // !defined(AFX_BOXEVENTTABLESET_H__6DFF410D_BA5D_4127_8108_206FA401AA45__INCLUDED_)
