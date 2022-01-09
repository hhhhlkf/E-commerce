#include "galleryitem.h"
#include "ui_galleryitem.h"
#include <QPalette>
#include <QDebug>
#include <QIcon>
GalleryItem::GalleryItem(QWidget *parent,Product* product) :
    QWidget(parent),
    ui(new Ui::GalleryItem),product(product)
{
    ui->setupUi(this);
    //去掉滑动条

    setAttribute(Qt::WA_StyledBackground); //设置样式表
    //设置样式
    this->setStyleSheet("QWidget#GalleryItem{border:0px; background:white; border-radius:5px;}");
//    ui->itemPic->setStyleSheet("QWidget#itemPic{border:1px; background:white; border-radius:5px;}");
    ui->textEdit->setStyleSheet("QTextEdit{border:0px; background:white;}"
                                "QTextEdit{color:rgb(55,55,55)}");

    ui->itemPic->setAutoFillBackground(true); //用调色板需要用到
    ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

GalleryItem::~GalleryItem()
{
    delete ui;
}

void GalleryItem::setMessage()
{
    ui->textEdit->setText("名称:"+product->getProductName()+"\n价格:"+QString::number(product->getProductPrice()));
}

void GalleryItem::setPicture()
{
      QString str = "QWidget{border-image:url("+product->getProductImage()+");}";
      ui->pushButton->setStyleSheet(str);
}

Product *GalleryItem::getProduct() const
{
    return product;
}

void GalleryItem::setProduct(Product *value)
{
    product = value;
    if(product!=nullptr)
    {
        setMessage();
        setPicture();
    }
}



void GalleryItem::on_pushButton_clicked()
{
    emit sglClick(product->getProductId(),product->getProductName(),QString::number(product->getProductPrice()),
                  product->getProductDiscount(),product->getProductImage());
}
