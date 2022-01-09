#include "tcpsocket.h"

TcpSocket::TcpSocket(QObject *parent) : QTcpSocket(parent)
{
    qRegisterMetaType<qintptr>("qintptr");
    connect(this,&TcpSocket::readyRead,[=](){
       ReceivedMessage();
    });
    connect(this,&TcpSocket::disconnected,[=]()
    {
        qDebug() << "disconnect" ;
        this->deleteLater();
    });
}

void TcpSocket::SendMessageToServer(QByteArray message)
{
//    QMutexLocker locker(&mutex);
    if(message.length()>0)
    {
        write(message);
        //qDebug()<<"发送成功";
    }
}

void TcpSocket::ReceivedMessage()
{

    //qDebug()<<"Myreceive";
    QByteArray datagram;
    if(bytesAvailable()>0)
    {
        datagram.append(this->readAll());
    }
    //qDebug()<<datagram;
    emit SendAByteArray(datagram);
}
