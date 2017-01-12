#-------------------------------------------------
#
# Project created by QtCreator 2016-10-27T15:00:28
#
#-------------------------------------------------

QT       += core gui concurrent charts KArchive
#QMAKE_CXXFLAGS  += -Ofast


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = FastQt
TEMPLATE = app


SOURCES += main.cpp
include("sequence/sequence.pri")
include("analysis/analysis.pri")
include("ui/ui.pri")
include("model/model.pri")
include("utils/utils.pri")

RESOURCES += icons/icons.qrc

