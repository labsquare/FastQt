#include "abstractsequencereader.h"
#include "sequence/sequence.hxx"


AbstractSequenceReader::AbstractSequenceReader(QIODevice *device)
    :mDevice(device)
{


}

int AbstractSequenceReader::percentComplete() const
{

    int percent = (double)(mDevice->pos()) / mDevice->size() * 100;
    return percent;

}

const Sequence &AbstractSequenceReader::sequence() const
{
    return mSequence;
}

QIODevice *AbstractSequenceReader::device()
{
    return mDevice;
}

void AbstractSequenceReader::setSequence(const Sequence &seq)
{

    mSequence = seq;
}
