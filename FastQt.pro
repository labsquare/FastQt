#-------------------------------------------------
#
# Project created by QtCreator 2016-10-27T15:00:28
#
#-------------------------------------------------
QT       += core gui concurrent charts svg
#QMAKE_CXXFLAGS  += -Ofast
QMAKE_CXXFLAGS += -std=c++11
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT


# METHOD 1 : If KArchive is not installed as a Qt Module then copy to your Qt installation :
#exemple
#cp /usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KArchive.pri  ~/path/to/Qt/5.7/gcc_64/mkspecs/modules

#QT +=  KArchive

# METHOD 2 : Otherwise link it as a common library
unix {
INCLUDEPATH += "/usr/include/KF5/KArchive"
LIBS +=  -L"/usr/lib"  -lKF5Archive
}

win32{
LIBS += -L$$PWD/win32/KArchive/bin -llibKF5Archive.dll
INCLUDEPATH += $$PWD/win32/KArchive/include/KF5/KArchive
RC_FILE = myapp.rc

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
include("cli/cli.pri")

RESOURCES += \
    resources.qrc


TRANSLATIONS = fastqc_fr.ts


