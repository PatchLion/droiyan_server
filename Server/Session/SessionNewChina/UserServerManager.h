///////////////////////////////////////////////////////////////////////////////
// Socket Manager Header file define
//
#ifndef __USERSERVERMANAGER_H
#define __USERSERVERMANAGER_H

#include "../LibsIncs/Poolbase.h"

class CUserServerManager : public CPoolBaseManager
{
public:
	int sid;

public:
	CUserServerManager();
	~CUserServerManager();

};

#endif
