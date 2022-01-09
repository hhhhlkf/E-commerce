#ifndef NEWSELECTITEM_H
#define NEWSELECTITEM_H

#include <QWidget>
#include "objects.h"
namespace Ui {
class NewSelectItem;
}
//查询后显示的列表栏
class NewSelectItem : public QWidget
{
    Q_OBJECT

public:
    explicit NewSelectItem(QWidget *parent = nullptr);
    ~NewSelectItem();
    //设置id
    void setNum(int id);
    //设置图片
    void setPicture(QString url);
    //设置歌名
    void setCommondityName(QString CommondityName);
    //设置log 默认
    void setLogPic();
    //设置作者
    void setCommondityAuthor(QString author);
    //设置专辑
    void setCommondityAlbum(QString name);
    //设置timer
    void setCommondityTimer(QString strTimer);
    Product * product;
    Product *getProduct() const;
    void setProduct(Product *value);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    Ui::NewSelectItem *ui;

signals:
    void sglSetClick(int id,int num,QString name,QString Image,QString money);
};

#endif // NEWSELECTITEM_H
