// ClientSelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "servicemanager.h"
#include "ClientSelectDlg.h"
#include "ClientSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSelectDlg dialog


CClientSelectDlg::CClientSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientSelectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientSelectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CClientSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientSelectDlg)
	DDX_Control(pDX, IDC_CLIENT_NAME, m_wndClientName);
	DDX_Control(pDX, IDC_LIST_CLIENT, m_wndListClient);
	//}}AFX_DATA_MAP
}

void CClientSelectDlg::InitListCtrl()
{
#ifdef _USE_ENGLISH
	m_wndListClient.InsertColumn(0, "Name", LVCFMT_CENTER, 60);
	m_wndListClient.InsertColumn(1, "ID", LVCFMT_CENTER, 30);
	m_wndListClient.InsertColumn(2, "Registered Business Number", LVCFMT_CENTER, 140);
#else
	m_wndListClient.InsertColumn(0, "이름", LVCFMT_CENTER, 60);
	m_wndListClient.InsertColumn(1, "ID", LVCFMT_CENTER, 30);
	m_wndListClient.InsertColumn(2, "사업자 등록 번호", LVCFMT_CENTER, 140);
#endif
}

BEGIN_MESSAGE_MAP(CClientSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CClientSelectDlg)
	ON_BN_CLICKED(IDC_BUTTON_CLIENTSEARCH, OnButtonClientsearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientSelectDlg message handlers

BOOL CClientSelectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	InitListCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CClientSelectDlg::OnButtonClientsearch() 
{
	CString client_name;

	m_wndClientName.GetWindowText(client_name);

	if(client_name.IsEmpty()) return;

	CClientSet clientset(&g_db);

	clientset.m_strFilter.Format("strName Like '%%%s%%'", client_name);

	if(clientset.Open())
	{
		m_wndListClient.DeleteAllItems();
		while(!clientset.IsEOF())
		{
			CString item_name;
			
			int index = m_wndListClient.InsertItem(0, clientset.m_strName);
			item_name.Format("%d", clientset.m_wID);
			m_wndListClient.SetItemText(index, 1, item_name);
			m_wndListClient.SetItemText(index, 2, clientset.m_strRegNo);
			m_wndListClient.SetItemData(index, (DWORD)clientset.m_wID);

			clientset.MoveNext();
		}
		clientset.Close();
	}
}

void CClientSelectDlg::OnOK() 
{
	POSITION pos = m_wndListClient.GetFirstSelectedItemPosition();
	
	if(pos)
	{
		int nItem = m_wndListClient.GetNextSelectedItem(pos);
		m_vClientID = (int)m_wndListClient.GetItemData(nItem);
		m_vClientName = m_wndListClient.GetItemText(nItem, 0);
	}
	else
	{
#ifdef _USE_ENGLISH
		MessageBox("Choose a game room first.", "View charge information", MB_OK|MB_ICONINFORMATION);
#else
		MessageBox("게임방을 먼저 선택하세요.", "과금정보 보기", MB_OK|MB_ICONINFORMATION);
#endif
		return;
	}
	
	CDialog::OnOK();
}
