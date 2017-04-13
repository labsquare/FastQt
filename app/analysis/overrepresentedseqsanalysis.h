#ifndef OVERREPRESENTEDSEQSANALYSIS_H
#define OVERREPRESENTEDSEQSANALYSIS_H
#include <QtCore>
#include "analysis.h"

class ResultsModel;
class OverRepresentedSeq;
class OverRepresentedSeqsAnalysis;

class OverRepresentedSeqsAnalysis : public Analysis
{
    Q_OBJECT
public:
    OverRepresentedSeqsAnalysis(QObject * parent = nullptr);

    void processSequence(const Sequence& sequence) Q_DECL_OVERRIDE;
    void reset() Q_DECL_OVERRIDE;
    QWidget* createResultWidget() Q_DECL_OVERRIDE;
    void save(const QString& path) Q_DECL_OVERRIDE;



protected:
    QHash<QByteArray, quint64> mSequences;
    quint64 mCount = 0;
    quint64 mCountAtUniqueLimit = 0;
    quint64 mUniqueSequenceCount = 0;
    bool mFrozen = false;
    static const int OBSERVATION_CUTOFF = 100000;

};


class OverRepresentedSeq
{
public:
    OverRepresentedSeq(const QByteArray& seq, quint64 count, double percentage);
    const QByteArray& seq() const;
    quint64 count() const;
    double percentage() const;

    bool operator <(const OverRepresentedSeq& other) const;

private:
    QByteArray mSeq;
    quint64 mCount;
    double mPercentage;

};

class ResultsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ResultsModel(QObject * parent = nullptr);
    ~ResultsModel();

    void add(const QByteArray& seq, quint64 count, double percentage);


    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void sort();



    void clear() ;


private:
    QList<OverRepresentedSeq> mSeqs;


};

#endif // OVERREPRESENTEDSEQSANALYSIS_H
