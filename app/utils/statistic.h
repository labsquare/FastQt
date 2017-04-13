#ifndef STATISTIC_H
#define STATISTIC_H
/* Define section */
#include <cmath>


template <typename Container>
inline double mean(Container &c)
{
    double n = 0;
    double sum = 0;
    for(auto it : c)
    {
        sum += it;
        n++;
    }
    return sum/n;

}
template <typename Container>
inline double mean_ponderate(Container& c)
{
        double n = 0;
        double sum = 0;
        for(auto it = c.begin(); it != c.end(); it++)
        {
            sum += (it - c.begin()) * *it;
            n += *it;
        }

        return sum/n;
}
template <typename Container>
inline double stddev(Container& c, double mean = 0)
{
        double stddev = 0;
        double sum = 0;

        for(auto it = c.begin(); it != c.end(); it++)
        {
            sum += *it;
            stddev += pow((it - c.begin()) - mean, 2) * *it;
        }

        stddev /= sum - 1;

        return sqrt(stddev);
}


double normal_distribution(double mean, double stddev, double x)
{
    double lhs = 1/(sqrt(2*M_PI*stddev*stddev));
    double rhs = pow(M_E, 0 - (pow(x-mean,2)/(2*stddev*stddev)));

    return lhs*rhs;
}

#endif // STATISTIC_H
