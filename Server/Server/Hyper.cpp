// Hyper.cpp: implementation of the CHyper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "Hyper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHyper::CHyper()
{
	InitBuf();
}

CHyper::~CHyper()
{

}

int CHyper::save(TCHAR *pBuf)
{
	int nOffset = 0,i;

	memcpy(pBuf+nOffset,(char*)&m_StartPos.x,sizeof(long));
	nOffset+=sizeof(long);//시작좌표 저장x
	memcpy(pBuf+nOffset,(char*)&m_StartPos.y,sizeof(long));
	nOffset+=sizeof(long);//시작좌표 저장y

	memcpy(pBuf+nOffset,(char*)&m_nViewLineCount,sizeof(int));
	nOffset+=sizeof(int);//몇개의 행을 보여줄건가
	memcpy(pBuf+nOffset,(char*)&m_nCountLine,sizeof(int));
	nOffset+=sizeof(int);//몇개의 자료(입력된거)를 가지고 있나...
	for(i = 0; i<m_nCountLine ; i++)
	{
		memcpy(pBuf+nOffset,(char*)&m_HyperText[i].m_nCol,sizeof(int));
		nOffset+=sizeof(int);
		memcpy(pBuf+nOffset,(char*)&m_HyperText[i].m_nRow,sizeof(int));
		nOffset+=sizeof(int);
		memcpy(pBuf+nOffset,(char*)&m_HyperText[i].m_nWidth,sizeof(int));
		nOffset+=sizeof(int);
		memcpy(pBuf+nOffset, (char*)&m_HyperText[i].m_nEvent, sizeof(int));
		nOffset+=sizeof(int);
		memcpy(pBuf+nOffset, (char*)&m_HyperText[i].m_FontColor, sizeof(COLORREF));
		nOffset+=sizeof(COLORREF);
		memcpy(pBuf+nOffset, (char*)&m_HyperText[i].m_nZoneNum, sizeof(int));
		nOffset+=sizeof(int);
		m_HyperText[i].m_nTextlength = m_HyperText[i].m_strText.GetLength();
		memcpy(pBuf+nOffset, (char*)&m_HyperText[i].m_nTextlength, sizeof(int));
		nOffset+=sizeof(int);                                                                  
		memcpy(pBuf+nOffset, m_HyperText[i].m_strText.GetBuffer(m_HyperText[i].m_nTextlength), m_HyperText[i].m_nTextlength);
		nOffset +=m_HyperText[i].m_nTextlength;
	}

	memcpy(pBuf+nOffset,(char*)&m_nImgCount,sizeof(int));
	nOffset+=sizeof(int);//몇개의 자료(그림)를 가지고 있나...

	for(i = 0;i < m_nImgCount;i++)
	{
		CRect temp = m_HyperImg[i].rectImg;

		memcpy(pBuf+nOffset,(char*)&temp.top,sizeof(long));
		nOffset+=sizeof(long);
		memcpy(pBuf+nOffset,(char*)&temp.bottom ,sizeof(long));
		nOffset+=sizeof(long);
		memcpy(pBuf+nOffset,(char*)&temp.left,sizeof(long));
		nOffset+=sizeof(long);
		memcpy(pBuf+nOffset,(char*)&temp.right,sizeof(long));
		nOffset+=sizeof(long);
		memcpy(pBuf+nOffset,(char*)&m_HyperImg[i].m_Event,sizeof(int));
		nOffset+=sizeof(int);
		memcpy(pBuf+nOffset,(char*)&m_HyperImg[i].m_ZoneNum,sizeof(int));
		nOffset+=sizeof(int);
		memcpy(pBuf+nOffset,(char*)&m_HyperImg[i].m_nImgId,sizeof(int));
		nOffset+=sizeof(int);
	}

	return nOffset;
}

void CHyper::load()
{
	int i;
	int nOffset = 0;
	char temp_text[10000];
	memcpy((char*)&m_StartPos.x,m_Buf+nOffset,sizeof(long));
	nOffset+=sizeof(long);//시작좌표 저장x
	memcpy((char*)&m_StartPos.y,m_Buf+nOffset,sizeof(long));
	nOffset+=sizeof(long);//시작좌표 저장y
	memcpy((char*)&m_nViewLineCount,m_Buf+nOffset,sizeof(int));
	nOffset+=sizeof(int);//몇개의 행을 보여줄건가
	memcpy((char*)&m_nCountLine,m_Buf+nOffset,sizeof(int));
	nOffset+=sizeof(int);//몇개의 자료(입력된거)를 가지고 있나...
	
	for(i = 0; i < m_nCountLine; i++)
	{
	
		memcpy((char*)&m_HyperText[i].m_nCol,m_Buf+nOffset,sizeof(int));
		nOffset+=sizeof(int);
		memcpy((char*)&m_HyperText[i].m_nRow,m_Buf+nOffset,sizeof(int));
		nOffset+=sizeof(int);
		memcpy((char*)&m_HyperText[i].m_nWidth,m_Buf+nOffset,sizeof(int));
		nOffset+=sizeof(int);
		memcpy((char*)&m_HyperText[i].m_nEvent,m_Buf+nOffset,sizeof(int));
		nOffset+=sizeof(int);
		memcpy((char*)&m_HyperText[i].m_FontColor,m_Buf+nOffset,sizeof(COLORREF));
		nOffset+=sizeof(COLORREF);
		memcpy((char*)&m_HyperText[i].m_nZoneNum,m_Buf+nOffset,sizeof(int));
		nOffset+=sizeof(int);
		memcpy((char*)&m_HyperText[i].m_nTextlength,m_Buf+nOffset,sizeof(int));
		nOffset+=sizeof(int);                                                                   
		memcpy((char*)&temp_text,m_Buf+nOffset, m_HyperText[i].m_nTextlength);
		nOffset +=m_HyperText[i].m_nTextlength;
		m_HyperText[i].m_strText = temp_text;
		m_HyperText[i].m_strText = m_HyperText[i].m_strText.Left(m_HyperText[i].m_nTextlength);
	}
	
	memcpy((char*)&m_nImgCount,m_Buf+nOffset,sizeof(int));
	nOffset+=sizeof(int);//몇개의 자료(그림)를 가지고 있나...

	for(i = 0;i < m_nImgCount;i++)
	{
		CRect temp;
		memcpy((char*)&m_HyperImg[i].rectImg.top,m_Buf+nOffset,sizeof(long));
		nOffset+=sizeof(long);
		memcpy((char*)&m_HyperImg[i].rectImg.bottom,m_Buf+nOffset,sizeof(long));
		nOffset+=sizeof(long);
		memcpy((char*)&m_HyperImg[i].rectImg.left,m_Buf+nOffset,sizeof(long));
		nOffset+=sizeof(long);
		memcpy((char*)&m_HyperImg[i].rectImg.right,m_Buf+nOffset,sizeof(long));
		nOffset+=sizeof(long);
		memcpy((char*)&m_HyperImg[i].m_Event,m_Buf+nOffset,sizeof(int));
		nOffset+=sizeof(int);
		memcpy((char*)&m_HyperImg[i].m_ZoneNum,m_Buf+nOffset,sizeof(int));
		nOffset+=sizeof(int);
		memcpy((char*)&m_HyperImg[i].m_nImgId,m_Buf+nOffset,sizeof(int));
		nOffset+=sizeof(int);
		/*m_HyperImg[i].rectImg.top+=  m_StartPos.y;
		m_HyperImg[i].rectImg.bottom+=  m_StartPos.y;
		m_HyperImg[i].rectImg.left+=  m_StartPos.x;
		m_HyperImg[i].rectImg.right+=  m_StartPos.x;*/
	}
}


void CHyper::GetHyperText(TCHAR *pBuf, int nSize)
{
	::CopyMemory(m_Buf, pBuf, nSize);
}

void CHyper::InitBuf()
{
	::ZeroMemory(m_Buf, sizeof(m_Buf));
}
