#pragma once

#include <QLineEdit>

class FilenameLine : public QLineEdit {
	Q_OBJECT
public:
	FilenameLine(QWidget*);
	~FilenameLine(void);

public slots:
	void signalFile(void);

signals:
	void sendContent(QString);
};

