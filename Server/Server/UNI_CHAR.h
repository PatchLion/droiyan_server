// UNI_CHAR.h: interface for the UNI_CHAR class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNI_CHAR_H__D72EBF2D_980C_4CC2_B41E_B0DE75BF52E9__INCLUDED_)
#define AFX_UNI_CHAR_H__D72EBF2D_980C_4CC2_B41E_B0DE75BF52E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class UNI_CHAR  
{
public:
	//typedef struct 
	class CVJ
	{
		friend UNI_CHAR;
	protected:
		int C;
		int V;
		int J;
	}; //초성 중성 종성의 번호를 저장할 구조체
	
	static BOOL CheckString(CString str);

	UNI_CHAR();
	virtual ~UNI_CHAR();
protected:
	static BOOL CheckUNIChar(CVJ cvj);
	static CVJ  UNIDivChar(char *pDivWord);


protected:
	//유니코드의 자모 번호
	//유니코드 한글 초성 순서표
	static char *UniCodeC[19];
	//유니코드 한글 중성 순서표
	static char *UniCodeV[21];
	//유니코드 한글 종성 순서표 
	static char *UniCodeJ[28];
};

#endif // !defined(AFX_UNI_CHAR_H__D72EBF2D_980C_4CC2_B41E_B0DE75BF52E9__INCLUDED_)
