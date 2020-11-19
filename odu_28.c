//
// Created by ZexUlt on 24.10.2020.
//

#include "odu_28.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>


void Solver_main()
{
    int n1, n2;
    do{
        n1 = (sInit.b - sInit.a)/ sInit.h;
        sInit.h /= 2;
        n2 = (sInit.b - sInit.a)/ sInit.h;

        ShootingMethod(data.Y1, data.Y2, data.T, n1);
        ShootingMethod(data.Y1_, data.Y2_, data.T_, n2);
    }while(metric(data.Y1, data.Y1_, n1) < sInit.eps);
}


void ShootingMethod(double* y1, double* y2, double* T, int n)
{
    double tr = 0; // Right point for shooting
    double tl;
    double t1 = sInit.a;

    if(y1 != NULL && y2 != NULL && T != NULL){
        free(y1);
        free(y2);
        free(T);
    }

    y1 = (double*) malloc(n * sizeof(double));
    y2 = (double*) malloc(n * sizeof(double));
    T = (double*) malloc(n * sizeof(double));

    y1[0] = sInit.y_a;
    y2[0] = tr;
    T[0] = t1;

    GetStartingPoints(y1, y2, T);
    Adams(y1, y2, T, n);

    printf("%lf", f2(T[n - 1], y1[n - 1], y2[n - 1]));
    tl = tr;

    do{
        tl -= .1;

        free(T);
        free(y1);
        free(y2);

        y1 = (double*) malloc(n * sizeof(double));
        y2 = (double*) malloc(n * sizeof(double));
        T = (double*) malloc(n * sizeof(double));

        y1[0] = sInit.y_a;
        y2[0] = tl;
        T[0] = tl;

        GetStartingPoints(y1, y2, T);
        Adams(y1, y2, T, n);

    }while (f2(T[n - 1], y1[n - 1], y2[n - 1]) < 0);

    double m;

    while(1){
        m = (tl + tr)/2;

        free(T);
        free(y1);
        free(y2);

        y1 = (double*) malloc(n * sizeof(double));
        y2 = (double*) malloc(n * sizeof(double));
        T = (double*) malloc(n * sizeof(double));

        y1[0] = sInit.y_a;
        y2[0] = tl;
        T[0] = tl;

        GetStartingPoints(y1, y2, T);
        Adams(y1, y2, T, n);

        if(fabs(f2(T[n - 1], y1[n - 1], y2[n - 1])) <= sInit.eps){
            break;
        }else if(f2(T[n - 1], y1[n - 1], y2[n - 1]) > 0){
            tr = m;
        }else{
            tl = m;
        }
    }

//    return loss;
}

void GetStartingPoints(double* Y1, double* Y2, double* T)
{
    double k1, k2, k3, k4, l1, l2, l3, l4;

    for(int i = 0; i < 4; i++){
        k1 = f1(T[i], Y1[i], Y2[i])*sInit.h;
        l1 = f2(T[i], Y1[i], Y2[i])*sInit.h;
        k2 = f1(T[i] + sInit.h/2, Y1[i] + k1/2, Y2[i] + l1/2)*sInit.h;
        l2 = f2(T[i] + sInit.h/2, Y1[i] + k1/2, Y2[i] + l1/2)*sInit.h;
        k3 = f1(T[i] + sInit.h/2, Y1[i] + k2/2, Y2[i] + l2/2)*sInit.h;
        l3 = f2(T[i] + sInit.h/2, Y1[i] + k2/2, Y2[i] + l2/2)*sInit.h;
        k4 = f1(T[i] + sInit.h/2, Y1[i] + k3/2, Y2[i] + l3/2)*sInit.h;
        l4 = f2(T[i] + sInit.h/2, Y1[i] + k3/2, Y2[i] + l3/2)*sInit.h;

        Y1[i + 1] = Y1[i] + (k1 + 2*k2 + 2*k3 + k4)/6;
        Y2[i + 1] = Y2[i] + (l1 + 2*l2 + 2*l3 + l4)/6;
        T[i + 1] = T[i] + sInit.h;
    }
}

void Adams(double* Y1, double* Y2, double* T, int n)
{
    for(int i = 3; i < n - 1; i++){
        Y1[i + 1] = Y1[i] + sInit.h*(
                55*f1(T[i], Y1[i], Y2[i])
                - 59*f1(T[i - 1], Y1[i - 1], Y2[i - 1])
                + 37*f1(T[i - 2], Y1[i - 2], Y2[i - 2])
                - 9*f1(T[i - 3], Y1[i - 3], Y2[i - 3]))/24;

        Y2[i + 1] = Y2[i] + sInit.h*(
                55*f2(T[i], Y1[i], Y2[i])
                - 59*f2(T[i - 1], Y1[i - 1], Y2[i - 1])
                + 37*f2(T[i - 2], Y1[i - 2], Y2[i - 2])
                - 9*f2(T[i - 3], Y1[i - 3], Y2[i - 3]))/24;

        T[i + 1] = T[i] + sInit.h;
    }
}

double sum(double *array, int _size)
{
    if(_size <= 0){
        return 0;
    }else if(_size == 1){
        return array[0];
    }else{
        return sum(array, _size/2) + sum(array + _size/2, _size - _size/2);
    }
}

double metric(double* y1, double* y2, int n)
{
    double* tmp = (double*)malloc(n * sizeof(double));
    for(int i = 0, j = 0; i < n; i++, j += 2){
        tmp[i] = y1[i] - y2[j];
        tmp[i] *= tmp[i]/n;
    }
    return sum(tmp, n);
}