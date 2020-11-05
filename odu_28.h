//
// Created by ZexUlt on 24.10.2020.
//

#ifndef PRAKT_2020_ODU_28_H
#define PRAKT_2020_ODU_28_H

#include "funk_28.h"

typedef struct {
    double* Y1;
    double* Y2;
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



void Solver_main();
void getStartingPoints(double* storageArray);
double* expandArray(double* arrayToExpand);
void allocateMemory();
#endif // PRAKT_2020_ODU_28_H
