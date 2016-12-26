#ifndef ITEMSMANAGER_H
#define ITEMSMANAGER_H

#include <QWidget>
#include "ui_ItemsManager.h"

class CItemsManager : public QWidget, public Ui::CItemsManager
{
	Q_OBJECT

public:
	CItemsManager(QWidget *parent = 0);
	~CItemsManager();

protected:
	QSize sizeHint() const;
};

#endif // ITEMSMANAGER_H
