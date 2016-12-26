#include "GMMainWindow.h"
#include "ui_GMMainWindow.h"
#include <QtWidgets>
#include <QtCore>
#include "ItemsManager.h"

const char* kDBConfigFileName = "DBConnect.ini";



CGMMainWindow::CGMMainWindow(QWidget *parent)
	: QMainWindow(parent)
	, m_itemsManager(0)
{
	setupUi(this);

	m_mdiArea = new QMdiArea;
	m_mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	m_mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setCentralWidget(m_mdiArea);

	QStringList drivers = QSqlDatabase::drivers();
	qDebug() << "DB Driver list: ";
	foreach(QString driver, drivers)
		qDebug() << driver;

	initMenuBar();

	setUnifiedTitleAndToolBarOnMac(true);
}

CGMMainWindow::~CGMMainWindow()
{
}

void CGMMainWindow::initMenuBar()
{ 
	//Start
	QMenu* start_menu = new QMenu(tr("Start"));
	menubar->addMenu(start_menu);

	//ConnectDB
	QAction* connect_db_menu = start_menu->addAction(tr("Connect DB"));
	connect(connect_db_menu, &QAction::triggered, this, &CGMMainWindow::onConnectDBSelected);
	
	//Rest Config File
	QAction* reset_config_file = start_menu->addAction(tr("Reset config file"));
	connect(reset_config_file, &QAction::triggered, this, &CGMMainWindow::onResetConfigFile);




	//////////////////////////////////////////////////////////////////////////
	//Items Manage
	QAction* items_mgr_menu = menubar->addAction(tr("Items Manage"));
	connect(items_mgr_menu, &QAction::triggered, this, &CGMMainWindow::onItemsManage);

}

void CGMMainWindow::onConnectDBSelected(bool checked)
{
	QString db_type, db_value;
	QSettings setting(configFilePath(), QSettings::IniFormat);
	setting.beginGroup("Config");
	db_type = setting.value("DB").toString();
	db_value = setting.value("VALUE").toString();
	setting.endGroup();

	if (!db_type.isEmpty())
	{
		if ("ODBC" == db_type.trimmed().toUpper())
		{

			m_dbConnect = QSqlDatabase::addDatabase("QODBC");
			
			if (!m_dbConnect.isValid())
			{
				QMessageBox::warning(this, tr("Failure"), tr("Invalid DB type!"));
				return;
			}

			if (db_value.isEmpty())
			{
				QMessageBox::warning(this, tr("Failure"), tr("Invalid DB Value!"));
				return;
			}

			m_dbConnect.setDatabaseName(db_value);
			m_dbConnect.setHostName(QString("192.168.5.103"));
			m_dbConnect.setPort(1433);
			m_dbConnect.setUserName(QString("sa"));
			m_dbConnect.setPassword(QString("sa"));
			bool r = m_dbConnect.open();

			if (r) {
				qDebug() << "SQL Server 2000 Connect OK!";


				QSqlQuery query;
				
				if (!query.exec("SELECT Name FROM SysObjects Where XType='U' orDER BY Name"))
				{
					qWarning() << query.lastError().text();
				}
				
				qDebug() << "size = " << query.at();

				while (query.next())
				{
					QString name = query.value(0).toString();
					qDebug() << name;
				}
				
			}
			else {
				qDebug() << m_dbConnect.lastError().text();
			}
		}
	}
	else
	{
		QMessageBox::warning(this, tr("Failure"), tr("Invalid config!"));
	}
}

void CGMMainWindow::onResetConfigFile(bool checked)
{
	QSettings setting(configFilePath(), QSettings::IniFormat);
	setting.beginGroup("Config");
	setting.setValue("DB", "ODBC");
	setting.setValue("VALUE", "DRIVER={SQL Server};Server=192.168.5.103;Database=drgame;uid=sa;pwd=sa");
	setting.endGroup();
}

QString CGMMainWindow::configFilePath()
{
	return  QApplication::applicationDirPath() + "/" + kDBConfigFileName;
}

void CGMMainWindow::onItemsManage(bool checked)
{
	if (!m_itemsManager)
	{
		m_itemsManager = new CItemsManager;
		m_mdiArea->addSubWindow(m_itemsManager);
	}
	
	m_itemsManager->show();
}
