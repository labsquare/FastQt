#include "mainanalysewidget.h"

MainAnalyseWidget::MainAnalyseWidget(const QString& filename, QWidget *parent):
    QWidget(parent)
{

    mFilename       = filename;
    mListWidget     = new QListWidget;
    mStackedWidget  = new QStackedWidget;


    QSplitter * splitter     = new QSplitter(Qt::Horizontal);
    QVBoxLayout * mainLayout = new QVBoxLayout;

    splitter->addWidget(mListWidget);
    splitter->addWidget(mStackedWidget);
    mainLayout->addWidget(splitter);

    setLayout(mainLayout);

    QFileInfo info(filename);
    setWindowTitle(info.fileName());
    mListWidget->setMaximumWidth(100);


    addAnalyse(new StatAnalyseWidget);

    connect(mListWidget,SIGNAL(currentRowChanged(int)),mStackedWidget,SLOT(setCurrentIndex(int)));

}

void MainAnalyseWidget::runAllAnalysis()
{
    QFile file(mFilename);
    if (file.open(QIODevice::ReadOnly))
    {
        emit started();

        FastqReader reader(&file);

        bool done = false;

        while (reader.next())
        {
            Sequence seq = reader.sequence();

            if (!done)
            {
                done = true;
                qDebug()<<(&seq);
            }


            emit updated(seq);

            seq.setSequence("AAA");

        }

        emit finished();
    }

}
void MainAnalyseWidget::addAnalyse(AbstractAnalyseWidget *widget)
{

    mAnalyisis.append(widget);
    mListWidget->addItem(new QListWidgetItem(widget->windowIcon(),widget->windowTitle()));
    mStackedWidget->addWidget(widget);

    connect(this,&MainAnalyseWidget::started, widget, &AbstractAnalyseWidget::analysisStarted);
    connect(this,&MainAnalyseWidget::updated, widget, &AbstractAnalyseWidget::analysisUpdated);
    connect(this,&MainAnalyseWidget::finished, widget, &AbstractAnalyseWidget::analysisFinished);
}

//void MainAnalyseWidget::addAnalyse(AbstractAnalyseWidget *widget)
//{


////    mAnalyseWidgets.append(widget);
////    mListWidget->addItem(new QListWidgetItem(widget->windowIcon(),widget->windowTitle()));
////    mStackedWidget->addWidget(widget);



//}
