/********************************************************************************
** Form generated from reading UI file 'ItemsManager.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEMSMANAGER_H
#define UI_ITEMSMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CItemsManager
{
public:

    void setupUi(QWidget *CItemsManager)
    {
        if (CItemsManager->objectName().isEmpty())
            CItemsManager->setObjectName(QStringLiteral("CItemsManager"));
        CItemsManager->resize(400, 300);

        retranslateUi(CItemsManager);

        QMetaObject::connectSlotsByName(CItemsManager);
    } // setupUi

    void retranslateUi(QWidget *CItemsManager)
    {
        CItemsManager->setWindowTitle(QApplication::translate("CItemsManager", "CItemsManager", 0));
    } // retranslateUi

};

namespace Ui {
    class CItemsManager: public Ui_CItemsManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEMSMANAGER_H
