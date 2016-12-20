#if !defined(AFX_INITITEMTABLESET_H__E4693E2A_9E7F_43AA_8AC7_A284FD80D530__INCLUDED_)
#define AFX_INITITEMTABLESET_H__E4693E2A_9E7F_43AA_8AC7_A284FD80D530__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InitItemTableSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInitItemTableSet recordset
typedef struct _INITITEMTABLE
{
	BYTE tClass;
	int iSid;
	int iSubSid;

} InitItemTable;


class CInitItemTableSet : public CRecordset
{
public:
	CInitItemTableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CInitItemTableSet)

// Field/Param Data
	//{{AFX_FIELD(CInitItemTableSet, CRecordset)
	BYTE	m_tTypeClass;
	int		m_sSid;
	int		m_sSubSid;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInitItemTableSet)
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

#endif // !defined(AFX_INITITEMTABLESET_H__E4693E2A_9E7F_43AA_8AC7_A284FD80D530__INCLUDED_)
