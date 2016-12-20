#if !defined(AFX_DRESSINGSET_H__AFC036DE_1CE0_48A0_9781_DD0CF2CD176E__INCLUDED_)
#define AFX_DRESSINGSET_H__AFC036DE_1CE0_48A0_9781_DD0CF2CD176E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DressingSet.h : header file
//


typedef struct _DRESSING_DATA
{
	int		sSid;
	int		sItemSid;
	int		sCountMin;
	int		sCountMax;
	int		sItem[10];
	int		sItemRatio[10];
} DRESSING_DATA;

typedef struct _DRESSING_RESULT
{
	int		sSid;
	int		sCount;
} DRESSING_RESULT;

typedef CTypedPtrArray <CPtrArray, DRESSING_RESULT*> DressingResultArray;

/////////////////////////////////////////////////////////////////////////////
// CDressingSet recordset

class CDressingSet : public CRecordset
{
public:
	CDressingSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDressingSet)

// Field/Param Data
	//{{AFX_FIELD(CDressingSet, CRecordset)
	int		m_sSid;
	int		m_sItemNum;
	int		m_sCountMin;
	int		m_sCountMax;
	int		m_sItem01;
	int		m_sItemRatio01;
	int		m_sItem02;
	int		m_sItemRatio02;
	int		m_sItem03;
	int		m_sItemRatio03;
	int		m_sItem04;
	int		m_sItemRatio04;
	int		m_sItem05;
	int		m_sItemRatio05;
	int		m_sItem06;
	int		m_sItemRatio06;
	int		m_sItem07;
	int		m_sItemRatio07;
	int		m_sItem08;
	int		m_sItemRatio08;
	int		m_sItem09;
	int		m_sItemRatio09;
	int		m_sItem10;
	int		m_sItemRatio10;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDressingSet)
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

#endif // !defined(AFX_DRESSINGSET_H__AFC036DE_1CE0_48A0_9781_DD0CF2CD176E__INCLUDED_)
