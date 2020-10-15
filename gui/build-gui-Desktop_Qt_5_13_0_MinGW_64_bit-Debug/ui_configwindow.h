/********************************************************************************
** Form generated from reading UI file 'configwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGWINDOW_H
#define UI_CONFIGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigWindow
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelAlpha;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEditAlpha;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonAlpha;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelFont;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *lineEditFont;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButtonFont;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *ConfigWindow)
    {
        if (ConfigWindow->objectName().isEmpty())
            ConfigWindow->setObjectName(QString::fromUtf8("ConfigWindow"));
        ConfigWindow->resize(400, 300);
        widget = new QWidget(ConfigWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 20, 351, 142));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelAlpha = new QLabel(widget);
        labelAlpha->setObjectName(QString::fromUtf8("labelAlpha"));

        horizontalLayout->addWidget(labelAlpha);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        lineEditAlpha = new QLineEdit(widget);
        lineEditAlpha->setObjectName(QString::fromUtf8("lineEditAlpha"));

        horizontalLayout->addWidget(lineEditAlpha);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButtonAlpha = new QPushButton(widget);
        pushButtonAlpha->setObjectName(QString::fromUtf8("pushButtonAlpha"));

        horizontalLayout->addWidget(pushButtonAlpha);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelFont = new QLabel(widget);
        labelFont->setObjectName(QString::fromUtf8("labelFont"));

        horizontalLayout_2->addWidget(labelFont);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        lineEditFont = new QLineEdit(widget);
        lineEditFont->setObjectName(QString::fromUtf8("lineEditFont"));

        horizontalLayout_2->addWidget(lineEditFont);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        pushButtonFont = new QPushButton(widget);
        pushButtonFont->setObjectName(QString::fromUtf8("pushButtonFont"));

        horizontalLayout_2->addWidget(pushButtonFont);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(ConfigWindow);

        QMetaObject::connectSlotsByName(ConfigWindow);
    } // setupUi

    void retranslateUi(QWidget *ConfigWindow)
    {
        ConfigWindow->setWindowTitle(QCoreApplication::translate("ConfigWindow", "Config", nullptr));
        labelAlpha->setText(QCoreApplication::translate("ConfigWindow", "Alpha", nullptr));
        pushButtonAlpha->setText(QCoreApplication::translate("ConfigWindow", "Confirm", nullptr));
        labelFont->setText(QCoreApplication::translate("ConfigWindow", "FontSize", nullptr));
        pushButtonFont->setText(QCoreApplication::translate("ConfigWindow", "Confirm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigWindow: public Ui_ConfigWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGWINDOW_H
