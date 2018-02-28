#include "connection.h"

Connection::Connection(qintptr ID)
{
    this -> id = ID;
}

void Connection::run()
{
    qDebug() << id << " STRATING THREAD";
    socket.reset(new QTcpSocket());
    if (!socket -> setSocketDescriptor(id))
    {
        emit this->error(socket -> error());
        return;
    }

    emit add_connection();
    message = "client connected to chat";
    emit newmessage();
    /*socket -> write("client connected to chat");
    socket -> flush();
    socket -> waitForBytesWritten(3000);
    */
    connect(socket.data(), SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket.data(), SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);

    qDebug() << id << "Client connected";
    exec();
}


void Connection::readyRead()
{
    QByteArray data = socket -> readAll();
    qDebug() << id << " data : " << data;
    message = data;
    emit newmessage();
}

void Connection::disconnected()
{

    qDebug() << id << " disconnected";
    emit remove_connection();
    exit(0);
}
