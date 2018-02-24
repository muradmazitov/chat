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
    emit add_connection();
    socket -> write("0 HI");
    connect(socket, SIGNAL(connected()), this, SLOT(connected()), Qt::DirectConnection);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);
    qDebug() << id << "Client connected";
    exec();
}

void Connection::connected()
{
    qDebug() << "CONNECTED USER";
}

void Connection::readyRead()
{
    QByteArray data = socket->readAll();
    qDebug() << id << " data : " << data;
    socket->write(data);
    socket->flush();
}

void Connection::disconnected()
{
    qDebug() << id << " disconnected";
    emit remove_connection();
    socket->deleteLater();
    exit(0);
}
