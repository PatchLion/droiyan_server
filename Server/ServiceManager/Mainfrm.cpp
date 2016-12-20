// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ServiceManager.h"

#include "MainFrm.h"
#include "ServiceManagerDoc.h"
#include "ServiceManagerView.h"
#include "StatusView.h"
#include "CountView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND_EX(CG_ID_VIEW_VIEWBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_VIEWBAR, OnUpdateControlBarMenu)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	ID_SEPARATOR,
	ID_SEPARATOR
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	UINT nID, nStyle;
	int cxWidth;
	m_wndStatusBar.GetPaneInfo (4, nID, nStyle, cxWidth);
	cxWidth = 80;
	m_wndStatusBar.SetPaneInfo (4, nID, nStyle, cxWidth);

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
/*
	// TODO: Add a menu item that will toggle the visibility of the
	// dialog bar named "ViewBar":
	//   1. In ResourceView, open the menu resource that is used by
	//      the CMainFrame class
	//   2. Select the View submenu
	//   3. Double-click on the blank item at the bottom of the submenu
	//   4. Assign the new item an ID: CG_ID_VIEW_VIEWBAR
	//   5. Assign the item a Caption: ViewBar

	// TODO: Change the value of CG_ID_VIEW_VIEWBAR to an appropriate value:
	//   1. Open the file resource.h
	// CG: The following block was inserted by the 'Dialog Bar' component
	{
		// Initialize dialog bar m_wndViewBar
		if (!m_wndViewBar.Create(this, CG_IDD_VIEWBAR,
			CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
			CG_ID_VIEW_VIEWBAR))
		{
			TRACE0("Failed to create dialog bar m_wndViewBar\n");
			return -1;		// fail to create
		}

		m_wndViewBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndViewBar);

	}
*/
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to create split bar ");
		return FALSE;    // failed to create
	}

	if (!m_wndSplitter.CreateView (0, 0, pContext->m_pNewViewClass, 
		CSize (200, 0), pContext))
	{
		TRACE0("Failed to create config view");
		return FALSE;    // failed to create
	}

	if (!m_wndSplitter1.CreateStatic (&m_wndSplitter, 2, 1,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		m_wndSplitter.IdFromRowCol (0, 1)))
	{
		TRACE0("Failed to create split bar1 ");
		return FALSE;    // failed to create
	}

	pContext->m_pNewViewClass = RUNTIME_CLASS (CStatusView);
	if (!m_wndSplitter1.CreateView (0, 0, pContext->m_pNewViewClass, 
		CSize (0, 400), pContext))
	{
		TRACE0("Failed to create status view");
		return FALSE;    // failed to create
	}

	pContext->m_pNewViewClass = RUNTIME_CLASS (CCountView);
	if (!m_wndSplitter1.CreateView (1, 0, pContext->m_pNewViewClass, 
		CSize (0, 0), pContext))
	{
		TRACE0("Failed to create count view");
		return FALSE;    // failed to create
	}

	return TRUE;
}
