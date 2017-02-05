/*
Copyright Copyright 2016-17 Sacha Schutz

    This file is part of FastQt.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

    @author : Pierre Lindenbaum from FastQC <http://www.bioinformatics.babraham.ac.uk/projects/fastqc/>
    @author : Sacha Schutz <sacha@labsquare.org>
    @author : Pierre Marijon <pierre@marijon.fr>
*/
#include "mainwindow.h"
#include "qfonticon.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    mView = new MainAnalyseView;
    setCentralWidget(mView);

    //    mTabWidget = new QTabWidget;
    //    mTabWidget->setMovable(true);
    //    mTabWidget->setTabsClosable(true);
    //    setCentralWidget(mTabWidget);

    setupActions();
    resize(800,600);

    move(200,200);

    //    connect(mTabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));


}

MainWindow::~MainWindow()
{

}

void MainWindow::addFiles()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,tr("Open Fastq file"), QDir::homePath(), tr("Fastq Files (*.fastq *.fastq.gz *.fastq.bz2 *.fastq.xz)"));
    if (!fileNames.isEmpty())
    {
        for (QString file : fileNames)
        {
            mView->addFile(file);
        }
    }

}

void MainWindow::remFiles()
{

}

void MainWindow::showAnalysis()
{
    mView->showAnalysis(mView->currentIndex());
}

void MainWindow::run()
{

    //    addFile("/home/sacha/merge.fastq");
    //    mainList.first()->run();

}

//void MainWindow::openFile()
//{

//    QStringList fileNames = QFileDialog::getOpenFileNames(this,tr("Open Fastq file"), QDir::homePath(), tr("Fastq Files (*.fastq *.fastq.gz *.fastq.bz2 *.fastq.xz)"));

//    if (!fileNames.isEmpty())
//    {
//        for (QString file : fileNames)
//        {
//            addFile(file);
//            mMainList.last()->run();
//        }
//    }
//}

void MainWindow::about()
{
    AboutDialog dialog(this);
    dialog.exec();
}


void MainWindow::setupActions()
{

    // Create Menu Bar
    setMenuBar(new QMenuBar());
    // File menu
    QMenu * fileMenu = menuBar()->addMenu(tr("&File"));
    QAction * openAction = fileMenu->addAction(QFontIcon::icon(0xf067), tr("&Add files"),this, SLOT(addFiles()), QKeySequence::Open);
    QAction * remAction  = fileMenu->addAction(QFontIcon::icon(0xf068), tr("&Remove file(s)"),this, SLOT(remFiles()), QKeySequence::Delete);
   // QAction * saveAction  = fileMenu->addAction(QFontIcon::icon(0xf03e), tr("&Export result(s) as image"),this, SLOT(remFiles()), QKeySequence::Save);
    fileMenu->addSeparator();
    fileMenu->addAction(QFontIcon::icon(0xf00d),tr("&Close"),qApp, SLOT(closeAllWindows()), QKeySequence::Close);

    //View menu
    QMenu * viewMenu = menuBar()->addMenu(tr("&View"));
    QAction * showAction = viewMenu->addAction(QFontIcon::icon(0xf06e), tr("&Show analysis"),this, SLOT(showAnalysis()));



    // Help menu
    QMenu * helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(QFontIcon::icon(0xf129),tr("About %1").arg(qAppName()),this,SLOT(about()));
    helpMenu->addAction(QFontIcon::icon(0xf129),tr("About &Qt"),qApp, SLOT(aboutQt()));


    QToolBar * bar = addToolBar(tr("Open"));
    bar->setToolButtonStyle(Qt::ToolButtonFollowStyle);
    bar->addAction(openAction);
    bar->addAction(remAction);
    bar->addSeparator();
    bar->addAction(showAction);



}



