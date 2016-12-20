// Hyper.h: interface for the CHyper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HYPER_H__25CE02AC_A0AB_4C48_BA34_86D3185407F8__INCLUDED_)
#define AFX_HYPER_H__25CE02AC_A0AB_4C48_BA34_86D3185407F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHyper  
{
public:
	CHyper();
	virtual ~CHyper();

	struct HyperText{
		int			m_nCol;
		int			m_nRow;
		int			m_nWidth;
		int			m_nEvent;
		COLORREF	m_FontColor;
		int			m_nZoneNum;
		int			m_nTextlength;
		CString		m_strText;
	};
	struct HyperImg{
		CRect rectImg;
		int m_Event;
		int m_ZoneNum;
		int m_nImgId;
	};

public:
	void InitBuf();
	void GetHyperText(TCHAR *pBuf, int nSize);
	TCHAR m_Buf[10000];

	CPoint m_StartPos;
	int m_nViewLineCount;
	int m_nCountLine;
	HyperText		m_HyperText[1024];

	int m_nImgCount;
	HyperImg		m_HyperImg[100];

	void		load();
	int			save(TCHAR *pBuf);
};

#endif // !defined(AFX_HYPER_H__25CE02AC_A0AB_4C48_BA34_86D3185407F8__INCLUDED_)
