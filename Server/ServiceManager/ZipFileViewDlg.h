#if !defined(AFX_ZIPFILEVIEWDLG_H__542B107C_9AA7_4449_8841_645B04DCB2C5__INCLUDED_)
#define AFX_ZIPFILEVIEWDLG_H__542B107C_9AA7_4449_8841_645B04DCB2C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZipFileViewDlg.h : header file
//
#include "ZipCompress.h"
/////////////////////////////////////////////////////////////////////////////
// CZipFileViewDlg dialog

class CZipFileViewDlg : public CDialog
{
// Construction
public:
	BOOL DirOpen();
	CZipFileViewDlg(CWnd* pParent = NULL);   // standard constructor

	CZipCompress m_zCom;
	CString m_FilePassName;
	BOOL bfOpen;

	void SAFEDELETE(arVerList &tempList);
// Dialog Data
	//{{AFX_DATA(CZipFileViewDlg)
	enum { IDD = IDD_FILE_COMPRESS };
	CProgressCtrl	m_Prograss;
	CListCtrl	m_fileList;
	CButton	m_Compress;
	CButton	m_DirSearch;
	CString	m_Dir;
	CString	m_FileVersion;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZipFileViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZipFileViewDlg)
	afx_msg void OnDirSearch();
	afx_msg void OnCompress();
	afx_msg void OnFileView();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZIPFILEVIEWDLG_H__542B107C_9AA7_4449_8841_645B04DCB2C5__INCLUDED_)
