#include "client.h"

#include <QtCore>
#include <QDebug>

Client::Client()
{
	m_wid = 0;
	m_name = "xxx";
}

Client::~Client()
{
}

void Client::setWID(unsigned long wid)
{
	m_wid = wid;
}

unsigned long Client::getWID()
{
	return m_wid;
}

void Client::setName(QString name)
{
	m_name = name;
}

QString Client::getName()
{
	return m_name;
}

