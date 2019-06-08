#-------------------------------------------------
#
# Project created by QtCreator 2019-05-24T11:51:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Try
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11


    LIBS += -L"c:/boost_1_47_0/stagegcc/lib/"
    INCLUDEPATH += c:/boost_1_47_0/
    DEPENDPATH += c:/boost_1_47_0/

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    scriptwindow.cpp \
    galeryorimage.cpp \
    newgalery.cpp \
    newphoto.cpp \
    jsonmanager.cpp

HEADERS += \
        mainwindow.h \
    scriptwindow.h \
    galeryorimage.h \
    newgalery.h \
    newphoto.h \
    jsonmanager.h

FORMS += \
        mainwindow.ui \
    scriptwindow.ui \
    galeryorimage.ui \
    newgalery.ui \
    newphoto.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
