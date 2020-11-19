#include "odu_28.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum {
    SUCCESS,
    FILENEXST,
    READ_ERROR
}ErrNo;

ErrNo parseInput(char*);


int main(int argv, char* argc[]) {
    if(argv > 1){
        char* fileName = argc[1];
        switch ((int) parseInput(fileName)) {
            case FILENEXST: printf("Error code 1 (file doesn't exists).\n");
                return 1;
            case READ_ERROR: printf("Error code 2 (file read error or not enough data in file).\n");
                return 2;
            case SUCCESS: printf("Continue processing.\n");
        }
    }

    SMainData answer = Solver_main();

    for(int i = 0; i < (sInit.b - sInit.a) / sInit.h; i++){
        printf("%lf ", answer.Y1[i]);
    }
    printf("\n");
    for(double i = sInit.a; i < sInit.b; i += sInit.h){
        printf("%lf ", 3*i + exp(-2*i));
    }
    return 0;
}

ErrNo parseInput(char* _fName)
{
    FILE* f = NULL;
    if(fopen_s(&f, _fName, "r") == 0){
       int err = fscanf_s(f, "%lf %lf %lf %lf %lf", &sInit.a, &sInit.b, &sInit.y_a, &sInit.y_b, &sInit.eps);

       if(err == EOF || err < 5){
           return READ_ERROR;
       }

       sInit.h = .1;
    } else {
      return FILENEXST;
    }
    return SUCCESS;
}