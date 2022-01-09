#ifndef NEWSELECTITEM_H
#define NEWSELECTITEM_H

#include <QWidget>
#include <QMouseEvent>
#include "rightcheck.h"
#include "objects.h"
namespace Ui {
class NewSelectItem;
}
//搜索列表中的状态栏类
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
    int id;
    QString name;
    Product * product;
    int num;
private:
    Ui::NewSelectItem *ui;
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);

    RightCheck * RightWidget;
Q_SIGNALS:
    void ChangetoModified();
    void delNewSelectitem(int num);

};

#endif // NEWSELECTITEM_H
