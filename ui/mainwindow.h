#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QFileInfo>
#include "mainanalysewidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addFile(const QString& filename);

public Q_SLOTS:
    void run();

private:
    QTabWidget * mTabWidget;
    QList<MainAnalyseWidget*> mainList;

    QFuture<void> mRunFuture;

};

#endif // MAINWINDOW_H
