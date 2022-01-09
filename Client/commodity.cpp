#include "commodity.h"
#include "ui_commodity.h"

Commodity::Commodity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Commodity)
{
    ui->setupUi(this);
    num = 0;
    ui->textEdit->setText(QString::number(num));

    isDigital = str.contains(QRegExp("^\\d+$"));
    if(isDigital)
    {
        QErrorMessage* error = new QErrorMessage();
        error->setWindowTitle(tr("错误报告"));
        error->showMessage(tr("出现非法字符！"));
        ui->textEdit->clear();
    }
    ui->CommodityName->setAlignment(Qt::AlignCenter);
    ui->CostText->setAlignment(Qt::AlignCenter);
    isDiscount = false;
}

Commodity::~Commodity()
{
    delete ui;
}

void Commodity::setPic(QString url)
{
    QString str="QWidget{border-image:url("+url+");}";
    ui->widUPic->setStyleSheet(str);
}

void Commodity::setCommodityName(QString name)
{
    ui->CommodityName->setText(name);
}

void Commodity::setCommodityPrice(QString Price)
{
    if(isDiscount){
       ui->CostText->setStyleSheet("QLineEdit#lineEdit{background: rgb(232, 227, 202);border-radius: 10px;padding: 0px 0px 0px 30px;font-size: 17;font-family:微软雅黑;color: rgb(255,0,0);padding-left: 18px;}");
    }
    ui->CostText->setText(Price+" ￥");
}


void Commodity::setCommodityNum(int number)
{
    ui->textEdit->setText(QString::number(number));
    connect(ui->plusBtn,&QPushButton::clicked,[=]()
    {
        str = ui->textEdit->toPlainText();
        isDigital = str.contains(QRegExp("^\\d+$"));
        if(!isDigital)
        {
            QErrorMessage* error = new QErrorMessage();
            error->setWindowTitle(tr("错误报告"));
            error->showMessage(tr("出现非法字符！"));
        }
        num = str.toInt();
        num++;
        ui->textEdit->clear();
        ui->textEdit->setText(QString::number(num));
    });
    connect(ui->minusBtn,&QPushButton::clicked,[=]()
    {
        str = ui->textEdit->toPlainText();
        isDigital = str.contains(QRegExp("^\\d+$"));
        if(!isDigital)
        {
            QErrorMessage* error = new QErrorMessage();
            error->setWindowTitle(tr("错误报告"));
            error->showMessage(tr("出现非法字符！"));
        }
        num = str.toInt();
        if(num>0)
        num--;
        ui->textEdit->clear();
        ui->textEdit->setText(QString::number(num));
    });
}

void Commodity::setCommodityId(int id)
{
    ui->lineEdit->setText(QString::number(id));
}

void Commodity::setCommodityType(QString type)
{
    ui->lineEdit_2->setText(type);
}

void Commodity::setTypeList(QList<ProductType *> TypeList)
{
    for (int i = 0;i<TypeList.size();i++) {
        QListWidgetItem * item = new QListWidgetItem(ui->listWidget);
        item->setText(TypeList[i]->getTypeName());
        connect(ui->listWidget,&QListWidget::currentRowChanged,[=](int Rownum){
           Q_UNUSED(Rownum);
           ui->lineEdit_2->setText(ui->listWidget->currentItem()->text());
        });
        ui->listWidget->addItem(item);
    }
}

void Commodity::setDiscount(bool flag)
{
    isDiscount = flag;
}



void Commodity::on_ptnBuy_clicked()
{

   emit  createOrder(-1,ui->lineEdit->text().toInt(),ui->CommodityName->text(),ui->lineEdit_2->text(),ui->textEdit->toPlainText().toInt(),Price);
}

void Commodity::on_btnBuy_clicked()
{
    emit  createOrder(1,ui->lineEdit->text().toInt(),ui->CommodityName->text(),ui->lineEdit_2->text(),ui->textEdit->toPlainText().toInt(),Price);
}

float Commodity::getPrice() const
{
    return Price;
}

void Commodity::setPrice(float value)
{
    Price = value;
}
