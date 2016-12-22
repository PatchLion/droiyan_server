///////////////////////////////////////////////////////////////////////////////
// CIOCP HEADER FILES
#ifndef _IOCPMANAGER_H
#define _IOCPMANAGER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Iocpbase.h"

template <class T>
class CIOCP : public CIOCPBASE
{
public:
	CIOCP() {};
	virtual ~CIOCP() {};

	T *GetUser(int uid)
	{
		return (T *)CIOCPBASE::GetUser(uid);
	}
};

#endif

