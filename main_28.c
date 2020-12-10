#include "odu_28.h"

#include <stdio.h>
#include <math.h>

char** error_messages = {
    "Continue processing.\n",
    "Error code 1 (file doesn't exists).\n",
    "Error code 2 (file read error or not enough data in file).\n",
    "Error code 3 (output error)"

};

#define ERROR_HANDLER(X) ((X) ? {printf(error_messages[(X)]); return (X)} : printf(error_messages[(X)]))

typedef enum {
    SUCCESS,
    FILENEXST,
    READ_ERROR,
    OUTPUT_ERROR
}ErrNo;

ErrNo output(double*, int);
ErrNo parseInput(char*);
void draw(double*, double, double, double, int);

int main(int argv, char* argc[]) {
    if(argv > 1){
        char* fileName = argc[1];
        ERROR_HANDLER(parseInput(fileName));

    SMainData answer = Solver_main();
    draw(answer.Y1, sInit.a, sInit.b, sInit.h, (sInit.b - sInit.a) / sInit.h);

   output(answer.Y1, (sInit.b - sInit.a) / sInit.h);
     

    
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

ErrNo output(double* y, int n)
{
    FILE* f = NULL;
    fopen_s(&f, "Data.out", "w");
    
    int err = fprintf_s(f, "%d", n);

    if(err < 0){
        return OUTPUT_ERROR;
    }

    for(int i = 0; i < n; i++){
        int err = fprintf_s(f, "%lf", y[i]);

        if(err < 0){
            return OUTPUT_ERROR;
        }
    }

    return SUCCESS;
}


void draw(double* y, double a, double b, double h, int n)
{
    double left = a;
    double right = b;
    FILE* pipe = _popen("gnuplot -persistent", "w");

    fprintf(pipe, "plot '-' with linespoints pointtype 0 lw 6 lt rgb \"#ff0000\" title \"True function\"");
    fprintf(pipe, " , '-' with linespoints pointtype 0 lw 2 lt rgb \"#00ff00\" title \"Approximation\"\n");

    for(;left < right; left += h){
        fprintf(pipe, "%lf %lf\n", left, 3*left + exp(-2*left));
    }

    fprintf(pipe, "%s\n", "e");
    fflush(pipe);

    left = a;
    for(int i = 0; i < n; i++, left += h){
        fprintf(pipe, "%lf %lf\n", left, y[i]);
    }

    fprintf(pipe, "%s\n", "e");
    fflush(pipe);
    _pclose(pipe);
}