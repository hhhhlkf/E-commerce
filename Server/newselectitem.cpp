#include "newselectitem.h"
#include "ui_newselectitem.h"
#include <QDebug>
NewSelectItem::NewSelectItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewSelectItem)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setStyleSheet("QWidget{background:transparent; border-radius:8px;}"
                        "QWidget:hover{background:transparent;}");
    RightWidget = NULL;
}

NewSelectItem::~NewSelectItem()
{
    delete ui;
}

void NewSelectItem::setNum(int id)
{
    ui->labMusicNum->setText(QString::number(id));
    this->id= id;
}

void NewSelectItem::setPicture(QString url)
{
    QString str = "QWidget{border-image:url("+url+");}";
    ui->ItemPic->setStyleSheet(str);
}

void NewSelectItem::setCommondityName(QString CommondityName)
{
    ui->CommodityName->setText(CommondityName);
     ui->CommodityName->setStyleSheet("QLabel#MusicName{color:rgb(54,54,54);}");
     name = CommondityName;
}

void NewSelectItem::setLogPic()
{

}

void NewSelectItem::setCommondityAuthor(QString author)
{
    ui->CommodityFactory->setText(author);
    ui->CommodityFactory->setStyleSheet("QLabel#CommodityFactory{color:rgb(101,101,101);}");

}

void NewSelectItem::setCommondityAlbum(QString name)
{
    ui->CommodityType->setText(name);
    ui->CommodityType->setStyleSheet("QLabel#CommodityType{color:rgb(101,101,101);}");

}

void NewSelectItem::setCommondityTimer(QString strTimer)
{
    ui->Commoditycost->setText(strTimer);
    ui->Commoditycost->setStyleSheet("QLabel#Commoditycost{color:rgb(155,155,202);}");

}

void NewSelectItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit ChangetoModified();
}

void NewSelectItem::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::RightButton)
    {
        if(RightWidget)
        {
            delete RightWidget;
            RightWidget = NULL;
        }
        else
        {
            RightWidget = new RightCheck(this);
            RightWidget->setGeometry(event->x(),event->y(),112,138);
            //qDebug()<<event->x()<<event->y();
            connect(RightWidget,&RightCheck::DelSelectItem,[=]()
            {
                emit delNewSelectitem(num);
            });
            RightWidget->raise();  //提示显示层数
            RightWidget->show();
        }
    }

}


