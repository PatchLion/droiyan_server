#include <QtWidgets/QApplication>
#include <QtCore>
#include "DBDataManager.h"

int main(int argc, char**argv)
{ 
	QApplication app(argc, argv);
	CDBDataManager::setServerAddr("192.168.10.145");
	CDBDataManager::setDroiyanUserAndPWD("droiyan", "droiyan");
	CDBDataManager::setDrgameUserAndPWD("drgame", "drgame");
	
	CDBDataManager dbManager;
	dbManager.show();

	return app.exec();
}