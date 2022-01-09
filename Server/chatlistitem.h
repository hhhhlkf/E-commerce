#ifndef CHATLISTITEM_H
#define CHATLISTITEM_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "objects.h"
namespace Ui {
class ChatListItem;
}
//聊天室右侧列表控件
class ChatListItem : public QWidget
{
    Q_OBJECT

public:
    explicit ChatListItem(QWidget *parent = nullptr);
    ~ChatListItem();
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent *event);
    int num;
    Client*client;
    qintptr getSockeDiscriptor() const;
    void setSockeDiscriptor(const qintptr &value);

    Client *getClient() const;
    void setClient(Client *value);

private:
    Ui::ChatListItem *ui;
    QWidget* delWidget;
    int Width;
    QPushButton * CloseBtn;
    QHBoxLayout * Layout;
    qintptr sockeDiscriptor;
signals:
    void CloseSignal(int num=0,qintptr sockDiscriptor=0);
public slots:
    void CloseSlots();
};

#endif // CHATLISTITEM_H
