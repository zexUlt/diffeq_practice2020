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
    double* Y1_;
    double* Y2_;
    double* T_;
    int n;
}SMainData;

typedef struct SInitialData{
    double a;
    double b;
    double h;
    double y_a;
    double y_b;
    double eps;
}SInitialData;

SInitialData sInit;
static SMainData data;


// Main solver functions
void Solver_main();
void ShootingMethod(int n);
void GetStartingPoints(double* Y1, double* Y2, double* T);
void Adams(double* Y1, double* Y2, double* T, int n);
double metric(double* y1, double* y2, int n);

// Helper functions
double sum(double* array, int _size);

#endif // PRAKT_2020_ODU_28_H
