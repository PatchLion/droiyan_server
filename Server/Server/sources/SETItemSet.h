#if !defined(AFX_SETITEMSET_H__25296B6D_1498_4A39_B792_40DE4F9E1BD8__INCLUDED_)
#define AFX_SETITEMSET_H__25296B6D_1498_4A39_B792_40DE4F9E1BD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SETItemSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSETItemSet recordset

class CSETItemSet : public CRecordset
{
public:
	CSETItemSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSETItemSet)

// Field/Param Data
	//{{AFX_FIELD(CSETItemSet, CRecordset)
	int		m_sSetIndex;
	CString	m_strMainName;
	BYTE	m_bySetCount;
	BYTE	m_bySetAddOption1;
	BYTE	m_bySetAddOption2;
	BYTE	m_bySetAddOption3;
	BYTE	m_bySetAddOption4;
	BYTE	m_bySetAddOption5;
	BYTE	m_bySetAddOption6;
	BYTE	m_bySetAddOption7;
	BYTE	m_bySetAddOption8;
	BYTE	m_bySetAddOption9;
	int		m_sSet2;
	int		m_sSet3;
	int		m_sSet4;
	int		m_sSet5;
	int		m_sSet6;
	int		m_sSet7;
	int		m_sSet8;
	int		m_sSet9;
	int		m_sSet10;
	int		m_sSet11;
	int		m_sSet12;
	int		m_sSet13;
	int		m_sSet14;
	int		m_sSet15;
	int		m_sItem01;
	int		m_sItem02;
	int		m_sItem03;
	int		m_sItem04;
	int		m_sItem05;
	int		m_sItem06;
	int		m_sItem07;
	int		m_sItem08;
	int		m_sItem09;
	int		m_sItem10;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSETItemSet)
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

#endif // !defined(AFX_SETITEMSET_H__25296B6D_1498_4A39_B792_40DE4F9E1BD8__INCLUDED_)
