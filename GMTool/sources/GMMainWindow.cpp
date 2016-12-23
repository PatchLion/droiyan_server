#include "GMMainWindow.h"
#include "ui_GMMainWindow.h"
#include <QtWidgets>
#include <QtCore>

const char* kDBConfigFileName = "DBConnect.ini";



CGMMainWindow::CGMMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setupUi(this);
	
	QStringList drivers = QSqlDatabase::drivers();
	qDebug() << "DB Driver list: ";
	foreach(QString driver, drivers)
		qDebug() << driver;

	initMenuBar();
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
/*
			dbconn.setDatabaseName(dsn);

			dbconn.setHostName(QString("127.0.0.1"));

			dbconn.setPort(1433);

			dbconn.setUserName(QString("sa"));

			dbconn.setPassword(QString("wang"));*/
			bool r = m_dbConnect.open();

			if (r) {
				qDebug() << "SQL Server 2000 Connect OK!";
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
	setting.setValue("VALUE", "DRIVER={SQL Server};Server=(192.168.10.145);Database=drgame;uid=drgame;pwd=drgame");
	setting.endGroup();
}

QString CGMMainWindow::configFilePath()
{
	return  QApplication::applicationDirPath() + "/" + kDBConfigFileName;
}
