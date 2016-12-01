#include "mainwindow.h"
#include <QApplication>
#include <quazip/quagzipfile.h>
#include "fastqreader.h"

#include "sequence.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<Sequence>();

    Sequence A;
    A.setSequence("AAAA");

    MainWindow win;

    win.show();


    return a.exec();
}
