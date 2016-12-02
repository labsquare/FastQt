#ifndef ABSTRACTSEQUENCEREADER_H
#define ABSTRACTSEQUENCEREADER_H
#include <QtCore>
#include "sequence.h"
class AbstractSequenceReader
{
public:
    AbstractSequenceReader(QIODevice * device);

    virtual bool next() = 0;
    virtual int percentComplete() const;

    const Sequence& sequence() const;

protected:
    void setSequence(const Sequence& seq);


private:
    QIODevice * mDevice;
    Sequence mSequence;
};

#endif // ABSTRACTSEQUENCEREADER_H
