///////////////////////////////////////////////////////////////////////////////
// Socket Resource array header files

#ifndef __USERSERVERRESOURCEARRAY_H
#define __USERSERVERRESOURCEARRAY_H

#include "../LibsIncs/Poolbase.h"

class CUserServerResourceArray : public CResourceArray
{
public:
	CUserServerResourceArray() {};
	CUserServerResourceArray(long dwSize);
	virtual ~CUserServerResourceArray();

	long GetResourceHandle();
	void ReleaseResourceHandle(long hResHandle);

	int GetUsedResourceCount();

	void SetFree(const long position);
	int TimeOutSetFree(const long position);

};

#endif