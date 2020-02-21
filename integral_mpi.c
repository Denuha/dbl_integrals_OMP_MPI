#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

#define PI 3.1415926

double f1(double x)
{
    return sin(x);
}

double f2(double x, double y)
{
    return x*y;
}


int main(int argc, char **argv)
{
	//mpiicc integral_mpi.c
	//mpirun ./a.out
	//mpirun -np 10 ./a.out

	int N = 100000;
	int myrank, ranksize, i, j, n;
    double s1, s2, min_time, h, h1, h2;
    double eps = 0.000001;
    int iter_max = N+1;
    // Initialize the MPI environment
	int errCode = MPI_Init(&argc, &argv);
	if (errCode != 0)
	{
		return errCode;
	}
		
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	//Определяем размер группы:
	MPI_Comm_size(MPI_COMM_WORLD, &ranksize);
	
	if (myrank == 0)
		printf("MPI Threads: %d\n\n", ranksize);
	n = N;
	do
	{
		s1 = 0;
		min_time = INT_MAX;
		for (i = 0; i< 10; i++)
		{
			double sum = 0;
			double a = 0.;
			double b = PI;
			h = fabs((b-a)/n);

			double start_time = MPI_Wtime();
		
			MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
			for (i = myrank; i < n; i+=ranksize)
			{
				double x = a + i*h + h/2;
				sum += f1(x);
			}
			MPI_Reduce(&sum,&s1, 1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
            double time = MPI_Wtime() - start_time;
			min_time = time < min_time ? time : min_time;
		} // for
		n *= 2;
	} while (  ( fabs(s1-2.0) > eps )   && (n < iter_max) );	
	
	if (myrank == 0)
	{
		printf("Integral: f=sin(x) [0;Pi], n = %d\n", n/2);
		printf("min_time (of 10) [sec]: %.10f\n", min_time);
		printf("res = %.10f\n\n", s1*h);
	}

	// double integral
	n = N;
	do
	{
		s1 = 0;
		min_time = INT_MAX;
		for (i = 0; i < 10; i++)
		{
			double sum = 0;
			double a = 1.;
			double b = 2;
			double c = 1;
			double d = 2;
			h1 = fabs((b-a)/n);
			h2 = fabs((d-c)/n);

			double start_time = MPI_Wtime();
		
			MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
			for (i = myrank; i < n; i+=ranksize)
			{				
				for (j = 0; j < n; j++)
				{
					double x = a + i*h1 + h1/2;
					double y = c + j*h2 + h2/2;
					sum += f2(x,y);        
				}  
			}
			MPI_Reduce(&sum,&s2, 1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
            double time = MPI_Wtime() - start_time;
			min_time = time < min_time ? time : min_time;
		} // for
		n *= 2;
	} while (  ( fabs(s2-2.25) > eps )   && (n < iter_max) );
	
	if (myrank == 0)
	{
    	printf("Double integral: f=xy a = [1;2], b = [1;2], n,m = %d\n", n/2);
		printf("min_time (of 10) [sec]: %.10f\n", min_time);
		printf("res = %.10f\n\n", s2*h1*h2);
	}


	MPI_Finalize();
	return -1;
}

