#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <math.h>
#include <sys/stat.h>

#define BILLION 1000000000.0

struct stat st = {0};

/* runs code we want to time, returns execution time */
double timer()
{
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    
    /* Place code which you 
        want to time here */ 
    
    clock_gettime(CLOCK_REALTIME, &end);

    //time_spent = end - start
    double time_spent = (end.tv_sec - start.tv_sec) + 
                        (end.tv_nsec - start.tv_nsec) / BILLION;

    printf("Runtime: %f \n", time_spent);
    return time_spent;
}

double* create_array(int a_size)
{
    double *a = malloc (a_size * sizeof(double));
    if (a ==NULL)
    {
        printf("Error allocating memory");
        exit(1);
    }
    return a;
}

void std_calc(double sum, double *a, int a_size, double average)
{
    float variance = 0.0, stdDev;

    /* calculate variance */
    for (int i = 0; i < a_size; i++)
    {
        variance += pow(a[i] - average,2.0);
        variance /= a_size;
    }

    stdDev = sqrt(variance);
    
    printf("\n Number of trials: %d\n", a_size);
    printf("Average: %f\n", average);
    printf("Standard Deviation: %f\n", stdDev);
    printf("Variance: %f\n", variance);
}

int main()
{
    int num_trials = 0;
    double time_sum = 0.0;
    double average = 0.0;
    
    printf("Enter the number of trials to run: \n");
    scanf("%d", &num_trials);

    int a_size = num_trials;
    double *a = create_array(a_size);

    printf( "%d \n", num_trials);
    
    for (int i = 0; i < num_trials; i++)
    {
        a[i] = timer();
        time_sum += a[i];
    }
    average = time_sum/num_trials;

    std_calc(time_sum, a, num_trials, average);
    
    free(a);
    return 0;
}
