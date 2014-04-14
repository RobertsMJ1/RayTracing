#include "FilenameLine.h"


FilenameLine::FilenameLine(QWidget* parent = 0) : QLineEdit(parent) {
}

FilenameLine::~FilenameLine() {
}

void FilenameLine::signalFile() {
	emit sendContent(text());
}
