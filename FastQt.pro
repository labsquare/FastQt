#-------------------------------------------------
#
# Project created by QtCreator 2016-10-27T15:00:28
#
#-------------------------------------------------

QT       += core gui concurrent charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

unix{
LIBS+=-lz
LIBS+=-lquazip5
}


TARGET = FastQt
TEMPLATE = app


SOURCES += main.cpp

include("sequence/sequence.pri")
include("analysis/analysis.pri")
include("ui/ui.pri")
include("model/model.pri")
