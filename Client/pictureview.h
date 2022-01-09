#ifndef PICTUREVIEW_H
#define PICTUREVIEW_H

#include <QGraphicsView>
//轮播图相关
class pictureView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit pictureView(QWidget *parent = nullptr);
    virtual ~pictureView();
protected:
    virtual void resizeEvent(QResizeEvent *event); //

signals:
    void sizeChanged(const QSize &);
};

#endif // PICTUREVIEW_H
