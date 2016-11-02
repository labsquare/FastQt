#include "mainwindow.h"
#include <QApplication>
#include "statanalysewidget.h"
#include <quazip/quagzipfile.h>
#include "fastqreader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    w.show();






    return a.exec();
}
