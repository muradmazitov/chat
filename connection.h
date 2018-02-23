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
public slots:
    void readyDATA();
    void disconnect();
public:
    QTcpSocket* socket;
    qintptr id;
};

#endif // CONNECTION_H