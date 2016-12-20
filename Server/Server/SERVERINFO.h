///////////////////////////////////////////////////////////////////
//	ServerDlg.h : header file for the CServerDlg class
//  Copyright (C) 2000,  Jin-Soo Jeon
//
//	If this code works, it was written by JinSoo Jeon.
//	If not, I don't know who wrote it.
//

#if !defined(AFX_SERVERINFO_H__7A7FB74E_858C_4B3F_86FC_850CBC924BE2__INCLUDED_)
#define AFX_SERVERINFO_H__7A7FB74E_858C_4B3F_86FC_850CBC924BE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef CTypedPtrArray <CPtrArray, int*> ZoneNumArray;

typedef struct _ZONEINFO
{
	int		iSid;
	int		iZone;
	int		iPkMode;
	int		iPotalX;
	int		iPotalY;
	int		iPotalX1;
	int		iPotalY1;
	int		iPotalZone;
} ZONEINFO;

typedef struct _TOWNPOTAL
{
	int		iPotalZone;
	POINT	iPotal[3];

} TOWNPOTAL;

class SERVERINFO  
{
public:
	SERVERINFO();
	virtual ~SERVERINFO();

	int				m_sid;
	int				m_sDBIndex;
	CString			m_szAddr;
	int				m_nPort;
	CString			m_strGTime;
	ZoneNumArray	m_zone;
};

#endif // !defined(AFX_SERVERINFO_H__7A7FB74E_858C_4B3F_86FC_850CBC924BE2__INCLUDED_)
