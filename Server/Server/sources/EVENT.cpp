// EVENT.cpp: implementation of the EVENT class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EVENT.h"
#include "EVENT_DATA.h"
#include "LOGIC.h"
#include "EXEC.h"
#include "LOGIC_ELSE.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EVENT::EVENT()
{
	m_arEvent.SetSize( MAX_EVENT );
}

EVENT::~EVENT()
{
	DeleteAll();
}

BOOL EVENT::LoadEvent(int zone)
{
	DWORD		length, count;
	CString		filename;
	CFile		pFile;
	BYTE		byte;
	char		buf[4096];
	char		first[1024];
	char		temp[1024];
	int			index = 0;
	int			t_index = 0;
	int			event_num;

	EVENT_DATA	*newData = NULL;

	filename.Format( ".\\MAP\\%d.evt", zone);

	m_Zone = zone;

	if( !pFile.Open( filename, CFile::modeRead) ) return FALSE;

	length = (DWORD)pFile.GetLength();
	
	CArchive in(&pFile, CArchive::load);

	count = 0;

	while(count < length)
	{
		in >> byte;	count ++;

		if( (char)byte != '\r' && (char)byte != '\n' ) buf[index++] = byte;

		if(((char)byte == '\n' || count == length ) && index > 1 )
		{
			buf[index] = (BYTE) 0;

			t_index = 0;

			if( buf[t_index] == ';' || buf[t_index] == '/' )		// 주석에 대한 처리
			{
				index = 0;
				continue;
			}

			t_index += ParseSpace( first, buf + t_index );

			if( !strcmp( first, "EVENT" ) )
			{
				t_index += ParseSpace( temp, buf + t_index );	event_num = atoi( temp );

				if( newData ) {	delete newData;	goto cancel_event_load; }

				if( m_arEvent[event_num] ) { TRACE("Event Double !!\n" ); goto cancel_event_load; }
				m_arEvent[event_num] = new EVENT_DATA;
				newData = m_arEvent[event_num];

				newData->m_EventNum = event_num;
			}
			else if( !strcmp( first, "L" ) )
			{
				if( !newData ) goto cancel_event_load;
				
				LOGIC* newLogic = new LOGIC;

				newLogic->Parse( buf + t_index );

				newData->m_arLogic.Add( newLogic );
			}
			else if( !strcmp( first, "E" ) )
			{
				if( !newData ) goto cancel_event_load;

				EXEC* newExec = new EXEC;

				newExec->Parse( buf + t_index );

				newData->m_arExec.Add( newExec );
			}
			else if( !strcmp( first, "A" ) )
			{
				if( !newData ) goto cancel_event_load;

				LOGIC_ELSE* newLogicElse = new LOGIC_ELSE;

				newLogicElse->Parse_and( buf + t_index );

				newData->m_arLogicElse.Add( newLogicElse );
			}
			else if( !strcmp( first, "O" ) )
			{
				if( !newData ) goto cancel_event_load;

				LOGIC_ELSE* newLogicElse = new LOGIC_ELSE;

				newLogicElse->Parse_or( buf + t_index );

				newData->m_arLogicElse.Add( newLogicElse );
			}
			else if( !strcmp( first, "END" ) )
			{
				if( !newData ) goto cancel_event_load;

				newData = NULL;
			}

			index = 0;
		}
	}

	in.Close();
	pFile.Close();

	return TRUE;

cancel_event_load:
	AfxMessageBox("Event Data Load Fail !!!");
	in.Close();
	pFile.Close();
	DeleteAll();
	return FALSE;
}

void EVENT::Init()
{
	DeleteAll();
}

void EVENT::Parsing(char *pBuf)
{
}

void EVENT::DeleteAll()
{
	for( int i = 0; i < m_arEvent.GetSize(); i++)
	{
		if( m_arEvent[i] ) delete m_arEvent[i];
	}

	m_arEvent.RemoveAll();
}
