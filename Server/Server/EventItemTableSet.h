#if !defined(AFX_EVENTITEMTABLESET_H__8D8DA49C_BCB4_476F_BE97_1D2115725197__INCLUDED_)
#define AFX_EVENTITEMTABLESET_H__8D8DA49C_BCB4_476F_BE97_1D2115725197__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EventItemTableSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEventItemTableSet recordset

class CEventItemTableSet : public CRecordset
{
public:
	CEventItemTableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEventItemTableSet)

// Field/Param Data
	//{{AFX_FIELD(CEventItemTableSet, CRecordset)
	int		m_sSid;
	CString	m_strSerialNum;
	BYTE	m_tEnd;
	BYTE	m_tGiveFlag;
	BYTE	m_tType;
	BYTE	m_tUsed;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventItemTableSet)
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

#endif // !defined(AFX_EVENTITEMTABLESET_H__8D8DA49C_BCB4_476F_BE97_1D2115725197__INCLUDED_)
