#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QThread>
//同Client
class tcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit tcpSocket(QTcpSocket *parent = nullptr);
    void dataRecived();
    qintptr socketDiscriptor;
signals:
    void sockDisConnect(qintptr,const quint16, QThread *);//NOTE:断开连接的用户信息，此信号必须发出！线程管理类根据信号计数的
    void sendByteArray(QByteArray,qintptr);
public slots:
    void dataSend(QByteArray,qintptr);
};

#endif // TCPSOCKET_H
