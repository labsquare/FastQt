#-------------------------------------------------
#
# Project created by QtCreator 2016-10-27T15:00:28
#
#-------------------------------------------------
QT       += core gui concurrent charts
#QMAKE_CXXFLAGS  += -Ofast

# METHOD 1 : If KArchive is not installed as a Qt Module then copy to your Qt installation :
#exemple
#cp /usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KArchive.pri  ~/path/to/Qt/5.7/gcc_64/mkspecs/modules

#QT +=  KArchive

# METHOD 2 : Otherwise link it as a common library
unix {
INCLUDEPATH += "/usr/include/KF5/KArchive"
LIBS +=  -L"/usr/lib"  -lKF5Archive
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = fastqt
TEMPLATE = app

# Installation
target.path  = /usr/local/bin
desktop.path = /usr/share/applications
desktop.files += fastqt.desktop
icons.path = /usr/share/icons/hicolor/48x48/apps
icons.files += fastqt.png

INSTALLS += target desktop icons

SOURCES += main.cpp
include("sequence/sequence.pri")
include("analysis/analysis.pri")
include("ui/ui.pri")
include("model/model.pri")
include("utils/utils.pri")
include("QFontIcon/QFontIcon.pri")

RESOURCES += \
    resources.qrc


TRANSLATIONS = fastqc_fr.ts


