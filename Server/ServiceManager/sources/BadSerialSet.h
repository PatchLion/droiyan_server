#if !defined(AFX_BADSERIALSET_H__1872D4B8_290C_11D3_9D84_00A0248552B0__INCLUDED_)
#define AFX_BADSERIALSET_H__1872D4B8_290C_11D3_9D84_00A0248552B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BadSerialSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBadSerialSet recordset

class CBadSerialSet : public CRecordset
{
public:
	CBadSerialSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CBadSerialSet)

// Field/Param Data
	//{{AFX_FIELD(CBadSerialSet, CRecordset)
	int		m_wSerial;
	CTime	m_dateStop;
	CString	m_strOper;
	CString	m_strReasion;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBadSerialSet)
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

#endif // !defined(AFX_BADSERIALSET_H__1872D4B8_290C_11D3_9D84_00A0248552B0__INCLUDED_)
