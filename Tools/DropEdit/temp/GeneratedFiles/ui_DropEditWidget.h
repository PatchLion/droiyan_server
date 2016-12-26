/********************************************************************************
** Form generated from reading UI file 'DropEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DROPEDITWIDGET_H
#define UI_DROPEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDropEditWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton;
    QTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;

    void setupUi(QWidget *CDropEditWidget)
    {
        if (CDropEditWidget->objectName().isEmpty())
            CDropEditWidget->setObjectName(QStringLiteral("CDropEditWidget"));
        CDropEditWidget->resize(595, 380);
        verticalLayout = new QVBoxLayout(CDropEditWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(CDropEditWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(CDropEditWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton = new QPushButton(CDropEditWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        treeWidget = new QTreeWidget(CDropEditWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        verticalLayout->addWidget(treeWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(CDropEditWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(CDropEditWidget);

        QMetaObject::connectSlotsByName(CDropEditWidget);
    } // setupUi

    void retranslateUi(QWidget *CDropEditWidget)
    {
        CDropEditWidget->setWindowTitle(QApplication::translate("CDropEditWidget", "Form", 0));
        label->setText(QApplication::translate("CDropEditWidget", "Drop\346\226\207\344\273\266\346\240\271\347\233\256\345\275\225\357\274\232", 0));
        label_2->setText(QApplication::translate("CDropEditWidget", "-", 0));
        pushButton->setText(QApplication::translate("CDropEditWidget", "\351\200\211\346\213\251", 0));
        pushButton_2->setText(QApplication::translate("CDropEditWidget", "\344\277\235\345\255\230", 0));
    } // retranslateUi

};

namespace Ui {
    class CDropEditWidget: public Ui_CDropEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DROPEDITWIDGET_H
