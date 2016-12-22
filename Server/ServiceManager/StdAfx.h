// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__E17147FA_20EA_11D2_A546_00A0248552AD__INCLUDED_)
#define AFX_STDAFX_H__E17147FA_20EA_11D2_A546_00A0248552AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#define _WIN32_WINNT 0x0502
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcview.h>
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions
#include <afxdb.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#if !defined ___COLUMNINFO
#define ___COLUMNINFO

struct COLUMNINFO
{
	BYTE ColumnWidth;
	LPTSTR lpstrText;
};

typedef COLUMNINFO* LPCOLUMNINFO;

#endif // !defined ___COLUMNINFO


#if !defined ___COLINFO
#define ___COLINFO

struct COLINFO
{
	LPCOLUMNINFO lpColInfo;
	BYTE nColumnCount;
};

typedef COLINFO* LPCOLINFO;

#endif // !defined ___COLINFO

#endif // !defined(AFX_STDAFX_H__E17147FA_20EA_11D2_A546_00A0248552AD__INCLUDED_)
