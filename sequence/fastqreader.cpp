#include "fastqreader.h"


FastqReader::FastqReader(QIODevice *device)
    :AbstractSequenceReader(device)
{

    mStream.setDevice(device);

}



bool FastqReader::next()
{

    if (mStream.atEnd())
        return false;

    Sequence readSequence;

    // read ID
    readSequence.setId(mStream.readLine());
    // read sequence
    readSequence.setSequence(mStream.readLine());
    // read unused +
    mStream.readLine();
    // read qualities
    readSequence.setQuality(mStream.readLine());

    setSequence(readSequence);

    return true;
}

int FastqReader::percentCompleted()
{

    return (double)(mStream.pos()) / mStream.device()->size() * 100;

}
