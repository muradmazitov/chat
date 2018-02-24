#include "client.h"

Client::Client(ChatDialog *w)
{
    socket = new QTcpSocket();
    connect(w->username, SIGNAL(textEdited(QString)), this, SLOT(change_username(QString)));
    connect(w->serveradress, SIGNAL(textEdited(QString)), this, SLOT(connect_to_server()));
    this -> serveradress = w -> serveradress;
    this -> lineEdit = w -> lineEdit;
    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(send_message()));

    dialog = w;
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(getmessage()));
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
        socket -> close();
    QString adress = serveradress -> text();
    socket -> connectToHost(QHostAddress(adress), 1234);
    socket -> waitForConnected(200);
}

void Client::send_message()
{
    QString data = this -> lineEdit -> text();

    socket -> write(QByteArray::fromStdString(data.toStdString()));
    socket -> flush();
    socket -> waitForBytesWritten(3000);
    lineEdit -> clear();
}

void Client::connected()
{
    socket -> write("0 HI");
    socket -> flush();
    socket -> waitForBytesWritten(3000);
}
