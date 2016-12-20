// ZipFileViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "servicemanager.h"
#include "ZipFileViewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZipFileViewDlg dialog


CZipFileViewDlg::CZipFileViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZipFileViewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZipFileViewDlg)
	m_Dir = _T("");
	m_FileVersion = _T("");
	m_FilePassName = _T("");
	bfOpen = FALSE;
	//}}AFX_DATA_INIT
}


void CZipFileViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZipFileViewDlg)
	DDX_Control(pDX, IDC_ZIP_PROGRESS, m_Prograss);
	DDX_Control(pDX, IDC_FILE_LIST, m_fileList);
	DDX_Control(pDX, ID_COMPRESS, m_Compress);
	DDX_Control(pDX, IDC_DIR_SEARCH, m_DirSearch);
	DDX_Text(pDX, IDC_DIR, m_Dir);
	DDX_CBString(pDX, IDC_FILE_VERSION, m_FileVersion);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZipFileViewDlg, CDialog)
	//{{AFX_MSG_MAP(CZipFileViewDlg)
	ON_BN_CLICKED(IDC_DIR_SEARCH, OnDirSearch)
	ON_BN_CLICKED(ID_COMPRESS, OnCompress)
	ON_BN_CLICKED(ID_FILE_VIEW, OnFileView)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZipFileViewDlg message handlers

void CZipFileViewDlg::OnDirSearch() 
{
	// TODO: Add your control notification handler code here
	int nNum = -1;
	CString strName = _T("");

	m_Dir = _T("");
	bfOpen = FALSE;

	CFileDialog file( TRUE, "All", "*.dol", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "드로이얀 온라인 패치 파일");

	if(file.DoModal() == IDOK)
	{
		strName = file.GetPathName();
		nNum = strName.Find("DroiyanOnline.dol");
		if(nNum == -1) { MessageBox("Droiyan Online Patch를 나타내는 파일이 없습니다.\n", NULL, MB_OK); return; }
		UpdateData(TRUE);
		m_FilePassName = strName;		
		strName.TrimRight("DroiyanOnline.dol");
		m_Dir = strName;
		if(!m_FileVersion.IsEmpty()) bfOpen = TRUE;
		UpdateData(FALSE);
	}
}

BOOL CZipFileViewDlg::DirOpen()
{
	OnDirSearch();
	return TRUE;
}

void CZipFileViewDlg::OnCompress() 
{
	// TODO: Add your control notification handler code here
	int i;
	int preVer = -1;
	CString zipName = _T("");

	SAFEDELETE(m_zCom.m_VerList);

	int ver = -1;
	if(!bfOpen)	
	{
		AfxMessageBox(_T("디렉토리 설정이 잘못됐습니다."));
		return;
	}

	ver = atoi(m_FileVersion);
	if(ver <= 0)
	{
		AfxMessageBox(_T("버젼이 맞지 않습니다."));
		return;
	}

	CString sz;
	m_zCom.GetFileName(zipName, sz, FALSE);
	if(!m_zCom.SetFileNameToDB(ver, zipName, 0))
	{
		AfxMessageBox(_T("DB에 파일이름 쓰기 실패."));
		return;
	}

	arVerList tempList;
															// 지금 작업버젼부터 이전버젼까지 다시 조사한다.
	if(!m_zCom.GetFileNameFromDB(tempList))					// 해당 압축파일의 이름과 버젼을 탐지
	{
		AfxMessageBox(_T("빈 DB입니다."));
		return;
	}

	if(tempList.GetSize() <= 0) return;						// 테스트용 오류 체크

	for(i = 0; i < tempList.GetSize(); i++)					// 등록된 압축파일 이름를 기준으로 
	{
		preVer = tempList[i]->iVer;
		zipName = tempList[i]->strZipName;
		if(!m_zCom.GetFileNameToCompress(preVer, m_Dir, zipName))// 실제 파일 DB에서 목록를 얻어온다.
		{
			AfxMessageBox(_T("압축 파일목록에 해당하는 DB파일를 여는데 실패했습니다."));
			SAFEDELETE(tempList);
			SAFEDELETE(m_zCom.m_VerList);
			return;
		}

		if(m_zCom.m_VerList[i]->arFileList.GetSize() <= 0)			// 압축할 파일이 없는 압축이름은 삭제
		{
			m_zCom.SetFileNameToDB(preVer, zipName, 1);
			AfxMessageBox(_T("압축 파일목록에 해당하는 실제 파일 목록이 없습니다."));
			SAFEDELETE(tempList);
			SAFEDELETE(m_zCom.m_VerList);
			return;
		}

	}
	
	SAFEDELETE(tempList);										// 임시 리스트를 삭제한다.

	CString		strMsg;

	m_Prograss.SetRange(0, 100);
	m_Prograss.SetPos(0);

	strMsg.Format("%s", "버젼별 압축 파일를 준비하고 있습니다.\n");
	SetDlgItemText(IDC_ZIP_STATIC, strMsg);

	int iSize = m_zCom.m_VerList.GetSize();

	if(iSize <= 0)
	{
		strMsg.Format("%s", "압축 파일이 존재하지 않습니다.\n");
		SetDlgItemText(IDC_ZIP_STATIC, strMsg);
		return;
	}

	for(i = 0; i < iSize; i++)
	{
		m_Prograss.SetPos(0);
		strMsg.Format("%s를 압축하고 있습니다.\n", m_zCom.m_VerList[i]->strZipName);
		SetDlgItemText(IDC_ZIP_STATIC, strMsg);

		if(!m_zCom.SetFilesToCompress(i, m_Dir, m_Prograss))
		{
			SAFEDELETE(m_zCom.m_VerList);
		}
	}

	m_Prograss.SetPos(0);

	strMsg.Format("압축이 끝났습니다.\n");
	SetDlgItemText(IDC_ZIP_STATIC, strMsg);
}

void CZipFileViewDlg::SAFEDELETE(arVerList &tempList)
{
	for(int i = 0; i < tempList.GetSize(); i++)
	{
		if(tempList[i]) delete tempList[i];
	}

	tempList.RemoveAll();
}

////////////////////////////////////////////////////////////////////////
//
//	압축 파일 목록를 보여준다.
//
void CZipFileViewDlg::OnFileView() 
{
	// TODO: Add your control notification handler code here
	CFileHeader file;

	CString str, strName, strPath;
	str = _T("");
	strName = _T("");
	strPath = _T("");

	if (!m_zCom.GetFileName(strName, strPath, TRUE))	return;

	m_zCom.m_zip.Open(strPath);

	m_fileList.DeleteAllItems();

	if(m_zCom.m_zip.GetNoEntries() < 500) 
	{
		for(WORD i = 0; i < m_zCom.m_zip.GetNoEntries(); i++)
		{
			CFileHeader fh;
			m_zCom.m_zip.GetFileInfo(fh, (WORD)i);
			int iItem = m_fileList.GetItemCount();
			m_fileList.InsertItem(iItem, fh.m_szFileName);
			CString sz;
			sz.Format("%d Byte", fh.m_uUncomprSize);
			m_fileList.SetItemText(iItem, 1, sz);
		}	
		m_fileList.UpdateData();
	}
	m_zCom.m_zip.Close();
}

BOOL CZipFileViewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int j;
	LV_COLUMN lvcolum;
	int	cItem = 0;

	TCHAR 	*Obj[2] = {"File Name", "Size"};
	int		width[2] = {180,80};

	for(j =0; j < 2; j++)
	{
		lvcolum.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_FMT | LVCF_WIDTH;
		lvcolum.fmt = LVCFMT_LEFT;
		lvcolum.pszText = Obj[j];
		lvcolum.iSubItem = j;
		lvcolum.cx = width[j];
		m_fileList.InsertColumn(j, &lvcolum);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CZipFileViewDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	SAFEDELETE(m_zCom.m_VerList);
}
