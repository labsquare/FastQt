#ifndef STATISTIC_H
#define STATISTIC_H
/* Define section */
# define M_PI 3.14159265358979323846 /* pi */
# define M_NEPER 2.718281828459045235359 /* e */


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


template<typename MEAN, typename STDDEV, typename X>
X normal_distribution(MEAN _mean, STDDEV _stddev, X x)
{
    double lhs = 1/(sqrt(2*M_PI*_stddev*_stddev));
    double rhs = pow(M_E, 0 - (pow(x-_mean,2)/(2*_stddev*_stddev)));

    return lhs*rhs;
}

#endif // STATISTIC_H
