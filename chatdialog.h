#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include "ui_chatdialog.h"
#include <QString>
#include <QWidget>
#include <QTextTable>
#include <QScrollBar>

class ChatDialog : public QDialog, public Ui::ChatDialog
{
    Q_OBJECT

public:
    ChatDialog(QWidget *parent = 0);

public slots:
    void appendMessage(QString message);
signals:
    tryStartServer();
/*private slots:
    void returnPressed();
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);*/

private:
    QTextTableFormat tableFormat;
};

#endif
