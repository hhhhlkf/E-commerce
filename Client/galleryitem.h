#ifndef GALLERYITEM_H
#define GALLERYITEM_H

#include <QWidget>
#include "objects.h"
namespace Ui {
class GalleryItem;
}
//推荐列表单个商品类
class GalleryItem : public QWidget
{
    Q_OBJECT

public:
    explicit GalleryItem(QWidget *parent = nullptr,Product* product = nullptr);
    ~GalleryItem();
    //设置说明
    void setMessage();
    //设置图片
    void setPicture();


    Product *getProduct() const;
    void setProduct(Product *value);

private slots:
    void on_pushButton_clicked();


private:
    Ui::GalleryItem *ui;
    Product *product;
signals:
    void sglClick(int id,QString name,QString price,float discount,QString Image);
};

#endif // GALLERYITEM_H
