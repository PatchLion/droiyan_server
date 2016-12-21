///////////////////////////////////////////////////////////////////////////////
// Pool Base Component Define.
//
#include "stdafx.h"
#include "Poolbase.h"

//-----------------------------------------------------------------------------
// Free Resource List

CFreeList::CFreeList()
 : m_pHead(NULL), m_pTail(NULL), m_Count(0)
{
	InitializeCriticalSection(&m_cs);
//	InitializeCriticalSectionAndSpinCount(&m_cs, SPINX);

	m_pDNodeArray = NULL;
	m_iNodeHead = 0;
	m_iNodeTail = 0;
}

CFreeList::CFreeList(int arraysize)
 : m_pHead(NULL), m_pTail(NULL), m_Count(0)
{
	m_nArraySize = arraysize;

	InitializeCriticalSection(&m_cs);
//	InitializeCriticalSectionAndSpinCount(&m_cs, SPINX);

	m_pDNodeArray = new DNODE* [m_nArraySize];
	memset(m_pDNodeArray, 0, sizeof(DNODE*) * m_nArraySize);

	m_iNodeHead = 0;
	m_iNodeTail = 0;
}

CFreeList::~CFreeList()
{
	RemoveAll();

	delete [] m_pDNodeArray;
	m_nArraySize = 0;
	m_pDNodeArray = NULL;

	DeleteCriticalSection(&m_cs);
}

void CFreeList::AddTail(const RHANDLE* newHandle)
{
	EnterCriticalSection(&m_cs);

	// IKING 2001.1.
	// 기존 리스트에 데이타가 있는지 확인...
	DNODE* p = m_pHead;

	while(p != NULL)
	{
		if ( p->pRH == newHandle )
		{
			LeaveCriticalSection(&m_cs);
			return; 
		}
		p = p->next;
	}
	//

	//DNODE* pNew = new DNODE;
	// 버퍼에 노드 저장하기...
	DNODE* pNew;
	if ( m_iNodeTail != m_iNodeHead )
	{
		pNew = m_pDNodeArray[m_iNodeTail];
		m_pDNodeArray[m_iNodeTail++] = NULL;
		m_iNodeTail %= m_nArraySize;
	}
	else
	{
		pNew = new DNODE;
//		TRACE("NEW NODE MALLOCED...\n");
	}
	//

	if ( pNew == NULL )
	{
		LeaveCriticalSection(&m_cs);
		return;
	}

	pNew->pRH = newHandle;
	pNew->prev = NULL;
	pNew->next = NULL;
	
	if ( m_pTail == NULL )                           // List is empty
		m_pHead = pNew;
	else
	{
		pNew->prev = m_pTail;
		m_pTail->next = pNew;
	}

	m_pTail = pNew;
	m_Count++;

	LeaveCriticalSection(&m_cs);
}

const RHANDLE* CResourceArray::AddNew(int hPos)
{
	long hSession = 0;
	RHANDLE* chd = 0;

	EnterCriticalSection(&m_cs);
	hSession = GetResourceHandle();
	if(hSession != 0)
	{
		RHANDLEHEADER* pSH = new RHANDLEHEADER;
		chd = new RHANDLE;
		chd->handle = hSession;
		chd->pos = hPos; 

		pSH->pRH = chd;
		pSH->bFree = true;
		pSH->dwTime = 0;

	}
	else
	{
		// Event Log call
		#ifdef _DEBUG
		OutputDebugString(__TEXT("Handle could not be allocated\n"));
		#endif
	}
	LeaveCriticalSection( &m_cs );

	return chd;
}

void CFreeList::RemoveAll()
{
	DNODE* pNext = 0;

	EnterCriticalSection(&m_cs);

	DNODE* p = m_pHead;
	while(p != NULL)
	{
		pNext = p->next;
		delete p;
		p = pNext;
	}
	m_pHead = m_pTail = NULL;
	m_Count = 0;
	
	LeaveCriticalSection(&m_cs);
}

const RHANDLE* CFreeList::Pop()
{
	const RHANDLE* rh = 0;
	EnterCriticalSection(&m_cs);

	DNODE* p = m_pHead;
	if ( p != NULL )
	{
		// Obtain RHANDLE
		rh = p->pRH;

		if(p->next)
		{
			p->next->prev = NULL;
			m_pHead = p->next;
		}
		else
			m_pHead = m_pTail = NULL;

		//delete p;
		// 버퍼에 노드 저장하기...
		p->next = NULL;
		p->prev = NULL;
		p->pRH = NULL;

		m_pDNodeArray[m_iNodeHead] = p;
		if ( m_iNodeHead >= m_nArraySize - 1 )
			m_iNodeHead = 0;
		else
			m_iNodeHead++;

		//m_iNodeHead %= m_nArraySize;
		//

		m_Count--;
	}

	LeaveCriticalSection( &m_cs );

	return rh;
}

DWORD CFreeList::GetCount()
{
	DWORD dwCount;
	dwCount = m_Count;
	return dwCount;
}


//---------------------------------------------------------------------------
// CResourceArray Class

CResourceArray::CResourceArray(long dwSize) : m_size(dwSize), m_count(0)
{
	InitializeCriticalSection(&m_cs);
	//InitializeCriticalSectionAndSpinCount(&m_cs, SPINX);

	m_pHandles = new RHANDLEHEADER* [dwSize];
	memset(m_pHandles, 0, sizeof(RHANDLEHEADER*) * dwSize);
}

CResourceArray::~CResourceArray()
{
	RemoveAll();                                  // Just in case
	delete [] m_pHandles;
	m_size = 0;
	m_pHandles = NULL;

	DeleteCriticalSection(&m_cs);
}

const RHANDLE* CResourceArray::Add()
{
	long hSession = 0;
	RHANDLE* chd = 0;

	EnterCriticalSection(&m_cs);
	if( m_count >= 0 && m_count < m_size)
	{
		hSession = GetResourceHandle();
		if(hSession != 0)
		{
			RHANDLEHEADER* pSH = new RHANDLEHEADER;
			chd = new RHANDLE;
			chd->handle = hSession;
			chd->pos = m_count; 

			pSH->pRH = chd;
			pSH->bFree = true;
			pSH->dwTime = 0;

			m_pHandles[m_count] = pSH;
			m_count++;
		}
		else
		{
			// Event Log call
			#ifdef _DEBUG
			OutputDebugString(__TEXT("Handle could not be allocated\n"));
			#endif
		}
	}

	LeaveCriticalSection( &m_cs );

	return chd;
}

void CResourceArray::RemoveAll()
{
	RHANDLEHEADER* pTemp = 0;

	EnterCriticalSection(&m_cs);

	for(int i = 0 ; i < m_count ; i++)
	{
		pTemp = m_pHandles[i];
		if(pTemp)
		{
			const RHANDLE* pRHTemp = pTemp->pRH;
			if(pRHTemp)
			{
				ReleaseResourceHandle(pRHTemp->handle);
				delete (RHANDLE*)pRHTemp;
			}
			delete pTemp;
		}
		m_pHandles[i] = NULL;
	}
	m_count = 0;

	LeaveCriticalSection(&m_cs);
}

long CResourceArray::GetResourceHandle()
{
	return -1;
}

RHANDLE* CResourceArray::GetHandle(const long position)
{
	RHANDLE *rHandle;

	if ( position >= 0 && position < m_size )
		rHandle = (RHANDLE *)m_pHandles[position]->pRH;
	else 
		return NULL;

	return rHandle;
}

long CResourceArray::GetDataValue(const long position)
{
	long r_handle;

	if ( position >= 0 && position < m_size )
		r_handle = m_pHandles[position]->pRH->handle;
	else
		return NULL;

	return r_handle;
}

void CResourceArray::ReleaseResourceHandle(long hResHandle)
{
#ifdef _DEBUG
	CHAR sz[100] = {0};
	wsprintf(sz, "Handle Dellocated-------------->%Handle: %d\n", hResHandle);
	OutputDebugString(sz);
#endif

}

void CResourceArray::SetBusy(const long position)
{
	if ( position >= 0 && position < m_size )
	{
		m_pHandles[position]->bFree = false;
		m_pHandles[position]->dwTime = GetTickCount();
	}
}

void CResourceArray::SetFree(const long position)
{
	if ( position >= 0 && position < m_size )
	{
		m_pHandles[position]->bFree = true;
		m_pHandles[position]->dwTime = 0;
	}
}

int CResourceArray::TimeOutSetFree(const long position)
{
	if ( position >= 0 && position < m_size )
	{
		m_pHandles[position]->bFree = true;
		m_pHandles[position]->dwTime = 0;
	}

	return 1;
}

bool CResourceArray::IsFree(const long position)
{
   if (m_pHandles[position] != NULL)
	if ( position >= 0 && position < m_size )
		return m_pHandles[position]->bFree;

	return FALSE;
}

long CResourceArray::GetCount()
{
	long lRet;
	lRet = m_count;
	return lRet;
}

void CResourceArray::SetTimeStamp(const long position, long nTimeStamp)
{
	if ( nTimeStamp == 0 )
		nTimeStamp = GetTickCount();

	if ( position >= 0 && position < m_size )
		m_pHandles[position]->dwTime = nTimeStamp;
}

//-----------------------------------------------------------------------------
// CPoolBase Manager Class define

CPoolBaseManager::CPoolBaseManager() : m_dwNumCurrentResources(0), m_bStartAllocator(false)
{
	InitializeCriticalSection(&m_cs);
	//InitializeCriticalSectionAndSpinCount(&m_cs, SPINX);

	m_pResources = NULL;
	m_pFreeList = NULL;
}

CPoolBaseManager::~CPoolBaseManager()
{
	DeallocateResources();

	if ( m_pResources )
	{
		delete m_pResources;
		m_pResources = NULL;
	}

	if ( m_pFreeList )
	{
		delete m_pFreeList;
		m_pFreeList = NULL;
	}

	DeleteCriticalSection(&m_cs);
}

DWORD WINAPI AllocateMoreResourcesThread(LPVOID lpParameter)
{
	CPoolBaseManager *pPBM = (CPoolBaseManager *)lpParameter;

	while ( WaitForSingleObject( pPBM->m_hStopEvent, pPBM->m_dwAllocationPoll ) == WAIT_TIMEOUT )
	{
		if ( pPBM->FreeResourcesLeft() <= pPBM->m_dwMinPoolSize && pPBM->m_bStartAllocator)
		{
			pPBM->AllocateResources(pPBM->m_dwResourceAllocSize);
		}
	}

	return 0;
}

DWORD WINAPI RefreshDeadResourcesThread(LPVOID lpParameter)
{
	CPoolBaseManager *pPBM = (CPoolBaseManager *)lpParameter;

	while ( WaitForSingleObject(pPBM->m_hStopEvent, pPBM->m_dwDeadResourcePoll) == WAIT_TIMEOUT )
	{
		pPBM->ReleaseDeadResources();
	}

	return 0;
}

int CPoolBaseManager::AddResource(int hPos)
{
	const RHANDLE* pRH = 0;

	EnterCriticalSection(&m_cs);

	pRH = m_pResources->AddNew(hPos);
	if ( pRH )
	{
		m_pFreeList->AddTail(pRH);
	}
	else
	{
		LeaveCriticalSection(&m_cs);
		return 0;
	}

	LeaveCriticalSection(&m_cs);

	return 1;
}

DWORD CPoolBaseManager::AllocateResources(DWORD dwNumAdd)
{
	DWORD count = 0;
	const RHANDLE* pRH = 0;
	DWORD newRes = 0;

	DWORD dwNumRes = GetNumResources();

	if(dwNumAdd + dwNumRes > m_dwMaxResources)
		newRes = m_dwMaxResources - dwNumRes;
	else
		newRes = dwNumAdd;

	// Connect the sessions
	for(DWORD i = 0 ; i < newRes ; i++)
	{
		pRH = m_pResources->Add();
		if ( pRH )
		{
			m_pFreeList->AddTail(pRH);
			count++;
		}
	}

	InterlockedExchangeAdd((long*)&m_dwNumCurrentResources, count);

#ifdef _DEBUG
	if ( newRes > 0 )
	{
	CHAR sz[100] = {0};
	wsprintf(sz, "Allocations were increased----->%lu\n", m_dwNumCurrentResources);
	OutputDebugString(sz);
	}
#endif

	// Allow the allocator thread to start, if it hasn't before
	if(!m_bStartAllocator)
		InterlockedExchange((long*)&m_bStartAllocator, true);

	// Return
	return count;
}

void CPoolBaseManager::DeallocateResources()
{
	EnterCriticalSection(&m_cs);

	// Stop the allocator/deadresource threads
	SetStop();

	m_dwNumCurrentResources = 0;
	if ( m_pResources )
		m_pResources->RemoveAll();
	
	if ( m_pFreeList )
		m_pFreeList->RemoveAll();

	m_hRefreshThread = NULL;

	LeaveCriticalSection(&m_cs);
}

// Will be called on a schedule by another thread
void CPoolBaseManager::ReleaseDeadResources()
{
	DWORD now = GetTickCount();
	RHANDLEHEADER* pTemp = 0;
	DWORD stamp = 0;

	DWORD count = m_pResources->GetCount();
	if ( count >= m_dwMaxResources )
		count = m_dwMaxResources;

	EnterCriticalSection(&m_cs);

	for(DWORD i = 0 ; i < count ; i++)
	{
		pTemp = m_pResources->m_pHandles[i];
		if(pTemp)
		{
			if(m_pResources->IsFree(i) == false)
			{
				stamp = pTemp->dwTime;
				if(now - stamp > m_dwHandleLifeTime)
				{
					if(pTemp->pRH)
					{
						//m_pResources->SetFree(i);
						if ( m_pResources->TimeOutSetFree(i) == 1 )
							m_pFreeList->AddTail(pTemp->pRH);
					}
				}
			}
		}
	}

	LeaveCriticalSection(&m_cs);
}

void CPoolBaseManager::Init(DWORD dwMaxResources,      DWORD dwStartResources,
							DWORD dwWaitForHandleTime, DWORD dwHandleLifeTime,
							DWORD dwAllocationPoll,    DWORD dwMinPoolSize,
							DWORD dwResourceAllocSize, DWORD dwDeadResourcePoll,
							CResourceArray *pRA)
{
	// Event to signal workers to stop
	m_hStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_dwStartResources = dwStartResources;
	m_dwMaxResources = dwMaxResources;
	m_dwWaitForHandleTime = dwWaitForHandleTime;
	m_dwHandleLifeTime = dwHandleLifeTime;
	m_dwAllocationPoll = dwAllocationPoll;
	m_dwMinPoolSize = dwMinPoolSize;
	m_dwResourceAllocSize = dwResourceAllocSize;
	m_dwDeadResourcePoll = dwDeadResourcePoll;

	m_nResourceWaitingCount = 0;

	m_pResources = pRA;
	m_pFreeList = new CFreeList(dwMaxResources);

	//DWORD dwAid;
	//DWORD dwPid;

	//m_hAllocThread = CreateThread(0, 0, &AllocateMoreResourcesThread, this, 0, &dwAid);
	//m_hRefreshThread = CreateThread(0, 0, &RefreshDeadResourcesThread, this, 0, &dwPid);

	// START RESOURCE SETTING...
	AllocateResources(m_dwStartResources);
}

DWORD CPoolBaseManager::GetFreeResource(const RHANDLE** poutHandle)
{
	const RHANDLE* pHandle = 0;

	EnterCriticalSection(&m_cs);

	pHandle = m_pFreeList->Pop();
	if ( pHandle )
	{
		m_pResources->SetBusy(pHandle->pos);
		*poutHandle = pHandle;

		LeaveCriticalSection(&m_cs);
		return 0;
	}
	
	*poutHandle = NULL;

	LeaveCriticalSection(&m_cs);

	return E_NORESOURCESAVAILABLE;
}

void CPoolBaseManager::ReleaseResource(const RHANDLE* handle)
{
	if ( handle == NULL ) return;

	EnterCriticalSection(&m_cs);

	if ( m_pResources->IsFree(handle->pos) == false )
	{
		m_pResources->SetFree(handle->pos);
		m_pFreeList->AddTail(handle);
	}
	else
	{
		m_pFreeList->AddTail(handle);

		TRACE("ADJUST ABNORMAL RELEASE RESOURCE[%d]...\n", handle->pos );
	}

	LeaveCriticalSection(&m_cs);

}

DWORD CPoolBaseManager::FreeResourcesLeft()
{
	DWORD dwCount;
	dwCount = m_pFreeList->GetCount();
	return dwCount; 
}

DWORD CPoolBaseManager::GetNumResources()
{
	DWORD dwCount;
	dwCount = m_dwNumCurrentResources;
	return dwCount;
}

void CPoolBaseManager::SetStop()
{
	SetEvent(m_hStopEvent);
	//WaitForSingleObject(m_hAllocThread, INFINITE);
	//WaitForSingleObject(m_hRefreshThread, INFINITE);
};
