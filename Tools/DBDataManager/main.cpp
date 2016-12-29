#include <QtWidgets/QApplication>
#include <QtCore>
#include <QxOrm.h>
#include <QxOrm_Impl.h>
#include "Char.h"
#include <QTextCodec>

int main(int argc, char**argv)
{ 
	QApplication app(argc, argv);
	//QFile::remove("./qxBlog.sqlite");
	//QTextCodec* codec = QTextCodec::codecForName("GBK");
	//QTextCodec::setCodecForLocale(codec); // ¹Ø¼üÊÇÕâ¾ä

	// Parameters to connect to database
	qx::QxSqlDatabase::getSingleton()->setDriverName("QODBC");
	qx::QxSqlDatabase::getSingleton()->setDatabaseName("DRIVER={SQL SERVER};SERVER=192.168.5.103;DATABASE=drgame;UID=drgame;PWD=drgame;");
	qx::QxSqlDatabase::getSingleton()->setHostName("192.168.5.103");
	qx::QxSqlDatabase::getSingleton()->setUserName("sa");
	qx::QxSqlDatabase::getSingleton()->setPassword("sa");

	qx::QxSqlQuery query("");
	//query.bind(":sex", author::female);

	list_char list_char_of_user;
	QSqlError daoError = qx::dao::fetch_by_query(query, list_char_of_user);
	/*if (!daoError.isValid())
	{
		qx::dump(list_char_of_user, true);
	}*/
	list_char::const_iterator charItor = list_char_of_user.begin();
	for (charItor; list_char_of_user.end() != charItor; charItor++)
	{
		qDebug() << charItor->second->char01;
	}

	return app.exec();
}