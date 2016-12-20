#ifndef _OV_H_
#define _OV_H_

struct OV: public OVERLAPPED
{
	OV()
	{ 
		Internal = InternalHigh = Offset = OffsetHigh = 0;
		hEvent = 0; 
	}
};

#endif