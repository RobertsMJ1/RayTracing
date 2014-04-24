#include "framework.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Framework w;
	w.show();
	return a.exec();
}
