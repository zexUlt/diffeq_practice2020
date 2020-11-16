//
// Created by ZexUlt on 24.10.2020.
//

#include "odu_28.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>


void Solver_main()
{

}


void ShootingMethod(int n)
{
    double tr = 0; // Right point for shooting
    double tl;
    double t1 = sInit.a;
    double loss;

    data.Y1 = (double*) calloc(n, sizeof(double));
    data.Y2 = (double*) calloc(n, sizeof(double));
    data.T = (double*) calloc(n, sizeof(double));

    data.Y1[0] = sInit.y_a;
    data.Y2[0] = tr;
    data.T[0] = t1;

    GetStartingPoints(data.Y1, data.Y2, data.T);
    Adams(data.Y1, data.Y2, data.T, n);

    printf("%lf", f2(data.T[n - 1], data.Y1[n - 1], data.Y2[n - 1]));
    tl = tr;

    do{
        tl -= .1;

        free(data.T);
        free(data.Y1);
        free(data.Y2);

        data.Y1 = (double*) calloc(n, sizeof(double));
        data.Y2 = (double*) calloc(n, sizeof(double));
        data.T = (double*) calloc(n, sizeof(double));

        data.Y1[0] = sInit.y_a;
        data.Y2[0] = tl;
        data.T[0] = tl;

        GetStartingPoints(data.Y1, data.Y2, data.T);
        Adams(data.Y1, data.Y2, data.T, n);

    }while (f2(data.T[n - 1], data.Y1[n - 1], data.Y2[n - 1]) < 0);

    double m;

    while(1){
        m = (tl + tr)/2;

        free(data.T);
        free(data.Y1);
        free(data.Y2);

        data.Y1 = (double*) calloc(n, sizeof(double));
        data.Y2 = (double*) calloc(n, sizeof(double));
        data.T = (double*) calloc(n, sizeof(double));

        data.Y1[0] = sInit.y_a;
        data.Y2[0] = tl;
        data.T[0] = tl;

        GetStartingPoints(data.Y1, data.Y2, data.T);
        Adams(data.Y1, data.Y2, data.T, n);

        if(fabs(f2(data.T[n - 1], data.Y1[n - 1], data.Y2[n - 1])) <= sInit.eps){
            break;
        }else if(f2(data.T[n - 1], data.Y1[n - 1], data.Y2[n - 1]) > 0){
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
        k1 = f1(data.T[i], data.Y1[i], data.Y2[i])*sInit.h;
        l1 = f2(data.T[i], data.Y1[i], data.Y2[i])*sInit.h;
        k2 = f1(data.T[i] + sInit.h/2, data.Y1[i] + k1/2, data.Y2[i] + l1/2)*sInit.h;
        l2 = f2(data.T[i] + sInit.h/2, data.Y1[i] + k1/2, data.Y2[i] + l1/2)*sInit.h;
        k3 = f1(data.T[i] + sInit.h/2, data.Y1[i] + k2/2, data.Y2[i] + l2/2)*sInit.h;
        l3 = f2(data.T[i] + sInit.h/2, data.Y1[i] + k2/2, data.Y2[i] + l2/2)*sInit.h;
        k4 = f1(data.T[i] + sInit.h/2, data.Y1[i] + k3/2, data.Y2[i] + l3/2)*sInit.h;
        l4 = f2(data.T[i] + sInit.h/2, data.Y1[i] + k3/2, data.Y2[i] + l3/2)*sInit.h;

        data.Y1[i + 1] = data.Y1[i] + (k1 + 2*k2 + 2*k3 + k4)/6;
        data.Y2[i + 1] = data.Y2[i] + (l1 + 2*l2 + 2*l3 + l4)/6;
        data.T[i + 1] = data.T[i] + sInit.h;
    }
}

void Adams(double* Y1, double* Y2, double* T, int n)
{
    for(int i = 3; i < n - 1; i++){
        data.Y1[i + 1] = data.Y1[i] + sInit.h*(
                55*f1(data.T[i], data.Y1[i], data.Y2[i])
                - 59*f1(data.T[i - 1], data.Y1[i - 1], data.Y2[i - 1])
                + 37*f1(data.T[i - 2], data.Y1[i - 2], data.Y2[i - 2])
                - 9*f1(data.T[i - 3], data.Y1[i - 3], data.Y2[i - 3]))/24;

        data.Y2[i + 1] = data.Y2[i] + sInit.h*(
                55*f2(data.T[i], data.Y1[i], data.Y2[i])
                - 59*f2(data.T[i - 1], data.Y1[i - 1], data.Y2[i - 1])
                + 37*f2(data.T[i - 2], data.Y1[i - 2], data.Y2[i - 2])
                - 9*f2(data.T[i - 3], data.Y1[i - 3], data.Y2[i - 3]))/24;

        data.T[i + 1] = data.T[i] + sInit.h;
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