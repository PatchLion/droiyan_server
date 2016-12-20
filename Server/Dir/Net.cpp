// Net.cpp: implementation of network functions.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BadukDir.h"

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

	u_long argp = 1;
	ioctlsocket (SockId, FIONBIO, &argp);
	connect(SockId,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(SockId, &fds);
	struct timeval t;
	t.tv_sec = 2;
	t.tv_usec = 0;

	select (0, NULL, &fds, NULL, &t);

	if (!FD_ISSET(SockId, &fds))
	{
		closesocket (SockId);
		return INVALID_SOCKET;
	}

	return SockId;
}

SOCKET OpenServer (LPCTSTR servIP, int servPort)
{
	struct sockaddr_in serv_addr;
	SOCKET SockId;
	int reuse = 1;

	memset (&serv_addr, 0, sizeof(serv_addr));

	serv_addr.sin_family      = AF_INET;
	if (servIP == NULL)
		serv_addr.sin_addr.s_addr = htons(INADDR_ANY);
	else
		serv_addr.sin_addr.s_addr = inet_addr(servIP);
	serv_addr.sin_port        = htons(servPort);

	SockId = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt( SockId, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse));
	if (SockId == INVALID_SOCKET ||
		bind(SockId,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == SOCKET_ERROR ||
		listen(SockId,5) == SOCKET_ERROR) 
		return INVALID_SOCKET;
	
	return SockId;
}
