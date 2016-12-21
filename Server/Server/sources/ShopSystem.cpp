#include "stdafx.h"
#include "ShopSystem.h"

ShopSystem::ShopSystem(void)
{
	m_iAllTime = 0;    //每间隔多少秒加元宝
	m_iAllDnNum = 0;   //每间隔多少元宝
	m_iZoneNum = 0;
	memset(m_iZone,0,sizeof(int) *255); //地图ID
	m_iZoneTime = 0;  //每间隔多少秒加元宝
	m_iZoneDnNum = 0;   //每间隔多少元宝
	memset(m_Item,0,sizeof(ShopItemData)*512);
	m_ItemNum = 0;

}

ShopSystem::~ShopSystem(void)
{
}
BOOL ShopSystem::ShopLoadConfig()
{
	char szTemp[255];


	m_iAllDnNum = GetPrivateProfileInt("元宝",
		"全局元宝",0,".\\Shop.ini");
	m_iAllTime = GetPrivateProfileInt("元宝",
		"全局时间",0,".\\Shop.ini");
	m_iAllTime = 1000 * m_iAllTime;
	if (m_iAllTime == 0)
	{
		m_iAllTime = 10000000;
	}

	m_iZoneDnNum = GetPrivateProfileInt("元宝",
		"地图元宝",0,".\\Shop.ini");
	m_iZoneTime = GetPrivateProfileInt("元宝",
		"地图时间",0,".\\Shop.ini");
	m_iZoneTime = 1000 * m_iZoneTime;
	if (m_iZoneTime == 0)
	{
		m_iZoneTime = 10000000;
	}
	m_iZoneNum = GetPrivateProfileInt("元宝",
		"ZONENUM",0,".\\Shop.ini");
	for (int i=0; i<m_iZoneNum; i++)
	{
		sprintf(szTemp,"ZONE%02d",i);
		m_iZone[i] = GetPrivateProfileInt("元宝",
			szTemp ,0,".\\Shop.ini");
	}
	
	m_ItemNum = GetPrivateProfileInt("商品",
		"数量",0,".\\Shop.ini");

	for (int i=0; i<m_ItemNum; i++)
	{
		sprintf(szTemp,"物品%02d",i);
		m_Item[i].iSid = GetPrivateProfileInt("商品",
			szTemp ,0,".\\Shop.ini");

		sprintf(szTemp,"数量%02d",i);
		m_Item[i].iNum = GetPrivateProfileInt("商品",
			szTemp ,0,".\\Shop.ini");
		sprintf(szTemp,"价格%02d",i);
		m_Item[i].iDn = GetPrivateProfileInt("商品",
			szTemp ,0,".\\Shop.ini");
		sprintf(szTemp,"购买名字%02d",i);
		int iLen = GetPrivateProfileString(
			"商品",
			szTemp,
			NULL ,
			m_Item[i].BuyName,
			20,
			".\\Shop.ini"
			);
		m_Item[i].BuyName[iLen] = '\0';

		sprintf(szTemp,"属性%02d-1",i);
		m_Item[i].iAttribute[0]= GetPrivateProfileInt("商品",
			szTemp ,0,".\\Shop.ini");
		sprintf(szTemp,"属性%02d-2",i);
		m_Item[i].iAttribute[1]= GetPrivateProfileInt("商品",
			szTemp ,0,".\\Shop.ini");
		sprintf(szTemp,"属性%02d-3",i);
		m_Item[i].iAttribute[2]= GetPrivateProfileInt("商品",
			szTemp ,0,".\\Shop.ini");
		sprintf(szTemp,"属性%02d-4",i);
		m_Item[i].iAttribute[3]= GetPrivateProfileInt("商品",
			szTemp ,0,".\\Shop.ini");
		sprintf(szTemp,"属性%02d-5",i);
		m_Item[i].iAttribute[4]= GetPrivateProfileInt("商品",
			szTemp ,0,".\\Shop.ini");
		sprintf(szTemp,"颜色%02d",i);
		m_Item[i].iColor= GetPrivateProfileInt("商品",
			szTemp ,0,".\\Shop.ini");
		sprintf(szTemp,"改数%02d",i);
		m_Item[i].iUpgradeNum= GetPrivateProfileInt("商品",
			szTemp ,0,".\\Shop.ini");

	}
	
	return TRUE;

}

BOOL ShopSystem::IsZone(int iZone)
{
	for (int i=0; i<m_iZoneNum; i++)
	{
		if (m_iZone[i] == iZone)
		{
			return TRUE;
		}
	}
	return FALSE;
}

int ShopSystem::IsBuyItemName(char *name)
{
	for (int i=0; i<m_ItemNum; i++)
	{
		if(strcmp(m_Item[i].BuyName,name) == 0)
		{
			return i;
		}
	}
	return -1;
}
