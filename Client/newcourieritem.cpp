#include "newcourieritem.h"
#include "ui_newcourieritem.h"
//历史记录和购物车的单个物件类
NewCourierItem::NewCourierItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewCourierItem)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setStyleSheet("QWidget{background:transparent; border-radius:8px;}"
                        "QWidget:hover{background:transparent;}");
}

NewCourierItem::~NewCourierItem()
{
    delete ui;
}

void NewCourierItem::setNum(int id)
{
    ui->labMusicNum->setNum(id);
    ui->labMusicNum->setStyleSheet("QLabel#labMusicNum{color:rgb(195,195,219);}");

}

void NewCourierItem::setPicture(QString url)
{
   QString str = "QWidget{border-image:url("+url+");}";
   ui->widMusicPic->setStyleSheet(str);
   image = url;
}

void NewCourierItem::setCommondityName(QString CommondityName)
{
    ui->MusicName->setText(CommondityName);
     ui->MusicName->setStyleSheet("QLabel#MusicName{color:rgb(54,54,54);}");

}

void NewCourierItem::setLogPic()
{
    //ui->labMusicLog->setMaximumSize(27,17);
}

void NewCourierItem::setCommondityAuthor(QString author)
{
    ui->MusicAuthor->setText(author);
    ui->MusicAuthor->setStyleSheet("QLabel#MusicAuthor{color:rgb(101,101,101);}");
}

void NewCourierItem::setCommondityAlbum(QString name)
{
    ui->MusicAlbum->setText(name);
    ui->MusicAlbum->setStyleSheet("QLabel#MusicAlbum{color:rgb(101,101,101);}");
}

void NewCourierItem::setCommondityTimer(QString strTimer)
{
    ui->MusicTimer->setText(strTimer);
    ui->MusicTimer->setStyleSheet("QLabel#MusicTimer{color:rgb(155,155,202);}");
}

bool NewCourierItem::getCheckBox()
{
    if(ui->checkBox->isChecked()==true)return true;
    else return false;
}

void NewCourierItem::setcheckBox()
{
    ui->checkBox->setChecked(false);
}

Order *NewCourierItem::getOrder() const
{
    return order;
}

void NewCourierItem::setOrder(Order *value)
{
    order = value;
    setNum(order->getOrderId());
    setCommondityName(order->getOrderProductName());
    setCommondityAuthor(order->getOrderProductStyle());
    setCommondityAlbum(QString::number(order->getOrderProductNum()));
    setCommondityTimer(order->getOrderCost());
}

QString NewCourierItem::getImage() const
{
    return image;
}

void NewCourierItem::setImage(const QString &value)
{
    image = value;
}

void NewCourierItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit sglClicked(order->getOrderProductId(),order->getOrderProductNum(),order->getOrderProductName(),order->getOrderProductStyle());
}
