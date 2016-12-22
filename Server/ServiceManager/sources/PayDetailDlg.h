#if !defined(AFX_PAYDETAILDLG_H__ED5E2F05_258F_11D3_B440_00A0248552B0__INCLUDED_)
#define AFX_PAYDETAILDLG_H__ED5E2F05_258F_11D3_B440_00A0248552B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PayDetailDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPayDetailDlg dialog


#include "ClientPaySet.h"


class CPayDetailDlg : public CDialog
{
// Construction
public:
	CPayDetailDlg( char* strName, long nMonth, int wID, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPayDetailDlg)
	enum { IDD = IDD_PAYDETAIL };
	CListCtrl	m_listDetail;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPayDetailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPayDetailDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	unsigned long GetTotalMoney();
	unsigned long GetTotalTime();
	void MonyForm( CString*);
	long m_nTotal;
	char* m_strName;
	void AddDetail( CClientPaySet*);
	long m_nMonth;
	int m_wID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAYDETAILDLG_H__ED5E2F05_258F_11D3_B440_00A0248552B0__INCLUDED_)
