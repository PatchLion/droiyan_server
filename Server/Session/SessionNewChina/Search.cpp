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
 : CSearchBase<CSessDesc>(dim)
{
}

CSearch::~CSearch()
{
}

CSessDesc* CSearch::GetUserUid(int uid)
{
	if ( uid < 0 || uid >= m_arrayDim ) return NULL;

	return GetObject( uid );
}

void CSearch::SetUserUid(int uid, CSessDesc *pUser)
{
	if ( uid < 0 || uid >= m_arrayDim ) return;

	SetObject( uid, pUser);
}

void CSearch::FreeUser( int uid )
{
	if ( uid < 0 || uid >= m_arrayDim ) return;

	SetObjectToFree(uid);
}



