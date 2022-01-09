#include "searchform.h"
#include "ui_searchform.h"

SearchForm::SearchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchForm)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground); //设置样式表
    this->setStyleSheet("QWidget{border:1px; background:white; border-radius:5px;}"
                        "QScrollBar:vertical{background:transparent; width:8px;}"
                        "QScrollBar::handle:vertical{background:rgb(224,224,224); width:5px; border-radius:3px;}"
                        "QScrollBar::up-arrow:vertical{border:none;}"
                        "QScrollBar::sub-line:vertical{background:transparent;}"
                        "QScrollBar::add-line:vertical{background:transparent;}"
                        );
    ui->label->setStyleSheet("QLabel#label{padding-left:15px;color:rgb(102,102,102);}");
    ui->listWidget->setStyleSheet("QListWidget{border:1px;background:blue;border-radius:5px;}"
                                  "QListWidget::Item{ background:white; height:60px;}"
                                  "QListWidget::Item:hover{background:rgb(246,246,247);}"
                                  );

    setListItem(); //设置样式  ，这里也可以根据搜索的东西，反馈数据

}

SearchForm::~SearchForm()
{
    delete ui;
}

void SearchForm::setListItem()
{
    //这里添加
    QListWidgetItem * newWidget = new QListWidgetItem(ui->listWidget);
    SearchItem * addNew = new SearchItem();
    addNew->setLabNumColor(false);  //设置红色
    ui->listWidget->setItemWidget(newWidget,addNew);

    QStringList num;
    for (int i =0; i<21; i++) {
        num.append(QString::number(i+1));
    }

    QStringList music = {"Lover Song","消愁","请笃信一个梦","摆脱",
                        "不灭的心","深夜一角","假摔","海底",
                        "乌鸦","春风十里","车站","姜子牙",
                        "能解答一切的答案","我的那些年","起风了","一荤一素",
                        "乌鸦","深夜一角","摆脱","消愁"};

    for (int i = 0;i<20;i++) {
        QListWidgetItem * newWidget = new QListWidgetItem(ui->listWidget);
        SearchItem * addNew = new SearchItem();
        addNew->setLabNumText(num[i+1]);
        addNew->setLabNameText(music[i]);
        addNew->setLabrankingText(QString::number(1245321-i*26));
        if(i<2)
        {
            addNew->setLabNumColor(false);  //设置红色
        }
        else {
            addNew->setLabNumColor(true);  //设置黑色
        }
        ui->listWidget->setItemWidget(newWidget,addNew);
    }

}
