///////////////////////////////////////////////////////////////////////////////
// Socket Manager Header file define
//
#ifndef __USERMANAGER_H
#define __USERMANAGER_H

#include "../LibsIncs/Poolbase.h"

class CUserManager : public CPoolBaseManager
{
public:
	int sid;

public:
	CUserManager();
	~CUserManager();

};

#endif
