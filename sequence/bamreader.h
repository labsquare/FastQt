#ifndef BAMREADER_H
#define BAMREADER_H
#include <QtCore>
#include "fastqreader.h"
#include "htslib/sam.h"

class BamReader : public AbstractSequenceReader
{
public:
    BamReader(QFile *device);
    bool next() Q_DECL_OVERRIDE;


private:
    QString mFilename;

    samFile *fp_in = nullptr;
    bam_hdr_t *bamHdr = nullptr;
    bam1_t *aln = nullptr;
};

#endif // BAMREADER_H
