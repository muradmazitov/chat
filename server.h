#ifndef SERVER_H
#define SERVER_H

#include <QDebug>
#include <QTcpServer>

#include <QMap>
#include <connection.h>
#include <chatdialog.h>
#include <client.h>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(ChatDialog *w = 0, QObject *parent = 0);

protected:
    void incomingConnection(qintptr socketDescriptor);

public slots:
    void GetMessage();

private slots:
    void StartServer();
    void AddConnection();
    void RemoveConnection();

private:
    int CountConnected = 0;
    QMap <qintptr, Connection *> Peers;
    bool Active = false;
};

#endif // SERVER_H
