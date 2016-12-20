// BadukDirCom.cpp: implementation of the CBadukDirCom class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BadukDir.h"
#include "BadukDirCom.h"
#include "UserSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

char ExeFilePath[_MAX_PATH];
//CErrorLog		g_ErrorLog;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBadukDirCom::CBadukDirCom(LPCTSTR lpszServerName) :
CBaseCom (lpszServerName)
{
	m_nNumServer = 0;

	m_vServerCount = 0;
	m_pSvrKindCount = NULL;
	m_pZoneNumber = NULL;
	m_pCurrentPos = NULL;
	m_pAddress = NULL;
	m_pPort = NULL;
}

CBadukDirCom::~CBadukDirCom()
{
	RemoveData();
}

BOOL CBadukDirCom::Process()
{
	return CBaseCom::Process ();
}

void CBadukDirCom::OnPauseService()
{
	CBaseCom::OnPauseService ();
}

BOOL CBadukDirCom::OnContinueService()
{
	return CBaseCom::OnContinueService ();
}

void CBadukDirCom::OnStopService()
{
	if (m_db.IsOpen ())
	{
		m_db.Close ();
	}

	CBaseCom::OnStopService ();
}

BOOL CBadukDirCom::OnStartService()
{
	CString strConnect;
	
//	g_ErrorLog.WriteError2(TRUE, _T(""),_T("OnStartService가 호출"));

//	strConnect.Format (_T("DSN=%s;UID=%s;PWD=%s"), "saver", "saver", "rudnfdldirl");
//	strConnect.Format (_T("DSN=saver;UID=saver;PWD=rudnfdldirl"));
	strConnect.Format (_T("DSN=%s;UID=%s;PWD=%s"), m_strGameID, m_strUserID, m_strPassword);
	 
//	g_ErrorLog.WriteError2(TRUE, _T(""),strConnect);

	if (!m_db.Open(strConnect)) return FALSE;

//	g_ErrorLog.WriteError2(TRUE, _T(""),_T("OnStartService에서 DB연결"));

	if (!LoadGameAddr ())
		return FALSE;

//	g_ErrorLog.WriteError2(TRUE, _T(""),_T("OnStartService에서 ini파일 읽음"));

	return CBaseCom::OnStartService ();
}

void CBadukDirCom::OnTimer ()
{
	CBaseCom::OnTimer ();
}

BOOL CBadukDirCom::OnOpenSession (CSessDesc* pDes)
{
	return CBaseCom::OnOpenSession (pDes);
}

void CBadukDirCom::OnCloseSession (CSessDesc* pDes, int nCode)
{
	CBaseCom::OnCloseSession (pDes, nCode);
}

int CBadukDirCom::OnReceiveMsg (CSessDesc* pDes, CMsg& msg)
{
//	g_ErrorLog.WriteError2(TRUE, _T(""),_T("OnReceiveMsg가 호출"));
	switch (msg.ID ())
	{
	case SM_DIR_REQ :	return OnSMDirReq (pDes, msg);
	}

	return 0;
}

int CBadukDirCom::OnSMDirReq(CSessDesc *pDes, CMsg &msg)
{
	int nDes;
	CString strUserID;
	BYTE bStart;
	int zone_number;
	int server_number;

	msg >> nDes >> strUserID >> bStart >> server_number;

	TRACE1("Req Server : %d\n", server_number);
	CMsg msgSend;
	msgSend.ID (SM_DIR_ACK) 
		<< nDes 
		<< strUserID 
		<< bStart;

	if(server_number < 0 || server_number >= m_vServerCount)
	{
		msgSend << _T("") << 0;

		pDes->Say(msgSend);
		return 0;
	}

	CUserSet userset(&m_db);

	userset.m_strUserID = strUserID;
	if ( bStart == 1 )
	{
/*		if (userset.GetLogInZoneNumber())
		{
			switch(server_number)  // Insert code when server is added.
			{
			case 0:
				zone_number = userset.m_nZoneNumber;
				break;
			default:
				zone_number = userset.m_nZoneNumber;
				break;
			}
			
		}
		else 
*///		{
			zone_number = 0;
//		}
	}
	else
	{
/*		if ( userset.GetZoneNumber() )
		{
			if ( userset.m_nZoneNumber == 100) // Insert code when server is added.
				return 0;

			switch(server_number) // Insert code when server is added.
			{
			case 0:
				zone_number = userset.m_nZoneNumber;
				break;
			default:
				zone_number = userset.m_nZoneNumber;
				break;
			}
		}
		else
		{
*/			zone_number = 0;
//		}
	}

	if (zone_number >= 0 && zone_number < m_pSvrKindCount[server_number])
	{
		CString strAddr;
		int nPort;

		strAddr = m_pAddress[server_number][zone_number][m_pCurrentPos[server_number][zone_number]];
		nPort = m_pPort[server_number][zone_number][m_pCurrentPos[server_number][zone_number]];

		m_pCurrentPos[server_number][zone_number] = m_pCurrentPos[server_number][zone_number] + 1;
		m_pCurrentPos[server_number][zone_number] = m_pCurrentPos[server_number][zone_number] % m_pZoneNumber[server_number][zone_number];

		msgSend	<< strAddr 	<< nPort;

		pDes->Say (msgSend);
	}
	else
	{
		msgSend << _T("") << 0;

		pDes->Say(msgSend);
	}

	return 0;
}

BOOL CBadukDirCom::LoadGameAddr()
{
	int i,j,k;

	RemoveData();
	m_nNumServer = 0;
	while (TRUE)
	{
		CString strEntryAddr, strEntryPort, strAddr;
		int nPort;
		strEntryAddr.Format (_T("GSAddr%d"), m_nNumServer);
		strEntryPort.Format (_T("GSPort%d"), m_nNumServer);
		if (!GetConfigString (NULL, strEntryAddr, strAddr) ||
			!GetConfigInt (NULL, strEntryPort, nPort))
			break;
		m_arrayGSAddr.Add (strAddr);
		m_arrayGSPort.Add (nPort);
		m_nNumServer++;
	}
	// 게임 서버 정보 초기화...
	// 실행파일 경로 가져오기...
	char Buf[_MAX_PATH], Path[_MAX_PATH];
	char drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
	char IniPath[_MAX_PATH];
	char temp_buff[16];
	char temp_addr[20];
	int temp_port;

	::GetModuleFileName( AfxGetApp()->m_hInstance, Buf, 256 );
	_splitpath( Buf, drive, dir, fname, ext );
	strcpy( Path, drive );
	strcat( Path, dir );		
	strcpy( ExeFilePath, Path );

	strcpy( IniPath, ExeFilePath );
	strcat( IniPath, "dir.ini" );
	
	// ID 얻기...
	m_vServerCount = GetPrivateProfileInt("SERVER", "COUNT", 0, IniPath);
	if(m_vServerCount == 0)
	{
		::MessageBox(NULL, "ERROR: SERVERCOUNT", "변수 에러", MB_OK);
		return FALSE;
	}

	m_pSvrKindCount = new int[m_vServerCount];
	m_pZoneNumber = new int *[m_vServerCount];
	m_pCurrentPos = new int *[m_vServerCount];
	m_pAddress = new char ***[m_vServerCount];
	m_pPort = new int **[m_vServerCount];
	for(k = 0; k < m_vServerCount; k++)
	{
		char t_str[20];
		char t_kind[20];

		sprintf(t_str, "DIR_GAME_SERVER_%02d", k+1);
		m_pSvrKindCount[k] = GetPrivateProfileInt(t_str, "SVR_KIND_COUNT", 0, IniPath);
		if(m_pSvrKindCount[k] == 0)
		{
			::MessageBox( NULL, "ERROR: SVR_KIND_COUNT", "변수 에러", MB_OK );
			return FALSE;
		}

		m_pZoneNumber[k] = new int[m_pSvrKindCount[k]];
		m_pCurrentPos[k] = new int[m_pSvrKindCount[k]];
		for(i = 0; i < m_pSvrKindCount[k]; i++) m_pCurrentPos[k][i] = 0;
		m_pAddress[k] = new char**[m_pSvrKindCount[k]];
		m_pPort[k] = new int*[m_pSvrKindCount[k]];
		for ( i = 0; i < m_pSvrKindCount[k]; i++ )
		{
			sprintf(t_str, "DIR_GAME_SERVER_%02d", k+1);
			sprintf( t_kind, "SVR_COUNT_%02d", i+1 );
			m_pZoneNumber[k][i] = GetPrivateProfileInt(t_str, t_kind, 0, IniPath);
			if(m_pZoneNumber[k][i] == 0)
			{
				::MessageBox( NULL, "ERROR: SVR_KIND_COUNT", "변수 에러", MB_OK );
				return FALSE;
			}
			m_pAddress[k][i] = new char*[m_pZoneNumber[k][i]];
			for(j = 0; j < m_pZoneNumber[k][i]; j++)
			{
				m_pAddress[k][i][j] = new char[16];
			}
			m_pPort[k][i] = new int[m_pZoneNumber[k][i]];
		}

		for ( i = 0; i < m_pSvrKindCount[k]; i++ )
		{
			sprintf( t_kind, "SVR_%02d_KIND_%02d", k+1, i+1 );

			for ( j = 0; j < m_pZoneNumber[k][i]; j++ )
			{
				sprintf( t_str, "SVR%02d_ADDR", j+1 );
				if ( GetPrivateProfileString(t_kind, t_str, "0", temp_addr, sizeof(temp_addr), (LPCSTR)IniPath) == 0 )
				{
					::MessageBox( NULL, "ERROR: SVR_KIND_COUNT", "변수 에러", MB_OK );
					return FALSE;
				}

				sprintf( t_str, "SVR%02d_PORT", j+1 );
				if ( GetPrivateProfileString(t_kind, t_str, "0", temp_buff, sizeof(temp_buff), (LPCSTR)IniPath) == 0 )
				{
					::MessageBox( NULL, "ERROR: SVR_KIND_COUNT", "변수 에러", MB_OK );
					return FALSE;
				}
				temp_port = atoi(temp_buff);
				lstrcpy(m_pAddress[k][i][j], temp_addr);
				m_pPort[k][i][j] = temp_port;
			}
		}
	}
	//

	return TRUE;
}

void CBadukDirCom::RemoveData()
{
	int i, j, k;

	if(m_vServerCount)
	{
		for(k = 0; k < m_vServerCount; k++)
		{
			if(m_pSvrKindCount[k])
			{
				for(i = 0; i < m_pSvrKindCount[k]; i++)
				{
					for(j = 0; j < m_pZoneNumber[k][i]; j++)
					{
						delete[] m_pAddress[k][i][j];
					}
					delete[] m_pAddress[k][i];
					delete[] m_pPort[k][i];
				}
				delete[] m_pZoneNumber[k]; m_pZoneNumber[k] = NULL;
				delete[] m_pCurrentPos[k]; m_pCurrentPos[k] = NULL;
				delete[] m_pAddress[k]; m_pAddress[k] = NULL;
				delete[] m_pPort[k]; m_pPort[k] = NULL;
			}
		}
		delete[] m_pSvrKindCount;
		delete[] m_pZoneNumber;
		delete[] m_pCurrentPos;
		delete[] m_pAddress;
		delete[] m_pPort;
	}
}