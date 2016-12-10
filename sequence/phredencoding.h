#ifndef PHREDENCODING_H
#define PHREDENCODING_H
#include <QtCore>

class PhredEncoding
{
public:
    PhredEncoding(const QString& n = QString(), int offset = 0);

    static PhredEncoding fastqEncodingOffset(char lowestChar);
    bool isValid();

    const QString& name() const { return mName;}
    int offset() const {return mOffset;}


private:

    QString mName;
    int mOffset;
    static const int SANGER_ENCODING_OFFSET = 33;
    static const int ILLUMINA_1_3_ENCODING_OFFSET = 64;



};

#endif // PHREDENCODING_H
