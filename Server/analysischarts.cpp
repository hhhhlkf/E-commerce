#include "analysischarts.h"
#include "ui_analysischarts.h"
analysisCharts::analysisCharts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::analysisCharts)
{
    ui->setupUi(this);
    ui->tabselectWidget1->setTabIcon(0,QIcon("./images/Pie.svg"));
    ui->tabselectWidget1->setTabIcon(1,QIcon("./images/Line.svg"));
    ui->radioButton->setChecked(true);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    initConnect();
    initPieChart();
    initLineChart();
}

analysisCharts::~analysisCharts()
{
    delete ui;
}

void analysisCharts::initData(QList<Order*>orderList)
{
    QStringList headerList;
    OrderList.clear();
    OrderList = orderList;
    qDebug()<<"orderList的大小"<<orderList.size();
    theModel = new QStandardItemModel(orderList.size(),11,this);
    theModel->setColumnCount(11);
    headerList<<"订单编号"<<"物品名称"<<"物品个数"<<"物品种类"<<"物品编号"<<"花费金额"<<"消费时间"<<"客户姓名"<<"客户编号"<<"购物判断"<<"隐藏判断";
    theModel->setHorizontalHeaderLabels(headerList);
    for(int i=0;i<orderList.size();i++)
    {
            QStandardItem* aItem = new QStandardItem(QString::number(orderList[i]->getOrderId()));
            aItem->setTextAlignment(Qt::AlignHCenter| Qt::AlignVCenter);

            theModel->setItem(i,0,aItem);

            aItem = new QStandardItem(orderList[i]->getOrderProductName());
            aItem->setTextAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
            theModel->setItem(i,1,aItem);

            aItem = new QStandardItem(QString::number(orderList[i]->getOrderProductNum()));
            aItem->setTextAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
            theModel->setItem(i,2,aItem);

            aItem = new QStandardItem(orderList[i]->getOrderProductStyle());
            aItem->setTextAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
            theModel->setItem(i,3,aItem);

            aItem = new QStandardItem(QString::number(orderList[i]->getOrderProductId()));
            aItem->setTextAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
            theModel->setItem(i,4,aItem);

            aItem = new QStandardItem(orderList[i]->getOrderCost());
            aItem->setTextAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
            theModel->setItem(i,5,aItem);

            aItem = new QStandardItem(orderList[i]->getOrderTime().toString());
            aItem->setTextAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
            theModel->setItem(i,6,aItem);

            aItem = new QStandardItem(orderList[i]->getOrderClient());
            aItem->setTextAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
            theModel->setItem(i,7,aItem);

            aItem = new QStandardItem(QString::number(orderList[i]->getOrderClientId()));
            aItem->setTextAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
            theModel->setItem(i,8,aItem);

            aItem = new QStandardItem(QString::number(orderList[i]->getOrderCheck()));
            aItem->setTextAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
            theModel->setItem(i,9,aItem);

            aItem = new QStandardItem(QString::number(orderList[i]->getOrderHide()));
            aItem->setTextAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
            theModel->setItem(i,10,aItem);
            if((i+1)%2==0)
            for(int k =0 ;k < 11; k++)
            {
                theModel->item(i,k)->setBackground(QColor(233,245,252));
                theModel->item(i,k)->setEnabled(false);
            }
            else
            {
                for(int k =0 ;k < 11; k++)
                {
                    theModel->item(i,k)->setEnabled(false);
                }
            }
    }
    ui->tableView->setModel(theModel);
}

void analysisCharts::initConnect()
{
    connect(ui->radioButton,&QRadioButton::clicked,[=]()
    {
       ui->lineEdit->setEnabled(false);
       ui->lineEdit_2->setEnabled(false);
       QList<QString>strList;
       for(int i=0;i<OrderList.size();i++)
       {
              QString date = OrderList[i]->getOrderTime().toString();
              date.replace("月","");
              QStringList list = date.split(" ");
              if(list[1].toInt()<10)list[1]="0"+list[1];
              if(list[2].toInt()<10)list[2]="0"+list[2];
              QString DateShow = list[4]+list[1]+list[2];
              bool flag =true;
              for(int i=0;i<strList.size();i++)
              {
                  if(strList[i] == DateShow)
                  {flag = false;break;}
              }
              if(flag)
              {
                  strList.append(DateShow);
                  ui->comboBoxbbegin->addItem(DateShow);
                  ui->comboBoxafter->addItem(DateShow);
              }
       }
    });
    connect(ui->radioButton_2,&QRadioButton::clicked,[=]()
    {
       ui->lineEdit->setEnabled(true);
       ui->lineEdit_2->setEnabled(true);
       ui->comboBoxafter->clear();
       ui->comboBoxbbegin->clear();
    });
    connect(ui->pushButton_search,&QPushButton::clicked,[=]()
    {
        QString lineEdit = ui->lineEdit->text();
        emit refreshChart(lineEdit);
    });
    connect(ui->pushButton_search_2,&QPushButton::clicked,[=]()
    {
        QString lineEdit = ui->lineEdit_2->text();
        emit refreshChart(lineEdit);
    });
    connect(ui->crashBtn,&QPushButton::clicked,[=]()
    {
        initData(OrderList);
        qDebug()<<"OrderList的大小"<<OrderList.size();
        ui->comboBoxafter->clear();
        ui->comboBoxbbegin->clear();
        QList<QString>strList;
        for(int i=0;i<OrderList.size();i++)
        {
               QString date = OrderList[i]->getOrderTime().toString();
               date.replace("月","");
               QStringList list = date.split(" ");
               if(list[1].toInt()<10)list[1]="0"+list[1];
               if(list[2].toInt()<10)list[2]="0"+list[2];
               QString DateShow = list[4]+list[1]+list[2];
               bool flag =true;
               for(int i=0;i<strList.size();i++)
               {
                   if(strList[i] == DateShow)
                   {flag = false;break;}
               }
               if(flag)
               {
                   strList.append(DateShow);
                   ui->comboBoxbbegin->addItem(DateShow);
                   ui->comboBoxafter->addItem(DateShow);
               }
        }
    });
}

void analysisCharts::initPieChart()
{
    QChart * chart = new QChart();
    chart->setTitle(" Piechart演示");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->chartViewBar->setChart(chart);
    ui->chartViewBar->setRenderHint(QPainter::Antialiasing);
}

void analysisCharts::buildPieChart()
{
    QChart *chart =ui->chartViewBar->chart(); //获取chart对象
    chart->removeAllSeries(); //删除所有序列
    QString begin = ui->comboBoxbbegin->currentText();
    QString after = ui->comboBoxafter->currentText();
    QString Begin = begin.mid(4,2);
    QString After = after.mid(4,2);
    qDebug()<<Begin<<After;
    int Be = Begin.toInt();int Af = After.toInt();
    if(Be>Af){int a =Be;Be = Af;Af = a;}
    QPieSeries * series = new QPieSeries();
    series->setHoleSize(ui->spinPieSize->value()*0.3);
    float* numList = new float[Af-Be+1];
//    qreal sumCost=0;
    for(int i=Be;i<=Af;i++)
    {
        numList[i-Be]=0;
//        qDebug()<<numList[0];
        for(int j=0;j<OrderList.size();j++)
        {
            QStringList strList = OrderList[j]->getOrderTime().toString().split(" ");
            if(strList[1].replace("月","").toInt()==i)
            {
                 float num=OrderList[j]->getOrderCost().toFloat()+numList[i-Be];
//                 qDebug()<<OrderList[j]->getOrderCost().toFloat();
                 numList[i-Be]=num;
                 qDebug()<<numList[i-Be];
            }
        }
//        sumCost+=(qreal)numList[i-Be];
//        qDebug()<<numList[i-Be];
        series->append(QString::number(i)+"月消费额",(qreal)numList[i-Be]);
    }
    QPieSlice * slice;
    for(int i=0;i<Af-Be+1;i++)
    {
        slice = series->slices().at(i);
        qDebug()<<slice->percentage();
        slice->setLabel(slice->label()+QString::asprintf(":%.0f￥,%.1f%%",slice->value(),slice->percentage()*100));
        connect(slice, SIGNAL(hovered(bool)),
                this, SLOT(onPieslicehighlight(bool)));
    }
    slice->setExploded(true); //最后一个设置为exploded
    chart->addSeries(series);
    series->setLabelsVisible(true); //只影响当前的slices，必须添加完slice之后再设置
 //添加饼图序列
//    chart->setTitle("Piechart----"+);
    if(!ui->radioButton->isChecked())
    {
        if(ui->comboBox->currentIndex()==0)
            chart->setTitle("关于"+OrderList[0]->getOrderProductName()+"营销情况饼状图");
        else
            chart->setTitle("关于"+OrderList[0]->getOrderClient()+"购买情况饼状图");
    }
    else
    {
        if(ui->comboBox->currentIndex()==0)
        chart->setTitle("所有商品的营销情况饼图");
        else
            chart->setTitle("所有客户的购买情况饼图");

    }
    chart->legend()->setVisible(true); //图例
    chart->legend()->setAlignment(Qt::AlignRight);//Qt::AlignRight
}

void analysisCharts::initLineChart()
{
    QChart *chart = new QChart(); //创建chart
    chart->setTitle("Barchart演示");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->chartViewBar_2->setChart(chart); //为ChartView设置chart
    ui->chartViewBar_2->setRenderHint(QPainter::Antialiasing);
}

void analysisCharts::buildLineChart()
{
    QChart *chart =ui->chartViewBar_2->chart(); //获取ChartView关联的chart
    chart->removeAllSeries(); //删除所有序列
    chart->removeAxis(chart->axisX()); //删除坐标轴
    chart->removeAxis(chart->axisY()); //删除坐标轴
    QBarSet * setCost;QBarSet * setNum;
    if(ui->comboBox->currentIndex()==0)
    {
        setCost = new QBarSet("商品钱数");
        setNum = new QBarSet("购买数量");
    }
    else
    {
        setCost = new QBarSet("商品购买量");
        setNum = new QBarSet("购买数量");
    }
    QLineSeries * Line = new QLineSeries();
    Line->setName("商品购买量");
    QPen pen;
    pen.setColor(Qt::gray);
    pen.setWidth(2);
    Line->setPen(pen);
    QString begin = ui->comboBoxbbegin->currentText();
    QString after = ui->comboBoxafter->currentText();
    QString Begin = begin.mid(4,2);
    QString After = after.mid(4,2);
    qDebug()<<Begin<<After;
    int Be = Begin.toInt();int Af = After.toInt();
    float* numList = new float[Af-Be+1];
    int * buyNum = new int[Af-Be+1];
//    qreal sumCost=0;
    for(int i=Be;i<=Af;i++)
    {
        numList[i-Be]=0;
        buyNum[i-Be]=0;
//        qDebug()<<numList[0];
        for(int j=0;j<OrderList.size();j++)
        {
            QStringList strList = OrderList[j]->getOrderTime().toString().split(" ");
            if(strList[1].replace("月","").toInt()==i)
            {
                 float num=OrderList[j]->getOrderCost().toFloat()+numList[i-Be];
                 int bnum = OrderList[j]->getOrderProductNum()+buyNum[i-Be];
                 buyNum[i-Be]=bnum;
                 numList[i-Be]=num;
//                 qDebug()<<numList[i-Be];
            }
        }
        setCost->append(numList[i-Be]/100);
        setNum->append(buyNum[i-Be]);
        Line->append(QPointF(i-Be,numList[i-Be]/100));
    }
    QBarSeries *series = new QBarSeries();
    series->append(setCost);
    series->append(setNum);
    chart->addSeries(series); //添加柱状图序列
    chart->addSeries(Line); //添加折线图序列
    QStringList categories;
    for (int i=Be;i<=Af;i++) {
        categories<<QString::number(i)+"月";
    }
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories); //添加横坐标文字列表
    chart->setAxisX(axisX, series); //设置横坐标
    chart->setAxisX(axisX, Line);//设置横坐标
    axisX->setRange(categories.at(0), categories.at(categories.count()-1)); //这只坐标轴范围
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-10, 100);
    if(ui->comboBox->currentIndex()==0)
    axisY->setTitleText("货物购买数量/货物购买钱数(每100￥)");
    else
    axisY->setTitleText("顾客购买数量/顾客购买钱数(每100￥)");
    axisY->setTickCount(12);//11
    axisY->setLabelFormat("%.0f"); //标签格式
//    axisY->setGridLineVisible(false);
//    axisY->setMinorTickCount(4);
    chart->setAxisY(axisY, series); //为
    chart->setAxisY(axisY, Line);
    chart->legend()->setVisible(true); //显示图例
    chart->legend()->setAlignment(Qt::AlignBottom); //图例显示在下方

}

void analysisCharts::on_cBoxTheme_currentIndexChanged(int index)
{
    ui->chartViewBar->chart()->setTheme(QChart::ChartTheme(index));
}

void analysisCharts::on_btnDrawPieChart_clicked()
{
    buildPieChart();
}

void analysisCharts::onPieslicehighlight(bool show)
{
    QPieSlice *slice;
    slice=(QPieSlice *)sender();
//    slice->setLabelVisible(show);
    slice->setExploded(show);
}

void analysisCharts::on_spinPieSize_textChanged(const QString &arg1)
{
    QPieSeries  *series;
    series=(QPieSeries*)ui->chartViewBar->chart()->series().at(0);
    series->setPieSize(arg1.toDouble());
}

void analysisCharts::on_btnDrawPieChart_2_clicked()
{
    buildLineChart();
}



void analysisCharts::on_cBoxTheme_2_currentIndexChanged(int index)
{
    ui->chartViewBar_2->chart()->setTheme(QChart::ChartTheme(index));
}

void analysisCharts::on_spinPieSize_2_valueChanged(double arg1)
{
    QLineSeries * series;
    series=(QLineSeries*)ui->chartViewBar_2->chart()->series().at(1);
    if(arg1 ==1)
    series->setPointsVisible(true);
    else series->setPointsVisible(false);
}
