///////////////////////////////////////////////////////////////////////////////
// Socket Resource array header files

#ifndef __USERRESOURCEARRAY_H
#define __USERRESOURCEARRAY_H

#include "Poolbase.h"

class CUserResourceArray : public CResourceArray
{
public:
	CUserResourceArray() {};
	CUserResourceArray(long dwSize);
	virtual ~CUserResourceArray();

	long GetResourceHandle();
	void ReleaseResourceHandle(long hResHandle);

	int GetUsedResourceCount();

	void SetFree(const long position);
	int TimeOutSetFree(const long position);

};

#endif