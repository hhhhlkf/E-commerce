#include "rightcheck.h"
#include "ui_rightcheck.h"

RightCheck::RightCheck(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RightCheck)
{
    ui->setupUi(this);
}

RightCheck::~RightCheck()
{
    delete ui;
}

void RightCheck::on_pushButton_myquit_clicked()
{
    DelSelectItem();
}
