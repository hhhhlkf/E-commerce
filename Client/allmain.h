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
#include "loadfileqss.h"
#include "picturebutton.h"
#include "picturewidget.h"
#include "pictureview.h"
#include "commendlistitem.h"
#include "galleryitem.h"
#include "galleryprivate.h"
#include "chatmessage/qnchatmessage.h"
#include <QDateTime>
#include <QDate>
#include <QTcpSocket>
#include "newcourieritem.h"
#include "commodity.h"
#include "newselectitem.h"
#include "personform.h"
#include "developerdemo.h"
#include "changecolorform.h"
#include <QJsonArray>
#include "objects.h"
#include "objecttojson.h"
#include "socket/tcpsocket.h"
#include "LogAndSign/loginform.h"
#include "LogAndSign/signinform.h"
#include <QFileDialog>
#include "notification/createnotification.h"
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QDesktopServices>
#include <QUrl>
#define initAll 1000001
#define updateOrder 1000002
#define deleteShopping 1000003
#define searchProduct 1000004
#define addOrderList 1000005
#define chatRoom 1000006
#define searchProductType 1000007
#define clientUpdate 1000008
QT_BEGIN_NAMESPACE
namespace Ui { class Allmain; }
QT_END_NAMESPACE

class Allmain : public QMainWindow
{
    Q_OBJECT

public:
    Allmain(QWidget *parent = nullptr);
    ~Allmain();
    void settabWidget();//tabwidget的标签初始化

    void setSocket(TcpSocket* socket);//将登录时的socket转移到主页面来


protected:
    void paintEvent(QPaintEvent* event);//头像设置成圆形

    void mousePressEvent(QMouseEvent* event);
    //鼠标移动
    void mouseMoveEvent(QMouseEvent* event);
    //鼠标释放
    void mouseReleaseEvent(QMouseEvent* event);
    //以上三个鼠标事件为了控制在去掉了默认的关闭，最大化，最小化事件后窗口的移动而重写
    void setListT1(); //初始化左上ListT1

    void setListT2();//初始化左下ListT2

    void setPictureWall();//初始化轮播图

    void setCommendlistWall(QList<Product*>Plist);//初始化首界面推荐商品

    void setGallery(QList<Product*>Plist);//初始化推荐页面商品

    void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type);
    //为聊天消息增加气泡效果

    void dealMessageTime(QString curMsgTime);
    //处理当前消息发送时间

    void ChatMessageRecived(QString mess);
    //处理当前接收到的消息

    void ChatMessageSend();
    //处理发送的消息

    void setInitData(QList<Order*>shoppingCart);
    //初始化购物车列表

    void setHistoryData(QList<Order*>HistoryList);
    //初始化历史记录列表

    void setselectData(QString text);
    //搜索出来的商品初始化

    void initData();
    //接收到客户端数据后进行初始化

    void initOutLook();
    //未接受到数据时的初始化

    void connectBuySignaal(Commodity* commodity);
    //添加跳转信号

    void initAtBeginng(TcpSocket*socket,Client*client);
    //向客户端申请接收数据

    void setNotification(int color,QString mess);
    //操作后的提示小弹窗
private slots:
    void on_btnPerL_clicked();

    void on_btnPerR_clicked();

    void on_btnPerL_2_clicked();

    void on_btnPerR_2_clicked();

    bool eventFilter(QObject *target, QEvent *event);

    void on_pushButton_name_clicked();

    void on_pushButton_set_clicked();

    void on_pushButton_cloth_clicked();

    void getByteArray(QByteArray json);
    //接收到消息后进行分类筛选

    void on_tabselectWidget_tabCloseRequested(int index);

    void setGalleryConnected(GalleryItem*item);

    void setOrderConnected(int choose,NewCourierItem* item);
    void on_ptnBuy_clicked();

    void on_btnDel_clicked();

    void on_btnRes_clicked();

    void on_btnDelH_clicked();

    void exitAndReturn();
    //退出登录的后续完善工作

    void on_pushButton_people_clicked();

    void on_pushButton_title_left_clicked();

    void on_pushButton_title_right_clicked();

private:
    logInForm *From;
    QPoint last;
    QListWidgetItem * SearchCommodity;
    QListWidgetItem *chosenCommodity;
    QListWidgetItem * myCollect;
    QListWidgetItem * ShoppingCart;
    QListWidgetItem * ChatRoom;
    QListWidgetItem * Activitity;
    QListWidgetItem * findCommodity;
    PictureWidget* pictureWidget;
    Ui::Allmain *ui;
    GalleryPrivate * gallerPrivate[2];
    TcpSocket * tcpSocket;
    QList<Commodity*>CommodityList;
    personForm * p_person = nullptr;
    DeveloperDemo * p_dev = nullptr;
    ChangeColorForm * changeColor = nullptr;
    QString picShow;
    QList<Client*>ClientList;
    QList<Product*>ProductList;
    QList<ProductType*>ProductTypeList;
    QList<Order*>OrderList;
    QList<Product*>TemporaryList;
    QList<NewCourierItem*>ShoppingCartList;
    QList<NewCourierItem*>HistoryItemList;
    static int ShoppingCartNum;
signals:
    void setNewInfo(Client * client);
};
#endif // ALLMAIN_H
