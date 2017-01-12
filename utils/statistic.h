#ifndef STATISTIC_H
#define STATISTIC_H

/* Define section */
# define M_PI 3.14159265358979323846 /* pi */
# define M_NEPER 2.718281828459045235359 /* e */

template<template<typename> typename CONTENER, typename TYPE, typename OUT>
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

template<template<typename> typename CONTENER, typename TYPE, typename OUT>
OUT mean_ponderate(CONTENER<TYPE>& contener)
{
    double n = 0;
    OUT sum = 0;
    for(size_t i = 0; i != contener.size(); i++)
    {
        sum += i * contener[i];
        n += contener[i];
    }

    return sum/n;
}

template<template<typename> typename CONTENER, typename TYPE, typename OUT>
OUT stddev_ponderate(CONTENER<TYPE>& contener)
{
    /* https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Weighted_incremental_algorithm */
    OUT sum = 1.0;
    OUT mean, old_mean = 0.0;
    OUT s = 0.0;

    for(size_t i = 0; i != contener.size(); i++)
    {
        sum += i;
        old_mean = mean;
        mean += (i / sum) * (contener[i] - mean);
        s += i * (contener[i] - old_mean) * (contener[i] - mean);
     }


    return s / sum;
}

template<typename MEAN, typename STDDEV, typename X>
X normal_distribution(MEAN _mean, STDDEV _stddev, X x)
{
    X std_value = (1.0/sqrt(2.0 * M_PI)) * exp(-0.5*x*x);
    return (std_value + _mean +_mean) * _stddev;
}

#endif // STATISTIC_H
