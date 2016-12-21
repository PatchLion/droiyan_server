#if !defined(AFX_NPCCHATSET_H__AA8F1A6B_12F8_4B3C_8498_445802B69237__INCLUDED_)
#define AFX_NPCCHATSET_H__AA8F1A6B_12F8_4B3C_8498_445802B69237__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NpcChatSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNpcChatSet recordset

class CNpcChatSet : public CRecordset
{
public:
	CNpcChatSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CNpcChatSet)

// Field/Param Data
	//{{AFX_FIELD(CNpcChatSet, CRecordset)
	int		m_sCid;
	int		m_sSize;
	CString	m_strTalk;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNpcChatSet)
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

#endif // !defined(AFX_NPCCHATSET_H__AA8F1A6B_12F8_4B3C_8498_445802B69237__INCLUDED_)
