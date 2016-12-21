#if !defined(AFX_VALITEMTABLESET_H__AAE0F8FF_D432_4933_BB1B_4BAD697EC40C__INCLUDED_)
#define AFX_VALITEMTABLESET_H__AAE0F8FF_D432_4933_BB1B_4BAD697EC40C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ValItemTableSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CValItemTableSet recordset

class CValItemTableSet : public CRecordset
{
public:
	CValItemTableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CValItemTableSet)

// Field/Param Data
	//{{AFX_FIELD(CValItemTableSet, CRecordset)
	int		m_sSid;
	int		m_sValItem01;
	BYTE	m_tPersentVal01;
	int		m_sValItem02;
	BYTE	m_tPersentVal02;
	int		m_sValItem03;
	BYTE	m_tPersentVal03;
	int		m_sValItem04;
	BYTE	m_tPersentVal04;
	int		m_sValItem05;
	BYTE	m_tPersentVal05;
	int		m_sValItem06;
	BYTE	m_tPersentVal06;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CValItemTableSet)
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

#endif // !defined(AFX_VALITEMTABLESET_H__AAE0F8FF_D432_4933_BB1B_4BAD697EC40C__INCLUDED_)
