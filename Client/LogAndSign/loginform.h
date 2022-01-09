#ifndef LOGINFORM_H
#define LOGINFORM_H
//登录界面
#include <QWidget>
#include "objects.h"
#include "objecttojson.h"
#include "socket/tcpsocket.h"
#include "LogAndSign/signinform.h"
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
namespace Ui {
class logInForm;
}

class logInForm : public QWidget
{
    Q_OBJECT

public:
    explicit logInForm(QWidget *parent = nullptr);
    ~logInForm();

    TcpSocket *getScoket() const;
    void setScoket(TcpSocket *value);

    Client *getClient() const;
    void setClient(Client *value);
    void paintEvent(QPaintEvent *event);
private slots:
    void on_loginbtn_clicked();

    void on_signBtn_clicked();

    void on_forgetBtn_clicked();
    void getSelect(QByteArray array);
private:
    Ui::logInForm *ui;
    TcpSocket * socket;
    Client*client;
    SignInForm * signInFrom;
    bool flag;
    QPoint last;
protected:
    void mousePressEvent(QMouseEvent* event);
    //鼠标移动
    void mouseMoveEvent(QMouseEvent* event);
    //鼠标释放
    void mouseReleaseEvent(QMouseEvent* event);
signals:
    void sendMessage(Client*client,TcpSocket * socket);
};

#endif // LOGINFORM_H
