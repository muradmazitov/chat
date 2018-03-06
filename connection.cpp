#include "connection.h"

Connection::Connection(qintptr ID)
{
    this->id = ID;
}

void Connection::run()
{
    qDebug() << id << " STRATING THREAD";
    Socket.reset(new QTcpSocket());
    if (!Socket->setSocketDescriptor(id))
    {
        emit this->Error(Socket -> error());
        return;
    }

    emit AddConnection();
    Message = "client connected to chat";
    emit NewMessage();

    connect(Socket.data(), SIGNAL(readyRead()), this, SLOT(ReadyRead()), Qt::DirectConnection);
    connect(Socket.data(), SIGNAL(disconnected()), this, SLOT(Disconnected()), Qt::DirectConnection);

    qDebug() << id << "Client connected";
    exec();
}


void Connection::ReadyRead()
{
    QByteArray data = Socket->readAll();
    qDebug() << id << " data : " << data;
    Message = data;
    emit NewMessage();
}

void Connection::Disconnected()
{

    qDebug() << id << " disconnected";
    emit RemoveConnection();
    exit(0);
}
