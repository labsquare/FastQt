/*
Copyright Copyright 2016-17 Sacha Schutz

    This file is part of FastQt.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

    @author : Pierre Lindenbaum from FastQC <http://www.bioinformatics.babraham.ac.uk/projects/fastqc/>
    @author : Sacha Schutz <sacha@labsquare.org>
    @author : Pierre Marijon <pierre@marijon.fr>
*/
#include "phredencoding.h"

PhredEncoding::PhredEncoding(const QString& n, int offset)
    :mName(n), mOffset(offset)
{

}

PhredEncoding PhredEncoding::fastqEncodingOffset(char lowestChar)
{
    qDebug()<< int(lowestChar);

    if (lowestChar < 33){
        qCritical()<<QStringLiteral("No known encodings with chars < 33 (Yours was %1)").arg(lowestChar);
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

    qCritical()<<QStringLiteral("No known encodings with chars > 126 (Yours was %1)").arg(lowestChar);
    return PhredEncoding();

}

bool PhredEncoding::isValid()
{
    return !mName.isEmpty();
}
