#include "changecolorform.h"
#include "ui_changecolorform.h"
#include "loadfileqss.h"
ChangeColorForm::ChangeColorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeColorForm)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground); //设置样式表
    this->setStyleSheet("QWidget{border:1px; background:rgb(255,255,255); border-radius:8px;}"
                        "QWidget:hover{background:rgb(255,255,255);}");
    ui->ptnRed->setStyleSheet("QPushButton{background:rgb(236,65,65); border:0px;}");
    ui->ptnBlue->setStyleSheet("QPushButton{background:rgb(57,175,234);border:0px;}");
    ui->ptnPink->setStyleSheet("QPushButton{background:rgb(255,122,158);border:0px;}");
    ui->ptnOrange->setStyleSheet("QPushButton{background:rgb(176,160,116);border:0px;}");
    ui->ptnYellow->setStyleSheet("QPushButton{background:rgb(249,238,90);border:0px;}");
    ui->ptnGreen->setStyleSheet("QPushButton{background:rgb(106,204,25);border:0px;}");
}

ChangeColorForm::~ChangeColorForm()
{
    delete ui;
}

void ChangeColorForm::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->close();
}

void ChangeColorForm::on_ptnRed_clicked()
{

     LoadFileQss::setStyle("./FileColorQSS/Red.qss"); //加载qss 样式表，用静态方式
}

void ChangeColorForm::on_ptnBlue_clicked()
{
     LoadFileQss::setStyle("./FileColorQSS/Blue.qss"); //加载qss 样式表，用静态方式
}


void ChangeColorForm::on_ptnPink_clicked()
{
     LoadFileQss::setStyle("./FileColorQSS/Pink.qss"); //加载qss 样式表，用静态方式
}

void ChangeColorForm::on_ptnOrange_clicked()
{
    LoadFileQss::setStyle("./Allthe.qss"); //加载qss 样式表，用静态方式
}

void ChangeColorForm::on_ptnYellow_clicked()
{
    LoadFileQss::setStyle("./FileColorQSS/Yellow.qss"); //加载qss 样式表，用静态方式
}

void ChangeColorForm::on_ptnGreen_clicked()
{
    LoadFileQss::setStyle("./FileColorQSS/Green.qss"); //加载qss 样式表，用静态方式
}
