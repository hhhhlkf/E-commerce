#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include <QWidget>
#include "searchitem.h"
#include "objects.h"
#include <QList>
namespace Ui {
class SearchForm;
}
//搜索提示框类
class SearchForm : public QWidget
{
    Q_OBJECT

public:
    explicit SearchForm(QWidget *parent = nullptr);
    ~SearchForm();

public slots:
    void setListItem(QList<Product*>ProductList);
private:
    Ui::SearchForm *ui;
};

#endif // SEARCHFORM_H
