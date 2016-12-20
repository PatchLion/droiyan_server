///////////////////////////////////////////////////////////////////////////////
// CSearch Class impl.
//
#include "stdafx.h"
#include "Search.h"

//-----------------------------------------------------------------------------
// CSearch Class Define...
//
CSearch::CSearch()
{
}

CSearch::CSearch(int dim)
 : CSearchBase<USER>(dim)
{
}

CSearch::~CSearch()
{
}

USER* CSearch::GetUserUid(int uid)
{
	if ( uid < 0 || uid >= m_arrayDim ) return NULL;

	return GetObject( uid );
}

void CSearch::SetUserUid(int uid, USER *pUser)
{
	if ( uid < 0 || uid >= m_arrayDim ) return;

	SetObject( uid, pUser);
}

void CSearch::FreeUser( int uid )
{
	if ( uid < 0 || uid >= m_arrayDim ) return;

	SetObjectToFree(uid);
}

/*
//-----------------------------------------------------------------------------
// CRoomSearch Class Define...
//
CRoomSearch::CRoomSearch()
{
}

CRoomSearch::CRoomSearch(int dim)
 : CSearchBase<CRoom>(dim)
{
}

CRoomSearch::~CRoomSearch()
{
}

CRoom* CRoomSearch::GetRoomUid(int uid)
{
	if ( uid < 0 || uid >= m_arrayDim ) return NULL;

	return GetObject( uid );
}

void CRoomSearch::SetRoomUid(int uid, CRoom *pRoom)
{
	if ( uid < 0 || uid >= m_arrayDim ) return;

	SetObject( uid, pRoom);
}

void CRoomSearch::FreeRoom( int uid )
{
	if ( uid < 0 || uid >= m_arrayDim ) return;

	SetObjectToFree(uid);
}

//-----------------------------------------------------------------------------
// CNpcSearch Class Define...
//
CNpcSearch::CNpcSearch()
{
}

CNpcSearch::CNpcSearch(int dim)
 : CSearchBase<CNPC>(dim)
{
}

CNpcSearch::~CNpcSearch()
{
}

CNPC* CNpcSearch::GetNpcUid(int uid)
{
	if ( uid < 0 || uid >= m_arrayDim ) return NULL;

	return GetObject( uid );
}

void CNpcSearch::SetNpcUid(int uid, CNPC *pNpc)
{
	if ( uid < 0 || uid >= m_arrayDim ) return;

	SetObject( uid, pNpc);
}

void CNpcSearch::FreeNpc( int uid )
{
	if ( uid < 0 || uid >= m_arrayDim ) return;

	SetObjectToFree(uid);
}
*/

