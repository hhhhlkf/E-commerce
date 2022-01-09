#include "picturebutton.h"
#include <QPen>
#include <QPainter>
#include <QDebug>
#include <QPainterPath>
pictureButton::pictureButton(QWidget *parent)
    : QAbstractButton(parent)
{
    m_isSelected = false;
    m_id = 0;
    setCheckable(true);
    setFixedSize(8,8);
}

pictureButton::~pictureButton()
{

}

int pictureButton::id() const
{
    return m_id;
}

void pictureButton::setId(int id)
{
    m_id = id;
}

void pictureButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRectF drawRect = this->rect();
    QPainterPath drawPath;
    QPen drawPen;
    drawPen.setWidth(1);
    //选中为红,未选中为灰
    drawPen.setColor(Qt::gray);
    painter.setPen(drawPen);
    //抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    drawPath.addRoundedRect(drawRect,4,4);
    painter.setClipPath(drawPath);
    if(isChecked())
    {
         painter.fillRect(drawRect,QColor(236,65,65));  //变成红色
    }
    else {
         painter.fillRect(drawRect,QColor(128,128,128,128));
    }

    if(isChecked())
    {
//        emit entered(m_id);
    }

}

void pictureButton::enterEvent(QEvent *event)
{
    if(!isChecked())
        setChecked(true);
    emit entered(m_id);
    return QAbstractButton::enterEvent(event);
}

void pictureButton::leaveEvent(QEvent *event)
{
     //setChecked(false);
     return QAbstractButton::leaveEvent(event);
}
