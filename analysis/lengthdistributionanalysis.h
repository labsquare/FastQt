#ifndef SEQUENCELENGTHDISTRIBUTIONANALYSIS_H
#define SEQUENCELENGTHDISTRIBUTIONANALYSIS_H
#include <QtCharts>
#include "analysis.h"

using namespace QT_CHARTS_NAMESPACE;

/*!
 * \class SequenceLengthDistributionAnalysis
 * \brief This analysis generates a graph showing the distribution of fragment sizes in the file which was analysed.
 * Relative to Sequence length distribution in  FastQC module
 * <http://www.bioinformatics.babraham.ac.uk/projects/fastqc/Help/3%20Analysis%20Modules/7%20Sequence%20Length%20Distribution.html>
 */
class LengthDistributionAnalysis : public Analysis
{
public:
    LengthDistributionAnalysis();
    void processSequence(const Sequence& sequence) Q_DECL_OVERRIDE;
    void reset() Q_DECL_OVERRIDE;
    QWidget * createResultWidget() Q_DECL_OVERRIDE;

    void computeDistribution();
    QVector<int> sizeDistribution (int min, int max);


private:
    QVector<quint64> mLengthCounts;
    QVector<double> mGraphCounts;
    QVector<QString> mXCategories;
    double mMax;



};

#endif // SEQUENCELENGTHDISTRIBUTIONANALYSIS_H
