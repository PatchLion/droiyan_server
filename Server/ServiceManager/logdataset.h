#if !defined(AFX_LOGDATASET_H__90251F73_1173_11D3_AACD_00A0248552AD__INCLUDED_)
#define AFX_LOGDATASET_H__90251F73_1173_11D3_AACD_00A0248552AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogDataSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogDataSet recordset

class CLogDataSet : public CRecordset
{
public:
	CLogDataSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CLogDataSet)

// Field/Param Data
	//{{AFX_FIELD(CLogDataSet, CRecordset)
	CTime	m_timeDate;
	long	m_nServiceID;
	long	m_nCount;
	long	m_nUseTime;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogDataSet)
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

#endif // !defined(AFX_LOGDATASET_H__90251F73_1173_11D3_AACD_00A0248552AD__INCLUDED_)
