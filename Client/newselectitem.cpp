#include "newselectitem.h"
#include "ui_newselectitem.h"

NewSelectItem::NewSelectItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewSelectItem)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setStyleSheet("QWidget{background:transparent; border-radius:8px;}"
                        "QWidget:hover{background:transparent;}");
}

NewSelectItem::~NewSelectItem()
{
    delete ui;
}

void NewSelectItem::setNum(int id)
{
    ui->labMusicNum->setNum(id);
    ui->labMusicNum->setStyleSheet("QLabel#labMusicNum{color:rgb(195,195,219);}");
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

Product *NewSelectItem::getProduct() const
{
    return product;
}

void NewSelectItem::setProduct(Product *value)
{
    product = value;
    setNum(product->getProductId());
    setCommondityName(product->getProductName());
    setCommondityAuthor(QString::number(product->getProductDiscount()));
    setCommondityTimer(QString::number(product->getProductPrice()));
    setCommondityAlbum(QString::number(product->getProductBuyNum()));
    setPicture(product->getProductImage());

}

void NewSelectItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit sglSetClick(product->getProductId(),product->getProductNum(),product->getProductName(),product->getProductImage(),QString::number(product->getProductPrice()));
}
