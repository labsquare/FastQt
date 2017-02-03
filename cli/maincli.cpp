#include "maincli.h"

MainCLI::MainCLI(QCommandLineParser* parser, QObject *parent) : QObject(parent), mParser(parser)
{

}

int MainCLI::exec()
{
    QList<AnalysisRunner*> runnerList;
    for(QString filename : mParser->positionalArguments())
    {
        AnalysisRunner* runner = new AnalysisRunner();
        runner->setFilename(filename);

        LengthDistributionAnalysis* len_dist_ana = new LengthDistributionAnalysis;
        runner->addAnalysis(new BasicStatsAnalysis);
        runner->addAnalysis(new PerBaseQualityAnalysis);
        runner->addAnalysis(new PerSequenceQualityAnalysis);
        runner->addAnalysis(new OverRepresentedSeqsAnalysis);
        runner->addAnalysis(new PerBaseNContentAnalysis);
        runner->addAnalysis(new PerSequenceGCContent);
        runner->addAnalysis(len_dist_ana);
        runner->addAnalysis(new PerBaseContentAnalysis(nullptr, len_dist_ana));

        runnerList.append(runner);
        runnerList.last()->run();
    }

    return 0;
}
