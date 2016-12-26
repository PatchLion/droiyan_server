#ifndef GMMAINWINDOW_H
#define GMMAINWINDOW_H

#include <QMainWindow>
#include "ui_GMMainWindow.h"
#include <QtSql>
#include <QMdiArea>

class CItemsManager;
class CGMMainWindow : public QMainWindow, public Ui::CGMMainWindow
{
    Q_OBJECT
private:
	struct stDBConfig
	{
		QString type;
		QString config;
	};

public:
    explicit CGMMainWindow(QWidget *parent = 0);
    ~CGMMainWindow();

protected Q_SLOTS:
	//Support SQLITE, ODBC, MYSQL
	void onConnectDBSelected(bool checked);
	void onResetConfigFile(bool checked);
	void onItemsManage(bool checked);

private:
	void initMenuBar();
	static QString configFilePath();

private:
	QSqlDatabase	m_dbConnect;
	QMdiArea *m_mdiArea;
	CItemsManager *m_itemsManager;
};

#endif // GMMAINWINDOW_H
