#ifndef NEWCOURIERITEM_H
#define NEWCOURIERITEM_H

#include <QWidget>
#include "objects.h"
namespace Ui {
class NewCourierItem;
}
//购物车和历史记录列表栏
class NewCourierItem : public QWidget
{
    Q_OBJECT

public:
    explicit NewCourierItem(QWidget *parent = nullptr);
    ~NewCourierItem();
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

    bool getCheckBox();
    int number;
    void setcheckBox();
    Order * order;
    Order *getOrder() const;
    void setOrder(Order *value);
    QString image;
    QString getImage() const;
    void setImage(const QString &value);
    void mouseDoubleClickEvent(QMouseEvent *event);
private:
    Ui::NewCourierItem *ui;

signals:
    void sglClicked(int id,int num,QString ProductName,QString ProductStyle);
//    emit sglClicked(order->getOrderProductId(),order->getOrderProductNum(),order->getOrderProductName(),order->getOrderProductStyle());

};

#endif // NEWCOURIERITEM_H
