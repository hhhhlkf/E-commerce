#include "transobjects.h"
#include "objects.h"
#include "soap/soapH.h"
#include "soap/soapStub.h"
#include "soap/ProductTypeMapperSoapBinding.nsmap"
#include "stringtrans.h"
class transObjects
{
public:
    transObjects();
    static Client * transClient(bn1__client * javaclient);
    static Order * transOrder(dn1__order* javaorder);
    static Product * transProduct(an1__product* javaproduct);
    static ProductType * transProductType(cn1__productType* javaproductType);

    static bn1__client * retransClient(Client *client);
    static dn1__order * retransOrder(Order *order);
    static an1__product* retransProduct(Product * product);
    static cn1__productType* retransProductType(ProductType * productType);
};
transObjects::transObjects()
{

}

Client *transObjects::transClient(bn1__client *javaclient)
{
    Client* client = new Client();
    client->setClientId(javaclient->clientId);
    client->setClientName(StringTrans::string2QString(javaclient->clientName));
    client->setClientPwd(StringTrans::string2QString(javaclient->clientPwd));
    client->setClientPhone(StringTrans::string2QString(javaclient->clientPhone));
    client->setClientEmail(StringTrans::string2QString(javaclient->clientEmail));
    client->setClientSignTime(StringTrans::tTime2QDateTime(javaclient->clientSignTime));
    client->setClientPwd(StringTrans::string2QString(javaclient->clientPwd));
    client->setClientBought(javaclient->clientBought);
    client->setClientImage(StringTrans::string2QString(javaclient->clientImage));
    return client;
}

Order *transObjects::transOrder(dn1__order *javaorder)
{
    Order*order = new Order();
    order->setOrderId(javaorder->orderId);
    order->setOrderCost(StringTrans::string2QString(javaorder->orderCost));
    order->setOrderHide(javaorder->orderHide);
    order->setOrderTime(StringTrans::tTime2QDateTime(javaorder->orderTime));
    order->setOrderCheck(javaorder->orderCheck);
    order->setOrderClient(StringTrans::string2QString(javaorder->orderClient));
    order->setOrderClientId(javaorder->orderClientId);
    order->setOrderProductId(javaorder->orderProductId);
    order->setOrderProductNum(javaorder->orderProductNum);
    order->setOrderProductName(StringTrans::string2QString(javaorder->orderProductName));
    order->setOrderProductStyle(StringTrans::string2QString(javaorder->orderProductStyle));
    return order;
}

Product *transObjects::transProduct(an1__product *javaproduct)
{
    Product * product = new Product();
    product->setProductDiscount(javaproduct->productDiscount);
    product->setProductImage(StringTrans::string2QString(javaproduct->productImage));
    product->setProductBuyNum(javaproduct->productBuyNum);
    product->setProductNum(javaproduct->productNum);
    product->setProductPrice(javaproduct->productPrice);
    product->setProductName(StringTrans::string2QString(javaproduct->productName));
    product->setProductId(javaproduct->productId);
    return product;
}

ProductType *transObjects::transProductType(cn1__productType *javaproductType)
{
    ProductType * productType = new ProductType();
    productType->setTypeName(StringTrans::string2QString(javaproductType->typeName));

    productType->setTypeId(javaproductType->typeId);

    productType->setTypeProduct(StringTrans::string2QString(javaproductType->typeProduct));

    productType->setTypeProductId(javaproductType->typeProductId);

    return productType;
}

bn1__client *transObjects::retransClient(Client *client)
{
//    bn1__client(int bought,std::string *email,int id,std::string *image,
    //std::string *name,std::string *phone,std::string *pwd,time_t *time) :

//    bn1__client *javaclient = new bn1__client();

     int bought =client->getClientBought();
     std::string *email = StringTrans::QString2string(client->getClientEmail());
     int id = client->getClientId();
     std::string *image = StringTrans::QString2string(client->getClientImage());
     std::string * name = StringTrans::QString2string(client->getClientImage());
     std::string * phone  =StringTrans::QString2string(client->getClientPhone());
     std::string * pwd = StringTrans::QString2string(client->getClientPwd());
     time_t *time = StringTrans::QDateTime2tTime(client->getClientSignTime());
     return new bn1__client(bought,email,id,image,name,phone,pwd,time);
}

dn1__order *transObjects::retransOrder(Order *order)
{

    int check = order->getOrderCheck();
    std::string * client = StringTrans::QString2string(order->getOrderClient());
    int cid = order->getOrderClientId();
    std::string * cost = StringTrans::QString2string(order->getOrderCost());
    int hide = order->getOrderHide();
    int id = order->getOrderId();
    int pid = order->getOrderProductId();
    std::string * Pname = StringTrans::QString2string(order->getOrderProductName());
    int Pnum = order->getOrderProductNum();
    std::string * Pstyle = StringTrans::QString2string(order->getOrderProductStyle());
    time_t* time = StringTrans::QDateTime2tTime(order->getOrderTime());
    return new dn1__order(check,client,cid,cost,
    hide,id,pid,Pname,Pnum,Pstyle,time);
}

an1__product *transObjects::retransProduct(Product *product)
{
//    an1__product(int buynum,int discount,int pId,std::string *pImage,std::string *pName,
    //int pNum,int pPrice)
      int buynum = product->getProductBuyNum();
      float discount = product->getProductDiscount();
      int pId = product->getProductId();
      std::string * pImage = StringTrans::QString2string(product->getProductImage());
      std::string * pName = StringTrans::QString2string(product->getProductName());
      int pNum = product->getProductNum();
      int pPrice = product->getProductPrice();
      return new an1__product(buynum,discount,pId,pImage,pName,pNum,pPrice);
}

cn1__productType *transObjects::retransProductType(ProductType *productType)
{
     cn1__productType * javaProductType = new cn1__productType();
     javaProductType->typeId = productType->getTypeId();
     javaProductType->typeName = StringTrans::QString2string(productType->getTypeName());
     javaProductType->typeProduct =StringTrans::QString2string(productType->getTypeProduct());
     javaProductType->typeProductId = productType->getTypeProductId();
     return javaProductType;
}

