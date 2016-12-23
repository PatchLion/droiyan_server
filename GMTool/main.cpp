#include <QtWidgets/QApplication>
#include "GMMainWindow.h"

int main(int argc, char** argv)
{
	QApplication a(argc, argv);

	CGMMainWindow mainWindow;
	mainWindow.show();

	return a.exec();
}

