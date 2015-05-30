/* -*- fabonacci running on Raspberry Pi cluster, have fun!!; -*- */
/*
 *  Author: Hub on IT Engineering Solutions
 *
 *  Documentation:
 *  http://hubonit.com/ideas/?p=300
 */

#include "mpi.h"
#include <stdio.h>
#include <math.h>

int Fibonacci(int x)
{
   if (x == 0) return 0;
   else if ( x == 1 ) return 1;
   else return ( Fibonacci(x-1) + Fibonacci(x-2) );
} 


int main(int argc,char *argv[])
{
    int    n, myid, numprocs, i;
    double mypi, pi, h, sum, x;
    double startwtime = 0.0, endwtime;
    int    namelen;
    char   processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Get_processor_name(processor_name,&namelen);

    fprintf(stdout,"Process %d of %d is on %s\n", myid, numprocs, processor_name);
    fflush(stdout);

    int a[40];
    n = 40;
    if (myid == 0) startwtime = MPI_Wtime();

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

   for ( i = myid + 1 ; i <= n ; i += numprocs)
   {
      printf("%d\n", Fibonacci(i));
   }


    if (myid == 0) {
	endwtime = MPI_Wtime();

	printf("wall clock time = %f\n", endwtime-startwtime);	       
	fflush(stdout);
    }

    MPI_Finalize();
    return 0;
}
