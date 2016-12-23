/********************************************************************************
** Form generated from reading UI file 'GMMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GMMAINWINDOW_H
#define UI_GMMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CGMMainWindow
{
public:
    QAction *actionSdfdf;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CGMMainWindow)
    {
        if (CGMMainWindow->objectName().isEmpty())
            CGMMainWindow->setObjectName(QStringLiteral("CGMMainWindow"));
        CGMMainWindow->resize(800, 600);
        actionSdfdf = new QAction(CGMMainWindow);
        actionSdfdf->setObjectName(QStringLiteral("actionSdfdf"));
        centralwidget = new QWidget(CGMMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        CGMMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CGMMainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        CGMMainWindow->setMenuBar(menubar);
        statusBar = new QStatusBar(CGMMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CGMMainWindow->setStatusBar(statusBar);

        retranslateUi(CGMMainWindow);

        QMetaObject::connectSlotsByName(CGMMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CGMMainWindow)
    {
        CGMMainWindow->setWindowTitle(QApplication::translate("CGMMainWindow", "Droiyan GM tool", 0));
        actionSdfdf->setText(QApplication::translate("CGMMainWindow", "sdfdf", 0));
    } // retranslateUi

};

namespace Ui {
    class CGMMainWindow: public Ui_CGMMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GMMAINWINDOW_H
