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
#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <QtCore>
/*!
 * \class Sequence
 * \brief Sequence contains identifier, nucleotid sequence and quality
 * @see AbstractSequenceReader
 */
class Sequence
{
public:
    Sequence();
    Sequence(const QByteArray& id, const QByteArray& sequence, const QByteArray& quality);


    const QByteArray &id() const;
    void setId(const QByteArray &id);

    const QByteArray &sequence() const;
    void setSequence(const QByteArray &sequence);

    const QByteArray &quality() const;
    void setQuality(const QByteArray &quality);




    int size() const;

private:
    QByteArray mId;
    QByteArray mSequence;
    QByteArray mQuality;

};
Q_DECLARE_METATYPE(Sequence)

#endif // SEQUENCE_H
