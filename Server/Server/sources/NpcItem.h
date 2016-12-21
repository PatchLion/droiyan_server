// NpcItem.h: interface for the CNpcItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPCITEM_H__56D8779F_271E_4B39_92CF_3DA33366FBA8__INCLUDED_)
#define AFX_NPCITEM_H__56D8779F_271E_4B39_92CF_3DA33366FBA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNpcItem  
{
public:

	int **m_ppItem;
	int m_nRow;
	int m_nField;

	CNpcItem();
	~CNpcItem();
};

struct drop_novelity {
	char name[64];//物品名称
	byte code1;//物品代码
	byte code2;
	int per;
};
struct drop_info {
	char name[64]; //怪物名称
	byte code1;//怪物种类
	byte code2;
	int money;//掉钱数量
	int DropLeechdom;//掉药品几率
	int DropNovelity;//掉物品几率
	int n; //物品种类数量
	struct drop_novelity novelity[256];
};
struct convert_table{ //100级物品生成表
	char src_name[64];
	SHORT Ssid;
	char dst_name[64];
	SHORT Dsid;
	BOOL have;
};

#endif // !defined(AFX_NPCITEM_H__56D8779F_271E_4B39_92CF_3DA33366FBA8__INCLUDED_)
