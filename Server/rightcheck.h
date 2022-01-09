#ifndef RIGHTCHECK_H
#define RIGHTCHECK_H

#include <QWidget>
//
namespace Ui {
class RightCheck;
}
class RightCheck : public QWidget
{
    Q_OBJECT

public:
    explicit RightCheck(QWidget *parent = nullptr);
    ~RightCheck();

private slots:
    void on_pushButton_myquit_clicked();

private:
    Ui::RightCheck *ui;

Q_SIGNALS:
    void DelSelectItem();
};

#endif // RIGHTCHECK_H
