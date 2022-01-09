QT       += core gui
QT	+= multimedia
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    LogAndSign/loginform.cpp \
    LogAndSign/signinform.cpp \
    changecolorform.cpp \
    chatmessage/qnchatmessage.cpp \
    commendlistitem.cpp \
    commodity.cpp \
    developerdemo.cpp \
    galleryitem.cpp \
    galleryprivate.cpp \
    main.cpp \
    allmain.cpp \
    newcourieritem.cpp \
    newselectitem.cpp \
    notification/createnotification.cpp \
    objects.cpp \
    objecttojson.cpp \
    personform.cpp \
    picturebutton.cpp \
    pictureitem.cpp \
    pictureview.cpp \
    picturewidget.cpp \
    socket/tcpsocket.cpp

HEADERS += \
    LogAndSign/loginform.h \
    LogAndSign/signinform.h \
    allmain.h \
    changecolorform.h \
    chatmessage/qnchatmessage.h \
    commendlistitem.h \
    commodity.h \
    developerdemo.h \
    galleryitem.h \
    galleryprivate.h \
    loadfileqss.h \
    newcourieritem.h \
    newselectitem.h \
    notification/createnotification.h \
    objects.h \
    objecttojson.h \
    personform.h \
    picturebutton.h \
    pictureitem.h \
    pictureview.h \
    picturewidget.h \
    socket/tcpsocket.h

FORMS += \
    LogAndSign/loginform.ui \
    LogAndSign/signinform.ui \
    allmain.ui \
    changecolorform.ui \
    commendlistitem.ui \
    commodity.ui \
    developerdemo.ui \
    galleryitem.ui \
    newcourieritem.ui \
    newselectitem.ui \
    personform.ui \
    picturewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=
