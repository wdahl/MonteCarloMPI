#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "timing.h"

int main(int argc, char* argv[])
{
    if(argc != 2){
        printf("Usage: %s <number of iterations>\n", argv[0]);
        exit(1);
    }

   int n = atoi(argv[1]);
   double x,y;
   int i, count=0; 
   double z;
   double result;

   srand(35791246);
   count=0;

    timing_start();

   for ( i=0; i<n; i++) {
      x = (double)rand()/RAND_MAX;
      y = (double)rand()/RAND_MAX;
      z = x*x+y*y;
      if (z<=1){
          count++;
      }
    }
   result=(double)count/n*4;

    timing_stop();

   printf("# of trials= %d , estimate of pi is: %lf \n",n,result);

   print_timing();
   return 0;
}