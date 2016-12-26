#ifndef Functions_h__
#define Functions_h__

#include <QtCore>

#include "NpcItem.h"

namespace DropEdit
{
	//从文件获取掉落物品信息
	bool getDropInfoFromINIFile(const QString& filepath, drop_info& dropItem);
}
#endif // Functions_h__