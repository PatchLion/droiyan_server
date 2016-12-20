// SearchLogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "SearchLogDlg.h"
#include "Session.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchLogDlg dialog


CSearchLogDlg::CSearchLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchLogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchLogDlg)
	m_strSerial1 = _T("");
	m_strSerial2 = _T("");
	m_timeStart = CTime::GetCurrentTime ();
	//}}AFX_DATA_INIT
}


void CSearchLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchLogDlg)
	DDX_Text(pDX, IDC_EDIT_USERID, m_strUserID);
	DDX_Text(pDX, IDC_EDIT_SERIAL1, m_strSerial1);
	DDX_Text(pDX, IDC_EDIT_SERIAL2, m_strSerial2);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START, m_timeStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchLogDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchLogDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchLogDlg message handlers

