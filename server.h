#ifndef SERVER_H
#define SERVER_H

#include <QDebug>
#include <connection.h>
#include <QTcpServer>
#include <chatdialog.h>

class Server : public QObject
{
    Q_OBJECT
public:
    Server(ChatDialog *w = 0);

private slots:
    void startServer();
    void incomingConnection();
private:
    //QMultiHash<QHostAddress, Connection *> peers;
    QTcpServer *server;
};

#endif // SERVER_H
