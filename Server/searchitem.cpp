#include "searchitem.h"
#include "ui_searchitem.h"

SearchItem::SearchItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchItem)
{
    ui->setupUi(this);
//    ui->lab_num->setFont()
    this->setStyleSheet("QLabel{background:transparent;}"
                        );
    ui->lab_name->setStyleSheet("QLabel{color:rgb(51,51,51);}");
    ui->lab_ranking->setStyleSheet("QLabel{color:rgb(204,204,204);}");
//    ui->lab_message->setStyleSheet("QLabel{color:rgb(153,153,153);}");

}

SearchItem::~SearchItem()
{
    delete ui;
}

void SearchItem::setLabNumColor(bool bo)
{
    if(bo == false)
    {
        ui->lab_num->setStyleSheet("QLabel{color:rgb(255,61,61)}");
    }
    else {
        ui->lab_num->setStyleSheet("QLabel{color:rgb(222,222,222)}");
    }
}

void SearchItem::setLabNumText(QString str)
{
    ui->lab_num->setText(str);
}

void SearchItem::setLabNameText(QString str)
{
    ui->lab_name->setText(str);
}

void SearchItem::setLabrankingText(QString str)
{
    ui->lab_ranking->setText(str);
}

//void SearchItem::setLabMessageText(QString str)
//{
//    ui->lab_message->setText(str);
//}


