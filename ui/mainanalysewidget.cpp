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

#include "imageformatdefinition.h"

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


    mToolBar = addToolBar("actions");
    mToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);


    connect(mListWidget,SIGNAL(currentRowChanged(int)),this,SLOT(setCurrentIndex(int)));


}

MainAnalyseWidget::~MainAnalyseWidget()
{
    delete mResultWidget;
}

void MainAnalyseWidget::setRunner(AnalysisRunner *runner)
{
    mRunner = runner;


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

void MainAnalyseWidget::setCurrentIndex(int index)
{
    mStackWidget->setCurrentIndex(index);
    //Create tool bar
    mToolBar->clear();
    mToolBar->addAction(QFontIcon::icon(0xf0c7),tr("Save"), this, SLOT(saveCurrentAnalysis()));
    mToolBar->addActions(mStackWidget->widget(index)->actions());

    if (mStackWidget->widget(index)->metaObject()->className() == QChartView::staticMetaObject.className())
    {
        QChartView * view = qobject_cast<QChartView*>(mStackWidget->widget(index));
        view->chart()->zoomReset();
    }




}

void MainAnalyseWidget::saveCurrentAnalysis()
{
    Analysis* ana =  dynamic_cast<Analysis*>(mStackWidget->currentWidget());
    QString path = QFileDialog::getSaveFileName(this, tr("Save Image without extension"),
                                                QString(),
                                                tr(""));
    if (!path.isEmpty())
    {
       ana->save(path);
    }

}












