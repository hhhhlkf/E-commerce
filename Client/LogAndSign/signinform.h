#ifndef SIGNINFORM_H
#define SIGNINFORM_H
//注册界面
#include <QWidget>
#include "objects.h"
#include "objecttojson.h"
#include "socket/tcpsocket.h"
#include <QMouseEvent>
namespace Ui {
class SignInForm;
}

class SignInForm : public QWidget
{
    Q_OBJECT

public:
    explicit SignInForm(QWidget *parent = nullptr);
    ~SignInForm();
    TcpSocket *getSocket() const;
    void setSocket(TcpSocket *value);

    Client *getClient() const;
    void setClient(Client *value);
    void getSelect(QByteArray message);
private:
    Ui::SignInForm *ui;
    TcpSocket*socket;
    Client*client;
    QPoint last;
protected:
    void mousePressEvent(QMouseEvent* event);
    //鼠标移动
    void mouseMoveEvent(QMouseEvent* event);
    //鼠标释放
    void mouseReleaseEvent(QMouseEvent* event);
signals:
    void sendMessageOut(TcpSocket*socket,Client*client);
    void returnToLogIn();
private slots:
    void on_createBtn_clicked();
    void on_returnLogBtn_clicked();
};

#endif // SIGNINFORM_H
