#ifndef SERVER_H
#define SERVER_H

#include <QDebug>
#include <QTcpServer>

#include <QMap>
#include <connection.h>
#include <chatdialog.h>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(ChatDialog *w = 0, QObject *parent = 0);

protected:
    void incomingConnection(qintptr socketDescriptor);

public slots:
    void get_message();

private slots:
    void startServer();
    void add_connection();
    void remove_connection();

private:
    int count_connected = 0;
    QMap <qintptr, Connection *> peers;
    bool active = false;
};

#endif // SERVER_H
