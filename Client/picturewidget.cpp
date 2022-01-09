#include "picturewidget.h"
#include "ui_picturewidget.h"
#include "pictureitem.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QPainterPath>
#include <QGraphicsView>
#include <QDebug>
#include <QQueue>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <cmath>
#include <ctime>
#include <QTransform>
#include <QButtonGroup>
#include <QMap>
static int dir = 0;//记录方向
static QList<qreal> spaceList;
static QList<qreal> unitList;
static QList<qreal> transScaleList;//缩放比例表
static QSize pictrueBigSize = RAW_VIEW_SIZE/SCALE_VIEW_PIXMAP;
static QSize pictrueSmallSize = RAW_VIEW_SIZE/SCALE_VIEW_PIXMAP/SCALE_BIG_SMALL;
static QList<pictureItem *> itemList;
static QList<int> finishList;
static QMap<int, pictureItem *> mapLink;  //按钮id 与 图片资源的映射
static int startNum = 0;
static QList<QPointF> pointA;

PictureWidget::PictureWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PictureWidget),
    m_timer(new QTimer(this)),
    m_scene(new QGraphicsScene(this)),
    m_index(0),
    m_currentRule(RuleA),
    m_rollCount(0),
    btnMoveEnable(true)
{

    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground); //设置样式表
    setButtonGroup(); //设置按钮组
    setInitList();
    setPictureScreen();
    setTimerAndConnect();

    m_newT = new QTimer(this);
    m_newT->setInterval(5000);
    connect(m_newT,&QTimer::timeout,[this](){
            on_btnR_clicked();
    });
    m_newT->start();
}

PictureWidget::~PictureWidget()
{
    m_newT->stop();
    delete ui;
}

void PictureWidget::setButtonGroup()
{
    m_BtnGroup = new QButtonGroup(this);
    m_BtnGroup->addButton(ui->btnPic0,0);
    m_BtnGroup->addButton(ui->btnPic1,1);
    m_BtnGroup->addButton(ui->btnPic2,2);
    m_BtnGroup->addButton(ui->btnPic3,3);
    m_BtnGroup->addButton(ui->btnPic4,4);
    m_BtnGroup->addButton(ui->btnPic5,5);
    m_BtnGroup->addButton(ui->btnPic6,6);
    m_BtnGroup->addButton(ui->btnPic7,7);
    m_BtnGroup->addButton(ui->btnPic8,8);
    m_BtnGroup->addButton(ui->btnPic9,9);
    m_BtnGroup->setExclusive(true);
    m_BtnGroup->button(1)->setChecked(true);
    for (int i = 0; i<10; i++) {
        static_cast<pictureButton*>(m_BtnGroup->button(i))->setId(i);
    }
}

void PictureWidget::setInitList()
{
    m_PointList << P1 << P2<< P3 << P4 << P5 << P6 << P7 << P8 << P9 << P10;
    m_ZValueList << 1 << 2 << 1  << 0  << 0  << 0  << 0  << 0  << 0  << 0;
    m_PixmapScaleList << 0.8<< 1 << 0.8 << 0.8 << 0.8 << 0.8 << 0.8 << 0.8 << 0.8 <<0.8;
}

void PictureWidget::setPictureScreen()
{
    //设置样式 无标边框
    ui->graphicsView->setStyleSheet("background: transparent; padding: 0px; border: 0px;");
    ui->graphicsView->setScene(m_scene);
    m_scene->setSceneRect(0,0,RAW_VIEW_SIZE.width(),RAW_VIEW_SIZE.height());

    m_MidLine.setPoints(QPointF(0,0),\
                      QPointF(RAW_VIEW_SIZE.width(),0));

    //添加对应图片
    for (int i = 1; i<=10;i++) {
        m_PixmapList.append(QPixmap(QString(":/bin/images/picturewall/%1.jpg").arg(i)));
    }
    for (int i = 0; i<10;i++) {
        itemList.append(new pictureItem(m_PixmapList[i].scaled(pictrueBigSize,
                               Qt::KeepAspectRatio,Qt::SmoothTransformation)));
        itemList[i]->setScale(m_PixmapScaleList[i]);
        itemList[i]->setType(i);
        itemList[i]->setItemId(i);
        itemList[i]->setOffset(QPointF(0,0));
    }
    //图元添加图片
    for(int i = 0; i<10; i++)
    {
        m_scene->addItem(itemList[i]);//添加图元
        itemList[i]->setPos(m_MidLine.pointAt(m_PointList[i]));//设置位置
        itemList[i]->setZValue(m_ZValueList[i]);//设置显示优先级
        itemList[i]->setTransformationMode(Qt::SmoothTransformation);//设置缩放模式
        if(i != 1)
        {
           itemList[i]->setPos(itemList[i]->x(),RAW_VIEW_SIZE.height()/10);
        }
        pointA.append(itemList[i]->pos());  //放入到对应位置
        //qDebug()<< pointA[i].x() << ": " << pointA[i].y();
    }
    //放入映射map中
    for(int i =0; i<10; i++)
    {
        mapLink.insert(static_cast<pictureButton*>(m_BtnGroup->button(i))->id(),itemList[i]);
    }

    QMap<int,pictureItem *>::const_iterator it;

    for (it = mapLink.constBegin();it!=mapLink.constEnd();it++) {
        //qDebug()<< it.key()<< ": " << it.value();
    }

}

void PictureWidget::setTimerAndConnect()
{
    //利用持续时间和帧数计算出定时时间,持续时间/（帧数*持续时间），这里乘1000是转为秒
    m_timer->setInterval(DURATION_MS/(FPS*DURATION_MS/1000));
    connect(m_timer,&QTimer::timeout,this,&PictureWidget::timerOutFunc);

    for(int i = 0; i<10; i++)
    {
        connect(itemList[i],&pictureItem::clickedId,this,&PictureWidget::clickedItemRoll);
        connect(itemList[i],&pictureItem::changePage,this,&PictureWidget::changePage);
        void (pictureButton:: *funcPtr)(int) = &pictureButton::entered;
        connect(static_cast<pictureButton*>(m_BtnGroup->button(i)),funcPtr,[this](int id){
             pictureItem * p = mapLink.value(id); //获取id 的图片值
             btnMoveEnable = false;
             clickedItemRoll(p->type());
             //qDebug()<<p->type();
        });
    }

}

int PictureWidget::getIndexByRules(int oldIndex, int rule)
{
    switch (rule) {
    case 1:
        return  (oldIndex+1)/10;
    case -1:
         return oldIndex==0?9:oldIndex-1;
    default:
        return 0;
    }

}

void PictureWidget::rollItem(int rollDir, unsigned rollCount)
{
    rollCount = 0;
    if(m_timer->isActive())
        return;
    //获取新的数据
    //主要位置  主位置
    int nbegin = rollDir;
    startNum = getrightN(nbegin);
    m_timer->start();
}

int PictureWidget::getrightN(int num)
{
    if(num == -1)
    {
        num = 9;
    }
    if(num == 10)
    {
        num = 0;
    }

    return num;
}

void PictureWidget::timerOutFunc()
{
//    on_btnR_clicked();

    QVector<QGraphicsItemAnimation *>item(10);

    for (int i = 0; i < 10; i++) {
        item[i] = new QGraphicsItemAnimation();
    }

    QTimeLine *timeline = new QTimeLine(200);
    timeline->setLoopCount(1); //设置3次
    int first = getrightN(startNum-1);
    for (int i = 0; i<10; i++) {
        itemList[i] = mapLink.value(first%10);
        first++;

//        QPointF point = m_MidLine.pointAt(m_PointList[i]);
//        itemList[i]->setPos(point);//设置位置
        itemList[i]->setScale(m_PixmapScaleList[i]);
        itemList[i]->setZValue(m_ZValueList[i]);//设置显示优先级
        itemList[i]->setTransformationMode(Qt::SmoothTransformation);//设置缩放模式
        item[i]->setItem(itemList[i]);
        item[i]->setTimeLine(timeline);
        item[i]->setPosAt(1,pointA[i]);

//        if(int(itemList[i]->zValue()) == 2)
//        {
//            item[i]->setScaleAt(1,1,1);
//        }

        itemList[i]->setPos(pointA[i]);

    }

//    QMap<int,pictureItem *>::const_iterator it;

//    for (it = mapLink.constBegin();it!=mapLink.constEnd();it++) {
//        qDebug()<< it.key()<< ": " << it.value();
//    }
    timeline->start();
    m_scene->invalidate();
    m_timer->stop();
}

void PictureWidget::clickedItemRoll(int type)
{
    if(m_timer->isActive())
        return;
    rollItem(type, 0); //得到最新的id 按钮位置
}

void PictureWidget::changePage(int page)
{
    emit sendChangeMessage(page);
}

//左边运动
void PictureWidget::on_btnL_clicked()
{
    int id = m_BtnGroup->checkedId();
    if(id-1<0)
    {
        id = 9;
    }
    else {
        id = id -1;
    }
    m_BtnGroup->button(id)->setChecked(true);
    rollItem(id,0);
}
//右边运动
void PictureWidget::on_btnR_clicked()
{
    int id = m_BtnGroup->checkedId();
    id = (id+1)%10;
    m_BtnGroup->button(id)->setChecked(true);
    rollItem(id,0);
}

template<typename T>
void PictureWidget::rollList(QList<T> &oldList, int dir, int count)
{
    for(int i = 0; i<count; i++)
    {
        if(dir == 1)
        {
            oldList.prepend(oldList.last());
            oldList.removeLast();
        }
        else if(dir == -1)
        {
            oldList.append(oldList.first());
            oldList.removeFirst();
        }
    }

}
