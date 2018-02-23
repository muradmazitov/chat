#include "connection.h"

Connection::Connection(qintptr ID, QObject *parent) : QThread(parent)
{
    this -> id = ID;
}

void Connection::run()
{
    qDebug() << id << " STRATING THREAD";
    socket = new QTcpSocket;
    if (!socket -> setSocketDescriptor(id))
    {
        emit this->error(socket -> error());
        return;
    }
    socket -> write("HELLO CLIENT");
    socket -> flush();
    connect(socket, SIGNAL(connected()), this, SLOT(connected()), Qt::DirectConnection);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);
    qDebug() << id << "Client connected";
    exec();
}
void Connection::connected()
{
    qDebug() << "CONNECTED UDER";
    socket -> write("HELLO");
    socket -> flush();
}
void Connection::readyRead()
{
    QByteArray data = socket->readAll();
    socket->write(data);
    socket->flush();
}

void Connection::disconnected()
{
    socket->deleteLater();
    exit(0);
}

