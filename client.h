#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QObject>
#include <QWidget>
#include <chatdialog.h>
class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(ChatDialog *w);

public slots:
    void ChangeUsername(QString name);
    void ConnectToServer();
    void SendMessage();
    void Connected();
    void Stop();
    void GetMessage();

private:
    QString Username = "Anonim";
    QTcpSocket *Socket;
    ChatDialog *Dialog;
};

#endif // CLIENT_H
