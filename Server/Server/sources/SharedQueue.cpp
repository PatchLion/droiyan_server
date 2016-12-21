/////////////////////////////////////////////////////////////////////////////////////
// SharedQueue.cpp
// CSharedQueue class source
// 2002/11/13 by zinee
//
#include "stdafx.h"
#include "SharedQueue.h"

CSharedQueue::CSharedQueue()
{
}

CSharedQueue::~CSharedQueue()
{
}

BOOL CSharedQueue::Create( LPCTSTR pSharedName, int nQueueCount )
{
	int nMemorySize;

	// (nFront+nRear+nQueueCount)+QueueSize
	nMemorySize = sizeof(int)*3+sizeof(QUEUE)*nQueueCount;

	if( m_SharedMemory.Create( nMemorySize, pSharedName ) == FALSE )
		return FALSE;

	m_hMutex = CreateMutex( NULL, FALSE, "Mutex_SharedQueue" );

	m_pQueue = (QUEUE*)((char*)m_SharedMemory.m_lpData+sizeof(int)*3);

	m_nQueueCount = nQueueCount;

	m_pnFront	= (int*)((char*)m_SharedMemory.m_lpData);
	m_pnRear	= (int*)((char*)m_SharedMemory.m_lpData+sizeof(int));

	*m_pnFront	= 0;
	*m_pnRear	= 0;
	*((int*)((char*)m_SharedMemory.m_lpData+sizeof(int)*2)) = nQueueCount;

	return TRUE;
}

BOOL CSharedQueue::Open( LPCTSTR pSharedName )
{
	int nMemorySize, nQueueCount;

	nMemorySize = sizeof(int)*3; //+sizeof(QUEUE)*nQueueCount;

	// Open SharedMemory (3*int)size, and get Queue Size of SharedMemory 
	if( m_SharedMemory.Open( pSharedName, nMemorySize ) == FALSE )
		return FALSE;

	nQueueCount = *((int*)((char*)m_SharedMemory.m_lpData+sizeof(int)*2));
	m_SharedMemory.Delete();

	// (nFront+nRear+nQueueCount)+QueueSize
	nMemorySize = sizeof(int)*3+sizeof(QUEUE)*nQueueCount;

	if( m_SharedMemory.Open( pSharedName, nMemorySize ) == FALSE )
		return FALSE;

	m_hMutex = CreateMutex( NULL, FALSE, "Mutex_SharedQueue" );

	m_pQueue = (QUEUE*)((char*)m_SharedMemory.m_lpData+sizeof(int)*3);

	m_nQueueCount = nQueueCount;

	m_pnFront	= (int*)((char*)m_SharedMemory.m_lpData);
	m_pnRear	= (int*)((char*)m_SharedMemory.m_lpData+sizeof(int));

	return TRUE;

}

BOOL CSharedQueue::Release()
{
	m_pQueue		= NULL;
	m_nQueueCount	= 0;
	m_pnFront		= NULL;
	m_pnRear		= NULL;

	m_SharedMemory.Delete();
	CloseHandle( m_hMutex );
	return TRUE;
}


BOOL CSharedQueue::GetQueue( QUEUE* pQueue )
{
	DWORD	dwWaitResult = WaitForSingleObject( m_hMutex, INFINITE );

	if( !IsExistData() ) 
	{
		ReleaseMutex( m_hMutex );
		return FALSE;
	}

	memcpy( pQueue, &m_pQueue[*m_pnFront], sizeof(QUEUE) );

	IncFront();

	ReleaseMutex( m_hMutex );

	return TRUE;
}

BOOL CSharedQueue::PutQueue( QUEUE* pQueue )
{
	DWORD	dwWaitResult = WaitForSingleObject( m_hMutex, INFINITE );

	if( IsFullData() ) 
	{
		ReleaseMutex( m_hMutex );
		return FALSE;
	}

	memcpy( &m_pQueue[*m_pnRear], pQueue, sizeof(QUEUE) );

	IncRear();

	ReleaseMutex( m_hMutex );

	return TRUE;
}

void CSharedQueue::IncQueuePos( int* pnQueuePos )
{
	if( *pnQueuePos == m_nQueueCount-1 ) 
		(*pnQueuePos) = 0;
	else (*pnQueuePos)++;
}

BOOL CSharedQueue::IncFront( void )
{
	if( *m_pnFront == *m_pnRear )
		return FALSE;

	IncQueuePos( m_pnFront );
	return TRUE;
}

BOOL CSharedQueue::IncRear( void )
{
	int nRear;

	nRear = *m_pnRear;

	IncQueuePos( &nRear );

	if( nRear == *m_pnFront )
		return FALSE;

	*m_pnRear = nRear;
	return TRUE;
}

BOOL CSharedQueue::IsExistData(void)
{
	if( *m_pnFront == *m_pnRear )
		return FALSE;

	return TRUE;
}

BOOL CSharedQueue::IsFullData(void)
{
	int nRear;

	nRear = *m_pnRear;

	IncQueuePos( &nRear );

	if( nRear == *m_pnFront )
		return TRUE;

	return FALSE;
}
