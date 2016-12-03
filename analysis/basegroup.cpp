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

QList<BaseGroup> BaseGroup::makeBaseGroups(int maxLength)
{

    int startingBase = 1;
    int interval = 1;

    QList<BaseGroup> groups;

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
            interval = 5;
        }
        if (startingBase == 100 && maxLength > 300) {
            interval = 10;
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


