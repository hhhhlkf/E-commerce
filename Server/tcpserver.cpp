#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent,int port) : QTcpServer(parent)
{
    listen(QHostAddress::Any,port);
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    tcpSocket * socket = new tcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    qDebug()<<socket->socketDescriptor();//
    socket->socketDiscriptor=socketDescriptor;
    auto thread =ThreadHandle::getClass().getThread();
    connect(socket,SIGNAL(sendByteArray(QByteArray,qintptr)),this,SLOT(dataRecivedFromClient(QByteArray,qintptr)));
    connect(socket,SIGNAL(sockDisConnect(qintptr, const quint16 , QThread *)),this,SLOT(disconnectChoice(qintptr, const quint16 , QThread *)));
    connect(this,SIGNAL(sglSendFromServer(QByteArray,qintptr)),socket,SLOT(dataSend(QByteArray,qintptr)));
    socket->moveToThread(thread);
    socketPool.insert(socketDescriptor,socket);
}

void TcpServer::dataSendFromServer(QByteArray message, qintptr socketDiscriptor)
{
    qDebug()<<"信号传递";//
    emit sglSendFromServer(message,socketDiscriptor);
}

void TcpServer::dataRecivedFromClient(QByteArray message, qintptr socketDiscriptor)
{
    emit sglRecivedReomClient(message,socketDiscriptor);
}

void TcpServer::disconnectChoice(qintptr SocketDescriptor, const quint16 peerPort, QThread *currentThread)
{
    Q_UNUSED(peerPort);
    tcpSocket* socket = socketPool[SocketDescriptor];
    socketPool.remove(SocketDescriptor);
    socket->close();
    socket->deleteLater();
    ThreadHandle::getClass().removeThread(currentThread);
    emit sendDisconnectedSignal(SocketDescriptor);
}



