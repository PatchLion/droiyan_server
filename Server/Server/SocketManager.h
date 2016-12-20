///////////////////////////////////////////////////////////////////////////////
// Socket Manager Header file define
//
#ifndef __SOCKETMANAGER_H
#define __SOCKETMANAGER_H

#include "Poolbase.h"

class CSocketManager : public CPoolBaseManager
{
public:
	int sid;

public:
	CSocketManager();
	~CSocketManager();

};

#endif
