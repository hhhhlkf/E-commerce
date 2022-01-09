#ifndef CREATENOTIFICATION_H
#define CREATENOTIFICATION_H
//创建提示弹窗
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QHBoxLayout>
class CreateNotification : public QWidget
{
    Q_OBJECT
public:
    explicit CreateNotification(int color,QString message,QWidget *parent = nullptr);
signals:

};

#endif // CREATENOTIFICATION_H
