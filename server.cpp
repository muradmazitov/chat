#include "server.h"

Server::Server(ChatDialog *w, QObject *parent) : QTcpServer(parent)
{
    connect(w->pushButton, SIGNAL(pressed()), this, SLOT(StartServer()));
}

void Server::StartServer()
{
    if (Active)
    {
        return;
    }

    Active = true;

    if (!this->listen(QHostAddress::Any, 1234))
    {
        qDebug() << "Server couldnt start";
        Active = false;
    }
    else
    {
        qDebug() << "Server just started and adress is " << QString(serverAddress().toString());
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    if (CountConnected > 10)
    {
        return;
    }
    qDebug() << "INCOMING CONNECTION" << socketDescriptor;

    Connection *connection = new Connection(socketDescriptor);

    connect(connection, SIGNAL(AddConnection()), this, SLOT(AddConnection()));
    connect(connection, SIGNAL(RemoveConnection()), this, SLOT(RemoveConnection()));
    connect(connection, SIGNAL(NewMessage()), this, SLOT(GetMessage()));

    connection->start();
    Peers.insert(socketDescriptor, connection);
}

void Server::GetMessage()
{
    Connection *sender = dynamic_cast<Connection*>(QObject::sender());
    QByteArray message = sender->Message;
    QList <Connection *> list = Peers.values();
    foreach (Connection * e, list)
    {
        e->Socket->write(message);
        e->Socket->flush();
        e->Socket->waitForBytesWritten(3 * 1000);
    }
}

void Server::AddConnection()
{
    qDebug() << "ADDING CONNECTION";
    CountConnected++;
}

void Server::RemoveConnection()
{
    qDebug() << "REMOVING CONNECTION";
    CountConnected--;
    Connection *sender = dynamic_cast<Connection *>(QObject::sender());

    if (Peers.find(sender -> id) != Peers.end())
    {
        Peers.erase(Peers.find(sender -> id));
    }
}
