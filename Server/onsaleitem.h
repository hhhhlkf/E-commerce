#ifndef ONSALEITEM_H
#define ONSALEITEM_H

#include <QWidget>
#include <QIcon>
#include <QPushButton>
#include <QHBoxLayout>
#include "objects.h"
namespace Ui {
class onSaleItem;
}
//
class onSaleItem : public QWidget
{
    Q_OBJECT

public:
    int num;
    explicit onSaleItem(QWidget *parent = nullptr);
    ~onSaleItem();
    void setNum(int id);
    //设置图片
    void setPicture(QString url);
    //设置货物名称
    void setCommondityName(QString CommondityName);

    //设置作者
    void setCommondityAuthor(QString author);
    //设置专辑
    void setCommondityAlbum(QString name);
    //设置timer
    void setCommondityTimer(QString strTimer);
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent *event);
    int id;
    QString name;
    QString str;
    QIcon * pic;
    QWidget* delWidget;
    QPushButton * CloseBtn;
    int Width;
    QHBoxLayout * Layout;
    int productNumber;
private:
    Ui::onSaleItem *ui;
protected:
    void mousePressEvent(QMouseEvent *event);
signals:
    void getinfo(int productNum,QString str,int id,QString name,QString cost);
    void CloseSignal(int num,Product* product);
public slots:
    void CloseSlots();
public:
    int productNum;
};

#endif // ONSALEITEM_H
