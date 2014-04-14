#ifndef FIRSTTIME_H
#define FIRSTTIME_H

#include <QtWidgets/QMainWindow>
#include "ui_firsttime.h"

class FirstTime : public QMainWindow
{
	Q_OBJECT

public:
	FirstTime(QWidget *parent = 0);
	~FirstTime();

private:
	Ui::FirstTimeClass ui;
};

#endif // FIRSTTIME_H
