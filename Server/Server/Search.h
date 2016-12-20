///////////////////////////////////////////////////////////////////////////////
// CSearch Class Header files
//
#ifndef __CSEARCH_H
#define __CSEARCH_H

#include "Session.h"

template<class T>
class CSearchBase
{
protected:
	int m_arrayDim;
	T **m_pDescArray;

public:
	CSearchBase()
	{
		m_arrayDim = 0;
		m_pDescArray = NULL;
	};

	CSearchBase(int dim);
	virtual ~CSearchBase();

	int MakeArray(int dim);

	T *GetObject(int idx);
	void SetObjectToFree(int idx);
	void SetObject(int idx, T *pDesc);
};

template <class T>
CSearchBase<T>::CSearchBase(int dim)
{
	MakeArray(dim);
}

template <class T>
CSearchBase<T>::~CSearchBase()
{
	if ( m_pDescArray )
	{
		for ( int i = 0; i < m_arrayDim; i++ )
		{
			m_pDescArray[i] = NULL;
		}

		delete m_pDescArray;

		m_pDescArray = NULL;
	}
}

template <class T>
int CSearchBase<T>::MakeArray(int dim)
{
	m_arrayDim = dim;

	m_pDescArray = new T* [dim+1];
	if ( !m_pDescArray )
		return -1;

	for ( int i = 0; i < dim; i++ )
	{
		m_pDescArray[i] = NULL;
	}

	return dim;
}

template <class T>
void CSearchBase<T>::SetObjectToFree(int idx)
{
	m_pDescArray[idx] = NULL;
}

template <class T>
void CSearchBase<T>::SetObject(int idx, T *pDesc)
{
	m_pDescArray[idx] = pDesc;
}

template <class T>
T* CSearchBase<T>::GetObject( int idx )
{
	if ( m_pDescArray[idx] )
	{
		return m_pDescArray[idx];	
	}

	return NULL;
};

//-----------------------------------------------------------------------------
// CSearch Class Header.
class USER;
class CSearch : public CSearchBase<USER>
{
public:
	CSearch();
	CSearch(int dim);
	~CSearch();

	USER *GetUserUid(int uid);
	void SetUserUid(int uid, USER *pUser);
	void FreeUser( int uid );

};

/*
class CRoom;
class CRoomSearch : public CSearchBase<CRoom>
{
public:
	CRoomSearch();
	CRoomSearch(int dim);
	~CRoomSearch();

	CRoom *GetRoomUid(int uid);
	void SetRoomUid(int uid, CRoom *pRoom);
	void FreeRoom( int uid );

};


class CNPC;
class CNpcSearch : public CSearchBase<CNPC>
{
public:
	CNpcSearch();
	CNpcSearch(int dim);
	~CNpcSearch();

	CNPC *GetNpcUid(int uid);
	void SetNpcUid(int uid, CNPC *pNpc);
	void FreeNpc( int uid );

};
*/

#endif

