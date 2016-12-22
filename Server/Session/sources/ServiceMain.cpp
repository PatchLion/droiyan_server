///////////////////////////////////////////////////////////////////////////////
// Service Main
#include "stdafx.h"
#include "Session.h"
#include "SessionCom.h"
#include "SocketManager.h"
#include "UserManager.h"
#include "UserServerManager.h"
#include "Sresourcearray.h"
#include "Uresourcearray.h"
#include "USresourcearray.h"
#include "Mcommon.h"
#include "Search.h"
#include "Iocp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// FUNCTION PART...
void InitEnv();
//

#define SESSION_ALIVE_REQ	0x8FF0
#define SESSION_ALIVE_ACK	0x8FF1


DWORD dwSrvCtrlToPend[256] = {
	SERVICE_START_PENDING,
	SERVICE_STOP_PENDING,
	SERVICE_PAUSE_PENDING,
	SERVICE_CONTINUE_PENDING,
	0,
	SERVICE_STOP_PENDING,
	0
};

DWORD dwSrvPendToState[] = 
{
	0,
	0,
	SERVICE_RUNNING,
	SERVICE_STOPPED,
	0,
	SERVICE_RUNNING,
	SERVICE_PAUSED,
	0
};

int console_main(void);
int console_line = 8;
int GetCurrentUserCount(int& left);
void mputs(int x,int y,char* str);
/////////////////////////////////////////////////////////////////////////////////
// Resource Pool Manager Parameter
//
#define CMD_SERVER_CLOSE	1000
#define CMD_USER_CLOSE		2000

const int NUMALLOC = 1000;				// Number of times each thread will run
const int NUMSTARTRESOURCES = 100;		// Number of handles to start with
int NUMSTARTRESOURCES_USER = 1000;		// Number of handles to start with

const int MAXPOSSIBLE = 100;			// Maximum number of handles that can be
										//   allocated
int MAXPOSSIBLE_USER = 1000;			// Maximum number of handles that can be
										//   allocated

const int WAITFORHANDLE = 2000;			// Time a client will wait for a handle

//const int HANDLEEXPIRES = 600000*6;	// 60 minutes - time each resource can
//										//   live before being considered 'dead'
const int HANDLEEXPIRES = 600000*3;		// 30 minutes - time each resource can
//										//   live before being considered 'dead'

//const int HANDLEEXPIRES = 60000;		// 1 minutes - time each resource can
										//   live before being considered 'dead'

const int DEADRESOURCEPOLL = 600000;	// 10 minutes - time between each garbage
//										//   collection
//const int DEADRESOURCEPOLL = 60000;		// 1 minutes - time between each garbage
										//   collection

int ALLOCATIONPOLL = 2000;				// ms between each check for whether to
										//   allocate more
const int RESOURCEALLOCSIZE = 1;		// Number of resources to add at a time
const int MINPOOLSIZE = 0;				// Least amount of resources before
/////////////////////////////////////////////////////////////////////////////////

DWORD dwAliveBaseTime = 0;		
DWORD dwCheckServerBaseTime = 0;		

CSocketManager *g_pSQM = NULL;
CUserManager *g_pUQM = NULL;
CUserServerManager *g_pUSQM = NULL;
CIOCP<CSessDesc> m_ServerBase;
CIOCP<CSessDesc> m_UserBase;
CIOCP<CSessDesc> m_UserServerBase;
int nServerSignalCount = 0;
int nUserSignalCount = 0;


HANDLE g_hIOCP = NULL;
CSessionCom	*g_pCom = NULL;

extern TCHAR g_szAppName[];

///////////////////////////////////////////////////////////////////////////////
// FUNCTION PART...
//
void WINAPI ServiceHandler (DWORD dwControl)
{
	if ( g_hIOCP )
		PostQueuedCompletionStatus (g_hIOCP, dwControl, 1, NULL);
}

///////////////////////////////////////////////////////////////////////////////
// Check TimeOut User
//
void CheckTimeOutSockets( DWORD dwCurrentTime )
{
	++nUserSignalCount %= 2;

	// 2분에 한번씩...
	if ( nUserSignalCount != 0 ) return;

	// 사용자 시간 강제로 갱신 하기...
	CSessDesc *pSocket = NULL;

	for ( int i = 0; i < NUMSTARTRESOURCES_USER; i++ )
	{
		if ( g_pUQM->m_pResources->IsFree( i ) == true )
  			continue;

		pSocket = (CSessDesc *)g_pUQM->m_pResources->GetDataValue( i );
		if ( pSocket )
		{
			if ( pSocket->IsSocketAlive() )
			{
				// 클라이언트 시간 세팅 하기..
				g_pUQM->m_pResources->SetTimeStamp( pSocket->m_Sid );

				// 서버측 연결 시간 업데이트 하기...
				if ( pSocket->m_nLinkedSid >= 0 )
				{
					if ( pSocket->pLinkedDesc )
						g_pUSQM->m_pResources->SetTimeStamp( pSocket->pLinkedDesc->m_Sid );
				}
			}

			if ( pSocket->m_UserStatus != USER_LOGEDIN )
			{
				if ( pSocket->m_ConnectTimeTick == 0 ) continue;

				if ( pSocket->m_UserStatus == USER_DOWNLOADIN )
				{
					if ( dwCurrentTime - pSocket->m_ConnectTimeTick > (60000*120) )
						pSocket->SoftClose();
				}
				else
				{
					if ( dwCurrentTime - pSocket->m_ConnectTimeTick > (60000*5) )
						pSocket->SoftClose();
				}
			}
		}
	};

#ifdef _INTERNET_USAGE

/*
	CSessDesc *pDes;
	int i, nSocketCount;
	CMsg msgSend;

	nSocketCount = IocpUserBase.m_SocketArraySize;
	for ( i = 0; i < nSocketCount; i++ )
	{
		if ( IocpUserBase.m_SockArray[i] )
		{
			// 클라이언트측 소켓 얻기...
			pDes = (CSessDesc *)IocpUserBase.m_SockArray[i];
			if ( pDes )
			{
				char packet[50];
				BYTE temp, start1, start2;
				MYSHORT len;
				BYTE sum = 1;
				int index = 0;

				start1 = 0xfe, start2 = 0xff;
				len.i = 1;
				
				packet[index++] = start1;
				packet[index++] = start2;
				packet[index++] = 0x01;
				
				temp = (BYTE) len.b[0];		//	Filter( temp, index);
				packet[index++] = temp;
				sum = sum + temp;
				
				temp = (BYTE) len.b[1];		//	Filter( temp, index);
				packet[index++] = temp;
				sum = sum + temp;

				temp = 0x01;			//	ALIVE SIGNAL;
				packet[index++] = temp;
				sum = sum + temp;
				
				packet[index++] = sum;
				//	Filter( sum, index);

				packet[index++] = start2;
				packet[index++] = start1;

				pDes->Send( index, packet );
			}
		}
	};
*/
#else
/*
	CSessDesc *pDes;
	int i, nSocketCount;

	nSocketCount = IocpUserBase.m_SocketArraySize;
	for ( i = 0; i < nSocketCount; i++ )
	{
		if ( IocpUserBase.m_SockArray[i] )
		{
			// 클라이언트측 소켓 얻기...
			pDes = (CSessDesc *)IocpUserBase.m_SockArray[i];
			if ( pDes && pDes->IsTimeOut(dwCurrentTime) )
			{
				// 서버측 소켓 제거하기...
				if ( IocpUserServerBase.m_SockArray[i] )
				{
					pDes = (CSessDesc *)IocpUserServerBase.m_SockArray[i];
					if ( pDes && IocpUserServerBase.m_SockArray[i] )
						pDes->Close();
				}

				// 클라이언트측 소켓 제거하기...
				pDes = (CSessDesc *)IocpUserBase.m_SockArray[i];
				if ( pDes && IocpUserBase.m_SockArray[i] )
					pDes->Close();
			}
		}
	};
*/
#endif
}

void CheckUMandGS()
{
	if ( g_pCom && g_pCom->m_pDesUM )
	{
		if ( g_pCom->m_pDesUM->m_bConnectFlag == FALSE )
			g_pCom->ReConnectUM();
	}

	if ( g_pCom && g_pCom->m_pDesGS )
	{
		if ( g_pCom->m_pDesGS->m_bConnectFlag == FALSE )
			g_pCom->ReConnectGS();
	}
}

void SendServerAliveSignal()
{
	CSessDesc *pSocket = NULL;

	++nServerSignalCount %= 5;

	// 5분에 한번 체크 하기...
	//if ( nServerSignalCount != 0 ) return;

	if ( g_pCom && g_pCom->m_pDesGS )
	{
		// 신호 보내기...
		//CMsg msgSend;
		//msgSend.ID(SESSION_ALIVE_REQ) 
		//		<< g_pCom->m_pDesGS->m_Sid;
		//g_pCom->m_pDesGS->Say(msgSend);

		// 시간 갱신하기...
		if ( g_pCom->m_pDesGS->m_bConnectFlag == TRUE )
			g_pSQM->m_pResources->SetTimeStamp( g_pCom->m_pDesGS->m_Sid );
	}

	if ( g_pCom && g_pCom->m_pDesUM )
	{
		// 신호 보내기...
		//CMsg msgSend;
		//msgSend.ID(SESSION_ALIVE_REQ) 
		//		<< g_pCom->m_pDesUM->m_Sid;
		//g_pCom->m_pDesUM->Say(msgSend);

		// 시간 정하기...
		if ( g_pCom->m_pDesUM->m_bConnectFlag == TRUE )
			g_pSQM->m_pResources->SetTimeStamp( g_pCom->m_pDesUM->m_Sid );
	}
}

void WINAPI ServiceMain( DWORD dwArgc, LPTSTR* lpszArgv )
{
	BOOL			fControlKey = TRUE;
	DWORD			dwControl = 0, dwCurrentTime;
#ifdef _DEBUG
	CSessionCom		com(g_szAppName);
#elif _CONSOLE
	CSessionCom		com(g_szAppName);
#else
	CSessionCom		com(lpszArgv[0]);
#endif

	g_hIOCP = CreateIoCompletionPort (INVALID_HANDLE_VALUE, NULL, 1, 0);
	if (g_hIOCP == NULL)
		return;

	g_pCom = &com;

#ifdef _DEBUG
	SERVICE_STATUS_HANDLE hSS = RegisterServiceCtrlHandler( g_szAppName, ServiceHandler );
	AllocConsole();	// you only get 1 console.
	console_main();
#elif _CONSOLE
	SERVICE_STATUS_HANDLE hSS = RegisterServiceCtrlHandler( g_szAppName, ServiceHandler );
	AllocConsole();	// you only get 1 console.
	console_main();
#else
	SERVICE_STATUS_HANDLE hSS = RegisterServiceCtrlHandler( lpszArgv[0], ServiceHandler );
#endif

	SERVICE_STATUS ss;
	ss.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	ss.dwControlsAccepted = SERVICE_ACCEPT_STOP |
		                    SERVICE_ACCEPT_PAUSE_CONTINUE |
							SERVICE_ACCEPT_SHUTDOWN;

	InitEnv();

#ifdef _DEBUG
	char str_buf[200];
	int lu, uc;
	sprintf(str_buf, "]Max User : %d    ", NUMSTARTRESOURCES_USER );
	mputs(1,7,str_buf);

	uc = GetCurrentUserCount(lu);
	sprintf(str_buf, "]Current User : [%d/%d]   ", uc, lu);
	mputs(1,console_line,str_buf);
#elif _CONSOLE
	char str_buf[200];
	int lu, uc;
	sprintf(str_buf, "]Max User : %d    ", NUMSTARTRESOURCES_USER );
	mputs(1,7,str_buf);

	uc = GetCurrentUserCount(lu);
	sprintf(str_buf, "]Current User : [%d/%d]   ", uc, lu);
	mputs(1,console_line,str_buf);
#endif

	dwAliveBaseTime = ::GetTickCount();
	dwCheckServerBaseTime = dwAliveBaseTime;

	do
	{
		if (fControlKey)
		{
			ss.dwWin32ExitCode = NO_ERROR;
			ss.dwServiceSpecificExitCode = 0;
			ss.dwCheckPoint = 0;
			ss.dwWaitHint = 0;

			if (dwControl == SERVICE_CONTROL_INTERROGATE)
			{
#ifndef _DEBUG
#ifndef _CONSOLE
				SetServiceStatus (hSS, &ss);
#endif
#endif
			}
			else
			{
				if ( dwControl < 0 )
				{
					fControlKey = 0;
					Sleep(10);
					continue;
				}

				#ifndef _DEBUG
				#ifndef _CONSOLE
				if (dwSrvCtrlToPend[dwControl] != 0)
				{
					ss.dwCurrentState = dwSrvCtrlToPend[dwControl];
					ss.dwCheckPoint = 0;
					ss.dwWaitHint = 500;
					SetServiceStatus (hSS, &ss);
				}
				#endif
				#endif

				switch (dwControl)
				{
				case 0 :
					if (!com.OnStartService ())
						PostQueuedCompletionStatus (g_hIOCP, SERVICE_CONTROL_STOP, 1, NULL);
					else
					{
						dwAliveBaseTime = ::GetTickCount();
						dwCheckServerBaseTime = dwAliveBaseTime;
					}
					break;
		
				case SERVICE_CONTROL_CONTINUE :
					if (!com.OnContinueService ())
						PostQueuedCompletionStatus (g_hIOCP, SERVICE_CONTROL_STOP, 1, NULL);
					break;

				case SERVICE_CONTROL_PAUSE :
					com.OnPauseService ();
					break;
		
				case SERVICE_CONTROL_STOP :
				case SERVICE_CONTROL_SHUTDOWN :
					com.OnStopService ();
					break;
				}

				#ifndef _DEBUG
				#ifndef _CONSOLE
				if (dwSrvPendToState[ss.dwCurrentState] != 0)
				{
					ss.dwCurrentState = dwSrvPendToState[ss.dwCurrentState];
					ss.dwCheckPoint = 0;
					ss.dwWaitHint = 0;
					SetServiceStatus (hSS, &ss);
				}
				#endif
				#endif
			}
		}
		else
		{
			dwCurrentTime = ::GetTickCount();

			if ( (dwCurrentTime-dwCheckServerBaseTime) > 10000 )
			{
				#ifdef _DEBUG
				char str_buf[200];
				int lu,uc;
				uc = GetCurrentUserCount(lu);
				sprintf(str_buf, "]Current User : [%d/%d]   ", uc, lu);
				mputs(1,console_line,str_buf);
				#elif _CONSOLE
				char str_buf[200];
				int lu,uc;
				uc = GetCurrentUserCount(lu);
				sprintf(str_buf, "]Current User : [%d/%d]   ", uc,lu);
				mputs(1,console_line,str_buf);
				#endif

				CheckUMandGS();
				dwCheckServerBaseTime = dwCurrentTime;
			}

			if ( (dwCurrentTime-dwAliveBaseTime) > 60000 )
			{
				// 사용자에게 얼라이브 신호 보내기(현재는 무시)...
				CheckTimeOutSockets(dwCurrentTime);
				
				// 서버에 신호 보내기...
				SendServerAliveSignal();

				dwAliveBaseTime = ::GetTickCount();
			}
		}

		if (ss.dwCurrentState != SERVICE_STOPPED)
		{
			#ifdef _DEBUG
			fControlKey = 0;
			Sleep(10);
			#elif _CONSOLE
			fControlKey = 0;
			Sleep(10);
			#else
			DWORD dwCompKey;
			OVERLAPPED* po;

			BOOL ControlKey;
			ControlKey = GetQueuedCompletionStatus ( g_hIOCP, &dwControl, &dwCompKey, &po, 10 );
			if ( ControlKey == TRUE && dwCompKey == 1 )
				fControlKey = ControlKey;
			else
				fControlKey = 0;
			#endif
		}
		else
		{
			#ifdef _DEBUG
			ss.dwCurrentState = SERVICE_RUNNING;
			fControlKey = 0;
			Sleep(10);
			#elif _CONSOLE
			ss.dwCurrentState = SERVICE_RUNNING;
			fControlKey = 0;
			Sleep(10);
			#endif
		}

	} while (ss.dwCurrentState != SERVICE_STOPPED);

	// Clear Socket Pool...
	if ( g_pSQM )
	{
		g_pSQM->DeallocateResources();
		delete g_pSQM;
		g_pSQM = NULL;
	}

	if ( g_pUQM )
	{
		g_pUQM->DeallocateResources();
		delete g_pUQM;
		g_pUQM = NULL;
	}

	if ( g_pUSQM )
	{
		g_pUSQM->DeallocateResources();
		delete g_pUSQM;
		g_pUSQM = NULL;
	}

	CloseHandle (g_hIOCP);
}

void InitEnv()
{
	// 용량 설정...
	if ( g_pCom )
	{
		MAXPOSSIBLE_USER = g_pCom->m_nCapacity;
		NUMSTARTRESOURCES_USER = g_pCom->m_nCapacity;
		ALLOCATIONPOLL = g_pCom->m_nCapacity;
	}

	// Create Server Socket Quarter Pool...
	g_pSQM = new CSocketManager;

	// SERVER SOCKET INIT...
	CSockResourceArray *pSRA;

	pSRA = new CSockResourceArray(MAXPOSSIBLE);

	// Create Socket Quarter Pool...
	g_pSQM->Init(MAXPOSSIBLE, NUMSTARTRESOURCES, WAITFORHANDLE, HANDLEEXPIRES,
				ALLOCATIONPOLL, MINPOOLSIZE, RESOURCEALLOCSIZE, DEADRESOURCEPOLL,
				pSRA );
	//

	// Socket for Server IOCP Base 초기화...
	m_ServerBase.SetThreadCount(1);
	m_ServerBase.NaglingStatusOff(); // NT 서버는 안되는 영우가 있음...
	m_ServerBase.Init( SOCKET_FOR_NONESTATE, g_pSQM );

	// Create User Socket Quarter Pool...
	g_pUQM = new CUserManager;

	// USER SOCKET INIT...
	CUserResourceArray *pURA;

	pURA = new CUserResourceArray(MAXPOSSIBLE_USER);

	// Create Socket Quarter Pool...
	g_pUQM->Init(MAXPOSSIBLE_USER, NUMSTARTRESOURCES_USER, WAITFORHANDLE, HANDLEEXPIRES,
				ALLOCATIONPOLL, MINPOOLSIZE, RESOURCEALLOCSIZE, DEADRESOURCEPOLL,
				pURA );
	//

	// Socket for User IOCP Base 초기화...
	m_UserBase.SetThreadCount(2);
	m_UserBase.NaglingStatusOff();
	m_UserBase.SetupResourceKeeper();
	m_UserBase.Init( SOCKET_FOR_USER, g_pUQM );

	// Create UserServer Socket Quarter Pool...
	g_pUSQM = new CUserServerManager;

	// USER SOCKET INIT...
	CUserServerResourceArray *pUSRA;

	pUSRA = new CUserServerResourceArray(MAXPOSSIBLE_USER);

	// Create Socket Quarter Pool...
	g_pUSQM->Init(MAXPOSSIBLE_USER, NUMSTARTRESOURCES_USER, WAITFORHANDLE, HANDLEEXPIRES,
				ALLOCATIONPOLL, MINPOOLSIZE, RESOURCEALLOCSIZE, DEADRESOURCEPOLL,
				pUSRA );
	//
	// Socket for User IOCP Base 초기화...
	m_UserServerBase.SetThreadCount(2);
	m_UserServerBase.Init( SOCKET_FOR_USERSERVER, g_pUSQM );

}

CSessDesc* GetServerSocket( CIOCPBASE *pIocpBase )
{
	const RHANDLE* pHandle = 0;
	CSessDesc *pDes;
	int sid;

	pHandle = 0; sid = -1;

	DWORD ret = g_pSQM->GetFreeResource(&pHandle);
	if ( ret == 0 )
	{
		sid = pHandle->pos;
		pDes = (CSessDesc *)pHandle->handle;
	}		
	else
	{
		return NULL;
	}

	pDes->m_pIocpBase = pIocpBase;
	pDes->m_Sid = sid;
	pDes->m_SNumber = sid;
	pDes->m_State = STATE_ACCEPTED;
	pDes->m_RecvOverlap.hEvent = NULL;

	return pDes;
}

CSessDesc* GetUserServerSocket( CIOCPBASE *pIocpBase )
{
	const RHANDLE* pHandle = 0;
	CSessDesc *pDes;
	int sid;

	pHandle = 0; sid = -1;

	DWORD ret = g_pUSQM->GetFreeResource(&pHandle);
	if ( ret == 0 )
	{
		sid = pHandle->pos;
		pDes = (CSessDesc *)pHandle->handle;
	}		
	else
	{
		return NULL;
	}

	pDes->m_pIocpBase = pIocpBase;
	pDes->m_Sid = sid;
	pDes->m_SNumber = sid;
	pDes->m_State = STATE_ACCEPTED;
	pDes->m_RecvOverlap.hEvent = NULL;

	return pDes;
}

CSessDesc* GetUserSocketUid( int uid )
{
	CSessDesc *pDes;

	if (uid >= 0 && uid < MAXPOSSIBLE_USER )
	{
		pDes = m_UserBase.GetUser(uid);
		if ( pDes )
		{
			if ( !pDes->IsSocketAlive()  )
			{
				m_UserBase.UserFree(uid);
				return NULL;
			}
		}
		return pDes;
	}
	//

	return NULL;
}

CSessDesc* GetUserServerSocketUid( int uid )
{
	CSessDesc *pDes;

	if (uid >= 0 && uid < MAXPOSSIBLE_USER )
	{
		pDes = m_UserServerBase.GetUser(uid);
		if ( pDes )
		{
			if ( !pDes->IsSocketAlive()  )
			{
				m_UserServerBase.UserFree( uid );
				return NULL;
			}
		}
		return pDes;
	}
	//

	return NULL;
}

int GetCurrentUserCount(int& leftuser)
{
	int usercount = 0, nLeftuser = 0;

	for ( int i = 0; i < NUMSTARTRESOURCES_USER; i++ )
	{
		if ( g_pUQM->m_pResources->IsFree( i ) == true )
		{
			nLeftuser++;
  			continue;
		}

		CSessDesc *pSocket = (CSessDesc *)g_pUQM->m_pResources->GetDataValue( i );
		if ( pSocket )
		{
			if ( pSocket->m_SockFlag == 1 )
			{
				usercount++;
			}
		}
	}

	leftuser = nLeftuser;
	return usercount;
}
