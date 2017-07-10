/*
Copyright 2016-17 Sacha Schutz

    This file is part of FastQt.

    FastQt is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FastQt is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FastQt.  If not, see <http://www.gnu.org/licenses/>.

    @author : Pierre Lindenbaum from FastQC <http://www.bioinformatics.babraham.ac.uk/projects/fastqc/>
    @author : Sacha Schutz <sacha@labsquare.org>
    @author : Pierre Marijon <pierre@marijon.fr>
*/
#include "fastqreader.h"
#include "sequence.h"


FastqReader::FastqReader(QIODevice *device)
    :AbstractSequenceReader(device)
{


}



bool FastqReader::next()
{


    Sequence readSequence;

    // read ID


    readSequence.setId(device()->readLine());

    // to make compatible with QUazip
    if (readSequence.id().isEmpty())
        return false;

    // read sequence
    readSequence.setSequence(device()->readLine());
    // read unused +
    device()->readLine();
    // read qualities
    readSequence.setQuality(device()->readLine());


    setSequence(readSequence);

    return true;
}


