#-------------------------------------------------
#
# Project created by QtCreator 2017-04-13T21:31:27
#
#-------------------------------------------------

QT       += testlib
QT       += core gui concurrent charts svg

# Unittest only works on inux

unix {
INCLUDEPATH += "/usr/include/KF5/KArchive"
LIBS +=  -L"/usr/lib"  -lKF5Archive
}

include("../app/sequence/sequence.pri")
include("../app/analysis/analysis.pri")
include("../app/QFontIcon/QFontIcon.pri")
include("../app/utils/utils.pri")
include("../app/model/model.pri")



TARGET = tst_fastqtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_fastqtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
