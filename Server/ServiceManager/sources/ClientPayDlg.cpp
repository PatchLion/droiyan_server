// ClientPayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "servicemanager.h"
#include "ClientPayDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientPayDlg dialog


CClientPayDlg::CClientPayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientPayDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientPayDlg)
	m_strFromYear = _T("");
	m_strToYear = _T("");
	//}}AFX_DATA_INIT
}


void CClientPayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientPayDlg)
	DDX_Control(pDX, IDC_CLIENT_LIST, m_listctrl);
	DDX_Control(pDX, IDC_TO_MONTH, m_toMonth);
	DDX_Control(pDX, IDC_FROM_MONTH, m_fromMonth);
	DDX_Text(pDX, IDC_FROM_YEAR, m_strFromYear);
	DDX_Text(pDX, IDC_TO_YEAR, m_strToYear);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClientPayDlg, CDialog)
	//{{AFX_MSG_MAP(CClientPayDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientPayDlg message handlers

void CClientPayDlg::AddClient(CClientSet *pSet)
{
	CString strText;
	LV_ITEM	item;

	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = 0;
	item.iSubItem = 0;
	item.pszText = (char*)LPCTSTR(pSet->m_strName);

	int nIndex = m_listctrl.InsertItem (&item);
	m_listctrl.SetItemText (nIndex, 1, pSet->m_strRegNo);
}

BOOL CClientPayDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	CClientSet clientset(&g_db);
	LV_COLUMN lvc;
	CTime date;

	m_listctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.fmt = LVCFMT_LEFT;
#ifdef _USE_ENGLISH
	lvc.pszText = _T("Firm Name");
#else
	lvc.pszText = _T("상  호");
#endif
	lvc.cx = 190;
	lvc.iSubItem = 0;
	m_listctrl.InsertColumn ( 0, &lvc);

	lvc.fmt = LVCFMT_CENTER;
#ifdef _USE_ENGLISH
	lvc.pszText = _T("Registered Business Number");
#else
	lvc.pszText = _T("사업자 등록번호");
#endif
	lvc.cx = 120;
	lvc.iSubItem = 1;
	m_listctrl.InsertColumn ( 1, &lvc);

	if(!clientset.Open ())
	{
		AfxMessageBox (IDS_ERR_DBOPEN);
		return TRUE;
	}

	while(!clientset.IsEOF ())
	{
		AddClient(&clientset);
		clientset.MoveNext();
	}

	clientset.Close();
	date = CTime::GetCurrentTime();

	m_strFromYear.Format( "%ld", date.GetYear());
	m_strToYear.Format( "%ld", date.GetYear());
	m_fromMonth.SetCurSel(date.GetMonth()-1);
	m_toMonth.SetCurSel(date.GetMonth()-1);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CClientPayDlg::OnOK()
{
	// TODO: Add extra validation here
	POSITION pos = m_listctrl.GetFirstSelectedItemPosition();
	int nItem;

	m_nFrom  = atol(m_strFromYear);
	m_nFrom *= 100;
	m_nFrom += m_fromMonth.GetCurSel() + 1;

	m_nTo  = atol(m_strToYear);
	m_nTo *= 100;
	m_nTo += m_toMonth.GetCurSel() + 1;

	m_listClient.RemoveAll();

	while(pos)
	{
		nItem = m_listctrl.GetNextSelectedItem(pos);
		LPCTSTR(m_listctrl.GetItemText( nItem, 1));

		if(pos) m_listClient.AddTail(LPCTSTR(m_listctrl.GetItemText( nItem, 1)));
	}

	CDialog::OnOK();
}
