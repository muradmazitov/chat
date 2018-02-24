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
    void change_username(QString name);
    void connect_to_server();
    void send_message();
    void connected();
    void getmessage();

private:
    QLineEdit *lineEdit, *serveradress;
    QString username;
    QTcpSocket *socket;
    ChatDialog *dialog;
};

#endif // CLIENT_H
