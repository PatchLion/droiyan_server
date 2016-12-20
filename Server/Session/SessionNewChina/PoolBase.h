///////////////////////////////////////////////////////////////////////////////
// Poolbase.h
//
#ifndef __POOLBASE_H
#define __POOLBASE_H

#define E_NORESOURCESAVAILABLE 0x80002838
const int SPINX = 5000;						// Spin count for critical sections

struct RHANDLE
{
   long handle;
   long pos;
};

struct RHANDLEHEADER
{
   const RHANDLE* pRH;
   bool bFree;
   DWORD dwTime;
};

struct DNODE
{
	const RHANDLE* pRH;
	DNODE* prev;
	DNODE* next;
};

class CPoolBaseManager;
struct POOL_THREAD
{
	int id;
	CPoolBaseManager *pBM;
};

// List class is linked list of RHANDLEs
class CFreeList
{
private:
	int m_nArraySize;
	DNODE **m_pDNodeArray;
	int m_iNodeHead;
	int m_iNodeTail;

public:
	CFreeList();
	CFreeList(int size);
	virtual ~CFreeList();

	const RHANDLE* Pop();
	void AddTail(const RHANDLE* newHandle);
	void RemoveAll();
	
	DWORD GetCount();

private:
	DWORD m_Count;
	DNODE* m_pHead;
	DNODE* m_pTail;
	CRITICAL_SECTION m_cs;
};

// CResourceArray Class manages data structures for handle information
class CResourceArray
{
public:
	CResourceArray() {};
	CResourceArray(long dwSize);
	virtual ~CResourceArray();

	RHANDLEHEADER** m_pHandles;
	long m_size;

	const RHANDLE* Add();
	const RHANDLE* AddNew(int hPos);
	void RemoveAll();

	bool IsFree(const long position);
	long GetCount();
	void SetTimeStamp( const long position, long nTimeStamp = 0 );

	RHANDLE* GetHandle(const long position);
	long GetDataValue(const long position);

	virtual long GetResourceHandle();
	virtual void ReleaseResourceHandle(long hResHandle);
	virtual void SetBusy(const long position);
	virtual void SetFree(const long position);
	virtual int TimeOutSetFree(const long position);

private:
	CRITICAL_SECTION m_res_cs;
	long m_rescount;
};


class CPoolBaseManager
{
public:
	DWORD m_dwNumCurrentResources;
	CFreeList* m_pFreeList;
	CResourceArray* m_pResources;
	HANDLE m_hStopEvent;
	DWORD m_dwAllocationPoll;
	DWORD m_dwMinPoolSize;
	bool m_bStartAllocator;
	DWORD m_dwResourceAllocSize;
	DWORD m_dwDeadResourcePoll;
	HANDLE m_hAllocThread;
	HANDLE m_hRefreshThread;
	DWORD m_dwMaxResources;

protected:
	CRITICAL_SECTION m_pb_cs;

	int dwMaxResources;
	DWORD m_dwHandleLifeTime;
	DWORD m_dwStartResources;
	DWORD m_dwWaitForHandleTime;

public:
	DWORD FreeResourcesLeft();
	DWORD GetNumResources();
	void SetStop();

	DWORD AllocateResources(DWORD dwNumAdd);
	int AddResource(int hPos);
	void DeallocateResources();
	void ReleaseDeadResources();

	DWORD GetFreeResource(const RHANDLE** poutHandle);
	void ReleaseResource(const RHANDLE* handle);

public:
	CPoolBaseManager();
	virtual ~CPoolBaseManager();

	void Init(DWORD dwMaxResources,      DWORD dwStartResources,
			  DWORD dwWaitForHandleTime, DWORD dwHandleLifeTime,
			  DWORD dwAllocationPoll,    DWORD dwMinPoolSize,
			  DWORD dwResourceAllocSize, DWORD dwDeadResourcePoll,
			  CResourceArray *pRA );
};

#endif
