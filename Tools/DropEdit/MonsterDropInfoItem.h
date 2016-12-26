#ifndef MONSTERDROPINFOITEM_H
#define MONSTERDROPINFOITEM_H

#include <QWidget>

namespace Ui {
class CMonsterDropInfoItem;
}

class CMonsterDropInfoItem : public QWidget
{
    Q_OBJECT

public:
    explicit CMonsterDropInfoItem(QWidget *parent = 0);
    ~CMonsterDropInfoItem();

private:
    Ui::CMonsterDropInfoItem *ui;
};

#endif // MONSTERDROPINFOITEM_H
