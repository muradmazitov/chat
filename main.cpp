#include "chatdialog.h"
#include <QApplication>
#include <server.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatDialog w;
    Server *server = new Server(&w);
    w.show();
    return a.exec();
}
