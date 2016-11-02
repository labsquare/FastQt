#-------------------------------------------------
#
# Project created by QtCreator 2016-10-27T15:00:28
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

unix{
LIBS+=-lz
LIBS+=-lquazip5
}


TARGET = FastQt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    abstractanalysewidget.cpp \
    mainanalysewidget.cpp \
    statanalysewidget.cpp \
    seqqualityanalysewidget.cpp \
    fastqprocess.cpp \
    fastqreader.cpp

HEADERS  += mainwindow.h \
    abstractanalysewidget.h \
    mainanalysewidget.h \
    statanalysewidget.h \
    seqqualityanalysewidget.h \
    fastqprocess.h \
    fastqreader.h

FORMS    += mainwindow.ui
