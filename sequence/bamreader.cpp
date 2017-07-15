#include "bamreader.h"

BamReader::BamReader(QFile *device)
    :AbstractSequenceReader(device)
{
    mFilename = device->fileName();
}

bool BamReader::next()
{
    if (fp_in == nullptr)
    {
        fp_in = hts_open(mFilename.toStdString().c_str(),"r"); //open bam file
        bamHdr = sam_hdr_read(fp_in); //read header
        aln = bam_init1(); //initialize an alignment
    }


    if ( sam_read1(fp_in,bamHdr,aln) > 0 )
    {
        Sequence seq;

        uint32_t len = aln->core.l_qseq; //length of the read.

        uint8_t *q = bam_get_seq(aln); //sequence string
        uint8_t *q2 = bam_get_qual(aln); //sequence quality

        char *qseq = static_cast<char *>(malloc(len));
        char* qqua = static_cast<char *>(malloc(len));

        for(unsigned int i=0; i< len ; i++){
            qseq[i] = seq_nt16_str[bam_seqi(q,i)]; //gets nucleotide id and converts them into IUPAC id.
            qqua[i] = static_cast<char>(q2[i]);
        }

        seq.setSequence(QByteArray(qseq, len));
        seq.setQuality(QByteArray(qqua, len));


        // update sequence
        setSequence(seq);
        return true;

    }

    else
    {
        bam_destroy1(aln);
        sam_close(fp_in);
    }

    return false;
}
