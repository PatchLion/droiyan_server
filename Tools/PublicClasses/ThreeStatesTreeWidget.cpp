#include "ThreeStatesTreeWidget.h"

CThreeStatesTreeWidget::CThreeStatesTreeWidget(QWidget* parent /*= 0*/)
	: QTreeWidget(parent)
	, m_isUpdating(false)
{
	connect(this, &CThreeStatesTreeWidget::itemChanged, this, &CThreeStatesTreeWidget::onItemChanged);
}

CThreeStatesTreeWidget::~CThreeStatesTreeWidget()
{

}

void CThreeStatesTreeWidget::onItemChanged(QTreeWidgetItem * item, int column)
{
	if (0 == column && !m_isUpdating)
	{
		m_isUpdating = true;

		updateChildrenNode(item);
		updateParentNode(item);

		m_isUpdating = false;
	}
}

void CThreeStatesTreeWidget::updateChildrenNode(QTreeWidgetItem* parentItem)
{
	if (parentItem)
	{
		Qt::CheckState state = parentItem->checkState(0);
		if (state == Qt::Checked || state == Qt::Unchecked)
		{
			for (int i = 0; i < parentItem->childCount(); i++)
			{
				QTreeWidgetItem* childItem = parentItem->child(i);
				childItem->setCheckState(0, state);
				updateChildrenNode(childItem);
			}
		}
	}
}

void CThreeStatesTreeWidget::updateParentNode(QTreeWidgetItem* childItem)
{
	if (childItem && childItem->parent())
	{
		QTreeWidgetItem* parentItem = childItem->parent();

		int total = parentItem->childCount();
		int checked = 0;
		for (int i = 0; i < parentItem->childCount(); i++)
		{
			if (parentItem->child(i)->checkState(0) == Qt::Checked)
			{
				checked++;
			}
		}

		if (checked == total)
		{
			parentItem->setCheckState(0, Qt::Checked);
		}
		else if (0 == checked)
		{
			parentItem->setCheckState(0, Qt::Unchecked);
		}
		else
		{
			parentItem->setCheckState(0, Qt::PartiallyChecked);
		}

		updateParentNode(parentItem);
	}
}

