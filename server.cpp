#include "server.h"

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
        active = false;
    }
    else
    {
        qDebug() << "Server just started and adress is " << QString(serverAddress().toString());
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    if (count_connected > 5) return;

    qDebug() << "INCOMING CONNECTION" << socketDescriptor;

    Connection *connection = new Connection(socketDescriptor);

    connect(connection, SIGNAL(add_connection()), this, SLOT(add_connection()));
    connect(connection, SIGNAL(remove_connection()), this, SLOT(remove_connection()));
    connect(connection, SIGNAL(newmessage()), this, SLOT(get_message()));

    connection -> start();
    peers.insert(socketDescriptor, connection);
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
        e -> socket -> waitForBytesWritten(3 * 1000);
    }
}

void Server::add_connection()
{
    qDebug() << "ADDING CONNECTION";
    count_connected++;
}

void Server::remove_connection()
{
    qDebug() << "REMOVING CONNECTION";
    count_connected--;
    Connection *sender = dynamic_cast <Connection *> (QObject::sender());

    if (peers.find(sender -> id) != peers.end())
        peers.erase(peers.find(sender -> id));
}
