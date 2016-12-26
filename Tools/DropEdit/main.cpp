#include <QtWidgets/QApplication>
#include "DropEditWidget.h"

int main(int argc, char** argv)
{
	QApplication a(argc, argv);

	CDropEditWidget mainWindow;
	mainWindow.show();

	return a.exec();
}

