#include "mainanalysewidget.h"

MainAnalyseWidget::MainAnalyseWidget(const QString& filename, QWidget *parent):
     QWidget(parent)
{

    mListWidget = new QListWidget;
    mStackedWidget = new QStackedWidget;
    mReader = new FastqReader(filename);

    QSplitter * splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(mListWidget);
    splitter->addWidget(mStackedWidget);
    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(splitter);

    setLayout(mainLayout);

    QFileInfo info(filename);
    setWindowTitle(info.fileName());

    addAnalyse(new StatAnalyseWidget(mReader));

    mListWidget->setMaximumWidth(100);


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
