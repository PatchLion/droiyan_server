#if !defined(AFX_BADIDSET_H__90251F74_1173_11D3_AACD_00A0248552AD__INCLUDED_)
#define AFX_BADIDSET_H__90251F74_1173_11D3_AACD_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BadIDSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBadIDSet recordset

class CBadIDSet : public CRecordset
{
public:
	CBadIDSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CBadIDSet)

// Field/Param Data
	//{{AFX_FIELD(CBadIDSet, CRecordset)
	CString	m_strComment;
	CString	m_strOper;
	CString	m_strPasswd;
	CString	m_strUserID;
	CTime	m_timeReg;
	CTime	m_timeReturn;
	BYTE	m_tType;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBadIDSet)
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

#endif // !defined(AFX_BADIDSET_H__90251F74_1173_11D3_AACD_00A0248552AD__INCLUDED_)
