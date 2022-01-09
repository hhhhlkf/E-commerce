#include "developerdemo.h"
#include "ui_developerdemo.h"

void DeveloperDemo::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->close();
}

DeveloperDemo::DeveloperDemo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeveloperDemo)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground); //设置样式表
}

DeveloperDemo::~DeveloperDemo()
{
    delete ui;
}
