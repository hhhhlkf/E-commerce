#include "allmain.h"
#include "analysischarts.h"
#include <QApplication>
int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication a(argc, argv);
    LoadFileQss::setStyle("./Allthe.qss");

    AllMain w;
//    analysisCharts w;
    w.show();
    return a.exec();
}
