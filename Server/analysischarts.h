#ifndef ANALYSISCHARTS_H
#define ANALYSISCHARTS_H
#include "objects.h"
#include <QWidget>
#include <QList>
#include <QtCharts>
#include <QPieSeries>
#include <QPieSlice>
QT_CHARTS_USE_NAMESPACE
namespace Ui {
class analysisCharts;
}
//图表分析界面类
class analysisCharts : public QWidget
{
    Q_OBJECT

public:
    explicit analysisCharts(QWidget *parent = nullptr);
    ~analysisCharts();
    void initData(QList<Order*>orderList);//初始化数据
    void initConnect();
    void initPieChart();//初始化饼状图
    void buildPieChart();//创建饼状图
    void initLineChart();//初始化折现图
    void buildLineChart();//创建折线图
private:

    QStandardItemModel  *theModel;//数据模型
    QList<Order*>OrderList;
//    QChart * chart;

private:
    Ui::analysisCharts *ui;

signals:
    void refreshChart(QString text);

private slots:
    void on_cBoxTheme_currentIndexChanged(int index);
    void on_btnDrawPieChart_clicked();
    void onPieslicehighlight(bool show);
    void on_spinPieSize_textChanged(const QString &arg1);
    void on_btnDrawPieChart_2_clicked();
    void on_cBoxTheme_2_currentIndexChanged(int index);
    void on_spinPieSize_2_valueChanged(double arg1);
};

#endif // ANALYSISCHARTS_H
