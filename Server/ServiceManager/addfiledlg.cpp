// AddFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "AddFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddFileDlg dialog


CAddFileDlg::CAddFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddFileDlg)
	m_strSrcPath = _T("");
	m_wGameVer = 0;
	m_fComp = FALSE;
	//}}AFX_DATA_INIT
}


void CAddFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddFileDlg)
	DDX_Control(pDX, IDC_LIST_FILE, m_listFile);
	DDX_Text(pDX, IDC_EDIT_PATH, m_strSrcPath);
	DDX_Text(pDX, IDC_EDIT_VER, m_wGameVer);
	DDX_Check(pDX, IDC_CHECK_COMP, m_fComp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddFileDlg, CDialog)
	//{{AFX_MSG_MAP(CAddFileDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADDFILE, OnButtonAddfile)
	ON_BN_CLICKED(IDC_BUTTON_DELFILE, OnButtonDelfile)
	ON_BN_CLICKED(IDC_BUTTON_ADDALL, OnButtonAddall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddFileDlg message handlers

void CAddFileDlg::OnButtonAddfile() 
{
	GetDlgItemText (IDC_EDIT_PATH, m_strSrcPath);
	if (!::SetCurrentDirectory (m_strSrcPath))
	{
		return;
	}
	m_strSrcPath.MakeUpper ();

	LPTSTR szFileName[16384];
	CFileDialog dlg (TRUE);
	szFileName[0] = 0;
	dlg.m_ofn.Flags |= OFN_ALLOWMULTISELECT | OFN_EXPLORER;
	dlg.m_ofn.lpstrFile = (LPTSTR)szFileName;
	dlg.m_ofn.nMaxFile = 16384;

	if (dlg.DoModal () == IDOK)
	{
		POSITION pos = dlg.GetStartPosition ();
		while (pos)
		{
			CString strFullPath = dlg.GetNextPathName (pos);
			strFullPath.MakeUpper ();
			int nIndex = strFullPath.Find (m_strSrcPath);
			if (nIndex != -1)
			{
				strFullPath = strFullPath.Right (strFullPath.GetLength () - nIndex - 
					m_strSrcPath.GetLength () - 1);
				m_listFile.AddString (strFullPath);
			}
		}
	}
}

void CAddFileDlg::OnButtonDelfile() 
{
	int bufIndex[1024];
	int nNumSel = m_listFile.GetSelItems(1024, bufIndex);
	CStringList listDel;
	for (int i = 0; i < nNumSel; i++)
	{
		CString strFile;
		m_listFile.GetText (bufIndex[i], strFile);
		listDel.AddTail (strFile);
	}
	while (!listDel.IsEmpty ())
	{
		CString strFile = listDel.RemoveHead ();
		int nIndex = m_listFile.FindStringExact (-1, strFile);
		m_listFile.DeleteString (nIndex);
	}
}

void CAddFileDlg::OnOK() 
{
	for (int i = 0; i < m_listFile.GetCount (); i++)
	{
		CString strText;
		m_listFile.GetText (i, strText);
		m_listFileName.AddTail (strText);
	}
	CDialog::OnOK();
}

void CAddFileDlg::OnButtonAddall() 
{
	GetDlgItemText (IDC_EDIT_PATH, m_strSrcPath);
	if (!::SetCurrentDirectory (m_strSrcPath))
	{
		return;
	}

	m_listFile.Dir (0, _T("*.*"));
}

