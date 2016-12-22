// ConfigSheet.cpp : implementation file
//

#include "stdafx.h"
#include "ServiceManager.h"
#include "ConfigSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigSheet

IMPLEMENT_DYNAMIC(CConfigSheet, CPropertySheet)

CConfigSheet::CConfigSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CConfigSheet::CConfigSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CConfigSheet::~CConfigSheet()
{
}


BEGIN_MESSAGE_MAP(CConfigSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CConfigSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigSheet message handlers
