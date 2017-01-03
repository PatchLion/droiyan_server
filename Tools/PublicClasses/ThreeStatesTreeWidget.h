//ÈýÌ¬Ê÷
#ifndef ThreeStatesTreeWidget_h__
#define ThreeStatesTreeWidget_h__

#include <QtWidgets>

class CThreeStatesTreeWidget : public QTreeWidget
{
	Q_OBJECT
public:
	CThreeStatesTreeWidget(QWidget* parent = 0);
	~CThreeStatesTreeWidget();

protected Q_SLOTS:
	void onItemChanged(QTreeWidgetItem * item, int column);

private:
	void updateChildrenNode(QTreeWidgetItem* parentItem);
	void updateParentNode(QTreeWidgetItem* childItem);

private:
	bool m_isUpdating;
};

#endif // ThreeStatesTreeWidget_h__
