#ifndef OBJECTS_H
#define OBJECTS_H
#include <QString>
#include <QDateTime>
//pojo
class Client
{
private:
    QString clientName;
    int clientId;
    QString clientPhone;
    QString clientEmail;
    QDateTime clientSignTime;
    QString clientPwd;
    int clientBought;
    QString clientImage;

public:
    Client();
    Client(QString clientName, int clientId, QString clientPhone, QString clientEmail, QDateTime clientSignTime, QString clientPwd, int clientBought, QString clientImage);

    void setClientName(QString clientName);
    void setClientId(int clientId);
    void setClientPhone(QString clientPhone);
    void setClientEmail(QString clientEmail);
    void setClientSignTime(QDateTime clientSignTime);
    void setClientPwd(QString clientPwd);
    void setClientBought(int clientBought);
    void setClientImage(QString clientImage);


    QString getClientImage() const;
    int getClientBought() const;
    QString getClientPwd() const;
    QDateTime getClientSignTime() const;
    QString getClientEmail() const;
    QString getClientPhone() const;
    int getClientId() const;
    QString getClientName() const;
};

class Order
{
public:
    Order();
    Order(int orderId, QString orderProductName, int orderProductNum, QString orderProductStyle, int orderProductId, QString orderCost, QDateTime orderTime, QString orderClient, int orderClientId, int orderCheck, int orderHide);


    int getOrderHide() const;
    void setOrderHide(int value);

    int getOrderCheck() const;
    void setOrderCheck(int value);

    int getOrderClientId() const;
    void setOrderClientId(int value);

    QString getOrderClient() const;
    void setOrderClient(const QString &value);

    QDateTime getOrderTime() const;
    void setOrderTime(const QDateTime &value);

    QString getOrderCost() const;
    void setOrderCost(const QString &value);

    int getOrderProductId() const;
    void setOrderProductId(int value);

    QString getOrderProductStyle() const;
    void setOrderProductStyle(const QString &value);

    int getOrderProductNum() const;
    void setOrderProductNum(int value);

    QString getOrderProductName() const;
    void setOrderProductName(const QString &value);

    int getOrderId() const;
    void setOrderId(int value);

private:
    int orderId;
    QString orderProductName;
    int orderProductNum;
    QString orderProductStyle;
    int orderProductId;
    QString orderCost;
    QDateTime orderTime;
    QString orderClient;
    int orderClientId;
    int orderCheck;
    int orderHide;
};


class Product
{
public:
    Product();
    Product(int productId, QString productName, int productPrice, int productNum, int productBuyNum, QString productImage, float productDiscount);
    float getProductDiscount() const;
    void setProductDiscount(float value);

    QString getProductImage() const;
    void setProductImage(const QString &value);

    int getProductBuyNum() const;
    void setProductBuyNum(int value);

    int getProductNum() const;
    void setProductNum(int value);

    int getProductPrice() const;
    void setProductPrice(int value);

    QString getProductName() const;
    void setProductName(const QString &value);

    int getProductId() const;
    void setProductId(int value);

private:
    int productId;
    QString productName;
    int productPrice;
    int productNum;
    int productBuyNum;
    QString productImage;
    float productDiscount;
};


class ProductType
{
public:
    ProductType();
    ProductType(QString typeName, int typeId, QString typeProduct, int typeProductId);

    QString getTypeName() const;
    void setTypeName(const QString &value);

    int getTypeId() const;
    void setTypeId(int value);

    QString getTypeProduct() const;
    void setTypeProduct(const QString &value);

    int getTypeProductId() const;
    void setTypeProductId(int value);

private:
    QString typeName;
    int typeId;
    QString typeProduct;
    int typeProductId;
};

#endif // OBJECTS_H
