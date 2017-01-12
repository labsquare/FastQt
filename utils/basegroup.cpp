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
#include "basegroup.h"

BaseGroup::BaseGroup()
{

}

BaseGroup::BaseGroup(int lowerCount, int upperCount)
    :mLowerCount(lowerCount), mUpperCount(upperCount)
{

}

int BaseGroup::lowerCount() const
{
    return mLowerCount;
}

int BaseGroup::upperCount() const
{
    return mUpperCount;
}

bool BaseGroup::contains(int value) const
{
    return value >= lowerCount() && value <= upperCount();
}

QString BaseGroup::toString() const
{
    if (lowerCount() == upperCount())
        return QString::number(lowerCount());
    else
        return QString("%1-%2").arg(lowerCount()).arg(upperCount());
}

QVector<BaseGroup> BaseGroup::makeBaseGroups(int maxLength)
{

    return makeLinearBaseGroups(maxLength);

    //    int startingBase = 1;
    //    int interval = 1;

    //    QList<BaseGroup> groups;

    //    while (startingBase <= maxLength) {

    //        int endBase = startingBase+(interval-1);
    //        if (endBase > maxLength) endBase = maxLength;

    //        BaseGroup bg(startingBase, endBase);
    //        groups.append(bg);

    //        startingBase += interval;

    //        // See if we need to increase the interval
    //        if (startingBase == 10 && maxLength > 75) {
    //            interval = 5;
    //        }
    //        if (startingBase == 50 && maxLength > 200) {
    //            interval = 5;
    //        }
    //        if (startingBase == 100 && maxLength > 300) {
    //            interval = 10;
    //        }
    //        if (startingBase == 500 && maxLength > 1000) {
    //            interval = 100;
    //        }
    //        if (startingBase == 1000 && maxLength > 2000) {
    //            interval = 500;
    //        }


    //    }

    //    return groups;

}

QVector<BaseGroup> BaseGroup::makeUngroupedGroups(int maxLength)
{

    int startingBase = 1;
    int interval = 1;

    QVector<BaseGroup> groups;

    while (startingBase <= maxLength) {

        int endBase = startingBase+(interval-1);
        if (endBase > maxLength) endBase = maxLength;

        BaseGroup bg(startingBase, endBase);
        groups.append(bg);

        startingBase += interval;
    }

    return groups;
}

QVector<BaseGroup> BaseGroup::makeExponentialBaseGroups(int maxLength)
{
    int startingBase = 1;
    int interval = 1;

    QVector<BaseGroup> groups;

    while (startingBase <= maxLength) {

        int endBase = startingBase+(interval-1);
        if (endBase > maxLength) endBase = maxLength;

        BaseGroup bg(startingBase, endBase);
        groups.append(bg);

        startingBase += interval;

        // See if we need to increase the interval
        if (startingBase == 10 && maxLength > 75) {
            interval = 5;
        }
        if (startingBase == 50 && maxLength > 200) {
            interval = 10;
        }
        if (startingBase == 100 && maxLength > 300) {
            interval = 50;
        }
        if (startingBase == 500 && maxLength > 1000) {
            interval = 100;
        }
        if (startingBase == 1000 && maxLength > 2000) {
            interval = 500;
        }


    }

    return groups;
}

QVector<BaseGroup> BaseGroup::makeLinearBaseGroups(int maxLength)
{
    // For lengths below 75bp we just return everything.
    if (maxLength <= 75) return makeUngroupedGroups(maxLength);

    // We need to work out what interval we're going to use.
    int interval = getLinearInterval(maxLength);


    int startingBase = 1;

    QVector<BaseGroup> groups;

    while (startingBase <= maxLength) {

        int endBase = startingBase+(interval-1);

        if (startingBase < 10) endBase = startingBase;

        if (startingBase == 10 && interval > 10) {
            endBase = interval-1;
        }

        if (endBase > maxLength) endBase = maxLength;

        BaseGroup bg(startingBase, endBase);
        groups.append(bg);

        if (startingBase < 10) {
            startingBase +=1;
        }
        else if (startingBase == 10 && interval > 10) {
            startingBase = interval;
        }
        else {
            startingBase += interval;
        }

    }

    return groups;
}

int BaseGroup::getLinearInterval(int length)
{
    // The the first 9bp as individual residues since odd stuff
    // can happen there, then we find a grouping value which gives
    // us a total set of groups below 75.  We limit the intervals
    // we try to sensible whole numbers.

    QVector<int> baseValues = {2,5,10};
    int multiplier = 1;

    while (true) {
        for (int b=0;b<baseValues.length();b++) {
            int interval = baseValues[b] * multiplier;
            int groupCount = 9 + ((length-9)/interval);
            if ((length-9) % interval != 0) {
                groupCount += 1;
            }
            if (groupCount < 75) return interval;
        }

        multiplier *= 10;

        if (multiplier == 10000000) {
            qCritical()<<Q_FUNC_INFO<<QString("Couldn't find a sensible interval grouping for length '%1'").arg(length);
        }
    }
}


