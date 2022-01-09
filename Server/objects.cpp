#include "objects.h"



Client::Client():clientId(0),clientBought(0)
{

}

Client::Client(QString clientName, int clientId, QString clientPhone, QString clientEmail, QDateTime clientSignTime, QString clientPwd, int clientBought, QString clientImage)
{
    this->clientName = clientName;
    this->clientId = clientId;
    this->clientPhone = clientPhone;
    this->clientEmail = clientEmail;
    this->clientSignTime = clientSignTime;
    this->clientPwd = clientPwd;
    this->clientBought = clientBought;
    this->clientImage = clientImage;
}

QString Client::getClientName() const
{
    return clientName;
}

int Client::getClientId() const
{
    return clientId;
}

QString Client::getClientPhone() const
{
    return clientPhone;
}

QString Client::getClientEmail() const
{
    return clientEmail;
}

QDateTime Client::getClientSignTime() const
{
    return clientSignTime;
}

QString Client::getClientPwd() const
{
    return clientPwd;
}

int Client::getClientBought() const
{
    return clientBought;
}

QString Client::getClientImage() const
{
    return clientImage;
}

void Client::setClientName(QString clientName)
{
    this->clientName = clientName;
}

void Client::setClientId(int clientId)
{
    this->clientId = clientId;
}

void Client::setClientPhone(QString clientPhone)
{
    this->clientPhone = clientPhone;
}

void Client::setClientEmail(QString clientEmail)
{
    this->clientEmail = clientEmail;
}

void Client::setClientSignTime(QDateTime clientSignTime)
{
    this->clientSignTime = clientSignTime;
}

void Client::setClientPwd(QString clientPwd)
{
    this->clientPwd = clientPwd;
}

void Client::setClientBought(int clientBought)
{
    this->clientBought = clientBought;
}

void Client::setClientImage(QString clientImage)
{
    this->clientImage = clientImage;
}

Order::Order():orderId(0),orderProductNum(0),orderProductId(0),orderClientId(0),orderCheck(0),orderHide(0)
{

}

Order::Order(int orderId, QString orderProductName, int orderProductNum, QString orderProductStyle, int orderProductId, QString orderCost, QDateTime orderTime, QString orderClient, int orderClientId, int orderCheck, int orderHide)
{
    this->orderId = orderId;
    this->orderProductName = orderProductName;
    this->orderProductNum = orderProductNum;
    this->orderProductStyle = orderProductStyle;
    this->orderProductId = orderProductId;
    this->orderCost = orderCost;
    this->orderTime = orderTime;
    this->orderClient = orderClient;
    this->orderClientId = orderClientId;
    this->orderCheck = orderCheck;
    this->orderHide = orderHide;
}

int Order::getOrderHide() const
{
    return orderHide;
}

void Order::setOrderHide(int value)
{
    orderHide = value;
}

int Order::getOrderCheck() const
{
    return orderCheck;
}

void Order::setOrderCheck(int value)
{
    orderCheck = value;
}

int Order::getOrderClientId() const
{
    return orderClientId;
}

void Order::setOrderClientId(int value)
{
    orderClientId = value;
}

QString Order::getOrderClient() const
{
    return orderClient;
}

void Order::setOrderClient(const QString &value)
{
    orderClient = value;
}

QDateTime Order::getOrderTime() const
{
    return orderTime;
}

void Order::setOrderTime(const QDateTime &value)
{
    orderTime = value;
}

QString Order::getOrderCost() const
{
    return orderCost;
}

void Order::setOrderCost(const QString &value)
{
    orderCost = value;
}

int Order::getOrderProductId() const
{
    return orderProductId;
}

void Order::setOrderProductId(int value)
{
    orderProductId = value;
}

QString Order::getOrderProductStyle() const
{
    return orderProductStyle;
}

void Order::setOrderProductStyle(const QString &value)
{
    orderProductStyle = value;
}

int Order::getOrderProductNum() const
{
    return orderProductNum;
}

void Order::setOrderProductNum(int value)
{
    orderProductNum = value;
}

QString Order::getOrderProductName() const
{
    return orderProductName;
}

void Order::setOrderProductName(const QString &value)
{
    orderProductName = value;
}

int Order::getOrderId() const
{
    return orderId;
}

void Order::setOrderId(int value)
{
    orderId = value;
}

Product::Product():productId(0),productPrice(0),productNum(0),productBuyNum(0),productDiscount(0)
{

}

Product::Product(int productId, QString productName, int productPrice, int productNum, int productBuyNum, QString productImage, float productDiscount)
{
    this->productId = productId;
    this->productName = productName;
    this->productPrice = productPrice;
    this->productNum = productNum;
    this->productBuyNum = productBuyNum;
    this->productImage = productImage;
    this->productDiscount = productDiscount;
}

float Product::getProductDiscount() const
{
    return productDiscount;
}

void Product::setProductDiscount(float value)
{
    productDiscount = value;
}

QString Product::getProductImage() const
{
    return productImage;
}

void Product::setProductImage(const QString &value)
{
    productImage = value;
}

int Product::getProductBuyNum() const
{
    return productBuyNum;
}

void Product::setProductBuyNum(int value)
{
    productBuyNum = value;
}

int Product::getProductNum() const
{
    return productNum;
}

void Product::setProductNum(int value)
{
    productNum = value;
}

int Product::getProductPrice() const
{
    return productPrice;
}

void Product::setProductPrice(int value)
{
    productPrice = value;
}

QString Product::getProductName() const
{
    return productName;
}

void Product::setProductName(const QString &value)
{
    productName = value;
}

int Product::getProductId() const
{
    return productId;
}

void Product::setProductId(int value)
{
    productId = value;
}

ProductType::ProductType():typeId(0),typeProductId(0)
{

}

ProductType::ProductType(QString typeName, int typeId, QString typeProduct, int typeProductId)
{
    this->typeName = typeName;
    this->typeId = typeId;
    this->typeProduct = typeProduct;
    this->typeProductId = typeProductId;
}

QString ProductType::getTypeName() const
{
    return typeName;
}

void ProductType::setTypeName(const QString &value)
{
    typeName = value;
}



int ProductType::getTypeId() const
{
    return typeId;
}

void ProductType::setTypeId(int value)
{
    typeId = value;
}



QString ProductType::getTypeProduct() const
{
    return typeProduct;
}

void ProductType::setTypeProduct(const QString &value)
{
    typeProduct = value;
}

int ProductType::getTypeProductId() const
{
    return typeProductId;
}

void ProductType::setTypeProductId(int value)
{
    typeProductId = value;
}
