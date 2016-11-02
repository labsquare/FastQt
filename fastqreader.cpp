#include "fastqreader.h"

FastqReader::FastqReader(QIODevice *device, QObject *parent) : QObject(parent)
{
    mDevice = device;
    mStream.setDevice(mDevice);
    mLineNumber = 0;


}


const QString &FastqReader::header()
{
    return mHeader;
}

const QString &FastqReader::sequence()
{
    return mSequence;
}

const QString &FastqReader::rawQualites()
{
    return mRawQualities;
}

const QVector<int> &FastqReader::qualities()
{
    return mQualities;
}

bool FastqReader::next()
{

    if (mStream.atEnd())
        return false;

    mHeader = mStream.readLine();
    mSequence = mStream.readLine();
    mStream.readLine();
    mRawQualities = mStream.readLine();

    // compute quality
    mQualities.clear();
    std::for_each(mRawQualities.begin(), mRawQualities.end(),[this](QChar ascii){this->mQualities.append(ascii.toLatin1()-33);});


    mLineNumber+=4;

    return true;

}

bool FastqReader::reset()
{
    mLineNumber = 0;
    return mStream.seek(0);

}
