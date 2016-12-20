#if !defined(AFX_CONVSERIALDLG_H__DDC94944_430E_11D2_A55C_00A0248552AD__INCLUDED_)
#define AFX_CONVSERIALDLG_H__DDC94944_430E_11D2_A55C_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ConvSerialDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConvSerialDlg dialog

class CConvSerialDlg : public CDialog
{
// Construction
public:
	CConvSerialDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConvSerialDlg)
	enum { IDD = IDD_CONVSERIAL };
	CString	m_strSerial1;
	CString	m_strSerial2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConvSerialDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConvSerialDlg)
	afx_msg void OnChangeEditSerial1();
	afx_msg void OnChangeEditSerial2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONVSERIALDLG_H__DDC94944_430E_11D2_A55C_00A0248552AD__INCLUDED_)
