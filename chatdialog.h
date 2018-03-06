#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include "ui_chatdialog.h"
#include <QTextTable>
#include <QScrollBar>
#include <QString>
#include <QWidget>

class ChatDialog : public QDialog, public Ui::ChatDialog
{
    Q_OBJECT

public:
    ChatDialog(QWidget *parent = 0);

public slots:
    void AppendMessage(QString message);

signals:
    TryStartServer();

private:
    QTextTableFormat TableFormat;
};

#endif
