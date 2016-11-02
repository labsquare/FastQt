#include "mainanalysewidget.h"

MainAnalyseWidget::MainAnalyseWidget(const QString& filename, QWidget *parent):
     QWidget(parent)
{

    mListWidget = new QListWidget;
    mStackedWidget = new QStackedWidget;
    mReader = new FastqProcess(filename);

    QSplitter * splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(mListWidget);
    splitter->addWidget(mStackedWidget);
    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(splitter);

    setLayout(mainLayout);

    QFileInfo info(filename);
    setWindowTitle(info.fileName());

    addAnalyse(new StatAnalyseWidget(mReader));
    addAnalyse(new SeqQualityAnalyseWidget(mReader));

    mListWidget->setMaximumWidth(100);

    connect(mListWidget,SIGNAL(currentRowChanged(int)),mStackedWidget,SLOT(setCurrentIndex(int)));


}

void MainAnalyseWidget::run()
{
    mReader->run();
}

void MainAnalyseWidget::addAnalyse(AbstractAnalyseWidget *widget)
{


    mAnalyseWidgets.append(widget);
    mListWidget->addItem(new QListWidgetItem(widget->windowIcon(),widget->windowTitle()));
    mStackedWidget->addWidget(widget);



}
