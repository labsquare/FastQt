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
#ifndef BASEGROUP_H
#define BASEGROUP_H
#include <QtCore>
/*!
 * \class BaseGroup
 * \brief This class groups nucleotid position in a range.
 * This is used in PerBaseQualityAnalysis and allow displaying all sequence
 * @see FastQC BaseGroup class for more detail
 */
class BaseGroup
{
public:
    BaseGroup();
    BaseGroup(int lowerCount, int upperCount);
    int lowerCount() const;
    int upperCount() const;
    bool contains(int value) const;
    QString toString() const;




    static QVector<BaseGroup> makeBaseGroups(int maxLength);
    static QVector<BaseGroup> makeUngroupedGroups(int maxLength);
    static QVector<BaseGroup> makeExponentialBaseGroups(int maxLength);
    static QVector<BaseGroup> makeLinearBaseGroups(int maxLength);

protected:
    static int getLinearInterval (int length);


private:
    int mLowerCount;
    int mUpperCount;
};

#endif // BASEGROUP_H
