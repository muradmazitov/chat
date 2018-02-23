#include "connection.h"

Connection::Connection(qintptr ID, QObject *parent) :
    QThread(parent)
{
    id = ID;

}

void Connection::run()
{
    socket = new QTcpSocket();
    if (!socket -> setSocketDescriptor(id)) {
        qDebug() << "WTF";
    } else {
        qDebug() << id << " connected";
    }
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyDATA()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnect()));
}

void Connection::readyDATA()
{
    QByteArray data = socket->readAll();
    socket->write(data);
}

void Connection::disconnect()
{
    socket->deleteLater();
    exit(0);
}

