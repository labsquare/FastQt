#ifndef FASTQREADER_H
#define FASTQREADER_H
#include <QtCore>

class FastqReader : public QObject
{
    Q_OBJECT
public:
    explicit FastqReader(QIODevice * device, QObject *parent = 0);



    const QString& header();
    const QString& sequence();
    const QString& rawQualites();
    const QVector<int>& qualities();

    bool next();
    bool reset();



private:
    QTextStream mStream;
    QIODevice * mDevice;

    QString mHeader;
    QString mSequence;
    QString mRawQualities;
    QVector<int> mQualities;
    int mLineNumber;


};

#endif // FASTQREADER_H
