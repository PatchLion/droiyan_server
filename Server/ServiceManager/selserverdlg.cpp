// SelServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ServiceManagerDoc.h"
#include "SelServerDlg.h"

#include "Server.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelServerDlg dialog


CSelServerDlg::CSelServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelServerDlg)
	m_strServer = _T("");
	//}}AFX_DATA_INIT
	m_nCheck = 0;
}


void CSelServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelServerDlg)
	DDX_Control(pDX, IDC_LIST_SERVER, m_listServer);
	DDX_LBString(pDX, IDC_LIST_SERVER, m_strServer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelServerDlg, CDialog)
	//{{AFX_MSG_MAP(CSelServerDlg)
	ON_LBN_DBLCLK(IDC_LIST_SERVER, OnDblclkListServer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelServerDlg message handlers

BOOL CSelServerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (m_pListServer)
	{
		POSITION pos = m_pListServer->GetHeadPosition ();
		while (pos)
		{
			CServer* pServer = (CServer*)m_pListServer->GetNext (pos);
			int nIndex;
			switch (m_nCheck)
			{
			case 0 : // Add All
				nIndex = m_listServer.AddString (pServer->m_strName);
				m_listServer.SetItemDataPtr (nIndex, pServer);
				break;
			case 1 : // Add Connected
				if (pServer->m_fConnect)
				{
					nIndex = m_listServer.AddString (pServer->m_strName);
					m_listServer.SetItemDataPtr (nIndex, pServer);
				}
				break;
			case 2 : // Add Disconnected
				if (!pServer->m_fConnect)
				{
					nIndex = m_listServer.AddString (pServer->m_strName);
					m_listServer.SetItemDataPtr (nIndex, pServer);
				}
			}
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelServerDlg::OnDblclkListServer() 
{
	OnOK ();
}
