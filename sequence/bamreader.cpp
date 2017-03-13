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

        int32_t pos = aln->core.pos +1; //left most position of alignment in zero based coordianate (+1)
        char *chr = bamHdr->target_name[aln->core.tid] ; //contig name (chromosome)
        uint32_t len = aln->core.l_qseq; //length of the read.

        uint8_t *q = bam_get_seq(aln); //quality string
        uint32_t q2 = aln->core.qual ; //mapping quality

        char *qseq = (char *)malloc(len);

        for(int i=0; i< len ; i++){
            qseq[i] = seq_nt16_str[bam_seqi(q,i)]; //gets nucleotide id and converts them into IUPAC id.
        }

        seq.setSequence(QByteArray(qseq));
        seq.setQuality(QByteArray(qseq));


        // update sequence
        setSequence(seq);
        return true;

    }

    else
    {
        bam_destroy1(aln);
        sam_close(fp_in);
    }



    // LOOP SNIPPET
    //    while(sam_read1(fp_in,bamHdr,aln) > 0){

    //        int32_t pos = aln->core.pos +1; //left most position of alignment in zero based coordianate (+1)
    //        char *chr = bamHdr->target_name[aln->core.tid] ; //contig name (chromosome)
    //        uint32_t len = aln->core.l_qseq; //length of the read.

    //        uint8_t *q = bam_get_seq(aln); //quality string
    //        uint32_t q2 = aln->core.qual ; //mapping quality

    //        qDebug()<<chr;


    //        char *qseq = (char *)malloc(len);

    //        for(int i=0; i< len ; i++){
    //            qseq[i] = seq_nt16_str[bam_seqi(q,i)]; //gets nucleotide id and converts them into IUPAC id.
    //        }



    //        qDebug()<<chr<<pos<<len<<qseq<<q<<q2;

    //        //        if(strcmp(chrom, chr) == 0){

    //        //            if(locus > pos+len){
    //        //                printf("%s\t%d\t%d\t%s\t%s\t%d\n",chr,pos,len,qseq,q,q2);
    //        //            }
    //        //        }
    //    }



    return false;
}
