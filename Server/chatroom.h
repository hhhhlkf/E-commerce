#ifndef CHATROOM_H
#define CHATROOM_H

#include <QWidget>
#include "chatmessage/qnchatmessage.h"
#include <QListWidget>
#include <QDateTime>
#include <QDate>
#include <QEvent>
#include <QKeyEvent>
#include "objects.h"
namespace Ui {
class ChatRoom;
}

class ChatRoom : public QWidget
{
    Q_OBJECT

public:
    explicit ChatRoom(QWidget *parent = nullptr);
    ~ChatRoom();
    void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type);

    void dealMessageTime(QString curMsgTime);

    void ChatMessageRecived(QString mess);

    void ChatMessageSend();

    Client *client;
    Client *getClient() const;
    void setClient(Client *value);
    qintptr sockeDiscriptor;

    qintptr getSockeDiscriptor() const;
    void setSockeDiscriptor(const qintptr &value);

private:
    Ui::ChatRoom *ui;
private slots:
    bool eventFilter(QObject *target, QEvent *event);
signals:
    void sglsendToClient(QString message,qintptr socketDiscriptor);
};

#endif // CHATROOM_H
