#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <QMutex>
#include <QObject>
#include <QTcpSocket>
//socket编程相关
class TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpSocket(QObject *parent = nullptr);
    QMutex mutex;
public slots:
    void SendMessageToServer(QByteArray message);
    void ReceivedMessage();
signals:
    void SendAByteArray(QByteArray datagram);
};

#endif // TCPSOCKET_H
