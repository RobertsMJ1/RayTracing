#ifndef FILENAMELINE_H
#define FILENAMELINE_H

#include <QLineEdit>

class FilenameLine : public QLineEdit
{
	Q_OBJECT

public:
	FilenameLine(QWidget*);
	~FilenameLine(void);
	
public slots:
	void signalFile(void);

signals:
	void sendContent(QString);
	
};

#endif // FILENAMELINE_H
