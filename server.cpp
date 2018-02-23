#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{

}

Server::Server(ChatDialog *w, QObject *parent) : QTcpServer(parent)
{
    connect(w -> pushButton, SIGNAL(pressed()), this, SLOT(startServer()));
}

void Server::startServer()
{
    if (active) return;

    active = true;
    if (!this -> listen(QHostAddress::Any, 1234))
    {
        qDebug() << "Server couldnt start";
    }
    else
    {
        qDebug() << "Server just started";
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "INCOMING CONNECTION" << socketDescriptor;
    Connection *connection = new Connection(socketDescriptor, this);
    peers[socketDescriptor] = connection;
    connect(connection, SIGNAL(finished()), connection, SLOT(deleteLater()));
    connection->start();
}
