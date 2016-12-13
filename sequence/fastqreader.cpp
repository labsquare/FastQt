#include "fastqreader.h"
#include "sequence/sequence.hxx"


FastqReader::FastqReader(QIODevice *device)
    :AbstractSequenceReader(device)
{


}



bool FastqReader::next()
{

    if (device()->atEnd())
        return false;

    Sequence readSequence;

    // read ID


    readSequence.setId(device()->readLine());
    // read sequence
    readSequence.setSequence(device()->readLine());
    // read unused +
    device()->readLine();
    // read qualities
    readSequence.setQuality(device()->readLine());


    setSequence(readSequence);

    return true;
}

int FastqReader::percentCompleted()
{

    return (double)(device()->pos()) / device()->size() * 100;

}
