#include "statanalysewidget.h"

StatAnalyseWidget::StatAnalyseWidget(QWidget *parent)
    :AbstractAnalyseWidget(parent)
{

    mEdit = new QPlainTextEdit;
    setLayout(new QVBoxLayout);
    layout()->addWidget(mEdit);
    setWindowTitle("Stat");
    setWindowIcon(QIcon::fromTheme("edit-undo"));


}

void StatAnalyseWidget::analysisStarted()
{
    qDebug()<<"yo";
    mEdit->appendPlainText("Start analysis...");

}

void StatAnalyseWidget::analysisUpdated(const Sequence &sequence)
{

    if (!done)
    {
        qDebug()<<&sequence;
        done = true;
    }

    mEdit->appendPlainText(sequence.sequence());
}



void StatAnalyseWidget::analysisFinished()
{
    mEdit->appendPlainText("End analysis");
}




