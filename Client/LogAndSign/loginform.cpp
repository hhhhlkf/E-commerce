#include "loginform.h"
#include "ui_loginform.h"
#include <winsock2.h>
#include <windows.h>
logInForm::logInForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::logInForm)
{
    ui->setupUi(this);
    socket = new TcpSocket;
    //qDebug()<<"my socket1"<<socket;
    connect(socket,&TcpSocket::SendAByteArray,[=](QByteArray message){
        getSelect(message);
    });
    connect(ui->lineName,&QLineEdit::textChanged,[=](){
       ui->wrongEdit2->setText("");
    });
    flag = true;
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    connect(ui->closeBtn,&QPushButton::clicked,[=](){
       this->close();
    });
    connect(ui->minisizeBtn,&QPushButton::clicked,[=](){
       this->showMinimized();
    });
    ui->linePassWord->setEchoMode(QLineEdit::Password);
}

logInForm::~logInForm()
{
    delete ui;
}

TcpSocket *logInForm::getScoket() const
{
    return socket;
}

void logInForm::setScoket(TcpSocket *value)
{
    socket = value;
}

Client *logInForm::getClient() const
{
    return client;
}

void logInForm::setClient(Client *value)
{
    client = value;
}

void logInForm::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
//        QPainter painter(this);
//        painter.fillRect(this->rect(), QColor(255, 255, 255, 255));  //QColor最后一个参数80代表背景的透明度

}

void logInForm::mousePressEvent(QMouseEvent *event)
{
    //获取title widget 的高度，这里固定为60px
    int Backwidget = ui->backwidget->height();
    if(event->y() <Backwidget)
    {
        last = event->globalPos(); //获取到按压的位置
    }
}

void logInForm::mouseMoveEvent(QMouseEvent *event)
{
    int Backwidget = ui->backwidget->height();
    if(event->y() <Backwidget)
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        last = event->globalPos();
        this->move(this->x()+dx,this->y()+dy);
    }
}

void logInForm::mouseReleaseEvent(QMouseEvent *event)
{
    int Backwidget = ui->backwidget->height();
    if(event->y() <Backwidget)
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        this->move(this->x()+dx,this->y()+dy);
    }
}

void logInForm::on_loginbtn_clicked()
{
    if(flag)
    {
        QString server_IP= "127.0.0.1";
        int port =8020;
        socket->connectToHost(server_IP,port);
        client = new Client;
        client->setClientName(ui->lineName->text());
        client->setClientPwd(ui->linePassWord->text());
        flag=false;
    }
    if(client!=nullptr){
        delete client;
        client = new Client;
        client->setClientName(ui->lineName->text());
        client->setClientPwd(ui->linePassWord->text());
        flag=false;
    }
    QList<Client*>clientList;
    clientList.append(client);
    QJsonObject object;
    ObjectToJson::integrateClientList(object,clientList);
    ObjectToJson::addSignal(object,"1000009");
    QByteArray array =ObjectToJson::changeJson(object);
    socket->SendMessageToServer(array);
}

void logInForm::on_signBtn_clicked()
{
    this->hide();
    signInFrom = new SignInForm;
    signInFrom->setSocket(socket);
    signInFrom->show();
    connect(signInFrom,&SignInForm::sendMessageOut,[=](TcpSocket*socket,Client*client1){
        this->socket = socket;
        flag = false;
        client = new Client(*client1);
        ui->lineName->setText(client->getClientName());
        ui->linePassWord->setText(client->getClientPwd());
        signInFrom->hide();
        this->show();
    });
    connect(signInFrom,&SignInForm::returnToLogIn,[=](){
       this->show();
       signInFrom->hide();
    });
}

void logInForm::on_forgetBtn_clicked()
{
    ui->linePassWord->setText("");
    ui->lineName->setText("");
}

void logInForm::getSelect(QByteArray array)
{
    QString signal = ObjectToJson::parseSignal(array);
    if(signal=="1000009"){
        QList<Client*>clientList = ObjectToJson::parseClient(array);
        if(clientList.size()!=0){
            ui->loginbtn->setText("登录成功!");
            client = clientList[0];
            this->hide();
            ui->lineName->clear();
            ui->linePassWord->clear();
            //qDebug()<<"my socket2"<<socket;
            emit sendMessage(client,socket);
        }
        else
            ui->wrongEdit2->setText("密码或账号可能错误!");
    }


}
