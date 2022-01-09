#ifndef ALLMAIN_H
#define ALLMAIN_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QButtonGroup>
#include <QStackedLayout>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QListWidget>
#include <QPoint>
#include "loadfileqss.h"
#include "analysischarts.h"
#include "newselectitem.h"
#include <QVector>
#include "chatroom.h"
#include <QHBoxLayout>
#include "chatlistitem.h"
#include "onsaleitem.h"
//#include "soap/ClientSoap/ClientMapperSoapBinding.nsmap"
#include "dataoperation.h"
#include "objects.h"
#include "stringtrans.h"
#include "searchform.h"
#include <QFileDialog>
#include "objecttojson.h"
#include "tcpserver.h"
#include <QMutex>
#include "notification/createnotification.h"
#define initAll 1000001
#define updateOrder 1000002
#define deleteShopping 1000003
#define searchProduct 1000004
#define addOrderList 1000005
#define chatRoom 1000006
#define searchProductType 1000007
#define clientUpdate 1000008
#define login 1000009
#define signin 1000010
//上面的宏定义为双方接收消息的信号
QT_BEGIN_NAMESPACE
namespace Ui { class AllMain; }
QT_END_NAMESPACE

class AllMain : public QMainWindow
{
    Q_OBJECT

public:
    AllMain(QWidget *parent = nullptr);
    ~AllMain();

    QList<Client*>ClientList;
    QList<Product*>ProductList;
    QList<ProductType*>ProductTypeList;
    QList<Order*>OrderList;

private:
    Ui::AllMain *ui;

protected:
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent* ev);
    //鼠标移动
    void mouseMoveEvent(QMouseEvent* ev);
    //鼠标释放
    void mouseReleaseEvent(QMouseEvent* ev);
    //解释同Client端

    bool eventFilter(QObject *watched, QEvent *event);
    //重写鼠标点击优先级事件

    void initCharts();
    //初始化表格

    void setList1();

    void setList2();
    //同Client端解释

    void setAddorDelBtn();
    //设置添加删除按钮样式和信号

    void selectCommodity(QList<Product*>List);
    //搜索商品

    void setTabName();
    //初始化tabWidget的标题文字

public slots:

    void dealMessage(QByteArray message,qintptr socketDiscriptor);
    //同Client

    void setSlots();
    //统一初始化信号和槽的链接

    void setChangePage();

    void setDelPage(QList<Product*>List);
    //初始化删除列表

    void addChatRoom(qintptr socketDiscriptor,Client*client);
    //添加聊天室

    void initall();
    //统一初始化

    void setSelectOnsale(QList<Product*>List);
    //设置打折商品

    void addOnSaleItem();
    //添加打折商品

    void initOnSaleList();
    //初始化打折商品

    ////Client表的增删改查
    QList<Client*> getClientList();

    Client* getClientByNameAndPwd(QString name,QString pwd);

    void InsertClient(Client* client);

    void deleteClientByNameAndPwd(QString name,QString pwd);

    void updateClient(Client* client);

    QList<Client*> getClientLikeList(QString mess);
    ////Order表的增删改查
    QList<Order*> getOrderList();

    QList<Order*> getOrderListByInfo(Order* order);

    void addOrder(Order* order);

    QList<Order*> getOrderLikeList(QString mess);

    QList<Order*> getOrderListHistory();

    void updateHistory(Order* order);

    void deleteShoppingCart(Order* order);
    ////商品表的增删改查
    QList<Product*>  getProductList(int choose);

    QList<Product*>  getProductListByInfo(Product* product);

    void addProduct(Product* product);

    void deleteProductByInfo(Product* product);

    void updateProductByInfo(Product* product);

    QList<Product*> getProductLikeList(QString mess);
    ////货物类型的增删改查
    QList<ProductType*> getProductTypeByProName(QString name);

    void addProductType(ProductType* type);

    void deleteProductTypeByName(QString name);

    void initChartData();
private slots:
    void on_addSaleBtn_clicked(); 

    void on_addSeries_clicked();

    void on_ptnAdd_clicked();

    void on_RefreshBtn_clicked();

    void on_picShow_clicked();

    void on_pushButton_title_left_clicked();

    void on_pushButton_title_right_clicked();

    void setNotification(int color,QString mess);
    //创建提示信息
private:
    QPoint last;
    analysisCharts * Charts;
    QListWidgetItem * Analysis;
    QListWidgetItem * Chat;
    QListWidgetItem * AddorDelCommodity;
    QListWidgetItem * Activity;
    QListWidgetItem * setCharts;
    QList<NewSelectItem*> selectItems;
    QList<NewSelectItem*>DelItems;
    QList<ChatRoom*>ChatRooms;
    QList<ChatListItem*>ChatRoomItems;
    QList<onSaleItem*>onSaleItemList;
    QList<onSaleItem*>onSaledItemList;
    SearchForm * searchForm;
    SearchForm * searchForm1;
    QString* onSalePic;
    static long long onSaleNum;
    static long long ChatRoomNum;
    static long long DelNum;
    static qintptr AsocketDiscriptor;
    static QByteArray Amessage;
    QString picShow;
    int onsaleCommodityId;
    int productNum;
    QStandardItemModel  *theModel;
    TcpServer * server;//传输端
    QMutex mutex;
    QReadWriteLock lock;
    QList<qintptr>socketDiscriptorList;
signals:
    void sglsearch(QList<Product*>List);
    void sglSearchUpdate(QList<Product*>List);
    void sglSearchDelete(QList<Product*>List);
    void sglSendByteArray(QByteArray json,qintptr socketDiscriptor);
    void sglChatRoom(QString mess,qintptr socketDiscriptor);
    void addChatRoom1(Client*client,qintptr socketDiscriptor);
};
#endif // ALLMAIN_H
