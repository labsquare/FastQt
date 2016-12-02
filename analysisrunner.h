#ifndef ANALYSISRUNNER_H
#define ANALYSISRUNNER_H
#include <QtCore>
#include "analysis.h"
#include "fastqreader.h"

class AnalysisRunner : public QThread
{
    Q_OBJECT
public:
    AnalysisRunner(QObject * parent = 0);
    AnalysisRunner(const QString& filename, QObject * parent = 0);

    virtual void run() override;
    void addAnalysis(Analysis* analysis);
    void setFilename(const QString& filename);

    const QList<Analysis*>& analysisList() const;

Q_SIGNALS:
    void updated(int sequencesProcessed, int percentCompleted);


private:
    QList<Analysis*> mAnalysisList;
    QString mFilename;

};

#endif // ANALYSISRUNNER_H
