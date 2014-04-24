#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <QtWidgets/QMainWindow>
#include "ui_framework.h"

class Framework : public QMainWindow
{
	Q_OBJECT

public:
	Framework(QWidget *parent = 0);
	~Framework();

private:
	Ui::FrameworkClass ui;
};

#endif // FRAMEWORK_H
