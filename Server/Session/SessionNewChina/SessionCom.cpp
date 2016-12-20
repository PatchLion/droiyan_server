// SessionCom.cpp: implementation of the CSessionCom class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Session.h"
#include "SessionCom.h"

#include "LogSet.h"
#include "SerialSet.h"
#include "UserSet.h"
#include "SerialKey.h"
#include "BankSerial.h"
#include "..\\include\\UMProtocol.h"
#include "..\\include\\packetdef.h"
#include "UserManager.h"
#include "UResourceArray.h"
#include "Mcommon.h"
#include "UserServerManager.h"
#include "SocketManager.h"
#include "Iocp.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSessDesc* GetUserSocketUid( int uid );
CSessDesc* GetServerSocket( CIOCPBASE *pIocpBase );


#define ERROR_CANCEL		(ERROR_USER + 0)
#define ERROR_EXTERNAL		(ERROR_USER + 1)
#define ERROR_DUPLICATE		(ERROR_USER + 2)
#define ERROR_UMIDENTIFY	(ERROR_USER + 3)

#define UM_SESSION_ALIVE_REQ			(UMPROTOCOL + 0x0F0)


extern int NUMSTARTRESOURCES_USER;		// Number of handles to start with

extern CSocketManager *g_pSQM;
extern CUserManager *g_pUQM;
extern CUserServerManager *g_pUSQM;

extern CIOCP<CSessDesc> m_ServerBase;
extern CIOCP<CSessDesc> m_UserBase;

char ExeFilePath[_MAX_PATH];
void DisplayDBError(CString header, SQLHSTMT hstmt);

extern CP_IP_TableArray		g_arCP_IP_Table;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSessionCom::CSessionCom(LPCTSTR lpszServerName) :
CBaseCom (lpszServerName)
{
	m_pDesUM = NULL;
	m_pDesGS = NULL;

	m_bServiceStartFlag = FALSE;
	m_bServiceContinueFlag = FALSE;

	InitializeCriticalSection(&m_CS_db);
}

CSessionCom::~CSessionCom()
{
	DeleteCriticalSection(&m_CS_db);

	for(int i = 0; i < g_arCP_IP_Table.GetSize(); i++)
	{
		if(g_arCP_IP_Table[i]) 
		{
			delete g_arCP_IP_Table[i];
			g_arCP_IP_Table[i] = NULL;
		}
	}
	g_arCP_IP_Table.RemoveAll();
}

BOOL CSessionCom::Process()
{
	return CBaseCom::Process ();
}

void CSessionCom::OnPauseService()
{
	m_bServiceContinueFlag = FALSE;

	if ( m_pDesUM && m_pDesUM->m_bConnectFlag == TRUE )
		m_pDesUM->SoftClose();
	//m_pDesUM->m_bConnectFlag = FALSE;

	if ( m_pDesGS && m_pDesGS->m_bConnectFlag == TRUE )
		m_pDesGS->SoftClose();
	//m_pDesGS->m_bConnectFlag = FALSE;

	CBaseCom::OnPauseService ();
}

BOOL CSessionCom::OnContinueService()
{
	if ( m_bServiceContinueFlag == TRUE ) return TRUE;
	m_bServiceContinueFlag = TRUE;

	if (!CBaseCom::OnContinueService ())
		return FALSE;

	if (!GetConfigString (NULL, _T("ServName"), m_strServName))
		return FALSE;

	if (!GetConfigInt (NULL, _T("Pay"), m_fPay))
		return FALSE;

	if (!ConnectUM ())
		return FALSE;

	LoadFilterAddress ();

	m_fSuspend = TRUE;

	return TRUE;
}

//-------------------------------------------------------------------
//·Î±× ÀüºÎ »èÁ¦
void CSessionCom::OnStopService()
{
	m_bServiceStartFlag = FALSE;

	for (int i = 0; i < AUTOMATA_THREAD2+1; i++ )
	{
		if ( m_db[i].IsOpen () )
		{
			CLogSet logset (&m_db[i]);
			logset.m_nServiceID = m_nServerID;
			logset.Initialize();

			m_db[i].Close ();
		}
	}

	if ( m_pDesUM && m_pDesUM->m_bConnectFlag == TRUE )
		m_pDesUM->SoftClose();
	//m_pDesUM->m_bConnectFlag = FALSE;

	if ( m_pDesGS && m_pDesGS->m_bConnectFlag == TRUE )
		m_pDesGS->SoftClose();
	//m_pDesGS->m_bConnectFlag = FALSE;

	CBaseCom::OnStopService ();
}

BOOL CSessionCom::OnStartService()
{
	if ( m_bServiceStartFlag == TRUE ) return TRUE;
	m_bServiceStartFlag = TRUE;

	if (!CBaseCom::OnStartService ())
		return FALSE;

	CString strConnect;

	//strConnect.Format (_T("DSN=%s;UID=%s;PWD=%s"), 
	//	m_strGameID, m_strGameID, m_strGameID);

	strConnect.Format (_T("DSN=%s;UID=%s;PWD=%s"), 
		m_strGameID, m_strUserID, m_strPassword);

//
	for (int i = 0 ; i < AUTOMATA_THREAD2+1; i++ )
	{
		if( !m_db[i].Open(strConnect) )
		{
			#ifdef _DEBUG
			AfxMessageBox("m_db.open");
			#endif
			return FALSE;
		}

		CLogSet logset(&m_db[i]);
		logset.m_nServiceID = m_nServerID;
		logset.Initialize ();
	}

	CLogSet logset(&m_db[0]);

	if( !logset.GetGameRoomInfo() )
	{
#ifdef _DEBUG
		AfxMessageBox("Telecom Load Fail");
#endif
		return FALSE;
	}

	if (!GetConfigString (NULL, _T("ServName"), m_strServName))
	{
#ifdef _DEBUG
		AfxMessageBox("SERVNAME");
#endif
		return FALSE;
	}

	if (!GetConfigInt (NULL, _T("Pay"), m_fPay))
		return FALSE;

	if (!ConnectUM ())
	{
#ifdef _DEBUG
		AfxMessageBox("CONNECTUM");
#endif
		return FALSE;
	}

	LoadFilterAddress ();

	// ¼­¹ö ÀÌ¸§ ÃÊ±âÈ­...
	m_nGameServers = 1;
	m_ServerNames[0] = "Æ÷¼¼ÀÌµ·";
	m_ServerNames[1] = "¸Ó¸°";
	m_ServerNames[2] = "±â³×ºñ¾Æ";
	m_ServerNames[3] = "LANCELOT";
	m_ServerNames[4] = "GALAHAD";
	m_ServerNames[5] = "GAWAIN";
	m_ServerNames[6] = "EXCALIBUR";
	//

	m_fSuspend = FALSE;

	return TRUE;
}

void CSessionCom::OnTimer ()
{
	CBaseCom::OnTimer ();
}

BOOL CSessionCom::OnOpenSession (CSessDesc* pDes)
{
	if (!CBaseCom::OnOpenSession (pDes))
		return FALSE;

	pDes->m_strUserID = _T("");

	struct sockaddr_in client_addr;
	int nLen = sizeof (client_addr);
	getpeername (pDes->m_Socket, (struct sockaddr *)&client_addr, &nLen);
	pDes->m_strIPAddr = inet_ntoa (client_addr.sin_addr);

	if (!CheckFilterAddress (pDes->m_strIPAddr))
		return FALSE;
	return TRUE;
}

void CSessionCom::OnCloseSession (CSessDesc* pDes, int nCode)
{
	if ( pDes == NULL ) return;

	if (pDes == m_pDesUM)
	{
		if ( m_pDesUM && m_pDesUM->m_bConnectFlag == TRUE )
			m_pDesUM->SoftClose();

		//m_pDesUM->m_bConnectFlag = FALSE;

		m_fSuspend = TRUE;
	}
	else if (pDes == m_pDesGS)
	{
		if ( m_pDesGS && m_pDesGS->m_bConnectFlag == TRUE )
			m_pDesGS->SoftClose();

		//m_pDesGS->m_bConnectFlag = FALSE;

		m_fSuspend = TRUE;
	}
	else
	{
		CMsg msgSend;
		BYTE bReason = DR_NORMAL;
		switch (nCode)
		{
		case ERROR_DUPLICATE	:
			bReason = DR_DUPLICATE;
			break;
		case ERROR_EXTERNAL		:
			bReason = DR_CANCEL;
			break;
		case ERROR_CLIENTSEND	:
		case ERROR_CLIENTRECV	:
			bReason = DR_CLIENT;
			break;
		case ERROR_SERVERSEND	:
		case ERROR_SERVERRECV	:
			if ( pDes->GetState () == CSessDesc::stateDown )
			{
				pDes->Unlink();

				msgSend.ID(FM_ENDDOWN_ACK);
				pDes->Say(msgSend);
				return;
			}
			else if (pDes->GetState () == CSessDesc::stateGame)
			{
				pDes->Unlink();

				msgSend.ID(SM_DIR_REQ) 
						<< pDes->m_Sid
						<< pDes->m_strUserID 
						<< (BYTE)0
						<< pDes->m_vServerNumber;

				if ( m_pDesGS && m_pDesGS->m_bConnectFlag == TRUE )
					m_pDesGS->Say(msgSend);
				return;
			}
			break;
		case ERROR_RECVTIMEOUT	:
			bReason = DR_TIMEOUT;
			break;
		case ERROR_UNLINK		:
			bReason = DR_LINK;
			break;
		case ERROR_SUSPEND :
			CBaseCom::OnCloseSession (pDes, nCode);
			return;
		}

		if (pDes->m_strUserID != _T(""))
		{
			if(pDes->m_iLoginFlag == 1)
			{
				CLogSet logset(&m_db[pDes->m_iSidMod]);
				logset.m_strUserID = pDes->m_strUserID;
				logset.m_bReason = bReason;

				int nRet = logset.Logout();
				switch ( nRet )
				{
					case 0 :
						//TRACE("[%s] Logout Success...\n", pDes->m_strUserID );
						break;
					case 1 :
						TRACE("User[%s] Not Logged In...\n", pDes->m_strUserID );
						break;
					default :
						TRACE("[%s] : Unknown error...\n", pDes->m_strUserID );
						break;
				}
			}
		}
/*
		if (pDes->m_strUserID != _T(""))
		{
			if ( pDes->m_bLogOutFlag == FALSE )
			{
				pDes->m_bLogOutFlag = TRUE;

				CLogSet logset(&m_db[pDes->m_iSidMod]);
				logset.m_strUserID = pDes->m_strUserID;
				logset.m_bReason = bReason;

				int nRet = logset.Logout();
				switch ( nRet )
				{
					case 0 :
						//TRACE("[%s] Logout Success...\n", pDes->m_strUserID );
						break;
					case 1 :
						TRACE("User[%s] Not Logged In...\n", pDes->m_strUserID );
						break;
					default :
						TRACE("[%s] : Unknown error...\n", pDes->m_strUserID );
						break;
				}
			}
		}
*/

		//if ( nCode == ERROR_UNLINK && pDes->GetState () == CSessDesc::stateDown )
		if ( bReason == DR_CLIENT && pDes->GetState () == CSessDesc::stateDown )
		{
			pDes->Unlink();

			msgSend.ID(FM_ENDDOWN_ACK);
			pDes->Say(msgSend);

			Sleep(1);
		}
		else
		{
#ifndef _INTERNET_USAGE
			if ( pDes->m_LinkedFlag == 1 )
				pDes->Unlink();
#endif			
			CBaseCom::OnCloseSession (pDes, nCode);
		}
	}
}

void CSessionCom::OnDupCloseSession(CSessDesc* pDes, int nCode)
{
	if ( pDes == NULL ) return;

	CMsg msgSend;
	BYTE bReason = DR_NORMAL;
	switch (nCode)
	{
	case ERROR_DUPLICATE	:
		bReason = DR_DUPLICATE;
		break;
	case ERROR_EXTERNAL		:
		bReason = DR_CANCEL;
		break;
	case ERROR_CLIENTSEND	:
	case ERROR_CLIENTRECV	:
		bReason = DR_CLIENT;
		break;
	case ERROR_SERVERSEND	:
	case ERROR_SERVERRECV	:
		if ( pDes->GetState () == CSessDesc::stateDown )
		{
			pDes->Unlink();

			msgSend.ID(FM_ENDDOWN_ACK);
			pDes->Say(msgSend);
			return;
		}
		else if (pDes->GetState () == CSessDesc::stateGame)
		{
			pDes->Unlink();

			msgSend.ID(SM_DIR_REQ) 
					<< pDes->m_Sid
					<< pDes->m_strUserID 
					<< (BYTE)0
					<< pDes->m_vServerNumber;

			if ( m_pDesGS && m_pDesGS->m_bConnectFlag == TRUE )
				m_pDesGS->Say(msgSend);

			return;
		}
		break;
	case ERROR_RECVTIMEOUT	:
		bReason = DR_TIMEOUT;
		break;
	case ERROR_UNLINK		:
		bReason = DR_LINK;
		break;
	case ERROR_SUSPEND :
		CBaseCom::OnCloseSession(pDes, nCode);
		return;
	}

	if (pDes->m_strUserID != _T(""))
	{
		if ( pDes->m_bLogOutFlag == FALSE )
		{
			pDes->m_bLogOutFlag = TRUE;
/*
			EnterCriticalSection(&m_CS_db);
			CLogSet logset(&m_db[AUTOMATA_THREAD]);
			logset.m_strUserID = pDes->m_strUserID;
			logset.m_bReason = bReason;

			int nRet = logset.Logout();
			LeaveCriticalSection(&m_CS_db);

			switch ( nRet )
			{
				case 0 :
					//TRACE("[%s] Logout Success...\n", pDes->m_strUserID );
					break;
				case 1 :
					TRACE("User[%s] Not Logged In...\n", pDes->m_strUserID );
					break;
				default :
					TRACE("[%s] : Unknown error...\n", pDes->m_strUserID );
					break;
			}
*/		}
	}

	if ( bReason == DR_CLIENT && pDes->GetState () == CSessDesc::stateDown )
	{
		pDes->Unlink();

		msgSend.ID(FM_ENDDOWN_ACK);
		pDes->Say(msgSend);
	}
	else
	{
#ifndef _INTERNET_USAGE
		if ( pDes->m_LinkedFlag == 1 )
			pDes->Unlink();
#endif			
		CBaseCom::OnCloseSession(pDes, nCode);
	}
}

int CSessionCom::OnReceiveMsg(CSessDesc* pDes, CMsg& msg)
{
	switch (msg.ID ())
	{
	case 0						: 
		{
			int nofcount;

			nofcount = ((CUserResourceArray *)(g_pUQM->m_pResources))->GetUsedResourceCount();
			CMsg msgSend;
			msgSend.ID (0) 
				<< (BYTE)m_fSuspend
				<< nofcount;
			pDes->Say (msgSend);
		}
		return 0;

		// Session Message Process
	case SM_CHANGEPASSWD_REQ	: return OnSMChangePasswdReq(pDes, msg);
	case SM_IDEXIST_REQ			: return OnSMIDExistReq(pDes, msg);
	case SM_GAMEINFO_REQ		: return OnSMGameInfoReq(pDes, msg);
	case SM_GAMEINFO2_REQ		: return OnSMGameInfo2Req (pDes, msg);
	case SM_LOGIN_REQ			: return OnSMLoginReq(pDes, msg);
	case SM_REGUSER_REQ			: return OnSMRegUserReq(pDes, msg);		
	case SM_GETINFO_REQ			: return OnSMGetInfoReq(pDes, msg);
	case SM_SETINFO_REQ			: return OnSMSetInfoReq(pDes, msg);
	case SM_REGSN_REQ			: return OnSMRegSNReq(pDes, msg);
	case SM_DOWN_REQ			: return OnSMDownReq(pDes, msg);
	case SM_GAME_REQ			: return OnSMGameReq(pDes, msg);
	case SM_UPGRADING_ACK		: return OnSMUpgradingAck (pDes, msg);

	// IKING 1999.1.
	case SM_GAMEEND_REQ			: return OnSMGameEndReq (pDes, msg);
	case SM_RECONNECT_REQ		: return OnSMReconnectReq (pDes, msg);
	//
	// User Manager Process
	case UM_IDENTIFY_ACK		: return OnUMIdentifyAck (msg);
	case UM_REIDENTIFY_ACK		: return OnUMReIdentifyAck (msg);
	case UM_KICKOUT_ACK			: return OnUMKickoutAck (msg);
	case UM_CURSTATUS_ACK		: return OnUMCurStatusAck(msg);
	case UM_CURSTATUS1_ACK		: return OnUMCurStatus1Ack(msg);
	// Helper Message Process
	case SM_DIR_ACK				: return OnSMDirAck(msg);

	case SM_GAMESERVER_CONNECT_REQ: return OnSMGameConnectionReq(pDes, msg);
	case SM_ALIVE_ACK			: 
		{
			if ( pDes->m_Type == SOCKET_FOR_USER )
			{
				if ( pDes->m_SockFlag != 1 ) break;

				pDes->m_dwLastTime = ::GetTickCount();

				// Å¬¶óÀÌ¾ðÆ® ½Ã°£ ¼¼ÆÃ ÇÏ±â..
				g_pUQM->m_pResources->SetTimeStamp( pDes->m_Sid );

				// ¼­¹öÃø ¿¬°á ½Ã°£ ¾÷µ¥ÀÌÆ® ÇÏ±â...
				if ( pDes->m_nLinkedSid >= 0 )
				{
					if ( pDes->pLinkedDesc )
						g_pUSQM->m_pResources->SetTimeStamp( pDes->pLinkedDesc->m_Sid );
				}
			}
			else if ( pDes->m_Type == SOCKET_FOR_SERVER )
			{
				if ( pDes->m_SockFlag != 1 ) break;

				g_pSQM->m_pResources->SetTimeStamp( pDes->m_Sid );
			}
			return 0;
		}
	}

	return 0;
}

// Session Message Handler Functions
int CSessionCom::OnSMIDExistReq(CSessDesc *pDes, CMsg& msg)
{
	CString strUserID;
	msg >> strUserID;

	BYTE result;
	CMsg t_msg;
	if (strUserID == _T(""))
		return ERROR_CANCEL;

	if(strUserID.FindOneOf("\\/;*?\"<>|") != -1)
	{
		result = 1;
	}
	else {
		CUserSet userset(&m_db[pDes->m_iSidMod]);
		userset.m_strUserID = strUserID;

		if (userset.GetUser())
		{
			result = 1;
		}
		else
		{
			result = 0;
		}
	}

	t_msg.ID(SM_IDEXIST_ACK) << result;
	pDes->Say(t_msg);

	return 0;
}

int CSessionCom::OnSMLoginReq(CSessDesc * pDes, CMsg & msg)
{
	BYTE nRet = 1;

	CString strNicAddress;
	CString strUserID, strPasswd, strSerial1, strSerial2;
	//msg >> strUserID 
	//	>> strPasswd 
	//	>> strSerial1 
	//	>> strSerial2;

	msg >> strUserID 
		>> strPasswd
		>> strNicAddress;

	strSerial1 = _T("0"); 
	strSerial2 = _T("0");

	CMsg msgSend;

	// Ä³¸¯ÅÍÀÇ ¾ÆÀÌµð¸¦ ´ë¹®ÀÚ·Î...
	//strUserID.MakeUpper();

	// ¾ÆÀÌµð ÃÊ±âÈ­ ÇÏ±â...
	if ( pDes )
	{
		pDes->m_strUserID = strUserID;
	}

	if(CheckIDValid(strUserID) == FALSE)
	{
		msgSend.ID(SM_LOGIN_ACK)
			<< nRet;

		pDes->Say (msgSend);
	}
	else
	{
		CLogSet logset (&m_db[pDes->m_iSidMod]);
		logset.m_strUserID = strUserID;
		logset.m_strPasswd = strPasswd;
		logset.m_nServiceID = m_nServerID;
		logset.m_wSerial = CheckSerial (strSerial1, strSerial2);
		memset(logset.m_strIPAddr, 0x00, IP_LENGTH);
		memcpy(logset.m_strIPAddr, (LPTSTR)(LPCTSTR)pDes->m_strIPAddr, IP_LENGTH);
//		logset.m_strIPAddr = pDes->m_strIPAddr;
		logset.m_strNicAddr = strNicAddress;

		// 2001/07/19 Add by byun.
		BYTE nCP = 0;
		TCHAR strServerIP[IP_LENGTH]; ::memset(strServerIP, 0x00, IP_LENGTH);
		int remain_time = 0;
		BYTE tViewType = 0;
		TIMESTAMP_STRUCT time_stamp;

		time_stamp.month = 0;
		time_stamp.day = 0;

		pDes->m_bDisplay = 0;

		// nRet Define
		// 0 : Valid
		// 1 : No Account
		// 2 : No Account
		// 3 : Duplicated Connection
		// 4 : Out of date
		// 5 : Failed insert currentuser table
		// 6 : Invalid
		// 7 : Mismatch password
		// 100 : DB Open Failed

		// m_bDisplay Define
		// 1 : °³ÀÎ Á¤¾×
		// 2 : °³ÀÎ ½Ã°£
		// 3 : °×¹æ Á¤¾×
		// 4 : °×¹æ ½Ã°£
		// 5 : »õ °èÁ¤
		
		// time_stamp Define
		// ±â°£ Á¤¾×Á¦ÀÏ¶§

		nRet = logset.Login ((BYTE)m_fPay, pDes->m_bDisplay, remain_time, time_stamp, strServerIP, tViewType);
		if (nRet < 0)
			return ERROR_INVALID;

		CString strCPMsg = _T("");
		CString strCPTempMsg = _T("");

#ifdef _CHINESE_MSG

		if(pDes->m_bDisplay == 1)
		{	
			nCP = 1;
			if(time_stamp.day == 1)
			{
				strCPMsg.Format("ÄúµÄÓÎÏ·ÌìÊý¼´½«ÓÃÍê£¬ÎªÁË²»Ó°ÏìÄú½øÐÐÓÎÏ·£¬ÇëÄú½øÐÐ´¢Öµ.\n\n");
			}
			else if(time_stamp.day <= 0)
			{
				strCPMsg.Format("ÄúµÄÓÎÏ·Ê±¼äÒÑ¾­ÓÃÍê£¬Çë´¢Öµºó¼ÌÐø½øÐÐÓÎÏ·.\n\n");
			}
			else
			{
				strCPMsg.Format("ÄúÊ£ÓàµÄÓÎÏ·Ê±¼äÎª %dÌì.\n\n", remain_time);
			}
		}
		else if(pDes->m_bDisplay == 2)
		{
			nCP = 1;
			if(remain_time <= 30)
			{
				strCPMsg.Format("ÄúµÄÓÎÏ·µãÊý¼´½«ÓÃÍê£¬ÎªÁË²»Ó°ÏìÄú½øÐÐÓÎÏ·£¬ÇëÄú½øÐÐ´¢Öµ.\n\n");
			}
			else
			{
				int time = remain_time / 60;
				int min = remain_time % 60;
				strCPMsg.Format("ÄúÊ£ÓàµÄÓÎÏ·Ê±¼äÎª %dÐ¡Ê± %d·ÖÖÓ.\n\n", time, min);
			}
		}

		if(pDes->m_bDisplay == 5)
		{
			nCP = 1;
			strCPMsg.Format("ÄúµÄÃâ·ÑÊ±¼äÒÑ¾­ÓÃÍê£¬ÇëÈ¥Ö÷Ò³½øÐÐ´¢Öµ.\n\n");
		}

#else
		strCPTempMsg.Format("Àçµî·ÏÀ» ÇÏ½Ã¸é °è¼ÓÇØ¼­ µå·ÎÀÌ¾á ¿Â¶óÀÎÀ» Áñ±â½Ç¼ö ÀÖ½À´Ï´Ù.");

		if(pDes->m_bDisplay == 1)
		{	
			nCP = 1;
			strCPMsg.Format("»ç¿ëÁßÀÌ½Å °èÁ¤Àº °³ÀÎÁ¤¾×À¸·Î %d¿ù %dÀÏÈÄ¿¡´Â ±â°£ÀÌ Á¾·áÇÏ°Ô µË´Ï´Ù.\n\n", time_stamp.month, time_stamp.day);
			strCPMsg += strCPTempMsg;
		}
		else if(pDes->m_bDisplay == 2)
		{
			nCP = 1;
			strCPMsg.Format("»ç¿ëÁßÀÌ½Å °èÁ¤Àº °³ÀÎ½Ã°£À¸·Î %dºÐÈÄ Á¾·áÇÏ°Ô µË´Ï´Ù.\n\n", remain_time);
			strCPMsg += strCPTempMsg;
		}
		else if(pDes->m_bDisplay == 3)
		{
			nCP = 1;
			strCPMsg.Format("µî·ÏÇÏ½Å °ÔÀÓ¹æ IPÁÖ¼Ò´Â %d¿ù %dÀÏÈÄ¿¡ ±â°£ÀÌ Á¾·áÇÏ°Ô µË´Ï´Ù.\n\n", time_stamp.month, time_stamp.day);
			strCPMsg += strCPTempMsg;
		}
		else if(pDes->m_bDisplay == 4)
		{
			nCP = 1;
			strCPMsg.Format("µî·ÏÇÏ½Å °ÔÀÓ¹æ IPÁÖ¼Ò´Â %dºÐÈÄ Á¾·áÇÏ°Ô µË´Ï´Ù.\n\n", remain_time);
			strCPMsg += strCPTempMsg;
		}

		if(pDes->m_bDisplay == 5)
		{
			nCP = 1;
			strCPMsg.Format("»ç¿ëÁßÀÌ½Å °èÁ¤Àº ¹«·áÃ¼Çè ±â°£¹× ·¹º§ÀÌ Áö³µ½À´Ï´Ù.\n\n°è¼ÓÇØ¼­ Áñ±â½Ã·Á¸é È¨ÆäÀÌÁö¿¡¼­ °áÁ¦ÈÄ ÀÌ¿ëÇÏ¿© ÁÖ¼¼¿ä.");
		}
#endif

		switch(nRet)	
		{
		case 0:	case 3:			// ¼º°ø ÇÏ¿´À»°æ¿ì CP¿Í Notice¸¦ º¸³½´Ù.
			{
				pDes->m_strUserID = strUserID;
				pDes->m_iLoginFlag = 1;	// Å×ÀÌºí¿¡ InsertÁßÀÌ´Ù.

				if(nRet == DUPLICATED_USER)
				{
					nRet = 0;
					pDes->m_iLoginFlag = 3;		// ÀÌ¹Ì °°Àº °èÁ¤¿¡ »ç¿ëÀÚ°¡ ÀÖ´Ù.
					pDes->m_strDupIPAddr = _T("");
					pDes->m_strDupIPAddr = (LPCTSTR)strServerIP;
				}

				BYTE bNotice = 1;
				msgSend.ID(SM_LOGIN_ACK)
				<< nRet
				<< nCP;

				if(nCP == 1)
				{
					msgSend	<< strCPMsg;					
//					msgSend << (BYTE)pDes->m_bDisplay << (BYTE)time_stamp.month << (BYTE)time_stamp.day << (int)remain_time;

				}

				if(m_strNotice.IsEmpty())
				{
					bNotice = 0;
					msgSend << bNotice;
				}
				else
				{
					msgSend << bNotice << (LPCTSTR)m_strNotice;
				}
			}
			break;

		case 4:
			{
				strCPMsg = _T("");

#ifdef _CHINESE_MSG
				strCPMsg.Format("ÄúµÄÓÎÏ·µãÊýÒÑ¾­ÓÃÍê£¬Çë´¢Öµºó¼ÌÐø½øÐÐÓÎÏ·.");
#else
				strCPMsg.Format("¹«·áÃ¼Çè ±â°£ÀÌ Áö³µ½À´Ï´Ù.\nÀ¯·á °èÁ¤À¸·Î µî·ÏÇÏ½Ã¸é µå·ÎÀÌ¾á ¿Â¶óÀÎÀ» Áñ±â½Ç¼ö ÀÖ½À´Ï´Ù.");
#endif

				msgSend.ID(SM_LOGIN_ACK)
				<< nRet
				<< (BYTE)0x01
				<< (LPCTSTR)strCPMsg;
			}
			break;
		case 1: case 2: case 5: case 6: case 7: case 100:
			{
				msgSend.ID(SM_LOGIN_ACK)
				<< nRet;
			}
			break;

		}

		pDes->Say (msgSend);

		if(nRet == 99) pDes->SockCloseProcess();
	}
/*
		if ( nRet == LR_USER_DUP )
		{
			msgSend.ID(SM_LOGIN_ACK)
				<< nRet
				<< (LPCTSTR)strServerIP;

			pDes->Say (msgSend);

			return 0;
		}
		else if(nRet == 5)
		{
			msgSend.ID (SM_LOGIN_ACK) 
			pDes->Say (msgSend);

			return ERROR_INVALID;
		}
//		
		if(nRet != 0 && nRet != 1)
		{
			pDes->m_vRemainTime = 0;
			pDes->m_bGameRoom = 0;
			pDes->m_bDisplay = 0;
		}

		if(nRet == 0 || nRet == 4)
		{
			pDes->m_strUserID = strUserID;
			if(pDes->m_bDisplay == 2 && remain_time > 0)
			{
				pDes->m_vRemainTime = remain_time;
				pDes->m_dwStartTime = GetTickCount();
				pDes->m_bDisplay = 0;						// Á¶ÀÎÇÑ - 2001.10.04 : °³ÀÎ½Ã°£Á¦ ¸Þ¼¼Áö Ç¥½Ã ÀáÁ¤ »èÁ¦
			}
		}

		BYTE bNotice;
		msgSend.ID (SM_LOGIN_ACK) 
			<< nRet
			<< pDes->m_bDisplay;
		if(pDes->m_bDisplay == 4 || pDes->m_bDisplay == 5)
		{
			msgSend << remain_time;
		}
		else if(pDes->m_bDisplay == 1 || pDes->m_bDisplay == 3)
		{
			msgSend << time_stamp.year << time_stamp.month << time_stamp.day << time_stamp.hour << time_stamp.minute;
		}
		else pDes->m_bDisplay = 0;

		if(m_strNotice.IsEmpty())
		{
			bNotice = 0;
			msgSend << bNotice;
		}
		else
		{
			bNotice = 1;
			msgSend << bNotice << (LPCTSTR)m_strNotice;
		}
		pDes->Say (msgSend);
		/////////////////////////////////////

/*		if (!logset.Login ())
			return ERROR_INVALID;

		if (logset.m_bLoginResult == LR_USER_DUP)
		{
			msgSend.ID (UM_KICKOUT_REQ) 
				<< strUserID 
				<< logset.m_bCheckResult
				<< DR_DUPLICATE;
			m_desUM.Say (msgSend);

			return ERROR_DUPLICATE;
		}

		if (logset.m_bLoginResult == LR_USER_VALID)
			pDes->m_strUserID = strUserID;
		pDes->m_bPay = logset.m_bCheckResult;

		if(m_strNotice.IsEmpty())
		{
			BYTE bNotice = 0;
			msgSend.ID (SM_LOGIN_ACK) 
				<< logset.m_bLoginResult
				<< logset.m_bCheckResult
				<< bNotice;
		}
		else
		{
			BYTE bNotice = 1;
			msgSend.ID(SM_LOGIN_ACK)
				<< logset.m_bLoginResult
				<< logset.m_bCheckResult
				<< bNotice
				<< (LPCTSTR)m_strNotice;
		}
		pDes->Say (msgSend);*/
//	}
/*
		if (!logset.Login ())
			return ERROR_INVALID;

		if (logset.m_bLoginResult == LR_USER_DUP)
		{
			msgSend.ID (UM_KICKOUT_REQ) 
				<< strUserID 
				<< logset.m_bCheckResult
				<< DR_DUPLICATE;
			m_desUM.Say (msgSend);

			return ERROR_DUPLICATE;
		}

		if (logset.m_bLoginResult == LR_USER_VALID)
			pDes->m_strUserID = strUserID;
		pDes->m_bPay = logset.m_bCheckResult;

		if(m_strNotice.IsEmpty())
		{
			BYTE bNotice = 0;
			msgSend.ID (SM_LOGIN_ACK) 
				<< logset.m_bLoginResult
				<< logset.m_bCheckResult
				<< bNotice;
		}
		else
		{
			BYTE bNotice = 1;
			msgSend.ID(SM_LOGIN_ACK)
				<< logset.m_bLoginResult
				<< logset.m_bCheckResult
				<< bNotice
				<< (LPCTSTR)m_strNotice;
		}
		pDes->Say (msgSend);
	}
*/

	pDes->m_UserStatus = USER_LOGEDIN;
	pDes->m_ConnectTimeTick = 0;

	return 0;
}

int CSessionCom::OnSMRegUserReq(CSessDesc * pDes, CMsg & msg)
{
	CString strUserID, strPasswd, strName;
	CString strSocNo, strAddr, strTelNo, strMail;
	msg >> strUserID 
		>> strPasswd 
		>> strName 
		>> strSocNo 
		>> strAddr 
		>> strTelNo 
		>> strMail;

	CMsg msgSend;
	msgSend.ID (SM_REGUSER_ACK);
	CUserSet userset (&m_db[pDes->m_iSidMod]);
	userset.m_strSocNo = strSocNo;

	if (!CheckSocNum (strSocNo) || userset.SocNumExist())
		msgSend << (BYTE)0;
	else
	{
		userset.m_strUserID = strUserID;
		userset.m_strPasswd = strPasswd;
		userset.m_strName = strName;
		userset.m_strSocNo = strSocNo;
		userset.m_strAddr = strAddr;
		userset.m_strTel = strTelNo;
		userset.m_strEMail = strMail;

		if (userset.NewUser ())
			msgSend << (BYTE)0;
		else
			msgSend << (BYTE)1;
	}
	pDes->Say (msgSend);
		
	return 0;
}

int CSessionCom::OnSMGetInfoReq(CSessDesc * pDes, CMsg & msg)
{
	if (pDes->m_strUserID == _T(""))
		return ERROR_CANCEL;

	CUserSet userset (&m_db[pDes->m_iSidMod]);
	userset.m_strUserID = pDes->m_strUserID;
	if (userset.GetUser ())
	{
		CMsg msgSend;
		msgSend.ID (SM_GETINFO_ACK) 
			<< userset.m_strPasswd 
			<< _T("")
			<< _T("")
			<< userset.m_strAddr 
			<< userset.m_strTel 
			<< userset.m_strEMail;
		pDes->Say (msgSend);
	}

	return 0;
}

int CSessionCom::OnSMSetInfoReq(CSessDesc * pDes, CMsg & msg)
{
	if (pDes->m_strUserID == _T(""))
		return ERROR_CANCEL;

	CString strPasswd, strName, strSocNo;
	CString strAddr, strTelNo, strMail;
	msg >> strPasswd 
		>> strName 
		>> strSocNo 
		>> strAddr 
		>> strTelNo 
		>> strMail;
	
	CMsg msgSend;
	msgSend.ID (SM_SETINFO_ACK);

	CUserSet userset (&m_db[pDes->m_iSidMod]);
	userset.m_strUserID = pDes->m_strUserID;
	if (!userset.GetUser ())
		msgSend << (BYTE)0;
	else if (userset.m_strSocNo != strSocNo || userset.m_strName != strName)
		msgSend << (BYTE)0;
	else
	{
		userset.m_strPasswd = strPasswd;
		userset.m_strName = strName;
		userset.m_strSocNo = strSocNo;
		userset.m_strAddr = strAddr;
		userset.m_strTel = strTelNo;
		userset.m_strEMail = strMail;

		if (userset.UpdateUser ())
			msgSend << (BYTE)1;
		else
			msgSend << (BYTE)0;
	}
	pDes->Say (msgSend);

	return 0;
}

int CSessionCom::OnSMRegSNReq(CSessDesc * pDes, CMsg & msg)
{
	if (pDes->m_strUserID == _T(""))
		return ERROR_CANCEL;

	CString strSerial1, strSerial2, strPasswd;
	msg >> strSerial1 >> strSerial2 >> strPasswd;

	DWORD dwStart, dwEnd;
	BYTE bCheckRes;
	DWORD wSerial = CheckSerial (strSerial1, strSerial2);
	if (wSerial)
	{
		CSerialSet serialset (&m_db[pDes->m_iSidMod]);
		serialset.m_strUserID = pDes->m_strUserID;
		serialset.m_wSerial = wSerial;
		serialset.m_strPasswd = strPasswd;

		if (serialset.RegSerial ())
		{
			bCheckRes = serialset.m_bCheckResult;
			dwStart = serialset.m_timeStart.GetTime ();
			dwEnd = serialset.m_timeEnd.GetTime ();
		}
		else 
			bCheckRes = LR_SN_NOSN;
	}
	else
		bCheckRes = LR_SN_INVALID;

	CMsg msgSend;
	msgSend.ID (SM_REGSN_ACK) 
		<< bCheckRes
		<< dwStart 
		<< dwEnd;
	pDes->Say (msgSend);

	return 0;
}

int CSessionCom::OnSMDownReq( CSessDesc *pDes, CMsg &msg )
{
	if ( pDes )
	{
		pDes->m_UserStatus = USER_DOWNLOADIN;
	}

	return (pDes->Link(this, CSessDesc::stateDown, m_strFMAddr, m_nFMPort));
}

int CSessionCom::OnSMGameReq(CSessDesc *pDes, CMsg & msg)
{
	BYTE bOpt;
	int server_number;

	msg >> server_number;
	msg >> bOpt;

	if ( pDes == NULL || pDes->m_SockFlag != 1 )
		return ERROR_CANCEL;

	if (!bOpt)
		return ERROR_CANCEL;

//	if ( server_number < 0 )
//		return ERROR_CANCEL;

//	if (pDes->m_strUserID.IsEmpty())
//		return ERROR_CANCEL;

	CMsg msgSend;

	pDes->m_vServerNumber = server_number;

	if ( m_pDesGS && !m_pDesGS->IsValid() )
	{
		msgSend.ID(SM_GAME_ACK);
		msgSend << (BYTE)0;
		pDes->Say (msgSend);

		return ERROR_UNLINK;
	}

	msgSend.ID (SM_DIR_REQ) 
		<< (int)pDes->m_Sid
		<< pDes->m_strUserID 
		<< (BYTE)1
		<< pDes->m_vServerNumber;

	if ( m_pDesGS )
		m_pDesGS->Say(msgSend);

	return 0;
}

int CSessionCom::OnSMGameInfoReq(CSessDesc * pDes, CMsg & msg)
{
	CMsg msgSend;

	msgSend.ID(UM_CURSTATUS1_REQ)
		<< (int)pDes->m_Sid;
	m_pDesUM->Say(msgSend);

	return 0;
}

int CSessionCom::OnSMGameInfo2Req(CSessDesc * pDes, CMsg & msg)
{
	CMsg msgSend;
	msgSend.ID(UM_CURSTATUS_REQ)
		<< (int)pDes->m_Sid;

	if ( m_pDesUM )
		m_pDesUM->Say(msgSend);

	return 0;
}

int CSessionCom::OnSMDirAck(CMsg &msg)
{
	CSessDesc *pDes;
	CString strUserID, strAddr;
	int nPort, sid;
	BYTE bStart;

	msg >> sid
		>> strUserID
		>> bStart
		>> strAddr
		>> nPort;

	pDes = GetUserSocketUid( sid );
	if ( pDes == NULL )
		return 0;

	if (pDes->m_strUserID != strUserID || strAddr == _T(""))
	{
		pDes->SoftClose();
		return 0;
	}

	m_dwLastTime = ::GetTickCount();

#ifdef _INTERNET_USAGE
	CMsg msgSend;

	//@@@@@@@@@@ by zi_gi 2002-03-20 °°Àº °èÁ¤ÀÌ±â¶§¹®¿¡ °°Àº ¼­¹ö·Î ¹«Á¶°Ç º¸³½´Ù.
	if(pDes->m_iLoginFlag == DUPLICATED_USER) 
	{
		msgSend.ID (SM_CONNECTINFO_ACK)
					<< strUserID
					<< bStart
					<< pDes->m_strDupIPAddr
					<< nPort;
	}
	else
	{
		msgSend.ID (SM_CONNECTINFO_ACK)
					<< strUserID
					<< bStart
					<< strAddr
					<< nPort;
	}

	pDes->Say(msgSend);
#else
	int nType = (bStart) ? CSessDesc::stateStart : CSessDesc::stateGame;
	pDes->Link (this, nType, strAddr, nPort);
//	pDes->Link(this, nType, "127.0.0.1", nPort);

#endif

	return 0;
}

// User Manager Message Handler Functions

int CSessionCom::OnUMKickoutAck(CMsg & msg)
{
	CString strUserID;
	BYTE bReason;
	msg >> strUserID
		>> bReason;

	// Á¢¼ÓÀÚ Áß¿¡¼­ Ã¼Å©...
	int i, iFindIndex;
	CSessDesc *pDesFind = NULL;

	for ( i = 0; i < NUMSTARTRESOURCES_USER; i++ )
	{
		if ( g_pUQM->m_pResources->IsFree( i ) == true )
  			continue;

		CSessDesc *pDes = (CSessDesc *)g_pUQM->m_pResources->GetDataValue( i );
		if ( pDes )
		{
			if (pDes->m_strUserID == strUserID)
			{
				pDesFind = pDes;
				iFindIndex = i;
				break;
			}
		}
	}

	if ( pDesFind )
	{
		int nErrCode;
		switch (bReason)
		{
		case DR_DUPLICATE : 
			nErrCode = ERROR_DUPLICATE;
			break;
		case DR_CANCEL :
			nErrCode = ERROR_EXTERNAL;
			break;
		default :
			nErrCode = ERROR_INVALID;
			break;
		}

		pDesFind = GetUserSocketUid( iFindIndex );
		if ( pDesFind )
			OnCloseSession (pDesFind, nErrCode);
	}
	else
	{
		if (!strUserID.IsEmpty())
		{
//################################################################
//°­Á¦ Ãß¹æ ·Î±× ¾Æ¿ô
/*			EnterCriticalSection(&m_CS_db);
			CLogSet logset(&m_db[AUTOMATA_THREAD]);
			logset.m_strUserID = strUserID;
			logset.m_bReason = bReason;

			int nRet = logset.Logout();
			LeaveCriticalSection(&m_CS_db);

			switch(nRet)
			{
			case 0 : 
				TRACE("Force Logout Success [%s]...\n", strUserID);
				break;
			case 1 :
				TRACE("Force User Not Logged In [%s]...\n", strUserID);
				break;
			default :
				TRACE("Force [%s] Unknown error...\n", strUserID);
				break;
			}
*/		}
	}

	return 0;
}

int CSessionCom::OnUMCurStatusAck(CMsg& msg)
{
	int sid;
	CSessDesc *pDes;
	BYTE result;
	CString message;

	msg >> sid
		>> result;

	if(result)
	{
		msg >> m_strNotice;
	}
	else
		m_strNotice.Empty();

	pDes = GetUserSocketUid( sid );
	if ( !pDes ) return 0;

	CMsg msgSend;
	msgSend.ID (SM_GAMEINFO_ACK) 
		<< m_strServName 
		<< (BYTE)m_fPay 
		<< m_strGameID 
		<< m_wGameVer;
	pDes->Say (msgSend);

	return 0;
}

int CSessionCom::OnUMCurStatus1Ack(CMsg& msg)
{
	int sid;
	CSessDesc *pDes;
	BYTE result;
	CString message;
	CMsg msgSend;

	msg >> sid
		>> result;

	pDes = GetUserSocketUid( sid );
	if ( !pDes ) return 0;

	if(result)
	{
		msg >> m_strNotice;

		BYTE result = 3;

		msgSend.ID(SM_NOTICE_ACK)
			<< result
			<< m_strNotice;
		pDes->Say(msgSend);
	}
	else
	{
		msgSend.ID (SM_GAMEINFO_ACK) 
			<< m_strServName 
			<< (BYTE)m_fPay 
			<< m_strGameID 
			<< m_wGameVer;
		pDes->Say (msgSend);
	}

	return 0;
}

int CSessionCom::OnUMIdentifyAck(CMsg & msg)
{
	BYTE bRes;

	msg >> bRes;

	if (!bRes)
	{
#ifdef _DEBUG
// IKING 1999.1.
		::MessageBox(NULL, "OnUMIdentifyAck: ERROR_UMIDENTIFY", "SESSION", MB_OK );
#endif
		return ERROR_UMIDENTIFY;
	}

	msg >> m_wGameVer
		>> m_strGSAddr >> m_nGSPort
		>> m_strFMAddr >> m_nFMPort
		>> m_nSeed;

	// IKING 2000.1.
	// CONNECT-DIR-SERVER...
	if ( m_pDesGS && m_pDesGS->m_bConnectFlag == TRUE )
	{
		m_pDesGS->SoftClose();
		//m_pDesGS->m_bConnectFlag = FALSE;
	}

	m_pDesGS = GetServerSocket( &m_ServerBase );
	if ( m_pDesGS == NULL )
		return FALSE;

	if ( !m_pDesGS->Create() )
		return FALSE;

	m_fSuspend = !m_pDesGS->Connect( m_strGSAddr, m_nGSPort );

	m_pDesGS->Init(0);

	//
	// ACCEPT THREAD ENABLE...
	m_UserBase.m_bAcceptEnableFlag = TRUE;

	return 0;
}

int CSessionCom::OnUMReIdentifyAck(CMsg & msg)
{
	BYTE bRes;

	msg >> bRes;

	if (!bRes)
	{
#ifdef _DEBUG
// IKING 1999.1.
		::MessageBox(NULL, "OnUMIdentifyAck: ERROR_UMIDENTIFY", "SESSION", MB_OK );
#endif
		return ERROR_UMIDENTIFY;
	}

	// »ç¿ëÀÚ°¡ ºÙÀ» ¼ö ÀÖ°Ô ¼¼ÆÃ...
	m_UserBase.m_bAcceptEnableFlag = TRUE;	

	return 0;
}

BOOL CSessionCom::ConnectUM()
{
	CString strUMAddr;
	int nUMPort;

	if (!GetConfigString (NULL, _T("UMAddr"), strUMAddr))
		return FALSE;

	if (!GetConfigInt (NULL, _T("UMPort"), nUMPort))
		return FALSE;

	// IKING 2000.1.
	// CONNECT-USERMANAGER-SERVER...
	m_pDesUM = GetServerSocket( &m_ServerBase );
	if ( m_pDesUM == NULL )
		return FALSE;

	if ( !m_pDesUM->Create() )
		return FALSE;

	if ( !m_pDesUM->Connect( strUMAddr, nUMPort ) )
		return FALSE;

	m_pDesUM->Init( 0 );
	//

	CMsg msg;
	msg.ID (UM_IDENTIFY_REQ) << m_nServerID << m_strGameID;

	if ( m_pDesUM && m_pDesUM->m_bConnectFlag == TRUE )
		m_pDesUM->Say( msg );

	return TRUE;
}

BOOL CSessionCom::ReConnectUM()
{
	CString strUMAddr;
	int nUMPort;

	if (!GetConfigString (NULL, _T("UMAddr"), strUMAddr))
		return FALSE;

	if (!GetConfigInt (NULL, _T("UMPort"), nUMPort))
		return FALSE;

	// IKING 2000.1.
	// CONNECT-USERMANAGER-SERVER...
	m_pDesUM = GetServerSocket( &m_ServerBase );
	if ( m_pDesUM == NULL )
		return FALSE;

	if ( !m_pDesUM->Create() )
		return FALSE;

	if ( !m_pDesUM->Connect( strUMAddr, nUMPort ) )
		return FALSE;

	m_pDesUM->Init( 0 );
	//

	CMsg msg;
	msg.ID (UM_REIDENTIFY_REQ) << m_nServerID << m_strGameID;

	if ( m_pDesUM && m_pDesUM->m_bConnectFlag == TRUE )
		m_pDesUM->Say( msg );

	return TRUE;
}

BOOL CSessionCom::ReConnectGS()
{
	// IKING 2000.1.
	// CONNECT-DIR-SERVER...
	if ( m_pDesGS && m_pDesGS->m_bConnectFlag == TRUE )
	{
		m_pDesGS->SoftClose();
		//m_pDesGS = NULL;
		return FALSE;
	}

	m_pDesGS = GetServerSocket( &m_ServerBase );
	if ( m_pDesGS == NULL )
		return FALSE;

	if ( !m_pDesGS->Create() )
		return FALSE;

	m_fSuspend = !m_pDesGS->Connect( m_strGSAddr, m_nGSPort );
	m_pDesGS->Init(0);
	//

	return TRUE;
}

void CSessionCom::LoadFilterAddress()
{
	m_listFilter.RemoveAll ();

	CString strAddr, strName;
	for (int i = 0; TRUE; i++)
	{
		strName.Format (_T("Filter%d"), i);
		if (!GetConfigString (NULL, strName, strAddr))
			return;
		m_listFilter.AddTail (strAddr);
	}
}

BOOL CSessionCom::CheckFilterAddress(LPCTSTR lpszAddr)
{
	if (!m_listFilter.GetCount ())
		return TRUE;

	POSITION pos = m_listFilter.GetHeadPosition ();
	while (pos)
	{
		CString strAddr = m_listFilter.GetNext (pos);
		if (strAddr == lpszAddr)
			return TRUE;
	}
	return FALSE;
}

DWORD CSessionCom::CheckSerial(LPCTSTR lpszSerial1, LPCTSTR lpszSerial2)
{
	////////////////////////////////////////////////
	// bluesky 2001.1.11
	CString strID1 = lpszSerial1;
	CString strID2 = lpszSerial2;
    CString strStringCode;

	if (strID1.GetLength () != 6 ||
		strID2.GetLength () != 7)
		return 0;

	strStringCode.Format(_T("%s-%s"), lpszSerial1, lpszSerial2);

	int nNumDigit = atoi(strID1.Left (1));
	DWORD wSerial = atoi(strID2.Right (nNumDigit));

	CString strID2Check;

	//bluesky ½Ã¸®¾ó 1000000±îÁö Ã³¸® 
	if (wSerial > 99999)
	{
		EnterCriticalSection(&m_CS_db);
		CBankSerial BankSerial(&m_db[AUTOMATA_THREAD2]);
		BankSerial.m_strSerialCode = strStringCode;
		      
		if(BankSerial.GetSerialCode())
		{
			LeaveCriticalSection(&m_CS_db);
			return BankSerial.m_wSerial;
		}
		else
		{
			LeaveCriticalSection(&m_CS_db);
			return 0;
		}

	}
	else
	{
		if (wSerial > 9999)
		{
			strID2Check.Format ("%02d%u", m_nSeed % 100, wSerial);
			nNumDigit = 5;
		}
		else if (wSerial > 999)
		{
			strID2Check.Format ("%03d%u", m_nSeed % 1000, wSerial);
			nNumDigit = 4;
		}
		else if (wSerial > 99)
		{
			strID2Check.Format ("%04d%u", m_nSeed % 10000, wSerial);
			nNumDigit = 3;
		}
		else if (wSerial > 9)
		{
			strID2Check.Format ("%05d%u", m_nSeed % 100000, wSerial);
			nNumDigit = 2;
		}
		else 
		{
			strID2Check.Format ("%06d%u", m_nSeed % 1000000, wSerial);
			nNumDigit = 1;
		}

		CString strID1Check;
		int nDigit[7];
		for (int i = 0; i < 7; i++)
			nDigit[i] = atoi (strID2Check.Mid (i, 1));

		int nTemp[5];
		for (i = 0; i < 5; i++)
		{
			nTemp[i] = 0;
			for (int j = 0; j < 7; j++)
				nTemp[i] += (nDigit[j] + i + j) * (nDigit[j] + i + j);
			nTemp[i] %= 10;
		}

		strID1Check.Format ("%d%d%d%d%d%d", nNumDigit, 
			nTemp[0], nTemp[1], nTemp[2], nTemp[3], nTemp[4]);

		if (strID1Check != strID1 || strID2Check != strID2)
			return 0;

		return wSerial;
	}
}

BOOL CSessionCom::CheckSocNum(LPCTSTR lpszSocNo)
{
	int nNo[13];
	nNo[0] = lpszSocNo[0] - '0';
	nNo[1] = lpszSocNo[1] - '0';
	nNo[2] = lpszSocNo[2] - '0';
	nNo[3] = lpszSocNo[3] - '0';
	nNo[4] = lpszSocNo[4] - '0';
	nNo[5] = lpszSocNo[5] - '0';
	nNo[6] = lpszSocNo[7] - '0';
	nNo[7] = lpszSocNo[8] - '0';
	nNo[8] = lpszSocNo[9] - '0';
	nNo[9] = lpszSocNo[10] - '0';
	nNo[10] = lpszSocNo[11] - '0';
	nNo[11] = lpszSocNo[12] - '0';
	nNo[12] = lpszSocNo[13] - '0';

	int nSum = 0;
	int nDiv = 2;
	for (int i = 0; i < 12; i++)
	{
		if (nNo[i] < 0 || nNo[i] > 9)
			return FALSE;
		nSum += nNo[i] * nDiv;
		nDiv++;
		if (nDiv == 10)
			nDiv = 2;
	}
	return ((11 - (nSum % 11)) % 10 == nNo[12]);
}

int CSessionCom::OnSMGameEndReq(CSessDesc *pDes, CMsg &msg)
{
	CString UserId;
	msg >> UserId;

	if ( !UserId.IsEmpty() )
	{
		if ( pDes->m_bLogOutFlag == FALSE )
		{
			pDes->m_bLogOutFlag = TRUE;

/*
			// DBÀÇ Á¤º¸ Áö¿ì±â...
			CLogSet logset (&m_db[pDes->m_iSidMod]);
			logset.m_strUserID = UserId;
			logset.m_bReason = DR_CLIENT;

			int nRet = logset.Logout();
			switch(nRet)
			{
			case 0 :
				break;
			case 1 :
				TRACE("GE User[%s] Not Logged In...\n", UserId ); 
				break;
			default :
				TRACE("GE User[%s] Unknown error...\n", UserId ); 
				break;
			}
*/
		}

		return 0;
	}	

	return 1;
}

int CSessionCom::OnSMReconnectReq( CSessDesc *pDes, CMsg &msg )
{
	CString strUserID;
	CMsg msgSend;

	msg	>> strUserID;

	msgSend.ID (SM_DIR_REQ) 
		<< pDes->m_Sid
		<< pDes->m_strUserID 
		<< (BYTE)0
		<< pDes->m_vServerNumber;

	m_pDesGS->Say(msgSend);

	return 0;
}

BOOL CSessionCom::CheckIDValid(CString str_id)
{
	int ACCOUNT_NAME_LENGTH = 20;

	BOOL retVal = TRUE;
	int str_count, i;
	unsigned char ch;
	char t_userid[20];

	memset(t_userid, 0x00, ACCOUNT_NAME_LENGTH);

	str_count = str_id.GetLength();
	if(str_count <= 0 || str_count > ACCOUNT_NAME_LENGTH - 1) return FALSE;

	lstrcpy(t_userid, (LPCTSTR)str_id);

	for(i = 0; i < str_count; i++)
	{
		ch = (unsigned char)t_userid[i];
		if(ch == 0xa4) // ÀÚÀ½, ¸ðÀ½ Check
		{
			if(i == str_count-1)
			{
				retVal = FALSE;
				break;
			}
			i++;
			ch = (unsigned char)t_userid[i];
			if(ch < 0xa1 || ch > 0xd3)
			{
				retVal = FALSE;
				break;
			}
		}
		else if(ch >= 0xb0 && ch <= 0xc8) // ¿Ï¼ºÇü ÇÑ±Û Check
		{
			if(i == str_count-1)
			{
				retVal = FALSE;
				break;
			}
			i++;
			ch = (unsigned char)t_userid[i];
			if(ch < 0xa1 || ch > 0xfe)
			{
				retVal = FALSE;
				break;
			}
		}
		else if(ch<'!' || ch>'~')
		{
			retVal = FALSE;
			break;
		}
	}

	if(retVal == TRUE && str_id.FindOneOf("\\/;*?\"<>|") != -1) retVal = FALSE;

	return retVal;
}

BOOL CSessionCom::CheckPwdValid( CString strPasswd)
{
	int strlen = 0;
	char ch ;
	
	strlen = strPasswd.GetLength();
	for (int i=0; i < strlen; i++)  {
		ch  =  strPasswd.GetAt(i);
		if( !(ch > 0x2F && ch < 0x3A) ) {			// number check
			if( !(ch > 0x40 && ch < 0x5B) ) {		// upper case check
				if( !(ch > 0x60 && ch < 0x7B ) )	// lower case check
					return  FALSE;
			}
		}
	}

	if( i == strlen )
		return TRUE;
	else
		return FALSE;
}

int CSessionCom::OnSMUpgradingAck( CSessDesc *pDes, CMsg &msg )
{
	CMsg msgSend;
	msgSend.ID (SM_GAMEINFO_ACK) 
		<< m_strServName 
		<< (BYTE)m_fPay 
		<< m_strGameID 
		<< m_wGameVer;
	pDes->Say (msgSend);

	return 0;
}

// by Youn Gyu 2001. 3. 27  
int CSessionCom::OnSMChangePasswdReq(CSessDesc *pDes, CMsg &msg)
{
	BYTE nflag = 1;
	CMsg msgSend;
	CString strUserID, strCurrentPasswd, strNewPasswd;

	msg >> strUserID
		>> strCurrentPasswd
		>> strNewPasswd;

	if(CheckIDValid(strUserID) == FALSE)
	{
		BYTE result = 1;
		msgSend.ID (SM_CHANGEPASSWD_ACK) 
			<< result;

		pDes->Say (msgSend);
	}
	else
	{
		CLogSet logset (&m_db[pDes->m_iSidMod]);
		logset.m_strUserID = strUserID;
		logset.m_strPasswd = strCurrentPasswd;
		nflag = logset.ChangePass(strNewPasswd);

		msgSend.ID (SM_CHANGEPASSWD_ACK)		// nflag == 0ÀÏ¶§ ¼º°ø
				<< nflag;

		pDes->Say (msgSend);
	}

	return 0;
}

int RegFreeUser(CDatabase *pDB, CString strID, int ServiceID, CString IPAddr)
{
	SQLHSTMT hstmt;
	SQLRETURN	retcode;
	SWORD	sParam1 = 0;
	SDWORD	cbParam1;
	BOOL	retval = FALSE;
	SQLRETURN nResult;
	int ret_value;

	nResult = SQLAllocHandle (SQL_HANDLE_STMT, pDB->Get_hdbc(), (SQLHANDLE*)&hstmt);
	if (!SQLOK(nResult))
	{
		return -1;
	}

	CString strSQL;
	strSQL.Format (_T("{ ? = CALL UM_REGFREEUSER1 ('%s', %d, '%s')}"), strID, ServiceID, IPAddr );

	cbParam1 = SQL_NTS;

	retcode = SQLBindParameter(hstmt, 1,SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER,0,0,&sParam1,0,&cbParam1);

	retcode = SQLExecDirect (hstmt, (unsigned char *)(LPCTSTR)strSQL, SQL_NTS);
	if(retcode == SQL_ERROR) DisplayDBError(strSQL, hstmt);

	if (SQLOK(retcode))
	{
		if(sParam1 == 1) ret_value = 1;
		else ret_value = 0;
	}
	else ret_value = -1;

	SQLCloseCursor(hstmt);
	SQLFreeHandle (SQL_HANDLE_STMT, hstmt);

	return ret_value;
}

void DisplayDBError(CString header, SQLHSTMT hstmt)
{
/*	SQLCHAR			SqlState[6], Msg[SQL_MAX_MESSAGE_LENGTH];
	SQLINTEGER		NativeError;
	SQLSMALLINT		i, MsgLen;
	SQLRETURN		rc2;
	CTime			time;
	CString			t_str, t_strTime;
	
	if(HFILE(db_file) == (UINT)CFile::hFileNull) return;

	db_file.WriteString(header);

	// Get the status records.
	i = 1;
	while ((rc2 = SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, i, SqlState, &NativeError,
		Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA) {
		time = CTime::GetCurrentTime();
		t_strTime = time.Format("(%Y³â %m¿ù %dÀÏ %I:%M:%S %p)");
		t_str.Format("%s - (%s)%d:%s\n", t_strTime, SqlState, NativeError, Msg);
		db_file.WriteString(t_str);
		i++;
	}
*/
}


// by zi_gi2002-03-20 : °ÔÀÓ ¼­¹ö¿¡ Á¢¼ÓÀÌ µÇ¾ú´ÂÁö È®ÀÎ
int CSessionCom::OnSMGameConnectionReq(CSessDesc *pDes, CMsg &msg)
{
	CString strUserID;
	msg >> strUserID;

	BYTE result;
	CMsg msgSend;

	if(pDes->m_strUserID.CompareNoCase(strUserID) == 0)
	{
		result = 1;
		pDes->m_iLoginFlag = 2;			// CloseSocketÀÏ¶§ CurrentUser Table¿¡¼­ Delete¸¦ ¾ÈÇÑ´Ù.

		msgSend.ID(SM_GAMESERVER_CONNECT_ACK)
			<< result;
	}
	else
	{
		result = 0;
		msgSend.ID(SM_GAMESERVER_CONNECT_ACK)
			<< result;
	}

	pDes->Say(msgSend);

	return 0;
}


