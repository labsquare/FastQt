#ifndef FASTQREADER_H
#define FASTQREADER_H

#include <QObject>
#include <QIODevice>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include <QFile>
#include <QDebug>
#include <QTextStream>


struct FastqData {

    QString type;
    QString encode;
    quint64 totalSequence;
    quint64 sequenceLength;
    int gcPercent;


};



class FastqReader : public QObject
{
    Q_OBJECT
public:
    explicit FastqReader(const QString& filename, QObject *parent = 0);
    void run();
    const FastqData& results() const;

signals:
    void done();


protected slots:
    FastqData analyse();
    void analyseDone();


private:
    QString mFilename;
    QFutureWatcher<FastqData> mWatcher;
    FastqData mResults;


};

#endif // FASTQREADER_H
