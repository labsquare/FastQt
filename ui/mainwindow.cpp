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
    mTabWidget = new QTabWidget;
    mTabWidget->setMovable(true);
    mTabWidget->setTabsClosable(true);
    setCentralWidget(mTabWidget);

    setupActions();
    resize(800,600);

    move(200,200);

    connect(mTabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));


}

MainWindow::~MainWindow()
{

}

void MainWindow::addFile(const QString &filename)
{

    MainAnalyseWidget * w = new MainAnalyseWidget(filename);
    mainList.append(w);
    mTabWidget->addTab(w, w->windowIcon(), w->windowTitle());

}

void MainWindow::run()
{

    //    addFile("/home/sacha/merge.fastq");
    //    mainList.first()->run();

}

void MainWindow::openFile()
{

    QStringList fileNames = QFileDialog::getOpenFileNames(this,tr("Open Fastq file"), QDir::homePath(), tr("Fastq Files (*.fastq *.fastq.gz *.fastq.bz2 *.fastq.xz)"));

    if (!fileNames.isEmpty())
    {
        for (QString file : fileNames)
        {
            addFile(file);
            mainList.last()->run();
        }
    }
}

void MainWindow::about()
{
    AboutDialog dialog(this);
    dialog.exec();
}

void MainWindow::closeTab(int index)
{
     if (mTabWidget->widget(index))
     {
         QWidget * w = mTabWidget->widget(index);
         mTabWidget->removeTab(index);
         delete w;

     }

}

void MainWindow::setupActions()
{

    // Create Menu Bar
    setMenuBar(new QMenuBar());
    // File menu
    QMenu * fileMenu = menuBar()->addMenu(tr("&File"));
    QAction * openAction = fileMenu->addAction(QFontIcon::icon(0xf115), tr("&Open file"),this, SLOT(openFile()), QKeySequence::Open);
    fileMenu->addAction(QFontIcon::icon(0xf00d),tr("&Close"),qApp, SLOT(closeAllWindows()), QKeySequence::Close);

    // Help menu
    QMenu * helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(QFontIcon::icon(0xf129),tr("About %1").arg(qAppName()),this,SLOT(about()));
    helpMenu->addAction(QFontIcon::icon(0xf129),tr("About &Qt"),qApp, SLOT(aboutQt()));


    QToolBar * bar = addToolBar(tr("Open"));
    bar->setToolButtonStyle(Qt::ToolButtonFollowStyle);
    bar->addAction(openAction);


}



