#include "tcpsocket.h"
int num =0;
tcpSocket::tcpSocket(QTcpSocket *parent) : QTcpSocket(parent)
{
    qRegisterMetaType<qintptr>("qintptr");
    connect(this,&tcpSocket::readyRead,[=](){
       dataRecived();
    });
    connect(this,&tcpSocket::disconnected,[=]()
    {
//        qDebug() << "My socket : disconnect" ;
//        qDebug()<<"1.socketDescriptor is "<<socketDescriptor();
        emit sockDisConnect(socketDiscriptor,this->peerPort(),QThread::currentThread());//发送断开连接的用户信息
        //this->deleteLater();
    });
}

void tcpSocket::dataSend(QByteArray message,qintptr socketDiscriptor)
{
//    qDebug()<<"My socket:"<<socketDiscriptor << num++;
    //qDebug()<<message;
//    qDebug()<<this->socketDescriptor()<<"好家伙"<<socketDiscriptor;
    if(socketDiscriptor==this->socketDescriptor())
    {
        if(message.length()>0)
        write(message);
    }
}

void tcpSocket::dataRecived()
{

    while(bytesAvailable()>0)
    {
        QByteArray datagram;
        datagram = readAll();
        //qDebug()<<"11111111111111111111111111111111111111111111111111111";
        emit sendByteArray(datagram,this->socketDescriptor());
    }

}
