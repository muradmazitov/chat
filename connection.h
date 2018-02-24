#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <QThread>
#include <QDebug>

class Connection : public QThread
{
    Q_OBJECT
public:
    explicit Connection(qintptr ID, QObject *parent = 0);
    void run();
    QByteArray message;
signals:
    void error(QTcpSocket::SocketError sockEr);
    void newmessage();
    void add_connection();
    void remove_connection();
    void disconnect_id(qintptr id);
public slots:
    void readyRead();
    void connected();
    void disconnected();
public:
    QTcpSocket *socket;
    qintptr id;
};

#endif // CONNECTION_H
