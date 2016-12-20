#if !defined(AFX_ADDEVENTITEMTABLESET_H__483BAAED_0F5B_45BF_B92D_A12E855CE01A__INCLUDED_)
#define AFX_ADDEVENTITEMTABLESET_H__483BAAED_0F5B_45BF_B92D_A12E855CE01A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddEventItemTableSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddEventItemTableSet recordset

class CAddEventItemTableSet : public CRecordset
{
public:
	CAddEventItemTableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAddEventItemTableSet)

// Field/Param Data
	//{{AFX_FIELD(CAddEventItemTableSet, CRecordset)
	int		m_sSid;
	BYTE	m_tType;
	BYTE	m_tGiveFlag;
	BYTE	m_tEnd;
	BYTE	m_tUsed;
	CString	m_strSerialNum;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddEventItemTableSet)
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

#endif // !defined(AFX_ADDEVENTITEMTABLESET_H__483BAAED_0F5B_45BF_B92D_A12E855CE01A__INCLUDED_)
