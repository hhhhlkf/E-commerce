#include "galleryprivate.h"

const int Padding = 27;

GalleryPrivate::GalleryPrivate()
{
    itemWidth = 0;
    itemHeght = 0;
    itemCount = 0;
    currentItem = 0;
    animationDuraton = 200; //200毫秒
}

void GalleryPrivate::setItemRes(int itemWidth, int itemHeight, const QList<GalleryItem *> &itemData)
{
    currentItem = 0;
    this->itemWidth = itemWidth;
    this->itemHeght = itemHeight;
    int nSize = itemData.size();
    itemCount = nSize;
    //viewport 的固定大小 显示5个item 与中间4个间隔 每个固定15
    itemViewport = new QWidget();
    itemViewport->setFixedSize(this->itemWidth*5+Padding*4,this->itemHeght);

    // itemContainer 的大小为所有item排在一起的大小
    itemContainer = new QWidget(itemViewport);
    itemContainer->resize(nSize*this->itemWidth + (nSize-1) * Padding,this->itemHeght);
    itemContainer->move(0,0);

    //让对象添加到 对应的位置。
    for (int index = 0; index< itemCount; index++) {
        itemData[index]->setParent(itemContainer);
        itemData[index]->move(index*this->itemWidth+(index) *Padding,0);
    }

    itemViewport->setStyleSheet("QWidget#itemViewport{border:1px; background:white; }");
    itemContainer->setStyleSheet("QWidget#itemContainer{border:1px; background:white; }");

}

int GalleryPrivate::getPreviousItemIndex()
{
    if(hasPreviousItem())
    {
        currentItem--;
    }

    return  currentItem;
}

int GalleryPrivate::getNextItemIndex()
{
    if(hasNextItem())
    {
        currentItem++;
    }
    return currentItem;
}

bool GalleryPrivate::hasNextItem()
{
    return  currentItem < itemCount - 5;
}

bool GalleryPrivate::hasPreviousItem()
{
    return  currentItem > 0;
}

void GalleryPrivate::showImage(int index)
{
    if(index>=0 && index<itemCount - 4)
    {
        QPropertyAnimation *animation = new QPropertyAnimation(itemContainer,"pos");
        animation->setDuration(animationDuraton);
        if(index == 0)
        {
            animation->setEndValue(QPoint(0,0));
        }
        else {
            animation->setEndValue(QPoint(-(index*this->itemWidth+(index)*Padding),0));
        }
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

QWidget *GalleryPrivate::getItemViewport() const
{
    return itemViewport;
}
