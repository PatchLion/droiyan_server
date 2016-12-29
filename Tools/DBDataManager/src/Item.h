#ifndef Item_h__
#define Item_h__
#include "precompiled.h"
#include <QxOrm_Impl.h>
class QX_DATABASE_DLL_EXPORT CItem
{
public:
	CItem() : charNum(0){}
	virtual ~CItem(){}

public:
	int sid;
	int pid;
	int sid2;
	QString name;
	QString text;
	int byWeight;
	int dn;
	int byRLevel;
		/*[byClass][tinyint] NULL,
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
};

QX_REGISTER_PRIMARY_KEY(CItem, QString)
QX_REGISTER_HPP_QX_DATABASE(CItem, qx::trait::no_base_class_defined, 0)

typedef qx_shared_ptr<CItem> item_ptr;
typedef qx::QxCollection<QString, item_ptr> list_item;
#endif // Item_h__
