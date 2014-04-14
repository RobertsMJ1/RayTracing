/********************************************************************************
** Form generated from reading UI file 'firsttime.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIRSTTIME_H
#define UI_FIRSTTIME_H

#include <MyGLWidget.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "FilenameLine.h"

QT_BEGIN_NAMESPACE

class Ui_FirstTimeClass
{
public:
    QWidget *centralWidget;
    MyGLWidget *widget;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    FilenameLine *lineEdit;
    QPushButton *pushButton_13;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FirstTimeClass)
    {
        if (FirstTimeClass->objectName().isEmpty())
            FirstTimeClass->setObjectName(QStringLiteral("FirstTimeClass"));
        FirstTimeClass->resize(847, 527);
        centralWidget = new QWidget(FirstTimeClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new MyGLWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 631, 471));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(660, 150, 51, 23));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(720, 150, 51, 23));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(780, 150, 51, 23));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(720, 120, 51, 23));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(680, 210, 61, 31));
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(750, 210, 61, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(730, 280, 31, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(730, 100, 46, 13));
        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(730, 300, 21, 23));
        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(730, 340, 21, 23));
        pushButton_9 = new QPushButton(centralWidget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(690, 320, 21, 23));
        pushButton_10 = new QPushButton(centralWidget);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setGeometry(QRect(770, 320, 21, 23));
        pushButton_11 = new QPushButton(centralWidget);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
        pushButton_11->setGeometry(QRect(760, 380, 21, 23));
        pushButton_12 = new QPushButton(centralWidget);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
        pushButton_12->setGeometry(QRect(700, 380, 21, 23));
        lineEdit = new FilenameLine(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(640, 420, 201, 20));
        pushButton_13 = new QPushButton(centralWidget);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));
        pushButton_13->setGeometry(QRect(670, 440, 151, 23));
        FirstTimeClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(FirstTimeClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FirstTimeClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FirstTimeClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FirstTimeClass->setStatusBar(statusBar);

        retranslateUi(FirstTimeClass);
        QObject::connect(pushButton_2, SIGNAL(clicked()), widget, SLOT(left()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), widget, SLOT(right()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), widget, SLOT(down()));
        QObject::connect(pushButton, SIGNAL(pressed()), widget, SLOT(up()));
        QObject::connect(pushButton_5, SIGNAL(clicked()), widget, SLOT(zoomIn()));
        QObject::connect(pushButton_6, SIGNAL(clicked()), widget, SLOT(zoomOut()));
        QObject::connect(pushButton_7, SIGNAL(pressed()), widget, SLOT(py()));
        QObject::connect(pushButton_10, SIGNAL(pressed()), widget, SLOT(px()));
        QObject::connect(pushButton_9, SIGNAL(pressed()), widget, SLOT(mx()));
        QObject::connect(pushButton_8, SIGNAL(pressed()), widget, SLOT(my()));
        QObject::connect(pushButton_12, SIGNAL(pressed()), widget, SLOT(pz()));
        QObject::connect(pushButton_11, SIGNAL(pressed()), widget, SLOT(mz()));
        QObject::connect(pushButton_13, SIGNAL(clicked()), lineEdit, SLOT(signalFile()));
        QObject::connect(lineEdit, SIGNAL(sendContent(QString)), widget, SLOT(loadFile(QString)));

        QMetaObject::connectSlotsByName(FirstTimeClass);
    } // setupUi

    void retranslateUi(QMainWindow *FirstTimeClass)
    {
        FirstTimeClass->setWindowTitle(QApplication::translate("FirstTimeClass", "FirstTime", 0));
        pushButton_2->setText(QApplication::translate("FirstTimeClass", "Left", 0));
        pushButton_3->setText(QApplication::translate("FirstTimeClass", "Down", 0));
        pushButton_4->setText(QApplication::translate("FirstTimeClass", "Right", 0));
        pushButton->setText(QApplication::translate("FirstTimeClass", "Up", 0));
        pushButton_5->setText(QApplication::translate("FirstTimeClass", "Zoom In", 0));
        pushButton_6->setText(QApplication::translate("FirstTimeClass", "Zoom Out", 0));
        label->setText(QApplication::translate("FirstTimeClass", "Light", 0));
        label_2->setText(QApplication::translate("FirstTimeClass", "Camera", 0));
        pushButton_7->setText(QApplication::translate("FirstTimeClass", "+y", 0));
        pushButton_8->setText(QApplication::translate("FirstTimeClass", "-y", 0));
        pushButton_9->setText(QApplication::translate("FirstTimeClass", "-x", 0));
        pushButton_10->setText(QApplication::translate("FirstTimeClass", "+x", 0));
        pushButton_11->setText(QApplication::translate("FirstTimeClass", "-z", 0));
        pushButton_12->setText(QApplication::translate("FirstTimeClass", "+Z", 0));
        pushButton_13->setText(QApplication::translate("FirstTimeClass", "Load Config File", 0));
    } // retranslateUi

};

namespace Ui {
    class FirstTimeClass: public Ui_FirstTimeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRSTTIME_H
