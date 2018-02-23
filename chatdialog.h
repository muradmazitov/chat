#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include "ui_chatdialog.h"
#include <QString>
#include <QWidget>

class ChatDialog : public QDialog, public Ui::ChatDialog
{
    Q_OBJECT

public:
    ChatDialog(QWidget *parent = 0);

public slots:
    //void appendMessage(const QString &from, const QString &message);
signals:
    tryStartServer();
/*private slots:
    void returnPressed();
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);*/

private slots:
    void on_pushButton_clicked();

private:
    QString myNickName;
    QTextTableFormat tableFormat;
};

#endif
