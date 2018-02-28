#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <QThread>
#include <QDebug>
#include <QScopedPointer>

class Connection : public QThread
{
    Q_OBJECT
    
signals:
    void error(QTcpSocket::SocketError sockEr);
    void newmessage();
    void add_connection();
    void remove_connection();

public slots:
    void readyRead();
    void disconnected();

public:
    explicit Connection(qintptr ID);
    void run();
    QByteArray message;
    QScopedPointer <QTcpSocket> socket;
    qintptr id;
};

#endif // CONNECTION_H
