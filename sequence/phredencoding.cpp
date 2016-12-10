#include "phredencoding.h"

PhredEncoding::PhredEncoding(const QString& n, int offset)
    :mName(n), mOffset(offset)
{

}

PhredEncoding PhredEncoding::fastqEncodingOffset(char lowestChar)
{
    qDebug()<< int(lowestChar);

    if (lowestChar < 33){
        qCritical()<<QString("No known encodings with chars < 33 (Yours was %1)").arg(lowestChar);
        return PhredEncoding();
    }
    else if (lowestChar < 64)
        return PhredEncoding("Sanger / Illumina 1.9", SANGER_ENCODING_OFFSET);

    // There are potentially two encodings using an offset of 64.  Illumina
    // v1.3 allowed quality values of 1, whereas from v1.5 onwards the lowest
    // value allowed was 2.  If we guess wrong between these two then it's not
    // the end of the world since they use the same offset.

    else if (lowestChar == ILLUMINA_1_3_ENCODING_OFFSET+1) {
        return PhredEncoding("Illumina 1.3", ILLUMINA_1_3_ENCODING_OFFSET);
    }
    else if (lowestChar <= 126) {
        return PhredEncoding("Illumina 1.5", ILLUMINA_1_3_ENCODING_OFFSET);
    }

    qCritical()<<QString("No known encodings with chars > 126 (Yours was %1)").arg(lowestChar);
    return PhredEncoding();

}

bool PhredEncoding::isValid()
{
    return !mName.isEmpty();
}
