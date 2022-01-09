#ifndef PICTUREITEM_H
#define PICTUREITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QPixmap>
#include <QWidget>
//轮播图物品
class pictureItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit pictureItem(QGraphicsObject *parent = nullptr);
    explicit pictureItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);
    virtual ~pictureItem();
    void setPixmap(const QPixmap &pixmap);  //设置pixmap
    QPixmap pixmap() const;
     virtual QRectF boundingRect() const;  //绑定大小
    void setTransformationMode(Qt::TransformationMode mode);  //设置模式
    QPointF offset() const;
    void setOffset(const QPointF &offset);
    virtual int type()const;
    void setType(int type);
    int itemId()const;
    void setItemId(int id);
signals:
    void clicked();
    void clickedId(int);
    void changePage(int);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


public slots:

private:
    QPointF pressedSceneP; //按压的点
    QPointF m_offset;
    QPointF m_pos;
    Qt::TransformationMode mode; //样式
    QPixmap m_pixmap;
    bool isPressed;   // 判断按压
    int m_type;       //类型
    int m_id;         //id类型
    qreal m_pointPercent;
};

#endif // PICTUREITEM_H
