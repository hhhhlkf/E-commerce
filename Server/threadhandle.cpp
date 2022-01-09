#include "threadhandle.h"
#include <QDebug>
ThreadHandle &ThreadHandle::getClass()
{
    static ThreadHandle th;
    return th;
}

QThread *ThreadHandle::getThread()
{
    if(!initflag)
    {
        for(int i=0;i<1;i++)
        {
            QThread * th = new QThread();
            ThreadPool.insert(th,0);
            th->start();
        }
        initflag=true;
    }
        return findThread();
}

QThread *ThreadHandle::findThread()
{
    auto ite = ThreadPool.begin();
    for(auto it = ThreadPool.begin();it!=ThreadPool.end();it++)
    {
        if(it.value()<ite.value())ite =it;
    }
    if(ite.value()==MAXSIZE)
    {
        QThread * th =new QThread();
        ThreadPool.insert(th,1);
        th->start();
        return th;
    }
    else
    {
        ite.value()++;
        return ite.key();
    }
}

void ThreadHandle::removeThread(QThread*th)
{
    auto t =ThreadPool.find(th);
    if (t != ThreadPool.end())
    {
        t.value()--;
//        qDebug()<<"thread's value is:"<<t.value()<<"Pool's size"<<ThreadPool.size();
        if (t.value() == 0 && ThreadPool.size() > 1)
        {
            ThreadPool.remove(th);
            th->exit();
            th->wait(3000);
            delete th;
        }
    }
}

ThreadHandle::~ThreadHandle()
{

}

void ThreadHandle::clear()
{
    for (auto it  = ThreadPool.begin();it != ThreadPool.end() ;++it)
    {
        it.value()  = 0;
    }
}

ThreadHandle::ThreadHandle()
{
    initflag = false;
}
