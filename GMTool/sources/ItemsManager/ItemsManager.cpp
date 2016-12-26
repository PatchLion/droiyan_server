#include "ItemsManager.h"

CItemsManager::CItemsManager(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
}

CItemsManager::~CItemsManager()
{

}

QSize CItemsManager::sizeHint() const
{
	return QSize(600, 600);
}
