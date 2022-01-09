#ifndef PERSONFORM_H
#define PERSONFORM_H
#include <QWidget>
#include <QString>
#include <QIcon>
#include "objects.h"
#define LOCK 0
#define UNLOCK 1
namespace Ui {
class personForm;
}
//个人信息页面
class personForm : public QWidget
{
    Q_OBJECT
protected:
    void leaveEvent(QEvent *event);
public:
    explicit personForm(QWidget *parent = nullptr);
    ~personForm();


public slots:
    void setClient(Client*client);
private:
    Ui::personForm *ui;
    bool flag;
    static QString lockurl;
    static QString unlockurl;
    Client*client;
signals:
    void sglUpdateClient(Client*client);
    void exitApp();
    void setClientPortrait(int choose);

private slots:
    void on_pushButton_myquit_clicked();
};

#endif // PERSONFORM_H
