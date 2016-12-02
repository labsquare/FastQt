#-------------------------------------------------
#
# Project created by QtCreator 2016-10-27T15:00:28
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

unix{
LIBS+=-lz
LIBS+=-lquazip5
}


TARGET = FastQt
TEMPLATE = app


#        mainwindow.cpp \
#    abstractanalysewidget.cpp \
#    mainanalysewidget.cpp \
#    statanalysewidget.cpp \
#    seqqualityanalysewidget.cpp \
#    fastqprocess.cpp \
#    fastqreader.cpp \
SOURCES += main.cpp\
    sequence.cpp \
    abstractsequencereader.cpp \
    fastqreader.cpp \
    mainwindow.cpp \
    mainanalysewidget.cpp \
    abstractanalysewidget.cpp \
    statanalysewidget.cpp \
    analysisrunner.cpp \
    analysis.cpp \
    basicstatsanalysis.cpp

#HEADERS  += mainwindow.h \
#    abstractanalysewidget.h \
#    mainanalysewidget.h \
#    statanalysewidget.h \
#    seqqualityanalysewidget.h \
#    fastqprocess.h \
#    fastqreader.h \


HEADERS =    sequence.h \
    abstractsequencereader.h \
    fastqreader.h \
    mainwindow.h \
    mainanalysewidget.h \
    abstractanalysewidget.h \
    statanalysewidget.h \
    analysisrunner.h \
    analysis.h \
    basicstatsanalysis.h

FORMS    += mainwindow.ui
