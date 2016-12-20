///////////////////////////////////////////////////////////////////////////////
// Socket Resource Array C++ Files
#include "StdAfx.h"
#include "../LibsIncs/Poolbase.h"
#include "SResourceArray.h"
#include "Session.h"
#include "Mcommon.h"

//extern CServiceMain *pMainSvc;

CSockResourceArray::CSockResourceArray(long dwSize)
	: CResourceArray(dwSize)
{

}

CSockResourceArray::~CSockResourceArray()
{

}

long CSockResourceArray::GetResourceHandle()
{
	long handle;

	CSessDesc *pSocket = new CSessDesc;
	pSocket->m_Type = SOCKET_FOR_SERVER;
	handle = (long)pSocket;
		
	return handle;
}

void CSockResourceArray::ReleaseResourceHandle(long hResHandle)
{
	if ( hResHandle != 0 )
	{
		CSessDesc *pSocket = (CSessDesc *)hResHandle;
		delete pSocket;
		pSocket = NULL;
	}
}

int CSockResourceArray::GetUsedResourceCount()
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

void CSockResourceArray::SetFree(const long position)
{
	CBSocket *pSocket = (CBSocket *)GetDataValue( position );
	if ( pSocket && pSocket->m_SockFlag == 1 )
		pSocket->m_SockFlag = 0;

	CResourceArray::SetFree(position);
}

int CSockResourceArray::TimeOutSetFree(const long position)
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
