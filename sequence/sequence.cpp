#include "sequence.h"


Sequence::Sequence()
{

}

Sequence::Sequence(const QByteArray &id, const QByteArray &sequence, const QByteArray &quality)
    :mId(id), mSequence(sequence), mQuality(quality)
{

}

const QByteArray &Sequence::id() const
{
    return mId;
}

void Sequence::setId(const QByteArray &id)
{
    mId = id;
}

const QByteArray &Sequence::sequence() const
{
    return mSequence;
}

void Sequence::setSequence(const QByteArray &sequence)
{
    mSequence = sequence.trimmed();
}

const QByteArray &Sequence::quality() const
{
    return mQuality;
}

void Sequence::setQuality(const QByteArray &quality)
{
    mQuality = quality.trimmed();
}

int Sequence::size() const
{
    return mSequence.size();
}
