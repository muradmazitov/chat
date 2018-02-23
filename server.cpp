#include "server.h"

Server::Server(ChatDialog *w)
{
    connect(w -> pushButton, SIGNAL(clicked(bool)), this, SLOT(startServer()));
}

void Server::startServer()
{
    server = new QTcpServer();
    if (!server -> listen(QHostAddress::Any, 1234))
    {
        qDebug() << "Server couldnt start";
    }
    else
    {
        qDebug() << "Server just started";
    }
    connect(server, SIGNAL(newConnection()), this, SLOT(incomingConnection()));
}

void Server::incomingConnection()
{
    qintptr ID = server -> nextPendingConnection() -> socketDescriptor();
    qDebug() << "INCOMING CONNECTION" << ID;
    Connection *connection = new Connection(ID);
    connect(connection , SIGNAL(finished()), connection, SLOT(deleteLater()));
    //connection -> socket -> write("HELLO CLIENT");
    //connection -> socket -> flush();
}
