// ServiceManagerView.cpp : implementation of the CServiceManagerView class
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ServiceManagerDoc.h"
#include "ServiceManagerView.h"

#include "Server.h"
#include "Service.h"
#include "UserManager.h"
#include "FileManager.h"
#include "Session.h"

//==========================================================
#include "StatusConst.h"
#include "StatusView.h"
#include "ClientPaySet.h"
#include "ClientSet.h"
//==========================================================


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define Line_Margine    21
#define Left_Margine    50
#define Font_Size       14
#define FirstPage       30
#define EtcPage         33
#define COL_MARGIN      20
#define PaperWidth    1135
#define PaperHeight    793

#ifdef _USE_ENGLISH
#define FONT_NAME	_T("Arial")
#else
#define FONT_NAME	_T("굴림체")
#endif

/////////////////////////////////////////////////////////////////////////////
// CServiceManagerView

IMPLEMENT_DYNCREATE(CServiceManagerView, CTreeView)

BEGIN_MESSAGE_MAP(CServiceManagerView, CTreeView)
	//{{AFX_MSG_MAP(CServiceManagerView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServiceManagerView construction/destruction

CServiceManagerView::CServiceManagerView()
{
	// TODO: add construction code here
}

CServiceManagerView::~CServiceManagerView()
{
}

BOOL CServiceManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | 
		TVS_SHOWSELALWAYS | TVS_DISABLEDRAGDROP;
	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CServiceManagerView drawing

void CServiceManagerView::OnDraw(CDC* pDC)
{
	CServiceManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CServiceManagerView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	CServiceManagerDoc* pDoc = GetDocument();
	CTreeCtrl& tree = GetTreeCtrl ();
	tree.SetImageList (&pDoc->m_imageTree, TVSIL_NORMAL);
}

/////////////////////////////////////////////////////////////////////////////
// CServiceManagerView diagnostics

#ifdef _DEBUG
void CServiceManagerView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CServiceManagerView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CServiceManagerDoc* CServiceManagerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CServiceManagerDoc)));
	return (CServiceManagerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CServiceManagerView message handlers

void CServiceManagerView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{

	switch (lHint)
	{
	case UPDATE_ALL					: OnUpdateAll (); break;
	case UPDATE_ADDSERVER			: OnAddServer ((CServer*)pHint); break;
	case UPDATE_DELSERVER			: OnDelServer ((CServer*)pHint); break;
	case UPDATE_SERVERSTATUS		: OnServerStatus ((CServer*)pHint); break;
	case UPDATE_INSTALLSERVICE		: OnInstallService ((CService*)pHint); break;
	case UPDATE_REMOVESERVICE		: OnRemoveService ((CService*)pHint); break;
	case UPDATE_SERVICESTATUS		: OnServiceStatus ((CService*)pHint); break;
	case UPDATE_SERVICECONFIG		: OnServiceConfig ((CService*)pHint); break;
	case UPDATE_ADDFILE				: OnAddFile ((CFileInfo*)pHint); break;
	case UPDATE_DELFILE				: OnDeleteFile ((CFileInfo*)pHint); break;
	case UPDATE_UPDATEFILE			: OnUpdateFile ((CFileInfo*)pHint); break;
	}
}


void CServiceManagerView::OnUpdateAll()
{
	CServiceManagerDoc* pDoc = GetDocument ();
	CTreeCtrl& tree = GetTreeCtrl ();

	tree.DeleteAllItems ();

	CString strName;
	strName.LoadString (IDS_TREE_SERVER);
	m_hServer = InsertItem (strName, 0, 0, NULL, selServerRoot);

	strName.LoadString (IDS_TREE_SERVICE);
	m_hService = InsertItem (strName, 3, 3, NULL, selServiceRoot);

	strName.LoadString (IDS_TREE_SM);
	m_hSession = InsertItem (strName, 3, 3, m_hService, selSessionRoot);

	strName.LoadString (IDS_TREE_GS);
	m_hGame = InsertItem (strName, 3, 3, m_hService, selGameRoot);

	strName.LoadString (IDS_TREE_VERSION);
	m_hVersion = InsertItem (strName, 11, 11, NULL, selVersionRoot);

	strName.FormatMessage (IDS_TREE_VER_CURRENT, 0);
	m_hCurrentVer = InsertItem (strName, 10, 10, m_hVersion, selVersion);
	strName.FormatMessage (IDS_TREE_VER_NUMFILE, 0);
	m_hNumFile = InsertItem (strName, 10, 10, m_hVersion, selNumFile);
	m_hFolder = InsertItem (_T(""), 11, 11, m_hVersion, selFolder);

	POSITION pos = pDoc->m_listServer.GetHeadPosition ();
	while (pos)
	{
		CServer* pServer = (CServer*)pDoc->m_listServer.GetNext (pos);
		OnAddServer (pServer);
	}
}

void CServiceManagerView::OnAddServer(CServer * pServer)
{
	CServiceManagerDoc* pDoc = GetDocument ();
	CTreeCtrl& tree = GetTreeCtrl ();

	HTREEITEM hServer = InsertItem (pServer->m_strName, 0, 0, m_hServer, selServer, pServer);

	CString strName;
	strName.LoadString (IDS_TREE_IPADDR);
	InsertItem (strName, 7, 7, hServer);
	strName.LoadString (IDS_TREE_SERVICE);
	InsertItem (strName, 3, 3, hServer);
	OnServerStatus (pServer);
}

void CServiceManagerView::OnDelServer(CServer * pServer)
{
	CServiceManagerDoc* pDoc = GetDocument ();
	CTreeCtrl& tree = GetTreeCtrl ();

	HTREEITEM hServer = FindServerItem (pServer);
	if (hServer)
		tree.DeleteItem (hServer);
}

void CServiceManagerView::OnServerStatus(CServer * pServer)
{
	CServiceManagerDoc* pDoc = GetDocument ();
	CTreeCtrl& tree = GetTreeCtrl ();

	HTREEITEM hServer = FindServerItem (pServer);
	if (hServer)
	{
		int nImage = (pServer->m_fConnect) ? 1 : 2;
		tree.SetItemImage (hServer, nImage, nImage);

		HTREEITEM hAddrRoot = tree.GetChildItem (hServer);
		HTREEITEM hAddr = tree.GetChildItem (hAddrRoot);
		while (hAddr)
		{
			tree.DeleteItem (hAddr);
			hAddr = tree.GetChildItem (hAddrRoot);
		}

		POSITION pos = pServer->m_listAddr.GetHeadPosition ();
		while (pos)
		{
			CString strAddr = pServer->m_listAddr.GetNext (pos);
			nImage = (pServer->m_strAddr == strAddr) ? 8 : 9;
			InsertItem (strAddr, nImage, nImage, hAddrRoot);
		}

	}
}

void CServiceManagerView::OnInstallService(CService * pService)
{
	CServiceManagerDoc* pDoc = GetDocument ();
	CTreeCtrl& tree = GetTreeCtrl ();

	int nImage = 3;
	switch (pService->m_dwStatus)
	{
	case SERVICE_RUNNING :	nImage = 5; break;
	case SERVICE_PAUSED :	nImage = 4; break;
	case SERVICE_STOPPED :	nImage = 6; break;
	}

	HTREEITEM hServer = FindServerItem (pService->m_pServer);
	CString strText;
	if (hServer)
	{
		HTREEITEM hAddrRoot = tree.GetChildItem (hServer);
		HTREEITEM hServiceRoot = tree.GetNextSiblingItem (hAddrRoot);
		HTREEITEM hService;
		if (hServiceRoot)
		{
			hService = InsertItem (pService->m_strDisplayName, 
				nImage, nImage, hServiceRoot, selService, pService);

			strText.FormatMessage (IDS_TREE_SERVICE_ADDR, pService->m_strAddr);
			InsertItem (strText, 10, 10, hService);

			strText.FormatMessage (IDS_TREE_SERVICE_PORT, pService->m_nPort);
			InsertItem (strText, 10, 10, hService);

			strText.FormatMessage (IDS_TREE_SERVICE_CAPACITY, pService->m_nCapacity);
			InsertItem (strText, 10, 10, hService);

			if (pService->m_dwTimer)
				strText.FormatMessage (IDS_TREE_SERVICE_TIMER, pService->m_dwTimer);
			else
				strText.LoadString (IDS_TREE_SERVICE_TIMERNONE);
			InsertItem (strText, 10, 10, hService);

			if (pService->m_dwTimeOuts)
				strText.FormatMessage (IDS_TREE_SERVICE_TIMEOUTS, pService->m_dwTimeOuts);
			else
				strText.LoadString (IDS_TREE_SERVICE_TIMEOUTNONE);
			InsertItem (strText, 10, 10, hService);
		}

		CUserManager* pUM;
		CFileManager* pFM;
		CSession* pSM;

		switch (pService->m_nType)
		{
		case CService::typeUM :
			strText.LoadString (IDS_TREE_UM);
			hService = InsertItem (strText, nImage, nImage, m_hService, selService, pService);
			
			pUM = (CUserManager*)pService;
			strText.FormatMessage (IDS_TREE_CONFIG_SERVER, pUM->m_pServer->m_strName);
			InsertItem (strText, 10, 10, hService);

			strText.FormatMessage (IDS_TREE_UM_FMADDR, pUM->m_strFMAddr, pUM->m_nFMPort);
			InsertItem (strText, 10, 10, hService);

			strText.FormatMessage (IDS_TREE_UM_GSADDR, pUM->m_strGSAddr, pUM->m_nGSPort);
			InsertItem (strText, 10, 10, hService);

			break;

		case CService::typeFM :
			strText.LoadString (IDS_TREE_FM);
			hService = InsertItem (strText, nImage, nImage, m_hService, selService, pService);
			
			pFM = (CFileManager*)pService;
			strText.FormatMessage (IDS_TREE_CONFIG_SERVER, pFM->m_pServer->m_strName);
			InsertItem (strText, 10, 10, hService);

			strText.FormatMessage (IDS_TREE_FM_SRCPATH, pFM->m_strSrcPath);
			InsertItem (strText, 10, 10, hService);

			strText.FormatMessage (IDS_TREE_FM_BUFFER, pFM->m_dwBuffer);
			InsertItem (strText, 10, 10, hService);

			break;

		case CService::typeSM :
			pSM = (CSession*)pService;
			hService = InsertItem (pSM->m_strName, nImage, nImage, m_hSession, selService, pService);
			
			strText.FormatMessage (IDS_TREE_CONFIG_SERVER, pSM->m_pServer->m_strName);
			InsertItem (strText, 10, 10, hService);

			strText.FormatMessage (IDS_TREE_SM_CAPACITY, pSM->m_nCapacity);
			InsertItem (strText, 10, 10, hService);

			strText.FormatMessage (IDS_TREE_SM_ID, pSM->m_nServerID);
			InsertItem (strText, 10, 10, hService);

			if (pSM->m_fPay)
				strText.LoadString (IDS_TREE_SM_PAY);
			else
				strText.LoadString (IDS_TREE_SM_FREE);
			InsertItem (strText, 10, 10, hService);

			break;

		case CService::typeGS :
			hService = InsertItem (pService->m_strDisplayName, nImage, nImage, m_hGame, selService, pService);
			
			strText.FormatMessage (IDS_TREE_CONFIG_SERVER, pService->m_pServer->m_strName);
			InsertItem (strText, 10, 10, hService);

			strText.FormatMessage (IDS_TREE_GS_ID, pService->m_nServerID);
			InsertItem (strText, 10, 10, hService);
			break;
		}
	}
}

void CServiceManagerView::OnRemoveService(CService * pService)
{
	CServiceManagerDoc* pDoc = GetDocument ();
	CTreeCtrl& tree = GetTreeCtrl ();

	HTREEITEM hService = FindServiceItem (m_hServer, pService);
	if (hService)
		tree.DeleteItem (hService);

	hService = FindServiceItem (m_hService, pService);
	if (hService)
		tree.DeleteItem (hService);
}

void CServiceManagerView::OnServiceStatus(CService * pService)
{
	CServiceManagerDoc* pDoc = GetDocument ();
	CTreeCtrl& tree = GetTreeCtrl ();

	int nImage = 3;
	switch (pService->m_dwStatus)
	{
	case SERVICE_RUNNING :	nImage = 5; break;
	case SERVICE_PAUSED :	nImage = 4; break;
	case SERVICE_STOPPED :	nImage = 6; break;
	}

	HTREEITEM hService = FindServiceItem (m_hServer, pService);
	if (hService)
		tree.SetItemImage (hService, nImage, nImage);

	hService = FindServiceItem (m_hService, pService);
	if (hService)
		tree.SetItemImage (hService, nImage, nImage);
}

void CServiceManagerView::OnServiceConfig(CService * pService)
{
	CServiceManagerDoc* pDoc = GetDocument ();
	CTreeCtrl& tree = GetTreeCtrl ();

	HTREEITEM hService = FindServiceItem (m_hServer, pService);
	if (hService)
	{
		CString strText;
		HTREEITEM hAttr;

		hAttr = tree.GetChildItem (hService);
		if (!hAttr)	return;
		strText.FormatMessage (IDS_TREE_SERVICE_ADDR, pService->m_strAddr);
		tree.SetItemText (hAttr, strText);

		hAttr = tree.GetNextSiblingItem (hAttr);
		if (!hAttr)	return;
		strText.FormatMessage (IDS_TREE_SERVICE_PORT, pService->m_nPort);
		tree.SetItemText (hAttr, strText);

		hAttr = tree.GetNextSiblingItem (hAttr);
		if (!hAttr)	return;
		strText.FormatMessage (IDS_TREE_SERVICE_CAPACITY, pService->m_nCapacity);
		tree.SetItemText (hAttr, strText);

		hAttr = tree.GetNextSiblingItem (hAttr);
		if (!hAttr)	return;
		if (pService->m_dwTimer)
			strText.FormatMessage (IDS_TREE_SERVICE_TIMER, pService->m_dwTimer);
		else
			strText.LoadString (IDS_TREE_SERVICE_TIMERNONE);
		tree.SetItemText (hAttr, strText);

		hAttr = tree.GetNextSiblingItem (hAttr);
		if (!hAttr)	return;
		if (pService->m_dwTimeOuts)
			strText.FormatMessage (IDS_TREE_SERVICE_TIMEOUTS, pService->m_dwTimeOuts);
		else
			strText.LoadString (IDS_TREE_SERVICE_TIMEOUTNONE);
		tree.SetItemText (hAttr, strText);
	}
	hService = FindServiceItem (m_hService, pService);
	if (hService)
	{
		CUserManager* pUM;
		CFileManager* pFM;
		CSession* pSM;
		HTREEITEM hAttr = tree.GetChildItem (hService);
		CString strText;
		switch (pService->m_nType)
		{
		case CService::typeUM :
			pUM = (CUserManager*)pService;

			strText.FormatMessage (IDS_TREE_CONFIG_SERVER, pUM->m_pServer->m_strName);
			tree.SetItemText (hAttr, strText);

			hAttr = tree.GetNextSiblingItem (hAttr);
			strText.FormatMessage (IDS_TREE_UM_FMADDR, pUM->m_strFMAddr, pUM->m_nFMPort);
			tree.SetItemText (hAttr, strText);

			hAttr = tree.GetNextSiblingItem (hAttr);
			strText.FormatMessage (IDS_TREE_UM_GSADDR, pUM->m_strGSAddr, pUM->m_nGSPort);
			tree.SetItemText (hAttr, strText);

			strText.FormatMessage (IDS_TREE_VER_CURRENT, pDoc->m_wGameVer);
			tree.SetItemText (m_hCurrentVer, strText);

			break;

		case CService::typeFM :
			pFM = (CFileManager*)pService;

			strText.FormatMessage (IDS_TREE_CONFIG_SERVER, pFM->m_pServer->m_strName);
			tree.SetItemText (hAttr, strText);

			hAttr = tree.GetNextSiblingItem (hAttr);
			strText.FormatMessage (IDS_TREE_FM_SRCPATH, pFM->m_strSrcPath);
			tree.SetItemText (hAttr, strText);

			hAttr = tree.GetNextSiblingItem (hAttr);
			strText.FormatMessage (IDS_TREE_FM_BUFFER, pFM->m_dwBuffer);
			tree.SetItemText (hAttr, strText);

			tree.SetItemText (m_hFolder, pFM->m_strSrcPath);

			break;

		case CService::typeSM :
			pSM = (CSession*)pService;

			tree.SetItemText (hService, pSM->m_strName);

			strText.FormatMessage (IDS_TREE_CONFIG_SERVER, pSM->m_pServer->m_strName);
			tree.SetItemText (hAttr, strText);

			hAttr = tree.GetNextSiblingItem (hAttr);
			strText.FormatMessage (IDS_TREE_SM_CAPACITY, pSM->m_nCapacity);
			tree.SetItemText (hAttr, strText);

			hAttr = tree.GetNextSiblingItem (hAttr);
			strText.FormatMessage (IDS_TREE_SM_ID, pSM->m_nServerID);
			tree.SetItemText (hAttr, strText);

			hAttr = tree.GetNextSiblingItem (hAttr);
			if (pSM->m_fPay)
				strText.LoadString (IDS_TREE_SM_PAY);
			else
				strText.LoadString (IDS_TREE_SM_FREE);
			tree.SetItemText (hAttr, strText);

			break;

		case CService::typeGS :
			strText.FormatMessage (IDS_TREE_CONFIG_SERVER, pService->m_pServer->m_strName);
			tree.SetItemText (hAttr, strText);

			hAttr = tree.GetNextSiblingItem (hAttr);
			strText.FormatMessage (IDS_TREE_GS_ID, pService->m_nServerID);
			tree.SetItemText (hAttr, strText);
			break;
		}
	}
}

HTREEITEM CServiceManagerView::FindServerItem(CServer * pServer)
{
	CTreeCtrl& tree = GetTreeCtrl ();
	HTREEITEM hServer = tree.GetChildItem (m_hServer);
	while (hServer)
	{
		if (GetItemData (hServer)->m_pObject == pServer)
			return hServer;
		hServer = tree.GetNextSiblingItem (hServer);
	}
	return NULL;
}

HTREEITEM CServiceManagerView::FindServiceItem(HTREEITEM hParent, CService * pService)
{
	CTreeCtrl& tree = GetTreeCtrl ();
	if (GetItemData (hParent)->m_pObject == pService)
		return hParent;

	HTREEITEM hChild = tree.GetChildItem (hParent);
	while (hChild)
	{
		HTREEITEM hService = FindServiceItem (hChild, pService);
		if (hService)
			return hService;
		hChild = tree.GetNextSiblingItem (hChild);
	}
	return NULL;
}

HTREEITEM CServiceManagerView::FindFile(HTREEITEM hParent, CFileInfo * pInfo)
{
	CTreeCtrl& tree = GetTreeCtrl ();
	if (GetItemData (hParent)->m_pObject == pInfo)
		return hParent;

	HTREEITEM hChild = tree.GetChildItem (hParent);
	while (hChild)
	{
		HTREEITEM hFile = FindFile (hChild, pInfo);
		if (hFile)
			return hFile;
		hChild = tree.GetNextSiblingItem (hChild);
	}
	return NULL;
}

HTREEITEM CServiceManagerView::FindFile(HTREEITEM hParent, CString fileName)
{
	CTreeCtrl& tree = GetTreeCtrl ();
	CSelItem *sel_item = (CSelItem *)GetItemData(hParent);
	if (sel_item && sel_item->m_nType == CSelItem::selFile && ((CFileInfo *)sel_item->m_pObject)->m_strFileName.CompareNoCase((LPCTSTR)fileName) == 0)
		return hParent;

	HTREEITEM hChild = tree.GetChildItem (hParent);
	while (hChild)
	{
		HTREEITEM hFile = FindFile (hChild, fileName);
		if (hFile)
			return hFile;
		hChild = tree.GetNextSiblingItem (hChild);
	}
	return NULL;
}

void CServiceManagerView::OnAddFile(CFileInfo* pInfo)
{
	CTreeCtrl& tree = GetTreeCtrl ();
	HTREEITEM hVersion = tree.GetChildItem (m_hFolder);
	CString strVer;
	strVer.FormatMessage (IDS_TREE_VER_VERSION, pInfo->m_wVer);
	while (hVersion)
	{
		CString strVer1 = tree.GetItemText (hVersion);
		if (strVer1 == strVer)
			break;
		hVersion = tree.GetNextSiblingItem (hVersion);
	}
	if (!hVersion)
	{
		hVersion = InsertItem (strVer, 11, 11, m_hFolder);
		tree.SortChildren (m_hFolder);
	}

	CString strText;
	if (pInfo->m_strCompName != _T(""))
		strText.FormatMessage (IDS_TREE_VER_FILECOMP, pInfo->m_strFileName);
	else
		strText = pInfo->m_strFileName;
	InsertItem (strText, 12, 12, hVersion, selFile, pInfo);
}

void CServiceManagerView::OnDeleteFile(CFileInfo* pInfo)
{
	CTreeCtrl& tree = GetTreeCtrl ();
	HTREEITEM hFile = FindFile (m_hFolder, pInfo);
	if (hFile)
	{
		HTREEITEM hParent = tree.GetParentItem (hFile);
		tree.DeleteItem (hFile);
		if (!tree.GetChildItem (hParent))
			tree.DeleteItem (hParent);
	}
}

void CServiceManagerView::OnUpdateFile(CFileInfo* pInfo)
{
}

void CServiceManagerView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	HTREEITEM hItemSel = pNMTreeView->itemNew.hItem;
	CServiceManagerDoc* pDoc = GetDocument ();
	pDoc->m_pSelItem = GetItemData (hItemSel);
	if (pDoc->m_pSelItem->m_nType == CSelItem::selSessionRoot ||
		(pDoc->m_pSelItem->m_nType == CSelItem::selService &&
		((CService*)pDoc->m_pSelItem->m_pObject)->m_nType == CService::typeSM))
		pDoc->UpdateAllViews (this, UPDATE_COUNT);

	*pResult = 0;
}

CSelItem* CServiceManagerView::GetItemData (HTREEITEM hItem)
{
	CTreeCtrl& tree = GetTreeCtrl ();
	return (CSelItem*)tree.GetItemData (hItem);
}

HTREEITEM CServiceManagerView::InsertItem(LPCTSTR lpszText, int nImage1, 
										  int nImage2, HTREEITEM hParent,
										  int nType, CObject * pObject)
{
	CTreeCtrl& tree = GetTreeCtrl ();
	CServiceManagerDoc* pDoc = GetDocument ();

	HTREEITEM hItem = tree.InsertItem (lpszText, nImage1, nImage2, hParent);
	CSelItem* pSelItem = new CSelItem (nType, pObject);
	tree.SetItemData (hItem, (DWORD)pSelItem);
	pDoc->m_listSelItem.AddTail (pSelItem);

	return hItem;
}

/////////////////////////////////////////////////////////////////////////////
// CServiceManagerView printing

void CServiceManagerView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CServiceManagerDoc* pDoc = GetDocument();
	LPDEVMODE m_pDevMode;

	m_pDevMode = pInfo->m_pPD->GetDevMode();
	switch(pDoc->m_wPrintType)
	{
		case PRINT_DEFAULT  : m_pDevMode->dmOrientation = DMORIENT_LANDSCAPE;
							  pInfo->SetMaxPage(GetListPageNum()); break;

		case PRINT_BILL_ALL : m_pDevMode->dmOrientation = DMORIENT_PORTRAIT;
							  pInfo->SetMaxPage(pDoc->m_listClient.GetCount()); break;

		case PRINT_BILL     : m_pDevMode->dmOrientation = DMORIENT_PORTRAIT; break;
		case PRINT_TAX      : m_pDevMode->dmOrientation = DMORIENT_PORTRAIT;
							  pInfo->SetMaxPage(1); break;

		case PRINT_ADDR     : m_pDevMode->dmOrientation = DMORIENT_PORTRAIT;
							  pInfo->SetMaxPage(GetLabelPageNum()); break;
	}
	pDC->ResetDC(m_pDevMode);
	GlobalUnlock( pInfo->m_pPD->m_pd.hDevMode);

	CTreeView::OnBeginPrinting(pDC, pInfo);
}

void CServiceManagerView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CServiceManagerDoc* pDoc = GetDocument();
	CFont font, *oldfont;

	if( pInfo->m_nCurPage == 1 && pDoc->m_wPrintType == PRINT_DEFAULT ) DrawTitle(pDC);

	pDC->SetMapMode(MM_LOENGLISH);

	font.CreateFont( Font_Size, 0, 0, 0, 0, FALSE, FALSE, 0,
		             DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
					 CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					 DEFAULT_PITCH, FONT_NAME);

	oldfont=(CFont*) pDC->SelectObject(&font);

	switch(pDoc->m_wPrintType)
	{
		case PRINT_TAX      : PrintTax(pDC); break;
		case PRINT_ADDR     : PrintLabel( pDC, pInfo); break;
		case PRINT_DEFAULT  : PrintList( pInfo->m_nCurPage, pDC, m_plistData); break;
		case PRINT_BILL_ALL : DrawBillForm(pDC); DrawItem(pDC); break;
	}

	pDC->SelectObject(oldfont);
	font.DeleteObject();

	CTreeView::OnPrint(pDC, pInfo);
}

BOOL CServiceManagerView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	// TODO: call DoPreparePrinting to invoke the Print dialog box
	return DoPreparePrinting(pInfo);
}

CListCtrl& CServiceManagerView::GetList()
{
	CServiceManagerDoc *pDoc = GetDocument();
	POSITION pos = pDoc->GetFirstViewPosition();
	CView *pView;

	pView = pDoc->GetStatusView();

	return ((CStatusView *)pView)->GetListCtrl();
}

BOOL CServiceManagerView::PrintList( UINT nPage, CDC *pDC, CListCtrl *list)
{
	int StartItem, EndItem = list->GetItemCount();
	CServiceManagerDoc* pDoc = GetDocument();
	CString ItemText;
	UINT Left, Top;

	if( nPage == 1 )
	{
		if( EndItem > FirstPage ) EndItem = FirstPage;
		StartItem = 0; Top = -140;
	}
	else
	{
		StartItem = (nPage - 2)*EtcPage + FirstPage; Top = -80;
		if( EndItem > StartItem + FirstPage ) EndItem = StartItem + EtcPage;
	}
	Left = Left_Margine;

	ItemText.Format("Page : %ld", nPage);
	pDC->TextOut( PaperWidth - 2*Left - 10, Top+2*Line_Margine, ItemText);
	pDC->MoveTo( PaperWidth - Left, Top+Line_Margine);
	pDC->LineTo( Left, Top+Line_Margine);

	pDC->MoveTo( PaperWidth - Left, Top+2*Line_Margine + 8);
	pDC->LineTo( Left, Top+2*Line_Margine + 8);

	for( int j=0; j<ColInfo[pDoc->m_nListStatus].nColumnCount; j++)
	{
		pDC->TextOut( Left, Top+2*Line_Margine, ColInfo[pDoc->m_nListStatus].lpColInfo[j].lpstrText);

		for( int i=StartItem; i<EndItem; i++)
		{	
			ItemText = list->GetItemText( i, j);
			pDC->TextOut( Left, Top-(i-StartItem)*Line_Margine, ItemText);
		}
		Left += ColInfo[pDoc->m_nListStatus].lpColInfo[j].ColumnWidth+COL_MARGIN;
	}

	return true;
}

void CServiceManagerView::DrawTitle( CDC *pDC)
{
#ifdef _USE_ENGLISH
	LPTSTR strTitle[] = { "Current User List", "Charge Info List",
		"Deposit History", "Stopped ID List", "Specific use history of game room"};
#else
	LPTSTR strTitle[] = { "현재 이용자 List", "과금정보 List",
		                  "입금내역", "정지된 ID List", "게임방 종량이용내역"};
#endif
	CServiceManagerDoc* pDoc = GetDocument();
	CFont font, *oldfont;

	pDC->SetMapMode(MM_LOENGLISH);
	font.CreateFont( Font_Size+10, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
		             DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
					 CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					 DEFAULT_PITCH, FONT_NAME);

	oldfont=(CFont*) pDC->SelectObject(&font);

	pDC->TextOut( Left_Margine, -Left_Margine+20, strTitle[pDoc->m_nListStatus]);

	pDC->SelectObject(oldfont);
	font.DeleteObject();
}

long CServiceManagerView::GetListPageNum()
{
	long ItemCount, nPage;

	m_plistData = &GetList();
	ItemCount = m_plistData->GetItemCount();

	nPage = (ItemCount - 30)/35 + 1;
	nPage += ((ItemCount - 30)%35 > 0 ? 1 : 0 );

	return nPage;
}

void CServiceManagerView::DrawBillForm( CDC *pDC)
{
	pDC->RoundRect( Left_Margine-10, -(Left_Margine+Line_Margine*3+10),
		            PaperHeight-Left_Margine+10, -(Left_Margine+Line_Margine*9+5), 20, 20);

	pDC->RoundRect( Left_Margine-10, -(Left_Margine+Line_Margine*10),
		            PaperHeight-Left_Margine+10, Line_Margine*2 - PaperWidth, 20, 20);

	pDC->MoveTo( PaperHeight-Left_Margine, Line_Margine*11 - PaperWidth);
	pDC->LineTo( Left_Margine, Line_Margine*11 - PaperWidth);
}

void CServiceManagerView::DrawItem( CDC *pDC)
{
	CServiceManagerDoc* pDoc = GetDocument();
	int row_pos = -(Left_Margine+Line_Margine*4);
	CTime m_timeTo, m_timeFrom, m_timeDead;
	int second_column = PaperHeight/2+15;
	int from_year, from_month;
	CFont font, *oldfont;
	CString strItem;

	m_timeDead = pDoc->m_timeDead;
	m_timeFrom = pDoc->m_timeFrom;
	m_timeTo = pDoc->m_timeTo;

#ifdef _USE_ENGLISH
	strItem.Format( "Name : %s", m_pClient->m_strName);
#else
	strItem.Format( "상      호 : %s", m_pClient->m_strName);
#endif
	pDC->TextOut( Left_Margine, row_pos, strItem);
	row_pos-=Line_Margine;

#ifdef _USE_ENGLISH
	strItem.Format( "President Name: %s", m_pClient->m_strHost);
#else
	strItem.Format( "대표자 성명: %s", m_pClient->m_strHost);
#endif
	pDC->TextOut( Left_Margine, row_pos, strItem);
#ifdef _USE_ENGLISH
	strItem.Format( "Business Registration Number : %s", m_pClient->m_strRegNo);
#else
	strItem.Format( "사업자등록번호 : %s", m_pClient->m_strRegNo);
#endif
	pDC->TextOut( second_column, row_pos, strItem);
	row_pos-=Line_Margine;

#ifdef _USE_ENGLISH
	strItem.Format( "Business Type: %s", m_pClient->m_strType);
#else
	strItem.Format( "업       태: %s", m_pClient->m_strType);
#endif
	pDC->TextOut( Left_Margine, row_pos, strItem);
#ifdef _USE_ENGLISH
	strItem.Format( "Kind: %s", m_pClient->m_strKind);
#else
	strItem.Format( "종           목: %s", m_pClient->m_strKind);
#endif
	pDC->TextOut( second_column, row_pos, strItem);
	row_pos-=Line_Margine;

#ifdef _USE_ENGLISH
	strItem.Format( "Billing period: %4d Year%2d Month%2d Date ~ %4d Year%2d Month%2d Date",
#else
	strItem.Format( "과 금 기 간: %4d년%2d월%2d일 부터 %4d년%2d월%2d일",
#endif
		             m_timeFrom.GetYear(), m_timeFrom.GetMonth(), m_timeFrom.GetDay(),
					 m_timeTo.GetYear(), m_timeTo.GetMonth(), m_timeTo.GetDay());

	pDC->TextOut( Left_Margine, row_pos, strItem);

#ifdef _USE_ENGLISH
	strItem.Format( "Payment period: %4d Year%2d Month%2d Date",
#else
	strItem.Format( "납  입   기  간: %4d년%2d월%2d일",
#endif
		             m_timeDead.GetYear(), m_timeDead.GetMonth(), m_timeDead.GetDay());

	pDC->TextOut( second_column, row_pos, strItem);
	row_pos-=Line_Margine;

#ifdef _USE_ENGLISH
	strItem.Format( "Address: %s", m_pClient->m_strAddress);
#else
	strItem.Format( "주       소: %s", m_pClient->m_strAddress);
#endif
	pDC->TextOut( Left_Margine, row_pos, strItem);
	row_pos -= Line_Margine*3;

	pDC->MoveTo( second_column - 20, Line_Margine*12 - PaperWidth + 10);
	pDC->LineTo( second_column - 20, row_pos + Line_Margine - 10);

#ifdef _USE_ENGLISH
	pDC->TextOut( second_column + 55, row_pos, _T("Billing Number               Use Time"));
	pDC->TextOut(  Left_Margine + 55, row_pos, _T("Billing Number               Use Time"));
#else
	pDC->TextOut( second_column + 55, row_pos, _T("과금번호               사용시간"));
	pDC->TextOut(  Left_Margine + 55, row_pos, _T("과금번호               사용시간"));
#endif
	DrawDetail(pDC);

	pDC->SetMapMode(MM_LOENGLISH);
	font.CreateFont( Font_Size+8, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
		             DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
					 CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					 DEFAULT_PITCH, FONT_NAME);

	oldfont=(CFont*) pDC->SelectObject(&font);

#ifdef _USE_ENGLISH
	pDC->TextOut( Left_Margine, -(Left_Margine+Line_Margine+10), _T("A bill for Droiyan Online"));
#else
	pDC->TextOut( Left_Margine, -(Left_Margine+Line_Margine+10), _T("드로이얀 온라인 사용요금 청구서"));
#endif

	strItem.Format( "%ld", (m_pClient->m_nTotalTime)*11);
	pDoc->MonyForm(&strItem);
	from_year = strItem.GetLength();
#ifdef _USE_ENGLISH
	strItem = _T("Total : ") + strItem + _T(" Won");
#else
	strItem = _T("합        계 : ") + strItem + _T(" 원");
#endif
	pDC->TextOut( Left_Margine+20, Line_Margine*4 - PaperWidth, strItem);

	strItem.Format( "%ld", m_pClient->m_nTotalTime);
	pDoc->MonyForm(&strItem);
	from_month = strItem.GetLength();
#ifdef _USE_ENGLISH
	strItem = _T("Surtax : ") + strItem + _T(" Won");
#else
	strItem = _T("부   가   세 : ") + strItem + _T(" 원");
#endif
	for(; from_month < from_year; from_month++ ) strItem.Insert( 14, ' ');
	pDC->TextOut( Left_Margine+20, Line_Margine*6 - PaperWidth, strItem);

	strItem.Format( "%ld", (m_pClient->m_nTotalTime)*10);
	pDoc->MonyForm(&strItem);
	from_month = strItem.GetLength();
#ifdef _USE_ENGLISH
	strItem = _T("Total amount of use : ") + strItem + _T(" Won");
#else
	strItem = _T("총  사 용 료 : ") + strItem + _T(" 원");
#endif
	for(; from_month < from_year; from_month++ ) strItem.Insert( 14, ' ');
	pDC->TextOut( Left_Margine+20, Line_Margine*8 - PaperWidth, strItem);

	strItem.Format( "%ld", m_pClient->m_nTotalTime);
	pDoc->MonyForm(&strItem);
	from_month = strItem.GetLength();
#ifdef _USE_ENGLISH
	strItem = _T("Total time of use : ") + strItem + _T(" Minutes");
#else
	strItem = _T("총  사용시간 : ") + strItem + _T(" 분");
#endif
	for(; from_month < from_year; from_month++ ) strItem.Insert( 14, ' ');
	pDC->TextOut( Left_Margine+20, Line_Margine*10 - PaperWidth, strItem);

	pDC->SelectObject(oldfont);
	font.DeleteObject();
}

void CServiceManagerView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CServiceManagerDoc* pDoc = GetDocument();
	POSITION Pos;

	if( pDoc->m_wPrintType == PRINT_BILL_ALL )
	{
		Pos = pDoc->m_listClient.FindIndex((pInfo->m_nCurPage)-1);
		m_pClient = (CClient*) pDoc->m_listClient.GetAt(Pos);
	}

	CTreeView::OnPrepareDC(pDC, pInfo);
}

void CServiceManagerView::DrawDetail( CDC* pDC)
{
	long nMonth = (m_pClient->m_wYear)*100 + m_pClient->m_wMonth;
	CClientPaySet clientpayset( &g_db, nMonth, m_pClient->m_wID);
	int row_pos = -(Left_Margine+Line_Margine*12 + 10);
	CServiceManagerDoc* pDoc = GetDocument();
	int second_column = PaperHeight/2+15;
	CString strItem;

	if(!clientpayset.Open ())
	{
		AfxMessageBox (IDS_ERR_DBOPEN);
		return;
	}

	while(!clientpayset.IsEOF())
	{
		pDC->TextOut( Left_Margine + 35, row_pos, clientpayset.m_strSerialCode);
		strItem.Format( "%ld", clientpayset.m_nUseTime);
		pDC->SetTextAlign(TA_RIGHT);

		pDoc->MonyForm(&strItem);
#ifdef _USE_ENGLISH
		strItem += _T(" Minutes");
#else
		strItem += _T(" 분");
#endif
		pDC->TextOut( second_column - 90, row_pos, strItem);

		clientpayset.MoveNext();
		pDC->SetTextAlign(TA_LEFT);

		if(!clientpayset.IsEOF())
		{
			pDC->TextOut( second_column + 35, row_pos, clientpayset.m_strSerialCode);
			strItem.Format( "%ld", clientpayset.m_nUseTime);
			pDC->SetTextAlign(TA_RIGHT);

			pDoc->MonyForm(&strItem);
#ifdef _USE_ENGLISH
			strItem += _T(" Minutes");
#else
			strItem += _T(" 분");
#endif
			pDC->TextOut( PaperHeight - (Left_Margine + 60), row_pos, strItem);

			clientpayset.MoveNext();
			pDC->SetTextAlign(TA_LEFT);
		}
		row_pos -= Line_Margine;
	}
	clientpayset.Close();
}

void CServiceManagerView::PrintTax( CDC* pDC)
{
	int first_column, second_column, row_pos;
	CString dumy;
	RECT rcBound;

	CServiceManagerDoc* pDoc = GetDocument();
	CTime curTime = CTime::GetCurrentTime();

	CClientSet clientset( &g_db, pDoc->m_wID);
	if(!clientset.Open())
	{
		AfxMessageBox (IDS_MSG_BANKSERIALFAIL);
		return;
	}

	if(clientset.IsEOF())
	{
		clientset.Close(); AfxMessageBox (IDS_MSG_BANKSERIALFAIL);
		return;
	}

	for( int i=0; i<2; i++)
	{
		second_column = 538;
		first_column = 246;
		row_pos = -60;

		if(i) row_pos -= 495;

		SetRect( &rcBound, second_column, row_pos, second_column+240, row_pos-32);
		dumy = clientset.m_strRegNo.Left(3);
		DrawNumber( second_column + 50, row_pos-8, dumy, pDC);
		dumy = clientset.m_strRegNo.Mid( 4, 2);
		DrawNumber( second_column + 116, row_pos-8, dumy, pDC);
		dumy = clientset.m_strRegNo.Mid( 7, 5);
		DrawNumber( second_column + 246, row_pos-8, dumy, pDC);

		SetRect( &rcBound, first_column, row_pos, first_column+220, row_pos-32);
		pDC->DrawText( "114-85-14213", &rcBound, DT_SINGLELINE|DT_VCENTER);
		row_pos -= 32;

		SetRect( &rcBound, second_column+145, row_pos-2, second_column+240, row_pos-34);
		pDC->DrawText( clientset.m_strHost, &rcBound, DT_SINGLELINE|DT_VCENTER);
		SetRect( &rcBound, second_column, row_pos-2, second_column+128, row_pos-34);
		pDC->DrawText( clientset.m_strName, &rcBound, DT_SINGLELINE|DT_VCENTER);

		SetRect( &rcBound, first_column+138, row_pos, first_column+220, row_pos-32);
#ifdef _USE_ENGLISH
		pDC->DrawText( "President Name", &rcBound, DT_SINGLELINE|DT_VCENTER);
#else
		pDC->DrawText( "대표 이름", &rcBound, DT_SINGLELINE|DT_VCENTER);
#endif
		SetRect( &rcBound, first_column, row_pos, first_column+120, row_pos-32);
#ifdef _USE_ENGLISH
		pDC->DrawText( "Firm Name", &rcBound, DT_SINGLELINE|DT_VCENTER);
#else
		pDC->DrawText( "회사 이름", &rcBound, DT_SINGLELINE|DT_VCENTER);
#endif
		row_pos -= 34;

		SetRect( &rcBound, second_column, row_pos, second_column+240, row_pos-32);
		pDC->DrawText( clientset.m_strAddress, &rcBound, DT_LEFT|DT_WORDBREAK);
		SetRect( &rcBound, first_column, row_pos, first_column+220, row_pos-32);
#ifdef _USE_ENGLISH
		pDC->DrawText( "Address", &rcBound, DT_LEFT|DT_WORDBREAK);
#else
		pDC->DrawText( "주소", &rcBound, DT_LEFT|DT_WORDBREAK);
#endif
		row_pos -= 32;

		SetRect( &rcBound, second_column+128, row_pos-2, second_column+240, row_pos-34);
		pDC->DrawText( clientset.m_strKind, &rcBound, DT_LEFT|DT_WORDBREAK);
		SetRect( &rcBound, second_column, row_pos-2, second_column+104, row_pos-34);
		pDC->DrawText( clientset.m_strType, &rcBound, DT_LEFT|DT_WORDBREAK);

		SetRect( &rcBound, first_column+120, row_pos, first_column+220, row_pos-32);
#ifdef _USE_ENGLISH
		pDC->DrawText( "Type1", &rcBound, DT_LEFT|DT_WORDBREAK);
#else
		pDC->DrawText( "업종1", &rcBound, DT_LEFT|DT_WORDBREAK);
#endif
		SetRect( &rcBound, first_column, row_pos, first_column+96, row_pos-32);
#ifdef _USE_ENGLISH
		pDC->DrawText( "Type2", &rcBound, DT_LEFT|DT_WORDBREAK);
#else
		pDC->DrawText( "업종2", &rcBound, DT_LEFT|DT_WORDBREAK);
#endif
		row_pos -= 66;

		first_column -= 62;
		dumy.Format( "%d", (pDoc->m_nMoney)*10/11);
		DrawNumber( first_column+282, row_pos-8, dumy, pDC);
		dumy.Format( "%d", pDoc->m_nMoney/11);
		DrawNumber( first_column+446, row_pos-8, dumy, pDC);

		SetRect( &rcBound, first_column-8, row_pos, first_column+96, row_pos-32);
		dumy.Format( "%d", (pDoc->m_nMoney)*10/11);
		dumy.Format( "%4d %2d %2d  %2d", pDoc->m_timeStart.GetYear(), pDoc->m_timeStart.GetMonth(), pDoc->m_timeStart.GetDay(), 11 - dumy.GetLength());
		pDC->DrawText( dumy, &rcBound, DT_SINGLELINE|DT_VCENTER);
		row_pos -= 48;

		SetRect( &rcBound, first_column, row_pos, first_column+42, row_pos-32);
		dumy.Format( "%2d %2d", clientset.m_timeReg.GetMonth(), clientset.m_timeReg.GetDay());
		pDC->DrawText( dumy, &rcBound, DT_SINGLELINE|DT_VCENTER);
		SetRect( &rcBound, first_column+50, row_pos, first_column+184, row_pos-32);
#ifdef _USE_ENGLISH
		pDC->DrawText( "Game room specific system", &rcBound, DT_SINGLELINE|DT_VCENTER);
#else
		pDC->DrawText( "게임방 종량", &rcBound, DT_SINGLELINE|DT_VCENTER);
#endif

		SetRect( &rcBound, first_column+242, row_pos, first_column+285, row_pos-32);
		dumy.Format( "%2d", pDoc->m_nMoney/11);
		pDC->DrawText( dumy, &rcBound, DT_RIGHT|DT_SINGLELINE|DT_VCENTER);

		SetRect( &rcBound, first_column+293, row_pos, first_column+342, row_pos-32);
		pDC->DrawText( "\\10", &rcBound, DT_RIGHT|DT_SINGLELINE|DT_VCENTER);

		SetRect( &rcBound, first_column+350, row_pos, first_column+458, row_pos-32);
		dumy.Format( "%2d", (pDoc->m_nMoney)*10/11);
		pDoc->MonyForm(&dumy);
		dumy = _T("\\") + dumy;
		pDC->DrawText( dumy, &rcBound, DT_RIGHT|DT_SINGLELINE|DT_VCENTER);

		SetRect( &rcBound, first_column+466, row_pos, first_column+551, row_pos-32);
		dumy.Format( "%2d", pDoc->m_nMoney/11);
		pDoc->MonyForm(&dumy);
		dumy = _T("\\") + dumy;
		pDC->DrawText( dumy, &rcBound, DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
		row_pos -= 152;

		SetRect( &rcBound, first_column, row_pos, first_column+84, row_pos-32);
		dumy.Format( "%2d", pDoc->m_nMoney);
		pDoc->MonyForm(&dumy);
		dumy = _T("\\") + dumy;
		pDC->DrawText( dumy, &rcBound, DT_RIGHT|DT_SINGLELINE|DT_VCENTER);

		SetRect( &rcBound, first_column+92, row_pos, first_column+175, row_pos-32);
		dumy.Format( "%2d", pDoc->m_nMoney);
		pDoc->MonyForm(&dumy);
		dumy = _T("\\") + dumy;
		pDC->DrawText( dumy, &rcBound, DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
		pDC->TextOut( first_column+532, row_pos-7, "****");
	}
	clientset.Close();
}

void CServiceManagerView::PrintLabel( CDC *pDC, CPrintInfo* pInfo)
{
/*	CServiceManagerDoc* pDoc = GetDocument();
	int UpperBound = (pInfo->m_nCurPage)*8;
	int Start = (pInfo->m_nCurPage - 1)*8;
	int index, Top = -55;
	CFont font, *oldfont;
	CString strItem;
	POSITION pos;
	RECT rcBound;

	pos = pDoc->m_listClient.FindIndex(Start);
	if( UpperBound > pDoc->m_listClient.GetCount() ) UpperBound = pDoc->m_listClient.GetCount();
	UpperBound -= Start;

	m_pClient = (CClient*) pDoc->m_listClient.GetAt(pos);
	for( index = 0; index < UpperBound; index++ )
	{
		m_pClient = (CClient*) pDoc->m_listClient.GetNext(pos);

		SetRect( &rcBound, 40, Top, 350, Top - 32 );
		pDC->DrawText( m_pClient->m_strZipCode, &rcBound, DT_LEFT|DT_WORDBREAK);

		font.CreateFont( Font_Size+1, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
						 DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
						 CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
						 DEFAULT_PITCH, FONT_NAME);

		oldfont=(CFont*) pDC->SelectObject(&font);

		SetRect( &rcBound, 440, Top, 750, Top - 32 );
		pDC->DrawText( "소 마", &rcBound, DT_LEFT|DT_WORDBREAK);
		Top -= 32;

		pDC->SelectObject(oldfont);
		font.DeleteObject();

		SetRect( &rcBound, 40, Top, 350, Top - 50 );
		pDC->DrawText( m_pClient->m_strAddress, &rcBound, DT_LEFT|DT_WORDBREAK);
		SetRect( &rcBound, 440, Top - 8, 750, Top - 40 );
		pDC->DrawText( "137-060", &rcBound, DT_LEFT|DT_WORDBREAK);
		Top -= 50;

		SetRect( &rcBound, 40, Top, 350, Top - 50 );
		pDC->DrawText( m_pClient->m_strName + " 귀하", &rcBound, DT_RIGHT|DT_WORDBREAK);
		SetRect( &rcBound, 440, Top + 10, 750, Top - 50 );
		pDC->DrawText( "서울시 서초구 방배동 925-4 영신B/D 502호", &rcBound, DT_LEFT|DT_WORDBREAK);
		Top -= 50;
	}*/
}

long CServiceManagerView::GetLabelPageNum()
{
	CServiceManagerDoc* pDoc = GetDocument();
	long PageNum = pDoc->m_listClient.GetCount();

	if( PageNum % 8 ) PageNum = PageNum/8 + 1;
	else PageNum /= 8;

	return PageNum;
}

void CServiceManagerView::DrawNumber( int x_pos, int y_pos, CString& number, CDC *pDC)
{
	int index, length = number.GetLength();

	x_pos -= 16*length + 2;
	for( index=0; index<length; index++, x_pos+=16) pDC->TextOut( x_pos, y_pos, number.Mid( index, 1));
}