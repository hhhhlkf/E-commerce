#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include "tcpsocket.h"
#include <QList>
#include <QMap>
#include "threadhandle.h"
//tcp客户端类，对scoket进行统一管理
class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr,int port=0);
    void incomingConnection(qintptr handle);
signals:
    void addChatRoom(qintptr socketDescriptor);
    void sglSendFromServer(QByteArray message,qintptr socketDiscriptor);
    void sglRecivedReomClient(QByteArray message,qintptr socketDiscriptor);
    void sendDisconnectedSignal(qintptr socketDiscriptor);
public slots:
    void dataSendFromServer(QByteArray message,qintptr socketDiscriptor);
    void dataRecivedFromClient(QByteArray message,qintptr socketDiscriptor);
    void disconnectChoice(qintptr SocketDescriptor, const quint16 peerPort, QThread *currentThread);

private:
   QMap<qintptr,tcpSocket*>socketPool;
protected:

};

#endif // TCPSERVER_H
