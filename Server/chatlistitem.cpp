#include "chatlistitem.h"
#include "ui_chatlistitem.h"

ChatListItem::ChatListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatListItem)
{
    ui->setupUi(this);
    delWidget = new QWidget(this);
    CloseBtn = new QPushButton();
    CloseBtn->setStyleSheet("QPushButton{border-image:url(images/x2.svg);}QPushButton::hover{border-image:url(images/x1.svg);}QPushButton::pressed{border-image:url(images/x1.svg);}");
    Layout = new QHBoxLayout();
    Width = this->width();
    Layout->addWidget(CloseBtn);
    connect(CloseBtn,&QPushButton::clicked,[=]()
    {
           CloseSlots();
    });
    delWidget->setLayout(Layout);
    delWidget->setGeometry(Width-50,3,30,50);
    delWidget->hide();
}

ChatListItem::~ChatListItem()
{
    delete ui;
}

void ChatListItem::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    delWidget->raise();
    delWidget->show();
}

void ChatListItem::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    delWidget->hide();
}

Client *ChatListItem::getClient() const
{
    return client;
}

void ChatListItem::setClient(Client *value)
{
    if(value!=nullptr)
    {
        client = new Client(*value);
        ui->NameButton->setStyleSheet("QPushButton{border-image:url("+ client->getClientImage()+");}");
        ui->Namelabel->setText(client->getClientName());
    }
}

qintptr ChatListItem::getSockeDiscriptor() const
{
    return sockeDiscriptor;
}

void ChatListItem::setSockeDiscriptor(const qintptr &value)
{
    sockeDiscriptor = value;
}

void ChatListItem::CloseSlots()
{
    emit CloseSignal(num,this->sockeDiscriptor);
}

