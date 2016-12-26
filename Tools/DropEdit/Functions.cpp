#include "Functions.h"
#include <QtCore>

bool DropEdit::getDropInfoFromINIFile(const QString& filepath, drop_info& dropItem)
{
	QFile file(filepath);
	if (!file.open(QIODevice::ReadOnly))
	{
		return false;
	}

	const QString monster = QString::fromLocal8Bit(file.readLine());
	QStringList listInfo = monster.split("-");

	if (7 == listInfo.size())
	{
		listInfo.removeAt(0);
	}
	else if (8 == listInfo.size())
	{
		listInfo.removeAt(0);
		listInfo.removeAt(0);
	}
	else
	{
		return false;
	}

	const QString fileName = QFileInfo(filepath).baseName().trimmed();

	strcpy(dropItem.name, fileName.toLocal8Bit().data());
	dropItem.code1 = listInfo[0].trimmed().toUShort();
	dropItem.code2 = listInfo[1].trimmed().toUShort();
	dropItem.money = listInfo[2].trimmed().toInt();
	dropItem.DropLeechdom = listInfo[3].trimmed().toInt();
	dropItem.DropNovelity = listInfo[4].trimmed().toInt();
	dropItem.n = listInfo[5].trimmed().toInt();

	for (int i = 0; i < dropItem.n; i++){
		const QString item = QString::fromLocal8Bit(file.readLine());
		const QStringList listItemInfo = item.split("-");

		if (listItemInfo.size() != 4)
		{
			continue;
		}

		//月之镯 - 44 - 0 - 500 
		strcpy(dropItem.novelity[i].name, listItemInfo[0].trimmed().toLocal8Bit().data());
		dropItem.novelity[i].code1 = listItemInfo[1].trimmed().toUShort();
		dropItem.novelity[i].code2 = listItemInfo[2].trimmed().toUShort();
		dropItem.novelity[i].per = listItemInfo[3].trimmed().toInt();
		if (dropItem.novelity[i].code1>256 || dropItem.novelity[i].code2 > 4){
			qWarning() << ("错误物品代码 %s ,%s\n", dropItem.name, dropItem.novelity[i].name);
		}

		if (file.atEnd())
		{
			break;
		}
	}

	return true;
}