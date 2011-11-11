#-------------------------------------------------
#
# Project created by QtCreator 2011-10-24T13:30:13
#
#-------------------------------------------------

QT       += core gui network

TARGET = Karte
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    loginwidget.cpp \
    checkoutwidget.cpp \
    flowlayout.cpp \
    rechargerwidget.cpp \
    kmodelproduct.cpp \
    kmodelcart.cpp \
    protocol/kprotocollinereceiver.cpp \
    protocol/kprotocoljsonreceiver.cpp \
    user.cpp

HEADERS  += mainwindow.h \
    loginwidget.h \
    checkoutwidget.h \
    flowlayout.h \
    kmodelproduct.h \
    kmodelcart.h \
    rechargerwidget.h \
    protocol/kprotocollinereceiver.h \
    protocol/kprotocoljsonreceiver.h \
    user.h

RESOURCES += \
    ssl.qrc

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += QJson
