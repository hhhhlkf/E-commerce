#include "allmain.h"
#include "ui_allmain.h"
#include <winsock2.h>
int Allmain::ShoppingCartNum  = 0;
Allmain::Allmain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Allmain)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    ui->line_Search->installEventFilter(this);
    ui->line_Search->setMouseTracking(true);
    From = new logInForm();
//    From->setAttribute(Qt::WA_TranslucentBackground, true);

//    From->setWindowOpacity(0.3);
    tcpSocket=nullptr;
    From->show();
    connect(From,&logInForm::sendMessage,[=](Client *cClient, TcpSocket *socket){
        //qDebug()<<"my socket3"<<socket;
        initAtBeginng(socket,cClient);
        From->hide();
        this->show();
    });
    initOutLook();
    ui->rightlabel->setText("右键\n试试");
}

void Allmain::initAtBeginng(TcpSocket *socket, Client *cClient)
{
    if(tcpSocket==nullptr){
        setSocket(socket);
        connect(tcpSocket,&TcpSocket::SendAByteArray,[=](QByteArray json)
        {
            //qDebug()<<tcpSocket->socketDescriptor();
            getByteArray(json);
        });
    }
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){
       this->close();
    });
    connect(ui->pushButton_min,&QPushButton::clicked,[=](){
       this->showMinimized();
    });
    Client * client = new Client(*cClient);
//    client->setClientId(3);
//    client->setClientName("吴国梁");
//    client->setClientPwd("1235377434");
//    client->setClientEmail("wgliang@jlu.cn");
//    client->setClientImage("D:/code/Qt/C++project/imagebase/头像男孩.svg");
//    client->setClientPhone("1231252534265");
//    client->setClientBought(300);
//    client->setClientSignTime(QDateTime::currentDateTime());
    ClientList.append(client);
    QJsonObject object;
    object.insert("signal",QString::number(initAll));
    ObjectToJson::integrateClientList(object,ClientList);
    QByteArray array = ObjectToJson::changeJson(object);
    tcpSocket->SendMessageToServer(array);
}

void Allmain::setNotification(int color,QString message)
{
     //qDebug()<<"input: "<<message;
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

void Allmain::initData()
{
    picShow=ClientList[0]->getClientImage();
    if(picShow!=""||!picShow.isNull())
    ui->pushButton_people->setStyleSheet("QPushButton{border-image:url("+picShow+");}");
    ui->pushButton_people->setDisabled(true);
    if(ProductList.size()!=0)
    {
        QList<Product*>ComList;
        QList<Product*>onSaleList;
        ui->listT3->clear();
        for(int i = 0; i < 2; i++)
        {
            for(int j=0;j<4;j++)
            {
                Product * product = new Product(*ProductList[(i*4+j)]);
                ComList.append(product);
            }
            setCommendlistWall(ComList);
            ComList.clear();
        }
        for(int i=0;i<ProductList.size();i++)
        {
            Product * product = new Product(*ProductList[i]);
                onSaleList.append(product);
        }
        if(gallerPrivate[0]==nullptr&&gallerPrivate[1]==nullptr)
        setGallery(onSaleList);
    }
    setInitData(OrderList);
    setHistoryData(OrderList);

    connect(ui->listT1,&QListWidget::currentRowChanged,[=](int num){
         ui->tabWidget->setCurrentIndex(num);
         ui->listT2->setCurrentRow(-1);
    });
    connect(ui->listT2,&QListWidget::currentRowChanged,[=](int num)
    {
            ui->listT1->setCurrentRow(-1);
            ui->tabWidget->setCurrentIndex(num+3);
    });
    connect(ui->ptnChange,&QPushButton::clicked,[=](){
            ChatMessageSend();
    });
    connect(ui->line_Search2,&QLineEdit::textChanged,[=](QString text)
    {
            setselectData(text);
    });
    ui->tabWidget->setCurrentIndex(0);
    ////client的初始化
    if(p_person!=nullptr)
    {
        p_person->setClient(ClientList[0]);
    }
}

void Allmain::initOutLook()
{
    gallerPrivate[0]=nullptr;
    gallerPrivate[1]=nullptr;
    setListT1();
    setListT2();
    settabWidget();
    setPictureWall();
    ui->ChatList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->ChatList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//垂直滚动条
    ui->ChatList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->ChatList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//垂直滚动条
    ui->textEdit->setFocus();
    ui->textEdit->installEventFilter(this);
    ui->tabWidget->setCurrentIndex(0);
//    searchForm = new SearchForm(this); //创建一个新的搜索框
//    searchForm->installEventFilter(this);
//    searchForm->setMouseTracking(true);
//    searchForm->hide();
    ui->tabselectWidget->setTabsClosable(true);

}

void Allmain::connectBuySignaal(Commodity* commodity)
{
    connect(commodity,&Commodity::createOrder,[=](int orderCheck,int productId,QString productName,
            QString producStyle,int buynum,float price){
        Order* order =new Order;
        order->setOrderCost(QString::number(buynum*price,'f',2));
        order->setOrderProductId(productId);
        order->setOrderProductName(productName);
        order->setOrderProductNum(buynum);
        order->setOrderClient(ClientList[0]->getClientName());
        order->setOrderClientId(ClientList[0]->getClientId());
        order->setOrderProductStyle(producStyle);
        order->setOrderHide(-1);
        order->setOrderCheck(orderCheck);
        QJsonObject object;
        ObjectToJson::addSignal(object,QString::number(addOrderList));
        QList<Order*>oList;
        oList.append(order);
        ObjectToJson::integrateOrderList(object,oList);
        ObjectToJson::integrateClientList(object,ClientList);
        QByteArray array = ObjectToJson::changeJson(object);
        tcpSocket->SendMessageToServer(array);
        if(orderCheck==1)
        {
            QListWidgetItem* item =new QListWidgetItem(ui->HistoryList);
            NewCourierItem* nitem = new NewCourierItem();
            nitem->setOrder(order);
            nitem->setcheckBox();
            nitem->number=++ShoppingCartNum;
            for(int i=0;i< ProductList.size();i++)
            {
                if(ProductList[i]->getProductId()==order->getOrderProductId())
                {
                    nitem->setPicture(ProductList[i]->getProductImage());
                }
            }
            ui->HistoryList->setItemWidget(item,nitem);
            HistoryItemList.append(nitem);
            setOrderConnected(1,nitem);
        }
        else{
            QListWidgetItem* item =new QListWidgetItem(ui->ShoppingCartList);
            NewCourierItem* nitem = new NewCourierItem();
            nitem->setOrder(order);
            nitem->setcheckBox();
            nitem->number=++ShoppingCartNum;
            for(int i=0;i< ProductList.size();i++)
            {
                if(ProductList[i]->getProductId()==order->getOrderProductId())
                {
                    nitem->setPicture(ProductList[i]->getProductImage());
                }
            }
            ui->ShoppingCartList->setItemWidget(item,nitem);
            ShoppingCartList.append(nitem);
            setOrderConnected(1,nitem);
        }
        OrderList.append(order);
    });
}



void Allmain::getByteArray(QByteArray json)
{
    QString signal = ObjectToJson::parseSignal(json);
     if(signal==""){
         //qDebug()<<"解析失败";
         return;
     }
     if(signal==QString::number(initAll))
     {
         ProductList.clear();OrderList.clear();
         ProductList = ObjectToJson::parseProduct(json);
         //qDebug()<<ProductList.size();
         OrderList = ObjectToJson::parseOrder(json);
         //qDebug()<<OrderList.size();
         ProductTypeList = ObjectToJson::parseProductType(json);
         //qDebug()<<ProductTypeList.size();
         initData();
     }
    else if(signal==QString::number(updateOrder)){
//         OrderList.clear();
//         OrderList = ObjectToJson::parseOrder(json);
         ObjectToJson::parseString(json);
         //qDebug()<<ObjectToJson::passage;
         setNotification(1,"操作成功");
     }
    else if(signal==QString::number(deleteShopping)){
         OrderList.clear();
         OrderList = ObjectToJson::parseOrder(json);
         setNotification(1,"删除成功");
     }
     else if(signal==QString::number(searchProduct)){
         TemporaryList.clear();
         TemporaryList = ObjectToJson::parseProduct(json);
                 //qDebug()<<TemporaryList.size();
     }
     else if(signal==QString::number(addOrderList)){
         ObjectToJson::parseString(json);
         //qDebug()<<ObjectToJson::passage;
         setNotification(1,ObjectToJson::passage);
     }
     else if(signal==QString::number(chatRoom)){
         ObjectToJson::parseString(json);
         //qDebug()<<ObjectToJson::passage;
         QString mess = ObjectToJson::passage;
        ChatMessageRecived(mess);
     }
     else if(signal==QString::number(searchProductType)){
         QList<ProductType*>PtList = ObjectToJson::parseProductType(json);
     }
     else if(signal==QString::number(clientUpdate)){
         ObjectToJson::parseString(json);
         //qDebug()<<ObjectToJson::passage;
         setNotification(1,ObjectToJson::passage);
     }
     else if(signal=="1000009"||signal=="1000010"){

     }
     else{//qDebug()<<"解析失败";
     setNotification(2,"解析失败");
     }

}

Allmain::~Allmain()
{
    delete ui;
}

void Allmain::settabWidget()
{
    ui->tabWidget->setTabText(0,"发现好货");
    ui->tabWidget->setTabText(1,"促销活动");
    ui->tabWidget->setTabText(2,"客服消息");
    ui->tabWidget->setTabText(3,"购物车");
    ui->tabWidget->setTabText(4,"购买记录");
    ui->tabWidget->setTabText(5,"搜索记录");
    ui->tabWidget->setTabText(6,"商品搜索");
}

void Allmain::setSocket(TcpSocket *socket)
{
    if(tcpSocket==nullptr)
    tcpSocket = socket;
}

void Allmain::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter_mainback(this);
    painter_mainback.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/mianwindows/images/mainback.png"));
    ui->pushButton_people->setMask(QRegion(0,0,28,28,QRegion::Ellipse));
}

void Allmain::mousePressEvent(QMouseEvent *event)
{
    //获取title widget 的高度，这里固定为60px
    int titleHeight = ui->title_Widget->height();
    if(event->y() <titleHeight)
    {
        last = event->globalPos(); //获取到按压的位置
    }
}

void Allmain::mouseMoveEvent(QMouseEvent *event)
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

void Allmain::mouseReleaseEvent(QMouseEvent *event)
{
    int titleHeight = ui->title_Widget->height();
    if(event->y() <titleHeight)
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        this->move(this->x()+dx,this->y()+dy);
    }
}

void Allmain::setListT1()
{
    ui->listT1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listT1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    findCommodity = new QListWidgetItem(ui->listT1);
    findCommodity->setIcon(QIcon("./images/逛街.svg"));
    findCommodity->setText("发现好货");
    Activitity = new QListWidgetItem(ui->listT1);
    Activitity->setIcon(QIcon("./images/促销活动.svg"));
    Activitity->setText("促销活动");
    ChatRoom = new QListWidgetItem(ui->listT1);
    ChatRoom->setIcon(QIcon("./images/客服消息.svg"));
    ChatRoom->setText("客服消息");

}

void Allmain::setListT2()
{
    ui->listT2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listT2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ShoppingCart = new QListWidgetItem(ui->listT2);
    ShoppingCart->setIcon(QIcon("./images/购物车.svg"));
    ShoppingCart->setText("我的购物车");
    myCollect = new QListWidgetItem(ui->listT2);
    myCollect->setIcon(QIcon("./images/收藏.svg"));
    myCollect->setText("购买记录");
    chosenCommodity = new QListWidgetItem(ui->listT2);
    chosenCommodity->setIcon(QIcon("./images/生活-选中.svg"));
    chosenCommodity->setText("搜索记录");
    SearchCommodity = new QListWidgetItem(ui->listT2);
    SearchCommodity->setIcon(QIcon("./images/搜索search.svg"));
    SearchCommodity->setText("商品搜索");
}

void Allmain::setPictureWall()
{
   pictureWidget = new PictureWidget();
   connect(pictureWidget,&PictureWidget::sendChangeMessage,[=](int choose){
       if(choose<=6)
       ui->tabWidget->setCurrentIndex(choose);
       else{
           if(choose==7){
               QDesktopServices::openUrl(QUrl("https://github.com/hhhhlkf/GraphBuilder"));
           }
           else if(choose==8)
           {
               QDesktopServices::openUrl(QUrl("https://hhhhlkf.github.io/"));
           }
           else if(choose==9)
           {
               QDesktopServices::openUrl(QUrl("https://gitee.com/linexus/music-wwy"));
           }
       }
   });
   ui->verLout_pic->addWidget(pictureWidget);
}

void Allmain::setCommendlistWall(QList<Product*>Plist)
{
    QListWidgetItem * newWidget = new QListWidgetItem(ui->listT3);
    CommendListItem * commendListItem = new CommendListItem();
    connect(commendListItem,&CommendListItem::sglClick,[=](int id,QString name,QString price,float discount,QString Image){
        Commodity*commodity = new Commodity();
        commodity->setCommodityId(id);
        commodity->setCommodityNum(0);
        commodity->setCommodityName(name);
        if(discount<1)
        {
            commodity->setCommodityPrice("折扣价："+QString::number(price.toInt()*discount));
            commodity->setPrice(price.toInt()*discount);
        }
        else
        {
            commodity->setCommodityPrice(price);
            commodity->setPrice(price.toFloat());
        }
        commodity->setPic(Image);
        QList<ProductType*>TypeList;
        for(int j =0;j<ProductTypeList.size();j++)
        {
            if(ProductTypeList[j]->getTypeProductId()==id){
                ProductType * type = new ProductType(*ProductTypeList[j]);
                TypeList.append(type);
            }
        }
        commodity->setAttribute(Qt::WA_DeleteOnClose);
        connectBuySignaal(commodity);
        commodity->setTypeList(TypeList);
        ui->tabselectWidget->addTab(commodity,name);
        ui->tabWidget->setCurrentIndex(5);
        ui->tabselectWidget->setCurrentIndex(ui->tabselectWidget->count());

    });
    commendListItem->setProductList(Plist);
    //ui->listT3->insertItem(0,newWidget);
    ui->listT3->setItemWidget(newWidget,commendListItem);
}

void Allmain::setGallery(QList<Product*>Plist)
{
    gallerPrivate[0] = new GalleryPrivate();
    gallerPrivate[1] = new GalleryPrivate();
    QList<GalleryItem * > items;
    QList<GalleryItem * > items2;
    int onSaleNum = 16 ;
    GalleryItem *item[onSaleNum/2];
    for (int i = 0;i < onSaleNum/2;i++)
    {
        item[i] = new GalleryItem();
        item[i]->setProduct(Plist[i]);
        setGalleryConnected(item[i]);
        items.append(item[i]);

    }
    GalleryItem *item2[onSaleNum/2];
    for (int i = 0;i< onSaleNum/2;i++)
    {
        item2[i] = new GalleryItem();
        item2[i]->setProduct(Plist[i+onSaleNum/2]);
        setGalleryConnected(item2[i]);
        items2.append(item2[i]);
    }
    gallerPrivate[0]->setItemRes(item[0]->width(),item[0]->height(),items);
    ui->horizontalLayout_6->setContentsMargins(0,0,0,0);
    ui->horizontalLayout_6->addWidget(gallerPrivate[0]->getItemViewport());
        ui->horizontalLayout_6->setContentsMargins(0,0,0,0);
    gallerPrivate[1]->setItemRes(item2[0]->width(),item2[0]->height(),items2);
    ui->horizontalLayout_22->addWidget(gallerPrivate[1]->getItemViewport());
}


void Allmain::dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type)
{
    messageW->setFixedWidth(ui->ChatList->width());
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(text, time, size, type);
    ui->ChatList->setItemWidget(item, messageW);
//    QJsonObject object;
//    ObjectToJson::addSignal(object,QString::number(chatRoom));
//    ObjectToJson::integrateClientList(object,ClientList);
//    ObjectToJson::integrateString(object,"",text);
//    QByteArray array = ObjectToJson::changeJson(object);
//    tcpSocket->SendMessageToServer(array);
}

void Allmain::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;
    if(ui->ChatList->count() > 0) {
        QListWidgetItem* lastItem = ui->ChatList->item(ui->ChatList->count() - 1);
        QNChatMessage* messageW = (QNChatMessage*)ui->ChatList->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
//        isShowTime = true;
    } else {
        isShowTime = true;
    }
    if(isShowTime) {
        QNChatMessage* messageTime = new QNChatMessage(ui->ChatList->parentWidget());
        QListWidgetItem* itemTime = new QListWidgetItem(ui->ChatList);

        QSize size = QSize(ui->ChatList->width(), 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, QNChatMessage::User_Time);
        ui->ChatList->setItemWidget(itemTime, messageTime);
    }
}

void Allmain::ChatMessageRecived(QString mess)
{

        QString msg=mess;
        QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
        qDebug()<<"addMessage" << msg << time << ui->ChatList->count();
        msg=msg.toUtf8();
        bool isResevicing = true;
        if(isResevicing)
        {
            dealMessageTime(time);
            QNChatMessage* messageW = new QNChatMessage(ui->ChatList->parentWidget());
            messageW->setLeftPixmap(QPixmap("images/nzk.ico"));
            QListWidgetItem* item = new QListWidgetItem(ui->ChatList);
            dealMessage(messageW, item, msg, time, QNChatMessage::User_She);
        }
}

void Allmain::ChatMessageSend()
{
    if(ui->textEdit->toPlainText()=="")
    {
        return;
    }
    QString msg = ui->textEdit->toPlainText();
    QString time =  QString::number(QDateTime::currentDateTime().toTime_t());
    dealMessageTime(time);

    QJsonObject object;
    ObjectToJson::addSignal(object,QString::number(chatRoom));
    ObjectToJson::integrateClientList(object,ClientList);
    ObjectToJson::integrateString(object,"",msg);
    QByteArray array = ObjectToJson::changeJson(object);
    tcpSocket->SendMessageToServer(array);

    QNChatMessage* messageW = new QNChatMessage(ui->ChatList->parentWidget());
    messageW->setRightPixmap(QPixmap(ClientList[0]->getClientImage()));
    QListWidgetItem* item = new QListWidgetItem(ui->ChatList);
    dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
    ui->textEdit->clear();
}

void Allmain::setInitData(QList<Order*>shoppingCart)
{
    ui->ShoppingCartList->clear();
    ShoppingCartList.clear();
    const int num=shoppingCart.size();
    QListWidgetItem *items[num];
    NewCourierItem * nitems[num];
    for (int i =0 ; i<num;i++)
    {
        if(shoppingCart[i]->getOrderCheck()==-1)
        {
            Order * order = new Order(*shoppingCart[i]);
            items[i] = new QListWidgetItem(ui->ShoppingCartList);
            nitems[i] = new NewCourierItem();
            nitems[i]->setOrder(order);
            for (int j=0;j<ProductList.size();j++) {
                if(ProductList[j]->getProductId()==order->getOrderProductId())
                {
//                    /qDebug()<<ProductList[j]->getProductImage();
                    nitems[i]->setPicture(ProductList[j]->getProductImage());
                }
            }
            nitems[i]->setcheckBox();
            nitems[i]->number=++ShoppingCartNum;
            ui->ShoppingCartList->setItemWidget(items[i],nitems[i]);
            ShoppingCartList.append(nitems[i]);
            setOrderConnected(1,nitems[i]);
        }
    }
}

void Allmain::setHistoryData(QList<Order*>HistoryList)
{
    ui->HistoryList->clear();
    HistoryItemList.clear();
    const int num=HistoryList.size();
    QListWidgetItem *items[num];
    NewCourierItem * nitems[num];
    for (int i =0 ; i<num;i++)
    {
        if(HistoryList[i]->getOrderCheck()==1)
        {
            Order * order = new Order(*HistoryList[i]);
            items[i] = new QListWidgetItem(ui->HistoryList);
            nitems[i] = new NewCourierItem();
            nitems[i]->setOrder(order);
            nitems[i]->number=++ShoppingCartNum;
            for (int j=0;j<ProductList.size();j++) {
//                qDebug()<<ProductList[j]->getProductImage()<<order->getOrderProductId();
                if(ProductList[j]->getProductId()==order->getOrderProductId())
                {
                    nitems[i]->setPicture(ProductList[j]->getProductImage());
                }
            }
            nitems[i]->setcheckBox();
            ui->HistoryList->setItemWidget(items[i],nitems[i]);
            HistoryItemList.append(nitems[i]);
            //qDebug()<<"传进来的number是："<<nitems[i]->number;
            setOrderConnected(2,nitems[i]);
        }

    }
}

void Allmain::setOrderConnected(int choose, NewCourierItem *item)
{
    Q_UNUSED(choose);
    connect(item,&NewCourierItem::sglClicked,[=](int id,int num,QString ProductName,QString ProductStyle)
    {
         Commodity*commodity = new Commodity();
         commodity->setCommodityId(id);
         commodity->setCommodityNum(num);
         commodity->setCommodityName(ProductName);
         commodity->setCommodityType(ProductStyle);
         for (int i=0;i<ProductList.size();i++) {
               if(ProductList[i]->getProductId()==id)
               {
                   commodity->setPic(ProductList[i]->getProductImage());
                   commodity->setCommodityPrice(QString::number(ProductList[i]->getProductPrice()));
                   float discount = ProductList[i]->getProductDiscount();
                   QString price = QString::number(ProductList[i]->getProductPrice());
                   if(discount<1)
                   {
                       commodity->setCommodityPrice("折扣价："+QString::number(price.toInt()*discount));
                       commodity->setPrice(price.toInt()*discount);
                   }
                   else
                   {
                       commodity->setCommodityPrice(price);
                       commodity->setPrice(price.toFloat());
                   }
               }
         }
         QList<ProductType*>TypeList;
         for(int j =0;j<ProductTypeList.size();j++)
         {
             if(ProductTypeList[j]->getTypeProductId()==id){
                 ProductType * type = new ProductType(*ProductTypeList[j]);
                 TypeList.append(type);
             }
         }
        commodity->setAttribute(Qt::WA_DeleteOnClose);
         commodity->setTypeList(TypeList);
         connectBuySignaal(commodity);
         ui->tabselectWidget->addTab(commodity,ProductName);
         ui->tabWidget->setCurrentIndex(5);
         ui->tabselectWidget->setCurrentIndex(ui->tabselectWidget->count());
    });
}
void Allmain::setselectData(QString text)
{
    ui->CommodityselectList->clear();
    QJsonObject object;
    ObjectToJson::integrateString(object,"",text);
    ObjectToJson::addSignal(object,QString::number(searchProduct));
    ObjectToJson::integrateClientList(object,ClientList);
        QByteArray array =ObjectToJson::changeJson(object);
    tcpSocket->write(array);
//    while(TemporaryList.size()==0){}
    const int num=TemporaryList.size();
    QListWidgetItem *items[num];
    NewSelectItem * nitems[num];
    for (int i =0 ; i<num;i++)
    {
        items[i] = new QListWidgetItem(ui->CommodityselectList);
        nitems[i] = new NewSelectItem();
        Product * product =new Product(*TemporaryList[i]);
        nitems[i]->setProduct(product);
        ui->CommodityselectList->setItemWidget(items[i],nitems[i]);
        connect(nitems[i],&NewSelectItem::sglSetClick,[=](int id,int num,QString name,QString Image,QString money){
            Commodity*commodity = new Commodity();
            commodity->setCommodityId(id);
            Q_UNUSED(num);
            commodity->setCommodityNum(0);
            commodity->setCommodityName(name);
            commodity->setCommodityPrice(money);
            commodity->setPic(Image);
            QList<ProductType*>TypeList;
            for(int j =0;j<ProductTypeList.size();j++)
            {
                if(ProductTypeList[j]->getTypeProductId()==id){
                    ProductType * type = new ProductType(*ProductTypeList[j]);
                    TypeList.append(type);
                }
            }
            commodity->setAttribute(Qt::WA_DeleteOnClose);
            commodity->setTypeList(TypeList);
            connectBuySignaal(commodity);
            ui->tabselectWidget->addTab(commodity,name);

            ui->tabWidget->setCurrentIndex(5);
            ui->tabselectWidget->setCurrentIndex(ui->tabselectWidget->count());
        });
    }
}





void Allmain::on_btnPerL_clicked()
{
    int num = gallerPrivate[0]->getPreviousItemIndex();
    gallerPrivate[0]->showImage(num);
}


void Allmain::on_btnPerR_clicked()
{
    int num = gallerPrivate[0]->getNextItemIndex();
    gallerPrivate[0]->showImage(num);
}

void Allmain::on_btnPerL_2_clicked()
{
    int num = gallerPrivate[1]->getPreviousItemIndex();
    gallerPrivate[1]->showImage(num);
}

void Allmain::on_btnPerR_2_clicked()
{
    int num = gallerPrivate[1]->getNextItemIndex();
    gallerPrivate[1]->showImage(num);
}

bool Allmain::eventFilter(QObject *target, QEvent *event)
{
    if(target == ui->textEdit)
    {
        if(event->type() == QEvent::KeyPress)//回车键
        {
             QKeyEvent *k = static_cast<QKeyEvent *>(event);
             if(k->key() == Qt::Key_Return)
             {
                 emit(ui->ptnChange->clicked());
                 return true;
             }
        }
    }
    return QWidget::eventFilter(target,event);
}


void Allmain::on_pushButton_name_clicked()
{
    if(p_dev)
    {
        if(p_dev->isHidden())
        {
            p_dev->show();
        }
        else {
            p_dev->hide();
        }

    }
    else {
        p_dev = new DeveloperDemo(this);
        p_dev->setGeometry(538,55,290,160); //这里要调整好
        p_dev->raise();  //提示显示层数
        p_dev->show();
    }
}

void Allmain::on_pushButton_set_clicked()
{
    if(p_person)
    {
        if(p_person->isHidden())
        {
            p_person->show();
        }
        else {
            p_person->hide();
        }
    }
    else
    {
        p_person = new personForm(this);
        p_person->setClient(ClientList[0]);
        connect(p_person,&personForm::sglUpdateClient,[=](Client*client){
            QJsonObject object;
            client->setClientImage(picShow);
            QList<Client*>Clist;Clist.append(client);
            ObjectToJson::integrateClientList(object,Clist);
            ObjectToJson::addSignal(object,QString::number(clientUpdate));
            QByteArray array = ObjectToJson::changeJson(object);
            tcpSocket->SendMessageToServer(array);
        });
        connect(p_person,&personForm::exitApp,[=](){
            exitAndReturn();
        });
        connect(p_person,&personForm::setClientPortrait,[=](int choose){
            ui -> pushButton_people ->setDisabled(bool(choose));
        });
        p_person->setGeometry(538,55,290,472); //这里要调整好
        p_person->raise();  //提示显示层数
        p_person->show();
    }
}

void Allmain::exitAndReturn()
{
    this->hide();
    From->show();
    ui->tabselectWidget->clear();
    ui->listT3->clear();
    ui->ChatList->clear();
    ui->ShoppingCartList->clear();
    ShoppingCartList.clear();
    ui->HistoryList->clear();
    HistoryItemList.clear();
    ClientList.clear();
    ProductList.clear();
    OrderList.clear();

}

void Allmain::on_pushButton_cloth_clicked()
{
    if(changeColor)
    {
        if(changeColor->isHidden())
        {
            changeColor->show();
        }
        else {
            changeColor->hide();
        }

    }
    else {
        changeColor = new ChangeColorForm(this);
        changeColor->setGeometry(578,60,409,317); //这里要调整好
        changeColor->raise();  //提示显示层数
        changeColor->show();
    }
}

void Allmain::on_tabselectWidget_tabCloseRequested(int index)
{
    if(index<0)return ;
    QWidget* tab = ui->tabselectWidget->widget(index);
    tab->close();
}

void Allmain::setGalleryConnected(GalleryItem *item)
{
    connect(item,&GalleryItem::sglClick,[=](int id,QString name,QString price,float discount,QString Image){
        Commodity*commodity = new Commodity();
        commodity->setCommodityId(id);
        commodity->setCommodityNum(0);
        commodity->setCommodityName(name);
        if(discount<1)
        {
            commodity->setCommodityPrice("折扣价："+QString::number(price.toInt()*discount));
            commodity->setPrice(price.toInt()*discount);
        }
        else
        {
            commodity->setCommodityPrice(price);
            commodity->setPrice(price.toFloat());
        }
        commodity->setPic(Image);
        QList<ProductType*>TypeList;
        for(int j =0;j<ProductTypeList.size();j++)
        {
            if(ProductTypeList[j]->getTypeProductId()==id){
                ProductType * type = new ProductType(*ProductTypeList[j]);
                TypeList.append(type);
            }
        }
        commodity->setAttribute(Qt::WA_DeleteOnClose);
        commodity->setTypeList(TypeList);
        ui->tabselectWidget->addTab(commodity,name);
        connectBuySignaal(commodity);
        ui->tabWidget->setCurrentIndex(5);
        ui->tabselectWidget->setCurrentIndex(ui->tabselectWidget->count());
    });
}



void Allmain::on_ptnBuy_clicked()
{
    QList<Order*>OList;
    QList<int>List;
    for (int i=0;i<ShoppingCartList.size();i++) {
        if(ShoppingCartList[i]->getCheckBox()){
            List.append(ShoppingCartList[i]->number);
            Order * order = new Order(*ShoppingCartList[i]->getOrder());
            Order * order1 = new Order(*order);
            NewCourierItem * widget = new NewCourierItem();
            widget->setOrder(order1);
            for(int j=0;j<ProductList.size();j++)
            {
                if(widget->order->getOrderProductId()==ProductList[j]->getProductId())
                {
                    widget->setPicture(ProductList[j]->getProductImage());break;

                }
            }
            order->setOrderCost(order->getOrderCost());
            order->setOrderProductNum(order->getOrderProductNum());
            order->setOrderCheck(1);
            OList.append(order);
            QListWidgetItem * item =new QListWidgetItem(ui->HistoryList);
            //ui->ShoppingCartList->takeItem(i);
            ui->HistoryList->setItemWidget(item,widget);
            HistoryItemList.append(widget);
            //ShoppingCartList.removeAt(i);
        }
    }
    for (int i=0;i<List.size();i++) {
        for (int j=0;j<ShoppingCartList.size();j++) {
            if(ShoppingCartList[j]->number==List[i]){
                ShoppingCartList.removeAt(j);
                ui->ShoppingCartList->takeItem(j);
            }
        }
    }
    QJsonObject object;
    ObjectToJson::integrateOrderList(object,OList);
    ObjectToJson::integrateClientList(object,ClientList);
    ObjectToJson::addSignal(object,QString::number(updateOrder));
    QByteArray array = ObjectToJson::changeJson(object);
    tcpSocket->SendMessageToServer(array);
}

void Allmain::on_btnDel_clicked()
{
    QList<Order*>OList;
    QList<int>List;
        for (int i=0;i<ShoppingCartList.size();i++) {
            if(ShoppingCartList[i]->getCheckBox()){
                List.append(ShoppingCartList[i]->number);
                Order*order = new Order(*ShoppingCartList[i]->getOrder());
                OList.append(order);
                //ShoppingCartList.removeAt(i);
            }
        }
        for (int i=0;i<List.size();i++) {
            for (int j=0;j<ShoppingCartList.size();j++) {
                if(ShoppingCartList[j]->number==List[i]){
                    ShoppingCartList.removeAt(j);
                    ui->ShoppingCartList->takeItem(j);
                }
            }
        }
        QJsonObject object;
        ObjectToJson::integrateOrderList(object,OList);
        ObjectToJson::integrateClientList(object,ClientList);
        ObjectToJson::addSignal(object,QString::number(deleteShopping));
        QByteArray array = ObjectToJson::changeJson(object);
        tcpSocket->SendMessageToServer(array);
}

void Allmain::on_btnRes_clicked()
{
    QList<Order*>OList;
    QList<int>List;
    //qDebug()<<HistoryItemList.size();
    for (int i=0;i<HistoryItemList.size();i++)
    {
        if(HistoryItemList[i]->getCheckBox()){
            List.append(HistoryItemList[i]->number);
            Order * order = new Order(*HistoryItemList[i]->getOrder());
            Order * order1 = new Order(*order);
            NewCourierItem * widget = new NewCourierItem();
            widget->setOrder(order1);
            for(int j=0;j<ProductList.size();j++)
            {
                if(widget->order->getOrderProductId()==ProductList[j]->getProductId())
                {
                    widget->setPicture(ProductList[j]->getProductImage());
                    //qDebug()<<ProductList[j]->getProductImage();
                    //break;
                }
            }
            order->setOrderCost(QString::number(order->getOrderCost().toFloat()*(-1)));
            order->setOrderProductNum(order->getOrderProductNum()*(-1));
            order->setOrderCheck(-1);
            OList.append(order);
            QListWidgetItem * item =new QListWidgetItem(ui->ShoppingCartList);
            ui->ShoppingCartList->setItemWidget(item,widget);
            ShoppingCartList.append(widget);
        }
    }
    for (int i=0;i<List.size();i++) {
        for (int j=0;j<HistoryItemList.size();j++) {
            if(HistoryItemList[j]->number==List[i]){
                HistoryItemList.removeAt(j);
                ui->HistoryList->takeItem(j);
            }
        }
    }
    QJsonObject object;
    ObjectToJson::integrateOrderList(object,OList);
    ObjectToJson::integrateClientList(object,ClientList);
    ObjectToJson::addSignal(object,QString::number(updateOrder));
    QByteArray array = ObjectToJson::changeJson(object);
    tcpSocket->SendMessageToServer(array);
}

void Allmain::on_btnDelH_clicked()
{
    QList<Order*>OList;
    QList<int>List;
    for (int i=0;i<HistoryItemList.size();i++) {
        if(HistoryItemList[i]->getCheckBox()){
            List.append(HistoryItemList[i]->number);
            Order*order = new Order(*HistoryItemList[i]->getOrder());
            order->setOrderHide(1);
            OList.append(order);
            //HistoryItemList.removeAt(i);
        }
    }
    for (int i=0;i<List.size();i++) {
        for (int j=0;j<HistoryItemList.size();j++) {
            if(HistoryItemList[j]->number==List[i]){
                HistoryItemList.removeAt(j);
                ui->HistoryList->takeItem(j);
            }
        }
    }
    QJsonObject object;
    ObjectToJson::integrateOrderList(object,OList);
    ObjectToJson::integrateClientList(object,ClientList);
    ObjectToJson::addSignal(object,QString::number(updateOrder));
    QByteArray array = ObjectToJson::changeJson(object);
    tcpSocket->SendMessageToServer(array);
}



void Allmain::on_pushButton_people_clicked()
{
    QString name = picShow;
    picShow = QFileDialog::getOpenFileName(this,"打开文件","D:/code/Qt/C++project/imagebase");
    ui->pushButton_people->setStyleSheet("QPushButton{border-image:url("+picShow+");}");
    if(picShow==""||picShow.isNull())
        ui->pushButton_people->setStyleSheet("QPushButton{border-image:url("+name+");}");
}

void Allmain::on_pushButton_title_left_clicked()
{
    if(ui->tabWidget->currentIndex()==0)
    {
        ui->tabWidget->setCurrentIndex(7);
    }
    ui->tabWidget->setCurrentIndex((ui->tabWidget->currentIndex()-1)%7);
}

void Allmain::on_pushButton_title_right_clicked()
{
    ui->tabWidget->setCurrentIndex((ui->tabWidget->currentIndex()+1)%7);
}
