#include "signinform.h"
#include "ui_signinform.h"

SignInForm::SignInForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignInForm)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    connect(ui->closeBtn,&QPushButton::clicked,[=](){
       this->close();
    });
    connect(ui->minisizeBtn,&QPushButton::clicked,[=](){
       this->showMinimized();
    });
    socket=nullptr;
}

SignInForm::~SignInForm()
{
    delete ui;
}

TcpSocket *SignInForm::getSocket() const
{
    return socket;
}

void SignInForm::setSocket(TcpSocket *value)
{
    if(socket==nullptr)
    socket = value;
}

Client *SignInForm::getClient() const
{
    return client;
}

void SignInForm::setClient(Client *value)
{
    client = value;
}

void SignInForm::getSelect(QByteArray array)
{
    QString signal = ObjectToJson::parseSignal(array);
    if(signal=="1000010"){
        QList<Client*>clientList = ObjectToJson::parseClient(array);
        if(clientList.size()!=0){
            client = clientList[0];
            this->hide();
            emit sendMessageOut(socket,client);
        }
    }
}

void SignInForm::mousePressEvent(QMouseEvent *event)
{
    int Backwidget = ui->backwidget->height();
    if(event->y() <Backwidget)
    {
        last = event->globalPos(); //获取到按压的位置
    }
}

void SignInForm::mouseMoveEvent(QMouseEvent *event)
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

void SignInForm::mouseReleaseEvent(QMouseEvent *event)
{
    int Backwidget = ui->backwidget->height();
    if(event->y() <Backwidget)
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        this->move(this->x()+dx,this->y()+dy);
    }
}

void SignInForm::on_createBtn_clicked()
{
    if(socket==nullptr)
    {
        socket = new TcpSocket;
    }
    QString server_IP= "127.0.0.1";
    int port =8020;
    socket->connectToHost(server_IP,port);
    connect(socket,&TcpSocket::SendAByteArray,[=](QByteArray message){
        getSelect(message);
    });
    client = new Client;
    if(ui->NameEdit->text()!="")
    client->setClientName(ui->NameEdit->text());
    if(ui->PasswordEdit->text()!=""){
        client->setClientPwd(ui->PasswordEdit->text());
    }
    if(ui->PhoneNumEdit->text()!=""){
        client->setClientPhone(ui->PhoneNumEdit->text());
    }
    if(ui->EmailEdit->text()!=""){
        client->setClientEmail(ui->EmailEdit->text());
    }
    QList<Client*>clientList;
    clientList.append(client);
    QJsonObject object;
    ObjectToJson::integrateClientList(object,clientList);
    ObjectToJson::addSignal(object,"1000010");
    QByteArray array =ObjectToJson::changeJson(object);
    socket->SendMessageToServer(array);
}



void SignInForm::on_returnLogBtn_clicked()
{
      emit returnToLogIn();
}
