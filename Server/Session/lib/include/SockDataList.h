#ifndef _SOCKDATALIST_H
#define _SOCKDATALIST_H

class WAIT_SEND_DATA : public CObject  
{
public:
	void *pSocket;
	int dcount;
	BYTE *pData;

public:
	WAIT_SEND_DATA()
	{
		pSocket = NULL;
		dcount = 0;
		pData = NULL;
	};

	~WAIT_SEND_DATA()
	{
		if (pData != NULL)
		{
			delete[] pData;
			pData = NULL;
		};
	};
};

class WAIT_RECV_DATA : public CObject  
{
public:
	void *pSocket;
	int usn;
	int dcount;
	BYTE *pData;
	int m_Type;

public:
	WAIT_RECV_DATA()
	{
		pSocket = NULL;
		usn = -1;
		dcount = 0;
		pData = NULL;
		m_Type = -1;
	};

	~WAIT_RECV_DATA()
	{
		if (pData != NULL)
		{
			pSocket = NULL;
			delete[] pData;
			pData = NULL;
		};
	};
};

#endif
