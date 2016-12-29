#include "Item.h"

QX_REGISTER_CPP_QX_DATABASE(CItem)

namespace qx {
	template <> void register_class(QxClass<CItem> & t)
	{
		t.setName("CHARS");

		t.id(&CItem::account, "strAccount");
		t.data(&CItem::char01, "strItem01");
		t.data(&CItem::char02, "strItem02");
		t.data(&CItem::char03, "strItem03");
	/*	[sSid2][smallint] NULL,
			[strName][varchar](50) COLLATE Chinese_PRC_CI_AS NULL,
			[strText][varchar](100) COLLATE Chinese_PRC_CI_AS NULL,
			[byWeight][tinyint] NULL,
			[iDN][int] NULL,
			[byRLevel][tinyint] NULL,
			[byClass][tinyint] NULL,
			[byWear][tinyint] NULL,
			[sDuration][smallint] NULL,
			[sDefense][smallint] NULL,
			[byAX][tinyint] NULL,
			[byAY][tinyint] NULL,
			[byAZ][tinyint] NULL,
			[byRstr][tinyint] NULL,
			[byRdex][tinyint] NULL,
			[byRvol][tinyint] NOT NULL,
			[sAttackDelay][smallint] NULL,
			[byRange][tinyint] NULL,
			[byErrorRate][tinyint] NULL,
			[sBullNum][smallint] NULL,
			[byBullType][tinyint] NULL,
			[bySubDefense][tinyint] NULL,
			[bySubCure][tinyint] NULL,
			[sRepairHP][smallint] NULL,
			[sRepairPP][smallint] NULL,
			[sRepairSP][smallint] NULL,
			[sEvent][smallint] NULL,
			[sZone][smallint] NULL,
			[byMPP][tinyint] NULL,
			[sCTime][smallint] NULL,
			[bySpecial][tinyint] NULL*/
		t.fct_0<int>(&CItem::charNum, "sItemNum");
	}
}
