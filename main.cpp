#include "chatdialog.h"
#include <QApplication>
#include <server.h>
#include <client.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatDialog w;
    Client *client = new Client(&w);
    Server *server = new Server(&w);
    w.show();
    return a.exec();
}
