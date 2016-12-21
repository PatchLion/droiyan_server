/////////////////////////////////////////////////////////////////////
//	ServerDlg.cpp : implementation file of the the CServerDlg class
//  Copyright (C) 2000,  Jin-Soo Jeon
//
//	If this code works, it was written by Jin-Soo Jeon.
//	If not, I don't know who wrote it.
//
#include "stdafx.h"
#include "Server.h"
#include "user.h"
#include "ServerDlg.h"
#include "Sresourcearray.h"
#include "SocketManager.h"
#include "Uresourcearray.h"
#include "UserManager.h"
#include "Search.h"
#include "Mcommon.h"
#include "SockDataList.h"
#include <process.h>

DWORD WorkerServerThread(LPVOID lp );
DWORD WorkerUserThread(LPVOID lp );
//DWORD WINAPI WorkerChatThread(LPVOID lp );
//unsigned __stdcall WorkerChatThread( void *lp );
UINT WorkerChatThread( void *lp );

//const int NUMALLOC = 1000;						// Number of times each thread will run
const int NUMSTARTRESOURCES = 5;					// Number of handles to start with
int NUMSTARTRESOURCES_USER = MAX_USER;				// Number of handles to start with

const int MAXPOSSIBLE = 5;							// Maximum number of handles that can be allocated
int MAXPOSSIBLE_USER = MAX_USER;					// Maximum number of handles that can be allocated

const int WAITFORHANDLE = 2000;						// Time a client will wait for a handle

const int HANDLEEXPIRES = 60000*30;					// 30 minutes - time each resource can
//													// live before being considered 'dead'

const int DEADRESOURCEPOLL = 60000*5;				// 5 minutes - time between each garbage
													// collection
const int ALLOCATIONPOLL = MAX_USER;				// ms between each check for whether to
													//   allocate more
const int RESOURCEALLOCSIZE = 1;					// Number of resources to add at a time
const int MINPOOLSIZE = 0;							// Least amount of resources before
/////////////////////////////////////////////////////////////////////////////////
CRITICAL_SECTION m_CS_FileWrite;

// 2002.1.
CRITICAL_SECTION m_CS_LoginData;
CPtrList RecvLoginData;
long nLoginDataCount = 0;
CRITICAL_SECTION m_CS_LogoutData;
CPtrList RecvLogoutData;
long nLogoutDataCount = 0;				

CRITICAL_SECTION m_CS_SqlDataProcess;

CPtrList RecvSqlData;
CRITICAL_SECTION m_CS_SqlData;
long nSqlDataCount = 0;		
int g_ChatEnable[AUTOMATA_THREAD+1];
//
DWORD nRunThreadTimer[AUTOMATA_THREAD+1];

// Fortress Data Packet
// 2002.1.
CRITICAL_SECTION m_CS_FortressData;
CPtrList RecvFortressData;
long nFortressDataCount = 0;

int socket_buffer_size_kiro = 8;

int PacketLength = 512;
long LastDBAccessTime = 0;
long g_TMflag = 0;
long g_TTF[AUTOMATA_THREAD+1];
// chat-data-process thread 
CHATDATAPACKET *g_WaitRecvDataChat[DATA_BUF_SIZE_FOR_THREAD+1][AUTOMATA_THREAD+1];
int g_nChatDataHead[AUTOMATA_THREAD+1];
int g_nChatDataTail[AUTOMATA_THREAD+1];
BYTE g_ServerId = 0;
char ExeFilePath[_MAX_PATH] = {""};

DWORD g_ThreadAliveTime[AUTOMATA_THREAD+1];
DWORD g_ThreadErr[AUTOMATA_THREAD+1];

//

//압축 
//CCompressManager jcm;  // 로그인 할경우 데이터 압축 & 해제 
// 암호화 관련
void Make_public_key();
//
char ExePath[_MAX_PATH];
CString m_Gongji_Message;

CSocketManager *g_pSQM = NULL;
CUserManager *g_pUQM = NULL;
CSearch *g_pUserList = NULL;

extern CServerDlg *g_pMainDlg;

long	g_PotionViewOnOff = 0;

BOOL CServerDlg::InitEnv()
{
	int i;
	// 게임 서버 정보 초기화...
	// 실행파일 경로 가져오기...
//	char Buf[_MAX_PATH], Path[_MAX_PATH];
//	char drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
//	char IniPath[_MAX_PATH];
//
//	::GetModuleFileName( AfxGetApp()->m_hInstance, Buf, 256 );
//	_splitpath( Buf, drive, dir, fname, ext );
//	strcpy( Path, drive );
//	strcat( Path, dir );		
//	strcpy( ExeFilePath, Path );
//
//	strcpy( IniPath, ExeFilePath );
//	strcat( IniPath, "DB.ini" );
//	
//	// DB-PORT 얻기...
//	m_nDBPort = GetPrivateProfileInt("DBSERVER", "PORT", 0, IniPath);
//	if(m_nDBPort == 0)
//	{
//		::MessageBox(NULL, "ERROR: LOGIN_SERVER PORT", "변수 에러", MB_OK);
//		return FALSE;
//	}
//
//	// DB-ADDRESS 얻기...
//	if ( GetPrivateProfileString("DBSERVER", "IPADDRESS", "0", m_DBAddr, sizeof(m_DBAddr), (LPCSTR)IniPath) == 0 )
//	{
//		::MessageBox( NULL, "ERROR: LOGIN_SERVER_ADDRESS", "변수 에러", MB_OK );
//		return FALSE;
//	}
//
//	m_pDBSocket = NULL;
//
//	// JJS	2002.02.28
//	BOOL bIsZoneClient = FALSE;
//	m_pZoneSocket = NULL;
//
//	// Zone Server Address 
//	if (GetPrivateProfileString("ZONE_SERVER", "SERVER_IP", "", m_strZoneAddr, sizeof(m_strZoneAddr), (LPCSTR)IniPath) != 0 )
//	{
//		bIsZoneClient = TRUE;	// Zone Client 로 동작
//	}
//	//

	for ( i = 0; i <= AUTOMATA_THREAD; i++ )
	{
		g_TTF[i] = 0;
		g_ChatEnable[i] = TRUE;
		g_nChatDataHead[i] = 0;
		g_nChatDataTail[i] = 0;

		g_ThreadAliveTime[i] = 0;
	}

	for ( i = 0; i < AUTOMATA_THREAD; i++ )
	{
		for ( int j = 0; j <= DATA_BUF_SIZE_FOR_THREAD; j++ )
		{
			g_WaitRecvDataChat[j][i] = NULL;
		}
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
	m_ServerBase.Init( SOCKET_FOR_SERVER, g_pSQM, WorkerServerThread );
	//	

	// Create User Socket Quarter Pool...
	g_pUQM = new CUserManager;

	// SERVER SOCKET INIT...
	CUserResourceArray *pURA;

	pURA = new CUserResourceArray(MAXPOSSIBLE_USER);

	// Create Socket Quarter Pool...
	g_pUQM->Init(MAXPOSSIBLE_USER, NUMSTARTRESOURCES_USER, WAITFORHANDLE, HANDLEEXPIRES,
				ALLOCATIONPOLL, MINPOOLSIZE, RESOURCEALLOCSIZE, DEADRESOURCEPOLL,
				pURA );
	//
	g_pUserList = new CSearch( MAXPOSSIBLE_USER );

	// Pool for UserBase 초기화...   wait 역활 
	m_UserBase.SetThreadCount(AUTOMATA_THREAD);
	m_UserBase.Init( SOCKET_FOR_USER, g_pUQM, WorkerUserThread );
/*
	///////////////////////////////////////////////////////////////////////////////////////////
	// Login Server Part

	// DB socket 만들어 열기...
	m_pDBSocket = GetServerSocket( &m_ServerBase );
	if(m_pDBSocket == NULL) 
	{
		::MessageBox(NULL, "ERROR: GetServerSocket", "Error", MB_OK);
		return FALSE;
	}
	m_pDBSocket->m_ReConnectFlag = TRUE;

	if(!DBSocketConnect())
	{
		::MessageBox(NULL, "Login Server 를 먼저 실행해 주십시요.", "Error", MB_OK);
		return FALSE;
	}

	// 데이타베이스 초기 연결...
	TCHAR TempBuf[SEND_BUF_SIZE];
	int index = 0;
	SetByte(TempBuf, g_ServerId, index );
	SetByte(TempBuf, DB_SERVER_IN_REQ, index );
	SetByte(TempBuf, (BYTE)0x01, index );
	m_pDBSocket->Send( TempBuf, index );
	//

	///////////////////////////////////////////////////////////////////////////////////////////
	// Zone Server Part

	if(bIsZoneClient)
	{
		m_pZoneSocket = GetServerSocket( &m_ServerBase );
		if(m_pZoneSocket == NULL) 
		{
			::MessageBox(NULL, "ERROR: GetServerSocket, Zone", "Error", MB_OK);
			return FALSE;
		}
		m_pZoneSocket->m_ReConnectFlag = TRUE;
		
		if(!ZoneSocketConnect())
		{
			::MessageBox(NULL, "ERROR: Can't connect to Zone Server.", "Error", MB_OK);
			return FALSE;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////
*/
	return TRUE;
}

int CServerDlg::MakeThreadSafeUserMessage( int cmd_code, int wparam, long lparam )
{
	return 0;
}

int CServerDlg::MakeThreadSafeMessage( int cmd_code, int wparam, long lparam )
{
	return 0;
}

void CServerDlg::ServerCloseMessage(int wparam, long lparam) 
{
	MakeThreadSafeMessage( CMD_SERVER_CLOSE, wparam, lparam );
}

void CServerDlg::UserCloseMessage(int wparam, long lparam) 
{
	MakeThreadSafeUserMessage( CMD_USER_CLOSE, wparam, lparam );
}

BOOL CServerDlg::AutoMataAppCmd(WAIT_RECV_DATA *wrd)
{
	int cmd, index = 0;
	memcpy( &cmd, wrd->pData, sizeof(int) );
	index += sizeof(int);

	switch( cmd )
	{
/*
		case CMD_SERVER_CLOSE:
			{
				int sid, lparam;
				CSSocket *p_rSocket, *pSock;

				memcpy( &sid, wrd->pData+index, sizeof(int) );
				index += sizeof(int);

				memcpy( &lparam, wrd->pData+index, sizeof(long) );
				index += sizeof(long);

				p_rSocket = (CSSocket *)lparam;

				delete wrd;

				pSock = (CSSocket *)g_pSQM->m_pResources->GetDataValue( sid );
				if ( pSock && p_rSocket == pSock )
				{
					TRACE("SERVER CLOSED...\n");

					((CBSocket *)pSock)->SockCloseProcess(1);
				}
			}
			
			break;
*/
		case CMD_USER_CLOSE:
			{
				int uid, lparam;
				USER *pUser = NULL;

				memcpy( &uid, wrd->pData+index, sizeof(int) );
				index += sizeof(int);

				memcpy( &lparam, wrd->pData+index, sizeof(long) );
				index += sizeof(long);

				delete wrd;

				pUser = m_Com.GetUserUid( uid );

				if ( pUser )
				{
					pUser->SoftClose();
					//TRACE("AUTOMATA SEND ERROR USER CLOSE = [%d]\n",pUser->m_Uid);
				}
			}
			break;
/*
		case CMD_ROOM_CLOSE:
			{
				int rid, lparam;
				CRoom *pRoom;

				memcpy( &rid, wrd->pData+index, sizeof(int) );
				index += sizeof(int);

				memcpy( &lparam, wrd->pData+index, sizeof(long) );
				index += sizeof(long);

				delete wrd;

				pRoom = (CRoom *)g_pRQM->m_pResources->GetDataValue( rid );

				if ( pRoom )
				{
					pRoom->m_RoomFlag = 0;
					pRoom->ReleaseRoomResource( rid );
					TRACE("ROOM DELETED IN TIMESTAMP FUNCTION[%d]...\n", pRoom->m_RNumber );
				}
			}
			break;
*/
		default:
			delete wrd;
			break;
	}

	return TRUE;
}

LRESULT CServerDlg::OnStartAutomata( WPARAM wparam, LPARAM lparam )
{
	m_UserBase.m_bAcceptEnableFlag = TRUE;

	return 1;
}

/*
DWORD WINAPI WorkerAutomataThread(LPVOID lp )
{
	long *thno;
	int nThreadNo = 0;
	CServerDlg *pMainDlg = g_pMainDlg;

	int proccount = 0;
	DWORD lastTick = GetTickCount();
	thno = (long *)lp;
	nThreadNo = *thno;
	pMainDlg->m_nThreadCount++;

	// 암호화 관련 
	//BYTE pTBuf[RECEIVE_BUF_SIZE+1];
	//int cryption_flag = 0;
	//DWORD tmp_rec_val; 
	//

	srand( (unsigned)time( NULL ) );
	myrand( 1, 10000 ); myrand( 1, 10000 );

start_loop:;
	if ( pMainDlg->m_nThreadCount < AUTOMATA_THREAD )
	{
		Sleep(1);
		goto start_loop;
	}

	TRACE("Thread Started [%d][%d]...\n", nThreadNo, pMainDlg->m_nThreadCount-1 );

	USER *pSocket;	
	WAIT_RECV_DATA *wrd;

	CPtrList LocalRecvPtrList;
	int nLocalRecvDataLength = 0;

	// 스레드 메인 루틴...
	for (;;)
	{
		if ( nRecvDataLength[nThreadNo] < 1 )
		{
			proccount = 0;
			Sleep(1);
			continue;
		}



		EnterCriticalSection( &m_CS_ReceiveData[nThreadNo] );

		while( nRecvDataLength[nThreadNo] >= 1 )
		{
			wrd = (WAIT_RECV_DATA*)RecvPtrList[nThreadNo].RemoveHead();
			nRecvDataLength[nThreadNo] = RecvPtrList[nThreadNo].GetCount();

			LocalRecvPtrList.AddTail( wrd );
		}

		LeaveCriticalSection( &m_CS_ReceiveData[nThreadNo] );

		nLocalRecvDataLength = LocalRecvPtrList.GetCount();

		while( nLocalRecvDataLength >= 1 )
		{
			wrd = (WAIT_RECV_DATA*)LocalRecvPtrList.RemoveHead();
			nLocalRecvDataLength = LocalRecvPtrList.GetCount();

			if( wrd == NULL ) continue;

			if ( wrd->m_Type == SOCKET_FOR_APPLICATION )
			{
				TRACE("USER APPLICATION-CMP CALLED[%d]...\n",wrd->usn);

				//delete wrd;
				pMainDlg->AutoMataAppCmd(wrd);
				Sleep(1);
				continue;
			}
			else if ( wrd->m_Type == SOCKET_FOR_DISCONNECT )
			{
				if ( wrd->usn >= 0 && wrd->usn < 32767 )
				{
					pSocket = (USER *)g_pUQM->m_pResources->GetDataValue( wrd->usn );
				}
				else
				{
					delete wrd;
					Sleep(1);
					continue;
				}

				if ( pSocket == NULL )
				{
					delete wrd;
					Sleep(1);
					continue;
				}

				BYTE len;
				LOGINOUTTHREADDATA *pLIOTD;
				pLIOTD = new LOGINOUTTHREADDATA;
				pLIOTD->UID = wrd->usn;
				len = (BYTE)strlen(pSocket->m_strUserID);
				memcpy(pLIOTD->ID, &len, sizeof(BYTE) );
				memcpy(pLIOTD->ID+sizeof(BYTE), pSocket->m_strUserID, len);
				pLIOTD->ID[sizeof(BYTE)+len] = '\0';

				EnterCriticalSection( &m_CS_LogoutData );
				RecvLogoutData.AddTail(pLIOTD);
				nLogoutDataCount = RecvLogoutData.GetCount();
				LeaveCriticalSection( &m_CS_LogoutData );

				//pSocket->SockCloseProcess();
				
				delete wrd;
				Sleep(1);
				continue;
			}

			if ( wrd->usn >= 0 && wrd->usn < 32767 )
			{
				pSocket = (USER *)g_pUQM->m_pResources->GetDataValue( wrd->usn );
			}
			else
			{
				pSocket = (USER *)wrd->pSocket;
			};

			if ( pSocket == NULL || pSocket->m_Socket == INVALID_SOCKET )
			{
				delete wrd;
				Sleep(1);
				continue;
			}

			// IKING 1999.1.
			if ( pSocket->IsSocketAlive() != TRUE )
			{
				delete wrd;
				wrd = NULL;
				Sleep(1);
				continue;
			}

			pSocket->m_BufCount = 0;
			pSocket->m_BufHead = 0;
			memcpy(pSocket->m_pBuf, wrd->pData, wrd->dcount );
			pSocket->m_BufCount = wrd->dcount;

			delete wrd;
			wrd = NULL;

			// 실제 데이타 처리...
			pSocket->ProcessData();

			if (++proccount >= 20 )
			{
				proccount = 0;
				Sleep(1);
			}
		}

	
	}

	return 0;
}
*/

// 로그인 스레드 함수...
//DWORD WINAPI WorkerLoginThread(LPVOID lp )
//unsigned __stdcall WorkerLoginThread( void *lp )
UINT WorkerLoginThread( void *lp )
{
	LOGINOUTTHREADDATA *pLIOTD;

	CPtrList LocalLoginData;
	int nLocalLoginDataCount = 0;

	for (;;)
	{
		if ( nLoginDataCount < 1 )
		{
			Sleep(1);
			continue;
		}

		EnterCriticalSection( &m_CS_LoginData );

		while( nLoginDataCount >= 1 )
		{
			pLIOTD = (LOGINOUTTHREADDATA *)RecvLoginData.RemoveHead();
			nLoginDataCount = RecvLoginData.GetCount();

			LocalLoginData.AddTail(pLIOTD);
			nLocalLoginDataCount = LocalLoginData.GetCount();
		}

		LeaveCriticalSection( &m_CS_LoginData );

		while( nLocalLoginDataCount >= 1 )
		{
			pLIOTD = (LOGINOUTTHREADDATA*)LocalLoginData.RemoveHead();
			nLocalLoginDataCount = LocalLoginData.GetCount();

			if ( pLIOTD == NULL ) continue;

			USER *pUser = NULL;
			pUser = g_pUserList->GetUserUid(pLIOTD->UID);
			if ( pUser == NULL )
			{
				delete pLIOTD;
				Sleep(1);
				continue;
			}

//			EnterCriticalSection(&m_CS_SqlDataProcess);
			if ( pUser && pUser->m_SockFlag == 1 )
			{
				switch(pLIOTD->CODE)
				{
					case ACCOUNT_LOGIN_REQ:
						pUser->AccountLoginReq(pLIOTD->ID);
						break;

					case GAME_START_REQ:
						pUser->GameStart(pLIOTD->ID);
						break;

					case RESTART_REQ:
						pUser->RestartReq(pLIOTD->ID);
						break;
				}
			}
//			LeaveCriticalSection(&m_CS_SqlDataProcess);
			delete pLIOTD;
			Sleep(1);
		}

/*
		EnterCriticalSection( &m_CS_LoginData );
		pLIOTD = (LOGINOUTTHREADDATA *)RecvLoginData.RemoveHead();
		nLoginDataCount = RecvLoginData.GetCount();
		LeaveCriticalSection( &m_CS_LoginData );

		if ( pLIOTD == NULL ) continue;

		
		pUser = g_pUserList->GetUserUid(pLIOTD->UID);
		if ( pUser == NULL )
		{
			delete pLIOTD;
			Sleep(1);
			continue;
		}

		EnterCriticalSection(&m_CS_SqlDataProcess);
		if ( pUser && pUser->m_SockFlag == 1 )
		{
			switch(pLIOTD->CODE)
			{
				case ACCOUNT_LOGIN_REQ:
					pUser->AccountLoginReq(pLIOTD->ID);
					break;

				case GAME_START_REQ:
					pUser->GameStart(pLIOTD->ID);
					break;

				case RESTART_REQ:
					pUser->RestartReq(pLIOTD->ID);
					break;
			}
		}
		LeaveCriticalSection(&m_CS_SqlDataProcess);
		delete pLIOTD;
		Sleep(1);
*/
	}

	return 0;
}

// 로그인 스레드 함수...
//DWORD WINAPI WorkerLogoutThread(LPVOID lp )
//unsigned __stdcall WorkerLogoutThread( void *lp )
UINT WorkerLogoutThread( void *lp )
{
	LOGINOUTTHREADDATA *pLIOTD;

	CPtrList LocalLogoutData;
	int nLocalDataCount = 0;

	for (;;)
	{
		if ( nLogoutDataCount < 1 )
		{
			Sleep(1);
			continue;
		}

		EnterCriticalSection( &m_CS_LogoutData );

		while( nLogoutDataCount >= 1 )
		{
			pLIOTD = (LOGINOUTTHREADDATA *)RecvLogoutData.RemoveHead();
			nLogoutDataCount = RecvLogoutData.GetCount();

			LocalLogoutData.AddTail( pLIOTD );
			nLocalDataCount = LocalLogoutData.GetCount();
		}

		LeaveCriticalSection( &m_CS_LogoutData );

		while( nLocalDataCount >= 1 )
		{
			pLIOTD = (LOGINOUTTHREADDATA*)LocalLogoutData.RemoveHead();
			nLocalDataCount = LocalLogoutData.GetCount();

			if ( pLIOTD == NULL ) continue;

			USER *pUser = NULL;
			pUser = g_pUserList->GetUserUid(pLIOTD->UID);
			if ( pUser == NULL )
			{
				delete pLIOTD;
				Sleep(1);
				continue;
			}

//			EnterCriticalSection(&m_CS_SqlDataProcess);
			if ( pUser )
				pUser->SockCloseProcess();
//			LeaveCriticalSection(&m_CS_SqlDataProcess);
			delete pLIOTD;
			//Sleep(1);
		}

/*
		EnterCriticalSection( &m_CS_LogoutData );
		pLIOTD = (LOGINOUTTHREADDATA *)RecvLogoutData.RemoveHead();
		nLogoutDataCount = RecvLogoutData.GetCount();
		LeaveCriticalSection( &m_CS_LogoutData );

		if ( pLIOTD == NULL ) continue;

		pUser = g_pUserList->GetUserUid(pLIOTD->UID);
		if ( pUser == NULL )
		{
			delete pLIOTD;
			Sleep(1);
			continue;
		}

		EnterCriticalSection(&m_CS_SqlDataProcess);
		if ( pUser )
			pUser->SockCloseProcess();
		LeaveCriticalSection(&m_CS_SqlDataProcess);
		delete pLIOTD;
		Sleep(1);
*/
	}

	return 0;
}

//DWORD WINAPI WorkerSQLThread(LPVOID lp )
//unsigned __stdcall WorkerSQLThread( void *lp )
UINT WorkerSQLThread( void *lp )
{
	SQLDATAPACKET *pSDP;
	CPtrList LocalSqlData;
	int nLocalDataCount = 0;

	for (;;)
	{
		if ( nSqlDataCount < 1 )
		{
			Sleep(1);
			continue;
		}


		EnterCriticalSection( &m_CS_SqlData );

		while( nSqlDataCount >= 1 )
		{
			pSDP = (SQLDATAPACKET *)RecvSqlData.RemoveHead();
			nSqlDataCount = RecvSqlData.GetCount();

			LocalSqlData.AddTail( pSDP );
		}

		LeaveCriticalSection( &m_CS_SqlData );

		nLocalDataCount = LocalSqlData.GetCount();

		while( nLocalDataCount >= 1 )
		{
			pSDP = (SQLDATAPACKET*)LocalSqlData.RemoveHead();
			nLocalDataCount = LocalSqlData.GetCount();

			if ( pSDP == NULL ) continue;

			USER *pUser = NULL;
			pUser = g_pUserList->GetUserUid(pSDP->UID);
			if ( pUser == NULL )
			{
				delete pSDP;
				Sleep(1);
				continue;
			}

			if (  pUser->m_SockFlag != 1 )
			{
				delete pSDP;
				Sleep(1);
				continue;
			}

//			EnterCriticalSection(&m_CS_SqlDataProcess);
			switch(pSDP->code)
			{
			case NEW_CHAR_REQ_WITH_THREAD:
				pUser->NewCharReq((TCHAR *)pSDP->pData);
				break;
			case GUILD_OPEN_REQ:
				pUser->NewGuild((TCHAR *)pSDP->pData);
				break;
			case DEL_GUILD_CHAR_REQ:
				pUser->DeleteGuildUser((TCHAR *)pSDP->pData);
				break;
			case GUILD_KICK_OUT:
				pUser->GuildKickOut((TCHAR *)pSDP->pData);
				break;
			case GUILD_MARK_ADD_REQ:
				pUser->GuildMarkAddReq((TCHAR *)pSDP->pData);
				break;
//			case GUILD_INVITE_USER_REQ:
//				pUser->GuildInvite((TCHAR *)pSDP->pData);
//				break;
			case GUILD_OFF_WITH_THREAD:
				pUser->GuildOff((TCHAR *)pSDP->pData);
				break;
			case GUILD_DISPERSE:
				pUser->GuildDisperse((TCHAR *)pSDP->pData);
				break;
			case DELETE_CHAR_REQ:
				pUser->DeleteCharReq((TCHAR *)pSDP->pData);
				break;

			case BBS_DELETE:
				pUser->BBSDelete((TCHAR *)pSDP->pData);
				break;
			case BBS_EDIT:
				pUser->BBSEdit((TCHAR *)pSDP->pData);
				break;
			case BBS_WRITE:
				pUser->BBSWrite((TCHAR *)pSDP->pData);
				break;
			case BBS_NEXT:
				pUser->BBSNext((TCHAR *)pSDP->pData);
				break;
			case BBS_READ:
				pUser->BBSRead((TCHAR *)pSDP->pData);
				break;
			case DB_GUILD_ITEM_MOVE_REQ:
				pUser->GuildItemMoveReq((TCHAR *)pSDP->pData);
				break;
			case DB_GUILD_WHEREHOUSE_EVENT_REQ:
				pUser->GuildWharehouseOpenReq();
				break;
			case DB_USER_COUNT:
				{
					COM *pCom = g_pMainDlg->GetCOM();
					if ( pCom )
					{
						pCom->UpdateUserCount();
					}
				}
				break;
			case DB_USER_DEAD:
				pUser->UpdateUserDeadLog((TCHAR *)pSDP->pData);
				break;
			//yskang 0.1 호칭[애칭]
			case LOVE_NAME_RESULT:
				pUser->InsertLoveName((TCHAR *)pSDP->pData);
				break;
			default: break;
			};
//			LeaveCriticalSection(&m_CS_SqlDataProcess);

			delete pSDP;
			Sleep(1);
		}


/*
		EnterCriticalSection( &m_CS_SqlData );
		pSDP = (SQLDATAPACKET *)RecvSqlData.RemoveHead();
		nSqlDataCount = RecvSqlData.GetCount();
		LeaveCriticalSection( &m_CS_SqlData );

		if ( pSDP == NULL ) continue;

	
		pUser = g_pUserList->GetUserUid(pSDP->UID);
		if ( pUser == NULL )
		{
			delete pSDP;
			Sleep(1);
			continue;
		}

		if (  pUser->m_SockFlag != 1 )
		{
			delete pSDP;
			Sleep(1);
			continue;
		}

		EnterCriticalSection(&m_CS_SqlDataProcess);
		switch(pSDP->code)
		{
		case NEW_CHAR_REQ_WITH_THREAD:
			pUser->NewCharReq((TCHAR *)pSDP->pData);
			break;
		case GUILD_OPEN_REQ:
			pUser->NewGuild((TCHAR *)pSDP->pData);
			break;
		case DEL_GUILD_CHAR_REQ:
			pUser->DeleteGuildUser((TCHAR *)pSDP->pData);
			break;
		case GUILD_KICK_OUT:
			pUser->GuildKickOut((TCHAR *)pSDP->pData);
			break;
		case GUILD_MARK_ADD_REQ:
			pUser->GuildMarkAddReq((TCHAR *)pSDP->pData);
			break;
		case GUILD_INVITE_USER_REQ:
			pUser->GuildInvite((TCHAR *)pSDP->pData);
			break;
		case GUILD_OFF_WITH_THREAD:
			pUser->GuildOff((TCHAR *)pSDP->pData);
			break;
		case GUILD_DISPERSE:
			pUser->GuildDisperse((TCHAR *)pSDP->pData);
			break;
		case DELETE_CHAR_REQ:
			pUser->DeleteCharReq((TCHAR *)pSDP->pData);
			break;

		case BBS_DELETE:
			pUser->BBSDelete((TCHAR *)pSDP->pData);
			break;
		case BBS_EDIT:
			pUser->BBSEdit((TCHAR *)pSDP->pData);
			break;
		case BBS_WRITE:
			pUser->BBSWrite((TCHAR *)pSDP->pData);
			break;
		case BBS_NEXT:
			pUser->BBSNext((TCHAR *)pSDP->pData);
			break;
		case BBS_READ:
			pUser->BBSRead((TCHAR *)pSDP->pData);
			break;
		case DB_GUILD_ITEM_MOVE_REQ:
			pUser->GuildItemMoveReq((TCHAR *)pSDP->pData);
			break;
		case DB_GUILD_WHEREHOUSE_EVENT_REQ:
			pUser->GuildWharehouseOpenReq();
			break;
		case DB_USER_COUNT:
			{
				COM *pCom = g_pMainDlg->GetCOM();
				if ( pCom )
				{
					pCom->UpdateUserCount();
				}
			}
			break;
		};
		LeaveCriticalSection(&m_CS_SqlDataProcess);

		delete pSDP;
		Sleep(1);
*/
	}

	return 0;
}

UINT WorkerFortressThread( void *lp )
{
	FORTRESSDATAPACKET *pSDP;
	CPtrList LocalData;
	int nLocalDataCount = 0;

	for (;;)
	{
		if ( nFortressDataCount < 1 )
		{
			Sleep(1);
			continue;
		}


		EnterCriticalSection( &m_CS_FortressData );

		while( nFortressDataCount >= 1 )
		{
			pSDP = (FORTRESSDATAPACKET *)RecvFortressData.RemoveHead();
			nFortressDataCount = RecvFortressData.GetCount();

			LocalData.AddTail( pSDP );
		}

		LeaveCriticalSection( &m_CS_FortressData );

		nLocalDataCount = LocalData.GetCount();

		while( nLocalDataCount >= 1 )
		{
			pSDP = (FORTRESSDATAPACKET*)LocalData.RemoveHead();
			nLocalDataCount = LocalData.GetCount();

			if ( pSDP == NULL ) continue;

			CString strMsg = _T("");

			USER *pUser = NULL;
			CGuildFortress *pFort = NULL;

			int type = 0, i=0, mapindex = 0;

			if(pSDP->sFortressIndex < 0 || pSDP->sFortressIndex >= g_arGuildFortress.GetSize())
			{
				delete pSDP;
				Sleep(1);
				continue;
			}

			pFort = g_arGuildFortress[pSDP->sFortressIndex];

			if(!pFort)
			{
				delete pSDP;
				Sleep(1);
				continue;
			}

			if(pFort->m_lUsed != 1)			// 공성전이 아니면..잘못된 정보임
			{
				delete pSDP;
				Sleep(1);
				continue;
			}

			strMsg.Format( IDS_USER_GET_FORTRESS_SUCCESS, pSDP->FORTRESS );

			for(i = 0; i < MAX_USER; i++)
			{
				pUser = g_pUserList->GetUserUid(i);
				if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) continue;
				
				if (  pUser->m_SockFlag == 1 )
				{
					type = pUser->CheckInvalidMapType();
					mapindex = pUser->GetGuildMapIndex(type);
					if(mapindex > -1)
					{												//길드전이 일어나는 상점지역이면
						if(pFort->m_iZone == pUser->m_curz)
						{
							if(pFort->m_iGuildSid != pUser->m_dwGuild && pUser->m_tIsOP != 1 )	pUser->TownPotal();				
							pUser->SendSystemMsg((LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE, TO_ME);
						}
						else if(g_arMapTable[mapindex]->m_sStoreID == pFort->m_sFortressID)		
						{											// 방어길드원이 아니면 모두 마을로	
							if(pFort->m_iGuildSid != pUser->m_dwGuild && pUser->m_tIsOP != 1 )	pUser->TownPotal();	
							pUser->SendSystemMsg((LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE, TO_ME);
						}
						else if(pUser->m_curz == 1) //일반 필드면 일단 보낸다
						{
							pUser->SendSystemMsg((LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE, TO_ME);
						}
					}
				}
			}
/*
//			EnterCriticalSection(&m_CS_SqlDataProcess);
			switch(pSDP->code)
			{
				default:
					break;
			};
//			LeaveCriticalSection(&m_CS_SqlDataProcess);
*/
			delete pSDP;
			Sleep(1);
		}
	}

	return 0;
}

void CServerDlg::InitThreads()
{
	int i;
	//DWORD nid;
	//unsigned int nid;

	// AUTOMATA THREAD...
	for ( i = 0; i < AUTOMATA_THREAD; i++ )
		m_ThreadNo[i] = i;

	// 로그인 스레드 생성...
	//m_hLoginThread = ::CreateThread( NULL, 0, WorkerLoginThread, (LPVOID)this, 0, &nid);
	//m_hLoginThread = (HANDLE)_beginthreadex( NULL, 0, &WorkerLoginThread, (LPVOID)this, 0, &nid);
	m_hLoginThread = AfxBeginThread( WorkerLoginThread, (LPVOID)this );

	// 로그아웃  스레드 생성...
	//m_hLogoutThread = ::CreateThread( NULL, 0, WorkerLogoutThread, (LPVOID)this, 0, &nid);
	//m_hLogoutThread = (HANDLE)_beginthreadex( NULL, 0, &WorkerLogoutThread, (LPVOID)this, 0, &nid);
	m_hLogoutThread = AfxBeginThread( WorkerLogoutThread, (LPVOID)this );

	// SQL 문 처리 스레드...
	//m_hSqlThread = (HANDLE)_beginthreadex( NULL, 0, &WorkerSQLThread, (LPVOID)this, 0, &nid);
	m_hSqlThread = AfxBeginThread( WorkerSQLThread, (LPVOID)this );

	m_hFortressThread = AfxBeginThread( WorkerFortressThread, (LPVOID)this );

	// 채팅 스레드 생성...
	for ( i = 0; i < AUTOMATA_THREAD; i++ )
	{
		//m_ctThread[i] = ::CreateThread( NULL, 0, WorkerChatThread, (LPVOID)&m_ThreadNo[i], CREATE_SUSPENDED, &nid );
		//m_ctThread[i] = (HANDLE)_beginthreadex( NULL, 0, &WorkerChatThread, (LPVOID)&m_ThreadNo[i], CREATE_SUSPENDED, &nid );
		m_ctThread[i] = AfxBeginThread( WorkerChatThread, (LPVOID)&m_ThreadNo[i] );

		//::SetThreadPriority( m_amThread[i], THREAD_PRIORITY_ABOVE_NORMAL );
	}

	//for ( i = 0; i < AUTOMATA_THREAD; i++ )
	//{
	//	ResumeThread( m_ctThread[i]  );
	//}
}

void CServerDlg::UserFree(int uid)
{
	USER *pUser = NULL;

	pUser = g_pUserList->GetUserUid(uid);
	if ( pUser )
	{
		g_pUserList->FreeUser( uid );
		m_CurUserCount--;
	}
}

/*
void CServerDlg::SetAliveSignalFill()
{


	long curtick = GetTickCount();

	for ( int i = 0; i < MAX_USER; i++ )
	{
		pUser = m_Com.GetUserUid(i);

		if ( pUser && pUser->m_SockFlag == 1 )
		{
			// 시간 스탬프 갱신하기...
			long useruid = pUser->m_Sid;
			g_pUQM->m_pResources->SetTimeStamp( useruid, curtick );
		}
	}
}
*/

void CServerDlg::SetAliveSignalFill()
{
	long curtick = GetTickCount();

	for ( int i = 0; i < MAX_USER; i++ )
	{
		if ( g_pUQM->m_pResources->IsFree( i ) == true )
			continue;

		if ( g_pUserList->GetUserUid(i) == NULL )
		{
			g_pUQM->m_pResources->SetFree( i );
			g_pUQM->AddResource(i);
			continue;
		}

		USER *pUser = (USER*)g_pUQM->m_pResources->GetDataValue( i );
		if ( pUser && pUser->m_state != STATE_GAMESTARTED )
		{
			if ( pUser->m_ConnectionSuccessTick == 0 ) continue;
			if ( curtick - pUser->m_ConnectionSuccessTick > 30 * 60 * 1000 )
				pUser->SoftClose();
		}
	}

}

//DWORD WINAPI WorkerChatThread(LPVOID lp )
//unsigned __stdcall WorkerChatThread( void *lp )
UINT WorkerChatThread( void *lp )
{
	long *thno;
	int nThreadNo = 0;
	CServerDlg *pMainDlg = g_pMainDlg;
	thno = (long *)lp;
	nThreadNo = *thno;

	TRACE("ChatThread Started [%d]...\n", nThreadNo );

	CPtrList LocalRecvPtrList;
	int nLocalRecvDataLength = 0;
	int tail;
	CHATDATAPACKET *pCDP;

	// 스레드 메인 루틴...
	for (;;)
	{
		if (g_nChatDataHead[nThreadNo] == g_nChatDataTail[nThreadNo] )
		{
			Sleep(1);
			continue;
		}
		tail = g_nChatDataTail[nThreadNo];

		pCDP = g_WaitRecvDataChat[tail][nThreadNo];
		if ( pCDP == NULL )
		{
			tail++;
			tail %= DATA_BUF_SIZE_FOR_THREAD;
			g_nChatDataTail[nThreadNo] = tail;
			continue;
		}

		USER *pUser = NULL;
		pUser = g_pUserList->GetUserUid(pCDP->UID);
		if ( pUser == NULL )
		{
			g_WaitRecvDataChat[tail][nThreadNo] = NULL;

			delete pCDP;

			tail++;
			tail %= DATA_BUF_SIZE_FOR_THREAD;
			g_nChatDataTail[nThreadNo] = tail;
			continue;
		}

		if ( pUser->m_SockFlag == 1 )
		{
			switch(pCDP->code)
			{
			case CHAT_REQ:
				pUser->ChatReqWithLength((char *)pCDP->pData, pCDP->dcount);// >ChatReq((char *)pCDP->pData);
				break;
			}
		}

		delete pCDP;
		g_WaitRecvDataChat[tail][nThreadNo] = NULL;

		tail++;
		tail %= DATA_BUF_SIZE_FOR_THREAD;
		g_nChatDataTail[nThreadNo] = tail;
	}

	return 0;
}

CSSocket* CServerDlg::GetServerSocket( CIOCPBASE *pIocpBase )
{
	const RHANDLE* pHandle = 0;
	CSSocket *pSocket;
	int sid;

	pHandle = 0; sid = -1;

	DWORD ret = g_pSQM->GetFreeResource(&pHandle);
	if ( ret == 0 )
	{
		sid = pHandle->pos;
		pSocket = (CSSocket *)pHandle->handle;
	}		
	else
	{
		return NULL;
	}

	pSocket->m_pIocpBase = pIocpBase;
	pSocket->m_Sid = sid;
	pSocket->m_SNumber = sid;
	pSocket->m_State = STATE_ACCEPTED;
	pSocket->m_RecvOverlap.hEvent = NULL;
	pSocket->m_SendOverlap.hEvent = NULL;

	return pSocket;
}

BOOL CServerDlg::DBSocketConnect()
{
	if ( m_pDBSocket == NULL )
	{
		m_pDBSocket = GetServerSocket( &m_ServerBase );
		m_pDBSocket->m_ReConnectFlag = TRUE;
	}

	if ( !m_pDBSocket->m_ReConnectFlag )
	{
		return FALSE;
	}

	if ( !m_pDBSocket->Create() )
	{
		m_pDBSocket->SoftClose();
		return FALSE; 
	}

	if ( !m_pDBSocket->Connect(m_DBAddr, m_nDBPort) )
	{
		m_pDBSocket->SoftClose();
		return FALSE;
	}

	m_pDBSocket->Init();
	m_pDBSocket->m_ReConnectFlag = FALSE;
	m_pDBSocket->m_Type = SOCKET_FOR_DBSERVER;

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////
// JJS
BOOL CServerDlg::ZoneSocketConnect()
{
	if ( m_pBridgeSocket == NULL )
	{
		m_pBridgeSocket = GetServerSocket( &m_ServerBase );
		m_pBridgeSocket->m_ReConnectFlag = TRUE;
	}

	if ( !m_pBridgeSocket->m_ReConnectFlag )
	{
		return FALSE;
	}

	if ( !m_pBridgeSocket->Create() )
	{
		m_pBridgeSocket->SoftClose();
		return FALSE; 
	}

	if ( !m_pBridgeSocket->Connect(m_strZoneAddr, USER_SOCKET_PORT) )
	{
		m_pBridgeSocket->SoftClose();
		return FALSE;
	}

	m_pBridgeSocket->Init();
	m_pBridgeSocket->m_ReConnectFlag = FALSE;
	m_pBridgeSocket->m_Type = SOCKET_FOR_SERVER;

	return TRUE;
}

void CServerDlg::DBAccountLoginResult(char *pBuf, int index, int length )
{
	int uid;

	uid = GetShort(pBuf,index);
	if ( uid < 0 || uid >= MAX_USER )
		return;

	USER *pUser = m_Com.GetUserUid( uid );
	if ( pUser == NULL ) return;

	pUser->DBAccountLoginResult( pBuf, index, length );

}

void CServerDlg::DBGameStartResult( char *pBuf, int index, int length )
{
	int uid;
	char szID[CHAR_NAME_LENGTH+1];
	char pTempBuf[RECEIVE_BUF_SIZE+1];

	uid = GetShort(pBuf,index);
	if ( uid < 0 || uid >= MAX_USER )
		return;

	USER *pUser = m_Com.GetUserUid( uid );
	if ( pUser == NULL ) return;

	memset( szID, NULL, sizeof(szID) );

	int comp_data_len;
	int org_data_len, extracted_data_count;
	DWORD crc_value, cm_crc_value;
	char *pcaket_data_buffer, *extract_buf_ptr;

	// 데이타 압축풀기 시작...
	pUser->m_CompMng.FlushAddData();

	// 압축된 데이타길이얻기...
	comp_data_len = GetShort( pBuf, index );

	// 원래데이타길이얻기...
	org_data_len = GetShort( pBuf, index );

	// CRC값 얻기...
	crc_value = GetDWORD( pBuf, index );

	// 압축 데이타 얻기...
	GetString( pTempBuf, pBuf, comp_data_len, index );

	// 압축 풀기... 
	pUser->m_CompMng.PreUncompressWork( comp_data_len, org_data_len );

	pcaket_data_buffer = pUser->m_CompMng.GetCompressionBufferPtr();
	memcpy( pcaket_data_buffer , pTempBuf, comp_data_len ); 

	// 풀기...
	if ( pUser->m_CompMng.Extract() == false )
	{
		pUser->m_CompMng.FlushExtractedData();
		// 예기치 못한 에러...
		pUser->SoftClose();
		return;
	}

	// 에러 채크...
	if ( pUser->m_CompMng.ErrorOccurred != 0 )
	{
		pUser->m_CompMng.FlushExtractedData();
		// 예기치 못한 에러...
		pUser->SoftClose();
		return; 
	}

	cm_crc_value = pUser->m_CompMng.GetCrcValue();
	if ( crc_value != cm_crc_value )
	{
		pUser->m_CompMng.FlushExtractedData();
		// 예기치 못한 에러...
		pUser->SoftClose();
		return;
	}

	extracted_data_count = pUser->m_CompMng.GetExtractedDataCount();
	if ( org_data_len != extracted_data_count )
	{
		pUser->m_CompMng.FlushExtractedData();
		// 예기치 못한 에러...
		pUser->SoftClose();
		return;
	}
	//
	extract_buf_ptr = pUser->m_CompMng.GetExtractedBufferPtr();
	memcpy( pTempBuf, extract_buf_ptr, extracted_data_count );

	// 사용 끝. 버퍼 초기화...
	pUser->m_CompMng.FlushExtractedData();

	int uc_index = 0;
	GetString( szID, pTempBuf, CHAR_NAME_LENGTH, uc_index );
	if (strcmp( szID, pUser->m_strUserID ) != 0 )
	{
		// 예기치 못한 에러...
		pUser->SoftClose();
		return; 
	}

	pUser->DBGameStartResult( pTempBuf, uc_index, length );

}

void CServerDlg::DBjobPhasor( CSSocket* pServerSock, char *pTBuf, int length )
{
	char pBuf[RECEIVE_BUF_SIZE+1];

	memcpy( pBuf, pTBuf, length );

	int index = 0;
	BYTE byte = pBuf[index++];

	switch ( byte )
	{
	case DB_SERVER_IN_RES:
		{
			short serverid;
			serverid = GetShort(pBuf, index);
		}
		break;

	case ACCOUNT_LOGIN_RESULT:
		DBAccountLoginResult(pBuf, index, length );
		break;

	case GAME_START_RESULT:
		DBGameStartResult(pBuf, index, length );
		break;
	};	
}

void CServerDlg::Send2DBsvr( TCHAR *pBuf, int length )
{
	if ( m_pDBSocket )
		m_pDBSocket->Send( pBuf, length );
}

//-----------------------------------------------------------------------------
// CALLBACK FUNCTION...
//
DWORD WorkerServerThread(LPVOID lp )
{
	WAIT_RECV_DATA *wrd = (WAIT_RECV_DATA *)lp;
	CSSocket *pSocket;

	if ( wrd == NULL ) return 0;

	// IKING 2000.1.
	// 내부 프로그램 메시지 처리...
	if ( wrd->m_Type == SOCKET_FOR_APPLICATION )
	{
		TRACE("USER APPLICATION-CMP CALLED[%d]...\n",wrd->usn);

		g_pMainDlg->AutoMataAppCmd(wrd);

		return 1;
	}
	//

	if ( wrd->usn >= 0 && wrd->usn < 32767 )
	{
		pSocket = (CSSocket *)g_pSQM->m_pResources->GetDataValue( wrd->usn );
	}
	else
		return 0;

	if ( pSocket == NULL || pSocket->m_Socket == INVALID_SOCKET )
	{
		return 0;
	}

	// IKING 1999.1.
	if ( pSocket->IsSocketAlive() != TRUE )
	{
		return 0;
	}

	((CSSocket *)pSocket)->AutomataServer( (char *)wrd->pData, wrd->dcount );

	return 1;
}

DWORD WorkerUserThread(LPVOID lp )
{
	WAIT_RECV_DATA *wrd = (WAIT_RECV_DATA *)lp;
	USER *pSocket;

	if ( wrd == NULL ) return 0;

	// IKING 2000.1.
	// 내부 프로그램 메시지 처리...
	if ( wrd->m_Type == SOCKET_FOR_APPLICATION )
	{
		TRACE("USER APPLICATION-CMP CALLED[%d]...\n",wrd->usn);

		g_pMainDlg->AutoMataAppCmd(wrd);

		return 1;
	}
	//

	if ( wrd->usn >= 0 && wrd->usn < 32767 )
	{
		pSocket = (USER *)g_pUQM->m_pResources->GetDataValue( wrd->usn );
	}
	else
		return 0;

	if ( pSocket == NULL || pSocket->m_Socket == INVALID_SOCKET )
	{
		return 0;
	}

	// IKING 1999.1.
	if ( pSocket->IsSocketAlive() != TRUE )
	{
		return 0;
	}

	g_ThreadAliveTime[pSocket->m_iModSid] = GetTickCount();

	pSocket->ProcessData((char *)wrd->pData, wrd->dcount);

	return 1;
}
