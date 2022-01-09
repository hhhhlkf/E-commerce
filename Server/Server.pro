QT       += core gui
QT	+= multimedia
QT       += network
QT       += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
LIBS+= D:\Qt\Qt5.14.2\Tools\mingw730_64\x86_64-w64-mingw32\lib\libws2_32.a
DESTDIR = $$PWD/bin
CONFIG += c++11
RC_ICONS = $$PWD/bin/images/Electricalshop.ico
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    analysischarts.cpp \
    chatlistitem.cpp \
    chatmessage/qnchatmessage.cpp \
    chatroom.cpp \
    main.cpp \
    allmain.cpp \
    newselectitem.cpp \
    notification/createnotification.cpp \
    objects.cpp \
    objecttojson.cpp \
    onsaleitem.cpp \
    rightcheck.cpp \
    searchform.cpp \
    searchitem.cpp \
    soapnew/soapC.cpp \
    soapnew/soapClient.cpp \
    soapnew/stdsoap2.cpp \
    tcpserver.cpp \
    tcpsocket.cpp \
    threadhandle.cpp

HEADERS += \
    allmain.h \
    analysischarts.h \
    chatlistitem.h \
    chatmessage/qnchatmessage.h \
    chatroom.h \
    loadfileqss.h \
    newselectitem.h \
    notification/createnotification.h \
    objects.h \
    objecttojson.h \
    onsaleitem.h \
    rightcheck.h \
    searchform.h \
    searchitem.h \
    soapnew/soapH.h \
    soapnew/soapStub.h \
    soapnew/stdsoap2.h \
    stringtrans.h \
    tcpserver.h \
    tcpsocket.h \
    threadhandle.h

FORMS += \
    allmain.ui \
    analysischarts.ui \
    chatlistitem.ui \
    chatroom.ui \
    newselectitem.ui \
    onsaleitem.ui \
    rightcheck.ui \
    searchform.ui \
    searchitem.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    soapnew/info.md
