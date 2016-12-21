#if !defined(AFX_PATCHVER_H__CC7074AB_6AC7_4B72_B284_71A1E08ABDFD__INCLUDED_)
#define AFX_PATCHVER_H__CC7074AB_6AC7_4B72_B284_71A1E08ABDFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PatchVer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPatchVer recordset

class CPatchVer : public CRecordset
{
public:
	CPatchVer(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPatchVer)

// Field/Param Data
	//{{AFX_FIELD(CPatchVer, CRecordset)
	int		m_sVersion;
	CString	m_strFileName;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPatchVer)
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

#endif // !defined(AFX_PATCHVER_H__CC7074AB_6AC7_4B72_B284_71A1E08ABDFD__INCLUDED_)
