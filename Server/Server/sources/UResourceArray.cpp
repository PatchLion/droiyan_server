///////////////////////////////////////////////////////////////////////////////
// Socket Resource Array C++ Files
#include "StdAfx.h"
#include "User.h"
#include "Poolbase.h"
#include "UResourceArray.h"
#include "MCommon.h"
#include "resource.h"
#include "ServerDlg.h"
#include "Packet.h"

extern CServerDlg *g_pMainDlg;


CUserResourceArray::CUserResourceArray(long dwSize)
	: CResourceArray(dwSize)
{
}

CUserResourceArray::~CUserResourceArray()
{
}

long CUserResourceArray::GetResourceHandle()
{
	long handle;

	USER *pUser = new USER;
	if ( pUser == NULL )
	{
		TRACE("CUserResourceArray::GetResourceHandle...\n");
		return 0;
	}
	handle = (long)pUser;
		
	return handle;
}

void CUserResourceArray::ReleaseResourceHandle(long hResHandle)
{
	if ( hResHandle != 0 )
	{

		USER *pUser = (USER *)hResHandle;
		delete pUser;
		pUser = NULL;

		TRACE("CUserResourceArray::ReleaseResourceHandle...\n");
	}
}

int CUserResourceArray::GetUsedResourceCount()
{
	int c = 0, trc;

	RHANDLEHEADER* pTemp = 0;

	trc = GetCount();
	for(int i = 0 ; i < trc ; i++)
	{
		if ( IsFree(i) == false )
			c++;
	}

	return c;
}

void CUserResourceArray::SetFree(const long position)
{
	USER *pUser = (USER *)GetDataValue( position );
	if ( pUser )
		pUser->m_UserFlag = 0;

	CResourceArray::SetFree(position);
}

int CUserResourceArray::TimeOutSetFree(const long position)
{
	USER *pUser = (USER *)GetDataValue( position );
	if ( pUser )
	{
		pUser->SoftClose();
		return 0;
	}

	return 1;
}
