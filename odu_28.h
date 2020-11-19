//
// Created by ZexUlt on 24.10.2020.
//

#ifndef PRAKT_2020_ODU_28_H
#define PRAKT_2020_ODU_28_H

#include "funk_28.h"

typedef struct {
    double* Y1;
    double* Y2;
    double* T;
}SMainData;

typedef struct SInitialData{
    double a;
    double b;
    double h;
    double y_a;
    double y_b;
    double eps;
}SInitialData;

extern SInitialData sInit;
extern double* _Y1__;
extern double* _Y2__;
extern double* _T__;
extern double* Y1_;
extern double* Y2_;
extern double* T_;

// Main solver functions
SMainData Solver_main();
SMainData ShootingMethod(double*, double*, double*, int n, double h);
void GetStartingPoints(double* Y1, double* Y2, double* T, double h);
void Adams(double* Y1, double* Y2, double* T, int n, double h);
double metric(const double* y1, const double* y2, const int n);
double g(double t, double y1, double y2);

// Helper functions
double sum(double* array, int _size);
void swap(double* a, double* b);

#endif // PRAKT_2020_ODU_28_H
