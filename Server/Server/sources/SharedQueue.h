////////////////////////////////////////////////////////////////////////////////////
// SharedQueue.h
// CSharedQueue class header file.
// 02/11/13 by zinee
#include "SharedMemory.h"

#ifndef CSHAREDQUEUE_20021113_CLASS_HEADER
#define CSHAREDQUEUE_20021113_CLASS_HEADER

#define QUEUE_DSN_SIZE		40
#define QUEUE_USERID_SIZE	32
#define QUEUE_PASSWORD_SIZE	32
#define QUEUE_QUERY_SIZE	10000

struct QUEUE
{
	int		nIndex;
	char	Query[QUEUE_QUERY_SIZE];
};


////////////////////////////////////////////////////////////////////////////////////
// class CSharedQueue

class CSharedQueue
{
private:
	CSharedMemory	m_SharedMemory;

	HANDLE	m_hMutex;

	QUEUE*	m_pQueue;
	int		m_nQueueCount;

	int*	m_pnFront;
	int*	m_pnRear;

	void	IncQueuePos( int* pnQueuePos );
	BOOL	IncFront( void );
	BOOL	IncRear( void );

	BOOL	IsExistData(void);
	BOOL	IsFullData(void);

public:
	CSharedQueue();
	~CSharedQueue();

	BOOL	Create( LPCTSTR pSharedName, int nNumQueue );
	BOOL	Open( LPCTSTR pSharedName );
	BOOL	Release( void );
	BOOL	GetQueue( QUEUE* pQueue );
	BOOL	PutQueue( QUEUE* pQueue );
};


#endif