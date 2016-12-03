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
    if (file.open(QIODevice::ReadOnly|QFile::Text))
    {
        int seqCount = 0;
        int percentCompleted = 0;

        FastqReader reader(&file);

        QTime start = QTime::currentTime();
        qDebug()<<"start"<<start;

        while (reader.next())
        {
            ++seqCount;

            int percentNow = reader.percentComplete();
            if (percentNow >= percentCompleted + 10)
            {
                percentCompleted = percentNow;
                emit updated(seqCount, percentCompleted);
            }

            for (Analysis * a : mAnalysisList)
            {
                a->processSequence(reader.sequence());
            }
        }

        qDebug()<<"end"<<start.msecsTo(QTime::currentTime());



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

void AnalysisRunner::reset()
{
    for (Analysis * a : analysisList())
        a->reset();
}

const QList<Analysis*> &AnalysisRunner::analysisList() const
{
    return mAnalysisList;
}
