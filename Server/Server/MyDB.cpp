// MyDB.cpp: implementation of the CMyDB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyDB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyDB::CMyDB()
{
	m_strConnect = _T("");
}

CMyDB::~CMyDB()
{
	int i;
	for( i = 0; i < m_arDB.GetSize(); i++)
	{
		if( m_arDB[i] )
		{
			delete m_arDB[i];
		}
	}
	m_arDB.RemoveAll();
}

///////////////////////////////////////////////////////////////////////
//	DB Connection 정보를 초기화 한다.
//
void CMyDB::Init(int num)
{
	DB_CONNECTION* pNewDB = NULL;

	for( int i = 0; i < num; i++ )
	{
		pNewDB = new DB_CONNECTION;
		
		pNewDB->lRef = 0;
		pNewDB->bConnect = FALSE;
		pNewDB->iCount = 0;
		pNewDB->dwGetDBTime = 0;

		m_arDB.Add( pNewDB );
	}

	m_iTotalConnection = num;
}

///////////////////////////////////////////////////////////////////////
//	DB 에 연결한다.
//
BOOL CMyDB::DBConnect(LPCTSTR strConnect)
{
	DB_CONNECTION* pDB = NULL;

	m_strConnect = strConnect;

	try{
		for( int i = 0; i < m_arDB.GetSize(); i++)
		{
			if( m_arDB[i] )
			{
				pDB = m_arDB[i];
				
				if( !pDB->bConnect )
				{
					pDB->db.SetLoginTimeout(10);
					
					if(!pDB->db.Open(NULL, FALSE, FALSE, m_strConnect))
					{
						TRACE("SQL Connection Fail...");
						return FALSE;
					}
					
					pDB->bConnect = TRUE;
				}
				else
				{
					pDB->db.Close();
					pDB->db.SetLoginTimeout(10);
					if( !pDB->db.Open(NULL,FALSE,FALSE,strConnect) )
					{
						TRACE(_T("Game DB Connection Fail #%d"), i);
						return FALSE;
					}
				}
			}
			else return FALSE;
		}
	}
	catch(CMemoryException * e)
	{
		e->ReportError();
		e->Delete();

		return FALSE;
	}
	catch(CDBException* e)
	{
		e->ReportError();
		e->Delete();

		return FALSE;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
//	현재 사용하고 있지 않은 DB 에 연결한다.
//
CDatabase* CMyDB::GetDB(int &index)
{
	DB_CONNECTION* pDB = NULL;
	int i;

	index = -1;
	for(i = 0; i < m_arDB.GetSize(); i++ )
	{
		if( m_arDB[i] )
		{
			pDB = m_arDB[i];

			if( ::InterlockedCompareExchange( (long*)&(pDB->lRef), (long)1, (long)0 ) == (long)0 )
			{
				index = i;

				// 기존의 죽운 HANDLE 재생...
				if ( i >= (m_arDB.GetSize()-1) && i > 0 )
				{
					int j,ncount;
					DB_CONNECTION* pDB2 = NULL;
					ncount = (m_arDB.GetSize()-1);
					for ( j = 0; j < ncount; j++ )
					{
						pDB2 = m_arDB[j];
						pDB2->iCount = 0;
						pDB2->dwGetDBTime = 0;
						
						if ( m_strConnect != _T("") )
						{
							pDB2->db.Close();
							
							pDB2->db.SetLoginTimeout(10);
							if(!pDB2->db.Open(NULL, FALSE, FALSE, m_strConnect))
							{
								TRACE("Fail To Reconnect DB...[ %d ]\n", j );
								return NULL;
							}
							TRACE("Reconnect to DB2...[ %d ]\n", j );
						}
		
						::InterlockedExchange(&(pDB2->lRef), 0);
					}

					TRACE("ReInit DB handle In [%d]...\n", m_arDB.GetSize());
				}

				pDB->dwGetDBTime = GetTickCount();
				return &(pDB->db);
			}
		}
	}

	DWORD	dwCurrTime = GetTickCount();
	DWORD	dwComp = 0;
	int		iMaxUse = 0;
	int		iRelease = 0;

	for(i = 0; i < m_arDB.GetSize(); i++)
	{
		if(m_arDB[i])
		{
			pDB = m_arDB[i];

			if(pDB->dwGetDBTime > dwComp) 
			{
				dwComp = pDB->dwGetDBTime;
				iMaxUse = i;
			}

			if(dwCurrTime - pDB->dwGetDBTime >= MAX_DB_USE_TIME)
			{
				ReleaseDB(i);
				index = i;
				iRelease++;
			}
		}
	}

	if(iRelease > 0)
	{
		pDB = m_arDB[index];
		if( ::InterlockedCompareExchange( (long*)&(pDB->lRef), (long)1, (long)0 ) == (long)0 )
		{
			pDB->dwGetDBTime = GetTickCount();
			return &(pDB->db);
		}
	}

	if(iRelease == 0)
	{
		//BREAKPOINT();
		ReleaseDB(iMaxUse);
		pDB = m_arDB[iMaxUse];
		if( ::InterlockedCompareExchange( (long*)&(pDB->lRef), (long)1, (long)0 ) == (long)0 )
		{
			index = iMaxUse;
			pDB->dwGetDBTime = GetTickCount();
			return &(pDB->db);
		}
	}

	index = -1;
	return NULL;
}

///////////////////////////////////////////////////////////////////////
//	현재 사용하고 있는 DB 를 사용하지 않는 DB로 셋팅한다.
//	만약 DB가 20번 이상 같은 커넥션으로 사용됬다면 연결을 다시 설정한다.
//
void CMyDB::ReleaseDB(int index)
{
	DB_CONNECTION* pDB = NULL;
	
	if( index < 0 || index >= m_arDB.GetSize() ) return;
	
	try
	{
		if( m_arDB[index] )
		{
			pDB = m_arDB[index];
			// IKING 2002.1.1
			pDB->iCount++;
			//pDB->iCount = 0;
			//
			pDB->dwGetDBTime = 0;
			
			if( pDB->iCount >= 500 && m_strConnect != _T(""))
			{
				pDB->iCount = 0;
				pDB->db.Close();
				
				pDB->db.SetLoginTimeout (10);
				if(!pDB->db.Open(NULL, FALSE, FALSE, m_strConnect))
				{
					TRACE("Fail To Reconnect DB...[ %d ]\n", index );
					return;
				}

				::InterlockedExchange(&(pDB->lRef), 0);

				TRACE("Reconnect to DB...[%d] in [%d]\n", index, m_arDB.GetSize() );
			}
			else
			{
				if( ::InterlockedCompareExchange( (long*)&(pDB->lRef), (long)0, (long)1 ) != (long)1 )
				{
					TRACE("Fail To Release DB...[ %d ]\n", index );
				}
			}
		}
	}
	catch(CMemoryException * e)
	{
		e->ReportError();
		e->Delete();
	}
	catch(CDBException* e)
	{
		e->ReportError();
		e->Delete();
	}
}

