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
    void Error(QTcpSocket::SocketError sockEr);
    void NewMessage();
    void AddConnection();
    void RemoveConnection();

public slots:
    void ReadyRead();
    void Disconnected();

public:
    explicit Connection(qintptr ID);
    void run();
    QByteArray Message;
    QScopedPointer <QTcpSocket> Socket;
    qintptr id;
};

#endif // CONNECTION_H
