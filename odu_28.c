//
// Created by ZexUlt on 24.10.2020.
//

#include "odu_28.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

SInitialData sInit;
double* _Y1__;
double* _Y2__;
double* _T__;
double* Y1_;
double* Y2_;
double* T_;

SMainData Solver_main()
{
    int n1, n2;
    double acc;
    SMainData result1, result2;
    do{
        n1 = (sInit.b - sInit.a)/ sInit.h;
        sInit.h /= 2;
        n2 = (sInit.b - sInit.a)/ sInit.h;

        printf("%d %d %.10lf\n", n1, n2, sInit.eps);
        result1 = ShootingMethod(_Y1__, _Y2__, _T__, n1 + 1, sInit.h*2);
        result2 = ShootingMethod(Y1_, Y2_, T_, n2 + 1, sInit.h);
        acc = metric(result1.Y1, result2.Y1, n1);
//        for(int i = 0; i < n1; i++)
//            printf("%lf ", result1.Y1[i]);
//        printf("\n");
//        for(int i = 0; i < n2; i++)
//            printf("%lf ", result2.Y1[i]);
    }while(acc > sInit.eps);

    return result2;
}


SMainData ShootingMethod(double* y1, double* y2, double* __T, int n, double h)
{
    double tr = atan((sInit.y_b - sInit.y_a)/(sInit.b - sInit.a)); // Right point for shooting
    double tl = 0;
    double t1 = sInit.a;

    if(y1 != NULL && y2 != NULL && __T != NULL){
        free(y1);
        free(y2);
        free(__T);
    }

    y1 = (double*) calloc(n, sizeof(double));
    y2 = (double*) malloc(n * sizeof(double));
    __T = (double*) malloc(n * sizeof(double));

    y1[0] = sInit.y_a;
    y2[0] = tr;
    __T[0] = t1;

    GetStartingPoints(y1, y2, __T, h);
    Adams(y1, y2, __T, n, h);

    int isGPositive = 0;
    if(g(__T[n - 1], y1[n - 1], y2[n - 1]) > 0){
        tl = tr;
        isGPositive = 1;
    } else {
        swap(&tl, &tr);
        tr = tl;
        isGPositive = 0;
    }


    do{
        if(isGPositive){
            tl -= .1;
        } else {
            tr += .1;
        }

        free(__T);
        free(y1);
        free(y2);

        y1 = (double*) malloc(n * sizeof(double));
        y2 = (double*) malloc(n * sizeof(double));
        __T = (double*) malloc(n * sizeof(double));

        y1[0] = sInit.y_a;
        y2[0] = isGPositive ? tl : tr;
        __T[0] = t1;

        GetStartingPoints(y1, y2, __T, h);
        Adams(y1, y2, __T, n, h);
//        for(int i = 0; i < n; i++){
//            printf("%lf ", y1[i]);
//        }
//        printf("\n");
//        for(int i = 0; i < n; i++){
//            printf("%lf ", y2[i]);
//        }
//        printf("\n");
//        for(int i = 0; i < n; i++){
//            printf("%lf ", __T[i]);
//        }
//        printf("\n");
    }while (isGPositive ? g(__T[n - 1], y1[n - 1], y2[n - 1]) > 0 : g(__T[n - 1], y1[n - 1], y2[n - 1]) < 0);

    double m;

    while(1){
        m = (tl + tr)/2;
        free(__T);
        free(y1);
        free(y2);

        y1 = (double*) malloc(n * sizeof(double));
        y2 = (double*) malloc(n * sizeof(double));
        __T = (double*) malloc(n * sizeof(double));

        y1[0] = sInit.y_a;
        y2[0] = m;
        __T[0] = t1;

        GetStartingPoints(y1, y2, __T, h);
        Adams(y1, y2, __T, n, h);


//        printf("%.15lf\n", g(__T[n - 1], y1[n - 1], y2[n - 1]));

        if(fabs(g(__T[n - 1], y1[n - 1], y2[n - 1])) <= sInit.eps){
            break;
        }else if(g(__T[n - 1], y1[n - 1], y2[n - 1]) > 0){
            tr = m;
        }else{
            tl = m;
        }
    }
    SMainData data;
    data.Y1 = malloc(n * sizeof(double));
    data.Y2 = malloc(n * sizeof(double));
    data.T = malloc(n * sizeof(double));

    memcpy_s(data.Y1, n*sizeof(double), y1, n*sizeof(double));
    memcpy_s(data.Y2, n*sizeof(double), y2, n*sizeof(double));
    memcpy_s(data.T, n*sizeof(double), __T, n*sizeof(double));
//    for(int i = 0; i < n; i++)
//        printf("%lf ", data.Y1[i]);
//    printf("\n");

    return data;
}

void GetStartingPoints(double* Y1, double* Y2, double* __T, double h)
{
    double k1, k2, k3, k4, l1, l2, l3, l4;

    for(int i = 0; i < 4; i++){
        k1 = f1(__T[i], Y1[i], Y2[i])*h;
        l1 = f2(__T[i], Y1[i], Y2[i])*h;
        k2 = f1(__T[i] + h/2, Y1[i] + k1/2, Y2[i] + l1/2)*h;
        l2 = f2(__T[i] + h/2, Y1[i] + k1/2, Y2[i] + l1/2)*h;
        k3 = f1(__T[i] + h/2, Y1[i] + k2/2, Y2[i] + l2/2)*h;
        l3 = f2(__T[i] + h/2, Y1[i] + k2/2, Y2[i] + l2/2)*h;
        k4 = f1(__T[i] + h, Y1[i] + k3, Y2[i] + l3)*h;
        l4 = f2(__T[i] + h, Y1[i] + k3, Y2[i] + l3)*h;

        Y1[i + 1] = Y1[i] + (k1 + 2*k2 + 2*k3 + k4)/6;
        Y2[i + 1] = Y2[i] + (l1 + 2*l2 + 2*l3 + l4)/6;
        __T[i + 1] = __T[i] + h;
    }
}

void Adams(double* Y1, double* Y2, double* __T, int n, double h)
{
    for(int i = 3; i < n - 1; i++){
        Y1[i + 1] = Y1[i] + h*(
                55*f1(__T[i], Y1[i], Y2[i])
                - 59*f1(__T[i - 1], Y1[i - 1], Y2[i - 1])
                + 37*f1(__T[i - 2], Y1[i - 2], Y2[i - 2])
                - 9*f1(__T[i - 3], Y1[i - 3], Y2[i - 3]))/24;

        Y2[i + 1] = Y2[i] + h*(
                55*f2(__T[i], Y1[i], Y2[i])
                - 59*f2(__T[i - 1], Y1[i - 1], Y2[i - 1])
                + 37*f2(__T[i - 2], Y1[i - 2], Y2[i - 2])
                - 9*f2(__T[i - 3], Y1[i - 3], Y2[i - 3]))/24;

        __T[i + 1] = __T[i] + h;
    }
}

double g(double t, double y1, double y2)
{
    return y1 - sInit.y_b;
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

double metric(const double* y1, const double* y2, const int n)
{
    double* tmp = (double*)malloc(n * sizeof(double));
    for(int i = 0, j = 0; i < n; i++, j += 2){
        tmp[i] = y1[i] - y2[i*2];
        tmp[i] *= tmp[i]/n;
    }
    return sum(tmp, n);
}

void swap(double* a, double* b)
{
    double tmp = *a;
    *a = *b;
    *b = tmp;
}
