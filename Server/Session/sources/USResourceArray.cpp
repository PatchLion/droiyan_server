///////////////////////////////////////////////////////////////////////////////
// Socket Resource Array C++ Files
#include "StdAfx.h"
#include "Poolbase.h"
#include "USResourceArray.h"
#include "Session.h"
#include "SessionCom.h"
#include "Mcommon.h"


extern CSessionCom	*g_pCom;


CUserServerResourceArray::CUserServerResourceArray(long dwSize)
	: CResourceArray(dwSize)
{
}

CUserServerResourceArray::~CUserServerResourceArray()
{
}

long CUserServerResourceArray::GetResourceHandle()
{
	long handle;

	CSessDesc *pSessDes = new CSessDesc;
	pSessDes->m_Type = SOCKET_FOR_USERSERVER;
	pSessDes->m_pCom = g_pCom;
	handle = (long)pSessDes;
		
	return handle;
}

void CUserServerResourceArray::ReleaseResourceHandle(long hResHandle)
{
	if ( hResHandle != 0 )
	{
		CSessDesc *pSocket = (CSessDesc *)hResHandle;
		delete pSocket;
		pSocket = NULL;
	}
}

int CUserServerResourceArray::GetUsedResourceCount()
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

void CUserServerResourceArray::SetFree(const long position)
{
	CBSocket *pSocket = (CBSocket *)GetDataValue( position );
	if ( pSocket && pSocket->m_SockFlag == 1 )
		pSocket->m_SockFlag = 0;

	CResourceArray::TimeOutSetFree(position);
}

int CUserServerResourceArray::TimeOutSetFree(const long position)
{
	CSessDesc *pSessDesc = (CSessDesc *)GetDataValue( position );
	if ( pSessDesc && pSessDesc->m_SockFlag == 1 )
	{
		if ( pSessDesc )
			pSessDesc->SockCloseProcess(ERROR_RECVTIMEOUT);

		return 0;
	}

	//CResourceArray::TimeOutSetFree(position);
	return 1;
}
