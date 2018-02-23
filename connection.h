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

signals:
    void error(QTcpSocket::SocketError sockEr);

public slots:
    void readyRead();
    void connected();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr id;
};

#endif // CONNECTION_H
