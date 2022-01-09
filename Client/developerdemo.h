#ifndef DEVELOPERDEMO_H
#define DEVELOPERDEMO_H

#include <QWidget>

namespace Ui {
class DeveloperDemo;
}
//程序版本信息视图
class DeveloperDemo : public QWidget
{
    Q_OBJECT
protected:
    void leaveEvent(QEvent *event);
public:
    explicit DeveloperDemo(QWidget *parent = nullptr);
    ~DeveloperDemo();

private:
    Ui::DeveloperDemo *ui;
};

#endif // DEVELOPERDEMO_H
