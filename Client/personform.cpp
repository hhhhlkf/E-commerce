#include "personform.h"
#include "ui_personform.h"
QString personForm::lockurl = "./images/上锁.svg";
QString personForm::unlockurl = "./images/开锁.svg";
//鼠标离开
void personForm::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->close();


}

personForm::personForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::personForm)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground); //设置样式表
    QString str = "QPushButton{border-image:url("+lockurl+");}";
    ui->reviseBtn->setStyleSheet(str);
    flag = LOCK;
    connect(ui->reviseBtn,&QPushButton::clicked,[=](){
        if(flag==LOCK)
        {
            QString str = "QPushButton{border-image:url("+unlockurl+");}";
            ui->reviseBtn->setStyleSheet(str);
            flag = UNLOCK;
            ui->NameEdit->setDisabled(true);
            ui->PhoneNumEdit->setDisabled(false);
            ui->PasswordEdit->setDisabled(false);
            ui->EmailEdit->setDisabled(false);
            emit setClientPortrait(0);
        }
        else {
            QString str = "QPushButton{border-image:url("+lockurl+");}";
            ui->reviseBtn->setStyleSheet(str);
            flag = LOCK;
            ui->NameEdit->setDisabled(true);
            ui->PhoneNumEdit->setDisabled(true);
            ui->PasswordEdit->setDisabled(true);
            ui->EmailEdit->setDisabled(true);
            client->setClientPwd(ui->PasswordEdit->text());
            client->setClientEmail(ui->EmailEdit->text());
            client->setClientPhone(ui->PhoneNumEdit->text());
            Client* newClient = new Client(*client);
            emit sglUpdateClient(newClient);
            emit setClientPortrait(1);
        }
    });

}

personForm::~personForm()
{
    delete ui;
}


void personForm::setClient(Client *client)
{
    this->client = client;
    ui->NameEdit->setText(client->getClientName());
    ui->PhoneNumEdit->setText(client->getClientPhone());
    ui->PasswordEdit->setText(client->getClientPwd());
    ui->EmailEdit->setText(client->getClientEmail());
    ui->NameEdit->setDisabled(true);
    ui->PhoneNumEdit->setDisabled(true);
    ui->PasswordEdit->setDisabled(true);
    ui->EmailEdit->setDisabled(true);
}

void personForm::on_pushButton_myquit_clicked()
{
    emit exitApp();
}
