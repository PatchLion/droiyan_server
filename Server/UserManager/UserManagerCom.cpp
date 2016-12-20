// UserManagerCom.cpp: implementation of the CUserManagerCom class.
//
//////////////////////////////////////////////////////////////////////
 
#include "stdafx.h"
#include "UserManager.h"
#include "UserManagerCom.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define ERROR_DB				(ERROR_USER + 0)
#define ERROR_DUP				(ERROR_USER + 1)
#define ERROR_UNIDENTIFY		(ERROR_USER + 2)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUserManagerCom::CUserManagerCom(LPCTSTR lpszServerName) :
CBaseCom (lpszServerName)
{
}

CUserManagerCom::~CUserManagerCom()
{
}

BOOL CUserManagerCom::Process()
{
	return CBaseCom::Process ();
}

void CUserManagerCom::OnPauseService()
{
	CBaseCom::OnPauseService ();
}

BOOL CUserManagerCom::OnContinueService()
{
	return CBaseCom::OnContinueService ();
}

void CUserManagerCom::OnStopService()
{
	CBaseCom::OnStopService ();
}

BOOL CUserManagerCom::OnStartService()
{
	if (!GetConfigInt (NULL, _T("GameVer"), m_nGameVer))
		m_nGameVer = 0;
	if (!GetConfigString (NULL, _T("GSAddr"), m_strGSAddr))
		return FALSE;
	if (!GetConfigInt (NULL, _T("GSPort"), m_nGSPort))
		return FALSE;
	if (!GetConfigString (NULL, _T("FMAddr"), m_strFMAddr))
		return FALSE;
	if (!GetConfigInt (NULL, _T("FMPort"), m_nFMPort))
		return FALSE;

	m_nSeed = 1;
	CString strSeed = m_strGameID;
	strSeed.MakeUpper ();
	int nLen = strSeed.GetLength ();
	if (nLen > 4)
		nLen = 4;
	for (int i = 0; i < nLen; i++)
		m_nSeed *= (int)strSeed[i];

	return CBaseCom::OnStartService ();
}

void CUserManagerCom::OnTimer ()
{
	CBaseCom::OnTimer ();
}

BOOL CUserManagerCom::OnOpenSession (CSessDesc* pDes)
{
	pDes->m_pObject = NULL;
	return CBaseCom::OnOpenSession (pDes);
}

void CUserManagerCom::OnCloseSession (CSessDesc* pDes, int nCode)
{
	if (pDes->m_pObject)
	{
		delete pDes->m_pObject;
		pDes->m_pObject = NULL;
	}

	CBaseCom::OnCloseSession (pDes, nCode);
}

int CUserManagerCom::OnReceiveMsg (CSessDesc* pDes, CMsg& msg)
{
	switch (msg.ID ())
	{
	case 0						: 
		{
			CMsg msgSend;
			msgSend.ID (0) 
				<< (BYTE)m_fSuspend
				<< m_listActive.GetCount ();
			pDes->Say (msgSend);
		}
		return 0;
	case UM_KICKOUT_REQ			: return OnUMKickoutReq (pDes, msg);
	case UM_IDENTIFY_REQ		: return OnUMIdentifyReq (pDes, msg);
	case UM_CURSTATUS_REQ		: return OnUMCurStatusReq(pDes, msg);
	case UM_CURSTATUS1_REQ		: return OnUMCurStatus1Req(pDes, msg);
	}
	return ERROR_INVALID;
}

// User Manager Message Handler Functions

int CUserManagerCom::OnUMKickoutReq(CSessDesc * pDes, CMsg & msg)
{
	BYTE bServID, bReason;
	CString strUserID;
	msg >> strUserID >> bServID >> bReason;

	// IKING 1999.1.
	//CSessDesc *pDesFind;
	CSessDesc *pDesFind = NULL;
	//

	POSITION pos = m_listActive.GetHeadPosition ();
	while (pos)
	{
		CSessDesc *pDesTemp = (CSessDesc*)m_listActive.GetNext (pos);
		// IKING 1999.1.
		if ( !pDesTemp ) continue;
		//

		CSession* pSession = (CSession*)pDesTemp->m_pObject;
		if (pSession && pSession->m_nServID == bServID)
		{
			pDesFind = pDesTemp;
			break;
		}
	}

	if (pDesFind)
	{
		CMsg msgSend;
		msgSend.ID (UM_KICKOUT_ACK) << strUserID << bReason;
		pDesFind->Say (msgSend);
	}

	return 0;
}

int CUserManagerCom::OnUMIdentifyReq(CSessDesc * pDes, CMsg & msg)
{
	int nServID;
	CString strGameID;
	msg >> nServID 
		>> strGameID;

	if (strGameID != m_strGameID)
	{
		CMsg msgSend;
		msgSend.ID (UM_IDENTIFY_ACK) << (BYTE)0;
		pDes->Say (msgSend);
		return 0;
	}

	POSITION pos = m_listActive.GetHeadPosition ();
	while (pos)
	{
		CSessDesc *pDes = (CSessDesc*)m_listActive.GetNext (pos);
		// IKING 1999.1.
		if ( !pDes ) continue;
		//
		CSession* pSession = (CSession*)pDes->m_pObject;
		if (pSession && pSession->m_nServID == nServID)
			OnCloseSession (pDes, ERROR_DUP);
	}

	CSession* pSession = new CSession (nServID);
	pDes->m_pObject = pSession;

	CMsg msgSend;
	msgSend.ID (UM_IDENTIFY_ACK)
		<< (BYTE)1 
		<< (WORD)m_nGameVer
		<< m_strGSAddr 
		<< m_nGSPort
		<< m_strFMAddr 
		<< m_nFMPort
		<< m_nSeed;
	pDes->Say (msgSend);

	return 0;
}

int CUserManagerCom::OnUMCurStatusReq(CSessDesc *pDes, CMsg& msg)
{
	CSessDesc *pCDes;
	int result;
	CString message;

	msg >> (int&)pCDes;

	if(!GetConfigInt(NULL, _T("NoticeStatus"), result))
		result = 0;
	if (!GetConfigString (NULL, _T("NoticeMessage"), message))
		message = _T("");

	CMsg msgSend;
	msgSend.ID(UM_CURSTATUS_ACK);
	msgSend << (int)pCDes;
	msgSend << (BYTE)result;
	if(result == 1)
	{
		msgSend << message;
	}
	pDes->Say(msgSend);

	return 0;
}

int CUserManagerCom::OnUMCurStatus1Req(CSessDesc *pDes, CMsg& msg)
{
	CSessDesc *pCDes;
	int result;
	CString message;

	msg >> (int&)pCDes;

	if(!GetConfigInt(NULL, _T("NoticeSessionStatus"), result))
		result = 0;
	if (!GetConfigString (NULL, _T("NoticeSessionMessage"), message))
		message = _T("");

	CMsg msgSend;
	msgSend.ID(UM_CURSTATUS1_ACK);
	msgSend << (int)pCDes;
	msgSend << (BYTE)result;
	if(result == 1)
	{
		msgSend << message;
	}
	pDes->Say(msgSend);

	return 0;
}