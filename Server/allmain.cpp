#include "allmain.h"

#include "ui_allmain.h"
#include <string>
#include <vector>
#include "soapnew/soapH.h"
#include "soapnew/soapStub.h"
#include "soapnew/WholeMapperSoapBinding.nsmap"
#include <iostream>
long long AllMain::onSaleNum =0;
long long AllMain::ChatRoomNum=0;
long long AllMain::DelNum = 0;
QByteArray AllMain::Amessage = "";
qintptr AllMain::AsocketDiscriptor = 0;
class transObjects
{
public:
    transObjects();
    static Client * transClient(lkf2__client * javaclient);
    static Order * transOrder(lkf2__order* javaorder);
    static Product * transProduct(lkf2__product* javaproduct);
    static ProductType * transProductType(lkf2__productType* javaproductType);

    static lkf2__client * retransClient(Client *client);
    static lkf2__order * retransOrder(Order *order);
    static lkf2__product* retransProduct(Product * product);
    static lkf2__productType* retransProductType(ProductType * productType);
};
AllMain::AllMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AllMain)
{

    ui->setupUi(this);
    setList1();
    setList2();
    initall();
    setSlots();
    ui->tabWidgetFuc->setCurrentIndex(0);
    ui->tabWidget->setCurrentIndex(3);
    qDebug() << QThread::currentThread();
}

AllMain::~AllMain()
{
    delete ui;
}

void AllMain::setSlots()
{
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){
       this->close();
    });
    connect(ui->pushButton_min,&QPushButton::clicked,[=](){
       this->showMinimized();
    });
    connect(ui->listT1,&QListWidget::currentRowChanged,[=](int num){
         ui->tabWidget->setCurrentIndex(num);
         ui->listT2->setCurrentRow(-1);
    });
    connect(ui->listT2,&QListWidget::currentRowChanged,[=](int num)
    {
            ui->listT1->setCurrentRow(-1);
            ui->tabWidget->setCurrentIndex(num+3);

    });
    connect(this,&AllMain::sglsearch,[=](QList<Product*>List)
    {
        searchForm->setListItem(List);
    });
    connect(ui->line_Search2,&QLineEdit::textChanged,[=](QString text)
    {
        QList<Product*>ListP = getProductLikeList(text);
        emit sglsearch(ListP);
    });
    connect(ui->line_Search3,&QLineEdit::textChanged,[=](QString text)
    {
        QList<Product*>ListP = getProductLikeList(text);
        emit sglsearch(ListP);
    });
    connect(ui->line_Search4,&QLineEdit::textChanged,[=](QString text)
    {
        QList<Product*>ListP = getProductLikeList(text);
        searchForm1->setListItem(ListP);
    });
    connect(ui->ptnscearch2,&QPushButton::clicked,[=]()
    {
        if((!ui->line_Search2->text().isNull())&&ui->line_Search2->text()!="")
        {
            QList<Product*>ListP = getProductLikeList(ui->line_Search2->text());
            selectCommodity(ListP);
        }
    });
    connect(ui->ptnscearch3,&QPushButton::clicked,[=]()
    {
        if((!ui->line_Search3->text().isNull())&&ui->line_Search3->text()!="")
        {
            QList<Product*>ListP = getProductLikeList(ui->line_Search3->text());
            setDelPage(ListP);
        }
    });
    connect(ui->ptnscearch4,&QPushButton::clicked,[=]()
    {
        if((!ui->line_Search4->text().isNull())&&ui->line_Search4->text()!="")
        {
            QList<Product*>ListP = getProductLikeList(ui->line_Search4->text());
            setSelectOnsale(ListP);
        }
    });
    connect(ui->line_Search4,&QLineEdit::textChanged,[=](QString text)
    {
        QList<Product*>ListP = getProductLikeList(text);
        searchForm1->setListItem(ListP);
    });
    connect(ui->refreshBtn,&QPushButton::clicked,[=]()
    {
        if(!ui->line_Search2->text().isNull())
        {
            QList<Product*>ListP = getProductLikeList(ui->line_Search2->text());
            selectCommodity(ListP);
        }
    });
    connect(ui->refreshBtn2,&QPushButton::clicked,[=]()
    {
        if(!ui->line_Search3->text().isNull())
        {
            QList<Product*>ListP = getProductLikeList(ui->line_Search3->text());
            setDelPage(ListP);
        }
    });
    connect(Charts,&analysisCharts::refreshChart,[=](QString text)
    {
        QList<Order*> orderList = getOrderLikeList(text);
        Charts->initData(orderList);
    });
    connect(server,&TcpServer::sglRecivedReomClient,[=](QByteArray message, qintptr socketDiscriptor){
       dealMessage(message,socketDiscriptor);
       qDebug() <<"我的信号为："<< QThread::currentThread();
    });
    connect(this,&AllMain::sglSendByteArray,[=](QByteArray json,qintptr socketDiscriptor){
        server->dataSendFromServer(json,socketDiscriptor);
    });
    connect(server,&TcpServer::sendDisconnectedSignal,[=](qintptr socketDiscriptor){
        setNotification(2,QString::number(socketDiscriptor)+"断开连接");
    });
    connect(this,&AllMain::addChatRoom1,[=](Client*client,qintptr socketDiscriptor){
        addChatRoom(socketDiscriptor,client);
    });
}

void AllMain::dealMessage(QByteArray message, qintptr socketDiscriptor)
{
    QMutexLocker lock(&mutex);
    Client* client;
    QString Mess;
    QString signal = ObjectToJson::parseSignal(message);
     if(signal==""){
         //qDebug()<<"解析失败";
         setNotification(2,"解析失败");
         return;
     }
//     mutex.lock();
    if(signal==QString::number(initAll))
    {
        QList<Client*>clientList = ObjectToJson::parseClient(message);
        QJsonObject object;
        QList<Product* >productList = getProductList(2);
        ObjectToJson::integrateProductList(object,productList);
        Order* order =new Order;
        order->setOrderClient(clientList[0]->getClientName());
        order->setOrderClientId(clientList[0]->getClientId());
        order->setOrderHide(-1);
        QList<Order*>orderList = getOrderListByInfo(order);
        ObjectToJson::integrateOrderList(object,orderList);
        QList<ProductType*>ptList;
        for (int i =0;i<ProductList.size();i++) {
            QList<ProductType*> ProductTypeList = getProductTypeByProName(ProductList[i]->getProductName());
            for(int j=0;j<ProductTypeList.size();j++){
                ProductType* type = new ProductType(*ProductTypeList[j]);
                ptList.append(type);
            }
        }
        ObjectToJson::integrateProductTypeList(object,ptList);
        ObjectToJson::addSignal(object,QString::number(initAll));
        QByteArray byteArray = ObjectToJson::changeJson(object);
        //qDebug()<<"发送的次数在此显示";
        client = new Client(*clientList[0]);
        emit sglSendByteArray(byteArray,socketDiscriptor);
        setNotification(3,clientList[0]->getClientName()+"传输成功");
    }
    else if(signal==QString::number(updateOrder)){
        //qDebug()<<"接收到传输信号";
        QList<Client*>clientList = ObjectToJson::parseClient(message);
        QJsonObject object;
        QList<Order*>orderList = ObjectToJson::parseOrder(message);
        Order* order;
        bool flag =true;
        //qDebug()<<"钱数为"<<orderList[0]->getOrderCost()<<orderList[0]->getOrderCost().toFloat();
        if(orderList.size()!=0&&orderList[0]->getOrderCost().toFloat()<0){
            flag =false;
        }
        foreach(order,orderList){
            if(order->getOrderCheck()!=getOrderListByInfo(order)[0]->getOrderCheck()){
               clientList = getClientLikeList(order->getOrderClient());
               if(clientList.size()!=0)
               {
                   int cClient = clientList[0]->getClientBought()+order->getOrderCost().toFloat();
//                   qDebug()<<cClient;
                   clientList[0]->setClientBought(cClient);
                   updateClient(clientList[0]);
               }
               QList<Product*> productList = getProductLikeList(order->getOrderProductName());
               if(productList.size()!=0)
               {
                   productList[0]->setProductBuyNum(ProductList[0]->getProductBuyNum()+order->getOrderProductNum());
                   productList[0]->setProductNum(ProductList[0]->getProductNum()-order->getOrderProductNum());
                   updateProductByInfo(productList[0]);
               }
            }
            updateHistory(order);
            delete order;
        }
        ObjectToJson::integrateString(object,"","发送成功！");
        if(flag)setNotification(1,clientList[0]->getClientName()+"购买成功");
        else setNotification(3,clientList[0]->getClientName()+"退货成功");
        ObjectToJson::addSignal(object,signal);
        QByteArray byteArray = ObjectToJson::changeJson(object);
        emit sglSendByteArray(byteArray,socketDiscriptor);
        return;
    }
    else if(signal==QString::number(deleteShopping)){
        QList<Client*>clientList = ObjectToJson::parseClient(message);
        QJsonObject object;
        QList<Order*>orderList = ObjectToJson::parseOrder(message);
        Order* order;
        foreach(order,orderList){
            deleteShoppingCart(order);
            delete order;
        }
        setNotification(3,clientList[0]->getClientName()+"购物车清空");
        order = new Order;
        order->setOrderClient(clientList[0]->getClientName());
        order->setOrderClientId(clientList[0]->getClientId());
        order->setOrderHide(-1);
        orderList = getOrderListByInfo(order);
        ObjectToJson::integrateOrderList(object,orderList);
        ObjectToJson::addSignal(object,signal);
        QByteArray byteArray = ObjectToJson::changeJson(object);
        emit sglSendByteArray(byteArray,socketDiscriptor);
        return;
    }
    else if(signal==QString::number(searchProduct)){
        ObjectToJson::parseString(message);
        QJsonObject object;
        QString mess = ObjectToJson::passage;
        QList<Product*> PList = getProductLikeList(mess);
        ObjectToJson::integrateProductList(object,PList);
        ObjectToJson::addSignal(object,signal);
        QByteArray byteArray = ObjectToJson::changeJson(object);
        emit sglSendByteArray(byteArray,socketDiscriptor);
        return;
    }
    else if(signal==QString::number(addOrderList)){
        QList<Client*>clientList = ObjectToJson::parseClient(message);
        QList<Order*>orderList = ObjectToJson::parseOrder(message);
        QJsonObject object;
        Order* order;
        foreach(order,orderList){
            order->setOrderTime(QDateTime::currentDateTime());
            addOrder(order);
            if(clientList.size()!=0){
                clientList[0]->setClientBought(clientList[0]->getClientBought()+order->getOrderCost().toInt());
                updateClient(clientList[0]);
            }

            QList<Product*> productList = getProductLikeList(order->getOrderProductName());
            if(productList.size()!=0){
                productList[0]->setProductNum(productList[0]->getProductNum()-order->getOrderProductNum());
                productList[0]->setProductBuyNum(productList[0]->getProductBuyNum()+order->getOrderProductNum());
                updateProductByInfo(productList[0]);
            }
            delete order;
        }
        if(orderList[0]->getOrderCheck()==1){
            setNotification(1,clientList[0]->getClientName()+"购买成功");
            ObjectToJson::integrateString(object,"","购买成功");
        }
        else
        ObjectToJson::integrateString(object,"","添加成功");
        ObjectToJson::addSignal(object,signal);
        QByteArray byteArray = ObjectToJson::changeJson(object);
        emit sglSendByteArray(byteArray,socketDiscriptor);
        return;
    }
    else if(signal==QString::number(chatRoom)){
        QList<Client*>clientList = ObjectToJson::parseClient(message);
//        qDebug()<<"信息已接受";
        client =new Client(*clientList[0]);
        ObjectToJson::parseString(message);
        Mess = ObjectToJson::passage;
        //emit sglChatRoom(mess,socketDiscriptor);
        for(int i=0;i<ChatRooms.size();i++)
        {
//            qDebug()<<ChatRooms[i]->sockeDiscriptor;
            if(ChatRooms[i]->sockeDiscriptor==socketDiscriptor){
                ChatRooms[i]->ChatMessageRecived(Mess);break;
            }
        }
    }
    else if(signal==QString::number(searchProductType)){
        QList<Client*>clientList = ObjectToJson::parseClient(message);
        QList<Product*>productList = ObjectToJson::parseProduct(message);
        QList<ProductType*>productTypeList = getProductTypeByProName(productList[0]->getProductName());
        QJsonObject object;
        ObjectToJson::integrateProductTypeList(object,productTypeList);
        ObjectToJson::addSignal(object,signal);
        QByteArray byteArray = ObjectToJson::changeJson(object);
        emit sglSendByteArray(byteArray,socketDiscriptor);
        return;
    }
    else if(signal==QString::number(clientUpdate)){
        QList<Client*>clientList = ObjectToJson::parseClient(message);
        if(clientList.size()!=0){
            updateClient(clientList[0]);
        }
        QJsonObject object;
        ObjectToJson::integrateString(object,"","修改成功");
        ObjectToJson::addSignal(object,signal);
        QByteArray byteArray = ObjectToJson::changeJson(object);
        emit sglSendByteArray(byteArray,socketDiscriptor); 
        return;
    }
    else if(signal==QString::number(login)){
        QList<Client*>clientList = ObjectToJson::parseClient(message);
        if(clientList.size()!=0){
            Client * client = getClientByNameAndPwd(clientList[0]->getClientName(),clientList[0]->getClientPwd());
            if(client==NULL){
                QJsonObject object;
                ObjectToJson::integrateString(object,"","查找失败!");
                ObjectToJson::addSignal(object,signal);
                QByteArray byteArray = ObjectToJson::changeJson(object);
                emit sglSendByteArray(byteArray,socketDiscriptor);
            }
            else{
                QJsonObject object;
                clientList.clear();clientList.append(client);
                ObjectToJson::integrateString(object,"","登录成功!");
                ObjectToJson::addSignal(object,signal);
                ObjectToJson::integrateClientList(object,clientList);
                QByteArray byteArray = ObjectToJson::changeJson(object);
                emit sglSendByteArray(byteArray,socketDiscriptor);
            }
        }
        return;
    }
    else if(signal==QString::number(signin)){
        QList<Client*>clientList = ObjectToJson::parseClient(message);
        if(clientList.size()!=0){
              clientList[0]->setClientSignTime(QDateTime::currentDateTime());
              clientList[0]->setClientBought(0);
              InsertClient(clientList[0]);
              QJsonObject object;
              ObjectToJson::integrateClientList(object,clientList);
              ObjectToJson::integrateString(object,"","注册成功!");
              ObjectToJson::addSignal(object,signal);
              QByteArray byteArray = ObjectToJson::changeJson(object);
              emit sglSendByteArray(byteArray,socketDiscriptor);
        }
        return;
    }
    bool flag = true;
    for (int i=0;i<socketDiscriptorList.size();i++) {
        if(socketDiscriptorList[i]==socketDiscriptor){
            flag = false;break;
        }
    }
    if(flag){
        socketDiscriptorList.append(socketDiscriptor);
        bool flag1 = true;
        for (int i =0;i<ChatRoomItems.size();i++) {
            if(ChatRoomItems[i]->client->getClientId()==client->getClientId())
            {
                ChatRoomItems[i]->setSockeDiscriptor(socketDiscriptor);
                ChatRooms[i]->setSockeDiscriptor(socketDiscriptor);
                flag1=false;break;
            }
        }
        if(flag1)
        {
            emit addChatRoom1(client,socketDiscriptor);
            for(int i=0;i<ChatRooms.size();i++)
            {
                if(ChatRooms[i]->sockeDiscriptor==socketDiscriptor){
                    if((Mess!="")||(Mess.isNull()!=true))
                        {
                        ChatRooms[i]->ChatMessageRecived(Mess);break;
                    }
                }
            }
        }

    }

}

void AllMain::initChartData()
{
      QList<Order*> orderList = getOrderList();
//      qDebug()<<"orderList的大小"<<orderList.size();
      Charts->initData(orderList);
}

void AllMain::initall()
{
    server = new TcpServer(this,8020);
    this->setWindowFlag(Qt::FramelessWindowHint);
    searchForm = new SearchForm(ui->tabWidgetFuc);
    searchForm1 = new SearchForm(ui->tabWidget);
    searchForm->installEventFilter(this);
    searchForm->setMouseTracking(true);
    searchForm1->installEventFilter(this);
    searchForm1->setMouseTracking(true);
    ui->line_Search2->installEventFilter(this);
    ui->line_Search2->setMouseTracking(true);
    ui->line_Search3->installEventFilter(this);
    ui->line_Search3->setMouseTracking(true);
    ui->line_Search4->installEventFilter(this);
    ui->line_Search4->setMouseTracking(true);
    searchForm->hide();
    searchForm1->hide();
    QHBoxLayout * Layout = new QHBoxLayout();
    ui->ChatRoom->setLayout(Layout);
    //ui->ChatRoom->setStyleSheet("QTabBar::tab{background:white;border-bottom: 3px solid rgb(255,255,255);padding-left:5px;padding-right:5px;width: 0px;height:0px;}");
    ui->tabWidgetFuc->setStyleSheet("QTabBar::tab{background:white;border-bottom: 3px solid rgb(255,255,255);padding-left:5px;padding-right:5px;width: 0px;height:0px;}");
    setTabName();
    setAddorDelBtn();
    initOnSaleList();
    initCharts();
    initChartData();
//    addChatRoom(1111111,nullptr);
}

void AllMain::setSelectOnsale(QList<Product*>List)
{
    ui->CommodityselectList_4->clear();
    onSaleItemList.clear();
    for(int i=0 ; i<List.size();i++)
    {
        onSaleItem* Listitem = new onSaleItem();
        QListWidgetItem* item =new QListWidgetItem(ui->CommodityselectList_4);
        Listitem->setNum(List[i]->getProductId());
        Listitem->setPicture(List[i]->getProductImage());
        Listitem->setCommondityName(List[i]->getProductName());
        Listitem->setCommondityTimer(QString::number(List[i]->getProductPrice()));
        Listitem->productNum = List[i]->getProductNum();
        delete Listitem->delWidget;
        Listitem->delWidget=NULL;
        ui->CommodityselectList_4->setItemWidget(item,Listitem);
        onSaleItemList.append(Listitem);
        connect(Listitem,&onSaleItem::getinfo,[=](int num,QString pic,int id,QString name,QString cost)
        {
            ui->onsaleBtn->setStyleSheet("QWidget{border-image:url("+pic+");}");
            ui->CommodityName->setText(name);
            ui->Commoditycost->setText(cost);
            productNum=num;
            onsaleCommodityId = id;
            onSalePic = new QString(pic);
        });
    }
}

void AllMain::addOnSaleItem()
{
   QListWidgetItem * item = new QListWidgetItem(ui->CommodityselectList_5);
   onSaleItem* Listitem = new onSaleItem();
   Listitem->setNum(++onSaleNum);
   Listitem->setPicture(*onSalePic);
   Listitem->setCommondityName(ui->CommodityName->text());
   Listitem->setCommondityTimer(ui->Commoditycost->text());
   QWidget* onSaleWidget = new QWidget(Listitem);
   QHBoxLayout* Layout = new QHBoxLayout();
   int Width = Listitem->width();
   QLabel* myLabel = new QLabel();
   myLabel->setText(QString::number(ui->comboBox->currentText().toInt()*0.1));
   Layout->addWidget(myLabel);
   onSaleWidget->setLayout(Layout);
   onSaleWidget->setGeometry(Width-108,20,41,41);
   Listitem->id = onsaleCommodityId;
   ui->CommodityselectList_5->setItemWidget(item,Listitem);
   connect(Listitem,&onSaleItem::CloseSignal,[=](int id,Product*product)
   {
       int i=0;
       for(; i < onSaledItemList.size();i++)
           if(onSaledItemList[i]->num==id)break;
       //qDebug()<<onSaledItemList[i]->num<<id<<i;
       ui->CommodityselectList_5->takeItem(i);
       onSaledItemList.removeAt(i);
       product->setProductNum(-1);
       updateProductByInfo(product);


   });
   onSaledItemList.append(Listitem);
}

void AllMain::initOnSaleList()
{
   ui->CommodityselectList_5->clear();
   onSaledItemList.clear();
   Product* product1 = new Product();
   product1->setProductDiscount(1);
   QList<Product*>PList = getProductListByInfo(product1);
   for(int i=0;i<PList.size();i++)
   {
       QListWidgetItem * item = new QListWidgetItem(ui->CommodityselectList_5);
       onSaleItem* Listitem = new onSaleItem();
       Listitem->setNum(++onSaleNum);
       Listitem->setPicture(PList[i]->getProductImage());
       Listitem->setCommondityName(PList[i]->getProductName());
       Listitem->setCommondityTimer(QString::number(PList[i]->getProductPrice()));
       QWidget* onSaleWidget = new QWidget(Listitem);
       QHBoxLayout* Layout = new QHBoxLayout();
       int Width = Listitem->width();
       QLabel* myLabel = new QLabel();
       myLabel->setText(QString::number(PList[i]->getProductDiscount()));
       Layout->addWidget(myLabel);
       onSaleWidget->setLayout(Layout);
       onSaleWidget->setGeometry(Width-108,20,41,41);
       Listitem->id = PList[i]->getProductId();
       ui->CommodityselectList_5->setItemWidget(item,Listitem);
       connect(Listitem,&onSaleItem::CloseSignal,[=](int id,Product*product)
       {

           int i=0;
           for(; i < onSaledItemList.size();i++)
               if(onSaledItemList[i]->num==id)break;
           //qDebug()<<onSaledItemList[i]->num<<id<<i;
           ui->CommodityselectList_5->takeItem(i);
           onSaledItemList.removeAt(i);
           product->setProductNum(-1);
//           qDebug()<<product->getProductDiscount()<<product->getProductName()
//                  <<product->getProductId();
           updateProductByInfo(product);

       });
       onSaledItemList.append(Listitem);
   }

}

QList<Client *> AllMain::getClientList()
{
    ClientList.clear();
    struct soap select_soap;
    soap_init(&select_soap);
    soap_set_mode(&select_soap,SOAP_C_UTFSTRING);
    lkf2__getClientList res;
    lkf2__getClientListResponse rep;
    int result = soap_call___lkf1__getClientList(&select_soap,NULL,NULL,&res,rep);
    //qDebug()<<result;
    if(!result)
    {
        std::vector<lkf2__client*> clientList = rep.return_;
        for(int i=0;i<(int)clientList.size();i++)
        {
            Client* client = transObjects::transClient(clientList[i]);
            ClientList.append(client);
        }
        //qDebug()<<ClientList.size();
        for(int i=0;i<ClientList.size();i++)
        {
//            qDebug()<<ClientList[i]->getClientEmail();
        }
    }
    return ClientList;
}

Client *AllMain::getClientByNameAndPwd(QString name, QString pwd)
{
      struct soap select_soap;
      soap_init(&select_soap);
      soap_set_mode(&select_soap,SOAP_C_UTFSTRING);
      lkf2__getClientByNameAndPwd res;
      lkf2__getClientByNameAndPwdResponse rep;
      res.arg0 = StringTrans::QString2string(name);
      res.arg1 = StringTrans::QString2string(pwd);
      int result = soap_call___lkf1__getClientByNameAndPwd(&select_soap,NULL,NULL,&res,rep);
      if(!result&&rep.return_!=NULL)
      {
          lkf2__client* javaclient = rep.return_;
          Client * client = transObjects::transClient(javaclient);
          //qDebug()<<client->getClientName()<<client->getClientPwd();
          return client;
      }
      else
      return NULL;
}

void AllMain::InsertClient(Client *client)
{
    struct soap add_soap;
    soap_init(&add_soap);
    soap_set_mode(&add_soap,SOAP_C_UTFSTRING);

    lkf2__InsertClient res;
    lkf2__InsertClientResponse rep;
    res.arg0 = transObjects::retransClient(client);
    int result  = soap_call___lkf1__InsertClient(&add_soap,NULL,NULL,&res,rep);
    if(!result)
    {
//        qDebug()<<"插入成功";
    }
}

void AllMain::deleteClientByNameAndPwd(QString name, QString pwd)
{
    struct soap delete_soap;
    soap_init(&delete_soap);
    soap_set_mode(&delete_soap,SOAP_C_UTFSTRING);

    lkf2__deleteClientByNameAndPwd res;
    lkf2__deleteClientByNameAndPwdResponse rep;
    res.arg0 = StringTrans::QString2string(name);
    res.arg1 = StringTrans::QString2string(pwd);
    int result = soap_call___lkf1__deleteClientByNameAndPwd(&delete_soap,NULL,NULL,&res,rep);
    if(!result){
//        qDebug()<<"删除成功";
    }
}

void AllMain::updateClient(Client *client)
{
    struct soap update_soap;
    soap_init(&update_soap);
    soap_set_mode(&update_soap,SOAP_C_UTFSTRING);
    lkf2__updateClient res;
    lkf2__updateClientResponse rep;
    lkf2__client * javaclient = transObjects::retransClient(client);
    res.arg0 = javaclient;
    int  result = soap_call___lkf1__updateClient(&update_soap,NULL,NULL,&res,rep);
//    qDebug()<<result;
    if(!result){

//        qDebug()<<"更新成功1111";
    }
}

QList<Client *> AllMain::getClientLikeList(QString mess)
{
    ClientList.clear();
    struct soap select_soap;
    soap_init(&select_soap);
    soap_set_mode(&select_soap,SOAP_C_UTFSTRING);
    lkf2__getClientLikeList res;
    lkf2__getClientLikeListResponse rep;
    res.arg0 = (StringTrans::QString2string(mess));
    int result = soap_call___lkf1__getClientLikeList(&select_soap,NULL,NULL,&res,rep);
    if(!result)
    {
//        qDebug()<<"查询成功";
        std::vector<lkf2__client*> clientList = rep.return_;
        for(int i=0 ;i < (int)clientList.size();i++ )
        {
            Client* client = transObjects::transClient(clientList[i]);
            ClientList.append(client);
//            qDebug()<<client->getClientName();
        }
    }
    return ClientList;
}

QList<Order *> AllMain::getOrderList()
{
    OrderList.clear();
    struct soap select_soap;
    soap_init(&select_soap);
    soap_set_mode(&select_soap,SOAP_C_UTFSTRING);
    lkf2__getOrderList res;
    lkf2__getOrderListResponse rep;
    int result = soap_call___lkf1__getOrderList(&select_soap,NULL,NULL,&res,rep);
//    qDebug()<<result;
    if(!result)
    {
        std::vector<lkf2__order*> orderList = rep.return_;
        for(int i=0;i<(int)orderList.size();i++)
        {
            Order* order = transObjects::transOrder(orderList[i]);
            OrderList.append(order);
        }
//        qDebug()<<OrderList.size();
        for(int i=0;i<OrderList.size();i++)
        {
//            qDebug()<<OrderList[i]->getOrderProductName();
//            qDebug()<<OrderList[i]->getOrderCost();
//            qDebug()<<OrderList[i]->getOrderTime();
        }
    }
    return OrderList;
}

QList<Order *> AllMain::getOrderListByInfo(Order *order)
{
    OrderList.clear();
    struct soap select_soap;
    soap_init(&select_soap);
    soap_set_mode(&select_soap,SOAP_C_UTFSTRING);
    lkf2__getOrderListByInfo res;
    lkf2__getOrderListByInfoResponse rep;
    res.arg0  = transObjects::retransOrder(order);
    int result = soap_call___lkf1__getOrderListByInfo(&select_soap,NULL,NULL,&res,rep);
//    qDebug()<<result;
    if(!result)
    {
        std::vector<lkf2__order*> orderList = rep.return_;
//        qDebug()<<orderList.size();
        for(int i=0;i<(int)orderList.size();i++)
        {
            Order* order = transObjects::transOrder(orderList[i]);
            OrderList.append(order);
        }
        qDebug() << OrderList.size();
        for(int i=0;i<OrderList.size();i++)
        {
//            qDebug() << OrderList[i]->getOrderProductName();
        }
    }
    return OrderList;
}

void AllMain::addOrder(Order *order)
{
    struct soap add_soap;
    soap_init(&add_soap);
    soap_set_mode(&add_soap,SOAP_C_UTFSTRING);

    lkf2__addOrder res;
    lkf2__addOrderResponse rep;
    res.arg0 = transObjects::retransOrder(order);
    int result  = soap_call___lkf1__addOrder(&add_soap,NULL,NULL,&res,rep);
    if(!result)
    {
//        qDebug()<<"插入成功";
    }
}

QList<Order *> AllMain::getOrderLikeList(QString mess)
{
    OrderList.clear();
    struct soap select_soap;
    soap_init(&select_soap);
    soap_set_mode(&select_soap,SOAP_C_UTFSTRING);
    lkf2__getOrderLikeList res;
    lkf2__getOrderLikeListResponse rep;
    res.arg0 = (StringTrans::QString2string(mess));
    int result = soap_call___lkf1__getOrderLikeList(&select_soap,NULL,NULL,&res,rep);
    if(!result)
    {
//        qDebug()<<"查询成功";
        std::vector<lkf2__order*> orderList = rep.return_;
        for(int i=0 ;i < (int)orderList.size();i++ )
        {
            Order* order = transObjects::transOrder(orderList[i]);
            OrderList.append(order);
//            qDebug()<<order->getOrderId();
        }
    }
    return OrderList;
}

QList<Order *> AllMain::getOrderListHistory()
{
    OrderList.clear();
    struct soap select_soap;
    soap_init(&select_soap);
    soap_set_mode(&select_soap,SOAP_C_UTFSTRING);
    lkf2__getOrderList res;
    lkf2__getOrderListResponse rep;
    int result = soap_call___lkf1__getOrderList(&select_soap,NULL,NULL,&res,rep);
//    qDebug()<<result;
    if(!result)
    {
        std::vector<lkf2__order*> orderList = rep.return_;
        for(int i=0;i<(int)orderList.size();i++)
        {
            Order* order = transObjects::transOrder(orderList[i]);
            OrderList.append(order);
        }
        qDebug()<<OrderList.size();
        for(int i=0;i<OrderList.size();i++)
        {
//            qDebug()<<OrderList[i]->getOrderProductName();
//            qDebug()<<OrderList[i]->getOrderCost();
//            qDebug()<<OrderList[i]->getOrderTime();
        }
    }
    return OrderList;
}

void AllMain::updateHistory(Order *order)
{
    struct soap update_soap;
    soap_init(&update_soap);
    soap_set_mode(&update_soap,SOAP_C_UTFSTRING);
    lkf2__updateHistory res;
    lkf2__updateHistoryResponse rep;
    lkf2__order * javaorder = transObjects::retransOrder(order);
    res.arg0 = javaorder;
    int  result = soap_call___lkf1__updateHistory(&update_soap,NULL,NULL,&res,rep);
//    qDebug()<<result;
    if(!result){
        qDebug()<<"更新成功";
    }
}

void AllMain::deleteShoppingCart(Order *order)
{
    struct soap delete_soap;
    soap_init(&delete_soap);
    soap_set_mode(&delete_soap,SOAP_C_UTFSTRING);

    lkf2__deleteShoppingCart res;
    lkf2__deleteShoppingCartResponse rep;
    res.arg0 = transObjects::retransOrder(order);
    int result = soap_call___lkf1__deleteShoppingCart(&delete_soap,NULL,NULL,&res,rep);
    if(!result)
    {
//        qDebug()<<"删除成功";
    }
}

QList<Product *> AllMain::getProductList(int choose)
{
    ProductList.clear();
    struct soap select_soap;
    soap_init(&select_soap);
    soap_set_mode(&select_soap,SOAP_C_UTFSTRING);
    lkf2__getProductList res;
    lkf2__getProductListResponse rep;
    res.arg0 = choose;
    int result = soap_call___lkf1__getProductList(&select_soap,NULL,NULL,&res,rep);
//    qDebug()<<result;
    if(!result)
    {
        std::vector<lkf2__product*> productList = rep.return_;
        for(int i=0;i<(int)productList.size();i++)
        {
            Product* product = transObjects::transProduct(productList[i]);
            ProductList.append(product);
        }
//        qDebug()<<ProductList.size();
        for(int i=0;i<ProductList.size();i++)
        {
//            qDebug()<<ProductList[i]->getProductId();
        }
    }
    return ProductList;
}

QList<Product *> AllMain::getProductListByInfo(Product *product)
{
    ProductList.clear();
    struct soap select_soap;
    soap_init(&select_soap);
    soap_set_mode(&select_soap,SOAP_C_UTFSTRING);
    lkf2__getProductListByInfo res;
    lkf2__getProductListByInfoResponse rep;
    res.arg0  = transObjects::retransProduct(product);
    int result = soap_call___lkf1__getProductListByInfo(&select_soap,NULL,NULL,&res,rep);
//    qDebug()<<result;
    if(!result)
    {
        std::vector<lkf2__product*> productList = rep.return_;
//        qDebug()<<productList.size();
        for(int i=0;i<(int)productList.size();i++)
        {
            Product* product = transObjects::transProduct(productList[i]);
            ProductList.append(product);
        }
        qDebug() << ProductList.size();
        for(int i=0;i<ProductList.size();i++)
        {
//            qDebug() << ProductList[i]->getProductName();
        }
    }
    return ProductList;
}

void AllMain::addProduct(Product *product)
{
    struct soap add_soap;
    soap_init(&add_soap);
    soap_set_mode(&add_soap,SOAP_C_UTFSTRING);

    lkf2__addProduct res;
    lkf2__addProductResponse rep;
    res.arg0 = transObjects::retransProduct(product);
    int result  = soap_call___lkf1__addProduct(&add_soap,NULL,NULL,&res,rep);
    if(!result)
    {
        qDebug()<<"插入成功";
    }
}

void AllMain::deleteProductByInfo(Product *product)
{
    struct soap delete_soap;
    soap_init(&delete_soap);
    soap_set_mode(&delete_soap,SOAP_C_UTFSTRING);

    lkf2__deleteProductByInfo res;
    lkf2__deleteProductByInfoResponse rep;
    res.arg0 = transObjects::retransProduct(product);
    int result = soap_call___lkf1__deleteProductByInfo(&delete_soap,NULL,NULL,&res,rep);
    if(!result)
        qDebug()<<"删除成功";
}

void AllMain::updateProductByInfo(Product *product)
{
    struct soap update_soap;
    soap_init(&update_soap);
    soap_set_mode(&update_soap,SOAP_C_UTFSTRING);
    lkf2__updateProductByInfo res;
    lkf2__updateProductByInfoResponse rep;
    lkf2__product * javaproduct = transObjects::retransProduct(product);
    res.arg0 = javaproduct;
    int  result = soap_call___lkf1__updateProductByInfo(&update_soap,NULL,NULL,&res,rep);
//    qDebug()<<result;
    if(!result)qDebug()<<"更新成功2222";
}

QList<Product *> AllMain::getProductLikeList(QString mess)
{
    ProductList.clear();
    struct soap select_soap;
    soap_init(&select_soap);
    soap_set_mode(&select_soap,SOAP_C_UTFSTRING);
    lkf2__getProductLikeList res;
    lkf2__getProductLikeListResponse rep;
    res.arg0 = (StringTrans::QString2string(mess));
    int result = soap_call___lkf1__getProductLikeList(&select_soap,NULL,NULL,&res,rep);
    if(!result)
    {
        qDebug()<<"查询成功";
        std::vector<lkf2__product*> productList = rep.return_;
        for(int i=0 ;i < (int)productList.size();i++ )
        {
            Product* Product = transObjects::transProduct(productList[i]);
            ProductList.append(Product);
//            qDebug()<<Product->getProductId();
        }
    }
    return ProductList;
}

QList<ProductType *> AllMain::getProductTypeByProName(QString name)
{
    ProductTypeList.clear();
    struct soap select_soap;
    soap_init(&select_soap);
    soap_set_mode(&select_soap,SOAP_C_UTFSTRING);
    lkf2__getProductTypeByProName res;
    lkf2__getProductTypeByProNameResponse rep;
    res.arg0 = StringTrans::QString2string(name);
    int result = soap_call___lkf1__getProductTypeByProName(&select_soap,NULL,NULL,&res,rep);
//    qDebug()<<result;
    if(!result)
    {
        std::vector<lkf2__productType*> productTypeList = rep.return_;
        for(int i=0;i<(int)productTypeList.size();i++)
        {
            ProductType* productType = transObjects::transProductType(productTypeList[i]);
            ProductTypeList.append(productType);
        }
//        qDebug()<<ProductTypeList.size();
        for(int i=0;i<ProductTypeList.size();i++)
        {
//            qDebug()<<ProductTypeList[i]->getTypeName();
        }
    }
    return ProductTypeList;
}

void AllMain::addProductType(ProductType *type)
{
    struct soap add_soap;
    soap_init(&add_soap);
    soap_set_mode(&add_soap,SOAP_C_UTFSTRING);
    lkf2__addProductType res;
    lkf2__addProductTypeResponse rep;
    res.arg0 = transObjects::retransProductType(type);
    int result  = soap_call___lkf1__addProductType(&add_soap,NULL,NULL,&res,rep);
    if(!result)
    {
//        qDebug()<<"插入成功";
    }
}

void AllMain::deleteProductTypeByName(QString name)
{
    struct soap delete_soap;
    soap_init(&delete_soap);
    soap_set_mode(&delete_soap,SOAP_C_UTFSTRING);
    lkf2__deleteProductTypeByName res;
    lkf2__deleteProductTypeByNameResponse rep;
    res.arg0 = StringTrans::QString2string(name);
    int result = soap_call___lkf1__deleteProductTypeByName(&delete_soap,NULL,NULL,&res,rep);
    if(!result)
    {
//        qDebug()<<"删除成功";
    }
}



bool AllMain::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->line_Search2)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {

            int x = ui->line_Search2->x();
            int y = ui->line_Search2->y();
//            qDebug()<<x<<y;
            int hight = ui->line_Search2->height();
            searchForm->setGeometry(x,y+hight+33,searchForm->width(),searchForm->height());
//            QList<Product*>List = getProductList(1);
//            emit sglsearch(List);
            searchForm->show();
            return true;
        }
        else {
            return false;
        }

    }
    else if (watched == searchForm)
    {
        //当鼠标离开时候，界面隐藏
        if(event->type() == QEvent::Leave)
        {
            searchForm->hide();
            return true;
        }
        else {
            return false;
        }

    }
    else if (watched == searchForm1)
    {
        //当鼠标离开时候，界面隐藏
        if(event->type() == QEvent::Leave)
        {
            searchForm1->hide();
            return true;
        }
        else {
            return false;
        }

    }
    else if(watched == ui->line_Search3)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {

            int x = ui->line_Search3->x();
            int y = ui->line_Search3->y();
//            qDebug()<<x<<y;
            int hight = ui->line_Search3->height();
            searchForm->setGeometry(x,y+hight+35,searchForm->width(),searchForm->height());
            searchForm->show();
            return true;
        }
        else {
            return false;
        }
    }
    else if(watched == ui->line_Search4)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {

            int x = ui->line_Search4->x();
            int y = ui->line_Search4->y();
            int hight = ui->line_Search4->height();
            searchForm1->setGeometry(x,y+hight+40,searchForm1->width(),searchForm1->height());
            searchForm1->show();
            return true;
        }
        else {
            return false;
        }
    }
    return QWidget::eventFilter(watched,event);
}

void AllMain::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter_mainback(this);
    painter_mainback.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/mianwindows/images/mainback.png"));
    ui->pushButton_people->setMask(QRegion(0,0,28,28,QRegion::Ellipse));
}

void AllMain::mousePressEvent(QMouseEvent *event)
{
    //获取title widget 的高度，这里固定为60px
    int titleHeight = ui->title_Widget->height();
    if(event->y() <titleHeight)
    {
        last = event->globalPos(); //获取到按压的位置
    }
}

void AllMain::mouseMoveEvent(QMouseEvent *event)
{
    int titleHeight = ui->title_Widget->height();
    if(event->y() <titleHeight)
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        last = event->globalPos();
        this->move(this->x()+dx,this->y()+dy);
    }

}

void AllMain::mouseReleaseEvent(QMouseEvent *event)
{
    int titleHeight = ui->title_Widget->height();
    if(event->y() <titleHeight)
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        this->move(this->x()+dx,this->y()+dy);
    }
}

void AllMain::initCharts()
{
    Charts = new analysisCharts();
    ui->tabWidget->addTab(Charts,"数据分析");
}

void AllMain::setList1()
{
    ui->listT1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listT1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    AddorDelCommodity = new QListWidgetItem(ui->listT1);
    AddorDelCommodity->setIcon(QIcon("./images/022-货物查询.svg"));
    AddorDelCommodity->setText("增删货物");
    Chat = new QListWidgetItem(ui->listT1);
    Chat->setIcon(QIcon("./images/客服消息.svg"));
    Chat->setText("用户反馈");
    Activity = new QListWidgetItem(ui->listT1);
    Activity->setIcon(QIcon("./images/活动专区.svg"));
    Activity->setText("活动设置");
}

void AllMain::setList2()
{
    ui->listT2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listT2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCharts = new QListWidgetItem(ui->listT2);
    setCharts->setIcon(QIcon("./images/17-图表板.svg"));
    setCharts->setText("数据分析");
}

void AllMain::setAddorDelBtn()
{
    ui->widNewMus->setGeometry(370,30,348,32);
    ui->widNewMus->setStyleSheet("QWidget#widNewMus{background:rgb(255,255,255);border:1px solid rgb(187,187,187);border-radius:16px;}");
    ui->ptnNew->setParent(ui->widNewMus);
    ui->ptnNew->setGeometry(0,1,115,30);
    ui->ptnNew->move(1,1);
    ui->ptnNew->setCheckable(true);
    ui->ptnNew2->setParent(ui->widNewMus);
    ui->ptnNew2->setGeometry(ui->ptnNew->width()+2,1,115,30);
    ui->ptnNew2->move(ui->ptnNew->width()+1,1);
    ui->ptnNew2->setCheckable(true);
    ui->ptnNew3->setParent(ui->widNewMus);
    ui->ptnNew3->setGeometry(ui->ptnNew2->width()*2+4,1,115,30);
    ui->ptnNew3->move(ui->ptnNew->width()*2+2,1);
    ui->ptnNew3->setCheckable(true);
    ui->ptnNew->setStyleSheet("QPushButton{color:rgb(55,55,55);border:0px;background:rgb(255,255,255);border-radius:14px;}"
                            "QPushButton:hover{border:0px;background:rgb(244,244,244);border-radius:14px;}"
                            "QPushButton:checked{color:rgb(255,255,255);border:0px;background:rgb(187,187,187);border-radius:14px;}");
    ui->ptnNew2->setStyleSheet("QPushButton{color:rgb(55,55,55);border:0px;background:rgb(255,255,255);border-radius:14px;}"
                            "QPushButton:hover{border:0px;background:rgb(244,244,244);border-radius:14px;}"
                            "QPushButton:checked{color:rgb(255,255,255);border:0px;background:rgb(187,187,187);border-radius:14px;}");
    ui->ptnNew3->setStyleSheet("QPushButton{color:rgb(55,55,55);border:0px;background:rgb(255,255,255);border-radius:14px;}"
                            "QPushButton:hover{border:0px;background:rgb(244,244,244);border-radius:14px;}"
                            "QPushButton:checked{color:rgb(255,255,255);border:0px;background:rgb(187,187,187);border-radius:14px;}");
    QButtonGroup * btnGroup = new QButtonGroup(this);
    btnGroup->addButton(ui->ptnNew,0);
    btnGroup->addButton(ui->ptnNew2,1);
    btnGroup->addButton(ui->ptnNew3,2);
    btnGroup->setExclusive(true);
    btnGroup->button(0)->setChecked(true);
    connect(btnGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),[=](int i){
       ui->tabWidgetFuc->setCurrentIndex(i);
    });
}

void AllMain::selectCommodity(QList<Product*>List)
{
    selectItems.clear();
    ui->CommodityselectList->clear();
    for(int i=0;i<List.size();i++)
    {
        NewSelectItem* item = new NewSelectItem();
        QListWidgetItem * Listitem = new QListWidgetItem(ui->CommodityselectList);
        item->setNum(List[i]->getProductId());
        item->setPicture(List[i]->getProductImage());
        item->setCommondityName(List[i]->getProductName());
        item->setLogPic();
        item->setCommondityAuthor(QString::number(List[i]->getProductNum()));
        item->setCommondityAlbum(QString::number(List[i]->getProductBuyNum()));
        item->setCommondityTimer(QString::number(List[i]->getProductPrice()));
        item->product = new Product(*List[i]);
        ui->CommodityselectList->setItemWidget(Listitem,item);
        connect(item,&NewSelectItem::ChangetoModified,[=](){
            this->setChangePage();
            ui->listWidget->clear();
            ui->NumEdit->setText(QString::number(item->product->getProductId()));
            ui->NameEdit->setText(item->product->getProductName());
            ui->PhoneNumEdit->setText(QString::number(item->product->getProductPrice()));
            ui->PasswordEdit->setText(QString::number(item->product->getProductNum()));
            QList<ProductType*>typeList =getProductTypeByProName(item->product->getProductName());
            for(int i=0;i<typeList.size();i++)
            {
                QListWidgetItem* Item = new QListWidgetItem(ui->listWidget);
                Item->setText(typeList[i]->getTypeName());
                ui->listWidget->addItem(Item);

            }

            ui->picShow->setStyleSheet("QPushButton{border-image:url("+item->product->getProductImage()+");}");
            picShow = item->product->getProductImage();
        });
        selectItems.append(item);
    }
}

void AllMain::setTabName()
{
    ui->tabWidget->setTabIcon(0,QIcon("./images/022-货物查询.svg"));
    ui->tabWidget->setTabText(0,"货物");
    ui->tabWidget->setTabIcon(1,QIcon("./images/客服消息.svg"));
    ui->tabWidget->setTabText(1,"用户");
    ui->tabWidget->setTabIcon(2,QIcon("./images/活动专区.svg"));
    ui->tabWidget->setTabText(2,"活动");
    ui->tabWidget->setTabIcon(3,QIcon("./images/17-图表板.svg"));
    ui->tabWidget->setTabText(3,"分析");

}





void AllMain::setChangePage()
{
    ui->tabWidgetFuc->setCurrentIndex(0);
}

void AllMain::setDelPage(QList<Product*>List)
{
    DelItems.clear();
    ui->CommodityselectList_3->clear();
    for(int i=0;i<List.size();i++)
    {
        NewSelectItem* item = new NewSelectItem();
        QListWidgetItem * Listitem = new QListWidgetItem(ui->CommodityselectList_3);
        item->setNum(List[i]->getProductId());
        item->setPicture(List[i]->getProductImage());
        item->setCommondityName(List[i]->getProductName());
        item->setLogPic();
        item->setCommondityAuthor(QString::number(List[i]->getProductNum()));
        item->setCommondityAlbum(QString::number(List[i]->getProductBuyNum()));
        item->setCommondityTimer(QString::number(List[i]->getProductPrice()));
        item->num =++DelNum;
        //qDebug()<<num;
        DelItems.append(item);
        ui->CommodityselectList_3->setItemWidget(Listitem,item);
        connect(item,&NewSelectItem::delNewSelectitem,[=](int Num)
        {
//            ui->CommodityselectList_3->takeItem(num);
//            DelItems.pop_back();
            int i=0;
            for(;i<DelItems.size();i++)
            {
                if(DelItems[i]->num==Num)
                    break;
            }
            ui->CommodityselectList_3->takeItem(i);
            DelItems.removeAt(i);
            Product * product = new Product();
            product->setProductId(item->id);
            product->setProductName(item->name);
            deleteProductByInfo(product);
            setNotification(3,"删除成功");
        });
    }

}



void AllMain::addChatRoom(qintptr socketDiscriptor,Client*client1)
{

    ChatRoom * room = new ChatRoom(ui->ChatRoom);
    ChatListItem  * ListWidget = new ChatListItem();
    Client*client = getClientByNameAndPwd(client1->getClientName(),client1->getClientPwd());
    room->setClient(client);
    room->setSockeDiscriptor(socketDiscriptor);
    ListWidget->setClient(client);
    ListWidget->setSockeDiscriptor(socketDiscriptor);
    QListWidgetItem * item = new QListWidgetItem(ui->ChatList);
    ui->ChatRoom->addTab(room,"");
    ui->ChatList->setItemWidget(item,ListWidget);
    ListWidget->num=(++ChatRoomNum);
    connect(ListWidget,&ChatListItem::CloseSignal,[=](int num,qintptr socketD)
    {
        Q_UNUSED(socketD);
        int i=0;
        for (;i< ChatRoomItems.size();i++)
        {
            if(ChatRoomItems[i]->num==num)break;
        }
        //qDebug()<<i<<num<<ChatRoomItems[i]->num;
        ui->ChatRoom->removeTab(i);
        ui->ChatList->takeItem(i);
        ChatRooms.removeAt(i);
        ChatRoomItems.removeAt(i);
        socketDiscriptorList.removeAt(i);
    });
    connect(room,&ChatRoom::sglsendToClient,[=](QString mess,qintptr socketDiscriptor){
        QJsonObject object;
        ObjectToJson::integrateString(object,"",mess);
        ObjectToJson::addSignal(object,QString::number(chatRoom));
        QByteArray byteArray = ObjectToJson::changeJson(object);
        qDebug()<<"发送";
        emit sglSendByteArray(byteArray,socketDiscriptor);
    });
    ChatRooms.append(room);
    ChatRoomItems.append(ListWidget);
    connect(ui->ChatList,&QListWidget::currentRowChanged,[=](int num)
    {
        ui->ChatRoom->setCurrentIndex(num);
    });
    int width = 400;
    //qDebug()<<width;
    int tabCount = ui->ChatRoom->count();
    int tabWidth = width / tabCount;
    ui->ChatRoom->setStyleSheet(QString("QTabBar::tab{width:%1px;}").arg(tabWidth));
}



Client *transObjects::transClient(lkf2__client *javaclient)
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

Order *transObjects::transOrder(lkf2__order *javaorder)
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

Product *transObjects::transProduct(lkf2__product *javaproduct)
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

ProductType* transObjects::transProductType(lkf2__productType *javaproductType)
{
    ProductType * productType = new ProductType();
    productType->setTypeName(StringTrans::string2QString(javaproductType->typeName));

    productType->setTypeId(javaproductType->typeId);

    productType->setTypeProduct(StringTrans::string2QString(javaproductType->typeProduct));

    productType->setTypeProductId(javaproductType->typeProductId);

    return productType;
}

lkf2__client *transObjects::retransClient(Client *client)
{

     int bought =client->getClientBought();
     std::string *email = StringTrans::QString2string(client->getClientEmail());
     int id = client->getClientId();
     std::string *image = StringTrans::QString2string(client->getClientImage());
     std::string * name = StringTrans::QString2string(client->getClientName());
     std::string * phone  =StringTrans::QString2string(client->getClientPhone());
//     if(!phone)qDebug()<<"weikong";

     std::string * pwd = StringTrans::QString2string(client->getClientPwd());
          //qDebug()<<client->getClientPhone()<<client->getClientPwd()<<client->getClientName();
     time_t *time = StringTrans::QDateTime2tTime(client->getClientSignTime());
     lkf2__client * javaclient = new lkf2__client(bought,email,id,image,name,phone,pwd,time);
     return javaclient;
}

lkf2__order *transObjects::retransOrder(Order *order)
{

    int check = order->getOrderCheck();
    std::string * client = StringTrans::QString2string(order->getOrderClient());
    int cid = order->getOrderClientId();
    std::string * cost = StringTrans::QString2string(order->getOrderCost());
//    if(!cost)qDebug()<<"cost是空的";
    int hide = order->getOrderHide();
    int id = order->getOrderId();
    int pid = order->getOrderProductId();
    std::string * Pname = StringTrans::QString2string(order->getOrderProductName());
    int Pnum = order->getOrderProductNum();
    std::string * Pstyle = StringTrans::QString2string(order->getOrderProductStyle());
//    if(!Pstyle)qDebug()<<"Pstyle是空的";
    time_t* time = StringTrans::QDateTime2tTime(order->getOrderTime());
//    if(!time)qDebug()<<"time是空的";
    return new lkf2__order(check,client,cid,cost,
    hide,id,pid,Pname,Pnum,Pstyle,time);
}

lkf2__product *transObjects::retransProduct(Product *product)
{
//    lkf2__product(int buynum,int discount,int pId,std::string *pImage,std::string *pName,
    //int pNum,int pPrice)
      int buynum = product->getProductBuyNum();
      float discount = product->getProductDiscount();
      int pId = product->getProductId();
      std::string * pImage = StringTrans::QString2string(product->getProductImage());
      std::string * pName = StringTrans::QString2string(product->getProductName());
      int pNum = product->getProductNum();
      int pPrice = product->getProductPrice();
      return new lkf2__product(buynum,discount,pId,pImage,pName,pNum,pPrice);
}

lkf2__productType *transObjects::retransProductType(ProductType *productType)
{
     lkf2__productType * javaProductType = new lkf2__productType();
     javaProductType->typeId = productType->getTypeId();
     javaProductType->typeName = StringTrans::QString2string(productType->getTypeName());
     javaProductType->typeProduct =StringTrans::QString2string(productType->getTypeProduct());
     javaProductType->typeProductId = productType->getTypeProductId();
     return javaProductType;
}

transObjects::transObjects()
{

}

void AllMain::on_addSaleBtn_clicked()
{
    if(onSalePic)
    {
        Product * product =new Product;
        product ->setProductId(onsaleCommodityId);
        product ->setProductNum(-1);
        product->setProductDiscount(ui->comboBox->currentText().toInt()*0.1);
        updateProductByInfo(product);
        addOnSaleItem();
        onSalePic = NULL;
        ui->onsaleBtn->setStyleSheet("QPushButton#onsaleBtn");
        ui->CommodityName->setText("货品名称");
        ui->Commoditycost->setText("￥");
        setNotification(1,"打折成功");
        return;
    }
    setNotification(2,"打折失败");
}

void AllMain::on_addSeries_clicked()
{
    if(!ui->ProductSeriesEdit->text().isNull())
    {
        QListWidgetItem * item =new QListWidgetItem(ui->listWidget);
        item->setText(ui->ProductSeriesEdit->text());
        ui->listWidget->addItem(item);
        QString str;
        ui->ProductSeriesEdit->setText(str);
    }
}

void AllMain::on_ptnAdd_clicked()
{
    Product * product = new Product();
    QString str;
    product->setProductId(ui->NumEdit->text().toInt());
    product->setProductName(ui->NameEdit->text());
    product->setProductNum(ui->PasswordEdit->text().toInt());
    product->setProductPrice(ui->PhoneNumEdit->text().toInt());
    if(getProductListByInfo(product).size()==0)
    {
        product->setProductImage(picShow);
        addProduct(product);
        setNotification(1,"添加成功");
        picShow="";
    }
    else
    {
        product->setProductImage(picShow);
        picShow="";
        updateProductByInfo(product);\
        setNotification(1,"修改成功");
    }
    QList<Product*>List = getProductListByInfo(product);
    //qDebug()<<"List的大小为:"<<List.size();
    if(List.size()!=0)
    {

        QList<ProductType*>typeList = getProductTypeByProName(product->getProductName());
        for(int i=0;i<ui->listWidget->count();i++)
        {
            QListWidgetItem *item = ui->listWidget->item(i);
            ProductType * type = new ProductType;
            type->setTypeName(item->text());
//            qDebug()<<item->text();
            type->setTypeProduct(List[0]->getProductName());
            type->setTypeProductId(List[0]->getProductId());
            bool flag=true;
            for(int j =0;j<typeList.size();j++)
            {
//                qDebug()<<typeList.size();
                if(typeList[j]->getTypeName()==type->getTypeName())
                {
                    flag=false;break;
                }
            }
            if(flag)
            addProductType(type);
        }
    }

    ui->NumEdit->setText(str);
    ui->NameEdit->setText(str);
    ui->PasswordEdit->setText(str);
    ui->PhoneNumEdit->setText(str);
    ui->picShow->setStyleSheet("QPushButton#picShow");
    ui->listWidget->clear();
}

void AllMain::on_RefreshBtn_clicked()
{
    initOnSaleList();
}

void AllMain::on_picShow_clicked()
{
    picShow = QFileDialog::getOpenFileName(this,"打开文件","D:/code/Qt/C++project/imagebase");
    ui->picShow->setStyleSheet("QPushButton{border-image:url("+picShow+");}");
    if(picShow==""||picShow.isNull())
        ui->picShow->setStyleSheet("QPushButton#picShow");
}

void AllMain::on_pushButton_title_left_clicked()
{
    if(ui->tabWidget->currentIndex()==0)
    {
        ui->tabWidget->setCurrentIndex(4);
    }
    ui->tabWidget->setCurrentIndex((ui->tabWidget->currentIndex()-1)%4);
}

void AllMain::on_pushButton_title_right_clicked()
{
    ui->tabWidget->setCurrentIndex((ui->tabWidget->currentIndex()+1)%4);
}

void AllMain::setNotification(int color, QString message)
{
//    qDebug()<<"input: "<<message;
    CreateNotification * notice = new CreateNotification(color,message,this);
    notice->setGeometry(0,0,170,50);
    notice->setParent(this);
    notice->move(this->width()*0.5-notice->width()*0.5,-500);
    notice->show();
    QSequentialAnimationGroup * AnimationGroup = new QSequentialAnimationGroup(notice);
    QPropertyAnimation * animation = new QPropertyAnimation(notice,"geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(notice->x(),notice->y(),notice->width(),notice->height()));
    animation->setEndValue(QRect(notice->x(),notice->y()+570,notice->width(),notice->height()));
    animation->setEasingCurve(QEasingCurve::OutQuint);
    QPropertyAnimation * animation1 = new QPropertyAnimation(notice,"geometry");
    animation1->setDuration(800);
    animation1->setStartValue(QRect(notice->x(),notice->y()+570,notice->width(),notice->height()));
    animation1->setEndValue(QRect(notice->x(),notice->y()+100,notice->width(),notice->height()));
    animation1->setEasingCurve(QEasingCurve::OutQuint);
    AnimationGroup->addAnimation(animation);
    AnimationGroup->addPause(500);
    AnimationGroup->addAnimation(animation1);
    AnimationGroup->start();
}
