#ifndef STATISTIC_H
#define STATISTIC_H

/* Define section */
# define M_PI 3.14159265358979323846 /* pi */
# define M_NEPER 2.718281828459045235359 /* e */


template<template<class STUPIDWINDOW> class CONTENER, class TYPE, class OUT>
OUT mean(CONTENER<TYPE>& contener)
{
    double n = 0;
    OUT sum = 0;
    for(TYPE it : contener)
    {
        sum += it;
        n++;
    }

    return sum/n;
}

template<template<typename> class CONTENER, typename TYPE, typename OUT>
OUT mean_ponderate(CONTENER<TYPE>& contener)
{
    double n = 0;
    OUT sum = 0;

    for(auto it = contener.begin(); it != contener.end(); it++)
    {
        sum += (it - contener.begin()) * *it;
        n += *it;
    }

    return sum/n;
}

template<template<typename> class CONTENER, typename TYPE, typename OUT>
OUT stddev(CONTENER<TYPE>& contener, OUT mean)
{
    OUT stddev = 0;
    TYPE sum = 0;

    for(auto it = contener.begin(); it != contener.end(); it++)
    {
        sum += *it;
        stddev += pow((it - contener.begin()) - mean, 2) * *it;
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
