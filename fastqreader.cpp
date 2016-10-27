#include "fastqreader.h"
#include <functional>
FastqReader::FastqReader(const QString& filename, QObject *parent)
    :mFilename(filename),QObject(parent)
{
    connect(&mWatcher,SIGNAL(finished()),this,SLOT(analyseDone()));
}

void FastqReader::run()
{
    qDebug()<<Q_FUNC_INFO<<"run analyse";
    QFuture<FastqData> future = QtConcurrent::run(this, &FastqReader::analyse);
    mWatcher.setFuture(future);

}

const FastqData &FastqReader::results() const
{
 return mResults;
}

FastqData FastqReader::analyse()
{
    QFile file(mFilename);
    FastqData data ;

    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream stream(&file);
        QString line;


        data.sequenceLength = 0;
        data.totalSequence = 0;

        int modulo = 0;
        QVector<int> lengths;

        while (stream.readLineInto(&line))
        {
            ++data.totalSequence;

            // modulo = 0  header
            // modulo = 1  sequence
            // modulo = 2  +
            // modulo = 3  quality

            if ( modulo % 4 == 1){
                lengths.append(line.length());

            }

            ++modulo;
        }

        data.sequenceLength  = std::accumulate(lengths.begin(), lengths.end(),0) / data.totalSequence;


    }

    return data;

}

void FastqReader::analyseDone()
{
    qDebug()<<Q_FUNC_INFO<<"Analyse done";
    mResults  = mWatcher.result();
    emit done();
}
