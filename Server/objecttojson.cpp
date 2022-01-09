#include "objecttojson.h"

int ObjectToJson::number = 0;
QString ObjectToJson::string  = nullptr;
QString ObjectToJson::id = 0;
QString ObjectToJson::passage = nullptr;
ObjectToJson::ObjectToJson()
{

}

QJsonObject ObjectToJson::integrateClientList(QJsonObject &object, QList<Client *> ClientList)
{
//    QJsonObject object;
    QJsonObject* objectList;
    QJsonArray array;
    int size = ClientList.size();
    objectList = new QJsonObject[size];
    for (int i=0;i<size;i++) {
        objectList[i].insert("clientName",ClientList[i]->getClientName());
        objectList[i].insert("clientId",ClientList[i]->getClientId());
        objectList[i].insert("clientPhone",ClientList[i]->getClientPhone());
        objectList[i].insert("clientEmail",ClientList[i]->getClientEmail());
        objectList[i].insert("clientSignTime",ClientList[i]->getClientSignTime().toString());
        objectList[i].insert("clientPwd",ClientList[i]->getClientPwd());
        objectList[i].insert("clientBought",ClientList[i]->getClientBought());
        objectList[i].insert("clientImage",ClientList[i]->getClientImage());
        array.append(objectList[i]);
    }
//    object.insert("signal",signal);
    object.insert("ClientList",QJsonValue(array));
    return object;
}

QJsonObject ObjectToJson::integrateProductList(QJsonObject &object, QList<Product *> ProductList)
{
//    QJsonObject object;
    QJsonObject* objectList;
    QJsonArray array;
    int size = ProductList.size();
    objectList = new QJsonObject[size];
    for (int i=0;i<size;i++) {
          objectList[i].insert("productId",ProductList[i]->getProductId());
          objectList[i].insert("productName",ProductList[i]->getProductName());
          objectList[i].insert("productPrice",ProductList[i]->getProductPrice());
          objectList[i].insert("productNum",ProductList[i]->getProductNum());
          objectList[i].insert("productBuyNum",ProductList[i]->getProductBuyNum());
          objectList[i].insert("productImage",ProductList[i]->getProductImage());
          objectList[i].insert("productDiscount",ProductList[i]->getProductDiscount());
          array.append(objectList[i]);
    }
//    object.insert("signal",signal);
    object.insert("ProductList",QJsonValue(array));
    return object;
}

QJsonObject ObjectToJson::integrateProductTypeList(QJsonObject &object, QList<ProductType *> ProductTypeList)
{
//    QJsonObject object;
    QJsonObject* objectList;
    QJsonArray array;
    int size = ProductTypeList.size();
    objectList = new QJsonObject[size];
        for (int i=0;i<size;i++) {
            objectList[i].insert("typeName",ProductTypeList[i]->getTypeName());
            objectList[i].insert("typeId",ProductTypeList[i]->getTypeId());
            objectList[i].insert("typeProduct",ProductTypeList[i]->getTypeProduct());
            objectList[i].insert("typeProductId",ProductTypeList[i]->getTypeProductId());
            array.append(objectList[i]);
        }
//    object.insert("signal",signal);
    object.insert("ProductTypeList",QJsonValue(array));
    return object;
}

QJsonObject ObjectToJson::integrateOrderList(QJsonObject &object, QList<Order *> OrderList)
{
//    QJsonObject object;
    QJsonObject* objectList;
    QJsonArray array;
    int size = OrderList.size();
    objectList = new QJsonObject[size];
        for (int i=0;i<size;i++) {
            objectList[i].insert("orderId",OrderList[i]->getOrderId());
            objectList[i].insert("orderProductName",OrderList[i]->getOrderProductName());
            objectList[i].insert("orderProductNum",OrderList[i]->getOrderProductNum());
            objectList[i].insert("orderProductStyle",OrderList[i]->getOrderProductStyle());
            objectList[i].insert("orderProductId",OrderList[i]->getOrderProductId());
            objectList[i].insert("orderCost",OrderList[i]->getOrderCost());
            objectList[i].insert("orderTime",OrderList[i]->getOrderTime().toString());
            objectList[i].insert("orderClient",OrderList[i]->getOrderClient());
            objectList[i].insert("orderClientId",OrderList[i]->getOrderClientId());
            objectList[i].insert("orderCheck",OrderList[i]->getOrderCheck());
            objectList[i].insert("orderHide",OrderList[i]->getOrderHide());
            array.append(objectList[i]);
        }
//    object.insert("signal",signal);
    object.insert("OrderList",QJsonValue(array));
    return object;
}

QJsonObject ObjectToJson::integrateObjects(QJsonObject &object, int number, QString string)
{
//    QJsonObject object;
//    object.insert("signal",signal);
    object.insert("number",number);
    object.insert("string",string);
        return object;
}

QJsonObject ObjectToJson::integrateString(QJsonObject &object, QString id, QString passage)
{
//    QJsonObject object;
//    object.insert("signal",signal);
    object.insert("id",id);
    object.insert("passage",passage);
        return object;
}

QJsonObject ObjectToJson::integrateNum(QJsonObject &object, int number)
{
    /*QJsonObject object*/
//    object.insert("signal",signal);
    object.insert("number",number);
    return object;
}

QJsonObject ObjectToJson::addSignal(QJsonObject &object, QString signal)
{
    object.insert("signal",signal);
    return object;
}

QString ObjectToJson::parseSignal(QByteArray byteArray)
{
        QJsonParseError jsonError;
        QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
        if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)){
            if(doucment.isObject()){
                QJsonObject object = doucment.object();
                if(object.contains("signal")){
                    QJsonValue value =object.value("signal");
                    return value.toString();
                }
            }
        }
        return "";
}

QList<Client *> ObjectToJson::parseClient(QByteArray byteArray)
{

    QJsonParseError jsonError;
    QList<Client*> clientList;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)){
           if (doucment.isObject()){
                QJsonObject object = doucment.object();
                if(object.contains("ClientList")){
                    QJsonValue value = object.value("ClientList");
                    if(value.isArray()){
                        QJsonArray array = value.toArray();
                        int size = array.size();
                        for(int i=0;i<size;i++){
                            if(array[i].isObject()){
                                QJsonObject clientObject = array[i].toObject();
                                Client * client = new Client;
                                if(clientObject.contains("clientName")){
                                    QJsonValue object = clientObject.value("clientName");
                                    client->setClientName(object.toString());
                                }
                                if(clientObject.contains("clientId")){
                                    QJsonValue object = clientObject.value("clientId");
                                    client->setClientId(object.toVariant().toInt());
                                }
                                if(clientObject.contains("clientPhone")){
                                    QJsonValue object = clientObject.value("clientPhone");
                                    client->setClientPhone(object.toString());
                                }
                                if(clientObject.contains("clientEmail")){
                                    QJsonValue object = clientObject.value("clientEmail");
                                    client->setClientEmail(object.toString());
                                }
                                if(clientObject.contains("clientSignTime")){
                                    QJsonValue object = clientObject.value("clientSignTime");
                                    client->setClientSignTime(QDateTime::currentDateTime());
                                }
                                if(clientObject.contains("clientPwd")){
                                    QJsonValue object = clientObject.value("clientPwd");
                                    client->setClientPwd(object.toString());
                                }
                                if(clientObject.contains("clientBought")){
                                    QJsonValue object = clientObject.value("clientBought");
                                    client->setClientBought(object.toVariant().toInt());
                                }
                                if(clientObject.contains("clientImage")){
                                    QJsonValue object = clientObject.value("clientImage");
                                    client->setClientImage(object.toString());
                                }
                                clientList.append(client);
                            }
                        }
                    }
                }
           }
    }
    return clientList;
}

QList<Product *> ObjectToJson::parseProduct(QByteArray byteArray)
{
    QJsonParseError jsonError;
    QList<Product*> productList;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)){
           if (doucment.isObject()){
                QJsonObject object = doucment.object();
                if(object.contains("ProductList")){
                    QJsonValue value = object.value("ProductList");
                    if(value.isArray()){
                        QJsonArray array = value.toArray();
                        int size = array.size();
                        for(int i=0;i<size;i++){
                            if(array[i].isObject()){
                                QJsonObject productObject = array[i].toObject();
                                Product * product = new Product;
                                if(productObject.contains("productName")){
                                    QJsonValue object = productObject.value("productName");
                                    product->setProductName(object.toString());
                                }
                                if(productObject.contains("productId")){
                                    QJsonValue object = productObject.value("productId");
                                    product->setProductId(object.toVariant().toInt());
                                }
                                if(productObject.contains("productPrice")){
                                    QJsonValue object = productObject.value("productPrice");
                                    product->setProductPrice(object.toVariant().toInt());
                                }
                                if(productObject.contains("productNum")){
                                    QJsonValue object = productObject.value("productNum");
                                    product->setProductNum(object.toVariant().toInt());
                                }
                                if(productObject.contains("productBuyNum")){
                                    QJsonValue object = productObject.value("productBuyNum");
                                    product->setProductBuyNum(object.toVariant().toInt());
                                }
                                if(productObject.contains("productDiscount")){
                                    QJsonValue object = productObject.value("productDiscount");
                                    product->setProductDiscount(object.toVariant().toFloat());
                                }
                                if(productObject.contains("productImage")){
                                    QJsonValue object = productObject.value("productImage");
                                    product->setProductImage(object.toString());
                                }
                                productList.append(product);
                            }
                        }
                    }
                }
           }
    }
    return productList;
}

QList<ProductType *> ObjectToJson::parseProductType(QByteArray byteArray)
{
    QJsonParseError jsonError;
    QList<ProductType*> productTypeList;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)){
           if (doucment.isObject()){
                QJsonObject object = doucment.object();
                if(object.contains("ProductTypeList")){
                    QJsonValue value = object.value("ProductTypeList");
                    if(value.isArray()){
                        QJsonArray array = value.toArray();
                        int size = array.size();
                        for(int i=0;i<size;i++){
                            if(array[i].isObject()){
                                QJsonObject productTypeObject = array[i].toObject();
                                ProductType * productType = new ProductType;
                                if(productTypeObject.contains("typeName")){
                                    QJsonValue object = productTypeObject.value("typeName");
                                    productType->setTypeName(object.toString());
                                }
                                if(productTypeObject.contains("typeId")){
                                    QJsonValue object = productTypeObject.value("typeId");
                                    productType->setTypeId(object.toVariant().toInt());
                                }
                                if(productTypeObject.contains("typeProduct")){
                                    QJsonValue object = productTypeObject.value("typeProduct");
                                    productType->setTypeProduct(object.toString());
                                }
                                if(productTypeObject.contains("typeProductId")){
                                    QJsonValue object = productTypeObject.value("typeProductId");
                                    productType->setTypeProductId(object.toVariant().toInt());
                                }

                                productTypeList.append(productType);
                            }
                        }
                    }
                }
           }
    }return productTypeList;
}


QList<Order *> ObjectToJson::parseOrder(QByteArray byteArray)
{
    QJsonParseError jsonError;
    QList<Order*> orderList;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)){
           if (doucment.isObject()){
                QJsonObject object = doucment.object();
                if(object.contains("OrderList")){
                    QJsonValue value = object.value("OrderList");
                    if(value.isArray()){
                        QJsonArray array = value.toArray();
                        int size = array.size();
                        for(int i=0;i<size;i++){
                            if(array[i].isObject()){
                                QJsonObject orderObject = array[i].toObject();
                                Order * order = new Order;
                                if(orderObject.contains("orderProductName")){
                                    QJsonValue object = orderObject.value("orderProductName");
                                    order->setOrderProductName(object.toString());
                                }
                                if(orderObject.contains("orderId")){
                                    QJsonValue object = orderObject.value("orderId");
                                    order->setOrderId(object.toVariant().toInt());
                                }
                                if(orderObject.contains("orderProductId")){
                                    QJsonValue object = orderObject.value("orderProductId");
                                    order->setOrderProductId(object.toVariant().toInt());
                                }
                                if(orderObject.contains("orderProductNum")){
                                    QJsonValue object = orderObject.value("orderProductNum");
                                    order->setOrderProductNum(object.toVariant().toInt());
                                }
                                if(orderObject.contains("orderProductStyle")){
                                    QJsonValue object = orderObject.value("orderProductStyle");
                                    order->setOrderProductStyle(object.toString());
                                }
                                if(orderObject.contains("orderTime")){
                                    QJsonValue object = orderObject.value("orderTime");
                                    order->setOrderTime(QDateTime::currentDateTime());
                                }
                                if(orderObject.contains("orderCost")){
                                    QJsonValue object = orderObject.value("orderCost");
                                    order->setOrderCost(object.toString());
                                }
                                if(orderObject.contains("orderClient")){
                                    QJsonValue object = orderObject.value("orderClient");
                                    order->setOrderClient(object.toString());
                                }
                                if(orderObject.contains("orderClientId")){
                                    QJsonValue object = orderObject.value("orderClientId");
                                    order->setOrderClientId(object.toVariant().toInt());
                                }
                                if(orderObject.contains("orderCheck")){
                                    QJsonValue object = orderObject.value("orderCheck");
                                    order->setOrderCheck(object.toVariant().toInt());
                                }
                                if(orderObject.contains("orderHide")){
                                    QJsonValue object = orderObject.value("orderHide");
                                    order->setOrderHide(object.toVariant().toInt());
                                }
                                orderList.append(order);
                            }
                        }
                    }
                }
           }
    }return orderList;
}



void ObjectToJson::parseNum(QByteArray byteArray)
{
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)){
        if (doucment.isObject()){
            QJsonObject object = doucment.object();
            if(object.contains("number")){
                QJsonValue value = object.value("number");
                number = value.toVariant().toInt();
            }
        }
    }
}

void ObjectToJson::parseObjects(QByteArray byteArray)
{
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)){
        if (doucment.isObject()){
            QJsonObject object = doucment.object();
            if(object.contains("number")){
                QJsonValue value = object.value("number");
                number = value.toVariant().toInt();
            }
            if(object.contains("string")){
                QJsonValue value = object.value("string");
                string = value.toString();
            }
        }
    }
}

void ObjectToJson::parseString(QByteArray byteArray)
{
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)){
        if (doucment.isObject()){
            QJsonObject object = doucment.object();
            if(object.contains("id")){
                QJsonValue value = object.value("id");
                id = value.toVariant().toInt();
            }
            if(object.contains("passage")){
                QJsonValue value = object.value("passage");
                passage = value.toString();
            }
        }
    }
}

QByteArray ObjectToJson::changeJson(QJsonObject &object)
{
        QJsonDocument document;
        document.setObject(object);
        QByteArray byteArray = document.toJson(QJsonDocument::Compact);
        return byteArray;
}


