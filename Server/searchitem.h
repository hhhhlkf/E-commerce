#ifndef SEARCHITEM_H
#define SEARCHITEM_H

#include <QWidget>

namespace Ui {
class SearchItem;
}
//搜索提示框界面状态栏
class SearchItem : public QWidget
{
    Q_OBJECT

public:
    explicit SearchItem(QWidget *parent = nullptr);
    ~SearchItem();
    void setLabNumColor(bool bo); //设置样式
    void setLabNumText(QString str);

    void setLabNameText(QString str);
    void setLabrankingText(QString str);
//    void setLabMessageText(QString str);
private:
    Ui::SearchItem *ui;
};

#endif // SEARCHITEM_H
