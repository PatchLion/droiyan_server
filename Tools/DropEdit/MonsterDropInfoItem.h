#ifndef MONSTERDROPINFOITEM_H
#define MONSTERDROPINFOITEM_H

#include <QWidget>
#include "NpcItem.h"

namespace Ui {
class CMonsterDropInfoItem;
}

class CMonsterDropInfoItem : public QWidget
{
    Q_OBJECT

public:
	explicit CMonsterDropInfoItem(QWidget *parent = 0);
    explicit CMonsterDropInfoItem(const drop_info& dropitem, QWidget *parent = 0);
    ~CMonsterDropInfoItem();

	void initWithData(const drop_info& info);
	void clear();
private:
	void init();

private:
    Ui::CMonsterDropInfoItem *ui;
	drop_info m_dropInfo;
};

#endif // MONSTERDROPINFOITEM_H
