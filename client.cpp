#include "client.h"

Client::Client(ChatDialog *w)
{
    socket = new QTcpSocket();

    dialog = w;
    connect(dialog -> username, SIGNAL(textEdited(QString)), this, SLOT(change_username(QString)));
    connect(dialog -> serveradress, SIGNAL(textEdited(QString)), this, SLOT(connect_to_server()));

    connect(dialog -> lineEdit, SIGNAL(returnPressed()), this, SLOT(send_message()));

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(getmessage()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(stop()));
}

void Client::getmessage()
{
    QByteArray data = socket -> readAll();
    QString S = data;
    dialog -> appendMessage(S);
}

void Client::change_username(QString name)
{
    username = name;
}

void Client::connect_to_server()
{
    if (socket -> ConnectedState)
        socket -> disconnectFromHost();
    QString adress = dialog -> serveradress -> text();
    socket -> connectToHost(QHostAddress(adress), 1234);
    socket -> waitForConnected(1000);
}

void Client::send_message()
{
    QString data = dialog -> lineEdit -> text();

    socket -> write(QByteArray::fromStdString("<" + username.toStdString()  + "> "+ data.toStdString()));
    socket -> flush();
    socket -> waitForBytesWritten(3 * 1000);

    dialog -> lineEdit -> clear();
}

void Client::connected()
{
    socket -> write(QByteArray::fromStdString("Hi, server! I'm, " + username.toStdString()));
    socket -> flush();
    socket -> waitForBytesWritten(3 * 1000);
}

void Client::stop()
{
    socket -> disconnectFromHost();
}
