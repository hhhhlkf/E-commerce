#ifndef LOADFILEQSS_H
#define LOADFILEQSS_H

#include <QApplication>
#include <QFile>

class LoadFileQss//加载QSS
{
public:
    static void setStyle(const QString& fileName)
    {
        QFile fileQss(fileName);
        fileQss.open(QFile::ReadOnly);
        qApp->setStyleSheet(fileQss.readAll());
        fileQss.close();
    }
};


#endif // LOADFILEQSS_H
