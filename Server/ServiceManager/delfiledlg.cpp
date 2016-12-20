// DelFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ServiceManagerDoc.h"
#include "DelFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDelFileDlg dialog


CDelFileDlg::CDelFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDelFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDelFileDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDelFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDelFileDlg)
	DDX_Control(pDX, IDC_LIST_FILE, m_listFile);
	DDX_Control(pDX, IDC_LIST_DEL, m_listDel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDelFileDlg, CDialog)
	//{{AFX_MSG_MAP(CDelFileDlg)
	ON_BN_CLICKED(IDC_BUTTON_DELFILE, OnButtonDelfile)
	ON_BN_CLICKED(IDC_BUTTON_RESTORE, OnButtonRestore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDelFileDlg message handlers

void CDelFileDlg::OnButtonDelfile() 
{
	int bufIndex[1024];
	int nNumSel = m_listFile.GetSelItems(1024, bufIndex);
	CObList listDel;
	for (int i = 0; i < nNumSel; i++)
		listDel.AddTail ((CFileInfo*)m_listFile.GetItemDataPtr (bufIndex[i]));

	while (!listDel.IsEmpty ())
	{
		CFileInfo* pInfo = (CFileInfo*)listDel.RemoveHead ();
		int nIndex = m_listFile.FindStringExact (-1, pInfo->m_strFileName);
		if (nIndex != LB_ERR)
		{
			m_listFile.DeleteString (nIndex);
			nIndex = m_listDel.AddString (pInfo->m_strFileName);
			m_listDel.SetItemDataPtr (nIndex, pInfo);
			POSITION pos = m_listCurFile.Find (pInfo);
			if (pos)
				m_listCurFile.RemoveAt (pos);
			m_listDelFile.AddTail (pInfo);
		}
	}
}

void CDelFileDlg::OnButtonRestore() 
{
	int bufIndex[1024];
	int nNumSel = m_listDel.GetSelItems(1024, bufIndex);
	CObList listDel;
	for (int i = 0; i < nNumSel; i++)
		listDel.AddTail ((CFileInfo*)m_listDel.GetItemDataPtr (bufIndex[i]));

	while (!listDel.IsEmpty ())
	{
		CFileInfo* pInfo = (CFileInfo*)listDel.RemoveHead ();
		int nIndex = m_listDel.FindStringExact (-1, pInfo->m_strFileName);
		if (nIndex != LB_ERR)
		{
			m_listDel.DeleteString (nIndex);
			nIndex = m_listFile.AddString (pInfo->m_strFileName);
			m_listFile.SetItemDataPtr (nIndex, pInfo);
			POSITION pos = m_listCurFile.Find (pInfo);
			if (pos)
				m_listCurFile.RemoveAt (pos);
			m_listDelFile.AddTail (pInfo);
		}
	}
}

BOOL CDelFileDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	POSITION pos = m_listCurFile.GetHeadPosition ();
	while (pos)
	{
		CFileInfo* pInfo = (CFileInfo*)m_listCurFile.GetNext (pos);
		int nIndex = m_listFile.AddString (pInfo->m_strFileName);
		m_listFile.SetItemDataPtr (nIndex, pInfo);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
