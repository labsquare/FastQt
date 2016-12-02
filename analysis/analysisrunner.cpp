#include "analysisrunner.h"


AnalysisRunner::AnalysisRunner(QObject *parent)
    :QThread(parent)
{

}

AnalysisRunner::AnalysisRunner(const QString &filename, QObject *parent)
    :QThread(parent)
{
    setFilename(filename);
}

void AnalysisRunner::run()
{
    QFile file(mFilename);
    if (file.open(QIODevice::ReadOnly))
    {
        int seqCount = 0;
        int percentCompleted = 0;

        FastqReader reader(&file);


        while (reader.next())
        {
            Sequence seq = reader.sequence();
            ++seqCount;

            int percentNow = reader.percentComplete();
            if (percentNow >= percentCompleted + 10)
            {
                percentCompleted = percentNow;
                emit updated(seqCount, percentCompleted);
            }

            for (Analysis * a : mAnalysisList)
            {
                a->processSequence(seq);
            }
        }


    }


}

void AnalysisRunner::addAnalysis(Analysis *analysis)
{
    mAnalysisList.append(analysis);
}

void AnalysisRunner::setFilename(const QString &filename)
{
    mFilename = filename;
}

const QList<Analysis*> &AnalysisRunner::analysisList() const
{
    return mAnalysisList;
}
