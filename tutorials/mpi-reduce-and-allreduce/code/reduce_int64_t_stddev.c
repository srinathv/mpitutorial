// Author: Wes Kendall
// Copyright 2013 www.mpitutorial.com
// This code is provided freely with the tutorials on mpitutorial.com. Feel
// free to modify it for your own use. Any distribution of the code must
// either provide a link to www.mpitutorial.com or keep this header intact.
//
// Program that computes the standard deviation of an array of elements in parallel using
// MPI_Reduce.
//
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <assert.h>
#include <time.h>



// Default values
#define DEFAULT_ARG1 1000
#define DEFAULT_ARG2 1000



// Creates an array of random numbers. 
int64_t *create_rand_nums(int num_elements) {
  int64_t *rand_nums = (int64_t *)malloc(sizeof(int64_t) * num_elements);
  assert(rand_nums != NULL);
  int i;
  for (i = 0; i < num_elements; i++) {
    rand_nums[i] = (rand() );
  }
  return rand_nums;
}

int main(int argc, char *argv[]) {

    int arg1 = DEFAULT_ARG1; // Initialize with default value
    int arg2 = DEFAULT_ARG2; // Initialize with default value

    // Check if the first argument is provided
    if (argc > 1) {
        arg1 = atoi(argv[1]);
    }

    // Check if the second argument is provided
    if (argc > 2) {
        arg2 = atoi(argv[2]);
    }



  int num_elements_per_proc = atoi(argv[1]);

  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);


  for (int i = 0; i <= arg2; i++) { // repeated loops
  // Create a random array of elements on all processes.
  srand(time(NULL)*world_rank); // Seed the random number generator of processes uniquely
  int64_t *rand_nums = NULL;
  rand_nums = create_rand_nums(num_elements_per_proc);

  // Sum the numbers locally
  int64_t local_sum = 0;
  int i;
  for (i = 0; i < num_elements_per_proc; i++) {
    local_sum += rand_nums[i];
  }

  // Reduce all of the local sums into the global sum in order to
  // calculate the mean
  int64_t global_sum;
  MPI_Allreduce(&local_sum, &global_sum, 1, MPI_INT64_T, MPI_SUM,
                MPI_COMM_WORLD);
  float mean = global_sum / (num_elements_per_proc * world_size);

  // Compute the local sum of the squared differences from the mean
  float local_sq_diff = 0;
  for (i = 0; i < num_elements_per_proc; i++) {
    local_sq_diff += (rand_nums[i] - mean) * (rand_nums[i] - mean);
  }

  // Reduce the global sum of the squared differences to the root process
  // and print off the answer
  float global_sq_diff;
  MPI_Reduce(&local_sq_diff, &global_sq_diff, 1, MPI_FLOAT, MPI_SUM, 0,
             MPI_COMM_WORLD);

  // The standard deviation is the square root of the mean of the squared
  // differences.
  if (world_rank == 0) {
    float stddev = sqrt(global_sq_diff /
                        (num_elements_per_proc * world_size));
    printf("Mean - %f, Standard deviation = %f\n", mean, stddev);
  }

  // Clean up
  free(rand_nums);

  MPI_Barrier(MPI_COMM_WORLD);
} // loop of i over argv2
  MPI_Finalize();
}
