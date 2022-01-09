#ifndef COMMENDLISTITEM_H
#define COMMENDLISTITEM_H

#include <QWidget>
#include "galleryitem.h"
#include <QList>
#include "galleryprivate.h"
#include "objects.h"
namespace Ui {
class CommendListItem;
}
//推荐商品中的四个商品整合类
class CommendListItem : public QWidget
{
    Q_OBJECT

public:
    explicit CommendListItem(QWidget *parent = nullptr);
    ~CommendListItem();
    void addGallerItem();
    void setProductList(const QList<Product *> &value);

private:
    Ui::CommendListItem *ui;
    QList<GalleryItem*> GalleryList;
    GalleryItem * item;
    GalleryPrivate * galleryPrivate;
protected:
    QList<Product*>ProductList;
signals:
    void sglClick(int id,QString name,QString price,float discount,QString Image);
};

#endif // COMMENDLISTITEM_H
