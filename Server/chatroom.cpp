#include "chatroom.h"
#include "ui_chatroom.h"
#include <QDebug>
ChatRoom::ChatRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatRoom)
{
    ui->setupUi(this);
    connect(ui->ptnChange,&QPushButton::clicked,[=](){
       ChatMessageSend();
    });
    ui->textEdit->setFocus();
    ui->textEdit->installEventFilter(this);

}

ChatRoom::~ChatRoom()
{
    delete ui;
}

void ChatRoom::dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type)
{
    messageW->setFixedWidth(ui->ChatList->width());
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    //item->setSizeHint(QSize(300,54));
    messageW->setText(text, time, size, type);
    ui->ChatList->setItemWidget(item, messageW);
}

void ChatRoom::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;
    if(ui->ChatList->count() > 0) {
        QListWidgetItem* lastItem = ui->ChatList->item(ui->ChatList->count() - 1);
        QNChatMessage* messageW = (QNChatMessage*)ui->ChatList->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        //qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
//        isShowTime = true;
    } else {
        isShowTime = true;
    }
    if(isShowTime) {
        QNChatMessage* messageTime = new QNChatMessage(ui->ChatList->parentWidget());
        QListWidgetItem* itemTime = new QListWidgetItem(ui->ChatList);

        QSize size = QSize(ui->ChatList->width(), 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, QNChatMessage::User_Time);
        ui->ChatList->setItemWidget(itemTime, messageTime);
    }
}

void ChatRoom::ChatMessageRecived(QString mess)
{
    QString time = QString::number(QDateTime::currentDateTime().toTime_t());
    bool isReseving = true;
    if(isReseving){
        dealMessageTime(time);
        QNChatMessage* messageW = new QNChatMessage(ui->ChatList->parentWidget());
        messageW->setLeftPixmap(QPixmap(client->getClientImage()));
        QListWidgetItem* item = new QListWidgetItem(ui->ChatList);
        dealMessage(messageW, item, mess, time, QNChatMessage::User_She);
    }
}

void ChatRoom::ChatMessageSend()
{

        if(ui->textEdit->toPlainText()=="")
        {
            return;
        }
        QString msg = ui->textEdit->toPlainText();
        emit sglsendToClient(msg,sockeDiscriptor);
        QString time =  QString::number(QDateTime::currentDateTime().toTime_t());
        dealMessageTime(time);
        QNChatMessage* messageW = new QNChatMessage(ui->ChatList->parentWidget());
        messageW->setRightPixmap(QPixmap("images/nzk.ico"));
        QListWidgetItem* item = new QListWidgetItem(ui->ChatList);
        dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
        ui->textEdit->clear();
}

Client *ChatRoom::getClient() const
{
    return client;
}

void ChatRoom::setClient(Client *value)
{
    if(value!=nullptr)
    client = new Client(*value);
}

qintptr ChatRoom::getSockeDiscriptor() const
{
    return sockeDiscriptor;
}

void ChatRoom::setSockeDiscriptor(const qintptr &value)
{
    sockeDiscriptor = value;
}

bool ChatRoom::eventFilter(QObject *target, QEvent *event)
{
    if(target == ui->textEdit)
    {
        if(event->type() == QEvent::KeyPress)//回车键
        {
             QKeyEvent *k = static_cast<QKeyEvent *>(event);
             if(k->key() == Qt::Key_Return)
             {
                 emit(ui->ptnChange->clicked());
                 return true;
             }
        }
    }
    return QWidget::eventFilter(target,event);
}
