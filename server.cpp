#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{}

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
        qDebug() << "Server just started and adress is " << QString(serverAddress().toString());
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    if (count_connected > 5)
        return;

    qDebug() << "INCOMING CONNECTION" << socketDescriptor;
    Connection *connection = new Connection(socketDescriptor, this);

    peers[socketDescriptor] = connection;
    connect(connection, SIGNAL(disconnect_id(qintptr)), this, SLOT(disconnect_id(qintptr)));
    connect(connection, SIGNAL(finished()), connection, SLOT(deleteLater()));
    connect(connection, SIGNAL(add_connection()), this, SLOT(add_connection()));
    connect(connection, SIGNAL(remove_connection()), this, SLOT(remove_connection()));

    connect(connection, SIGNAL(newmessage()), this, SLOT(get_message()));
    connection -> start();
}

void Server::get_message()
{
    Connection *sender = dynamic_cast<Connection*>(QObject::sender());
    QByteArray message = sender -> message;
    QList <Connection *> list = peers.values();
    foreach(Connection * e, list)
    {
        e -> socket -> write(message);
        e -> socket -> flush();
        e -> socket -> waitForBytesWritten(3000);
    }
}

void Server::disconnect_id(qintptr id)
{
    peers.erase(peers.find(id));
}

void Server::add_connection()
{
    count_connected++;
}

void Server::remove_connection()
{
    count_connected--;
}
