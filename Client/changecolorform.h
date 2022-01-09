#ifndef CHANGECOLORFORM_H
#define CHANGECOLORFORM_H

#include <QWidget>
//修改界面风格类
namespace Ui {
class ChangeColorForm;
}

class ChangeColorForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeColorForm(QWidget *parent = nullptr);
    ~ChangeColorForm();
protected:
    void leaveEvent(QEvent *event);
private slots:
    void on_ptnRed_clicked();

    void on_ptnBlue_clicked();

    void on_ptnPink_clicked();


    void on_ptnOrange_clicked();

    void on_ptnYellow_clicked();

    void on_ptnGreen_clicked();

private:
    Ui::ChangeColorForm *ui;
};

#endif // CHANGECOLORFORM_H
