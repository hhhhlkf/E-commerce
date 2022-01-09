#ifndef COMMODITY_H
#define COMMODITY_H

#include <QWidget>
#include <QString>
#include <QErrorMessage>
#include "objects.h"
namespace Ui {
class Commodity;
}
//购买商品界面
class Commodity : public QWidget
{
    Q_OBJECT

public:
    explicit Commodity(QWidget *parent = nullptr);
    ~Commodity();
    void setPic(QString);
    void setCommodityName(QString);
    void setCommodityPrice(QString);
    void setCommodityNum(int num);
    void setCommodityId(int id);
    void setCommodityType(QString type);
    void setTypeList(QList<ProductType*>TypeList);
    void setDiscount(bool flag);
//    void setCommodity
    float getPrice() const;
    void setPrice(float value);

private slots:
    void on_ptnBuy_clicked();

    void on_btnBuy_clicked();
private:
    Ui::Commodity *ui;
    int num;
    QString str;
    bool isDigital;
    bool isDiscount;
    float Price;
    QList<ProductType*>TypeList;
signals:
    void createOrder(int orderCheck,int productId,QString productName,
                     QString producStyle,int buynum,float price);
};

#endif // COMMODITY_H
