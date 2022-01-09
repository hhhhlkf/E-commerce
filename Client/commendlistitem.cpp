#include "commendlistitem.h"
#include "ui_commendlistitem.h"
CommendListItem::CommendListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommendListItem)
{
    ui->setupUi(this);

}

CommendListItem::~CommendListItem()
{
    delete ui;
}

void CommendListItem::addGallerItem()
{
   galleryPrivate = new GalleryPrivate();
   GalleryItem*GalleryItems[4];
   for (int i = 0 ; i <= 3; i ++){
       GalleryItems[i] = new GalleryItem();
       GalleryItems[i]->setProduct(ProductList[i]);
       connect(GalleryItems[i],&GalleryItem::sglClick,[=](int id,QString name,QString price,float discount,QString Image)
       {
           emit sglClick(id,name,price,discount,Image);
       });
       GalleryList.append(GalleryItems[i]);
   }
   galleryPrivate->setItemRes(GalleryItems[0]->width(),GalleryItems[0]->height(),GalleryList);
   ui->horizontalLayout->setContentsMargins(0,0,0,0);
   ui->horizontalLayout->addWidget(galleryPrivate->getItemViewport());
   this->setStyleSheet("CommendListItem{border:1px; background:white; border-radius:5px;}");
}

void CommendListItem::setProductList(const QList<Product *> &value)
{
    ProductList = value;addGallerItem();
}

