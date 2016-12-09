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
