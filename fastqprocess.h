#ifndef FASTQPROCESS_H
#define FASTQPROCESS_H

#include <QObject>
#include <QIODevice>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE

#include "fastqreader.h"


struct QualitySet {
    qreal min;
    qreal max;
    qreal first_quartile;
    qreal last_quartile;
    qreal median;
};

struct FastqData {

    QString type;
    QString encode;
    quint64 totalSequence;
    quint64 meanSeqLength;
    quint64 minSeqLength;
    quint64 maxSeqLength;
    int gcPercent;
    QVector <QualitySet> qualities;

};



class FastqProcess : public QObject
{
    Q_OBJECT
public:
    explicit FastqProcess(const QString& filename, QObject *parent = 0);
    void run();
    const FastqData& results() const;

signals:
    void done();


protected:
    void globalParse(QTextStream& stream,FastqData& data);

protected slots:
    FastqData process();
    void analyseDone();


private:
    QString mFilename;
    QFutureWatcher<FastqData> mWatcher;
    FastqData mResults;


};

#endif // FASTQPROCESS_H
