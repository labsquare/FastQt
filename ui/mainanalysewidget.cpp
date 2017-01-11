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
#include "mainanalysewidget.h"

MainAnalyseWidget::MainAnalyseWidget(const QString& filename, QWidget *parent):
    QWidget(parent)
{

    mFilename       = filename;
    mRunner.setFilename(filename);


    mProgressLabel    = new QLabel("Bonjour");
    mListWidget       = new QListWidget;
    mStackWidget      = new QStackedWidget;
    mResultWidget     = new QSplitter(Qt::Horizontal);

    mProgressLabel->setAlignment(Qt::AlignCenter);
    mResultWidget->addWidget(mListWidget);
    mResultWidget->addWidget(mStackWidget);
    mListWidget->setMaximumWidth(150);

    mMainLayout = new QStackedLayout;
    mMainLayout->addWidget(mProgressLabel);
    mMainLayout->addWidget(mResultWidget);

    setLayout(mMainLayout);

    setWindowTitle(mFilename);

    connect(&mRunner, &AnalysisRunner::started, this, &MainAnalyseWidget::analysisStarted);
    connect(&mRunner, &AnalysisRunner::updated, this, &MainAnalyseWidget::analysisUpdated);
    connect(&mRunner, &AnalysisRunner::finished, this, &MainAnalyseWidget::analysisFinished);

    connect(mListWidget,&QListWidget::currentRowChanged, mStackWidget, &QStackedWidget::setCurrentIndex);

    mRunner.addAnalysis(new BasicStatsAnalysis);
    mRunner.addAnalysis(new PerBaseQualityAnalysis);
    mRunner.addAnalysis(new PerSequenceQualityAnalysis);
    mRunner.addAnalysis(new PerBaseContentAnalysis);


}




void MainAnalyseWidget::run()
{
    mMainLayout->setCurrentWidget(mProgressLabel);

    mRunner.reset();
    mRunner.start(QThread::HighPriority);

}

void MainAnalyseWidget::analysisStarted()
{

}

void MainAnalyseWidget::analysisUpdated(int seqCount, int percent)
{

    mProgressLabel->setText(QString("%1 Sequences procceed ( %2 )\%").arg(seqCount).arg(percent));
}

void MainAnalyseWidget::analysisFinished()
{
    clearResults();

    for (Analysis* a : mRunner.analysisList())
    {

        QListWidgetItem * item = new QListWidgetItem;
        item->setText(a->name());
        item->setToolTip(a->tooltip());
        item->setIcon(a->statusIcon());
        item->setSizeHint(QSize(item->sizeHint().width(), 30));


        mListWidget->addItem(item);
        mStackWidget->addWidget(a->createResultWidget());
    }


    mMainLayout->setCurrentWidget(mResultWidget);


}

void MainAnalyseWidget::clearResults()
{
    mListWidget->clear();

    for(int i = mStackWidget->count(); i >= 0; i--)
    {
        QWidget* widget = mStackWidget->widget(i);
        mStackWidget->removeWidget(widget);
        delete widget;
    }
}



