#if !defined(AFX_NEWSERIALDLG_H__7851ABB4_2931_11D2_A550_00A0248552AD__INCLUDED_)
#define AFX_NEWSERIALDLG_H__7851ABB4_2931_11D2_A550_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NewSerialDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewSerialDlg dialog

class CNewSerialDlg : public CDialog
{
// Construction
public:
	BOOL m_fGetBank;
	int m_fUpdate;

	CNewSerialDlg(int fUpdate = 0, CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CNewSerialDlg)
	enum { IDD = IDD_SERIAL };
	CSpinButtonCtrl	m_spinValidTime;
	CSpinButtonCtrl	m_spinValidDay;
	CSpinButtonCtrl	m_spinMaxRegUser;
	CSpinButtonCtrl	m_spinCustom1Day;
	CSpinButtonCtrl	m_spinCurRegUser;
	int		m_wSerial;
	CString	m_strPasswd;
	int		m_nMaxReg;
	int		m_nType;
	CTime	m_timeEnd;
	CTime	m_timeStart;
	int		m_nCurReg;
	CString	m_strIPNumber;
	int		m_nValidDay;
	int		m_nValidTime;
	int		m_nIPStart;
	int		m_nIPEnd;
	int		m_nCustom1ValidDay;
	int		m_nMonth;
	BOOL	m_nCheckClose;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewSerialDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewSerialDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioTypeMember();
	afx_msg void OnRadioTypeGame();
	afx_msg void OnButtonBank();
	afx_msg void OnRadioMonth();
	afx_msg void OnRadioTime();
	virtual void OnOK();
	afx_msg void OnRadioTypecustom1();
	afx_msg void OnRadioExtension();
	afx_msg void OnCheckClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWSERIALDLG_H__7851ABB4_2931_11D2_A550_00A0248552AD__INCLUDED_)
