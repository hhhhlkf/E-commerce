#ifndef PICTUREWIDGET_H
#define PICTUREWIDGET_H
//轮播图相关
#include <QWidget>
#include <QButtonGroup>
#include <QGraphicsScene>
#define RAW_VIEW_SIZE QSize(750,198)
#define SCALE_VIEW_PIXMAP (qreal)1/1 //View与图片比例
#define SCALE_BIG_SMALL (qreal)1/1 //图片大小比例
//P1-P10，10个位置，根据需要改动
#define P1 (qreal)0.00
#define P2 (qreal)0.15
#define P3 (qreal)0.44
#define P4 (qreal)0.15
#define P5 (qreal)0.15
#define P6 (qreal)0.15
#define P7 P2
#define P8 P2
#define P9 P2
#define P10 P2
#define MID_TYPE 1
#define FPS 60//帧数，每秒
#define DURATION_MS 500//移动一次图元经过时间,毫秒，不得低于帧数

namespace Ui {
class PictureWidget;
}

class PictureWidget : public QWidget
{
    Q_OBJECT

public:
    enum Rules:int{
        RuleA = 1,
        RuleB = -1,
        RuleC = 2,RuleD = -2};
    explicit PictureWidget(QWidget *parent = nullptr);
    ~PictureWidget();
    void setButtonGroup();  //设置button组
    void setInitList(); //设置相关图片信息
    void setPictureScreen(); //
    void setTimerAndConnect(); //设置定时器与
    int getIndexByRules(int oldIndex,int rule);
    template<typename T>
    void rollList(QList<T> &oldList, int dir, int count);
    void rollItem(int rollDir,unsigned rollCount);
    int  getrightN(int num); //获取准确的位置
public slots:
     void timerOutFunc();
     void clickedItemRoll(int type);
     void changePage(int page);
private slots:
     void on_btnL_clicked();

     void on_btnR_clicked();
signals:
     void sendChangeMessage(int choose);

private:
    Ui::PictureWidget *ui;
    QTimer *m_timer; //定时器
    QGraphicsScene *m_scene; //场景
//    PictrueView *m_view; //视图
    QLineF m_MidLine; //中等线，确定图片位置
    QList<qreal> m_PointList; //各个图片位置信息
    QList<QPixmap> m_PixmapList; //各个图片列表
    QList<qreal> m_ZValueList; //各个显示优先级列表
    QList<qreal> m_PixmapScaleList; //各个图片位置信息伸缩因子列表
    int m_index;
    Rules m_currentRule; //当前执行的类型操作
    unsigned m_rollCount; //滚动次数
    QButtonGroup *m_BtnGroup; //按钮盒子
    bool btnMoveEnable;

    QTimer *m_newT; //旋转定时器
};

#endif // PICTUREWIDGET_H
