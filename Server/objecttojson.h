#ifndef OBJECTTOJSON_H
#define OBJECTTOJSON_H
#include "objects.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QString>
#include <QList>
#include <QByteArray>
#include <QJsonValue>
#include <QVariant>
//解释同Client
class ObjectToJson
{
public:
    ObjectToJson();
    static QJsonObject integrateClientList(QJsonObject &object,QList<Client*>ClientList);
    static QJsonObject integrateProductList(QJsonObject &object,QList<Product*>ProductList);
    static QJsonObject integrateProductTypeList(QJsonObject &object,QList<ProductType*>ProductTypeList);
    static QJsonObject integrateOrderList(QJsonObject &object,QList<Order*>OrderList);
    static QJsonObject integrateObjects(QJsonObject &object,int number,QString string);
    static QJsonObject integrateString(QJsonObject &object,QString id,QString passage);
    static QJsonObject integrateNum(QJsonObject &object, int number);
    static QList<Client*> parseClient(QByteArray object);
    static QList<Product*> parseProduct(QByteArray object);
    static QList<ProductType*> parseProductType(QByteArray object);
    static QList<Order*> parseOrder(QByteArray object);
    static QJsonObject addSignal(QJsonObject &object,QString signal);
    static QString parseSignal(QByteArray object);
    static void parseNum(QByteArray object);
    static void parseObjects(QByteArray object);
    static void parseString(QByteArray object);
    static QByteArray changeJson(QJsonObject& object);
    static int number;
    static QString string;
    static QString id;
    static QString passage;
};

#endif // OBJECTTOJSON_H
