///////////////////////////////////////////////////////////////////////////////
// Socket Resource array header files

#ifndef __SOCKETRESOURCEARRAY_H
#define __SOCKETRESOURCEARRAY_H

#include "Poolbase.h"

class CSockResourceArray : public CResourceArray
{
public:
	CSockResourceArray() {};
	CSockResourceArray(long dwSize);
	virtual ~CSockResourceArray();

	long GetResourceHandle();
	void ReleaseResourceHandle(long hResHandle);

	int GetUsedResourceCount();
	void SetFree(const long position);
	int TimeOutSetFree(const long position);

};

#endif