#include "onsaleitem.h"
#include "ui_onsaleitem.h"

onSaleItem::onSaleItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::onSaleItem)
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
    delWidget->setGeometry(Width-58,20,41,41);
    delWidget->hide();

}

onSaleItem::~onSaleItem()
{
    delete ui;
}

void onSaleItem::setNum(int id)
{
    ui->labMusicNum->setNum(id);
    num =id;
    this->id =id;
    Q_UNUSED(id);
    ui->labMusicNum->setStyleSheet("QLabel#labMusicNum{color:rgb(195,195,219);}");
}

void onSaleItem::setPicture(QString url)
{
    str = url;

    ui->onSalePic->setStyleSheet("QWidget{border-image:url("+url+");}");
}

void onSaleItem::setCommondityName(QString CommondityName)
{
    ui->CommodityName->setText(CommondityName);
    name = CommondityName;
    ui->CommodityName->setStyleSheet("QLabel#MusicName{color:rgb(54,54,54);}");
}

void onSaleItem::setCommondityAuthor(QString author)
{
    Q_UNUSED(author);
}

void onSaleItem::setCommondityAlbum(QString name)
{
    Q_UNUSED(name);
}

void onSaleItem::setCommondityTimer(QString strTimer)
{
    ui->Commoditycost->setText(strTimer);
    ui->Commoditycost->setStyleSheet("QLabel#Commoditycost{color:rgb(155,155,202);}");
}

void onSaleItem::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    if(delWidget)
    {
        delWidget->raise();
        delWidget->show();
    }

}

void onSaleItem::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    if(delWidget)
    delWidget->hide();
}

void onSaleItem::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit getinfo(productNum,str,id,ui->CommodityName->text(),ui->Commoditycost->text());
}

void onSaleItem::CloseSlots()
{
    Product * product = new Product;
    product->setProductId(id);
    product->setProductName(name);
    product->setProductDiscount(1);
    emit CloseSignal(num,product);
}
