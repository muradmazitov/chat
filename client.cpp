#include "client.h"

Client::Client(ChatDialog *w)
{
    socket = new QTcpSocket();
    connect(w->username, SIGNAL(textEdited(QString)), this, SLOT(change_username(QString)));
    connect(w->connect_to, SIGNAL(pressed()), this, SLOT(connect_to_server()));
    this -> serveradress = w -> serveradress;
    this -> lineEdit = w -> lineEdit;
    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(send_message()));
}


void Client::change_username(QString name)
{
    username = name;
}

void Client::connect_to_server()
{
    QString adress = serveradress -> text();
    socket -> connectToHost(QHostAddress(adress), 1234);
    qDebug() << "WHAT " << socket -> socketDescriptor();
    socket -> write("0 HI");
    socket -> flush();

}

void Client::send_message()
{
    QString data = this -> lineEdit -> text();

    socket -> write(QByteArray::fromStdString(data.toStdString()));
    socket -> flush();
    socket -> waitForBytesWritten(3000);
    lineEdit -> clear();
}
