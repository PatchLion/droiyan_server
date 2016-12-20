// CP_IP_MASKTable.h: interface for the CCP_IP_MASKTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CP_IP_MASKTABLE_H__ED07F70E_F6A7_42C0_83BD_9EE56AA8A6E1__INCLUDED_)
#define AFX_CP_IP_MASKTABLE_H__ED07F70E_F6A7_42C0_83BD_9EE56AA8A6E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Define.h"

class CCP_IP_MASKTable  
{
public:
	CCP_IP_MASKTable();
	virtual ~CCP_IP_MASKTable();

public:
//	long	m_num;
	TCHAR	m_strClientID[30];
	double	m_startnum;
	double	m_endnum;

	TCHAR m_StartIP[16];
	TCHAR m_EndIP[16];
	int		m_iType;	
};

#endif // !defined(AFX_CP_IP_MASKTABLE_H__ED07F70E_F6A7_42C0_83BD_9EE56AA8A6E1__INCLUDED_)
