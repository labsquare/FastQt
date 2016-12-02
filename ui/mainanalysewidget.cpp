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
    mListWidget->setMaximumWidth(100);

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


}




void MainAnalyseWidget::launch()
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
        mListWidget->addItem(new QListWidgetItem(a->icon(),a->name()));
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



