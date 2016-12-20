// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__EF04572D_FE5B_4C30_AFF3_B2C7B1AE7AB8__INCLUDED_)
#define AFX_STDAFX_H__EF04572D_FE5B_4C30_AFF3_B2C7B1AE7AB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <Winsock2.h>
#include <afxinet.h>

#define WM_CLIENT_READCOLOSE WM_USER + 101

typedef struct ZyMsg
{
	char msg[100];
	int i;
}Msg;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__EF04572D_FE5B_4C30_AFF3_B2C7B1AE7AB8__INCLUDED_)
