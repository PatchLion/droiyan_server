#pragma once

struct ShopItemData 
{
	int iSid;
	int iNum;
	char BuyName[255];
	int iDn;
	int iAttribute[5];
	int iUpgradeNum;
	int iColor;
};
class ShopSystem
{
public:
	int m_iAllTime;    //每间隔多少秒加元宝
	int m_iAllDnNum;   //每间隔多少元宝
	int m_iZoneNum;
	int m_iZone[255]; //地图ID
	int m_iZoneTime;  //每间隔多少秒加元宝
	int m_iZoneDnNum;   //每间隔多少元宝
	ShopItemData m_Item[512];
	int m_ItemNum;

public:
	ShopSystem(void);
	~ShopSystem(void);
	BOOL ShopLoadConfig();
	BOOL IsZone(int iZone);
	int IsBuyItemName(char *name);
};
