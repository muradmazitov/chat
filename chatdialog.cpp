#include "chatdialog.h"

ChatDialog::ChatDialog(QWidget *parent) : QDialog(parent)
{
    setupUi(this);

    lineEdit->setFocusPolicy(Qt::StrongFocus);
    textEdit->setFocusPolicy(Qt::NoFocus);
    textEdit->setReadOnly(true);
    listWidget->setFocusPolicy(Qt::NoFocus);

   // connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));

    //myNickName = client.nickName();
    //newParticipant(myNickName);
    tableFormat.setBorder(0);
}

