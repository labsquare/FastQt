#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QFileInfo>
#include "mainanalysewidget.h"
#include "fastqprocess.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addFile(const QString& filename);


private:
    QTabWidget * mTabWidget;
    QList<MainAnalyseWidget*> mainList;
};

#endif // MAINWINDOW_H
