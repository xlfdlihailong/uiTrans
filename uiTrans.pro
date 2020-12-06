#-------------------------------------------------
#
# vs2013+QT5.5
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = uiTrans
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qlib/qlib.cpp \
    qlib/plib/plib.cpp \
    xtablewidget.cpp

HEADERS  += mainwindow.h \
    xtablewidget.h \
    qlib/qlib.h \
    qlib/plib/plib.h

FORMS    += mainwindow.ui \
    xtablewidget.ui

RESOURCES += \
    xlfd.qrc
