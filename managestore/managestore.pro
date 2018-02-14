#-------------------------------------------------
#
# Project created by QtCreator 2016-12-30T17:17:30
#
#-------------------------------------------------

QT       += core gui sql printsupport webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = managestore
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    changetext.cpp \
    newcreate.cpp \
    login.cpp \
    myweb.cpp

HEADERS  += mainwindow.h \
    changetext.h \
    connect.h \
    newcreate.h \
    login.h \
    myweb.h

FORMS    += mainwindow.ui \
    changetext.ui \
    newcreate.ui \
    login.ui

RC_FILE +=myicon.rc

RESOURCES += \
    res.qrc \
    res2.qrc
