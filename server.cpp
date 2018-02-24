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
    //if (!this -> listen(QHostAddress("127.0.0.1"), 1234))
    if (!this -> listen(QHostAddress::Any, 1234))
    {
        qDebug() << "Server couldnt start";
    }
    else
    {
        qDebug() << "Server just started and adress is " << QString(serverAddress().toString());
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    if (count_connected > 5)
    {
        nextPendingConnection() -> write("PIZDUI TI ZDES` LISHNII");
        return;
    }

    qDebug() << "INCOMING CONNECTION" << socketDescriptor;
    Connection *connection = new Connection(socketDescriptor, this);

    peers[socketDescriptor] = connection;

    connect(connection, SIGNAL(finished()), connection, SLOT(deleteLater()));
    connect(connection, SIGNAL(add_connection()), this, SLOT(add_connection()));
    connect(connection, SIGNAL(remove_connection()), this, SLOT(remove_connection()));
    connection -> start();
}

void Server::add_connection()
{
    count_connected++;
}

void Server::remove_connection()
{
    count_connected--;
}
