using namespace std;

#include <iostream>
#include <mpi.h>


double int_function(double);
double trapez_rule(double, double, int, double (*)(double));


int main(int nargs, char* args[])
{
    int n, local_n, numprocs, my_rank;
    double a, b, h, local_a, local_b, total_sum, local_sum;
    double  time_start, time_end, total_time;

    //  Start MPI 
    MPI_Init(&nargs, &args);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    time_start = MPI_Wtime();

    a = 0.0; b = 1.0;  n = 1000;
    h = (b - a) / n;

    local_n = n / numprocs;

    local_a = a + my_rank * local_n * h;
    local_b = local_a + local_n * h;
    total_sum = 0.0;
    local_sum = trapez_rule(local_a, local_b, local_n, &int_function);
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    time_end = MPI_Wtime();
    total_time = time_end - time_start;
    if (my_rank == 0) {
        cout << "Trapezoidal rule = " << total_sum << endl;
        cout << "Time = " << total_time << " on num of processors: " << numprocs << endl;
    }
    // End MPI
    MPI_Finalize();
    return 0;
}  // 

//  Function of integration
double int_function(double x)
{
    double value = 4. / (1. + x * x);
    return value;
}

//  Trapezoidal method
double trapez_rule(double a, double b, int n, double (*func)(double))
{
    double trapez_sum;
    double fa, fb, x, step;
    int    j;
    step = (b - a) / ((double)n);
    fa = (*func)(a) / 2.;
    fb = (*func)(b) / 2.;
    trapez_sum = 0.;
    for (j = 1; j <= n - 1; j++) {
        x = j * step + a;
        trapez_sum += (*func)(x);
    }
    trapez_sum = (trapez_sum + fb + fa) * step;
    return trapez_sum;
}