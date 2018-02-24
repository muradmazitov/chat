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

void ChatDialog::appendMessage(QString message)
{
     QTextCursor cursor(textEdit->textCursor());
       cursor.movePosition(QTextCursor::End);
       QTextTable *table = cursor.insertTable(1, 2, tableFormat);
       table->cellAt(0, 0).firstCursorPosition().insertText(message);
      QScrollBar *bar = textEdit->verticalScrollBar();
      bar->setValue(bar->maximum());
}
