// UNI_CHAR.cpp: implementation of the UNI_CHAR class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UNI_CHAR.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// UNI_CHAR.cpp: implementation of the UNI_CHAR class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UNI_CHAR.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//char* UNI_CHAR::UniCodeC[19];

//char* UNI_CHAR::UniCodeV[21];
//char* UNI_CHAR::UniCodeJ[28];


char *UNI_CHAR::UniCodeC[19]={"ㄱ","ㄲ","ㄴ","ㄷ","ㄸ","ㄹ","ㅁ","ㅂ","ㅃ","ㅅ","ㅆ","ㅇ",
	"ㅈ","ㅉ","ㅊ","ㅋ","ㅌ","ㅍ","ㅎ"};
	//유니코드 한글 중성 순서표
char* UNI_CHAR::UniCodeV[21]={"ㅏ","ㅐ","ㅑ","ㅒ","ㅓ","ㅔ","ㅕ","ㅖ","ㅗ","ㅘ","ㅙ","ㅚ",
	"ㅛ","ㅜ","ㅝ","ㅞ","ㅟ","ㅠ","ㅡ","ㅢ","ㅣ"};
	//유니코드 한글 종성 순서표 
char* UNI_CHAR::UniCodeJ[28]={" ","ㄱ","ㄲ","ㄳ","ㄴ","ㄵ","ㄶ","ㄷ","ㄹ","ㄺ","ㄻ","ㄼ","ㄽ",
	"ㄾ","ㄿ","ㅀ","ㅁ","ㅂ","ㅄ","ㅅ","ㅆ","ㅇ","ㅈ","ㅊ","ㅋ","ㅌ","ㅍ","ㅎ"}; 




UNI_CHAR::UNI_CHAR()
{
/* 	char *tmpUniCodeC[19]={"ㄱ","ㄲ","ㄴ","ㄷ","ㄸ","ㄹ","ㅁ","ㅂ","ㅃ","ㅅ","ㅆ","ㅇ",
		"ㅈ","ㅉ","ㅊ","ㅋ","ㅌ","ㅍ","ㅎ"};
		//유니코드 한글 중성 순서표
	 char* tmpUniCodeV[21]={"ㅏ","ㅐ","ㅑ","ㅒ","ㅓ","ㅔ","ㅕ","ㅖ","ㅗ","ㅘ","ㅙ","ㅚ",
		"ㅛ","ㅜ","ㅝ","ㅞ","ㅟ","ㅠ","ㅡ","ㅢ","ㅣ"};
		//유니코드 한글 종성 순서표 
	 char* tmpUniCodeJ[28]={" ","ㄱ","ㄲ","ㄳ","ㄴ","ㄵ","ㄶ","ㄷ","ㄹ","ㄺ","ㄻ","ㄼ","ㄽ",
		"ㄾ","ㄿ","ㅀ","ㅁ","ㅂ","ㅄ","ㅅ","ㅆ","ㅇ","ㅈ","ㅊ","ㅋ","ㅌ","ㅍ","ㅎ"}; 

	 // 초기화를 어떻게 해야 할지 모르겠다..
	 // 그러나 일단 숫자만 가지고 판단하기 때문에..
	 */
}

UNI_CHAR::~UNI_CHAR()
{

}


BOOL UNI_CHAR::CheckString(CString str)
{
	BYTE *cComp;
	int nLength = str.GetLength();
	cComp = (BYTE*)str.GetBuffer(nLength);

	for (int i=0; i < nLength; i++) 
	{
#ifdef KOR_VER			
		int nCode = 949;//korea
#endif
#ifdef CHN_VER
		int nCode = 936; //china
#endif
#ifdef ENG_VER
		int nCode = 1252; //English
#endif
		if ( IsDBCSLeadByteEx(nCode,str.GetAt(i)) ) { // 한글자소일 경우.
			ASSERT(i < nLength-1);
#ifdef KOR_VER			
			CVJ cvj;
			cvj = UNIDivChar(((LPSTR)(LPCTSTR)str)+i);
			if (!CheckUNIChar(cvj)) {
				return FALSE;
			}
#endif
#ifdef CHN_VER
		BYTE cTemp[2];

		memcpy(cTemp,cComp+i,sizeof(BYTE)*2);
		int nLen = MultiByteToWideChar(CP_ACP, 0,(char*)cTemp, -1, NULL, NULL);
		LPWSTR lpszW = new WCHAR[nLen];
		MultiByteToWideChar(CP_ACP, 0, (char*)cTemp, -1, lpszW, nLen);

		WORD wTemp = *(WORD *)lpszW;		
	
		delete[] lpszW;
		if(wTemp < 0x4e00 || wTemp > 0x9fa5){		
			return FALSE;
		}
#endif
			i ++;
		} else { // 영문 자소일 경우.
			if((cComp[i] >= 48 && cComp[i] <= 57) || 
			   (cComp[i] >= 64 && cComp[i] <= 90) ||
			   (cComp[i] >= 97 && cComp[i] <= 122)) 
			{
				
			}
			else{
				return FALSE;
			}
			//TRACE("(%c) \n", temp.GetAt(i));
		}
	}

	return TRUE;
}



BOOL UNI_CHAR::CheckUNIChar(CVJ cvj)
{
	BOOL rev = TRUE;
	if (cvj.C>=0 && cvj.C<19) {
		//TRACE("(%s) ", UniCodeC[cvj.C]);
	}
	else {
		//TRACE("(-) ");
		rev = FALSE;
	}

	if (cvj.V>=0 && cvj.V<21) {
		//TRACE("(%s) ", UniCodeV[cvj.V]);
	}
	else {
		//TRACE("(-) ");
		rev = FALSE;
	}

	if (cvj.J>=0 && cvj.J<28) {
		//TRACE("(%s) \n", UniCodeJ[cvj.J]);
	}
	else {
		//TRACE("(-) \n");
	}

	return rev;
}


UNI_CHAR::CVJ UNI_CHAR::UNIDivChar(char *pDivWord)
{
	CVJ Result; //변환한 초성 중성 종성 값을 넘길 변수
	int cCode,vCode,jCode; //유니코드 한글에서의 초성/중성/종성의 코드값
	char inputSyllable[3]; //넘어온 인자를 복사하여 이용
	
	strncpy(inputSyllable,pDivWord,2);//단어의 첫글자를 복사
	inputSyllable[2]=NULL;//strncpy는 NULL을 붙이지 낳으므로 강제로 넣어줌
	
	//유니코드로 변환, 완성형 코드를 사용해야하면 멜 주세욧(코드테이블 필요)
	int nLen = MultiByteToWideChar(CP_ACP, 0,inputSyllable, -1, NULL, NULL);
	LPWSTR lpszW = new WCHAR[nLen];
	MultiByteToWideChar(CP_ACP, 0, inputSyllable, -1, lpszW, nLen);
	
	
	cCode =(lpszW[0] - 0xAC00) / (588); //588=21*28(초성) 
	vCode =((lpszW[0] - 0xAC00) % (588)) / 28; //588=21*28(중성)
	jCode =(lpszW[0] - 0xAC00) % 28; //(종성)
		
	Result.C=cCode;
	Result.V=vCode;
	Result.J=jCode;
	
	
	delete []lpszW;
	return Result;
}

