// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__2D74873E_1BDB_470C_8FD4_4AD406DA5693__INCLUDED_)
#define AFX_STDAFX_H__2D74873E_1BDB_470C_8FD4_4AD406DA5693__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define _WIN32_WINNT 0x0502
#include "MemDefine.h"

//#define FD_SETSIZE			MAX_USER

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <winsock2.h>		// Winsock 2
#include <mswsock.h>		// Winsock 2

#include <afxdb.h>			// ODBC
#include <afxtempl.h>		// collection

//#define _GETVARSTRING_DEBUG

#include "Global.h"
#include "define.h"

#define SErr(c, f)		g_ErrorLog.ShowError((c), f)
#define WErr(c, f)		g_ErrorLog.WriteError((c), f)
#define WErr2(c, f, e)	g_ErrorLog.WriteError2((c), f, e)

#ifdef _DEBUG
#define BREAKPOINT() __asm { int 3 }
#else
#define BREAKPOINT() ;
#endif
//#define BREAKPOINT() __asm { int 3 }

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__2D74873E_1BDB_470C_8FD4_4AD406DA5693__INCLUDED_)
