#ifndef GALLERYPRIVATE_H
#define GALLERYPRIVATE_H

#include"galleryitem.h"
#include <QList>
#include <QWidget>
#include <QPropertyAnimation>
/***********************************************************************************************************************
 *                                                    GalleryPrivate                                                   *
 **********************************************************************************************************************/
class GalleryPrivate//轮播图相关
{
public:
    GalleryPrivate();
    //输入item对象的宽与长 以及要放入的对象
    void setItemRes(int itemWidth, int itemHeight, const QList<GalleryItem*>& itemData );
    //上一个的索引
    int getPreviousItemIndex();
    //下一个的索引
    int getNextItemIndex();
    //是否有下一个
    bool hasNextItem();
    //是否有上一个
    bool hasPreviousItem();
    //显示对应位置
    void showImage(int index);
    //获取view 的指针
    QWidget * getItemViewport() const;
private:
    //对象的宽
    int itemWidth;
    //对象的高
    int itemHeght;
    //对象的个数
    int itemCount;
    //当前的对象的索引
    int currentItem;
    // 动画的播放时间，单位为毫秒
    int animationDuraton;
    //能够看到对象的区域
    QWidget * itemViewport;
    //对象的全部区域
    QWidget * itemContainer;

};

#endif // GALLERYPRIVATE_H
