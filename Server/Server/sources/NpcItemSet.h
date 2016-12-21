#if !defined(AFX_NPCITEMSET_H__CF367426_D68D_4381_9220_884D259AEB01__INCLUDED_)
#define AFX_NPCITEMSET_H__CF367426_D68D_4381_9220_884D259AEB01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NpcItemSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNpcItemSet recordset

class CNpcItemSet : public CRecordset
{
public:
	CNpcItemSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CNpcItemSet)

// Field/Param Data
	//{{AFX_FIELD(CNpcItemSet, CRecordset)
	int		m_sIndex;
	int		m_sItem01;
	int		m_sPersent01;
	int		m_sItem02;
	int		m_sPersent02;
	int		m_sItem03;
	int		m_sPersent03;
	int		m_sItem04;
	int		m_sPersent04;
	int		m_sItem05;
	int		m_sPersent05;
	int		m_sItem06;
	int		m_sPersent06;
	int		m_sItem07;
	int		m_sPersent07;
	int		m_sItem08;
	int		m_sPersent08;
	int		m_sItem09;
	int		m_sPersent09;
	int		m_sItem10;
	int		m_sPersent10;
	int		m_sItem11;
	int		m_sPersent11;
	int		m_sItem12;
	int		m_sPersent12;
	int		m_sItem13;
	int		m_sPersent13;
	int		m_sItem14;
	int		m_sPersent14;
	int		m_sItem15;
	int		m_sPersent15;
	int		m_sItem16;
	int		m_sPersent16;
	int		m_sItem17;
	int		m_sPersent17;
	int		m_sItem18;
	int		m_sPersent18;
	int		m_sItem19;
	int		m_sPersent19;
	int		m_sItem20;
	int		m_sPersent20;	
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNpcItemSet)
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

#endif // !defined(AFX_NPCITEMSET_H__CF367426_D68D_4381_9220_884D259AEB01__INCLUDED_)
