///////////////////////////////////////////////////////////////////////////////
// Socket Resource Array C++ Files
#include "StdAfx.h"
#include "Poolbase.h"
#include "SResourceArray.h"
#include "Ssocket.h"
#include "resource.h"
#include "ServerDlg.h"

extern CServerDlg *g_pMainDlg;

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

	CSSocket *pSocket = new CSSocket;
	pSocket->SetIOPendingEnableFlag(TRUE);
	handle = (long)pSocket;
		
	return handle;
}

void CSockResourceArray::ReleaseResourceHandle(long hResHandle)
{
	if ( hResHandle != 0 )
	{
		CSSocket *pSocket = (CSSocket *)hResHandle;
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
	CBSocket *pSocket = (CBSocket *)GetDataValue( position );
	if ( pSocket && pSocket->m_SockFlag == 1 )
	{
		if ( g_pMainDlg )
			g_pMainDlg->ServerCloseMessage( pSocket->m_Sid, (long)pSocket );

		return 0;
	}

	return 1;
}
