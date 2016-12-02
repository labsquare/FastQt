#include "mainwindow.h"
#include <QApplication>
#include <quazip/quagzipfile.h>
#include "fastqreader.h"

#include "sequence.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<Sequence>();


    MainWindow win;

    win.show();


    return a.exec();
}
