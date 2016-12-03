#include <QApplication>
#include "mainwindow.h"
#include "perbasequalityanalysis.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<Sequence>();


    MainWindow window;
    window.show();


    return a.exec();
}
