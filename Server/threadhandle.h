#ifndef THREADHANDLE_H
#define THREADHANDLE_H
#include <QMap>
#include <QQueue>
#include <QThread>
#include <QHash>
//线程管理类，内置线程池
const int MAXSIZE = 5;
class ThreadHandle
{
public:
     static ThreadHandle& getClass();
     QThread * getThread();
     QThread * findThread();
     void removeThread(QThread*th);
     void clear();
    ~ThreadHandle();
     bool initflag;

private:
    ThreadHandle();
    QHash<QThread*,int>ThreadPool;

};

#endif // THREADHANDLE_H
