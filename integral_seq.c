#include <stdio.h>
#include <math.h>
#include <omp.h>
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

double integral_rectangle(double a, double b, int n)
{
    double h = fabs((b-a)/n);
    double sum = 0;

    int i;
    double x=0;

    for (i = 0; i < n; i++)
    {
        double x = a + i*h + h/2;
        sum += f1(x);
    }
    return sum*h;
}

double integral_dbl_rectangle(double a, double b, double c, double d, int n, int m)
{    
    double h1 = fabs((b-a)/n);
    double h2 = fabs((d-c)/m);
    double sum = 0.0;

    int i,j;
    double x=0,y=0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            x = a + i*h1 + h1/2;
            y = c + j*h2 + h2/2;
            sum += f2(x,y);        
        }  
    }   
    return sum*h1*h2;
}

int main()
{
    // module add intel/v2019.0.018
    // icc -qopenmp integral_seq.c -mkl -o a.out
    // sbatch script_omp_integral_seq.sh

    printf("Sequentially: \n\n");

    int i,n;
    int N = 200000;
    double eps = 0.000001; // 1/10^10
    int iter_max = N+1;
    double s1, s2, min_time;

    n = N;
    do
    {    
        s1=0;
        min_time = INT_MAX;
        for (i = 0; i < 10; i++)
        {
            double start_time = omp_get_wtime();   
            s1 = integral_rectangle(0, PI, n);    
            double time = omp_get_wtime() - start_time;
            //printf("time [sec]: %f  %.10f \n", time, s1);
            //if (time < min_time) min_time = time;
            min_time = time < min_time ? time : min_time;
        }
        n *= 2;
    } while (  ( fabs(s1-2.0) > eps )   && (n < iter_max) );
    printf("Integral: f=sin(x) [0;Pi], n = %d\n", n/2);
    printf("min_time (of 10) [sec]: %.10f\n", min_time);
    printf("res = %.10f\n\n", s1);
    
    n = N;
    do
    {    
        s2 = 0;
        min_time = INT_MAX;
        for (i = 0; i < 10; i++)
        {
            double start_time = omp_get_wtime();   
            s2 = integral_dbl_rectangle(1, 2, 1, 2, n, n);    
            double time = omp_get_wtime() - start_time;
            //printf("time [sec]: %f  %.10f \n", time, s1);
            //if (time < min_time) min_time = time;
            min_time = time < min_time ? time : min_time;
        }
        n *= 2;
    } while (  ( fabs(s1-2.25) > eps )   && (n < iter_max) );

    printf("Double integral: f=xy a = [1;2], b = [1;2], n,m = %d\n", n/2);
    printf("min_time (of 10) [sec]: %.10f\n", min_time);
    printf("res = %.10f\n\n", s2);

    return 0;
}
