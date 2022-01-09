#include "createnotification.h"

CreateNotification::CreateNotification(int color,QString message,QWidget *parent) : QWidget(parent)
{
    if(color==1){
        this->setStyleSheet("QWidget{border: rgb(255, 255, 255);background: "
                            "rgb(107, 255, 142);font-size: 18px;color:rgb(255,255,255);"
                            "border-radius:10px;font-family: 微软雅黑;}");
    }
    else if(color==2){
        this->setStyleSheet("QWidget{border: rgb(255, 255, 255);background: "
                            "rgb(232, 2, 2);font-size: 18px;color:rgb(255,255,255);"
                            "border-radius:10px;font-family: 微软雅黑;}");
    }
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    QHBoxLayout * Layout = new QHBoxLayout();
    QLabel * label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);
    label->setText(message);
    Layout->addWidget(label);
    this->setLayout(Layout);
//    this->setAttribute(Qt::WA_DeleteOnClose);
}


