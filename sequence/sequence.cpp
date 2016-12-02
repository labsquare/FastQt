#include "sequence.h"


Sequence::Sequence()
{

}

Sequence::Sequence(const QString &id, const QString &sequence, const QString &quality)
    :mId(id), mSequence(sequence), mQuality(quality)
{

}

const QString &Sequence::id() const
{
    return mId;
}

void Sequence::setId(const QString &id)
{
    mId = id;
}

const QString &Sequence::sequence() const
{
    return mSequence;
}

void Sequence::setSequence(const QString &sequence)
{
    mSequence = sequence;
}

const QString &Sequence::quality() const
{
    return mQuality;
}

void Sequence::setQuality(const QString &quality)
{
    mQuality = quality;
}
