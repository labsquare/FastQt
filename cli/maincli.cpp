#include "maincli.h"

MainCLI::MainCLI(QCommandLineParser* parser, QObject *parent) : QEventLoop(parent), mParser(parser)
{
    mTimer = new QTimer(this);
    mTimer->start(1000);
    connect(mTimer,SIGNAL(timeout()),this,SLOT(showProgression()));

}

int MainCLI::exec()
{
    // Display started information
    qDebug()<<"BLABABA";

    // Set thread number
    int threadNumber;
    if (mParser->value("threads").isEmpty())
         threadNumber = QThread::idealThreadCount();
    else
        threadNumber = mParser->value("threads").toInt();

    qDebug()<<threadNumber;
    // Set max thread number
    QThreadPool::globalInstance()->setMaxThreadCount(threadNumber);

    for(QString filename : mParser->positionalArguments())
    {
        AnalysisRunner* runner = new AnalysisRunner();
        runner->setFilename(filename);

        // ON VA FAIRE UN FACTORY POUR CA POUR QUE LE GUI ET CA , SOIT PAREIL
        LengthDistributionAnalysis* len_dist_ana = new LengthDistributionAnalysis;
        runner->addAnalysis(new BasicStatsAnalysis);
        runner->addAnalysis(new PerBaseQualityAnalysis);
        runner->addAnalysis(new PerSequenceQualityAnalysis);
        runner->addAnalysis(new OverRepresentedSeqsAnalysis);
        runner->addAnalysis(new PerBaseNContentAnalysis);
        runner->addAnalysis(new PerSequenceGCContent);
        runner->addAnalysis(len_dist_ana);
        runner->addAnalysis(new PerBaseContentAnalysis(nullptr, len_dist_ana));

        mRunnerList.append(runner);

        QThreadPool::globalInstance()->start(runner);
        qDebug()<<runner->filename();
    }


    return QEventLoop::exec(); // Loop until all runner has been finished
}

void MainCLI::showProgression()
{

   for (AnalysisRunner * runner : mRunnerList)
   {
        cout<<runner->filename().toStdString()<<" "<<runner->progression()<<endl;
   }


}
