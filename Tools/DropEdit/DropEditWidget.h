#ifndef DROPEDITWIDGET_H
#define DROPEDITWIDGET_H

#include <QWidget>
#include "NpcItem.h"

typedef QList<drop_info> ListDropInfo;
typedef QMap<QString, QStringList> MapKey;

namespace Ui {
class CDropEditWidget;
}

class CDropEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CDropEditWidget(QWidget *parent = 0);
    ~CDropEditWidget();

protected:
	void initDropInfos();
	void updateDropInfoListOnUI();
	bool refreshMonsterAndItemKeyMap(const drop_info& dropinfo, MapKey& monsterMap, MapKey& itemMap);
	bool outputMapKeyToFile(const QString& filepath, const MapKey& mapKey);
private:
    Ui::CDropEditWidget *ui;

	ListDropInfo m_listDropInfo;
};

#endif // DROPEDITWIDGET_H
