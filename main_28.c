#include "odu_28.h"

#include <stdio.h>
#include <stdlib.h>

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
                break;
            case READ_ERROR: printf("Error code 2 (file read error or not enough data in file).\n");
                break;
            case SUCCESS: printf("Continue processing.\n");
        }
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

       sInit.h = sInit.y_a;
    } else {
      return FILENEXST;
    }
    return SUCCESS;
}