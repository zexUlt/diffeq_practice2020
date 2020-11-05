//
// Created by ZexUlt on 24.10.2020.
//

#include "odu_28.h"

void solver_main()
{
    double tr = 0; // Right point for shooting
    double t1 = sInit.a;
    double k1, k2, k3, k4, l1, l2, l3, l4;

    data.n = (sInit.b - sInit.a)/sInit.h;

    data.Y1 = (double*) malloc(data.n*sizeof(double));
    data.Y2 = (double*) malloc(data.n*sizeof(double));
    data.T = (double*) malloc(data.n*sizeof(double));

    data.Y1[0] = sInit.y_a;
    data.Y2[0] = sInit.y_b;
    data.T[0] = t1;

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

    for(int i = 3; i < data.n - 1; i++){
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

void getStartingPoints(double* storageArray)
{

}