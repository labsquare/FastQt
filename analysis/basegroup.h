#ifndef BASEGROUP_H
#define BASEGROUP_H
#include <QtCore>

class BaseGroup
{
public:
    BaseGroup();
    BaseGroup(int lowerCount, int upperCount);
    int lowerCount() const;
    int upperCount() const;
    bool contains(int value) const;
    QString toString() const;


    static QList<BaseGroup> makeBaseGroups(int maxLength);


private:
    int mLowerCount;
    int mUpperCount;
};

#endif // BASEGROUP_H
