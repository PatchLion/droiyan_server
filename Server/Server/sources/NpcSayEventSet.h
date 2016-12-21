#if !defined(AFX_NPCSAYEVENTSET_H__78EE5A99_386D_4D6E_8BA7_6DDD28CC4F7F__INCLUDED_)
#define AFX_NPCSAYEVENTSET_H__78EE5A99_386D_4D6E_8BA7_6DDD28CC4F7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NpcSayEventSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNpcSayEventSet recordset

class CNpcSayEventSet : public CRecordset
{
public:
	CNpcSayEventSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CNpcSayEventSet)

// Field/Param Data
	//{{AFX_FIELD(CNpcSayEventSet, CRecordset)
	int		m_sSid;
	CString	m_strNpcSay;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNpcSayEventSet)
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

#endif // !defined(AFX_NPCSAYEVENTSET_H__78EE5A99_386D_4D6E_8BA7_6DDD28CC4F7F__INCLUDED_)
