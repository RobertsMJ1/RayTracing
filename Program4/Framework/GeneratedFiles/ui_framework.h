/********************************************************************************
** Form generated from reading UI file 'framework.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRAMEWORK_H
#define UI_FRAMEWORK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "FilenameLine.h"
#include "MyGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_FrameworkClass
{
public:
    QWidget *centralWidget;
    MyGLWidget *widget;
    QSlider *verticalSlider;
    QSlider *horizontalSlider;
    FilenameLine *lineEdit;
    QSlider *verticalSlider_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *label_5;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QLabel *label_6;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FrameworkClass)
    {
        if (FrameworkClass->objectName().isEmpty())
            FrameworkClass->setObjectName(QStringLiteral("FrameworkClass"));
        FrameworkClass->resize(901, 640);
        centralWidget = new QWidget(FrameworkClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new MyGLWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 570, 570));
        verticalSlider = new QSlider(centralWidget);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setGeometry(QRect(610, 10, 31, 151));
        verticalSlider->setMinimum(-200);
        verticalSlider->setMaximum(-1);
        verticalSlider->setSingleStep(1);
        verticalSlider->setValue(-50);
        verticalSlider->setOrientation(Qt::Vertical);
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(590, 200, 151, 31));
        horizontalSlider->setMaximum(360);
        horizontalSlider->setOrientation(Qt::Horizontal);
        lineEdit = new FilenameLine(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(590, 520, 151, 20));
        verticalSlider_2 = new QSlider(centralWidget);
        verticalSlider_2->setObjectName(QStringLiteral("verticalSlider_2"));
        verticalSlider_2->setGeometry(QRect(690, 10, 31, 151));
        verticalSlider_2->setMinimum(-89);
        verticalSlider_2->setMaximum(89);
        verticalSlider_2->setSingleStep(1);
        verticalSlider_2->setValue(-50);
        verticalSlider_2->setOrientation(Qt::Vertical);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(595, 180, 61, 20));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(680, 180, 51, 21));
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(590, 230, 151, 20));
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(590, 500, 151, 16));
        label_4->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(590, 290, 71, 21));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(590, 320, 71, 21));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(670, 320, 71, 21));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(670, 290, 71, 21));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(590, 270, 151, 20));
        label_5->setAlignment(Qt::AlignCenter);
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(590, 350, 71, 21));
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(670, 350, 71, 21));
        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(620, 550, 91, 23));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(590, 380, 151, 20));
        label_6->setAlignment(Qt::AlignCenter);
        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(590, 400, 71, 21));
        pushButton_9 = new QPushButton(centralWidget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(590, 430, 71, 21));
        pushButton_10 = new QPushButton(centralWidget);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setGeometry(QRect(670, 400, 71, 21));
        pushButton_11 = new QPushButton(centralWidget);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
        pushButton_11->setGeometry(QRect(670, 430, 71, 21));
        pushButton_12 = new QPushButton(centralWidget);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
        pushButton_12->setGeometry(QRect(590, 460, 71, 21));
        pushButton_13 = new QPushButton(centralWidget);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));
        pushButton_13->setGeometry(QRect(670, 460, 71, 21));
        pushButton_14 = new QPushButton(centralWidget);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));
        pushButton_14->setGeometry(QRect(750, 10, 141, 171));
        pushButton_15 = new QPushButton(centralWidget);
        pushButton_15->setObjectName(QStringLiteral("pushButton_15"));
        pushButton_15->setGeometry(QRect(750, 200, 141, 171));
        FrameworkClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FrameworkClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 901, 21));
        FrameworkClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FrameworkClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FrameworkClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FrameworkClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FrameworkClass->setStatusBar(statusBar);

        retranslateUi(FrameworkClass);
        QObject::connect(verticalSlider, SIGNAL(valueChanged(int)), widget, SLOT(zoom(int)));
        QObject::connect(verticalSlider_2, SIGNAL(valueChanged(int)), widget, SLOT(pitch(int)));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), widget, SLOT(yaw(int)));
        QObject::connect(lineEdit, SIGNAL(sendContent(QString)), widget, SLOT(loadConfig(QString)));
        QObject::connect(pushButton, SIGNAL(clicked()), widget, SLOT(lightXInc()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), widget, SLOT(lightXDec()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), widget, SLOT(lightYInc()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), widget, SLOT(lightYDec()));
        QObject::connect(pushButton_5, SIGNAL(clicked()), widget, SLOT(lightZInc()));
        QObject::connect(pushButton_6, SIGNAL(clicked()), widget, SLOT(lightZDec()));
        QObject::connect(pushButton_7, SIGNAL(clicked()), lineEdit, SLOT(signalFile()));
        QObject::connect(pushButton_9, SIGNAL(clicked()), widget, SLOT(transXInc()));
        QObject::connect(pushButton_11, SIGNAL(clicked()), widget, SLOT(transXDec()));
        QObject::connect(pushButton_12, SIGNAL(clicked()), widget, SLOT(transZInc()));
        QObject::connect(pushButton_13, SIGNAL(clicked()), widget, SLOT(transZDec()));
        QObject::connect(pushButton_8, SIGNAL(clicked()), widget, SLOT(prevGeo()));
        QObject::connect(pushButton_10, SIGNAL(clicked()), widget, SLOT(nextGeo()));
        QObject::connect(pushButton_14, SIGNAL(clicked()), widget, SLOT(RayTrace()));
        QObject::connect(pushButton_15, SIGNAL(clicked()), widget, SLOT(subdivide()));

        QMetaObject::connectSlotsByName(FrameworkClass);
    } // setupUi

    void retranslateUi(QMainWindow *FrameworkClass)
    {
        FrameworkClass->setWindowTitle(QApplication::translate("FrameworkClass", "Framework", 0));
        label->setText(QApplication::translate("FrameworkClass", "Zoom", 0));
        label_2->setText(QApplication::translate("FrameworkClass", "Rotate Y", 0));
        label_3->setText(QApplication::translate("FrameworkClass", "Rotate X", 0));
        label_4->setText(QApplication::translate("FrameworkClass", "Config File", 0));
        pushButton->setText(QApplication::translate("FrameworkClass", "+X", 0));
        pushButton_2->setText(QApplication::translate("FrameworkClass", "+Y", 0));
        pushButton_3->setText(QApplication::translate("FrameworkClass", "-Y", 0));
        pushButton_4->setText(QApplication::translate("FrameworkClass", "-X", 0));
        label_5->setText(QApplication::translate("FrameworkClass", "Light Position", 0));
        pushButton_5->setText(QApplication::translate("FrameworkClass", "+Z", 0));
        pushButton_6->setText(QApplication::translate("FrameworkClass", "-Z", 0));
        pushButton_7->setText(QApplication::translate("FrameworkClass", "Load Config", 0));
        label_6->setText(QApplication::translate("FrameworkClass", "Move Geometry", 0));
        pushButton_8->setText(QApplication::translate("FrameworkClass", "Prev", 0));
        pushButton_9->setText(QApplication::translate("FrameworkClass", "+X", 0));
        pushButton_10->setText(QApplication::translate("FrameworkClass", "Next", 0));
        pushButton_11->setText(QApplication::translate("FrameworkClass", "-X", 0));
        pushButton_12->setText(QApplication::translate("FrameworkClass", "+Z", 0));
        pushButton_13->setText(QApplication::translate("FrameworkClass", "-Z", 0));
        pushButton_14->setText(QApplication::translate("FrameworkClass", "RayTrace", 0));
        pushButton_15->setText(QApplication::translate("FrameworkClass", "Sub-Divide", 0));
    } // retranslateUi

};

namespace Ui {
    class FrameworkClass: public Ui_FrameworkClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRAMEWORK_H
