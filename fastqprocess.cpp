#include "fastqprocess.h"
#include <functional>
FastqProcess::FastqProcess(const QString& filename, QObject *parent)
    :mFilename(filename),QObject(parent)
{

    connect(&mWatcher,SIGNAL(finished()),this,SLOT(analyseDone()));
}

void FastqProcess::run()
{
    qDebug()<<Q_FUNC_INFO<<"run analyse";
    QFuture<FastqData> future = QtConcurrent::run(this, &FastqProcess::process);
    mWatcher.setFuture(future);

}

const FastqData &FastqProcess::results() const
{
    return mResults;
}

void FastqProcess::globalParse(QTextStream& stream,FastqData& data)
{
    //    QString line;
    //    int modulo = 0;
    //    while (stream.readLineInto(&line))
    //    {




    //    }
}

FastqData FastqProcess::process()
{

    QFile file(mFilename);
    FastqData data;
    data.totalSequence = 0;

    if (file.open(QIODevice::ReadOnly))
    {
        FastqReader reader(&file);
        int maxLen = 0;
        while (reader.next())
        {
            data.totalSequence++;
            maxLen = qMax (reader.qualities().length(), maxLen);

        }

        reader.reset();

        int range = qFloor(maxLen / 10) +1;
        QVector < QVector <int> > qq;
        qq.resize(range);






        qDebug()<<qq.size();



        return data;

    }

}

void FastqProcess::analyseDone()
{
    qDebug()<<Q_FUNC_INFO<<"Analyse done";
    mResults  = mWatcher.result();
    emit done();
}
