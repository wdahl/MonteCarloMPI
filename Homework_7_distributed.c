#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <mpi.h>

main(int argc, char *argv[])
{
    if(argc != 2){
        printf("Usage: mpirun -np <num of procs> ./%s <num of iterations>", argv[0]);
        exit(1);
    }

   int total_iters=atoi(argv[1]); //total iterations to do
   int rank_iters;//iterations for the rank
   double x, y;//cordinates of generated point
   int i, j, total_count=0, rank_count=0; // total count and count for specific rank of points within the circle
   double z;//result of equation
   double result;//pi estimate
   int rank, size;// proccess and total number of processes
   MPI_Status status; //recive statuses

   srand(35791246);
   
   MPI_Init(NULL,NULL);
   MPI_Comm_size(MPI_COMM_WORLD,&size);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    //get nujber of iterations each rank should do
   if(rank < total_iters%size){
       rank_iters = total_iters/size + 1;
   }
   else{
       rank_iters = total_iters/size;
   }

   timing_start();
   rank_count=0;
   //start iterations
   for ( i=0; i<rank_iters; i++) {
       //generate random point and see if it falls in the circle
      x = (double)rand()/RAND_MAX;
      y = (double)rand()/RAND_MAX;
      z = x*x+y*y;
      //falls in circle
      if (z<=1){ 
        rank_count++;
      } 
   }
   //adds each proccess total count of points the fell in the cirlce together
   MPI_Reduce(&rank_count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
   timing_stop();

    //master proccess calulates the pi estimate and prints it to the screen
   if(rank == 0){
       result=(double)total_count/total_iters*4;
       printf("# of trials= %d , estimate of pi is: %lf \n",total_iters,result);
        print_timing();
   }

   MPI_Finalize();
  
}