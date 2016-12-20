#if !defined(AFX_NOTICESETDIALOG_H__C7F8AD81_F57C_11D3_BC63_00C02615866B__INCLUDED_)
#define AFX_NOTICESETDIALOG_H__C7F8AD81_F57C_11D3_BC63_00C02615866B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NoticeSetDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNoticeSetDialog dialog

class CNoticeSetDialog : public CDialog
{
// Construction
public:
	CNoticeSetDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNoticeSetDialog)
	enum { IDD = IDD_NOTICE_SET };
	BOOL	m_vNoticeValue;
	CString	m_strNoticeMessage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNoticeSetDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNoticeSetDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnNoticeValue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTICESETDIALOG_H__C7F8AD81_F57C_11D3_BC63_00C02615866B__INCLUDED_)
