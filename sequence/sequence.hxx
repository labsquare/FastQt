#ifndef SEQUENCE_HXX
#define SEQUENCE_HXX
#include "sequence.h"

inline Sequence::Sequence()
{

}

inline Sequence::Sequence(const QByteArray &id, const QByteArray &sequence, const QByteArray &quality)
    :mId(id), mSequence(sequence), mQuality(quality)
{

}

inline const QByteArray &Sequence::id() const
{
    return mId;
}

inline void Sequence::setId(const QByteArray &id)
{
    mId = id;
}

inline const QByteArray &Sequence::sequence() const
{
    return mSequence;
}

inline void Sequence::setSequence(const QByteArray &sequence)
{
    mSequence = sequence.trimmed().toUpper();
}

inline const QByteArray &Sequence::quality() const
{
    return mQuality;
}

inline void Sequence::setQuality(const QByteArray &quality)
{
    mQuality = quality.trimmed();
}

inline int Sequence::size() const
{
  return mSequence.size();
}

#endif // SEQUENCE_HXX
