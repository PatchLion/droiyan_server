///////////////////////////////////////////////////////////////////////////////
// User Manager Class 
#include "StdAfx.h"
#include "Usermanager.h"

CUserManager::CUserManager()
{
}

CUserManager::~CUserManager()
{
}

void CUserManager::ResourceFree( int uid )
{
	if ( uid >= 0 )
	{
		if ( m_pResources->IsFree( uid ) == true ) 
  			return;

		RHANDLE *pHandle;
		pHandle = m_pResources->GetHandle( uid );
		ReleaseResource(pHandle);
	}
}
