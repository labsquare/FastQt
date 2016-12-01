#ifndef FASTQREADER_H
#define FASTQREADER_H

#include "abstractsequencereader.h"

class FastqReader : public AbstractSequenceReader
{
public:
    FastqReader(QIODevice * device);

     bool next() override;


private:
     QTextStream mStream;

};

#endif // FASTQREADER_H
