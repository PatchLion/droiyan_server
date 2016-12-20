#if !defined(AFX_SERIALSET_H__B181B57C_5A6F_11D2_A57B_00A0248552AD__INCLUDED_)
#define AFX_SERIALSET_H__B181B57C_5A6F_11D2_A57B_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SerialSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSerialSet recordset

class CSerialSet : public CRecordset
{
public:
	int GetType();
	int IsFirstUse ();
	CSerialSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSerialSet)

// Field/Param Data
	//{{AFX_FIELD(CSerialSet, CRecordset)
	int		m_wSerial;
	CString	m_strPasswd;
	CTime	m_timeStart;
	CTime	m_timeEnd;
	long	m_nMaxReg;
	long	m_nCurReg;
	long	m_nValidDay;
	int		m_addrStart;
	int		m_addrEnd;
	int		m_nType;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialSet)
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

#endif // !defined(AFX_SERIALSET_H__B181B57C_5A6F_11D2_A57B_00A0248552AD__INCLUDED_)
