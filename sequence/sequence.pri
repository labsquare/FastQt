INCLUDEPATH+=$$PWD

HEADERS += \
    $$PWD/sequence.h \
    $$PWD/abstractsequencereader.h \
    $$PWD/fastqreader.h \
    $$PWD/phredencoding.h \
    $$PWD/bamreader.h

SOURCES += \
    $$PWD/abstractsequencereader.cpp \
    $$PWD/fastqreader.cpp \
    $$PWD/phredencoding.cpp \
    $$PWD/sequence.cpp \
    $$PWD/bamreader.cpp
