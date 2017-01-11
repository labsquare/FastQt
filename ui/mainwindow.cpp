/*
Copyright Copyright 2016-17 Sacha Schutz

    This file is part of CuteVCF.

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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mTabWidget = new QTabWidget;
    setCentralWidget(mTabWidget);

    setMenuBar(new QMenuBar());

    QMenu * fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(tr("Open file"),this, SLOT(openFile()), QKeySequence::Open);
    fileMenu->addAction(tr("Close"),qApp, SLOT(closeAllWindows()), QKeySequence::Close);



    addToolBar("Open")->addAction("Open", this, SLOT(openFile()));

    resize(600,400);



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

    addFile("/home/sacha/merge.fastq");
    mainList.first()->run();

}

void MainWindow::openFile()
{


    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Fastq file"), QDir::homePath(), tr("Fastq Files (*.fastq)"));

    if (!fileName.isEmpty())
    {
        addFile(fileName);
        mainList.first()->run();
    }


}



