#include "pictureview.h"
#include <QResizeEvent>
pictureView::pictureView(QWidget *parent)
    : QGraphicsView(parent)

{

}

pictureView::~pictureView()
{

}

void pictureView::resizeEvent(QResizeEvent *event)
{
    emit sizeChanged(event->size());
    return QGraphicsView::resizeEvent(event);
}
