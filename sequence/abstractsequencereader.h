/*
Copyright Copyright 2016-17 Sacha Schutz

    This file is part of CuteVCF.

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
#ifndef ABSTRACTSEQUENCEREADER_H
#define ABSTRACTSEQUENCEREADER_H
#include <QtCore>
#include "sequence.h"
/*!
 * \class AbstractSequenceReader
 * \brief Base class for all Sequence reader like FastqReader
 * Process each Sequence from a QIODevice like a file
 * \example
 * QFile file("example.fastq");
 * if (file.open(QIODevice::ReadOnly))
 * {
 *    FastqReader reader(&file);
 *    while (reader.next())
 *      {
 *          qDebug()<<reader.sequence().quality();
 *      }
 *
 * }
 */
class AbstractSequenceReader
{
public:
    AbstractSequenceReader(QIODevice * device);

    /*!
     * \brief Move to the next sequence
     * \return false if the file end has been reach.
     */
    virtual bool next() = 0;
    /*!
     * \brief percentComplete return percent of bytes processed
     * \return a a value between 0 and 100
     */
    virtual int percentComplete() const;

    /*!
     * \brief Return the current sequence.
     * Use next to get the next sequence
     * \return Sequence
     */
    const Sequence& sequence() const;

protected:
    void setSequence(const Sequence& seq);
    QIODevice * device() const;

private:
    QIODevice * mDevice;
    Sequence mSequence;
};

#endif // ABSTRACTSEQUENCEREADER_H
