#include "Program1.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FirstTime w;
	w.show();
	return a.exec();
}
