#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <QtCore>

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
