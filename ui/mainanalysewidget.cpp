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
#include "mainanalysewidget.h"

MainAnalyseWidget::MainAnalyseWidget(QWidget *parent):
    QMainWindow(parent)
{

    setAttribute(Qt::WA_DeleteOnClose, false);

    mListWidget       = new QListWidget;
    mStackWidget      = new QStackedWidget;
    mResultWidget     = new QSplitter(Qt::Horizontal);


    mResultWidget->addWidget(mListWidget);
    mResultWidget->addWidget(mStackWidget);
    mResultWidget->setStretchFactor(1,4);


    setCentralWidget(mResultWidget);


//    mToolBar = addToolBar("actions");


    connect(mListWidget,SIGNAL(currentRowChanged(int)),mStackWidget,SLOT(setCurrentIndex(int)));


}

MainAnalyseWidget::~MainAnalyseWidget()
{
    delete mResultWidget;
}

void MainAnalyseWidget::setRunner(AnalysisRunner *runner)
{
    mRunner = runner;
//    mToolBar->clear();


    setWindowTitle(mRunner->filename());

    for ( Analysis * a : mRunner->analysisList())
    {

        QListWidgetItem * lItem = new QListWidgetItem;
        lItem->setText(a->name());
        lItem->setToolTip(a->description());
        lItem->setIcon(a->statusIcon());

        mListWidget->addItem(lItem);

        mStackWidget->addWidget(a->createResultWidget());

    }

}










