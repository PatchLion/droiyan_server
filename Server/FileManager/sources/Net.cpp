// Net.cpp: implementation of network functions.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Network Base Module

SOCKET OpenClient (LPCTSTR servIP, int servPort)
{
	struct sockaddr_in serv_addr;
	SOCKET SockId;

	memset (&serv_addr, 0, sizeof(serv_addr));

	serv_addr.sin_family      = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(servIP);
	serv_addr.sin_port        = htons(servPort);

	SockId = socket(AF_INET,SOCK_STREAM,0);
	if (SockId == INVALID_SOCKET) 
		return INVALID_SOCKET;

	if (connect(SockId,(struct sockaddr *)&serv_addr,sizeof(serv_addr)))
		return INVALID_SOCKET;

	return SockId;
}

SOCKET OpenServer (LPCTSTR servIP, int servPort)
{
	struct sockaddr_in serv_addr;
	SOCKET SockId;
	int reuse = 1;

	memset (&serv_addr, 0, sizeof(serv_addr));

	serv_addr.sin_family      = AF_INET;
	if (servIP && servIP[0])
		serv_addr.sin_addr.s_addr = inet_addr(servIP);
	else
		serv_addr.sin_addr.s_addr = htons(INADDR_ANY);
	serv_addr.sin_port        = htons(servPort);

	SockId = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt( SockId, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse));
	if (SockId == INVALID_SOCKET ||
		bind(SockId,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == SOCKET_ERROR ||
		listen(SockId,5) == SOCKET_ERROR) 
		return INVALID_SOCKET;
	
	return SockId;
}
