#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include <QWidget>
#include "searchitem.h"
namespace Ui {
class SearchForm;
}

class SearchForm : public QWidget
{
    Q_OBJECT

public:
    explicit SearchForm(QWidget *parent = nullptr);
    ~SearchForm();
    void setListItem();
private:
    Ui::SearchForm *ui;
};

#endif // SEARCHFORM_H
