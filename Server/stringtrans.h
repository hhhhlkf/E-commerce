#ifndef STRINGTRANS_H
#define STRINGTRANS_H
#include <QString>
#include <string>
#include <QDateTime>
#include <time.h>
#include <QDebug>
//字符串转换
class StringTrans
{
public:
    static std::string *QString2string(QString QString)
    {
        if(!QString.isNull())
        {
            return new std::string(QString.toStdString());
        }
        else
            return NULL;
    }
    static QString string2QString(std::string* string)
    {
        if(string!=NULL)
        {
             return QString(QString::fromUtf8(string->c_str()));
        }
        else
        return "";
    }
    static time_t* QDateTime2tTime(QDateTime Qtime)
    {
        if(!Qtime.isNull())
        return new time_t(Qtime.toTime_t());
        else
        {
//            qDebug()<<"为空";
             return NULL;
        }

    }
    static QDateTime tTime2QDateTime(time_t* time)
    {
        if(time!=NULL)
        {
            QDateTime Qtime = QDateTime::fromTime_t(*time);
            return Qtime;
        }
        else return QDateTime::currentDateTime();
    }
};

#endif // STRINGTRANS_H
