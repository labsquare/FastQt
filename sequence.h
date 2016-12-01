#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <QtCore>

class Sequence
{
public:
    Sequence();
    Sequence(const QString& id, const QString& sequence, const QString& quality);


    const QString &id() const;
    void setId(const QString &id);

    const QString &sequence() const;
    void setSequence(const QString &sequence);

    const QString &quality() const;
    void setQuality(const QString &quality);

private:
    QString mId;
    QString mSequence;
    QString mQuality;



};
Q_DECLARE_METATYPE(Sequence)

#endif // SEQUENCE_H
