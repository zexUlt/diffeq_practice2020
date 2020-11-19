//
// Created by ZexUlt on 24.10.2020.
//
#include "funk_28.h"

double f1(double x, double y1, double y2)
{
    return y2;
}

double f2(double x, double y1, double y2)
{
    return f(x) - p(x)*y2 - q(x)*y1;
}

static double p(double x)
{
    return 4*x/(2*x + 1);
}

static double q(double x)
{
    return -4*x/(2*x + 1);
}

static double f(double x)
{
    return 0;
}