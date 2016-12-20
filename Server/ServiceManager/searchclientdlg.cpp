// SearchClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "SearchClientDlg.h"

#include "ClientSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchClientDlg dialog


CSearchClientDlg::CSearchClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchClientDlg)
	m_nLoc = -1;
	m_strName = _T("");
	m_strHost = _T("");
	m_strTelNo = _T("");
	m_time = 0;
	m_strSearchRegNo1 = _T("");
	m_strSearchRegNo2 = _T("");
	m_strSearchRegNo3 = _T("");
	//}}AFX_DATA_INIT
}


void CSearchClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchClientDlg)
	DDX_CBIndex(pDX, IDC_COMBO_SEARCHLOC, m_nLoc);
	DDX_Text(pDX, IDC_EDIT_SEARCHNAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_SEARCHHOST, m_strHost);
	DDX_Text(pDX, IDC_EDIT_SEARCHTEL, m_strTelNo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_SEARCHDATE, m_time);
	DDX_Text(pDX, IDC_EDIT_SEARCHREGNO1, m_strSearchRegNo1);
	DDV_MaxChars(pDX, m_strSearchRegNo1, 3);
	DDX_Text(pDX, IDC_EDIT_SEARCHREGNO2, m_strSearchRegNo2);
	DDV_MaxChars(pDX, m_strSearchRegNo2, 2);
	DDX_Text(pDX, IDC_EDIT_SEARCHREGNO3, m_strSearchRegNo3);
	DDV_MaxChars(pDX, m_strSearchRegNo3, 5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchClientDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchClientDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchClientDlg message handlers

