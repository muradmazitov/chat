#include "client.h"

Client::Client(ChatDialog *w)
{
    Socket = new QTcpSocket();

    Dialog = w;
    connect(Dialog->username, SIGNAL(textEdited(QString)), this, SLOT(ChangeUsername(QString)));
    connect(Dialog->serveradress, SIGNAL(textEdited(QString)), this, SLOT(ConnectToServer()));

    connect(Dialog->lineEdit, SIGNAL(returnPressed()), this, SLOT(SendMessage()));

    connect(Socket, SIGNAL(connected()), this, SLOT(Connected()));
    connect(Socket, SIGNAL(readyRead()), this, SLOT(GetMessage()));
    connect(Socket, SIGNAL(disconnected()), this, SLOT(Stop()));
}

void Client::GetMessage()
{
    QByteArray data = Socket->readAll();
    QString S = data;
    Dialog -> AppendMessage(S);
}

void Client::ChangeUsername(QString name)
{
    Username = name;
}

void Client::ConnectToServer()
{
    if (Socket->ConnectedState)
    {
        Socket->disconnectFromHost();
    }
    QString adress = Dialog->serveradress->text();
    Socket->connectToHost(QHostAddress(adress), 1234);
    Socket->waitForConnected(1000);
    Dialog->pushButton->close();
}

void Client::SendMessage()
{
    QString data = Dialog->lineEdit->text();

    Socket->write(QByteArray::fromStdString("<" + Username.toStdString()  + "> "+ data.toStdString()));
    Socket->flush();
    Socket->waitForBytesWritten(3 * 1000);

    Dialog->lineEdit->clear();
}

void Client::Connected()
{
    Socket->write(QByteArray::fromStdString("Hi, server! I'm, " + Username.toStdString()));
    Socket->flush();
    Socket->waitForBytesWritten(3 * 1000);
}

void Client::Stop()
{
    Socket->disconnectFromHost();
}
