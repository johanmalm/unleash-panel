#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore>
#include <QObject>

class Client : public QObject
{
	Q_OBJECT
public:
	Client();
	~Client();

	void setWID(unsigned long wid);
	unsigned long getWID();
	void setName(QString name);
	QString getName();

private:
	unsigned long m_wid;
	QString m_name;
};

#endif // CLIENT_H
