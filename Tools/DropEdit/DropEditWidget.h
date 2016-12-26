#ifndef DROPEDITWIDGET_H
#define DROPEDITWIDGET_H

#include <QWidget>
#include "NpcItem.h"

struct stDropInfo : public drop_info
{
	stDropInfo(const drop_info& dropInfo)
	{
		*(drop_info*)this = dropInfo;
	}
	drop_info dropinfo() const { return *(drop_info*)this; }

	QString originFile;
};
typedef QList<stDropInfo> ListDropInfo;
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
	void initDropInfos(const QString& rootDir);
	void updateDropInfoListOnUI();
	bool refreshMonsterAndItemKeyMap(const drop_info& dropinfo, MapKey& monsterMap, MapKey& itemMap);
	bool outputMapKeyToFile(const QString& filepath, const MapKey& mapKey);

	void onIndexChanged();

protected Q_SLOTS:
	void on_pushButtonNext_clicked(bool checked);
	void on_pushButtonPre_clicked(bool checked);
	void on_listWidget_currentRowChanged(int currentRow);
	void on_pushButtonSelect_clicked(bool checked);

private:
    Ui::CDropEditWidget *ui;

	int m_currentIndex;
	ListDropInfo m_listDropInfo;
};

#endif // DROPEDITWIDGET_H
