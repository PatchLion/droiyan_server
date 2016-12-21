#ifndef __DATA_STRUCT
#define __DATA_STRUCT

struct RHANDLE
{
   long handle;
   long pos;
};

struct RHANDLEHEADER
{
   const RHANDLE* pRH;
   bool bFree;
   DWORD dwTime;
};

struct DNODE
{
   const RHANDLE* pRH;
   DNODE* prev;
   DNODE* next;
};



#endif
